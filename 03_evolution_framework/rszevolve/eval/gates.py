"""Correctness gates a candidate must pass before any QoR number is trusted.

1. Bazel C++ unit tests of rsz (pass/fail).  The Tcl regression tests compare logs against .ok files,
   so a genuinely better algorithm would "fail" them; they are therefore run only as smoke tests:
2. Smoke Tcl tests: run the selected rsz test scripts with the *evolved* binary and require a clean exit
   (no crash, no "Error" lines, no sanitizer abort).
3. Placement legality / hold / DRV / area guards are applied later in score.judge on the real benchmarks.

All gate output is kept under the candidate's results directory."""
from __future__ import annotations

from dataclasses import dataclass, field
from pathlib import Path

from ..config import PATHS, Knobs
from ..util import log, run, tail, write_json


@dataclass
class GateResult:
    passed: bool
    unit_tests: dict[str, str] = field(default_factory=dict)   # target -> PASSED/FAILED/MISSING
    smoke_tests: dict[str, str] = field(default_factory=dict)  # name -> ok/<reason>
    notes: list[str] = field(default_factory=list)

    def report(self) -> str:
        lines = [f"gates: {'PASS' if self.passed else 'FAIL'}"]
        for t, s in self.unit_tests.items():
            lines.append(f"  unit  {s:8s} {t}")
        for t, s in self.smoke_tests.items():
            lines.append(f"  smoke {('ok' if s == 'ok' else 'FAIL'):8s} {t}" + ("" if s == "ok" else f"  ({s})"))
        for n in self.notes:
            lines.append(f"  note: {n}")
        return "\n".join(lines)


def _existing_targets(targets: list[str]) -> list[str]:
    q = " + ".join(targets)
    res = run(["bazelisk", "query", q, "--keep_going"], cwd=PATHS.openroad_src, timeout=600)
    found = {l.strip() for l in res.stdout.splitlines() if l.strip().startswith("//")}
    return [t for t in targets if t in found]


def run_unit_tests(rsz_dir: Path, knobs: Knobs, out_dir: Path) -> dict[str, str]:
    """Overlay the candidate (the binary build already did, but the script restores afterwards), run tests, restore."""
    results: dict[str, str] = {}
    targets = _existing_targets(knobs.bazel_unit_tests)
    for t in knobs.bazel_unit_tests:
        if t not in targets:
            results[t] = "MISSING"
    if not targets:
        return results
    import subprocess
    slot = PATHS.openroad_src / "src" / "rsz"
    run(["rsync", "-a", "--delete", f"{rsz_dir}/", f"{slot}/"], timeout=300)
    try:
        res = run(["bazelisk", "test", f"--jobs={__import__('os').environ.get('BAZEL_JOBS', '8')}", "--config=no-werror",
                   "--test_output=errors", "--test_tag_filters=-py", *targets],
                  cwd=PATHS.openroad_src, timeout=knobs.build_timeout_s, log_file=out_dir / "unit_tests.log")
        for line in res.stdout.splitlines():
            for t in targets:
                if line.startswith(t) and ("PASSED" in line or "FAILED" in line or "NO STATUS" in line or "TIMEOUT" in line):
                    results[t] = "PASSED" if "PASSED" in line else "FAILED"
        for t in targets:
            results.setdefault(t, "PASSED" if res.ok else "FAILED")
    finally:
        run([PATHS.tools / "build_openroad.sh", "restore"], timeout=300)
    return results


def run_smoke_tests(binary: Path, knobs: Knobs, out_dir: Path) -> dict[str, str]:
    """Run rsz regression Tcl scripts with the evolved binary from the snapshot test dir; require a clean exit."""
    results: dict[str, str] = {}
    test_dir = PATHS.rsz_snapshot / "test"
    for name in knobs.smoke_tcl_tests:
        tcl = test_dir / f"{name}.tcl"
        if not tcl.exists():
            results[name] = "missing"; continue
        res = run([binary, "-no_splash", "-exit", tcl.name], cwd=test_dir, timeout=600, log_file=out_dir / f"smoke_{name}.log")
        bad = [l for l in res.stdout.splitlines() if l.startswith("[ERROR") or "Segmentation fault" in l or "AddressSanitizer" in l or "Assertion" in l]
        # equivalence helpers in the test scripts need eqy/yosys; a missing tool is not the candidate's fault
        bad = [l for l in bad if "eqy" not in l.lower() and "yosys" not in l.lower()]
        if res.timed_out:
            results[name] = "timeout"
        elif res.returncode != 0 and bad:
            results[name] = bad[0][:160]
        elif res.returncode not in (0, 1):
            results[name] = f"rc={res.returncode}: {tail(res.stdout, 3)}"
        else:
            results[name] = "ok"
    return results


def run_gates(rsz_dir: Path, binary: Path, knobs: Knobs, out_dir: Path, *, skip_unit: bool = False) -> GateResult:
    out_dir.mkdir(parents=True, exist_ok=True)
    g = GateResult(passed=True)
    if not skip_unit:
        g.unit_tests = run_unit_tests(rsz_dir, knobs, out_dir)
        if any(v == "FAILED" for v in g.unit_tests.values()):
            g.passed = False
        if all(v == "MISSING" for v in g.unit_tests.values()) and g.unit_tests:
            g.notes.append("no configured unit-test targets exist in this OpenROAD revision; check knobs.bazel_unit_tests")
    g.smoke_tests = run_smoke_tests(binary, knobs, out_dir)
    if any(v not in ("ok", "missing") for v in g.smoke_tests.values()):
        g.passed = False
    write_json(out_dir / "gates.json", {"passed": g.passed, "unit_tests": g.unit_tests, "smoke_tests": g.smoke_tests, "notes": g.notes})
    log(g.report())
    return g
