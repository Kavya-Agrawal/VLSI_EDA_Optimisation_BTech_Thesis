"""rszevolve — agentic evolution of OpenROAD's Resizer (src/rsz).

Layout:
  config.py        paths + knobs (repo layout is fixed; knobs come from config/default.json + CLI)
  util.py          subprocess with timeout/log capture, json helpers, timestamps
  budget.py        token / USD accounting across claude -p calls
  agents/          claude_runner (headless Claude Code), planner, coder, evaluator_agent, prompts/
  eval/            build (Bazel overlay), gates, run_eval (Tcl), paths (attribution), score, baseline, checkpoints
  context/         graphify driver + agent-context generator (Phase 1)
  knowledge/       hypothesis ledger, rulebase, lineage
  orchestrator.py  the iteration loop
  report/          summary tables + visualisations
"""
__version__ = "0.1.0"
