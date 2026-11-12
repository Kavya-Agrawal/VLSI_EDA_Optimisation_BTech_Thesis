"""Run eval_repair_timing.tcl for a set of designs with a given openroad binary and collect results.

A design lives in 04_benchmarks/designs/<pdk>/<design>/ with a design.json:
{
  "pdk": "nangate45", "design": "gcd", "top": "gcd",
  "odb": "placed.odb",                       # relative to the design dir
  "sdc": {"nominal": "nominal.sdc", "stressed": "stressed.sdc"},
  "libs": ["/abs/path/NangateOpenCellLibrary_typical.lib"],
  "set_rc": "/abs/path/setRC.tcl",
  "dont_use": "TAPCELL_X1 FILLCELL_X1 AOI211_X1 OAI211_X1",
  "clock_period_ns": {"nominal": 0.25, "stressed": 0.19},
  "provenance": {...}
}
Results for one (design, variant, replicate) are a directory with metrics.json, paths_pre.json,
paths_post.json, openroad.log and or_metrics.json."""
from __future__ import annotations

import json
import shutil
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any

from ..config import PATHS, Knobs
from ..util import log, read_json, run, write_json


@dataclass
class Design:
    key: str                 # "nangate45/gcd"
    dir: Path
    meta: dict[str, Any]

    @property
    def odb(self) -> Path:
        return self.dir / self.meta["odb"]

    def sdc(self, variant: str) -> Path:
        return self.dir / self.meta["sdc"][variant]

    @property
    def libs(self) -> list[str]:
        return [str(Path(p) if Path(p).is_absolute() else self.dir / p) for p in self.meta["libs"]]

    @property
    def set_rc(self) -> str:
        p = self.meta["set_rc"]
        return str(Path(p) if Path(p).is_absolute() else self.dir / p)

    def period(self, variant: str) -> float:
        return float(self.meta["clock_period_ns"][variant])

    def ready(self, variant: str) -> bool:
        return self.odb.exists() and self.sdc(variant).exists()


def load_design(key: str) -> Design:
    d = PATHS.designs / key
    meta = read_json(d / "design.json")
    if not meta:
        raise FileNotFoundError(f"{d/'design.json'} missing: run `make checkpoints`")
    return Design(key, d, meta)


def env_for(design: Design, variant: str, out_dir: Path, knobs: Knobs, *, skip_repair: bool = False,
            repair_args: str | None = None, sdc_override: Path | None = None) -> dict[str, str]:
    return {
        "EVO_LIBS": ";".join(design.libs),
        "EVO_ODB": str(design.odb),
        "EVO_SDC": str(sdc_override or design.sdc(variant)),
        "EVO_SET_RC": design.set_rc,
        "EVO_OUT_DIR": str(out_dir),
        "EVO_REPAIR_ARGS": repair_args or knobs.repair_timing_args,
        "EVO_PATH_COUNT": str(knobs.path_count),
        "EVO_DONT_USE": design.meta.get("dont_use", ""),
        "EVO_SKIP_REPAIR": "1" if skip_repair else "0",
    }


@dataclass
class EvalRun:
    design: str
    variant: str
    replicate: int
    out_dir: Path
    ok: bool
    seconds: float
    metrics: dict[str, Any] = field(default_factory=dict)
    error: str = ""

    @property
    def post(self) -> dict[str, Any]:
        return self.metrics.get("post", {})

    @property
    def pre(self) -> dict[str, Any]:
        return self.metrics.get("pre", {})


def run_one(binary: Path, design: Design, variant: str, out_dir: Path, knobs: Knobs, *, replicate: int = 0,
            skip_repair: bool = False, repair_args: str | None = None, sdc_override: Path | None = None,
            timeout: int | None = None) -> EvalRun:
    out_dir.mkdir(parents=True, exist_ok=True)
    env = env_for(design, variant, out_dir, knobs, skip_repair=skip_repair, repair_args=repair_args, sdc_override=sdc_override)
    cmd = [binary, "-no_splash", "-exit", "-metrics", out_dir / "or_metrics.json", PATHS.tcl / "eval_repair_timing.tcl"]
    res = run(cmd, env=env, timeout=timeout or knobs.eval_timeout_s, log_file=out_dir / "openroad.log")
    metrics = read_json(out_dir / "metrics.json", {}) or {}
    ok = res.ok and bool(metrics.get("post"))
    err = ""
    if not ok:
        tail_lines = [l for l in res.stdout.splitlines() if "ERROR" in l or "Error" in l or "error" in l][-5:]
        err = ("timeout" if res.timed_out else f"rc={res.returncode}") + (": " + " | ".join(tail_lines) if tail_lines else "")
    er = EvalRun(design.key, variant, replicate, out_dir, ok, res.seconds, metrics, err)
    write_json(out_dir / "run.json", {"design": design.key, "variant": variant, "replicate": replicate, "ok": ok,
                                      "seconds": round(res.seconds, 2), "error": err, "binary": str(binary),
                                      "repair_args": env["EVO_REPAIR_ARGS"]})
    status = f"WNS {metrics.get('pre',{}).get('wns_setup','?')} -> {metrics.get('post',{}).get('wns_setup','?')}  TNS {metrics.get('pre',{}).get('tns_setup','?')} -> {metrics.get('post',{}).get('tns_setup','?')}" if ok else err
    log(f"eval {design.key}/{variant} r{replicate}: {'ok' if ok else 'FAIL'} in {res.seconds:.0f}s  {status}")
    return er


def run_suite(binary: Path, design_keys: list[str], variant: str, out_root: Path, knobs: Knobs, *,
              replicates: int = 1, **kw) -> list[EvalRun]:
    runs: list[EvalRun] = []
    for key in design_keys:
        try:
            d = load_design(key)
        except FileNotFoundError as e:
            log(f"skip {key}: {e}")
            continue
        if not d.ready(variant):
            log(f"skip {key}/{variant}: checkpoint or sdc missing")
            continue
        for r in range(replicates):
            runs.append(run_one(binary, d, variant, out_root / key.replace("/", "__") / f"{variant}_r{r}", knobs, replicate=r, **kw))
    write_json(out_root / "runs.json", [{k: (str(v) if isinstance(v, Path) else v) for k, v in vars(x).items() if k != "metrics"} | {"post": x.post, "pre": x.pre} for x in runs])
    return runs


def aggregate(runs: list[EvalRun]) -> dict[str, dict[str, Any]]:
    """Per design: mean/min/max over replicates of the key post-repair numbers, plus determinism flag."""
    by: dict[str, list[EvalRun]] = {}
    for r in runs:
        by.setdefault(r.design, []).append(r)
    out: dict[str, dict[str, Any]] = {}
    for key, rs in by.items():
        good = [r for r in rs if r.ok]
        if not good:
            out[key] = {"ok": False, "error": "; ".join(sorted({r.error for r in rs}))}
            continue
        def stat(field: str, src: str = "post") -> dict[str, float]:
            vals = [float(getattr(r, src).get(field, 0.0)) for r in good]
            return {"mean": sum(vals) / len(vals), "min": min(vals), "max": max(vals)}
        wns = stat("wns_setup"); tns = stat("tns_setup")
        out[key] = {
            "ok": True, "replicates": len(good), "failed": len(rs) - len(good),
            "period_ns": float(good[0].metrics.get("clock_period_ns", 0)),
            "endpoints": int(good[0].metrics.get("endpoints", 0)),
            "pre": {"wns_setup": good[0].pre.get("wns_setup"), "tns_setup": good[0].pre.get("tns_setup"),
                    "setup_violations": good[0].pre.get("setup_violations")},
            "post": {
                "wns_setup": wns, "tns_setup": tns,
                "wns_hold": stat("wns_hold"), "tns_hold": stat("tns_hold"),
                "setup_violations": stat("setup_violations"), "hold_violations": stat("hold_violations"),
                "area_um2": stat("area_um2"), "util": stat("util"), "instances": stat("instances"), "buffers": stat("buffers"),
                "drv": stat("drv_slew")["mean"] + stat("drv_cap")["mean"] + stat("drv_fanout")["mean"],
                "placement_violations": max(float(r.metrics.get("placement_violations", 0) or 0) for r in good),
            },
            "repair_ms": stat("repair_ms", "metrics") if all("repair_ms" in r.metrics for r in good) else None,
            "deterministic": (wns["max"] - wns["min"] < 1e-6) and (tns["max"] - tns["min"] < 1e-6),
            "dirs": [str(r.out_dir) for r in good],
        }
    return out
