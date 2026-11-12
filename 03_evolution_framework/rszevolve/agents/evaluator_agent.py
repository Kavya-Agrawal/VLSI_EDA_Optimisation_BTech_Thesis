"""Evaluating agent: turns the computed verdict + path attribution into feedback.md for the planner."""
from __future__ import annotations

import json
from pathlib import Path
from typing import Any

from ..config import PATHS, Knobs
from ..eval.candidate import CandidateEval
from ..eval.paths import render_markdown
from ..eval.score import summarize
from ..util import write_text
from .claude_runner import READ_TOOLS, AgentCall, extract_json_block, run_agent


def feedback(iteration: int, tag: str, cluster: str, hypothesis: str, ce: CandidateEval, knobs: Knobs, *, log_dir: Path) -> tuple[str, dict[str, Any]]:
    verdict_txt = "vs champion:\n" + summarize(ce.vs_champion) + "\n\nvs baseline:\n" + summarize(ce.vs_baseline)
    paths_md = "\n".join(render_markdown(k, v["attribution"], v.get("diff_vs_baseline")) for k, v in ce.attribution.items()) or "(no path data: build or gates failed)"
    gates_txt = (ce.gates.report() if ce.gates else "gates not run") + "\n" + (ce.build.diagnostics() if ce.build else "")
    prompt = (PATHS.prompts / "evaluator.md").read_text()
    for k, v in {"TAG": tag, "ITERATION": str(iteration), "CLUSTER": cluster, "HYPOTHESIS": hypothesis, "VERDICT": verdict_txt,
                 "PATHS": paths_md[:60000], "GATES": gates_txt[:8000]}.items():
        prompt = prompt.replace("{{" + k + "}}", v)
    call = AgentCall(role="evaluator", prompt=prompt, cwd=ce.out_dir, model=knobs.evaluator_model, max_turns=knobs.evaluator_max_turns,
                     allowed_tools=list(READ_TOOLS), add_dirs=[PATHS.baseline, PATHS.context])
    res = run_agent(call, log_dir=log_dir, tag="evaluator")
    text = res.text.strip() or f"# Feedback (agent unavailable)\n\n```\n{verdict_txt}\n```\n\n{paths_md}\n"
    # always prepend the authoritative numbers so the planner never depends on the agent's prose alone
    md = f"# Feedback for iteration {iteration} ({tag}, cluster {cluster})\n\n```\n{verdict_txt}\n```\n\n{text}\n"
    write_text(ce.out_dir / "feedback.md", md)
    return md, (extract_json_block(res.text) or {})
