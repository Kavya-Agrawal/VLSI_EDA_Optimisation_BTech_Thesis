# pv_resizer_evolve — agentic evolution of OpenROAD's Resizer (`rsz`)

Branch `pv_resizer_evolve` is a clean-slate project with one goal: let a team of LLM agents
(planner → cluster-scoped coding sub-agents → evaluator) **re-think the algorithms and heuristics
inside OpenROAD's timing repair / resizer** and keep only changes that measurably improve
WNS / TNS on placed designs, judged with OpenROAD's own pre-route timing commands.

Not the goal: micro-optimisations, data-structure tweaks, runtime wins. The agents are asked for a
different heuristic, a different approximation paradigm, a different way of looking at the problem.

## Repository map (numbered = reading order)

| Folder | What is in it |
|---|---|
| [00_docs/](00_docs/) | approved plan, architecture, how to reproduce, decisions log |
| [01_openroad_original/](01_openroad_original/) | frozen, read-only copy of stock `src/rsz` (+ STA headers) at the pinned commit |
| [02_openroad_evolved/](02_openroad_evolved/) | champion rsz tree, every candidate, patches, `lineage.json` |
| [03_evolution_framework/](03_evolution_framework/) | the `rszevolve` Python package: agents, evaluator, orchestrator, Tcl |
| [04_benchmarks/](04_benchmarks/) | placed checkpoints + SDCs per design, `tiers.json` |
| [05_baseline_results/](05_baseline_results/) | stock OpenROAD WNS/TNS/paths per design (3 replicates) |
| [06_evolved_results/](06_evolved_results/) | per-iteration metrics, path reports, deltas, evaluator feedback |
| [07_visualizations/](07_visualizations/) | generated dashboard and plots |
| [08_graphify/](08_graphify/) | Graphify knowledge graphs (whole OpenROAD + rsz-focused) |
| [09_agent_context/](09_agent_context/) | curated context the agents read: big picture, per-file cards, algorithm dossiers |
| [10_agent_knowledge/](10_agent_knowledge/) | what the agents learned: rulebase, lessons, hypothesis ledger, dead ends |
| [11_agent_data/](11_agent_data/) | raw prompts / responses / token usage per iteration |
| [tools/](tools/) | env check, dependency installers, Bazel build wrapper, Dockerfile |
| `external/` | OpenROAD and OpenROAD-flow-scripts, pinned in `VERSIONS.lock` |

## Quick start

```bash
make help                       # every target with a one-line description
make deps                       # brew / apt packages (once)
make setup                      # clone OpenROAD + ORFS at pinned commits, python venv
make env-check                  # PASS/WARN/FAIL table
make build-openroad snapshot    # Bazel build of stock OpenROAD (1-2 h first time), freeze src/rsz
make graphify context           # Phase 1: knowledge graph + agent context packs
make checkpoints baseline       # placed checkpoints via ORFS, stock WNS/TNS numbers
make evolve N=5 BUDGET_USD=20   # Phase 2: five plan→code→build→evaluate iterations
make report viz show-champion   # tables, dashboard, champion diff
```

Knobs: `N` iterations, `BUDGET_USD` / `MAX_TOKENS` spend caps, `TIER=A|B|C` benchmark set,
`BAZEL_JOBS` for small-RAM machines, `CLAUDE_BIN`, `PYTHON`. See [00_docs/how_to_reproduce.md](00_docs/how_to_reproduce.md).

## How an iteration works

1. **Planner** reads the last evaluator feedback, the knowledge base and the hypothesis ledger, picks one
   algorithm cluster (setup strategy, sizing, buffering, hold, DRV, timing model) and writes a hypothesis.
2. **Coding sub-agent** for that cluster edits a copy of the champion `rsz` tree with only its cluster's
   context in view, and writes `HYPOTHESIS.md` (problem → current heuristic → new approach → why → risks).
3. **Build + gates**: Bazel incremental build, rsz regression tests, placement legality, DRV / hold guards.
4. **Evaluate**: on each benchmark checkpoint run `estimate_parasitics -placement` → `repair_timing` →
   `report_wns / report_tns / report_checks`. No routing, no GDS. Seconds to minutes per design.
5. **Evaluator agent** turns metrics and the worst paths into `feedback.md` with attributed causes.
6. **Record**: accept into champion or reject, update `lineage.json`, knowledge base, cost ledger.

Everything is logged under `06_evolved_results/<iter>/` and `11_agent_data/<iter>/`.

## Status

See `make status`. Pinned OpenROAD / ORFS commits and tool versions: [VERSIONS.lock](VERSIONS.lock).
