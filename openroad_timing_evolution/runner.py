"""Real OpenROAD/ORFS evaluation; no synthetic QoR fallback."""
from __future__ import annotations

import fcntl
import hashlib
import json
from pathlib import Path
import re
import shutil
import uuid
import xml.etree.ElementTree as ET

from . import kernel
from .metrics import Rejected, validate
from .policy import Policy, canonical
from .workspace import ROOT, Workspace, sha

REGRESSIONS = ("repair_setup_undo1", "repair_setup_undo2", "repair_setup_wns_guard",
               "repair_hold1", "repair_hold2")


def load_config(path):
    cfg = json.loads(Path(path).read_text())
    expected = set(json.loads((ROOT/"config/smoke.json").read_text()))
    if set(cfg) != expected or cfg["schema"] != 1:
        raise ValueError("unknown/missing configuration keys or schema")
    for k in ("jobs", "timeout_seconds", "seed", "replicates"):
        if type(cfg[k]) is not int or cfg[k] < 1:
            raise ValueError(f"invalid {k}")
    if cfg["jobs"] > 8 or cfg["replicates"] < 3:
        raise ValueError("use 1-8 jobs and at least 3 replicates")
    import math
    for k in ("max_area_regression", "max_wirelength_regression", "max_runtime_regression", "min_improvement"):
        if type(cfg[k]) not in (int,float) or not math.isfinite(cfg[k]) or not 0 <= cfg[k] <= 1:
            raise ValueError(f"invalid limit: {k}")
    for k in ("openroad_revision", "orfs_revision"):
        if not re.fullmatch(r"[0-9a-f]{40}", cfg[k]):
            raise ValueError("revisions must be full commit IDs")
    all_designs = []
    for split in ("train", "validation", "test"):
        if type(cfg[split]) is not list or not cfg[split]:
            raise ValueError("all benchmark splits must be nonempty")
        for d in cfg[split]:
            if type(d) is not str or not re.fullmatch(r"[a-z0-9_]+", d):
                raise ValueError("invalid design name")
        all_designs.extend(cfg[split])
    if len(set(all_designs)) != len(all_designs):
        raise ValueError("benchmark splits overlap or contain duplicates")
    return cfg


def formal_script(lib, before, after, top):
    def stage(path, name):
        return (f'read_liberty -ignore_miss_func "{lib}"\nread_verilog "{path}"\n'
                f'hierarchy -check -top {top}\nproc\nflatten\nopt_clean\n'
                f'rename {top} {name}\ndesign -stash {name}\n')
    return (stage(before,"gold") + stage(after,"gate")
            + "design -copy-from gold -as gold gold\ndesign -copy-from gate -as gate gate\n"
            + "equiv_make gold gate equiv\nhierarchy -check -top equiv\nequiv_simple\n"
            + "equiv_induct -seq 8\nequiv_status -assert\n")


class Campaign:
    def __init__(self, config):
        self.config = config
        self.ws = Workspace(config)
        self.lock = (self.ws.work/"campaign.lock").open("a")
        try:
            fcntl.flock(self.lock, fcntl.LOCK_EX | fcntl.LOCK_NB)
        except BlockingIOError:
            raise RuntimeError("another timing campaign is using this workspace")
        self.ws.prepare()
        self.id = uuid.uuid4().hex[:12]
        self.directory = self.ws.work/"runs"/self.id
        self.directory.mkdir(parents=True)
        # Pin the evaluator itself, template, adapter, config, source, flow and image.
        self.protocol = {"config": config, "docker_image_id": self.ws.image,
                         "files": {str(p.relative_to(ROOT)): sha(p)
                                   for p in sorted(ROOT.rglob("*")) if p.is_file()
                                   and p.parts[len(ROOT.parts)] in ("cpp","tcl","patches")}}
        self.protocol["files"].update({p.name: sha(p) for p in sorted(ROOT.glob("*.py"))})
        self.protocol_sha = hashlib.sha256(canonical(self.protocol).encode()).hexdigest()
        self.write("protocol.json", self.protocol)
        self.audit_binary = self.directory/"stock-openroad"
        self.audit_sha = None
        self.baselines = {}

    def write(self, name, data):
        (self.directory/name).write_text(json.dumps(data, indent=2, allow_nan=False)+"\n")

    def archive(self, record):
        with (self.directory/"archive.jsonl").open("a") as stream:
            stream.write(canonical(record)+"\n")
            stream.flush()
            import os
            os.fsync(stream.fileno())

    def assert_protocol(self):
        for rel, digest in self.protocol["files"].items():
            if sha(ROOT/rel) != digest:
                raise RuntimeError("trusted evaluator changed during campaign")
        if self.audit_sha and sha(self.audit_binary) != self.audit_sha:
            raise RuntimeError("frozen audit binary changed")

    def container_path(self, p):
        return "/experiment/"+str(Path(p).relative_to(self.ws.work))

    def build_candidate(self, policy):
        self.assert_protocol()
        directory = self.directory/policy.id
        directory.mkdir(exist_ok=True)
        saved = directory/"openroad"
        if saved.exists():
            if sha(saved) != (directory/"binary.sha256").read_text().strip():
                raise Rejected("cached compiled candidate changed")
            self.ws.write_policy(policy)
            self.ws.integrity(policy)
            return saved
        (directory/"policy.json").write_text(canonical(policy.data())+"\n")
        (directory/"EvolvedPathDriverPolicy.h").write_text(policy.header())
        kernel.check(policy, directory/"kernel")
        self.ws.write_policy(policy)
        binary = self.ws.build(policy, directory)
        # Compile targets for tests, then require an exact nonempty CTest selection.
        regex = r"^rsz\.(" + "|".join(REGRESSIONS) + r")\.tcl$"
        self.ws.execute(["ctest", "--test-dir", "/experiment/build", "--show-only=json-v1", "-R", regex], directory/"tests-list.log")
        log = (directory/"tests-list.log").read_text().split("\n",1)[1]
        names = {t["name"] for t in json.loads(log)["tests"]}
        if names != {f"rsz.{t}.tcl" for t in REGRESSIONS}:
            raise Rejected("upstream regression coverage is missing")
        self.ws.execute(["ctest", "--test-dir", "/experiment/build", "--no-tests=error",
                         "--output-on-failure", "-R", regex], directory/"regressions.log")
        shutil.copy2(binary, saved)
        (directory/"binary.sha256").write_text(sha(saved)+"\n")
        if not policy.enabled:
            shutil.copy2(saved, self.audit_binary)
            self.audit_sha = sha(self.audit_binary)
        self.ws.integrity(policy)
        return saved

    def measure(self, policy, binary, design, replica):
        self.assert_protocol()
        self.ws.integrity(policy)
        case = self.directory/policy.id/f"{design}-r{replica}"
        case.mkdir()  # existing output is an error, never reused as fresh evidence
        cp = self.container_path(case)
        binary_sha = sha(binary)
        argv = ["make", "-C", "/experiment/orfs/flow", f"DESIGN_CONFIG=designs/nangate45/{design}/config.mk",
                f"WORK_HOME={cp}/flow", "FLOW_VARIANT=base", f"NUM_CORES={self.config['jobs']}",
                f"OPENROAD_EXE={self.container_path(binary)}", "YOSYS_EXE=/usr/local/bin/yosys",
                "KLAYOUT_CMD=/usr/bin/klayout", "SYNTH_REPEATABLE_BUILD=1", "all", "drc"]
        elapsed = self.ws.execute(argv, case/"flow.log")
        results = case/f"flow/results/nangate45/{design}/base"
        logs = case/f"flow/logs/nangate45/{design}/base"
        required = [results/name for name in ("1_1_yosys.v", "6_final.v", "6_final.odb", "6_final.sdc", "6_final.spef", "6_final.gds")]
        for path in required:
            if not path.is_file() or path.stat().st_size == 0:
                raise Rejected(f"missing final-flow artifact: {path.name}")
        if policy.enabled:
            marker = f"RSZ_EVOLVE policy={policy.id} exercised="
            if not any(marker in p.read_text(errors="replace") for p in logs.glob("*.log")):
                raise Rejected("candidate was never exercised on a nontrivial path")
        library = "/experiment/orfs/flow/platforms/nangate45/lib/NangateOpenCellLibrary_typical.lib"
        params = ["env", f"EVO_LIB={library}"]
        for env, name in (("EVO_ODB","6_final.odb"),("EVO_SDC","6_final.sdc"),("EVO_SPEF","6_final.spef")):
            params.append(f"{env}={self.container_path(results/name)}")
        self.ws.execute([*params, self.container_path(self.audit_binary), "-no_init", "-exit",
                         "-metrics", cp+"/audit.json", "/framework/tcl/audit.tcl"], case/"audit.log")
        if "RSZ_EVOLVE_AUDIT_PASS" not in (case/"audit.log").read_text():
            raise Rejected("independent STA audit did not finish")
        design_config = (self.ws.orfs/f"flow/designs/nangate45/{design}/config.mk").read_text()
        tops = re.findall(r"^export DESIGN_NAME\s*=\s*([A-Za-z_][A-Za-z_0-9]*)\s*$", design_config, re.M)
        if len(tops) != 1:
            raise Rejected("adapter requires one literal DESIGN_NAME")
        script = formal_script(library, self.container_path(results/"1_1_yosys.v"),
                               self.container_path(results/"6_final.v"), tops[0])
        (case/"equivalence.ys").write_text(script)
        self.ws.execute(["yosys", "-s", cp+"/equivalence.ys"], case/"formal.log")
        if "Equivalence successfully proven!" not in (case/"formal.log").read_text():
            raise Rejected("formal proof success was not reported")
        # KLayout's XML report must exist and contain a real report-database root.
        drc_file = case/f"flow/reports/nangate45/{design}/base/6_drc.lyrdb"
        xml = ET.parse(drc_file).getroot()
        if xml.tag != "report-database" or xml.find("items") is None:
            raise Rejected("KLayout DRC unsupported or missing report structure")
        if list(xml.find("items")):
            raise Rejected("KLayout DRC violations")
        audit = json.loads((case/"audit.json").read_text())
        route = json.loads((logs/"5_2_route.json").read_text())
        def take(data, key):
            if key not in data:
                raise Rejected("required metric absent: "+key)
            return data[key]
        m = {"design":design,"replica":replica,"policy_id":policy.id,"binary_sha256":binary_sha,
             "audit_binary_sha256":self.audit_sha,"protocol_sha256":self.protocol_sha,
             "formal_pass":True,"audit_pass":True,"constraints_pass":take(audit,"evo__constraints_pass")==1,
             "flow_complete":True,"runtime_s":elapsed,
             "clock_period_ns":take(audit,"evo__period_ns"),"endpoint_count":take(audit,"evo__endpoints"),
             "area_um2":take(audit,"design__instance__area"),
             "wirelength_um":take(route,"detailedroute__route__wirelength"),
             "route_drc":take(route,"detailedroute__route__drc_errors"),
             "placement_violations":take(audit,"design__violations"),
             "antenna_nets":take(audit,"antenna__violating__nets"),
             "antenna_pins":take(audit,"antenna__violating__pins")}
        for domain in ("setup","hold"):
            for metric in ("wns","tns"):
                m[f"{domain}_{metric}_ns"] = take(audit,f"timing__{domain}__{metric}")
        for name in ("slew","cap","fanout"):
            m[f"max_{name}_violations"] = take(audit,f"timing__drv__max_{name}")
        m["clock_skew_setup_ns"] = take(audit,"clock__skew__setup")
        m["clock_skew_hold_ns"] = take(audit,"clock__skew__hold")
        validate(m)
        if sha(binary) != binary_sha:
            raise Rejected("candidate binary changed during flow")
        self.assert_protocol()
        self.ws.integrity(policy)
        (case/"metrics.json").write_text(json.dumps(m,indent=2)+"\n")
        (case/"artifacts.json").write_text(json.dumps({str(p.relative_to(case)):sha(p) for p in [*required, drc_file,case/"audit.json",case/"formal.log"]},indent=2)+"\n")
        return m

    def evaluate(self, policy, designs):
        record = {"policy":policy.data(),"policy_id":policy.id,"designs":designs,"status":"started"}
        self.archive(record)
        try:
            binary = self.build_candidate(policy)
            rows = [self.measure(policy,binary,d,r) for d in designs for r in range(self.config["replicates"])]
            self.archive({**record,"status":"evaluated","metrics":rows})
            return rows
        except Exception as exc:
            self.archive({**record,"status":"rejected","reason":str(exc)})
            raise

    def baseline(self, designs):
        missing = [d for d in designs if d not in self.baselines]
        if missing:
            rows = self.evaluate(Policy.stock(), missing)
            for d in missing:
                self.baselines[d] = [m for m in rows if m["design"]==d]
        return [m for d in designs for m in self.baselines[d]]
