Reading is done. I'm writing the card now.

# DelayEstimatorInternal.hh

## Purpose
This is a private header shared by two translation units: `DelayEstimator.cc` and `DelayEstimatorBufferTree.cc`. It declares the small table-model helpers that both estimators use, in namespace `rsz::estimator_detail`. The helpers look up Liberty arc delay and slew, calibrate output slew against STA's baseline, scale receiver input slew across a net, compute lumped-RC Elmore wire delay, and build a `DelayEstimate`. The header says it is "Not an API for other files". Everything else in the estimator, including the public `DelayEstimator` class, lives in `DelayEstimator.hh`.

## Public entry points
All functions are in `rsz::estimator_detail`. The header includes only `OptimizerTypes.hh` and forward-declares `sta::LibertyCell`.

- **`inline constexpr float kMinSlewRatioDenominator = 1.0e-15f`** is the floor for a slew used as a divisor. It guards the division in `estimateReceiverInputSlew`. The buffer-tree file uses it to guard `boundBufferTreeDownstreamStageDelay`.
- **`inline constexpr float kElmoreSlewFactor = 1.39f`** is the Elmore delay-to-slew factor. It is used only in `DelayEstimatorBufferTree.cc` (`wireOutputSlewFromDelay`, for wire delay at or above `kBufferTreeWireDelayScaleThreshold`).
- **`bool lookupArcDelayAndSlew(const SelectedArc&, float input_slew, float load_cap, const sta::LibertyCell* cell, float& delay, float& output_slew, ArcMatchMode = kExact, bool* match_relaxed_out = nullptr)`**
  - It evaluates the Liberty table model of `cell` on the arc matching `arc.ref_arc`, using the scene, min/max and PVT carried in `arc`.
  - It is a thin wrapper over the anonymous-namespace `lookupArcDelayAndSlewForArc` (`DelayEstimator.cc:291`).
  - Callers are `DelayEstimator.cc` (the window walk near line 1996, and `findArcDelay` at line 2058) and `DelayEstimatorBufferTree.cc` (lines 198 and 419).
- **`bool lookupBufferDelayAndSlew(const DelayStageState& target_stage, const LibertyCell* buffer_cell, float input_slew, float load_cap, float& delay, float& output_slew)`**
  - It gives the delay and slew of an inserted buffer on the target's output transition.
  - Callers are `DelayEstimator::findBufferDelay` (`DelayEstimator.cc:2203`) and `DelayEstimatorBufferTree.cc:276`.
- **`float estimateOutputSlew(const DelayStageState& stage, const LibertyCell* cell, float path_input_slew, float load_cap, float selected_output_slew, ArcMatchMode merge_arc_mode = kExact, bool* slew_relaxed_out = nullptr)`**
  - It returns the calibrated post-ECO driver output slew.
  - Callers are `DelayEstimator.cc:2011` and `DelayEstimatorBufferTree.cc:433`.
- **`float estimateReceiverInputSlew(const DelayStageState& driver_stage, const DelayStageState& receiver_stage, float candidate_driver_output_slew)`**
  - It returns the receiver input slew for a new driver output slew.
  - Callers are `DelayEstimator.cc:1980` and `DelayEstimatorBufferTree.cc:414`.
- **`float wireElmoreDelay(const WireRC&, float load_cap)`** is called by `bufferTreeWireDelay` (`DelayEstimatorBufferTree.cc:117`).
- **`DelayEstimate makeEstimate(float current_delay, float candidate_delay)`** is called at `DelayEstimator.cc:2036` and `DelayEstimatorBufferTree.cc:447` and `:472`.

## Inputs and outputs, precisely
**Reads**
- Liberty data only, through the scene and PVT in `SelectedArc`:
  - `LibertyCell::sceneCell(scene, min_max)`
  - the timing arc sets of the cell
  - NLDM/CCS tables, through `gateDelayAndSlewFromTableModel` (`DelayEstimator.cc:72`)
- `DelayStageState` snapshot fields, which are prepared earlier on the main thread:
  - `current_slew`, `current_model_slew`, `input_slew`
  - `output_slew_merge_arcs`
  - `sta_slew_bias`
  - `arc`
- These helpers do not touch odb, parasitics, the STA graph or options. The STA graph is read only when `DelayEstimator.cc` prepares the snapshots, for example `edgeFromSlew` and `arcDelay`.

**Writes and returns**
- All functions are pure. They mutate nothing global.
- Outputs go through reference parameters (`delay`, `output_slew`) and the optional `*match_relaxed_out` / `*slew_relaxed_out` flags.
- The relaxed flags are OR-set only. They are never reset to false, so callers can chain several lookups on one flag.
- `lookupArcDelayAndSlewForArc` initialises `delay = -sta::INF` and `output_slew = 0` before searching.
- `lookupBufferDelayAndSlew` initialises both to `0`.
- Outputs are in STA's internal units (seconds, farads).

## Algorithm / control flow
**`lookupArcDelayAndSlew`** (`DelayEstimator.cc:291`)
1. It returns false if `cell` is null or `sceneCell(scene, min_max)` is null.
2. It finds the cell's arc sets between the ports named like `ref_arc->from()` and `->to()`, matched by port name. If either port is missing, the arc-set list is empty.
3. It skips timing-check arc sets.
4. It takes the first arc found by `findMatchingTimingArc(ref_arc, arc_set)` (the exact matcher) and returns the table-model result.
5. If nothing matched and the mode is not `kRelaxedCandidate`, it returns false.
6. In relaxed mode it scans every non-check arc with `matchTimingArc(..., kRelaxedCandidate) == kRelaxed`. It keeps the arc with the worst output slew, using `min_max->compare`. The reported delay comes from that same arc. If any arc is kept, it sets `*match_relaxed_out`.

**`lookupBufferDelayAndSlew`** (`DelayEstimator.cc:398`)
1. It resolves the scene cell and its `bufferPorts`.
2. It scans non-check arcs of the buffer's input-to-output arc sets.
3. It keeps only arcs whose input and output edges both equal `target_stage.arc.outputRiseFall()`. This assumes a non-inverting buffer on that transition.
4. Among the arcs that evaluate, it keeps the worst delay for the min/max sense. The slew is the slew of that same arc.

**`estimateOutputSlew`** (`DelayEstimator.cc:1151`)
1. If `canUseSlewBias` holds, it uses the slew-bias path:
   - `canUseSlewBias` requires `sta_slew_bias.valid`, `cell == stage.arc.currentCell()`, and `slewsMatch(input_slew, stage.input_slew)`.
   - It evaluates the model's `table_worst_arc` at `sta_slew_bias.input_slew` and the new load.
   - It adds `interpolateStaSlewBias(model, load_cap)`, a three-sample interpolation, and clamps at 0.
   - If the lookup fails, it falls through to the merge path.
2. Otherwise it runs the merge path:
   - It starts from `selected_output_slew`.
   - For each `OutputSlewMergeArc`, it uses `path_input_slew` if the arc shares the selected input port and edge, and the arc's own stored `input_slew` otherwise. It looks the arc up and keeps the worst slew.
   - It returns `max(current_slew + (model_slew - current_model_slew), 0)`. This is a delta calibration against STA's merged vertex slew.

**`estimateReceiverInputSlew`**
- It returns `max(cand,0) * max(receiver.input_slew,0) / max(driver.current_slew, 1e-15)`, which keeps the current wire degradation ratio.

**`wireElmoreDelay`**
- It returns 0 if `res <= 0`, `cap < 0` or `load_cap < 0`. Otherwise it returns `res * (load_cap + 0.5 * cap)`.

**`makeEstimate`**
- `arrival_impr = current - candidate`.
- `legal = arrival_impr > 0`, with strict inequality.
- `reason` is `kEstimateLegal` or `kEstimateNonImproving`.
- `side_paths_evaluated` and `side_loss` stay at 0. Later passes fill them in (`applyDualRfCheck`, `applyFaninSideLoss`, in `DelayEstimator.cc`).

## Key data structures
All are defined in `OptimizerTypes.hh`.
- **`SelectedArc`** holds `scene`, `min_max`, `pvt` and `ref_arc`, plus accessors `inputPort`, `outputPort`, `inputRiseFall`, `outputRiseFall` and `currentCell`.
- **`DelayStageState`** is the per-stage electrical snapshot. It holds `arc`, `driver_pin`, `input_slew`, `load_cap`, `current_model_delay`, `current_delay`, `current_wire_delay`, `current_model_slew` and `current_slew`. It also holds `output_slew_merge_arcs`, `sta_slew_bias`, `opposite_rf_arcs` and `path_index`.
- **`SlewBiasModel`** holds `valid`, `table_worst_arc`, `input_slew` and `samples[3]` of `{load_cap, table_slew, sta_slew}`.
- **`OutputSlewMergeArc`** is `{ref_arc, input_slew, current_model_slew}`.
- **`WireRC`** is `{length, res, cap}`.
- **`DelayEstimate`** is `{legal, candidate_delay, arrival_impr, side_paths_evaluated, side_loss, reason}`.
- **`ArcMatchMode`** is `kExact` or `kRelaxedCandidate`.
- **`FailReason`** is the reason enum.

## Callers and callees (verified by reading)
- **Callers** (verified by grep): only `DelayEstimator.cc` and `DelayEstimatorBufferTree.cc`, through `using estimator_detail::...` declarations near the top of each file.
- **Definitions:**
  - `DelayEstimator.cc:376` (`lookupArcDelayAndSlew`)
  - `DelayEstimator.cc:398` (`lookupBufferDelayAndSlew`)
  - `DelayEstimator.cc:1151` (`estimateOutputSlew`)
  - `DelayEstimator.cc:1217` (`estimateReceiverInputSlew`)
  - `DelayEstimator.cc:1240` (`wireElmoreDelay`)
  - `DelayEstimator.cc:1576` (`makeEstimate`)
- **Callees:**
  - `lookupArcDelayAndSlewForArc`
  - `gateDelayAndSlewFromTableModel`
  - `findMatchingTimingArc`
  - `matchTimingArc`
  - `canUseSlewBias`
  - `interpolateStaSlewBias`
  - `LibertyCell::sceneCell`, `bufferPorts` and `timingArcSets`
- I did not read the bodies of `gateDelayAndSlewFromTableModel` or the matcher functions in detail.

## Invariants and "do not break"
- Keep these helpers free of STA analysis calls (`Resizer`, graph, parasitics). Worker threads call them on a `Target`'s prepared snapshot, and the snapshot is prepared on the main thread. The estimators are used by Mt policies, so a mutable or STA-touching helper would introduce data races.
- They have no journaling or rollback duty, because they never change the netlist.
- They are deterministic. The only tie-breaks are `min_max->compare` over arcs, which depends on arc iteration order.
- Relaxed matching must stay target-candidate only. Callers use `kExact` for fanin, fanout and downstream stages.
- The `*_relaxed_out` flags are accumulate-only. Do not reset them inside these helpers.
- The slew calibration baseline pairs `current_slew` with `current_model_slew`. A new caller must supply both from the same snapshot.
- `legal` means strictly positive arrival improvement. Policies treat `legal=false` as a skip.
- dont_touch and legality are not checked here. They are handled upstream in the generators and candidates.
- Parasitics validity is also not handled here. `WireRC` values come from the callers.

## Weak spots / assumptions an algorithm designer should know
- Delays are table lookups with lumped load and no wire-RC or CCS waveform effects. `DelayEstimator.cc` partly compensates by adding the table delta to STA's baseline (`current_delay + model_delta`) and by the slew-bias model.
- `lookupBufferDelayAndSlew` ignores inverting buffers and unequal input and output edges. It requires both edges to equal the target output transition.
- When the relaxed arc search finds several arcs, it picks the worst slew, not the best delay. That is deliberately conservative for slew but can misreport delay.
- Exact arc matching takes the first matching arc set. Conditional (`when`) arcs may therefore pick one condition arbitrarily.
- Slew-bias interpolation is valid only at a matching input slew (`slewsMatch`) and for the unchanged cell. Cell swaps always use merge calibration.
- `estimateReceiverInputSlew` assumes the net's slew degradation ratio stays constant after the ECO. A buffer or split changes the wire, so this is only approximate. The buffer-tree estimator adds its own scale factors and the `boundBufferTreeDownstreamStageDelay` bound for that reason.
- `wireElmoreDelay` returns 0 for non-positive resistance and also for negative caps. Bad `WireRC` data therefore yields an optimistic zero silently.
- The `kElmoreSlewFactor` of 1.39 is a fixed constant, with no technology dependence.