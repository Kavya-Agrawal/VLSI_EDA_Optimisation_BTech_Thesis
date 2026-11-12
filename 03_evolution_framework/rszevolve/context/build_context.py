"""Phase 1b: generate 09_agent_context/ from the rsz sources + graphify graph using headless Claude.

Outputs:
  00_BIG_PICTURE.md            what rsz solves, where it sits in the flow, rsz<->STA loop, inputs/outputs
  files/<File>.md              one card per rsz source file (purpose, entry points, I/O, callers/callees, invariants)
  algorithms/<cluster>.md      one dossier per cluster (problem, current heuristic step by step, weaknesses, literature, files)
  clusters.json                cluster -> files (editable) / read-only context / entry points / tests
  GLOSSARY.md, EVAL_CONTRACT.md
Files containing '<!-- hand-edited -->' are never overwritten."""
from __future__ import annotations

import fnmatch
import json
import re
from pathlib import Path
from typing import Any

from ..agents.claude_runner import READ_TOOLS, AgentCall, run_agent
from ..config import PATHS, Knobs
from ..util import log, now_iso, read_json, write_json, write_text

# Seed cluster membership by file-name patterns (confirmed/adjusted with the graph at generation time).
CLUSTER_PATTERNS: dict[str, dict[str, Any]] = {
    "setup_strategy": {
        "editable": ["RepairSetup*", "RepairTargetCollector*", "PathGroupFilter*", "Optimizer*", "OptimizationPolicy*",
                     "policy/*", "MoveTracker*", "MoveCommitter*", "RepairSetupContext*", "move/MoveGenerator*", "move/MoveCandidate*"],
        "question": "which endpoints/paths to attack, in what order, how many moves per pass, acceptance criteria, TNS vs WNS budgeting, stopping rules, move-sequence policy"},
    "sizing": {
        "editable": ["move/SizeUp*", "move/SizeDownFanout*", "move/VtSwap*", "move/SwapPins*", "SwapPinsEquivalence*", "DelayEstimator*", "LRSubproblem*"],
        "question": "how a cell size / VT / pin assignment is chosen for a driver (greedy slack-driven today) and how the resulting delay is estimated"},
    "buffering": {
        "editable": ["Rebuffer*", "BufferedNet*", "move/Buffer*", "move/Rebuffer*", "move/SplitLoad*", "move/Clone*", "move/Unbuffer*", "move/BufferToInverters*", "move/Reroute*"],
        "question": "how buffer trees are built/selected for a net (van Ginneken style today), when to clone or split a load, where to insert, when to remove"},
    "hold": {"editable": ["RepairHold*"], "question": "how hold violations are fixed with minimal setup damage"},
    "drv": {"editable": ["RepairDesign*", "PreChecks*"], "question": "how slew / capacitance / fanout / long-wire violations are repaired before timing repair"},
    "timing_model": {"editable": ["SequentialTimingEstimator*", "SkewBudget*", "DelayEstimatorBufferTree*", "DelayEstimatorInternal*"],
                     "question": "the estimates used to rank moves and budget skew/sequential timing"},
}
ALWAYS_READONLY = ["Resizer.cc", "Resizer.hh", "Resizer.tcl", "Resizer.i", "MakeResizer.cc", "ResizerObserver.hh", "OdbCallBack.cc",
                   "Graphics.*", "ConcreteSwapArithModules*", "SwapArithModules*", "RecoverPower*", "RepairSetupProfiler*", "RepairSetupAnalysis*",
                   "RepairSetupMove*", "Resizer-py.i"]


def rsz_source_files() -> list[Path]:
    src = PATHS.rsz_snapshot / "src"
    return sorted(p for p in src.rglob("*") if p.is_file() and p.suffix in (".cc", ".hh", ".h", ".tcl", ".i") and "test" not in p.parts)


def rel(p: Path) -> str:
    return str(p.relative_to(PATHS.rsz_snapshot / "src"))


def load_graph() -> dict[str, Any]:
    for cand in (PATHS.graphify / "rsz_focus" / "graphify-out" / "graph.json", PATHS.graphify / "full_openroad" / "graphify-out" / "graph.json"):
        if cand.exists():
            return read_json(cand, {}) or {}
    return {}


def graph_neighbors(graph: dict[str, Any]) -> dict[str, dict[str, set[str]]]:
    """file -> {'calls': {files}, 'called_by': {files}} using graph.json nodes/edges (graphify schema: nodes have
    'id','label','source_file' (or 'file'); edges have 'source','target','relation')."""
    nodes = {n.get("id"): n for n in graph.get("nodes", [])}
    edges = graph.get("edges", graph.get("links", []))
    node_file: dict[str, str] = {}
    for n in graph.get("nodes", []):
        f = n.get("source_file") or n.get("file") or n.get("path")
        if f:
            node_file[n["id"]] = f
    for e in edges:  # graphify puts the file on the edge for the source symbol
        if e.get("source_file") and e.get("source") not in node_file:
            node_file[e["source"]] = e["source_file"]
    def file_of(nid: str) -> str | None:
        f = node_file.get(nid)
        return Path(f).name if f else None
    out: dict[str, dict[str, set[str]]] = {}
    for e in edges:
        a, b = file_of(e.get("source")), file_of(e.get("target"))
        if not a or not b or a == b:
            continue
        out.setdefault(a, {"calls": set(), "called_by": set()})["calls"].add(b)
        out.setdefault(b, {"calls": set(), "called_by": set()})["called_by"].add(a)
    return out


def assign_clusters(files: list[Path]) -> dict[str, Any]:
    rels = [rel(f) for f in files]
    clusters: dict[str, Any] = {}
    taken: set[str] = set()
    for name, spec in CLUSTER_PATTERNS.items():
        editable = sorted({r for r in rels for pat in spec["editable"] if fnmatch.fnmatch(r, pat) or fnmatch.fnmatch(Path(r).name, pat)})
        taken.update(editable)
        clusters[name] = {"question": spec["question"], "editable": editable}
    unassigned = sorted(r for r in rels if r not in taken and not any(fnmatch.fnmatch(Path(r).name, p) for p in ALWAYS_READONLY))
    clusters["_unassigned"] = unassigned
    clusters["_always_readonly"] = sorted(r for r in rels if any(fnmatch.fnmatch(Path(r).name, p) for p in ALWAYS_READONLY))
    return clusters


def is_hand_edited(p: Path) -> bool:
    return p.exists() and "<!-- hand-edited -->" in p.read_text()


def _agent(prompt: str, role: str, knobs: Knobs, tag: str, *, max_turns: int = 40, add_dirs: list[Path] | None = None) -> str:
    call = AgentCall(role=role, prompt=prompt, cwd=PATHS.rsz_snapshot, model=knobs.context_model, max_turns=max_turns,
                     allowed_tools=list(READ_TOOLS), add_dirs=[PATHS.original, PATHS.graphify, PATHS.context] + (add_dirs or []))
    res = run_agent(call, log_dir=PATHS.agent_data / "context", tag=tag)
    return res.text


def build_context(knobs: Knobs, only: list[str] | None = None) -> int:
    want = set(only or ["clusters", "big_picture", "files", "algorithms", "glossary", "eval_contract"])
    files = rsz_source_files()
    graph = load_graph()
    nb = graph_neighbors(graph) if graph else {}
    PATHS.context.mkdir(parents=True, exist_ok=True)
    (PATHS.context / "files").mkdir(exist_ok=True)
    (PATHS.context / "algorithms").mkdir(exist_ok=True)

    clusters = assign_clusters(files)
    if "clusters" in want:
        for name, c in clusters.items():
            if name.startswith("_"):
                continue
            ro: set[str] = set()
            for f in c["editable"]:
                for callee in nb.get(Path(f).name, {}).get("calls", set()):
                    ro.add(callee)
            c["readonly_context"] = sorted(x for x in ro if x not in {Path(e).name for e in c["editable"]})
            c["tests"] = sorted(str(p.name) for p in (PATHS.rsz_snapshot / "test").glob("*.tcl") if any(k in p.name for k in {
                "setup_strategy": ["repair_setup"], "sizing": ["repair_setup", "size", "vt_swap", "swap_pins"], "buffering": ["rebuffer", "buffer", "clone", "split"],
                "hold": ["repair_hold"], "drv": ["repair_design", "repair_slew", "repair_cap", "repair_fanout", "repair_wire"], "timing_model": ["repair_setup"]}[name]))
        write_json(PATHS.context / "clusters.json", {"generated": now_iso(), "graph_used": bool(graph), "clusters": clusters})
        log(f"clusters.json: " + ", ".join(f"{k}={len(v['editable'])}" for k, v in clusters.items() if not k.startswith('_')) + f", unassigned={len(clusters['_unassigned'])}")

    if "eval_contract" in want and not is_hand_edited(PATHS.context / "EVAL_CONTRACT.md"):
        write_text(PATHS.context / "EVAL_CONTRACT.md", (PATHS.context_prompts / "eval_contract.md").read_text().replace("{{REPAIR_ARGS}}", knobs.repair_timing_args))

    file_index = "\n".join(f"- {rel(f)} ({f.stat().st_size//1000} KB)" + (f"  calls: {', '.join(sorted(nb[f.name]['calls'])[:8])}" if f.name in nb else "") for f in files)
    god = (PATHS.graphify / "rsz_focus" / "GOD_NODES.txt")
    god_txt = god.read_text()[:4000] if god.exists() else "(graphify not run yet)"

    if "big_picture" in want and not is_hand_edited(PATHS.context / "00_BIG_PICTURE.md"):
        prompt = (PATHS.context_prompts / "big_picture.md").read_text().replace("{{FILE_INDEX}}", file_index).replace("{{GOD_NODES}}", god_txt)
        txt = _agent(prompt, "context:big_picture", knobs, "big_picture", max_turns=60, add_dirs=[PATHS.orfs_src / "flow" / "scripts"])
        write_text(PATHS.context / "00_BIG_PICTURE.md", txt)

    if "files" in want:
        for f in files:
            out = PATHS.context / "files" / (rel(f).replace("/", "__") + ".md")
            if is_hand_edited(out) or (out.exists() and out.stat().st_mtime > f.stat().st_mtime and "--force" not in (only or [])):
                continue
            neigh = nb.get(f.name, {})
            prompt = (PATHS.context_prompts / "file_card.md").read_text().replace("{{FILE}}", rel(f)) \
                .replace("{{CALLS}}", ", ".join(sorted(neigh.get("calls", []))) or "(unknown)") \
                .replace("{{CALLED_BY}}", ", ".join(sorted(neigh.get("called_by", []))) or "(unknown)")
            txt = _agent(prompt, f"context:file:{f.name}", knobs, f"file_{rel(f).replace('/', '__')}", max_turns=25)
            if txt.strip():
                write_text(out, txt)
        log(f"file cards: {len(list((PATHS.context/'files').glob('*.md')))} / {len(files)}")

    if "algorithms" in want:
        for name, c in clusters.items():
            if name.startswith("_"):
                continue
            out = PATHS.context / "algorithms" / f"{name}.md"
            if is_hand_edited(out):
                continue
            cards = "\n\n".join((PATHS.context / "files" / (e.replace("/", "__") + ".md")).read_text()[:6000]
                                for e in c["editable"] if (PATHS.context / "files" / (e.replace("/", "__") + ".md")).exists())
            prompt = (PATHS.context_prompts / "algorithm_dossier.md").read_text().replace("{{CLUSTER}}", name).replace("{{QUESTION}}", c["question"]) \
                .replace("{{EDITABLE}}", "\n".join(f"- {e}" for e in c["editable"])).replace("{{READONLY}}", ", ".join(c.get("readonly_context", []))) \
                .replace("{{TESTS}}", ", ".join(c.get("tests", []))).replace("{{CARDS}}", cards)
            txt = _agent(prompt, f"context:algorithm:{name}", knobs, f"algorithm_{name}", max_turns=60)
            write_text(out, txt)

    if "glossary" in want and not is_hand_edited(PATHS.context / "GLOSSARY.md"):
        txt = _agent((PATHS.context_prompts / "glossary.md").read_text(), "context:glossary", knobs, "glossary", max_turns=20)
        write_text(PATHS.context / "GLOSSARY.md", txt)

    missing = [rel(f) for f in files if not (PATHS.context / "files" / (rel(f).replace("/", "__") + ".md")).exists()]
    write_json(PATHS.context / "COVERAGE.json", {"files_total": len(files), "cards_missing": missing, "generated": now_iso()})
    log(f"context done; missing cards: {len(missing)}")
    return 0 if not missing or "files" not in want else 1
