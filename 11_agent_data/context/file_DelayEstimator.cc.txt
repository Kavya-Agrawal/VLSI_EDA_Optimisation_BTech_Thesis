I've read the full file, its headers and the type definitions in `OptimizerTypes.hh`. I'm writing the card now.

# DelayEstimator.cc

## Purpose
Implements the stateless, Liberty-table-based delay model used by the multithreaded (MT) setup-repair moves (size up/down, VT swap, pin swap, rebuffer, split load). `buildContext()` runs on the main thread and snapshots STA state for a target driver into an `EstimatorContext`. The `estimate*` functions then score candidate cells from that snapshot and the Liberty tables only, so they are safe on worker threads. The file also holds the optional STA "slew-bias" sampler, the fanin side-load and dual rise/fall penalties, and helpers shared with `DelayEstimatorBufferTree.cc` through `DelayEstimatorInternal.hh`.

## Public entry points
All are `static` methods of `DelayEstimator` (declared in `DelayEstimator.hh`) unless noted.

- `bool findArcDelay(const SelectedArc&, float input_slew, float load_cap, const LibertyCell*, float& delay)`
  - One exact-match table lookup of cell delay on the selected arc.
  - Used by candidate code for ad-hoc delay queries.
- `optional<EstimatorContext> buildContext(Resizer&, const Target&, int delay_levels, FailReason*, bool use_sta_slew_bias, bool include_latch_fanin, DelayEstimatorCache*, const FaninSideLoadOptions*, bool dual_rf_eval)`
  - Main entry. Expands `target.endpoint_path` into a `PathExpanded`, takes scene and min/max from the path, and defaults min/max to `resizer.maxAnalysisMode()`.
  - Asserts `target.canBePathDriver()`.
- `buildContext(Resizer&, Instance*, Pin* driver_pin, const PathExpanded&, int path_index, const Scene*, const MinMax*, int delay_levels, ...)`
  - Lower-level overload that does the real work. Used by tests and policy prepare code.
- `DelayEstimate estimate(const EstimatorContext&, const LibertyCell* candidate_cell, vector<StageEvaluation>* trace=nullptr)`
  - Scores swapping the target to `candidate_cell`. This is the main ranking function.
  - Clears `trace` first, if one is given.
- `DelayEstimate estimateLoadChange(const EstimatorContext&, float target_load_delta)`
  - Same window walk with the target keeping its current cell and its load shifted by a delta. Used by split-load and fanout-size-down candidates.
- `bool findBufferDelay(const EstimatorContext&, const LibertyCell* buffer, float input_slew, float load_cap, float& delay)`
  - Buffer delay on the target's output transition. Wraps `lookupBufferDelayAndSlew`.
- `void chargeMovedLoads(const EstimatorContext&, const vector<SideLoad>&, float delay_delta, DelayEstimate&)`
  - Charges loads that a split moves to a new driver.
- Free function `float oppositeRfSideLoss(float opposite_slack, float delay_delta)`
  - Negative-region slack loss.
- `DelayEstimatorCache` (methods defined in this file)
  - `clear()`.
  - `maxEquivalentInputCapIncrease(Resizer&, const DelayStageState&)`.
  - `getOrSampleSlewBias(Resizer&, const DelayStageState&, float max_load_delta)`.
- `namespace estimator_detail` (internal, for `DelayEstimatorBufferTree.cc`)
  - `lookupArcDelayAndSlew`, `lookupBufferDelayAndSlew`, `estimateOutputSlew`, `estimateReceiverInputSlew`, `wireElmoreDelay`, `makeEstimate`.

Callers per the graph: `DelayEstimatorBufferTree.cc`, `DelayEstimatorReporter.cc`, `OptimizationPolicy.cc`, `SequentialTimingEstimator.cc`, `TestDelayEstimatorMt.cc` and the `*MtCandidate.cc` / `*MtGenerator.cc` files. I did not read those callers.

## Inputs and outputs, precisely
**Reads, in `buildContext` (main thread only):**
- STA graph and path data:
  - `Path::prevArc` and `prevEdge`.
  - `Graph::arcDelay` and `wireArcDelay`.
  - `Graph::slew` on the driver vertex, per rise/fall and dcalc analysis point.
  - `GraphDelayCalc::edgeFromSlew` for input slew and `loadCap(driver_pin)` for load.
- Liberty data:
  - Scene cells via `LibertyCell::sceneCell(scene, min_max)`.
  - Pvt from `scene->sdc()->pvt(inst)`, falling back to `operatingConditions`.
  - GateTableModel delay and slew tables.
- Slack and network data:
  - `sta->slack(vertex, min_max)` for side loads.
  - `sta->slack(driver_vertex, rf, min_max)` for the opposite transition.
  - `isClock`, `driveResistance`, `equivCells`, `dontUse` and `isLinkCell`.
  - When slew bias is on, the live reduced Pi parasitic of the driver net.

**Mutates:**
- Only the returned `EstimatorContext`.
- Exception: `buildSlewBiasModel` temporarily overwrites the live Pi model (`Parasitics::setPiModel`) and calls `ArcDelayCalc::gateDelay` and `finishDrvrPin`. The `PiModelRestore` RAII guard puts the model back on every exit path.
- It also writes the profiler events `slew_bias_model_hits`, `slew_bias_model_misses`, `fanin_side_loads_collected` and `dual_rf_arcs_prepared`.
- The warning 3210 and the `delay_estimator` debug messages go to the logger.

**Returns:**
- `EstimatorContext`. The target is `path_stages[target_stage_index]`, and `current_total_delay` is the sum of `stage.current_delay`.
- `DelayEstimate{legal, candidate_delay, arrival_impr, side_paths_evaluated, side_loss, reason}`.
- Failures set `*fail_reason` and return `nullopt`.

**`estimate*` reads only** the context, Liberty tables and `candidate_cell`. It touches no STA, odb or parasitics, and has no side effects apart from the optional `trace`.

## Algorithm / control flow

### `buildDelayStageState` (one stage)
1. `buildSelectedArc`:
   - Takes the driver's `LibertyPort`, its scene cell, and the path's `prevArc`.
   - Re-resolves the input and output ports by name in the scene cell.
   - Finds the matching arc in that cell via `findMatchingTimingArc`.
   - Sets `ref_arc` and `pvt`.
   - Failure codes include `kMissingSceneOrMinMax`, `kMissingOutputPort`, `kMissingCurrentPortMap`, `kMissingCurrentTimingArc`, `kMissingPrevTimingArc`, `kMissingArcTransition` and `kPathIndexOutOfRange`.
2. `input_slew` comes from `edgeFromSlew` on the input pin's driver vertex. If the pin or vertex is missing it warns (RSZ 3210) and uses 0.
3. `load_cap` comes from `GraphDelayCalc::loadCap`.
4. Table lookup gives `current_model_delay` and `current_slew`; failure gives `kMissingCurrentTimingArc`.
5. `current_delay` is the STA graph arc delay, or the model delay if the graph edge is null.
6. `current_wire_delay` is the next path edge's wire arc delay, if that edge is a wire.
7. `collectOutputSlewMergeArcs`:
   - Walks all in-edges of the driver vertex.
   - Keeps non-check arcs to the same output port and the same output rise/fall, excluding the selected `ref_arc`.
   - Records each arc's input slew and model slew at the current load.
8. `current_model_slew` is the worst (via `min_max->compare`) of the selected and merge-arc model slews.
9. `current_slew` is the STA vertex slew, or the model slew if there is no vertex.

### `collectPathStages`
- With `delay_levels == 0`, the context holds only the target.
- Otherwise it walks backward from `target-1` to `startIndex`, collecting up to N valid fanin stages. Stages that fail to build (for example a port or boundary) are silently skipped.
- It then walks forward, collecting up to N fanout stages. A stage on the target instance itself is skipped.
- `current_total_delay` is the sum of `current_delay` over `path_stages`.
- Fanin stages are not filtered by instance.

### `includeLatchFaninStages` (optional)
- Applies only when the target arc is a latch D→Q and the target is the path start.
- Validates `latchDataPathMatches`: the same scene, min/max, transitions and analysis point, and `q_path->prevPath()` equal to the D path.
- Expands the D-side data path only. It does not walk earlier launch clocks or latches.
- Builds the D-side driver stage and then up to `max(levels,1)-1` more fanin stages.
- Rejects any stage on the target instance, or one with a mismatched scene, min/max, analysis point or transition.
- Sets `path_index=-1` on the stitched stages and prepends them, adjusting `target_stage_index` and `current_total_delay`.
- Every failure is reported as `kMissingPrevTimingArc`.

### `prepareFaninNeighborSlewBias` (when `use_sta_slew_bias`)
- Only the immediate fanin stage (`target_stage_index-1`) gets a model, and only if `target_stage_index > 0`.
- `max_input_cap_delta` is the largest input-pin cap over all `equivCells` of the driver's link cell, minus the current input cap. It skips `dontUse` and non-link cells and is clamped at 0.
- If that delta is 0 or less, it skips.
- The model is built, or fetched from the cache.

### `buildSlewBiasModel`
- Three sample loads: `load`, `load + Δ/2`, `load + Δ`.
- `findStableTableWorstArc` requires the table-worst arc (the worst output slew across the selected arc and merge arcs) to be the same arc at all three loads. Otherwise it returns an invalid model.
- Needs scene parasitics, an ArcDelayCalc and a Pi-model parasitic (`isPiModel`).
- For each sample:
  - Looks up the table slew.
  - Builds a synthetic Pi by `syntheticPiForLoad`: the load delta is split across c1 and c2 in the base ratio, with rpi unchanged.
  - Sets the Pi, runs `ArcDelayCalc::gateDelay`, and reads `drvrSlew`.
  - Stores bias = `sta_slew - table_slew`.
- The result is `valid=true` only if all three samples succeed.
- It is documented as main-thread only, before workers start.

### `estimateWindow` (core of `estimate` and `estimateLoadChange`)
1. Resolve the candidate's scene cell and its input port by name. A missing one gives `kMissingCandidatePort`.
2. Compute `target_input_cap_delta = cand_in_cap - cur_in_cap`.
3. For each stage index:
   - **Stages before the fanin neighbor** (`index < target-1`) are unaffected; they add `current_delay`.
   - **Fanin neighbor** (`target-1`): `load += target_input_cap_delta`.
   - **Target:** `load = max(load + target_load_delta, 0)` and the cell is the candidate. Only the target uses `ArcMatchMode::kRelaxedCandidate`.
   - **Downstream stages** use their current cell.
   - **Input slew:** the first evaluated stage uses its cached `input_slew`. Later ones use `estimateReceiverInputSlew(prev, stage, propagated_output_slew)`, which is `cand_out_slew * stage.input_slew / max(prev.current_slew, 1e-15)`.
   - **Stage delay:** `current_delay + (model_delay - current_model_delay)`, a table-model delta on the STA baseline.
   - **Output slew:** `estimateOutputSlew`.
   - **Failure codes:** a failed lookup returns `kMissingCandidateTimingArc` (target) or `kMissingCurrentTimingArc` (others).
   - **Fanin neighbor deltas:** `fanin_delay_delta` and `fanin_slew_delta = new_slew - current_slew`.
4. `makeEstimate(current_total, candidate_total)` gives `arrival_impr = current - candidate`; `legal = arrival_impr > 0`, otherwise `kEstimateNonImproving`.
5. If still legal, run `applyDualRfCheck`.
6. Always run `applyFaninSideLoss`, even if the estimate is already illegal.

### `estimateOutputSlew`
- **Bias path:** if the stage has a valid bias model and `cell == stage.arc.currentCell()` and the input slew matches `stage.input_slew` (`slewsMatch`: abs tol 1e-15, rel tol 1e-6), the result is `max(table_slew(table_worst_arc) + interpolated_bias(load), 0)`. The bias is clamped to the sampled load range and interpolated piecewise-linearly through low, mid and high.
- **Merged path:** otherwise the worst slew over the selected arc and the merge arcs is calibrated as `current_slew + (model_slew - current_model_slew)`, clamped at 0.
- A merge arc uses the path input slew if it comes from the same input port and edge. Otherwise it uses its own recorded slew.

### `lookupArcDelayAndSlewForArc`
- Gets the scene cell, finds arc sets for the same (from, to) port names, and skips timing checks.
- Exact match: `findMatchingTimingArc`.
- If none and mode is `kRelaxedCandidate`, it scans arcs matching `ArcMatchType::kRelaxed`. It picks the one with the worst output slew via `min_max->compare` and reports that arc's delay. It OR-sets `match_relaxed_out` (never resets it).
- Anything that is not a `GateTableModel` (a `dynamic_cast`) returns false.

### `lookupBufferDelayAndSlew`
- Uses the buffer's single input/output ports and non-check arcs where both edges equal the target's output rise/fall.
- Takes the worst delay across those arcs.

### Fanin side loads
- **`collectFaninSideLoads`:** for each non-clock input pin of the target instance:
  - The selected-arc net uses the exact fanin delta. Its loads exclude the target pin.
  - Other nets use `driveResistance(driver)` as `delay_per_cap`, and are skipped if the drive resistance is ≤ 0 or the driver has no Liberty port.
  - Loads with infinite slack are skipped.
  - Each load is weighted by `sideLoadWeight`: 1 if the pin is in `critical_load_pins` or the set is null, otherwise `off_path_weight`.
- **`applyFaninSideLoss`:**
  - For the selected net, `delay_delta` is the fanin delay growth.
  - Otherwise `delay_delta = delay_per_cap * (cand_cap - cur_cap)`, with `slew_delta = kSideSlewPerDelay (1.4) * delay_delta`.
  - Positive deltas only. Then `delay_delta += kSideSlewDelayFactor (0.3) * max(slew_delta, 0)`.
  - Loss per load is `weight * (min(slack,0) - min(slack - delta, 0))`.
  - The worst `slack_after` is tracked.
- **`chargeSideLoss`:** accumulates `side_paths_evaluated`, adds `loss * fanin_side_loss_weight` to `side_loss`, and sets `legal=false` with `kSideSlackFloorViolation` if `worst_slack_after < sideSlackFloor(arrival_impr)`.
- **`sideSlackFloor(gain) = side_slack_floor - side_floor_margin*max(gain,0)`.**

### Dual rise/fall
- **`collectOppositeRfArcs`:** records target-cell arcs from the same input to the same output with the opposite output transition. Each record holds the input slew, the table delay at the current load, and the opposite-transition slack at the driver.
- **`applyDualRfCheck`:** re-looks up each arc in the candidate cell (relaxed matching) at the target's current load and takes the worst delay increase.
  - If the increase is positive and the slack is finite, it adds to `side_loss` (`oppositeRfSideLoss`) and increments `side_paths_evaluated`.
  - If `slack_after` is below the side slack floor, it sets `legal=false` with `kDualRfNonImproving`.
  - It does not apply `fanin_side_loss_weight`.

## Key data structures
Defined in `OptimizerTypes.hh` and `DelayEstimator.hh`:
- `SelectedArc{scene, min_max, pvt, ref_arc}`, where `ref_arc` is the arc of the current scene cell.
- `DelayStageState`, with `current_*` baselines (table-model and STA-graph pairs), `output_slew_merge_arcs`, `sta_slew_bias` and `opposite_rf_arcs`.
- `EstimatorContext{path_stages, target_stage_index, fanin_side_nets, side_slack_floor, side_floor_margin, fanin_side_loss_weight, opposite_rf_slack, current_total_delay}`.
- `FaninSideNet` and `SideLoad{pin, slack, weight}`.
- `SlewBiasModel{valid, table_worst_arc, input_slew, samples[3]}`.
- `DelayEstimate` and `StageEvaluation`, the optional per-stage trace.
- `DelayEstimatorCache` holds two maps: `max_equiv_input_cap_increase_by_port` (keyed by `LibertyPort*`) and `slew_bias_models`. The model key covers driver pin, ref arc, scene, min/max, current cell, input slew, load, Δload, Pi (c2, r, c1) and the merge-arc list. `Hash` uses `boost::hash_combine`.
- Constants in this file: `kSlewMatchAbsTolerance=1e-15`, `kSlewMatchRelTolerance=1e-6`, `kSideSlewDelayFactor=0.3`, `kSideSlewPerDelay=1.4`. `kMinSlewRatioDenominator` (1e-15) and `kElmoreSlewFactor` (1.39) are in `DelayEstimatorInternal.hh`.

## Callers and callees (verified by reading)
- **Verified callees:**
  - OpenSTA: `Graph`, `GraphDelayCalc`, `ArcDelayCalc`, `Parasitics`, `Sdc`, `Scene`, `PathExpanded`, `TableModel`, `Liberty`.
  - Resizer: `driveResistance`, `equivCells`, `dontUse`, `isLinkCell`.
  - Types and profiling: `OptimizerTypes` (`findMatchingTimingArc`, `matchTimingArc`, `latchDataPath`) and `RepairSetupProfiler` (`event`, `ProfileScope`).
- **Not seen in this file:** `BufferedNet`, `MakeWireParasitics` and `EstimateParasitics.h` are in the graph's callee list, but I saw no use of them here (`WireRC` is only a type).
- **Callers:** from the graph list above. This file defines the shared helpers that `DelayEstimatorBufferTree.cc` consumes.

## Invariants and "do not break"
- **Thread model:** `buildContext` and the cache run on the main thread only. `estimate`, `estimateLoadChange`, `findArcDelay`, `findBufferDelay` and `chargeMovedLoads` must stay pure functions of the context and Liberty data (no STA calls), because workers call them concurrently.
- **Pi-model restore:** `buildSlewBiasModel` mutates the live Pi model. It must restore it (`PiModelRestore`) and must not run during concurrent STA updates or worker scoring. The cache key reads the live Pi, so stale Pi data would make cache hits wrong.
- **Context shape:** `path_stages` always has the target, `target_stage_index` is valid, and `current_total_delay` is consistent with the stages. Latch-stitched stages use `path_index=-1`.
- **Scene cells:** timing lookups use `sceneCell(scene, min_max)`. Resizer queries (`equivCells`, `dontUse`) use the link cell from the driver instance (see `maxTargetInputCapDelta`). Do not mix the two.
- **Relaxed arc matching:** only the target candidate and the dual-RF check use it. Current-cell and downstream stages use exact matching.
- **Determinism:**
  - Ordering follows STA edge and pin iterator order.
  - `drivers->begin()` picks the first driver of a net.
  - Float comparisons use `min_max->compare`.
  - The cache is keyed by exact float values.
- **Cache lifetime:** `DelayEstimatorCache::clear()` is expected once per policy run. It assumes the equivalent-cell envelope is fixed within a run.
- **Rollback and odb:** this file does no journaling, rollback or odb edits. Legality here is estimator legality only (`dont_touch` and placement legality are handled by candidates and generators). The only dont-use filtering is in the cap-range scan.

## Weak spots / assumptions an algorithm designer should know
- **No interconnect slew degradation:** slew is propagated as `out_slew * (recv_in/drv_out)` using the pre-ECO ratio. That ratio is assumed constant, and it blows up if the current driver slew is near 0 (floored at 1e-15).
- **Wire delay held constant:** `current_wire_delay` is recorded but not re-estimated in `estimateWindow`. Wire delay changes from a new driver or load are ignored.
- **Lumped load:** load cap changes are applied additively to the Pi model's total cap. Cap changes on the fanin neighbor assume only the target's selected input pin changes. Other input pins of the target are handled only in the side-loss model, where `delay_per_cap` is a crude drive-resistance slope.
- **Slew bias coverage:** it is applied only to the immediate fanin stage, for the current cell only, and with the same input slew only. It needs a stable table-worst arc across three loads and a Pi-model parasitic.
- **Silent skips:** stages that fail to build are silently dropped from the window, so fanin/fanout windows may have fewer than N stages and the window can span non-adjacent stages. Fanout stages from the same instance as the target are skipped.
- **Table-only model:** only `GateTableModel` (NLDM) is supported. CCS or other models fail the lookup and make the candidate infeasible.
- **Non-improving candidates:** `legal` means `arrival_impr > 0` (strictly) from the path delay, before side losses. `side_loss` is reported separately for the caller to subtract. Only the side-slack-floor and dual-RF checks force `legal=false`.
- **Dual-RF `delay_delta`:** it uses table-model deltas at the current load only. It does not include the candidate's changed fanin loading, and it skips arcs the candidate cell lacks.
- **Heuristic constants:** 0.3 and 1.4 (side slew), the 1e-6 slew-match tolerance, and 3 sample points for the bias are not tuned in this file. `side_floor_margin`, `fanin_side_loss_weight` and `off_path_weight` come from the caller's policy.
- **Min/max `compare` convention:** "worst" selection depends on `MinMax::compare`. It is correct for setup (max) analysis, but hold (min) behaviour is untested here.
- **Cap-range scan cost:** `maxTargetInputCapDelta` scans all equivalent cells per call, hence the per-port cache. The cache key includes raw floats, so small parasitic changes cause misses.