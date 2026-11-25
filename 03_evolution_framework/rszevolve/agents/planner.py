"""Planning agent: picks a cluster and writes the hypothesis for this iteration."""
from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
from typing import Any

from ..config import PATHS, Knobs
from ..knowledge.ledger import champion_record, planner_experience_context, read_knowledge
from ..util import read_json, write_text
from .claude_runner import READ_TOOLS, AgentCall, extract_json_block, run_agent


@dataclass
class Hypothesis:
    cluster: str
    title: str
    hypothesis: str
    files: list[str]
    success_criteria: str
    risk: str
    rule_updates: str
    evidence_iterations: list[int]
    plan_markdown: str

    def as_dict(self) -> dict[str, Any]:
        return {k: v for k, v in vars(self).items() if k != "plan_markdown"}


def _clusters() -> dict[str, Any]:
    return (read_json(PATHS.context / "clusters.json", {}) or {}).get("clusters", {})


def _code_map(clusters: dict[str, Any]) -> str:
    sections: list[str] = []
    for name, spec in clusters.items():
        editable = [str(path) for path in spec.get("editable", [])]
        readonly = [str(path) for path in spec.get("readonly_context", [])]
        sections.append(f"## {name}\nDecision: {spec.get('question', '')}\n"
                        f"Editable implementation surface ({len(editable)} files): {', '.join(editable)}\n"
                        f"Key read-only dependencies: {', '.join(readonly[:30]) or '(none mapped)'}\n"
                        f"Mapped regression tests: {len(spec.get('tests', []))}")
    return "\n\n".join(sections)


def _repair_stats(knobs: Knobs, designs: list[str]) -> str:
    """Stock move counts + WNS/TNS per design, so the planner sizes its idea against what repair actually does."""
    from ..eval.baseline import load_baseline
    base = load_baseline().get("variants", {}).get(knobs.sdc_variant, {})
    lines = []
    for d in designs:
        a = base.get(d) or {}
        if not a.get("ok"):
            continue
        st = a.get("repair_stats") or {}
        lines.append(f"- {d}: period {a['period_ns']:.4g} ns, endpoints {a['endpoints']}, WNS {a['pre']['wns_setup']:+.4f} -> "
                     f"{a['post']['wns_setup']['mean']:+.4f}, TNS {a['pre']['tns_setup']:+.2f} -> {a['post']['tns_setup']['mean']:+.2f}, "
                     f"stock moves {st or '(re-run make baseline to record)'}")
    return "\n".join(lines) or "(no baseline)"


def hypothesis_from_text(text: str, *, forced_cluster: str | None = None) -> Hypothesis:
    """Reconstruct a plan from its durable agent output (used after terminal/IDE crashes)."""
    clusters = {k: v for k, v in _clusters().items() if not k.startswith("_")}
    js = extract_json_block(text) or {}
    cluster = forced_cluster or str(js.get("cluster", "")).strip()
    if cluster not in clusters:
        cluster = next(iter(clusters)) if clusters else "setup_strategy"
    evidence_iterations: list[int] = []
    for value in js.get("evidence_iterations", []):
        try:
            evidence_iterations.append(int(value))
        except (TypeError, ValueError):
            continue
    return Hypothesis(cluster=cluster, title=str(js.get("title", ""))[:200],
                      hypothesis=str(js.get("hypothesis", text[:1500])),
                      files=[str(f) for f in js.get("files", [])],
                      success_criteria=str(js.get("success_criteria", "")), risk=str(js.get("risk", "")),
                      rule_updates=str(js.get("rule_updates", "")),
                      evidence_iterations=sorted(set(evidence_iterations)), plan_markdown=text)


def plan(iteration: int, knobs: Knobs, *, feedback: str, tier: str, designs: list[str], budget_summary: str,
         log_dir: Path, forced_cluster: str | None = None) -> tuple[Hypothesis, dict[str, Any]]:
    clusters = {k: v for k, v in _clusters().items() if not k.startswith("_")}
    know = read_knowledge()
    ledger_tail = "\n".join(know.get("hypotheses_ledger", "").splitlines()[-25:])
    experience = planner_experience_context(recent=8)
    champ = champion_record()
    champ_summary = (f"original rsz (no accepted change yet)" if champ.get("iteration", 0) == 0 else
                     f"iteration {champ['iteration']} (score vs baseline {champ.get('score_vs_baseline', 0):+.4f}): {champ.get('hypothesis', '')[:200]}")
    prompt = (PATHS.prompts / "planner.md").read_text()
    for k, v in {"ITERATION": str(iteration), "CHAMPION_SUMMARY": champ_summary, "TIER": tier, "DESIGNS": ", ".join(designs),
                 "BUDGET": budget_summary, "CLUSTERS": ", ".join(f"`{c}` ({v['question'][:60]}...)" for c, v in clusters.items()),
                 "FEEDBACK": feedback or "(first iteration: no candidate feedback yet; use 05_baseline_results/SUMMARY.md)",
                 "KNOWLEDGE": "\n\n".join(f"--- {k}.md ---\n{v[:6000]}" for k, v in know.items() if k in ("rulebase", "lessons", "dead_ends")),
                 "LEDGER": ledger_tail, "EXPERIENCE": experience, "CODE_MAP": _code_map(clusters),
                 "REPAIR_STATS": _repair_stats(knobs, designs)}.items():
        prompt = prompt.replace("{{" + k + "}}", v)
    if forced_cluster:
        prompt += f"\n\nThe operator requires cluster `{forced_cluster}` for this iteration.\n"
    call = AgentCall(role="planner", prompt=prompt, cwd=PATHS.context, model=knobs.planner_model, max_turns=knobs.planner_max_turns,
                     allowed_tools=list(READ_TOOLS), add_dirs=[PATHS.knowledge, PATHS.baseline, PATHS.results, PATHS.original])
    res = run_agent(call, log_dir=log_dir, tag="planner")
    h = hypothesis_from_text(res.text, forced_cluster=forced_cluster)
    write_text(log_dir / "hypothesis.md", f"# Iteration {iteration} — {h.title}\n\ncluster: `{h.cluster}`\n\n{res.text}\n")
    return h, res.raw
