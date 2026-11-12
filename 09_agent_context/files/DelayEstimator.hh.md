# DelayEstimator.hh

## Purpose
This header is the delay model for the multithreaded (MT) optimizer moves: size-up, VT swap, split-load, size-down-fanout and rebuffer. On the main thread, `buildContext()` snapshots a path-local window of STA timing into an `EstimatorContext`. Worker threads then score candidates from that snapshot and the Liberty tables alone, without touching STA. The score is the table-model change in arrival time, plus a penalty for slack lost on other paths that share the target's fanin nets. It also holds `DelayEstimatorCache`, which reuses preparation work across targets in one policy run.

## Public entry points
- `static bool DelayEstimator::findArcDelay(const SelectedArc&, float input_slew, float load_cap, const sta::LibertyCell*, float& delay)`
  - Gives the Liberty table delay of one arc.
  - It uses exact arc matching only.
  - Caller: `move/SplitLoadMtCandidate.cc`.
- `static std::optional<EstimatorContext> buildContext(Resizer&, const Target&, int delay_levels, FailReason*, bool use_sta_slew_bias, bool include_latch_fanin, DelayEstimatorCache*, const FaninSideLoadOptions*, bool dual_rf_eval)`
  - This is the main-thread-only preparation step.
  - Callers: `OptimizationPolicy::buildPolicyContext` (`policy/OptimizationPolicy.cc:263`) and `SequentialTimingEstimator.cc:227`, which uses the lower-level overload.
- `static std::optional<EstimatorContext> buildContext(Resizer&, sta::Instance*, sta::Pin* driver_pin, const sta::PathExpanded&, int path_index, const sta::Scene*, const sta::MinMax*, int delay_levels, ...same trailing args)`
  - This is the lower-level overload. The `Target` overload unpacks `target.endpoint_path` into it.
- `static DelayEstimate estimate(const EstimatorContext&, const sta::LibertyCell* candidate_cell, std::vector<StageEvaluation>* trace=nullptr)`
  - Scores swapping the target cell for `candidate_cell`.
  - Callers: `SizeUpMtCandidate.cc:39` and `VtSwapMtCandidate.cc:59`.
  - `DelayEstimatorReporter.cc` also calls it.
- `static DelayEstimate estimateLoadChange(const EstimatorContext&, float target_load_delta)`
  - Scores a change in the target's load cap while the target keeps its cell.
  - Callers: `SplitLoadMtCandidate.cc:45` and `SizeDownFanoutMtCandidate.cc:37`.
- `static bool findBufferDelay(const EstimatorContext&, const sta::LibertyCell* buffer, float input_slew, float load_cap, float& delay)`
  - Gives the delay of a buffer on the target's output transition.
  - Caller: `SplitLoadMtCandidate.cc:64`.
- `static void chargeMovedLoads(const EstimatorContext&, const std::vector<SideLoad>&, float delay_delta, DelayEstimate&)`
  - Charges the loads a split moves to the new driver.
  - Caller: `SplitLoadMtCandidate.cc:76`.
- `static DelayEstimate estimateBufferTreeWithSidePaths(const EstimatorContext&, const RebufferTreePlan&, const std::vector<BufferTreeSidePathContext>&, trace*, side_evaluations*)`
  - Defined in `DelayEstimatorBufferTree.cc:477`.
  - Caller: `RebufferMtCandidate.cc:97`.
- `float oppositeRfSideLoss(float opposite_slack, float delay_delta)`: free function for the dual-RF check.
- `inline float sideLoadWeight(pin, critical_load_pins, off_path_weight)`: returns 1 for pins in the critical set (or when the set is null), otherwise `off_path_weight`. Callers: `SplitLoadMtGenerator.cc:125` and `RebufferMtGenerator.cc:131`.
- `class DelayEstimatorCache`
  - `clear()`.
  - `maxEquivalentInputCapIncrease(Resizer&, const DelayStageState&)`.
  - `getOrSampleSlewBias(Resizer&, const DelayStageState&, float max_load_delta)`.
  - It is held as `OptimizationPolicy::estimator_cache_` (`mutable`).

## Inputs and outputs, precisely
**`buildContext` reads**
- The expanded worst path (`PathExpanded`), scene, min/max, and the target's driver pin and instance.
- Per-stage `inputSlewOrZero`, STA graph arc delay and slew, and path wire delay.
- Liberty arcs and tables.
- Driver vertex edges and the opposite-transition slack.
- Slacks of fanin-net load vertices (`sta->slack(vertex, min_max)`).
- `resizer.driveResistance(driver)`, and `resizer.equivCells()` for the cap envelope.
- The reduced Pi parasitic, in the slew-bias case.
- Clock status (`sta->isClock`), dont-use and link-cell status.

**`buildContext` mutates**
- Only when `use_sta_slew_bias` is set. It temporarily calls `parasitics->setPiModel(...)` on the fanin driver's live Pi model and calls `arcDelayCalc()->gateDelay` / `finishDrvrPin`. A `PiModelRestore` guard restores the model afterwards.
- This is documented as single-threaded only.

**`buildContext` returns**
- `nullopt` plus a `FailReason`, or an `EstimatorContext`.

**`estimate*` functions**
- They read only the context and Liberty tables, and mutate nothing. The one exception is `chargeMovedLoads`, which updates the `DelayEstimate&` you pass in.
- They return a `DelayEstimate`: `legal`, `candidate_delay`, `arrival_impr`, `side_paths_evaluated`, `side_loss` and `reason`.
- Callers later turn `arrival_impr - side_loss` into a policy-level score. The score formula is not in this file.

**Context fields the caller sets after `buildContext`**
`OptimizationPolicy::buildPolicyContext` sets these when `fanin_side_loss`, `dual_rf_eval` or `rebuffer_mt_side_loads` is on:
- `side_slack_floor`, from `worstSlack(maxAnalysisMode())`.
- `side_floor_margin`.
- `fanin_side_loss_weight`.

If the caller never sets them, the floor stays at `-inf` and no side path can violate it.

## Algorithm / control flow
**`buildContext`**
1. Build the target `DelayStageState`. This must succeed; failures map to `FailReason` values.
2. `collectPathStages` adds up to `delay_levels` stages on each side of the target. Negative levels are clamped to 0. The context always has at least the target stage.
3. If `include_latch_fanin` is set, `includeLatchFaninStages` stitches in the D-side driver of a latch at the path start, with `path_index -1`. If that fails, `buildContext` fails.
4. If `use_sta_slew_bias` is set, `prepareFaninNeighborSlewBias` samples only the immediate fanin driver (`target_stage_index > 0`).
   - `max_load_delta` is the largest input-cap increase over all non-dont-use, link-cell equivalent cells.
   - It takes 3 sample loads: `load`, `load + Δ/2` and `load + Δ`.
   - It needs a stable table-worst arc at all three loads, and a valid Pi model.
   - Each sample records the gap between the STA slew and the table slew.
   - Anything unstable or missing gives `valid=false` and the model is not used.
5. If `fanin_side_loads` is non-null, `collectFaninSideLoads` records every input net of the target.
   - For each net it records the other load pins and their slack.
   - Infinite-slack loads are skipped.
   - Each load gets a `sideLoadWeight`.
   - A net off the selected arc takes `delay_per_cap = driveResistance(driver)`. If that value is ≤ 0 or the driver has no Liberty port, the net is skipped.
6. If `dual_rf_eval` is set, `collectOppositeRfArcs` finds target arcs from the same input to the same output on the opposite output transition. It also records their table delay and the driver's opposite-transition slack.

**`estimateWindow`** (shared by `estimate` and `estimateLoadChange`)
1. Find the candidate's scene cell and input port. If either is missing, return `kMissingCandidatePort`.
2. Compute `target_input_cap_delta`.
3. Walk the stages.
   - Stages before `target-1` are unchanged and reuse `current_delay`.
   - The fanin neighbour gets `load_cap += target_input_cap_delta`.
   - The target uses the candidate cell and `max(load + target_load_delta, 0)`.
   - Downstream stages keep their current cell.
   - Slew is propagated stage to stage. `estimateReceiverInputSlew` scales the new driver slew by the current receiver/driver slew ratio, using `kMinSlewRatioDenominator` = 1e-15.
4. Per stage, the delay is `current_delay + (table_delay - current_model_delay)`. This keeps the STA baseline and applies a model delta on top.
5. Output slew: if the cell is unchanged, the input slew matches and `sta_slew_bias.valid` holds, use the table slew plus the interpolated STA bias. Otherwise take the worst slew over `output_slew_merge_arcs` (merged slew), then calibrate to `current_slew + (model - current_model_slew)`, floored at 0.
6. Target-stage arc lookup uses `kRelaxedCandidate` matching: same port name and rise/fall when no exact arc is found. All other stages use `kExact`. A missing arc gives `kMissingCandidateTimingArc` for the target and `kMissingCurrentTimingArc` elsewhere.
7. `makeEstimate`: `arrival_impr = current_total_delay - candidate_total_delay`. `legal` means `arrival_impr > 0`, otherwise `kEstimateNonImproving`.
8. If legal, `applyDualRfCheck` runs.
   - It takes the worst increase in opposite-transition delay over the opposite-RF arcs.
   - `side_loss += oppositeRfSideLoss`.
   - It sets `kDualRfNonImproving` if the slack after falls below `sideSlackFloor(arrival_impr)`.
9. `applyFaninSideLoss` runs.
   - On the selected net it uses the window's exact fanin delay delta. Otherwise it uses `delay_per_cap * Δ input_cap` and a slew delta of `kSideSlewPerDelay` (1.4) × that delay.
   - It adds `kSideSlewDelayFactor` (0.3) × the slew growth to the delay delta.
   - Deltas ≤ 0 are skipped.
   - Each load adds `weight * (min(slack,0) - min(slack_after,0))` to the loss. This counts only slack below zero.
   - `chargeSideLoss` adds `loss * fanin_side_loss_weight` to `side_loss`.
   - If the worst slack after falls below `sideSlackFloor(arrival_impr)`, it sets `legal=false` with `kSideSlackFloorViolation`.

**`sideSlackFloor(gain) = side_slack_floor - side_floor_margin * max(gain, 0)`**. A side path may therefore drop below the global worst slack by at most `side_floor_margin` times the candidate's gain.

**`chargeMovedLoads`** applies the same loss and floor logic to loads moved by a split.

**`estimateBufferTreeWithSidePaths`**
1. Estimate the target path through the tree (`estimateBufferTreeWindow`). If that estimate is unavailable, return it as is.
2. For each side context, estimate the side path (`estimateSidePathWindow`).
3. Compute `slack_after = current_slack + side_arrival_impr`.
4. Add `weight * negative-region loss` to `side_loss`.
5. A side path below the floor, or one with no available estimate, makes the plan illegal.
6. Side effective load uses `kBufferTreeSideEffectiveLoadCapFactor`.

## Key data structures
Defined in `OptimizerTypes.hh` unless stated.
- `EstimatorContext`:
  - `path_stages` and `target_stage_index`.
  - `fanin_side_nets`.
  - `side_slack_floor`, `side_floor_margin` and `fanin_side_loss_weight`.
  - `opposite_rf_slack`.
  - `current_total_delay`, which is cached.
- `DelayStageState`:
  - The selected arc, driver pin, input slew and load cap.
  - Baseline model and STA delays and slews.
  - `output_slew_merge_arcs`.
  - `sta_slew_bias`.
  - `opposite_rf_arcs`.
  - `path_index`.
- `SelectedArc` holds scene, min/max, pvt and `ref_arc`.
- `SlewBiasModel` holds three `SlewBiasSample`s.
- `SideLoad` and `FaninSideNet`.
- `DelayEstimate`.
- `FaninSideLoadOptions`.
- `StageEvaluation`, `BufferTreeSidePathContext` and `BufferTreeSidePathEvaluation` (this header).
- `DelayEstimatorCache::SlewBiasModelKey`:
  - Driver pin, arc, scene, min/max, cell, input slew, load cap, `max_load_delta`, Pi (c2, r, c1) and merge arcs.
  - It has its own hash.
  - Maps: `max_equiv_input_cap_increase_by_port`, keyed by `LibertyPort*`, and `slew_bias_models`.
- `DelayEstimatorInternal.hh` shares helpers with the buffer-tree file only: `lookupArcDelayAndSlew`, `estimateOutputSlew`, `makeEstimate`, `wireElmoreDelay` and `kElmoreSlewFactor` = 1.39.

## Callers and callees (verified by reading)
- **Callers:** `policy/OptimizationPolicy.{cc,hh}`, `SequentialTimingEstimator.cc`, `move/{SizeUp,VtSwap,SplitLoad,SizeDownFanout,Rebuffer}Mt{Candidate,Generator}.cc`, and `DelayEstimatorReporter.cc`.
- **Callees:**
  - STA: `graph`, `slack`, `worstSlack` (the last is called by the policy), `graphDelayCalc()->edgeFromSlew`, `arcDelayCalc()->gateDelay`, parasitics `piModel` / `setPiModel`.
  - Resizer: `driveResistance`, `equivCells`, `dontUse`, `isLinkCell`, `maxAnalysisMode`.
  - Liberty table lookup via `lookupArcDelayAndSlew`.
  - Profiling and logging: `ProfileScope`, `RepairSetupProfiler::event` and `debugPrint` under the "delay_estimator" group.

## Invariants and "do not break"
- **Thread safety**
  - `buildContext`, `getOrSampleSlewBias` and `maxEquivalentInputCapIncrease` must run on the main thread only. Slew-bias sampling mutates live Pi parasitics and the delay-calc state.
  - `estimate*`, `findBufferDelay`, `findArcDelay` and `chargeMovedLoads` must not touch STA.
  - `DelayEstimatorCache` is not thread-safe, so the policy must call it from the prepare stage only.
- **Pi restore:** `PiModelRestore` must run on every exit path, or parasitics are left corrupted.
- **Cache lifetime:** call `DelayEstimatorCache::clear()` at the start of each policy run. The key covers electrical state, but a netlist change would leave stale `Pin*` / `TimingArc*` entries.
- **No journaling:** this file does no netlist edits, so there is nothing to roll back. All mutations are made by the moves that use it.
- **Determinism:** it relies on `unordered_*` containers only for cache lookups, and on iteration order of STA iterators. `drivers->begin()` picks an arbitrary driver on multi-driver nets.
- **dont_touch:** it is not checked here. Only `dontUse` is checked, for the cap envelope. The generators are responsible for dont_touch and legality.
- **Context validity:** the context is a snapshot. Any netlist or parasitic change after `buildContext` makes it stale.
- **Unset side-floor fields:** if the caller forgets to set `side_slack_floor` after `buildContext`, the check is silently off.
- **Arc matching:** keep `kRelaxedCandidate` limited to the target candidate.

## Weak spots / assumptions an algorithm designer should know
- **Interconnect slew:** the model approximates interconnect slew degradation with the current receiver/driver ratio, and ignores wire RC delay changes. The source calls this a speed/accuracy trade-off.
- **Window size:** only the stages within `delay_levels` of the target are re-scored, and the load cap of downstream stages never changes. Effects beyond the window are invisible.
- **Slew bias coverage:** it applies only to the immediate fanin driver, only when the cell and input slew are unchanged, and only if a stable table-worst arc exists. It is skipped silently (debug level 3) otherwise.
- **Side-load approximation:**
  - Off-path nets use a linear `delay_per_cap` (the driver's drive resistance).
  - The 1.4 and 0.3 constants are heuristic.
  - Only increases in fanin delay are charged. A cell that lowers input cap gets no credit for helping siblings.
  - Only slack below zero is counted, as a TNS proxy.
  - `weight` depends on whether the pin lies on a worst path of a violating endpoint.
- **Floor choice:** the global worst slack at prepare time is a coarse bound. Other moves accepted in the same run can invalidate it.
- **Dual RF:** the check applies only if the primary estimate is legal. It uses relaxed arc matching and checks only the worst-delta arc.
- **Legality:** `legal` is strictly `arrival_impr > 0`. A move that is neutral on the path but helps elsewhere is rejected.
- **Wide fanin nets:** nets with many loads cost O(loads) per candidate.
- **Cache key:** it includes floats compared exactly, so near-identical states miss the cache.
- **Skipped nets:** fanin nets whose driver has no Liberty port or a zero drive resistance are skipped, so those loads pay nothing.
- **Latch fanin:** `include_latch_fanin` fails the whole context if the D-side driver cannot be stitched in.