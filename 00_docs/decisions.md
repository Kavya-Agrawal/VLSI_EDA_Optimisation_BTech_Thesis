# Decisions log

Each entry: what was decided, why, what it rules out. Newest at the bottom.

## 2026-11-12 — Clean-slate branch
Everything from earlier thesis work was removed from the working tree of `pv_resizer_evolve`
(it remains in git history and on `pv-evolve/framework-implementation`). Earlier result files were
synthetic and are never cited here.

## 2026-11-12 — Pin to ORFS master (2026-11-11) and its OpenROAD submodule
`a47d4fdc` / `6932b629`. The last ORFS release tag (v3.0) is from January 2024 and predates the
`Optimizer` / `move/*Generator` refactor of rsz, which is exactly the modular layout the coding
sub-agents are scoped on. ORFS pins the OpenROAD commit it was tested with, so flow scripts and
binary are known-compatible. Fallback pair recorded in `VERSIONS.lock`.

## 2026-11-12 — Bazel, not CMake
OpenROAD removed CMake on 2026-11-01. Bazel is hermetic (own LLVM, Tcl, zlib), so one script serves
macOS / Linux / Docker. Cost: first build is long and `.bazelversion` 9.3.2 is fetched by bazelisk.
`--config=no-werror` is used so an agent's warning does not masquerade as a build failure; warnings
are still captured and shown to the coder.

## 2026-11-12 — Native macOS build, portable recipes
User choice. `tools/install_deps_linux.sh` + `tools/Dockerfile` keep Linux reproduction one command
away; `VERSIONS.lock` records everything that could drift.

## 2026-11-12 — Agents via headless Claude Code CLI
`claude -p --output-format json` returns usage and `total_cost_usd`, which `rszevolve.budget` sums
to enforce `BUDGET_USD` / `MAX_TOKENS`. Each sub-agent runs with `--add-dir` limited to its candidate
tree and context pack, and an allowed-tools list without network. The bundled CLI under the VS Code
extension is accepted when `claude` is not on PATH.

## 2026-11-12 — Evaluation on post-placement, pre-CTS checkpoints with ideal clocks
This is the exact state ORFS hands to `repair_timing` for the first time, matches the user's
"after global and detailed placement, in a loop with the timer", and avoids running CTS inside every
evaluation. A post-CTS variant can be added per design later (`make checkpoints VARIANT=post_cts`).

## 2026-11-12 — Stressed SDC variants
Nangate45 gcd/aes close timing trivially at the ORFS default period, which gives the evaluator no
signal. Each design gets a `stressed.sdc` whose clock period is tightened until the stock resizer
leaves a clear negative WNS. Both variants are measured; the loop scores on `stressed` by default.

## 2026-11-12 — Fail-closed scoring
A candidate must beat the champion on the paired per-design score and must not regress hold WNS or
DRV counts beyond tolerance, pass rsz regression tests, and keep the placement legal. Equal or
unknown is a rejection. This is the same stance as the earlier PV-Evolve work and SATLUTION.

## 2026-11-12 — Context packs are generated, then hand-editable
`make context` writes `09_agent_context/`. Files containing the line `<!-- hand-edited -->` are never
overwritten by a later run.
