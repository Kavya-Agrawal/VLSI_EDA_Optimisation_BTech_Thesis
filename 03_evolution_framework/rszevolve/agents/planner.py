"""Planning agent: picks a cluster and writes the hypothesis for this iteration."""
from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
from typing import Any

from ..config import PATHS, Knobs
from ..knowledge.ledger import champion_record, read_knowledge
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
    plan_markdown: str

    def as_dict(self) -> dict[str, Any]:
        return {k: v for k, v in vars(self).items() if k != "plan_markdown"}


def _clusters() -> dict[str, Any]:
    return (read_json(PATHS.context / "clusters.json", {}) or {}).get("clusters", {})


def plan(iteration: int, knobs: Knobs, *, feedback: str, tier: str, designs: list[str], budget_summary: str,
         log_dir: Path, forced_cluster: str | None = None) -> tuple[Hypothesis, dict[str, Any]]:
    clusters = {k: v for k, v in _clusters().items() if not k.startswith("_")}
    know = read_knowledge()
    ledger_tail = "\n".join(know.get("hypotheses_ledger", "").splitlines()[-25:])
    champ = champion_record()
    champ_summary = (f"original rsz (no accepted change yet)" if champ.get("iteration", 0) == 0 else
                     f"iteration {champ['iteration']} (score vs baseline {champ.get('score_vs_baseline', 0):+.4f}): {champ.get('hypothesis', '')[:200]}")
    prompt = (PATHS.prompts / "planner.md").read_text()
    for k, v in {"ITERATION": str(iteration), "CHAMPION_SUMMARY": champ_summary, "TIER": tier, "DESIGNS": ", ".join(designs),
                 "BUDGET": budget_summary, "CLUSTERS": ", ".join(f"`{c}` ({v['question'][:60]}...)" for c, v in clusters.items()),
                 "FEEDBACK": feedback or "(first iteration: no candidate feedback yet; use 05_baseline_results/SUMMARY.md)",
                 "KNOWLEDGE": "\n\n".join(f"--- {k}.md ---\n{v[:6000]}" for k, v in know.items() if k in ("rulebase", "lessons", "dead_ends")),
                 "LEDGER": ledger_tail}.items():
        prompt = prompt.replace("{{" + k + "}}", v)
    if forced_cluster:
        prompt += f"\n\nThe operator requires cluster `{forced_cluster}` for this iteration.\n"
    call = AgentCall(role="planner", prompt=prompt, cwd=PATHS.context, model=knobs.planner_model, max_turns=knobs.planner_max_turns,
                     allowed_tools=list(READ_TOOLS), add_dirs=[PATHS.knowledge, PATHS.baseline, PATHS.results, PATHS.original])
    res = run_agent(call, log_dir=log_dir, tag="planner")
    js = extract_json_block(res.text) or {}
    cluster = forced_cluster or str(js.get("cluster", "")).strip()
    if cluster not in clusters:
        # fall back to the evaluator's recommendation or the first cluster so the loop keeps going
        cluster = next(iter(clusters)) if clusters else "setup_strategy"
    h = Hypothesis(cluster=cluster, title=str(js.get("title", ""))[:200], hypothesis=str(js.get("hypothesis", res.text[:1500])),
                   files=[str(f) for f in js.get("files", [])], success_criteria=str(js.get("success_criteria", "")),
                   risk=str(js.get("risk", "")), rule_updates=str(js.get("rule_updates", "")), plan_markdown=res.text)
    write_text(log_dir / "hypothesis.md", f"# Iteration {iteration} — {h.title}\n\ncluster: `{h.cluster}`\n\n{res.text}\n")
    return h, res.raw
