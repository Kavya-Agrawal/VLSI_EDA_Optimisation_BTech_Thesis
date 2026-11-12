> Approved plan (2026-11-12). One correction discovered during implementation: OpenROAD removed its CMake build on 2026-11-01, so all builds use **Bazel** (`tools/build_openroad.sh`), which is hermetic and identical on macOS/Linux/Docker. Everywhere the plan says cmake/ninja, read bazelisk.

# Plan: `pv_resizer_evolve` — clean-slate, Graphify-grounded, multi-agent evolution of the OpenROAD Resizer (rsz)

## Context

The thesis repo currently carries ~1 GB of earlier work (ABC/PV-Evolve dashboards, OptMirror, fabricated "3,500 candidate" catalogues, Docker-only runners). None of it is reusable as-is for the new goal and the user wants a genuinely clean working tree on a new branch. Exploration established the hard facts that shape this plan:

- **No OpenROAD exists on this Mac** (arm64, 10 cores, 16 GB). No `openroad`, no `yosys`, no Docker. `external/OpenROAD` and `external/OpenROAD-flow-scripts` are empty submodule dirs (pinned to OpenROAD `63fe72c5` / ORFS `68cc9bc9`). `build/` is a stale ABC build. All earlier runs happened in Docker on a separate Linux PC with x86-only cmake flags.
- **The previous framework had no LLM agents at all** (seeded mutation over 6 fixed C++ blocks). Results under `openroad_timing_evolution/results/` and `OPENROAD_EVOLUTION_FINAL/` are synthetic/hand-written and must not be carried forward.
- A few pieces are worth salvaging as *ideas* (not files): `tcl/phase0_repair.tcl` (load checkpoint → `estimate_parasitics -placement` → `repair_timing` → report), `tcl/path_extract.tcl` (walk `find_timing_paths` into JSON), the Yosys `equiv_*` gate, the ctest subset `rsz.repair_setup_*`, and the fail-closed paired scoring in `metrics.py::compare`.
- Upstream rsz has since been refactored into `Optimizer`, `move/*Generator`+`*Candidate` pairs, `policy/`, `RepairSetup*`, `Rebuffer`, `RepairDesign`, `RepairHold`, `RecoverPower`, `DelayEstimator*`, etc. This modular layout maps cleanly onto per-algorithm coding sub-agents.

User decisions (from Q&A): **native macOS build, kept portable/reproducible (Linux + Docker recipes too)**; **agents driven by headless Claude Code CLI (`claude -p`) with a user-settable iteration count and token/cost budget**; **benchmarks tiered: start Nangate45 gcd/aes/ibex, escalate to jpeg + ASAP7 ibex, final validation on the full ORFS Nangate45 set**.

Target outcome: a branch where `make setup && make build-openroad && make graphify && make context && make checkpoints && make baseline && make evolve N=5 BUDGET_USD=20` runs the whole pipeline, with every prompt, diff, metric and path-level feedback logged so progress can be visualised.

---

## 0. Branch and clean slate

1. `git checkout -b pv_resizer_evolve` from `pv-evolve/framework-implementation` (history stays in git, working tree is emptied).
2. `git rm -r` everything tracked except `.gitmodules` and `.gitignore`: `archive/`, `OPENROAD_EVOLUTION_FINAL/`, `openroad_evolution/`, `openroad_timing_evolution/`, `Makefile`, `README.md`. Delete untracked `build/` (ABC) and `.vscode/`.
3. Rewrite `.gitignore` (ignore OpenROAD build dirs, checkpoints >50 MB, `graphify-out/` raw caches, `__pycache__`, `.venv`).
4. Commit `chore: clean slate for pv_resizer_evolve`.

## 1. Repository layout (numbered so it reads top-to-bottom)

```
.
├── README.md                     # map of the repo + quick start (make help)
├── Makefile                      # all user-facing commands (see §7)
├── VERSIONS.lock                 # pinned commits/versions: OpenROAD, ORFS, graphify, brew formulae, python
├── 00_docs/                      # this plan, architecture.md, how_to_reproduce.md, decisions.md
├── 01_openroad_original/         # READ-ONLY reference
│   ├── rsz_snapshot/             #   frozen copy of external/OpenROAD/src/rsz at the pinned commit
│   ├── sta_interface_snapshot/   #   the dbSta/sta headers rsz depends on (for context only)
│   └── UPSTREAM_COMMIT.txt
├── 02_openroad_evolved/          # the evolving code
│   ├── champion/rsz/             #   current best full src/rsz tree (copied into the build tree)
│   ├── champion.patch            #   champion vs original, unified diff
│   ├── candidates/<iter>_<id>/   #   each proposal: rsz tree + patch + HYPOTHESIS.md
│   └── lineage.json              #   parent/child, accepted/rejected, scores
├── 03_evolution_framework/       # python package `rszevolve` (planner, coder, evaluator, orchestrator)
├── 04_benchmarks/                # inputs the resizer consumes
│   ├── designs/<pdk>/<design>/   #   checkpoint .odb + .sdc (+ stressed .sdc) + platform setRC.tcl + libs symlinks
│   ├── tiers.json                #   tier A/B/C membership
│   └── scripts/                  #   make_checkpoint.tcl (ORFS up to 3_5_place_dp, then write checkpoint)
├── 05_baseline_results/          # stock OpenROAD numbers: metrics.json, paths.json, log per design (×3 replicates)
├── 06_evolved_results/           # per-iteration: metrics, paths, deltas vs baseline + champion, verdict
├── 07_visualizations/            # html dashboard + png plots generated from 05/06/11 (`make viz`)
├── 08_graphify/                  # graphify outputs (full repo + rsz-focused), wiki, call-flow html
├── 09_agent_context/             # curated context packs the agents actually read (see §3)
├── 10_agent_knowledge/           # what agents learned: rulebase.md, lessons.md, hypotheses_ledger.md, dead_ends.md
├── 11_agent_data/                # raw per-iteration logs: prompts, responses, token usage, timings
├── tools/                        # build_openroad_macos.sh, build_openroad_linux.sh, Dockerfile, check_env.sh, install_deps_*.sh
└── external/                     # submodules: OpenROAD, OpenROAD-flow-scripts (pinned)
```

## 2. Toolchain, build, portability (`tools/`, `VERSIONS.lock`)

- **Pin versions**: use the latest ORFS release tag and *its* pinned OpenROAD submodule commit (guarantees ORFS scripts ↔ OpenROAD compatibility and gives the modern `Optimizer`/`move/` rsz layout). Fallback if the build breaks on arm64: the already-known `63fe72c5` + `68cc9bc9`. Record both in `VERSIONS.lock`.
- **`tools/install_deps_macos.sh`**: brew install `cmake ninja bison flex swig boost eigen spdlog tcl-tk zlib libomp pkgconf python@3.12 pipx` (+ `yosys` for the optional equivalence gate, `or-tools` if the pinned OpenROAD needs it). Script prints versions into `VERSIONS.lock`.
- **`tools/build_openroad_macos.sh`**: `cmake -S external/OpenROAD -B build/openroad -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo -DBUILD_GUI=OFF -DENABLE_TESTS=ON -DLINK_TIME_OPTIMIZATION=OFF` (no `-march`), `ninja -C build/openroad openroad -j8`. Incremental rebuild after an rsz-only edit is ~1–3 min, which is what the evaluator relies on.
- **`tools/build_openroad_linux.sh`** and **`tools/Dockerfile`** (multi-arch, based on `openroad/flow-ubuntu22.04-dev`): same cmake flags, so results can be reproduced elsewhere. `make docker-build` / `make docker-shell` targets.
- **`tools/check_env.sh`** (= `make env-check`): verifies compilers, brew deps, submodule commits match `VERSIONS.lock`, `openroad -version`, `claude --version`, `graphify --version`, free RAM/disk; prints a pass/fail table.
- Overlay mechanism for evolved code: the build tree compiles `external/OpenROAD` with `src/rsz` **replaced by a symlink/rsync** to `02_openroad_evolved/<candidate>/rsz`. Original stays untouched in the submodule; the framework swaps the rsz dir, rebuilds incrementally, and restores. Two build dirs (`build/openroad_stock`, `build/openroad_evolved`) so the baseline binary is always available.

## 3. Phase 1 — Graphify + agent context (`08_graphify/`, `09_agent_context/`)

1. Install `pipx install graphifyy` (needs Python ≥3.10 → brew `python@3.12`); `graphify claude install` registers the `/graphify` skill. Pin version in `VERSIONS.lock`.
2. **Run graphify twice** (code-only extraction runs offline; the semantic pass on docs/markdown uses the Claude session):
   - `08_graphify/full_openroad/` — whole `external/OpenROAD/src` (big-picture map: which modules rsz talks to: `dbSta`, `sta`, `odb`, `grt`, `dpl`, `est`/parasitics, `utl`).
   - `08_graphify/rsz_focus/` — `src/rsz` + `src/dbSta` + `src/sta/include` + `src/rsz/test` + ORFS `flow/scripts/{resize,cts,global_route,floorplan}.tcl` with `--wiki` and `graphify export callflow-html`. Keep `graph.json`, `GRAPH_REPORT.md`, `graph.html`, wiki.
3. **Context-building script** (`rszevolve/context/build_context.py`, run via `make context`): reads `graph.json`, computes for each rsz file its callers/callees/community, then drives a Claude Code headless pass that writes:
   - `09_agent_context/00_BIG_PICTURE.md` — what problem rsz solves, where it sits in the ORFS flow (3_4 repair_design → CTS → repair_timing → post-GRT repair_timing), the resizer↔STA incremental loop (`estimate_parasitics`, `findRequireds`, `vertex slack`), what inputs it consumes (placed ODB, SDC, liberty, RC) and what it outputs (resized/buffered netlist + legalized placement).
   - `09_agent_context/files/<File>.md` — one card per rsz source file: purpose, public entry points, precise inputs/outputs/side effects, key data structures, callers/callees (from graph), invariants and "do not break" notes.
   - `09_agent_context/algorithms/<cluster>.md` — one dossier per algorithm cluster (§4): the problem statement, the current heuristic step by step, its complexity/approximations, known weaknesses, literature pointers (e.g., van Ginneken/Lillis buffering, Lagrangian-relaxation sizing, TILOS, slack-budgeting, timing-driven ECO), and the exact file set the cluster owns.
   - `09_agent_context/clusters.json` — machine-readable: cluster → {files, entry points, tests, allowed-to-edit, read-only context}.
   - `09_agent_context/GLOSSARY.md`, `09_agent_context/EVAL_CONTRACT.md` (what the evaluator measures and how verdicts are reached).
4. Deliverable check for Phase 1: every file in `src/rsz/src` has a card; every cluster dossier lists inputs/outputs; `graph.html` opens; a human can read `00_BIG_PICTURE.md` and understand the subsystem in 10 minutes.

## 4. Algorithm clusters → coding sub-agents (scoped contexts)

Derived from upstream file layout + graphify communities (final membership is confirmed by `clusters.json` after Phase 1):

| Sub-agent | Owns (editable) | Problem it may re-think |
|---|---|---|
| `setup_strategy` | `RepairSetup*`, `RepairTargetCollector`, `PathGroupFilter`, `Optimizer*`, `policy/`, `MoveTracker`, `MoveCommitter` | Which endpoints/paths to attack, in what order, how many moves per pass, acceptance criteria, TNS vs WNS budgeting, stopping rules |
| `sizing` | `move/SizeUp*`, `SizeDownFanout*`, `VtSwap*`, `SwapPins*`, `DelayEstimator*`, `LRSubproblem` | Gate-sizing choice (greedy vs Lagrangian/sensitivity-based, load-aware, multi-stage lookahead) |
| `buffering` | `Rebuffer*`, `BufferedNet`, `move/Buffer*`, `SplitLoad*`, `Clone*`, `Unbuffer*`, `BufferToInverters*` | Buffer-tree construction/selection, cloning vs splitting, where to insert |
| `hold` | `RepairHold*` | Hold fixing with minimal setup damage |
| `drv` | `RepairDesign*` | Slew/cap/fanout repair strategy pre-timing |
| `timing_model` | `SequentialTimingEstimator`, `SkewBudget`, `DelayEstimatorBufferTree` | Estimation used to rank moves |

Each sub-agent receives only: its dossier, its file cards, the read-only cards of files it calls, `00_BIG_PICTURE.md`, `EVAL_CONTRACT.md`, the planner's hypothesis spec, and the latest evaluator feedback. The prompt explicitly demands an *algorithm/heuristic change with a stated rationale*, forbids pure micro-optimisation/data-structure churn, and requires a `HYPOTHESIS.md` (problem → current approach → new approach → why WNS/TNS should improve → risks).

## 5. Phase 2 — Evolution framework (`03_evolution_framework/rszevolve/`)

```
rszevolve/
├── cli.py                 # `python -m rszevolve <cmd>`; all make targets call this
├── config.py              # paths, tiers, budgets, model names; defaults in config/default.yaml
├── orchestrator.py        # the loop: plan → code → build → gate → evaluate → feedback → record
├── agents/
│   ├── claude_runner.py   # wraps `claude -p --output-format json --max-turns K --allowedTools ...`; returns text + usage
│   ├── planner.py         # reads feedback + knowledge + ledger → picks cluster, writes hypothesis spec
│   ├── coder.py           # dispatches the cluster sub-agent in a sandboxed candidate dir (cwd = candidate rsz tree + context)
│   ├── evaluator_agent.py # turns raw metrics/paths into a narrative feedback.md (root-cause guesses per path)
│   └── prompts/*.md       # planner.md, coder_<cluster>.md, evaluator.md, rulebase_update.md
├── eval/
│   ├── build.py           # overlay candidate rsz into build tree, incremental ninja, capture compile errors → coder repair loop (≤3 tries)
│   ├── gates.py           # ctest subset (rsz.repair_setup*/repair_hold*/repair_design*), check_placement, DRV deltas, optional yosys equiv
│   ├── run_eval.py        # runs tcl/eval_repair_timing.tcl per design/replicate, parses JSON
│   ├── paths.py           # top-N worst paths: endpoint, startpoint, slack, stages, max slew/cap/fanout, wire-dominated?, buffers added; diff vs baseline/champion
│   ├── score.py           # paired, fail-closed: Δ(WNS/period), Δ(TNS/(period·endpoints)), per-tier aggregate, hold/DRV regressions reject
│   └── tcl/eval_repair_timing.tcl, tcl/path_report.tcl, tcl/make_checkpoint.tcl
├── knowledge/             # rulebase.py (self-evolving rules), ledger.py (hypotheses, outcomes)
├── budget.py              # token/cost accounting from claude JSON usage; stop when N iters or BUDGET_USD/MAX_TOKENS reached; resume
└── report/                # viz.py (plots + html dashboard), summary.py
```

**One iteration** (`make evolve-one` or one loop of `make evolve N=…`):
1. **Planner** (`claude -p`, model configurable, default Opus-class for planning): inputs = last `feedback.md`, `10_agent_knowledge/*`, `lineage.json`, cluster dossiers index. Output = `hypothesis_<iter>.md` + JSON {cluster, rationale, files, success criteria}.
2. **Coder sub-agent** for that cluster: works inside `02_openroad_evolved/candidates/<iter>_<id>/rsz` (copied from champion), scoped context in its cwd, tools limited to Read/Edit/Grep/Bash(limited). Produces code + `HYPOTHESIS.md`.
3. **Build + repair loop**: compile errors fed back to the same coder session (`--resume`) up to 3 times.
4. **Gates**: ctest subset, `check_placement`, no new max-slew/cap/fanout violations beyond tolerance, hold WNS not worse than baseline by > ε, optional Yosys equivalence on gcd. Any failure → rejected with reason logged.
5. **Evaluate** on tier designs (×2 replicates for determinism check), with timeout. Metrics + paths JSON written under `06_evolved_results/<iter>/`.
6. **Evaluator agent** writes `feedback.md`: WNS/TNS vs baseline & champion per design, the worst 10 paths with attributed causes (e.g., "endpoint X: 14 stages, 0.41 pF on net N, 3 buffers inserted, still −0.12 ns → wire-dominated, rebuffer should have split load"), what the hypothesis predicted vs observed, paths newly fixed/newly broken.
7. **Record**: accept/reject into champion, `lineage.json`, `11_agent_data/<iter>/` (prompts, responses, usage), rulebase update by the planner (lessons/dead-ends).

**Budget control**: `make evolve N=10 BUDGET_USD=25 MAX_TOKENS=…`; `budget.py` reads `total_cost_usd`/usage from each `claude -p` JSON result, stops cleanly when exhausted, prints a per-iteration cost table, and `make evolve-resume` continues from `lineage.json`.

## 6. Evaluation design (fast, pre-route, exactly the ORFS timing commands)

- **Checkpoints** (`make checkpoints`, once): for each design run ORFS `make DESIGN_CONFIG=… do-3_5_place_dp` (synth → floorplan → global place → `repair_design` → detailed place), then copy `3_5_place_dp.odb` + `3_place.sdc` + platform `setRC.tcl`/libs into `04_benchmarks/designs/nangate45/<design>/`. Also generate a `stressed.sdc` (clock period × 0.8–0.9) so every design has real negative slack to repair (gcd otherwise closes timing trivially → no signal). Optional post-CTS checkpoint variant via `make_checkpoint.tcl` (CTS without ORFS's own repair_timing) for a second evaluation point.
- **`eval_repair_timing.tcl`** (mirrors ORFS `cts.tcl`/`resize.tcl` steps): `read_db`, `read_sdc`, `source setRC.tcl`, `estimate_parasitics -placement`, record pre-repair `report_wns/report_tns`, timed `repair_timing -setup -repair_tns 100 [-setup_margin]` (ORFS defaults, configurable), `detailed_placement`, `estimate_parasitics -placement`, `report_worst_negative_slack_metric`, `report_tns_metric`, `report_check_types -violators`, `report_design_area_metrics`, `-metrics` JSON, plus `path_report.tcl` dumping the top-N `find_timing_paths -sort_by_slack` with per-pin slew/cap/fanout/wire length into JSON. No routing, no GDS.
- **Tiers** (`04_benchmarks/tiers.json`): A = nangate45 gcd/aes/ibex (every iteration, each eval ≈ seconds–few minutes); B = + nangate45 jpeg, asap7 ibex (every 5th iteration or when a candidate beats the champion on A); C = full ORFS nangate45 design set (final validation of the champion, `make validate-champion`). Planner is told the tier results separately so it does not overfit to gcd.
- **Baseline** (`make baseline`): stock binary, 3 replicates per design per SDC variant → `05_baseline_results/`, including paths JSON and runtime; determinism report.

## 7. Makefile (user-facing, simple)

`help` (default) · `env-check` · `setup` (submodules at pinned commits, deps, pipx graphify, python venv) · `build-openroad` (+ `build-openroad-stock`) · `graphify` · `context` · `checkpoints` · `baseline` · `evolve N=5 BUDGET_USD=20 TIER=A` · `evolve-one` · `evolve-resume` · `validate-champion` · `report` · `viz` · `show-champion` (diff) · `docker-build` / `docker-shell` · `clean-results` · `clean-build` · `test` (framework unit tests with a fake `openroad` stub).

## 8. Logging & visualisation (`07_visualizations/`, `11_agent_data/`)

Per iteration: hypothesis, cluster, diff stats, build/gate outcome, per-design WNS/TNS/area/buffers/runtime, Δ vs baseline and champion, token/cost, verdict. `make viz` renders: WNS/TNS vs iteration per design (baseline line + champion staircase), accept/reject timeline coloured by cluster, cost per iteration, worst-path slack histograms before/after, and an index.html linking each iteration's HYPOTHESIS.md/feedback.md/patch.

## 9. Order of work (what gets implemented, in sequence)

1. Branch + clean slate + layout skeleton + README + Makefile `help/env-check/setup`.
2. `tools/` deps + macOS build; stock binary runs `openroad -version`. Pin `VERSIONS.lock`. Linux/Docker recipes written alongside (Docker verified only as far as the image builds).
3. Phase 1: graphify runs, `rsz_snapshot`, `make context` → `09_agent_context/` complete.
4. Checkpoints + eval tcl + baseline for tier A (stressed SDC calibrated so baseline WNS < 0).
5. Framework: claude_runner + budget, evaluator (build/gates/run/paths/score), planner, coder dispatcher, orchestrator, knowledge, report/viz; unit tests with stubbed openroad/claude.
6. Smoke: `make evolve N=1` end-to-end; then `N=3` to validate the feedback loop; commit.

## 10. Verification

- `make env-check` passes on this Mac; `build/openroad_stock/bin/openroad -version` prints the pinned commit.
- `make graphify` produces `graph.json`/`GRAPH_REPORT.md`/`graph.html` for both scopes; `make context` yields one card per rsz source file and one dossier per cluster (script asserts coverage).
- `make baseline` writes metrics for gcd/aes/ibex with negative WNS under `stressed.sdc`, 3 replicates agree within tolerance.
- `make test` runs framework unit tests (scoring, path attribution, budget stop, overlay/restore of rsz dir, parsing of `-metrics` JSON) using stubs.
- `make evolve N=1`: one full iteration finishes; `06_evolved_results/0001/` contains metrics, paths, feedback.md; `11_agent_data/0001/` has prompts/responses/usage; `lineage.json` records verdict; a deliberately broken candidate is rejected at the build gate; a no-op candidate scores 0 and is rejected (fail-closed).
- `make viz` opens a dashboard showing baseline vs iteration numbers.

## Notes / assumptions

- Submodule checkout of OpenROAD (recursive) and ORFS is multi-GB and the first build is ~1–2 h on this machine; both are one-time.
- The ORFS checkpoint generation needs Yosys (brew `yosys`) for synthesis; after checkpoints exist, Yosys is only used by the optional equivalence gate.
- Clean slate removes earlier material from this branch's working tree only; it remains on `pv-evolve/framework-implementation` and in history.
- Agents never edit `external/OpenROAD` directly; they edit candidate copies under `02_openroad_evolved/`.
