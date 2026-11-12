You are the **Coding Agent for cluster `setup_strategy`** of OpenROAD's Resizer. Your cwd is a *candidate copy* of
`src/rsz` (`src/`, `include/`, `test/`). Only this tree is built; edit only files listed as editable. Read-only
context (do not edit): the files in "readonly_context" and anything outside this tree.

Your task: implement the planner's hypothesis below as a genuine algorithmic change. Do not refactor for speed,
do not reorganise data structures, do not touch unrelated code. Keep OpenROAD's C++ style (clang-format, 2-space,
`-Wall -Wextra` clean, C++20). Keep the Tcl interface and the `repair_timing` options unchanged unless the
hypothesis requires a new optional flag (default off is NOT acceptable: the new behaviour must be on by default so
the evaluator measures it).

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
****

You've hit your 5-hour limit · resets 7:50am (Asia/Calcutta)

Suggested files: 
Success criteria: 
Risk: 

=== Cluster dossier ===
<!-- hand-edited -->
# Cluster: `setup_strategy`

This dossier provides the formal engineering specification for the `setup_strategy` cluster in OpenROAD's Resizer (`src/rsz`). It governs global target endpoint collection, path prioritization, phase scheduling, speculative move exploration, journaled transactional rollbacks, and multi-threaded parallel candidate evaluation.

---

## 1. The Problem (Formal-ish)

### 1.1 Inputs and Outputs
- **Inputs**:
  - Timing graph $G = (V, E)$ populated with gate delays and interconnect RC parasitics derived from placed coordinates (`odb::dbBlock`, `sta::dbSta`).
  - Active timing constraints across clock domains (SDC), including clock periods $T_{\text{clk}}$, arrival times at inputs, required times at outputs, and clock uncertainties.
  - Setup optimization configuration parameters (`rsz::OptimizerRunConfig` in `src/OptimizerTypes.hh`): `setup_slack_margin`, `repair_tns_end_percent`, `max_passes`, `max_iterations`, `max_repairs_per_pass`, and active policy phase tokens (`phases`).
- **Outputs**:
  - Sequence of committed netlist modifications (cell master replacements, inserted repeaters, swapped pins) committed to `odb::dbDatabase`.
  - Optimized setup slack metrics: reduced Worst Negative Slack ($WNS$) and Total Negative Slack ($TNS$) without regressions in Design Rule Violations (DRVs) or hold timing slacks.

### 1.2 Objective Function
The primary objective is closing setup timing across all constrained endpoints $\mathcal{P}_{\text{end}}$:
$$\min \left( \sum_{p \in \mathcal{P}_{\text{end}}} \max(0, -s(p)) \right) \quad \text{subject to} \quad \min_{p \in \mathcal{P}_{\text{end}}} s(p) \ge -s_{\text{margin}}$$
where $s(p) = T_{\text{required}}(p) - T_{\text{arrival}}(p)$ is the setup slack at endpoint pin $p$. Secondary objectives enforce monotonicity: no newly introduced maximum slew, capacitance, or fanout violations, and no newly created hold timing violations ($s_{\text{hold}}(p) \ge -h_{\text{margin}}$).

### 1.3 Execution Context and Calling Frequency
Called from `rsz::repair_timing -setup` (Tcl entry point) through `rsz::Resizer::repairSetup()` (`src/Resizer.cc:5401`) and orchestrated by `rsz::Optimizer::run()` (`src/Optimizer.cc:161`). In a complete physical design flow, it executes after global placement (`resize.tcl`), post-CTS (`cts.tcl`), and post-global route (`global_route.tcl`).

---

## 2. Current Algorithm, Step by Step

### 2.1 Orchestration Loop (`rsz::Optimizer::run`)
The central controller executes a phased pipeline of optimization policies (`src/Optimizer.cc:204`):

```python
def Optimizer_run():
    # 1. Preamble initialization
    resizer.runRepairSetupPreamble() # Resizer.cc:5380
    committer.init()                 # MoveCommitter.cc:50
    parasitics_guard = est.IncrementalParasiticsGuard()
    
    # 2. Phase Token Parsing
    # Default: "LEGACY" (or user tokens: "WNS", "TNS", "PARALLEL_EVAL", etc.)
    phases = appendImplicitCritVtSwapForLegacyPhases(parseTokens(config.phases))
    
    # 3. Phased Execution Loop
    for phase_name in phases:
        policy = makePolicyForPhase(phase_name, setup_context)
        policy.start()
        while not policy.converged():
            policy.iterate()
        policy.finish()
```

### 2.2 Core Iteration Routine (`rsz::SetupLegacyBase::iterate`)
The core iterative loop is implemented in `src/policy/SetupLegacyBase.cc:110`:
1. **Target Collection (`rsz::RepairTargetCollector::collectPinsByPathEndpoint`)**:
   - Traverses all endpoints using OpenSTA's endpoint iterator (`src/RepairTargetCollector.cc:85`).
   - Filters endpoints with negative slack ($s(p) < \text{setup\_margin}$).
   - Sorts endpoints in ascending order of slack (worst-slack endpoint first).
2. **Path Unrolling (`sta::PathExpanded`)**:
   - For each target endpoint, unrolls the worst-slack timing path backwards from sink to launch register (`src/RepairTargetCollector.cc:210`).
   - Extracts all intermediate driver pins along the combinational data path (`collectExpandedPathDriverPins`).
3. **Candidate Move Generation (`rsz::MoveGenerator::generate`)**:
   - Queries registered move generators in configured sequence order (`src/move/MoveGenerator.cc:45`):
     - `SizeUpGenerator`: Evaluates up-sizing cell drive strengths.
     - `BufferGenerator`: Evaluates repeater insertion along wire segments.
     - `SwapPinsGenerator`: Evaluates permuting symmetric input pins.
     - `SplitLoadGenerator`: Evaluates isolating non-critical loads.
     - `CloneGenerator`: Evaluates gate replication for fanout reduction.
     - `SizeDownFanoutGenerator`: Evaluates downsizing non-critical side-loads.
4. **Fast Prescreening (`rsz::DelayEstimator::estimate`)**:
   - Scans candidate moves using first-order Elmore delay and slew bias approximations (`src/DelayEstimator.cc:120`).
   - Prunes moves predicting negative or zero timing gain.
5. **Speculative Application and Journaling (`rsz::MoveCommitter::commit`)**:
   - Opens a transactional journal frame (`rsz::MoveTracker::beginJournal` in `src/MoveTracker.cc:85`).
   - Applies the ECO change to OpenDB (`odb::dbInst::swapMaster` or net modifications).
   - Legalizes moved or resized instances via OpenDP (`dpl::Opendp::legalCellPos (called from Resizer.cc:3165)`).
6. **Incremental Timing Query and Acceptance Test**:
   - Updates local STA timing graph (`sta::Sta::updateTiming`).
   - Evaluates whether the move improved slack on the failing endpoint without causing major regressive violations on other paths (`src/policy/SetupWnsPolicy.cc:48`):
     - If accepted: `committer.commitTrackedMoves()` permanently integrates the modification.
     - If rejected: `committer.abortJournalScope()` rolls back all OpenDB mutations to the journal snapshot.

### 2.3 Heuristics, Thresholds, and Constants
- `repair_tns_end_percent` (`OptimizerTypes.hh:35`): Stop phase when $TNS_{\text{current}} \ge TNS_{\text{initial}} \times \text{percent}$. Default is $1.0$ (100% repair).
- `max_passes` (`OptimizerTypes.hh:36`): Upper bound on optimization passes (default 10,000).
- `max_repairs_per_pass` (`OptimizerTypes.hh:38`): Number of accepted moves allowed per endpoint before advancing to the next endpoint (default 1).
- `checkpoint_tolerance` (`SetupParallelEvalPolicy.cc:42`): Minimum slack delta required to commit a speculative batch (typically $1.0 \times 10^{-12}$ s).

### 2.4 Complexity and Greedy Characteristics
- **Time Complexity**: $\mathcal{O}(P \cdot K \cdot G \cdot \tau_{\text{STA}})$, where $P$ is the number of passes, $K$ is the number of failing endpoints, $G$ is the number of tested moves, and $\tau_{\text{STA}}$ is the incremental timing propagation latency.
- **Greedy Stance**: Commits the first single move that yields a positive slack delta on the target endpoint.
- **Blind Spots**: Never evaluates multi-move combinations simultaneously; ignores downstream congestion created by repeated cell drive expansions.

---

## 3. Interaction with the Timer and Other Clusters

- **OpenSTA Graph Interlock**: Every move committed via `rsz::MoveCommitter` modifies `odb::dbDatabase` objects, notifying OpenSTA through `dbStaCbk` listeners.
- **Incremental Invalidation**: Cell master swaps change pin capacitances ($C_{\text{pin}}$), immediately invalidating driver delays on preceding upstream stages and slews on succeeding downstream stages.
- **Subsystem Dependencies**:
  - Relies on `sizing` (`SizeUpGenerator`, `DelayEstimator`) for candidate generation.
  - Relies on `buffering` (`BufferGenerator`, `Rebuffer`) for long-wire delay reduction.
  - Relies on `timing_model` for rapid delay prescreening before invoking full STA.

---

## 4. Known Weaknesses and Failure Modes

1. **Greedy Local Trapping**: Committing the first move that provides a small slack gain often precludes a larger structural improvement (e.g. up-sizing a driver slightly prevents a beneficial buffer tree insertion).
2. **Path Thrashing on Shared Trunks**: Upstream nodes shared by thousands of fanout paths are repeatedly resized by competing endpoints, causing oscillations in arrival times and TNS thrashing.
3. **Lack of Global Slack Budgeting**: Moves are selected based on immediate endpoint slack rather than balanced slack distribution across all stages of a pipeline.
4. **Placement Density Saturation**: Repeated up-sizing in local clusters creates unlegalizable cell densities, eventually triggering OpenDP legalization failures and forced rollbacks.

---

## 5. Alternative Approaches from Literature

### 5.1 Global Lagrangian Relaxation (LR)
- **Concept**: Formulate setup timing closure as a constrained convex optimization over all circuit nodes simultaneously (Chen, Chu, Wong, 1999).
- **Injection Point**: Replace `rsz::SetupWnsPolicy` with an active multiplier updater in `src/policy/GlobalSizingPolicy.cc` that recalculates Lagrange multipliers $\lambda_{ij}$ across timing edges, driving concurrent sizing moves without single-endpoint greedy traps.
- **Expected Gain**: 5–15% better TNS reduction with smoother cell area growth.

### 5.2 Zero-Slack Algorithm (ZSA) Budgeting
- **Concept**: Distribute timing slack proportionally across all intermediate gates along critical paths before invoking local moves (Nair et al., 1989).
- **Injection Point**: Implement a pre-pass in `src/policy/BottleneckAnalysis.cc` that assigns explicit delay reduction targets ($\Delta D$) to intermediate driver pins, restricting move generators to target specific delay budgets.
- **Expected Gain**: Eliminates path thrashing and preserves timing on non-critical branches.

### 5.3 Batch Hypergraph Cut Pruning
- **Concept**: Partition failing endpoints into independent, non-interfering timing cones using graph min-cut formulations.
- **Injection Point**: Replace `src/policy/BatchSelector.cc` to select batches of completely independent timing cones, maximizing multithreaded efficiency in `SetupParallelEvalPolicy`.
- **Expected Gain**: Super-linear speedup in multithreaded optimization without move collision rollbacks.

---

## 6. Safe-Change Checklist for `setup_strategy`

When modifying code within this cluster, ensure:
- [ ] **Transactional Journaling**: All OpenDB operations must execute within active `committer.beginJournal()` boundaries so rejected moves roll back cleanly.
- [ ] **Placement Legality**: Every move must call `Resizer::legalCellPos (via dpl::Opendp::legalCellPos)` before STA evaluation; unplaced or overlapping instances will corrupt parasitics.
- [ ] **`dont_touch` Enforcement**: Verify `rsz::Resizer::dontTouch(inst)` is checked before proposing modifications.
- [ ] **Determinism**: Avoid iterating over `std::unordered_map` or sorting by pointer addresses; use deterministic node identifiers (`sta::Pin::name()`, `odb::dbInst::getId()`).
- [ ] **Regression Verification**: Run test suite `test/repair_setup*.tcl` (specifically `repair_setup1.tcl`, `repair_setup4_sequence.tcl`, and `repair_setup_parallel_eval.tcl`).


=== Editable files ===
- src/MoveCommitter.cc
- src/MoveCommitter.hh
- src/MoveTracker.cc
- src/MoveTracker.hh
- src/OptimizationPolicyConfig.cc
- src/OptimizationPolicyConfig.hh
- src/Optimizer.cc
- src/Optimizer.hh
- src/OptimizerTypes.cc
- src/OptimizerTypes.hh
- src/PathGroupFilter.cc
- src/PathGroupFilter.hh
- src/RepairSetupAnalysisReport.cc
- src/RepairSetupAnalysisReport.hh
- src/RepairSetupAnalysisTarget.cc
- src/RepairSetupAnalysisTarget.hh
- src/RepairSetupContext.hh
- src/RepairSetupMoveSampler.cc
- src/RepairSetupMoveSampler.hh
- src/RepairSetupMoveSnapshot.cc
- src/RepairSetupMoveSnapshot.hh
- src/RepairSetupProfiler.cc
- src/RepairSetupProfiler.hh
- src/RepairTargetCollector.cc
- src/RepairTargetCollector.hh
- src/move/MoveCandidate.cc
- src/move/MoveCandidate.hh
- src/move/MoveGenerator.cc
- src/move/MoveGenerator.hh
- src/policy/BatchSelector.cc
- src/policy/BatchSelector.hh
- src/policy/BottleneckAnalysis.cc
- src/policy/BottleneckAnalysis.hh
- src/policy/GlobalSizingPolicy.cc
- src/policy/GlobalSizingPolicy.hh
- src/policy/OptimizationPolicy.cc
- src/policy/OptimizationPolicy.hh
- src/policy/ParallelEvalState.cc
- src/policy/ParallelEvalState.hh
- src/policy/ProgressReporter.cc
- src/policy/ProgressReporter.hh
- src/policy/SetupCritVtSwapPolicy.cc
- src/policy/SetupCritVtSwapPolicy.hh
- src/policy/SetupDirectionalPolicy.cc
- src/policy/SetupDirectionalPolicy.hh
- src/policy/SetupLastGaspPolicy.cc
- src/policy/SetupLastGaspPolicy.hh
- src/policy/SetupLegacyBase.cc
- src/policy/SetupLegacyBase.hh
- src/policy/SetupLegacyPolicy.cc
- src/policy/SetupLegacyPolicy.hh
- src/policy/SetupParallelEvalPolicy.cc
- src/policy/SetupParallelEvalPolicy.hh
- src/policy/SetupReroutePolicy.cc
- src/policy/SetupReroutePolicy.hh
- src/policy/SetupTnsPolicy.cc
- src/policy/SetupTnsPolicy.hh
- src/policy/SetupWnsPolicy.cc
- src/policy/SetupWnsPolicy.hh
=== Read-only context files ===
BufferGenerator.cc, BufferToInvertersGenerator.cc, BufferedNet.cc, CloneGenerator.cc, Delay.cc, DelayEstimator.cc, EstimateParasitics.h, Graph.cc, GraphDelayCalc.cc, LRSubproblem.cc, MakeWireParasitics.h, Mode.cc, Opendp.h, Path.cc, PathEnd.cc, PathExpanded.cc, PathGroup.cc, Rebuffer.cc, RebufferMtCandidate.cc, RebufferMtGenerator.cc, RerouteGenerator.cc, Resizer.cc, Scene.cc, Search.cc, SizeDownFanoutGenerator.cc, SizeDownFanoutMtGenerator.cc, SizeUpMatchGenerator.cc, SizeUpMtCandidate.cc, SizeUpMtGenerator.cc, SplitLoadGenerator.cc, SplitLoadMtGenerator.cc, Sta.cc, StaState.cc, SwapPinsGenerator.cc, SwapPinsMtGenerator.cc, TestResizer.cc, UnbufferGenerator.cc, VtSwapCandidate.cc, VtSwapGenerator.cc, VtSwapMtCandidate.cc, VtSwapMtGenerator.cc, dbNetwork.cc

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

