"""Lineage (which candidate came from which champion, verdicts, scores) and the agents' knowledge files.

02_openroad_evolved/lineage.json   machine-readable history of every iteration
02_openroad_evolved/champion.json  what the current champion is and where its evaluation lives
10_agent_knowledge/rulebase.md     self-evolving rules the planner maintains
10_agent_knowledge/lessons.md      free-form lessons appended by the planner
10_agent_knowledge/hypotheses_ledger.md   one line per hypothesis with its outcome
10_agent_knowledge/dead_ends.md    ideas that failed and why (so they are not retried blindly)"""
from __future__ import annotations

import shutil
from pathlib import Path
from typing import Any

from ..config import PATHS
from ..util import now_iso, read_json, write_json, write_text

RULEBASE_SEED = """# Rulebase (self-evolving)

The planner may add, relax or tighten rules here after each iteration. Keep rules short and testable.
Rules marked [fixed] are safety constraints and cannot be removed by agents.

## Safety [fixed]
- Only files under the candidate `rsz/` tree may be edited. Never touch OpenSTA, odb, dbSta or other modules.
- The resizer must keep the design logically equivalent: no change to the netlist function, only sizing,
  buffering (insert/remove), cloning, pin swapping on commutative pins and VT swaps.
- Any move must keep the placement legalizable (`detailed_placement` must succeed) and must not create DRV
  violations beyond the reference.
- No non-determinism: no unordered iteration over pointer-keyed containers that changes results, no
  wall-clock-dependent decisions, no threads whose scheduling changes the outcome.
- Do not spend the iteration on runtime micro-optimisation or data-structure refactoring; the objective is
  WNS/TNS after `repair_timing`, judged by the evaluator.

## Method
- One hypothesis per iteration, written down before coding: problem -> current heuristic -> new approach ->
  why WNS/TNS should improve -> risks -> how we will see it in the path report.
- Prefer changes to *what* the algorithm decides (ordering, selection, acceptance, search strategy, cost
  model) over changes to *how fast* it does it.
- Read the evaluator's worst-path attribution before choosing a cluster; attack the dominant cause.
"""

LESSONS_SEED = "# Lessons\n\nAppended by the planner after each iteration. Newest at the bottom.\n"
LEDGER_SEED = "# Hypotheses ledger\n\n| iter | cluster | hypothesis (short) | verdict | score vs champion | note |\n|---|---|---|---|---|---|\n"
DEAD_ENDS_SEED = "# Dead ends\n\nIdeas that were tried and failed, with the reason. Check before proposing something similar.\n"


def ensure_knowledge_files() -> None:
    PATHS.knowledge.mkdir(parents=True, exist_ok=True)
    for name, seed in (("rulebase.md", RULEBASE_SEED), ("lessons.md", LESSONS_SEED),
                       ("hypotheses_ledger.md", LEDGER_SEED), ("dead_ends.md", DEAD_ENDS_SEED)):
        p = PATHS.knowledge / name
        if not p.exists():
            write_text(p, seed)


def read_knowledge() -> dict[str, str]:
    ensure_knowledge_files()
    return {p.stem: p.read_text() for p in sorted(PATHS.knowledge.glob("*.md")) if p.name != "README.md"}


def append_ledger(iteration: int, cluster: str, hypothesis: str, verdict: str, score: float, note: str = "") -> None:
    ensure_knowledge_files()
    p = PATHS.knowledge / "hypotheses_ledger.md"
    short = hypothesis.strip().replace("\n", " ")[:140].replace("|", "/")
    with p.open("a") as f:
        f.write(f"| {iteration} | {cluster} | {short} | {verdict} | {score:+.5f} | {note.replace('|', '/')[:120]} |\n")


def append_section(filename: str, title: str, body: str) -> None:
    ensure_knowledge_files()
    p = PATHS.knowledge / filename
    with p.open("a") as f:
        f.write(f"\n## {title}\n\n{body.strip()}\n")


# ----------------------------------------------------------------------------- lineage / champion

def load_lineage() -> dict[str, Any]:
    return read_json(PATHS.lineage, {"iterations": [], "champion_history": []}) or {"iterations": [], "champion_history": []}


def save_lineage(d: dict[str, Any]) -> None:
    d["updated"] = now_iso()
    write_json(PATHS.lineage, d)


def next_iteration_number() -> int:
    d = load_lineage()
    return (max([it["iteration"] for it in d["iterations"]] + [0])) + 1


def record_iteration(entry: dict[str, Any]) -> None:
    d = load_lineage()
    d["iterations"] = [it for it in d["iterations"] if it.get("iteration") != entry["iteration"]] + [entry]
    save_lineage(d)


def champion_record() -> dict[str, Any]:
    return read_json(PATHS.evolved / "champion.json", {}) or {
        "source": "original", "iteration": 0, "score_vs_baseline": 0.0, "aggregate_path": None, "updated": None}


def promote_champion(candidate_rsz: Path, iteration: int, candidate_results_dir: Path, score_vs_baseline: float, hypothesis: str) -> None:
    """Copy the candidate rsz tree over the champion and record where its evaluation lives."""
    champ = PATHS.champion
    champ.parent.mkdir(parents=True, exist_ok=True)
    if champ.exists():
        shutil.rmtree(champ)
    # Candidate trees preserve OpenROAD's relative test symlinks. Keep them as
    # links when promoting so copytree does not follow snapshot-external paths.
    shutil.copytree(candidate_rsz, champ, symlinks=True)
    rec = {"source": str(candidate_rsz), "iteration": iteration, "score_vs_baseline": score_vs_baseline,
           "aggregate_path": str(candidate_results_dir / "aggregate.json"), "results_dir": str(candidate_results_dir),
           "hypothesis": hypothesis[:500], "updated": now_iso()}
    write_json(PATHS.evolved / "champion.json", rec)
    d = load_lineage()
    d["champion_history"].append({"iteration": iteration, "score_vs_baseline": score_vs_baseline, "when": now_iso()})
    save_lineage(d)
    # refresh the champion patch
    import subprocess
    diff = subprocess.run(["diff", "-ruN", str(PATHS.rsz_snapshot), str(champ)], capture_output=True, text=True).stdout
    write_text(PATHS.evolved / "champion.patch", diff)
