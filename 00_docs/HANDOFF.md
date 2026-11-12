# HANDOFF — current status and what a helper agent can do

Updated: 2026-11-12 (evening). Branch `pv_resizer_evolve`.

## Done and verified (2026-11-13)
- Full loop implemented and self-tested: build overlay (20 s warm), gates (6 Bazel unit targets + 10 smoke Tcl) pass, no-op candidate correctly rejected, `make status/report/viz/test` work.
- gcd checkpoint + baseline exist (ORFS runs via GNU make in a space-free worktree at ~/pv_rsz_evolve_work).
- Graphify rsz_focus graph (10,950 nodes), GRAPH_REPORT.md, graph.html, callflow.html; clusters.json covers all 171 rsz files.

### Earlier
- Clean-slate branch, numbered layout, README, Makefile (GNU make 3.81 compatible), `VERSIONS.lock`.
- OpenROAD `6932b629` + ORFS `a47d4fdc` cloned (blobless) at `external/`; rsz frozen in `01_openroad_original/rsz_snapshot`; champion = original.
- Stock OpenROAD built with Bazel on macOS arm64 in 22 min: `build/bin/openroad_stock -version` works.
- Homebrew: bazelisk, yosys 0.71, python 3.12, pipx; `graphify` 0.9.105 via pipx.
- Evaluation Tcl (`03_evolution_framework/rszevolve/eval/tcl/eval_repair_timing.tcl` + `path_report.tcl`) smoke-tested on the gcd Nangate45 test design: pre/post WNS, TNS, hold, DRV, area, buffers, worst-path JSON. Runs in under a second.
- Python: config, util, budget, claude_runner (headless `claude -p`, verified JSON shape), run_eval, score, paths, checkpoints (ORFS driver + stressed-SDC calibration), baseline, cli skeleton.

## Not yet run (needs Claude usage, so run when you have budget)
- `make context` — generates 09_agent_context (big picture, 171 file cards, 6 dossiers, glossary). Costs roughly 1-3 USD-equivalent of Sonnet usage. Run `make context ONLY="big_picture algorithms"` first if budget is tight (dossiers work from sources).
- `make evolve N=1 BUDGET_USD=5` — first real iteration.

## Safe tasks for a helper agent (no Python in 03_evolution_framework/)
Run from the repo root. Everything is idempotent.

1. **Install the standalone Claude Code CLI** so `claude` is on PATH (today the framework falls back to the VS Code extension's bundled binary):
   `curl -fsSL https://claude.ai/install.sh | bash` then `claude --version`.
2. **Generate placed checkpoints for aes and ibex** (gcd is done) (ORFS synth→place, no repair_timing). This is pure ORFS and takes a while for ibex:
   `make checkpoints TIER=A` (skips gcd; or per design: `cd 03_evolution_framework && .venv/bin/python -m rszevolve checkpoints --only nangate45/aes`).
   Expected output: `04_benchmarks/designs/nangate45/<design>/{placed.odb,nominal.sdc,stressed.sdc,design.json}`.
   If ORFS fails, attach `04_benchmarks/orfs_runs/<pdk>__<design>/make_place.log` tail.
3. **Run the baseline** once checkpoints exist: `make baseline TIER=A` → `05_baseline_results/SUMMARY.md`.
4. **Graphify on the whole OpenROAD tree** (rsz_focus is done): `make graphify SCOPE=full` (30+ min, offline).
5. (done) rsz unit tests verified passing.
6. **Record versions**: `make lock-versions`, then commit with message `chore: lock tool versions`.
7. Tier B checkpoints when A is done: `make checkpoints TIER=B` (asap7/ibex and nangate45/jpeg are slow; fine to run overnight).

Anything that touches `03_evolution_framework/` or the Makefile should be left to Claude.
