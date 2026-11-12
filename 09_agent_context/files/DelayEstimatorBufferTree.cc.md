# DelayEstimatorBufferTree.cc

## Purpose
This file times a `RebufferMt` buffer-tree plan with Liberty table lookups and Elmore wire delays, with no STA call. It estimates the arrival gain along the target path (driver → tree → downstream path stages). It also estimates the delay change on each "side path", meaning another load pin the tree rewires. The result is a `DelayEstimate` that ranks candidate trees. The header comment says STA times each batch before a tree is kept, so a wrong estimate costs QoR, not correctness.

## Public entry points
Only one symbol is exported. Everything else is in an anonymous namespace.

```cpp
static DelayEstimate DelayEstimator::estimateBufferTreeWithSidePaths(
    const EstimatorContext& context,
    const RebufferTreePlan& plan,
    const std::vector<BufferTreeSidePathContext>& side_contexts,
    std::vector<StageEvaluation>* trace = nullptr,
    std::vector<BufferTreeSidePathEvaluation>* side_evaluations = nullptr);
```
- **Purpose:** returns the target-path arrival improvement, minus the weighted negative-slack loss of the side paths. It marks the estimate illegal if any side path falls below the side slack floor.
- **Caller:** only `RebufferMtCandidate::estimateTree` (`move/RebufferMtCandidate.cc:90-98`). That is called from the candidate's estimate step (`RebufferMtCandidate.cc:59`). The result goes through `raw_score_ = arrival_impr - side_loss` and a `min_score_` check.
- **Reporting:** `trace` and `side_evaluations` are for the accuracy report. The report code is probably `DelayEstimatorReporter.cc`; I did not open it.
- **Declared at:** `DelayEstimator.hh:265`.

## Inputs and outputs, precisely
**Reads**, all as precomputed snapshots (no live STA or odb access in this file):
- **`EstimatorContext`:**
  - `path_stages`, `target_stage_index`, `target()`.
  - `current_total_delay`.
  - `sideSlackFloor(gain)`, which is `side_slack_floor - side_floor_margin * max(gain, 0)`.
- **`DelayStageState`** fields used:
  - `arc` (`SelectedArc`: scene, min_max, pvt, ref_arc).
  - `input_slew`, `load_cap`, `current_delay`, `current_model_delay`, `current_slew`, `current_wire_delay`, `path_index`.
- **`RebufferTreePlan`:**
  - `tree_input_cap`.
  - `targetPath()`, which is dereferenced without a null check.
  - `loadPath(pin)`, also dereferenced unchecked.
  - Each `BufferTreeLoadPath` holds stages with `type` (wire/via/buffer), `buffer_cell`, `wire_rc`, `downstream_cap` and `drives_distributed_load`.
- **`BufferTreeSidePathContext`:** `load_pin`, `current_driver_to_load_delay`, `current_slack`, `weight`.
- **Liberty tables:** read through `estimator_detail::lookupArcDelayAndSlew` and `lookupBufferDelayAndSlew` (in `DelayEstimator.cc`). The buffer lookup uses `cell->sceneCell(scene, min_max)`, `bufferPorts`, and `gateDelayAndSlewFromTableModel`.

**Writes:** only the output parameters.
- **Returns** a `DelayEstimate`:
  - `legal`, `candidate_delay`, `arrival_impr`.
  - `side_paths_evaluated`, `side_loss`.
  - `reason`: `kEstimateLegal`, `kEstimateNonImproving`, `kInvalidBufferInsertion`, `kMissingCurrentTimingArc`, `kMissingBufferTimingArc`, `kSideSlackFloorViolation`.
- **`trace`:** cleared, then filled with one `StageEvaluation` per pre-target, driver, tree and post-target stage.
- **`side_evaluations`:** cleared and reserved, then one entry per side path.
- **Not touched:** odb, STA, parasitics, the journal, and the Resizer.

## Algorithm / control flow

### 1. Entry (`estimateBufferTreeWithSidePaths`)
1. Clear the outputs and create an empty `BranchTimingCacheNode` (the root of the cache).
2. Run `estimateBufferTreeWindow`.
3. If its reason is neither `kEstimateLegal` nor `kEstimateNonImproving`, return it immediately and skip the side paths. A non-improving target (`arrival_impr <= 0`) still proceeds to the side paths.
4. For each side context:
   - Call `estimateSidePathWindow`.
   - `side_impr` is the estimate's `arrival_impr`, or `-inf` if the estimate failed.
   - `slack_after = current_slack + side_impr`.
   - Increment `side_paths_evaluated`.
   - If the side estimate failed, set `legal=false` with the side's reason.
   - Otherwise add `weight * (min(current_slack, 0) - min(slack_after, 0))` to `side_loss`. Only slack in the negative region counts as loss, so a side path that stays positive costs nothing.
   - If `slack_after < context.sideSlackFloor(estimate.arrival_impr)`, set `legal=false` and `kSideSlackFloorViolation`.
   - Loop on after a failure; later sides can overwrite the reason. This is deliberate, so every side is still evaluated and appears in `side_evaluations`.
5. Return the estimate. `side_loss` is not subtracted here; `RebufferMtCandidate` does that.

### 2. Target window (`estimateBufferTreeWindow`)
1. Reject with `kInvalidBufferInsertion` if `tree_input_cap` is not finite.
2. Take `current_total_delay = context.current_total_delay + target.current_wire_delay`.
3. Replay the stages before the target at `current_delay`, unchanged.
4. Time the driver plus the target load path with `estimateBranchTiming`, using `kBufferTreeTargetEffectiveLoadCapFactor`.
5. For each stage after the target:
   - **Input slew:** the first one takes the tree's `load_slew` directly. Later ones use `estimateReceiverInputSlew(prev, stage, propagated_slew)`, which scales by the existing receiver/driver slew ratio.
   - **Stage delay:**
     - Look up the model delay with `lookupArcDelayAndSlew`.
     - Compute `stage.current_delay + (model_delay - stage.current_model_delay)`, which adds the table-model delta to the STA baseline.
     - Pass the result through `boundBufferTreeDownstreamStageDelay`.
   - **Output slew:** `estimateOutputSlew(...)`.
6. Return `makeEstimate(current_total_delay, candidate_total_delay)`. It is legal only if `arrival_impr > 0`.

### 3. Side path window (`estimateSidePathWindow`)
- Time the side load's path with `estimateBranchTiming` and `kBufferTreeSideEffectiveLoadCapFactor`.
- Compare the result to `target.current_delay + side.current_driver_to_load_delay` via `makeEstimate`.
- The side window ends at the load pin; there is no downstream propagation.

### 4. Branch timing (`estimateBranchTiming`, `branchDriverTiming`, `treeStageTiming`)
- **Driver:**
  - Delay comes from the plain table lookup at `plan.tree_input_cap`.
  - The propagated slew is not the table slew. It is `loadRatioSlewFloor`, which is `current_slew * clamp(tree_input_cap / stage.load_cap, 0, 1)^0.85`, or 0 if any input is non-positive.
- **Wire and via stages:**
  - `bufferTreeWireDelay` is raw Elmore (`res * (downstream_cap + 0.5 * wire.cap)`). The raw value is scaled by 0.78 if it is at least 20 ps; below 20 ps it is left unscaled.
  - Output slew is `hypot(input_slew, factor * wire_delay)`, where factor is 1.35 below 20 ps and 1.39 (`kElmoreSlewFactor`) otherwise.
- **Buffer stages:**
  - Effective load is `downstream_cap * f`, where f is the path factor (0.675 target, 0.875 side) if `drives_distributed_load`, else 0.60 (direct load).
  - The delay and slew come from the buffer lookup on that load, using the arc whose input and output transitions both equal the target's output transition.
  - A missing buffer arc gives `kMissingBufferTimingArc`.
- **Trie cache:** branch prefixes are memoized per plan in a `BranchTimingCacheNode` trie. It is a dummy root plus children keyed by `sameBufferTreePathStage`, which compares type, `downstream_cap`, `drives_distributed_load`, `buffer_cell`, and, for wire and via stages, the `WireRC`. The driver is cached at the root. Cache hits also append the cached trace entry, so traces stay complete.

### Constants
| Constant | Value |
|---|---|
| Target effective-load factor | 0.675 |
| Side effective-load factor | 0.875 |
| Direct-load factor | 0.60 |
| Load-ratio slew-floor exponent | 0.85 |
| Wire-delay scale threshold | 20 ps |
| Wire-delay scale | 0.78 |
| Short-wire slew factor | 1.35 |
| Elmore slew factor | 1.39 |

### Downstream bound (`boundBufferTreeDownstreamStageDelay`)
- Result is `max(stage_delay, current_delay * r)`, where `r = max(0.5, 0.45 + 0.35 * sqrt(clamp(input_slew / current_input_slew, 0, 1)))`.
- `r` reaches 0.8 when the input slew is unchanged and falls to 0.5 as it sharpens.
- The comment says this limits credit given to slews that come from the approximate tree model.

## Key data structures
- **`BranchTiming`:** `{legal, delay, load_slew, reason}`. Cumulative delay and slew at a point in the tree.
- **`BranchTimingCacheNode`:** trie node holding `valid`, `stage`, `prefix` (`BranchTiming`), `trace_entry`, and `children`. It is a `std::vector` of nodes, so child pointers are invalidated by `push_back`. The code re-points `parent` after each push, which is correct, but it keeps no pointer across one.
- **Reused types:**
  - `RebufferTreePlan`, `BufferTreeLoadPath`, `BufferTreePathStage` (from `Rebuffer.hh`).
  - `EstimatorContext`, `DelayStageState`, `DelayEstimate`, `WireRC`, `FailReason` (from `OptimizerTypes.hh`).
  - `StageEvaluation`, `BufferTreeSidePathContext`, `BufferTreeSidePathEvaluation` (from `DelayEstimator.hh`).

## Callers and callees (verified by reading)
- **Called by:** `RebufferMtCandidate::estimateTree`, and only that. The "called by unknown" in the graph is resolved by grep. There are no other call sites.
- **Calls (via `DelayEstimatorInternal.hh`, defined in `DelayEstimator.cc`):**
  - `lookupArcDelayAndSlew`, `lookupBufferDelayAndSlew`.
  - `estimateOutputSlew`, `estimateReceiverInputSlew`.
  - `wireElmoreDelay`, `makeEstimate`.
- **Other dependencies:**
  - `SelectedArc::currentCell()` (`OptimizerTypes.cc`).
  - `RebufferTreePlan::targetPath()` and `loadPath()` (`Rebuffer.cc`).
  - `EstimatorContext::sideSlackFloor` (inline in `OptimizerTypes.hh`).
  - STA headers: `LibertyCell::sceneCell`, `TimingArc`, `MinMax::compare`, and others.
- **Graph edges to not trust:** the graph lists `Graph.cc`, `Path.cc`, `PathExpanded.cc`, `Scene.cc`, `Delay.cc` and `EstimateParasitics.h`. These come from includes (`EstimateParasitics.h` is not even included here). This file makes no direct graph or path traversal.

## Invariants and "do not break"
- **No side effects:**
  - The functions are pure over their inputs and safe on worker threads. `DelayStageState` is documented as a prepared snapshot, and workers do not touch STA analysis state.
  - Keep it that way: do not add STA graph or parasitics reads here.
- **No journaling or rollback:** nothing is mutated, so there is nothing to undo. The plan (`plan.tree`) is applied elsewhere, after STA checks the batch.
- **Determinism:**
  - There is no randomness, and the cache is a pure memo, so results depend only on inputs and stage order.
  - Cache keys omit the effective-load factor (the file says so). A prefix the target path shares with a side path therefore reuses whichever was computed first. Since the target is always evaluated first, shared prefixes always use the target factor 0.675 for buffers. Reordering the evaluation changes numbers.
- **`dont_touch`, legality, parasitics:** not checked here. Eligibility and placement legality are upstream (`Rebuffer` planning and candidate generation). "Legal" in this file means only a finite estimate that improves arrival and keeps side slack above the floor.
- **Trace consistency:** `trace` order is pre-target stages, driver, tree stages along the target path, then post-target stages. The accuracy report depends on that. Cache hits must keep pushing entries.
- **Calibration:** the constants were fitted on the Nangate45 `report_delay_estimator_rebuffer_*` tests, so change them only with that report.

## Weak spots / assumptions an algorithm designer should know
- **Hard-coded calibration:**
  - The constants are Nangate45 fits. The source says the target factor was checked on another platform and raised estimate error in some Nangate45 cases.
  - Effective cap factors below 1 mean the estimator systematically under-loads buffers relative to a lumped model.
- **Cache key vs. factor:** side-path buffers that share a prefix with the target reuse the target-factor timing instead of 0.875. This slightly misprices side delay.
- **Driver slew is a heuristic:** `loadRatioSlewFloor` is a floor that falls with the load ratio. The table slew is discarded, and the result can be 0 if `stage.current_slew` or `stage.load_cap` is non-positive. That makes downstream slews and delays optimistic.
- **Side windows stop at the load pin:** the side estimate ignores any further slew effect past the load, and receiver pin cap changes. `current_driver_to_load_delay` is assumed to include wire delay.
- **Side-slack gating uses the target gain:** the floor is `side_slack_floor - margin * max(arrival_impr, 0)`. For a non-improving target (`arrival_impr <= 0`), the floor is not lowered. The `weight` is ignored by the floor and used only for `side_loss`.
- **Unchecked pointers:** `plan.targetPath()` and `plan.loadPath(side.load_pin)` are dereferenced directly, so the caller must guarantee they are non-null. The comments assert it.
- **Reason overwriting:** with several failing side paths, the final reason is the last failure; the first is not kept.
- **`kEstimateNonImproving` still gets side evaluation:** wasted work if the target does not improve. It is kept so the accuracy report sees the sides.
- **Stage delay uses an additive baseline:** post-target stages are `current_delay + (model_new - model_current)`, so STA's CCS or waveform effects are carried only in the baseline. The 0.5-0.8 floor can mask real gains from a much sharper slew.
- **Buffer arc selection:** `lookupBufferDelayAndSlew` takes the worst delay, using `min_max->compare`, over arcs with the target output transition on both the input and output sides. It assumes a non-inverting buffer and an input edge equal to the target output edge, and it ignores the buffer's other timing arc sets.
- **Dual-RF not modeled here:** `opposite_rf_slack` and `fanin_side_nets` in the context are unused by this file, so only the tree's own path is checked.