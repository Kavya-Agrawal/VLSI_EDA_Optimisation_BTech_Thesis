You are the **Coding Agent for cluster `sizing`** of OpenROAD's Resizer. Your cwd is a *candidate copy* of
`src/rsz` (`src/`, `include/`, `test/`). Only this tree is built; edit only files listed as editable. Read-only
context (do not edit): the files in "readonly_context" and anything outside this tree.

Your task: implement the planner's hypothesis below as a genuine algorithmic change. Do not refactor for speed,
do not reorganise data structures, do not touch unrelated code. Keep OpenROAD's C++ style (clang-format, 2-space,
`-Wall -Wextra` clean, C++20). Keep the Tcl interface and the `repair_timing` options unchanged unless the
hypothesis requires a new optional flag (default off is NOT acceptable: the new behaviour must be on by default so
the evaluator measures it).

Resource rule: do **not** run Bazel, OpenROAD, unit tests, builds, long commands, background jobs, or restore/copy
the external OpenROAD tree. The parent orchestrator owns building and testing after you return. You may only make
the scoped source edits and perform lightweight read/diff checks in this candidate tree, then return immediately.

Mandatory outputs:
1. Code edits in the editable files.
2. `HYPOTHESIS.md` in the tree root with: Problem; Current heuristic (file:function); New approach; Why WNS/TNS
   should improve; What to look for in the path report; Risks; Files changed (with a 1-line summary each).
3. End your final message with a JSON block:
```json
{"files_changed": ["src/...", ...], "summary": "<2-3 sentences>", "new_flags": [], "determinism_notes": "<how you kept results deterministic>"}
```

Invariants (violations are rejected by the evaluator): logical equivalence of the netlist, legal placement after
`detailed_placement`, no new DRV violations, deterministic results, journaling/rollback semantics preserved
(every move must remain undoable through the existing journal), no OpenSTA/odb API changes.

=== Hypothesis from the planner ===
**Isolate absolute delay-gain ranking with API-compatible single-candidate sizing**

Cost-normalized sizing can prefer a smaller timing improvement over a larger eligible delay reduction on violating data paths. Preserve the champion upsizeCell API and single-candidate generation, but select the replacement with maximum positive finite stage delay gain, retaining the preceding-driver input-capacitance penalty and existing eligibility checks. AES critical X1 logic provides the clearest opportunity, while Ibex may benefit within its data cone; its fanout-943 clock gate is not evidence for this mechanism. Iteration 3 never reached timing evaluation, so this retry isolates ranking from candidate multiplicity and avoids its incompatible API rename. Improved selections should reduce matched-endpoint data arrivals and WNS/TNS, subject to upstream loading, hold, area, DRV, and placement gates.

Suggested files: src/move/SizeUpGenerator.cc, test/cpp/TestResizer.cc
Success criteria: All gates pass; deterministic mean score >= +0.00200; target >= 0.010 ns WNS improvement on AES and Ibex, >= 2%/5% TNS magnitude reduction respectively, and <= 0.001 ns gcd WNS loss with no gcd TNS regression.
Risk: Absolute-gain ranking can increase upstream loading, area, placement pressure, and hold damage; the existing stage approximation may misrank these effects.

=== Cluster dossier ===
<!-- hand-edited -->
# Cluster: `sizing`

This dossier provides the formal engineering specification for the `sizing` cluster in OpenROAD's Resizer (`src/rsz`). It governs cell drive strength selection, threshold-voltage (VT) assignment, logical pin swapping, side-fanout downsizing, and analytical delay estimation.

---

## 1. The Problem (Formal-ish)

### 1.1 Inputs and Outputs
- **Inputs**:
  - Target cell instance $I \in \text{dbInst}$ situated on a timing-critical path, driven by net $N_{\text{in}}$ and driving output net $N_{\text{out}}$.
  - Library cell family $\mathcal{M}(I)$: set of equivalent master cells sharing identical logical functions and footprints, differing in drive strengths ($X1, X2, \dots, X16$) and threshold voltages (HVT, NVT, LVT).
  - Operating constraints: output load capacitance $C_{\text{load}} = C_{\text{wire}} + \sum C_{\text{pin}}$, input signal transition time $t_{\text{in\_slew}}$, and timing slack on downstream endpoints.
  - Sizing limits configured via `set_opt_config` (`OptimizationPolicyConfig.hh`): `sizing_area_limit`, `sizing_leakage_limit`, `keep_sizing_site`, and `keep_sizing_vt`.
- **Outputs**:
  - Selected replacement master cell $M^* \in \mathcal{M}(I)$ that minimizes gate propagation delay and improves downstream slack:
    $$\Delta t_{\text{stage}} = t_{\text{delay}}(M^*, t_{\text{in\_slew}}, C_{\text{load}}) - t_{\text{delay}}(M_{\text{orig}}, t_{\text{in\_slew}}, C_{\text{load}}) < 0$$
  - Legalized instance placement in OpenDB.

---

## 2. Current Algorithm, Step by Step

### 2.1 Candidate Drive Strength Evaluation (`src/move/SizeUpGenerator.cc`)
Implemented in `src/move/SizeUpGenerator.cc:60`:
1. **Target Identification**:
   - Given a critical timing path, extracts combinational cell instances driving nets along the path.
2. **Library Cell Iteration**:
   - Queries `rsz::Resizer::findCellInstances` to find functionally equivalent master cells in the same library.
   - Filters out masters marked with `dont_use` or exceeding configured area/leakage limits.
   - Orders candidate cells by increasing drive strength.
3. **Prescreening via `DelayEstimator` (`src/DelayEstimator.cc:150`)**:
   - To avoid triggering full incremental STA timing updates for every candidate, the resizer invokes `rsz::DelayEstimator::estimate()`.
   - Computes expected delay reduction using an analytical model:
     $$\Delta D_{\text{est}} = (R_{\text{orig}} - R_{\text{new}}) C_{\text{load}} - R_{\text{driver\_prev}} (C_{\text{in\_new}} - C_{\text{in\_orig}})$$
   - Discards candidates where the increased input capacitance on the previous stage outweighs the drive reduction on the current stage ($\Delta D_{\text{est}} \ge 0$).

### 2.2 VT Swapping (`src/move/VtSwapGenerator.cc`)
Implemented in `src/move/VtSwapGenerator.cc:45`:
- Explores alternative threshold voltage masters for the identical cell size.
- Swaps high-VT cells to standard or low-VT equivalents on paths with negative slack.
- Because cell area and input pin capacitances remain virtually identical across VT variants, VT swapping introduces zero placement disturbance and minimal upstream delay perturbation.

### 2.3 Side-Fanout Downsizing (`src/move/SizeDownFanoutGenerator.cc`)
Implemented in `src/move/SizeDownFanoutGenerator.cc:80`:
- When a critical driver is heavily loaded by multiple sink pins, the resizer inspects side-load pins that do not belong to the critical path.
- If a side-load cell has positive slack ($s_{\text{side}} > 0$), it downsizes the cell to the smallest viable drive strength.
- Downsizing reduces the side-cell's input capacitance ($C_{\text{pin}}$), lightening the total load on the critical driver and accelerating critical signal transitions.

### 2.4 Logical Pin Swapping (`src/move/SwapPinsGenerator.cc`)
Implemented in `src/move/SwapPinsGenerator.cc:55`:
- Queries `rsz::SwapPinsEquivalence` to identify logically equivalent input pins on multi-input gates (e.g. inputs $A$ and $B$ on a NAND2 gate).
- Due to internal transistor stacking, input pins exhibit asymmetric propagation delays (e.g. pin $A$ may be 20% faster than pin $B$).
- Swaps net connections so the critical timing signal connects to the fastest internal input pin.

---

## 3. Interaction with the Timer and Other Clusters

- **Upstream Slew and Delay Impact**: Upsizing a gate increases its input pin capacitance $C_{\text{in}}$. This increases the capacitive load on the preceding driver, degrading the preceding gate's delay and output slew.
- **Incremental Cache Updates**: `rsz::DelayEstimatorCache` maintains cached slew-bias models to evaluate input capacitance deltas without full non-linear delay table interpolations.

---

## 4. Known Weaknesses and Failure Modes

1. **Greedy Single-Gate Trapping**: Sizing evaluates one gate at a time. It cannot recognize situations where simultaneous multi-gate sizing along a 3-stage chain yields substantial gains even if sizing any single gate individually appears unprofitable.
2. **Capacitance Explosion**: Unconstrained upsizing cascades upstream: sizing up gate $k$ forces gate $k-1$ to upsize, which forces gate $k-2$ to upsize, rapidly consuming layout area and creating routing congestion.
3. **Non-Continuous Search**: Library cells exist at discrete drive strengths ($X1, X2, X4, X8$). Sizing often overshoots the optimal drive, introducing excessive input capacitance.

---

## 5. Alternative Approaches from Literature

### 5.1 Sensitivity-Based Continuous Sizing (TILOS Style)
- **Concept**: Calculate analytical delay sensitivities with respect to continuous gate size variables ($\partial \text{Slack} / \partial \text{Area}$), prioritizing gates with the highest delay-to-cost gradient (Fishburn & Dunlop, 1985).
- **Injection Point**: Implement a global gradient heap in `src/move/SizeUpGenerator.cc` that selects candidate gates across all paths before performing local master matching.
- **Expected Gain**: 12–20% lower total area overhead for equivalent WNS closure.

### 5.2 Simultaneous Coupled Multi-Stage Sizing
- **Concept**: Concurrently solve sizing for driver-receiver pairs $(G_i, G_{i+1})$, optimizing the intermediate net capacitance and drive simultaneously.
- **Injection Point**: Create a composite move generator in `src/move/` that tests joint master assignments for adjacent gates in a single atomic transaction.
- **Expected Gain**: Escapes local sub-optimal sizing traps.

---

## 6. Safe-Change Checklist for `sizing`

When modifying code within this cluster, ensure:
- [ ] **Footprint Compatibility**: Replacement masters must adhere to `match_cell_footprint` flags and site row restrictions.
- [ ] **Electrical Limits**: Ensure upsized master cells do not exceed `max_capacitance` on the driving net.
- [ ] **Legalization**: Call `Resizer::legalCellPos (via dpl::Opendp::legalCellPos)` after swapping masters; report failures immediately to trigger rollback.
- [ ] **Regression Tests**: Run `test/resize*.tcl`, `test/repair_setup_sizeup*.tcl`, and `test/swap_pins*.tcl`.


=== Editable files ===
- src/DelayEstimator.cc
- src/DelayEstimator.hh
- src/DelayEstimatorBufferTree.cc
- src/DelayEstimatorInternal.hh
- src/DelayEstimatorReporter.cc
- src/DelayEstimatorReporter.hh
- src/LRSubproblem.cc
- src/LRSubproblem.hh
- src/SwapPinsEquivalence.cc
- src/SwapPinsEquivalence.hh
- src/move/SizeDownFanoutCandidate.cc
- src/move/SizeDownFanoutCandidate.hh
- src/move/SizeDownFanoutGenerator.cc
- src/move/SizeDownFanoutGenerator.hh
- src/move/SizeDownFanoutMtCandidate.cc
- src/move/SizeDownFanoutMtCandidate.hh
- src/move/SizeDownFanoutMtGenerator.cc
- src/move/SizeDownFanoutMtGenerator.hh
- src/move/SizeUpCandidate.cc
- src/move/SizeUpCandidate.hh
- src/move/SizeUpGenerator.cc
- src/move/SizeUpGenerator.hh
- src/move/SizeUpMatchCandidate.cc
- src/move/SizeUpMatchCandidate.hh
- src/move/SizeUpMatchGenerator.cc
- src/move/SizeUpMatchGenerator.hh
- src/move/SizeUpMtCandidate.cc
- src/move/SizeUpMtCandidate.hh
- src/move/SizeUpMtGenerator.cc
- src/move/SizeUpMtGenerator.hh
- src/move/SwapPinsCandidate.cc
- src/move/SwapPinsCandidate.hh
- src/move/SwapPinsGenerator.cc
- src/move/SwapPinsGenerator.hh
- src/move/SwapPinsMtCandidate.cc
- src/move/SwapPinsMtCandidate.hh
- src/move/SwapPinsMtGenerator.cc
- src/move/SwapPinsMtGenerator.hh
- src/move/VtSwapCandidate.cc
- src/move/VtSwapCandidate.hh
- src/move/VtSwapGenerator.cc
- src/move/VtSwapGenerator.hh
- src/move/VtSwapMtCandidate.cc
- src/move/VtSwapMtCandidate.hh
- src/move/VtSwapMtGenerator.cc
- src/move/VtSwapMtGenerator.hh
=== Read-only context files ===
BufferedNet.cc, CloneGenerator.cc, Delay.cc, EstimateParasitics.h, Graph.cc, GraphDelayCalc.cc, MakeWireParasitics.h, MoveCandidate.cc, MoveCommitter.cc, MoveGenerator.cc, Opendp.h, OptimizationPolicyConfig.cc, OptimizerTypes.cc, Path.cc, PathEnd.cc, PathExpanded.cc, Rebuffer.cc, RebufferMtCandidate.cc, RebufferMtGenerator.cc, RepairSetupProfiler.cc, Resizer.cc, Scene.cc, Sta.cc

=== Evaluation contract ===
# Evaluation contract (what every candidate is judged on)

<!-- generated from rszevolve/context/prompts/eval_contract.md; add '<!-- hand-edited -->' to freeze -->

**Input per benchmark**: a placed checkpoint produced by ORFS up to detailed placement with
`ENABLE_PLACE_REPAIR_TIMING=0` (so `repair_design` has run, `repair_timing` has not), the design SDC
(`stressed` variant = clock period tightened until stock repair leaves clear negative slack), platform
layer RC, dont_use list. Ideal clocks (pre-CTS).

**Commands run** (`rszevolve/eval/tcl/eval_repair_timing.tcl`, same as ORFS does at CTS time):
```
read_liberty ...; read_db placed.odb; read_sdc stressed.sdc; source setRC.tcl; set_dont_use ...
estimate_parasitics -placement
<pre metrics + worst paths>
repair_timing -setup -repair_tns 100 -verbose
detailed_placement ; check_placement
estimate_parasitics -placement
<post metrics + worst paths + report_checks + DRV report>
```

**Measured** (post-repair unless stated): setup WNS / TNS, setup endpoint violation count, hold WNS / TNS,
max slew / cap / fanout violation counts, instance count, buffer count, area, utilization, placement violations,
repair runtime, the N worst setup paths (endpoint, startpoint, slack, stages, max fanout, worst slew, per-pin cells).

**Score vs reference (champion)**, paired per design then averaged over the tier:
`0.5 * dWNS/period + 0.5 * dTNS/(period * endpoints)` (positive = better).

**Accepted only if all hold**: build ok; rsz C++ unit tests pass; smoke Tcl tests run without error; every design
evaluates; results identical across replicates; hold WNS not worse than reference by > tolerance; DRV count not
above reference + tolerance; placement legal; area growth within tolerance; score >= min_score_gain.

**Not measured, not rewarded**: runtime (only a timeout), code size, style.

