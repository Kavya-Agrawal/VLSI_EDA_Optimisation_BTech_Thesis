# HANDOFF — current status and what a helper agent can do

Updated: 2026-11-12 (evening). Branch `pv_resizer_evolve`.

## Done and verified
- Clean-slate branch, numbered layout, README, Makefile (GNU make 3.81 compatible), `VERSIONS.lock`.
- OpenROAD `6932b629` + ORFS `a47d4fdc` cloned (blobless) at `external/`; rsz frozen in `01_openroad_original/rsz_snapshot`; champion = original.
- Stock OpenROAD built with Bazel on macOS arm64 in 22 min: `build/bin/openroad_stock -version` works.
- Homebrew: bazelisk, yosys 0.71, python 3.12, pipx; `graphify` 0.9.105 via pipx.
- Evaluation Tcl (`03_evolution_framework/rszevolve/eval/tcl/eval_repair_timing.tcl` + `path_report.tcl`) smoke-tested on the gcd Nangate45 test design: pre/post WNS, TNS, hold, DRV, area, buffers, worst-path JSON. Runs in under a second.
- Python: config, util, budget, claude_runner (headless `claude -p`, verified JSON shape), run_eval, score, paths, checkpoints (ORFS driver + stressed-SDC calibration), baseline, cli skeleton.

## In progress (Claude builds these; do not duplicate)
- `rszevolve/eval/build.py`, `gates.py`, `candidate.py` (Bazel overlay build + guards + evaluate-vs-champion)
- `rszevolve/context/*` (graphify driver + agent-context generator), `rszevolve/agents/*` (planner, coder, evaluator, prompts), `orchestrator.py`, `knowledge/*`, `report/*`, `tests/`

## Safe tasks for a helper agent (no Python in 03_evolution_framework/)
Run from the repo root. Everything is idempotent.

1. **Install the standalone Claude Code CLI** so `claude` is on PATH (today the framework falls back to the VS Code extension's bundled binary):
   `curl -fsSL https://claude.ai/install.sh | bash` then `claude --version`.
2. **Generate placed checkpoints for Tier A** (ORFS synth→place, no repair_timing). This is pure ORFS and takes a while for ibex:
   `make checkpoints TIER=A` (per design: `cd 03_evolution_framework && python3.12 -m rszevolve checkpoints --only nangate45/aes`).
   Expected output: `04_benchmarks/designs/nangate45/<design>/{placed.odb,nominal.sdc,stressed.sdc,design.json}`.
   If ORFS fails, attach `04_benchmarks/orfs_runs/<pdk>__<design>/make_place.log` tail.
3. **Run the baseline** once checkpoints exist: `make baseline TIER=A` → `05_baseline_results/SUMMARY.md`.
4. **Graphify extraction (offline part)**:
   `graphify extract external/OpenROAD/src --code-only --out 08_graphify/full_openroad --max-workers 8`
   `graphify extract external/OpenROAD/src/rsz --code-only --out 08_graphify/rsz_focus`
   then `graphify god-nodes --graph 08_graphify/rsz_focus/graphify-out/graph.json --top 25 > 08_graphify/rsz_focus/GOD_NODES.txt`.
5. **Verify the rsz C++ unit tests build and pass on this machine** (fills the Bazel cache for the gates):
   `cd external/OpenROAD && bazelisk test --jobs=8 --config=no-werror --test_output=errors //src/rsz/test:cpp_tests //src/rsz/test:TestResizer //src/rsz/test:TestPreChecks //src/rsz/test:TestSkewBudget //src/rsz/test:TestInsertBuffer //src/rsz/test:TestNestedJournal`
   Report which targets exist / pass.
6. **Record versions**: `make lock-versions`, then commit with message `chore: lock tool versions`.
7. Tier B checkpoints when A is done: `make checkpoints TIER=B` (asap7/ibex and nangate45/jpeg are slow; fine to run overnight).

Anything that touches `03_evolution_framework/` or the Makefile should be left to Claude.
