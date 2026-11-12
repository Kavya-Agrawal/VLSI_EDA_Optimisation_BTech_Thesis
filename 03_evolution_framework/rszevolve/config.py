"""Paths and knobs. The repo layout is fixed (numbered folders); knobs come from config/default.json
and can be overridden by CLI flags or environment variables (see tools/env.sh)."""
from __future__ import annotations

import json
import os
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any

FRAMEWORK_DIR = Path(__file__).resolve().parent.parent          # 03_evolution_framework
ROOT = Path(os.environ.get("ROOT", FRAMEWORK_DIR.parent)).resolve()


def _env_path(name: str, default: Path) -> Path:
    v = os.environ.get(name)
    return Path(v).expanduser().resolve() if v else default


@dataclass
class Paths:
    root: Path = ROOT
    docs: Path = ROOT / "00_docs"
    original: Path = ROOT / "01_openroad_original"
    rsz_snapshot: Path = ROOT / "01_openroad_original" / "rsz_snapshot"
    evolved: Path = ROOT / "02_openroad_evolved"
    champion: Path = ROOT / "02_openroad_evolved" / "champion" / "rsz"
    candidates: Path = ROOT / "02_openroad_evolved" / "candidates"
    lineage: Path = ROOT / "02_openroad_evolved" / "lineage.json"
    framework: Path = FRAMEWORK_DIR
    benchmarks: Path = ROOT / "04_benchmarks"
    designs: Path = ROOT / "04_benchmarks" / "designs"
    tiers: Path = ROOT / "04_benchmarks" / "tiers.json"
    orfs_runs: Path = ROOT / "04_benchmarks" / "orfs_runs"
    baseline: Path = ROOT / "05_baseline_results"
    results: Path = ROOT / "06_evolved_results"
    viz: Path = ROOT / "07_visualizations"
    graphify: Path = ROOT / "08_graphify"
    context: Path = ROOT / "09_agent_context"
    knowledge: Path = ROOT / "10_agent_knowledge"
    agent_data: Path = ROOT / "11_agent_data"
    tools: Path = ROOT / "tools"
    openroad_src: Path = field(default_factory=lambda: _env_path("OPENROAD_SRC", ROOT / "external" / "OpenROAD"))
    orfs_src: Path = field(default_factory=lambda: _env_path("ORFS_SRC", ROOT / "external" / "OpenROAD-flow-scripts"))
    build: Path = field(default_factory=lambda: _env_path("BUILD_DIR", ROOT / "build"))
    tcl: Path = FRAMEWORK_DIR / "rszevolve" / "eval" / "tcl"
    prompts: Path = FRAMEWORK_DIR / "rszevolve" / "agents" / "prompts"
    context_prompts: Path = FRAMEWORK_DIR / "rszevolve" / "context" / "prompts"

    @property
    def openroad_stock(self) -> Path:
        return _env_path("OPENROAD_STOCK", self.build / "bin" / "openroad_stock")

    @property
    def openroad_evolved(self) -> Path:
        return _env_path("OPENROAD_EVOLVED", self.build / "bin" / "openroad_evolved")

    @property
    def claude_bin(self) -> str:
        v = os.environ.get("CLAUDE_BIN")
        if v:
            return v
        import shutil, glob
        if shutil.which("claude"):
            return "claude"
        cands = sorted(glob.glob(os.path.expanduser("~/.vscode/extensions/anthropic.claude-code-*/resources/native-binary/claude")))
        return cands[-1] if cands else "claude"

    @property
    def yosys(self) -> str:
        return os.environ.get("YOSYS_EXE") or "yosys"


@dataclass
class Knobs:
    """Everything a user may want to tune. Defaults in config/default.json."""
    # models
    planner_model: str = "opus"
    coder_model: str = "opus"
    evaluator_model: str = "sonnet"
    context_model: str = "sonnet"
    # agent limits
    planner_max_turns: int = 30
    coder_max_turns: int = 80
    evaluator_max_turns: int = 20
    repair_attempts: int = 3                   # compile-error fix rounds per candidate
    # evaluation
    repair_timing_args: str = "-setup -repair_tns 100 -verbose"
    eval_timeout_s: int = 1800
    build_timeout_s: int = 7200
    path_count: int = 20                       # worst paths reported per design
    sdc_variant: str = "stressed"              # which SDC the loop scores on
    stressed_wns_target_ratio: float = -0.08   # calibrate stressed period so stock post-repair WNS ~= -8% of period
    # acceptance
    min_score_gain: float = 0.002              # paired score must beat champion by this much
    hold_wns_tolerance_ns: float = 0.005
    drv_tolerance: int = 0                     # extra DRV violations allowed vs champion
    area_tolerance_pct: float = 10.0           # candidate may grow area by at most this %
    # unit tests (bazel targets, pass/fail) and smoke tcl tests (must not crash/error)
    bazel_unit_tests: list[str] = field(default_factory=lambda: [
        "//src/rsz/test:cpp_tests", "//src/rsz/test:TestResizer", "//src/rsz/test:TestPreChecks",
        "//src/rsz/test:TestSkewBudget", "//src/rsz/test:TestInsertBuffer", "//src/rsz/test:TestNestedJournal",
    ])
    smoke_tcl_tests: list[str] = field(default_factory=lambda: [
        "repair_setup1", "repair_setup2", "repair_setup3", "repair_setup4", "repair_setup5",
        "repair_hold1", "repair_hold2", "repair_hold3", "repair_design1", "repair_design2",
    ])
    # graphify
    graphify_bin: str = "graphify"

    @classmethod
    def load(cls, path: Path | None = None, overrides: dict[str, Any] | None = None) -> "Knobs":
        k = cls()
        p = path or (FRAMEWORK_DIR / "config" / "default.json")
        if p.exists():
            for key, val in json.loads(p.read_text()).items():
                if hasattr(k, key) and not key.startswith("_"):
                    setattr(k, key, val)
        for key, val in (overrides or {}).items():
            if val is not None and hasattr(k, key):
                setattr(k, key, val)
        return k


PATHS = Paths()


def load_tiers() -> dict[str, list[str]]:
    d = json.loads(PATHS.tiers.read_text())
    return {k: v for k, v in d.items() if isinstance(v, list)}


def designs_for_tier(tier: str) -> list[str]:
    tiers = load_tiers()
    if tier == "all":
        seen: list[str] = []
        for t in ("A", "B", "C"):
            for d in tiers.get(t, []):
                if d not in seen:
                    seen.append(d)
        return seen
    if tier not in tiers:
        raise SystemExit(f"unknown tier {tier!r}; known: {sorted(tiers)}")
    return list(tiers[tier])
