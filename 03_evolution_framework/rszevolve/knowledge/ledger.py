"""Lineage (which candidate came from which champion, verdicts, scores) and the agents' knowledge files.

02_openroad_evolved/lineage.json   machine-readable history of every iteration
02_openroad_evolved/champion.json  what the current champion is and where its evaluation lives
10_agent_knowledge/rulebase.md     self-evolving rules the planner maintains
10_agent_knowledge/lessons.md      free-form lessons appended by the planner
10_agent_knowledge/hypotheses_ledger.md   one line per hypothesis with its outcome
10_agent_knowledge/dead_ends.md    ideas that failed and why (so they are not retried blindly)
10_agent_knowledge/iterations/     one structured, durable record per completed iteration
10_agent_knowledge/EXPERIENCE.md   regenerated agent-friendly index over all iteration records"""
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
EXPERIENCE_SEED = """# Experiment experience index

This is a derived, agent-friendly index. The durable source records are `iterations/<NNNN>.json`; raw evidence
remains in `02_openroad_evolved`, `06_evolved_results`, and `11_agent_data`. Regenerating this file never deletes
an iteration record.
"""


def ensure_knowledge_files() -> None:
    PATHS.knowledge.mkdir(parents=True, exist_ok=True)
    (PATHS.knowledge / "iterations").mkdir(exist_ok=True)
    for name, seed in (("rulebase.md", RULEBASE_SEED), ("lessons.md", LESSONS_SEED),
                       ("hypotheses_ledger.md", LEDGER_SEED), ("dead_ends.md", DEAD_ENDS_SEED),
                       ("EXPERIENCE.md", EXPERIENCE_SEED)):
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


def patch_stats(patch: str) -> dict[str, Any]:
    """Compact source-change description suitable for lineage and planner memory."""
    files: list[str] = []
    added = deleted = 0
    for line in patch.splitlines():
        if line.startswith("diff --git "):
            parts = line.split()
            if len(parts) >= 4:
                name = parts[3]
                if name.startswith("b/"):
                    name = name[2:]
                files.append(name)
        elif line.startswith("+") and not line.startswith("+++"):
            added += 1
        elif line.startswith("-") and not line.startswith("---"):
            deleted += 1
    return {"files": sorted(set(files)), "files_count": len(set(files)), "lines_added": added, "lines_deleted": deleted}


def _valid_experiment(record: dict[str, Any]) -> bool:
    return record.get("status") in ("accepted", "rejected") and bool(record.get("files_changed") or record.get("patch_stats", {}).get("files"))


def _design_line(name: str, values: dict[str, Any]) -> str:
    def num(key: str) -> float:
        return float(values.get(key) or 0)
    return (f"{name}: score {num('score'):+.5f}; "
            f"WNS {num('wns_ref'):+.4f}->{num('wns_cand'):+.4f} ns (d {num('d_wns_ns'):+.4f}); "
            f"TNS {num('tns_ref'):+.3f}->{num('tns_cand'):+.3f} ns (d {num('d_tns_ns'):+.3f})")


def _experience_card(record: dict[str, Any], *, detailed: bool = True) -> str:
    iteration = int(record.get("iteration", 0))
    score = float(record.get("score_vs_champion") or 0)
    valid = _valid_experiment(record)
    lines = [f"## Iteration {iteration}: {record.get('status', 'unknown')} · {record.get('cluster', 'unassigned')}",
             f"- **Evidence status:** {'valid algorithm experiment' if valid else 'infrastructure/no-code record; do not infer heuristic quality'}",
             f"- **Hypothesis:** {str(record.get('title') or record.get('hypothesis') or record.get('error') or '')[:600]}",
             f"- **Score:** vs champion {score:+.5f}; vs baseline {float(record.get('score_vs_baseline') or 0):+.5f}",
             f"- **Files planned:** {', '.join(record.get('planned_files') or []) or '(not recorded)'}",
             f"- **Files changed:** {', '.join(record.get('files_changed') or record.get('patch_stats', {}).get('files', [])) or '(none)'}"]
    stats = record.get("patch_stats") or {}
    if stats:
        lines.append(f"- **Patch scope:** {stats.get('files_count', 0)} files, +{stats.get('lines_added', 0)}/-{stats.get('lines_deleted', 0)} lines")
    if record.get("reasons"):
        lines.append(f"- **Verdict reasons:** {'; '.join(str(x) for x in record['reasons'])}")
    if detailed:
        for name, values in (record.get("per_design") or {}).items():
            lines.append(f"- **{_design_line(name, values)}**")
        evaluator = record.get("evaluator") or {}
        for key, label in (("dominant_cause", "Dominant cause"), ("lesson", "Lesson"), ("dead_end", "Dead end"),
                           ("recommended_cluster", "Recommended next cluster")):
            if evaluator.get(key):
                lines.append(f"- **{label}:** {evaluator[key]}")
        for key, label in (("good_changes", "Good changes"), ("bad_changes", "Bad changes"),
                           ("files_to_revisit", "Files to revisit"), ("files_to_avoid", "Files to avoid")):
            if evaluator.get(key):
                value = evaluator[key]
                lines.append(f"- **{label}:** {', '.join(map(str, value)) if isinstance(value, list) else value}")
    return "\n".join(lines)


def load_experience() -> list[dict[str, Any]]:
    ensure_knowledge_files()
    records = [read_json(path, {}) or {} for path in sorted((PATHS.knowledge / "iterations").glob("*.json"))]
    return sorted((record for record in records if record.get("iteration") is not None), key=lambda record: int(record["iteration"]))


def render_experience_index() -> None:
    records = load_experience()
    body = [EXPERIENCE_SEED.rstrip(), "", f"Recorded iterations: **{len(records)}** · valid algorithm experiments: **{sum(_valid_experiment(r) for r in records)}**", ""]
    body.extend(_experience_card(record) + "\n" for record in records)
    write_text(PATHS.knowledge / "EXPERIENCE.md", "\n".join(body).rstrip() + "\n")


def record_experience(entry: dict[str, Any]) -> None:
    """Upsert one iteration's durable record without modifying any other iteration."""
    ensure_knowledge_files()
    record = dict(entry)
    record["schema_version"] = 1
    record["valid_experiment"] = _valid_experiment(record)
    write_json(PATHS.knowledge / "iterations" / f"{int(record['iteration']):04d}.json", record)
    render_experience_index()


def backfill_experience() -> None:
    """Add missing durable records from lineage; existing richer records always win."""
    ensure_knowledge_files()
    changed = False
    for entry in load_lineage().get("iterations", []):
        path = PATHS.knowledge / "iterations" / f"{int(entry['iteration']):04d}.json"
        if not path.exists():
            record = dict(entry)
            record["schema_version"] = 1
            record["valid_experiment"] = _valid_experiment(record)
            write_json(path, record)
            changed = True
    if changed or not (PATHS.knowledge / "EXPERIENCE.md").exists():
        render_experience_index()


def planner_experience_context(*, recent: int = 8) -> str:
    """Compact all-history portfolio plus detailed recent evidence for the planning prompt."""
    backfill_experience()
    records = load_experience()
    if not records:
        return "No completed iterations yet."
    valid = [record for record in records if _valid_experiment(record)]
    accepted = [record for record in valid if record.get("status") == "accepted"]
    out = ["# Durable cross-iteration memory",
           f"All {len(records)} records remain on disk. {len(valid)} are valid code experiments; {len(accepted)} were accepted. "
           "Records marked infrastructure/no-code are not evidence about heuristic quality.", "", "## Cluster portfolio"]
    clusters = sorted({str(record.get("cluster")) for record in records if record.get("cluster")})
    for cluster in clusters:
        subset = [record for record in valid if record.get("cluster") == cluster]
        wins = sum(record.get("status") == "accepted" for record in subset)
        best = max((float(record.get("score_vs_champion") or 0) for record in subset), default=0)
        out.append(f"- {cluster}: {len(subset)} valid experiments, {wins} accepted, best score {best:+.5f}")
    out.extend(["", "## Complete compact history"])
    for record in records:
        flag = "valid" if _valid_experiment(record) else "infra/no-code"
        out.append(f"- #{record.get('iteration')} [{flag}] {record.get('status')} {record.get('cluster', '')}: "
                   f"score {float(record.get('score_vs_champion') or 0):+.5f}; files "
                   f"{', '.join(record.get('files_changed') or []) or 'none'}; "
                   f"{str(record.get('title') or record.get('error') or record.get('hypothesis') or '')[:180]}")
    file_outcomes: dict[str, dict[str, float]] = {}
    for record in valid:
        for filename in record.get("files_changed") or []:
            outcome = file_outcomes.setdefault(str(filename), {"tries": 0, "wins": 0, "best": -1e9})
            outcome["tries"] += 1
            outcome["wins"] += int(record.get("status") == "accepted")
            outcome["best"] = max(outcome["best"], float(record.get("score_vs_champion") or 0))
    if file_outcomes:
        out.extend(["", "## File outcome history"])
        for filename, outcome in sorted(file_outcomes.items(), key=lambda item: (item[1]["wins"], item[1]["best"]), reverse=True)[:30]:
            out.append(f"- {filename}: {int(outcome['tries'])} tries, {int(outcome['wins'])} accepted, best {outcome['best']:+.5f}")
    out.extend(["", f"## Detailed most recent {min(recent, len(records))} records"])
    out.extend(_experience_card(record) + "\n" for record in records[-recent:])
    return "\n".join(out)


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
