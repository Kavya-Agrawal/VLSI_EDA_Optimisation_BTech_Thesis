# DelayEstimatorReporter.cc

## Purpose
A diagnostic-only layer in the Resizer. It measures how well the rsz delay estimators predict real STA results. For one instance it takes the estimator's predicted timing gain from a cell swap or a planned rebuffer tree. It then applies the change inside an OpenDB ECO journal, re-times with STA, undoes the ECO, and prints predicted vs. golden stage tables. It is not part of any repair or optimisation loop and runs on the main thread only. It backs the Tcl commands `report_delay_estimator_accuracy` and `report_delay_estimator_accuracy_for_rebuffering`.

## Public entry points
Declared in `DelayEstimatorReporter.hh`.
- `static const std::vector<std::string_view>& knownEstimatorNames()` returns `{"legacy","stage_window"}`. `Resizer.cc:~1994` iterates it for Tcl validation.
- `static std::optional<EstimatorKind> parseEstimatorKind(const std::string&)` maps a name to `kLegacy` or `kStageWindow`, else `nullopt`. `Resizer.cc:1987` uses it as a validity check.
- `explicit DelayEstimatorReporter(Resizer&)` caches `sta()`, `network()`, `graph()`, `logger()`, `maxAnalysisMode()` and `resizer.block_`. It is a `friend` of `Resizer` (`Resizer.hh:1227`).
- `void reportAccuracyForSizing(sta::Instance* inst, sta::LibertyCell* replacement, const std::string& estimator, int delay_levels)` compares the predicted vs. STA-measured gain of a temporary cell swap. `Resizer.cc:~1972` calls it, via `Resizer.i` `report_delay_estimator_accuracy_cmd`.
- `void reportAccuracyForRebufferTree(sta::Instance* inst, sta::Pin* driver_pin, int delay_levels)` plans a RebufferMt tree on the worst path through `inst` and compares target-path and per-side-path estimates with STA. `Resizer.cc:~1981` calls it, via `report_delay_estimator_accuracy_for_rebuffering_cmd`.

Everything else is private. A fresh reporter object is created per command.

## Inputs and outputs, precisely
**Reads**
- STA graph, arrivals, slews, arc delays, `loadCap` and wire-arc delays. It uses `sta_->findPathEnds` with an `ExceptionThru`, `PathExpanded`, `graph_->arcDelay`/`wireArcDelay`/`slew`, `GraphDelayCalc::loadCap`/`edgeFromSlew`, and `sta_->arrival`.
- Liberty data: `sceneCell`, `scenePort`, `findLibertyPort`, `bufferPorts`.
- OpenDB connectivity via `dbNetwork::staToDb`/`dbToSta` (`dbNetDriver`).
- Policy config: `OptimizationPolicyConfig::forParallelEval(RepairEffort::kHigh)`, with `delay_estimation_levels` overridden.
- `kStaSlewBias = OptimizationPolicyConfig{}.sta_slew_bias`, passed to every `DelayEstimator::buildContext`.

**Mutates**
- Trial netlist edits (`Resizer::replaceCell`, `rebuffer().applyRebufferTreePlan(plan, "delay_estimator_rebuffer")`), always inside `EcoJournalScope`.
- Side effects before the ECO: `resizer_.init()`, `resizePreamble()` and `sta_->findRequireds()`. These also set up Resizer-wide state.
- It refreshes `block_ = resizer_.block_` after `init()`.

**Output**
- Text to `logger_->report`, in ps and fF scale (`kSecondsToPicoseconds = 1e12`, `kFaradsToFemtofarads = 1e15`).
- Nothing is returned. Errors are `logger_->error` (throws) with RSZ ids 3200–3241: 3200 unknown estimator, 3201 no setup path stage, 3202 replace failed, 3209 replacement lacks the driver port, 3211 bad `-driver_pin`, 3212 undo-failure warning, 3213 arrival pin not found, 3224 no arrival vertex, 3234 context build failed, 3235 no fixed stages, 3236 no tree plan, 3237 tree not applied, 3241 no target load pin.

## Algorithm / control flow
**`reportAccuracyForSizing`**
1. Parse the estimator kind.
2. Call `init()`, `resizePreamble()`, refresh `block_`, and call `findRequireds()`.
3. Clamp `delay_levels` to `[0, kMaxDelayLevels=2]`. Legacy forces `report_levels = 0`.
4. `findWorstTargetForInstance`: a through-pin search over the instance's output pins (`findPathEndsThrough`, count `kReporterPathSearchCount=1000`, setup/max, all scenes). For each path end it expands the path and finds the first stage pin that is a requested output with non-null `prevArc` and `prevEdge`. It builds the target with `makePathDriverTarget` and attaches an `EstimatorContext` via `prepareTargetContext`. The minimum slack wins. No match calls `errorNoSetupPathStage`.
5. Check that the replacement has the driver port (3209).
6. Estimator profile (no DB mutation):
   - **Legacy** (`buildLegacyProfile`) is a single target row. delay = `gateDelay(port, load_cap)` + `prev_drive × input_pin_cap`, where `prev_drive = resizer_.driveResistance(prev_driver_pin)`. It is "legal" iff `current − candidate > 0`, giving `kEstimateLegal` or `kEstimateNonImproving`. Failure reasons are `kMissingCurrentPortMap` and `kMissingCandidatePort`. Stage rows are best-effort and skipped if the context is unavailable. The fanin penalty goes in `extra_delay`.
   - **Stage window** (`buildDelayEstimatorProfile`) calls `DelayEstimator::estimate(ctx, replacement, &trace)` and turns the trace into candidate rows. If illegal and `trace.size() < stages.size()`, it sets `candidate_stages_incomplete`. If illegal with an empty trace, it skips the tables.
7. `captureFixedStages` snapshots stage pin identities and names while the path handles are valid. This must happen before any later STA search. `assignNextPins` resolves each stage's `next_pin`.
8. Golden before: the arrival at `fixed_stages.back().driver_pin_name`, plus `buildGoldenStageRows`.
9. `EcoJournalScope` begins the ECO. `replaceCell` and `updateParasiticsAndTiming` run, then `measureGoldenAfterSwap` (arrival and the same fixed stages). The scope destructor does `initForJournalRestore()`, `undoEco`, `updateParasiticsAndTiming`, and swallows exceptions with warn 3212. A failed replace is reported after the scope exits (3202).
10. `printSummary`.

**`reportAccuracyForRebufferTree`**
1. Validate that `driver_pin` is an output of `inst` (3211), then run the same preamble.
2. Find the worst target (optionally pinned to `driver_pin`) and `captureFixedStages`. The target load pin comes from `target.load_pin`.
3. `rebufferReportContext` builds the PARALLEL_EVAL context via `OptimizationPolicy::buildPolicyContext`. It uses `include_latch_fanin=false`, so every side load counts fully.
4. `planRebufferReport` builds a `MoveCommitter`, a default `OptimizerRunConfig` and a `RebufferMtGenerator`. It runs `startPhase(0)`, `prepareInputs` and `generate`. The best candidate is the legal one with the highest `estimate().score`, else the first candidate; none gives error 3236. It calls `finishPhase()`.
5. `captureSideGoldenRows` records per-side-load pre-ECO rows and arrivals.
6. `RebufferMtCandidate::estimateTree` produces the estimate, a trace and side evaluations.
7. `buildRebufferProfiles` builds the estimated current and candidate rows and the golden-before rows.
   - Trace layout: indices up to `target_index` are path stages, then `tree_stage_count` tree stages, then the fanout stages.
   - Contiguous wire/via tree stages are folded into the preceding row via `foldWire`.
   - If the target load is the last captured stage (`split_target_load_wire`), its wire becomes a separate `<target-load wire>` row.
   - Missing rows (placeholders) are inserted for tree buffers that do not exist pre-ECO.
8. `applyRebufferTreeForGolden` runs inside an ECO scope. It applies the plan, re-times, and takes the golden after-arrival. It then re-captures the target and side stages via `captureSidePathFixedStages`. This must happen before undo, because the inserted-buffer pins exist only during the ECO. It reads each side load's after-arrival and rows, and aligns candidate row names to the golden pin names.
9. Print the summary, the side-path table (est vs. golden delta and slack; "legal"/"reject") and per-side stage details.

**Arc matching in `buildGoldenStageRow`**
- It first looks for the edge input→driver with `findMatchingTimingArc(ref_arc, ...)`.
- For `kTarget` rows only, it falls back to `pickWorstArc` with `relaxed_only=true`, then with `false`. This picks the worst arc by `min_max->compare`.
- If there is still no arc for a target, it uses `cell_delay = arrival(driver) − arrival(input)` and sets `arc_match_relaxed`.
- Wire delay comes from `fixedStageWireDelay`: the wire arc to `next_pin`, else an arrival difference.

**Side-path capture**
- `captureSidePathFixedStages` finds path ends through `load_pin` and takes the lowest-slack path that has the driver before the load.
- `collectSidePathStages` takes stages from the driver through the load, plus `delay_levels` fanout stages. It builds contexts with `buildContext(..., 0, ..., kStaSlewBias)`.
- `captureSidePathConnectivityFixedStages` then walks the OpenDB net drivers backwards from `load_pin`, at most 32 hops, through buffer cells only, until it reaches `driver_pin`. This makes inserted buffers visible. If it fails, it falls back to the STA path stages.

**Score arithmetic**
- `estimatedStageScoreDelay = cell + (extra_delay if nonzero else wire)`. `goldenStagePathDelay = cell + wire`. Non-finite values count as 0 (`finiteOrZero`). Rows with `valid=false` are skipped in sums.
- Rows whose wire or delta delay is under `kTinyStageDelayComparison = 1e-12 s` in both columns print as "-".

## Key data structures
- `EstimatorKind {kLegacy, kStageWindow}`; `Role {kFanin, kTarget, kFanout}`, assigned by `roleFor(stage_index, target_index)`.
- `TargetMatch {Target, endpoint_name, slack}`.
- `StageProfileRow {valid, path_index, role, pin_name, cell_name, input_slew, cell_delay, wire_delay, load_cap, output_slew, extra_delay, arc_match_relaxed}`. Missing data is NaN (`kMissingValue`) and prints as "-".
- `EstimatorProfile {current_stages, candidate_stages, legal, fail_reason, candidate_stages_incomplete}`.
- `GoldenProfile {before_stages, after_stages, arrival_reference_pin_name, before/after_arrival, arrival_impr}`.
- `FixedStage {DelayStageState state, role, input/driver/next pin and *_name}`. Names are stored so pins can be re-found after the ECO via `findPin`.
- `SideGoldenRow`, `SidePathReport`, `WorstSidePath`.
- `RebufferRun`, and `RebufferReportPlan {Target, CandidateVector, best}`. The candidates hold references to `target`, so the struct must not move.
- `EcoJournalScope`: RAII, non-copyable.

## Callers and callees (verified by reading)
**Callers**
- `Resizer.cc` only (`Resizer::reportDelayEstimatorAccuracy*`, `isKnownEstimator`, `knownEstimators`). The Tcl commands in `Resizer.tcl` reach it through `Resizer.i`.

**Callees**
- `DelayEstimator.cc`: `DelayEstimator::buildContext` (all overloads) and `estimate`.
- `MoveCommitter.cc` and `MoveGenerator.cc`: constructing the committer and the `GeneratorContext`.
- `RebufferMtGenerator.cc`: `startPhase`, `prepareInputs`, `generate`, `finishPhase`.
- `RebufferMtCandidate.cc`: `estimate()`, `estimateTree`, `plan()`, `sideContexts()`.
- `Rebuffer.cc`: `resizer_.rebuffer().applyRebufferTreePlan`.
- `OptimizationPolicyConfig.cc`: `forParallelEval`, `sta_slew_bias`.
- `OptimizerTypes.cc`: `makePathDriverTarget`, `failReasonName`, `Target::activeScene`, `minMax`, `inputPath`, `prevDriverPath`.
- `OptimizationPolicy`: `buildPolicyContext`.
- `Resizer`: `init`, `resizePreamble`, `replaceCell`, `updateParasiticsAndTiming`, `initForJournalRestore`, `gateDelay`, `driveResistance`.
- STA and OpenDB: `Sta.cc`, `Graph.cc`, `GraphDelayCalc.cc`, `PathEnd.cc`, `Delay.cc`, `dbNetwork`, `odb::dbDatabase::beginEco`/`undoEco`.

## Invariants and "do not break"
- **Always undo trial edits.** Every mutation must be inside `EcoJournalScope`. The destructor does `initForJournalRestore()` → `undoEco` → `updateParasiticsAndTiming()`, so STA/parasitics are valid again on exit. If the undo throws, only a warning is issued and the design may keep the edits.
- **Capture stage identities before STA is re-run.** Through-filtered `PathEnd`/`Path` handles are invalidated by the next search or `arrivalAtDriver`. Hence the capture order: fixed stages first, then arrival, then ECO. `PathExpanded` must outlive its captured path handles.
- **Golden-after must use the pre-ECO fixed stages.** Re-selecting the worst path post-ECO would mix paths.
- **Materialise rows before undo.** The inserted-buffer pins exist only while the ECO is active.
- **Do not cache STA pointers across the ECO.** Names are stored and re-resolved with `findPin`. `replaceCell` may invalidate old handles.
- **Main thread only.** The generator is started with `startPhase(0)`, i.e. a phase without worker threads.
- **Deterministic.** There is no randomness. Ties are resolved by first-found order: the slack `<` comparison for targets, and `>` on score for the best candidate.
- **Keep estimator and golden configuration matched.** Both use `kStaSlewBias`, and the estimator uses the PARALLEL_EVAL / `kHigh` policy config.
- **Estimated and golden rows are aligned positionally.** `splitFinalLoadWire`, `insertRebufferTreePlaceholders`, `insertSidePathPlaceholders` and `alignSidePathCandidateNames` exist to keep them aligned. Changing the row layout in one place requires changing the others.
- It does not itself check `dont_touch`. It relies on `replaceCell` and the generators.

## Weak spots / assumptions an algorithm designer should know
- **Window limit.** `kMaxDelayLevels = 2`. Deeper windows are silently clamped (the comment cites accumulating table-cascade error).
- **Single worst path.** The report measures one path through the instance (min slack among up to 1000 path ends). Other paths, and other endpoints through the changed net, are not included. Only setup/max is analysed.
- **Reference arrival.** For sizing, the reference is the last captured stage's driver pin. For rebuffering, it is `next_pin_name` of the last stage, falling back to its driver pin. "Golden delta" is an arrival change at that pin, not an endpoint slack change.
- **Legacy ignores the window.** It models only the target stage: `gateDelay` plus a fanin-resistance × input-cap term. It does not model slew propagation or fanout effects.
- **Relaxed arc fallback only for `kTarget` rows.** Estimator and golden may compare different arcs (conditional / non-unate such as XOR). This is flagged with `arc_match_relaxed`, but the error can look larger or smaller than it is. The fallback "worst arc" is chosen by min/max compare, which may not be the arc STA used.
- **Connectivity-based side-path capture.** It assumes the chain from the load back to the driver passes only through buffer cells and is at most 32 hops. Otherwise it falls back to the STA path, which may not show the inserted buffers.
- **Placeholder and name alignment.** Name alignment copies pin names only for `kTarget` rows at indices ≥ 1 and requires valid golden rows, so a mismatch in row counts silently truncates the alignment.
- **Candidate choice.** The "best" tree is the legal one with the highest estimate score. It falls back to `first_tree` even if no tree is legal, so the report may describe a tree the policy would not commit.
- **Silent skips.** Side paths with `evaluation == nullptr` (target estimate failed) are omitted from the detail tables. Estimates that fail mid-walk show "(incomplete)" and suppress sums.
- **Tiny deltas are hidden.** A comparison below 1e-12 s on both sides prints "-". Errors at that scale cannot be seen.
- **Resizer side effects.** `init()` and `resizePreamble()` run before every report, so the command is not a pure read of the design state even though the netlist is restored.
- **Exact legacy score.** There is a `kLegacy` `legal` flag (`arrival_impr > 0`) but no threshold or margin. A tiny positive gain counts as legal.