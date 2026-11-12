<!-- hand-edited -->
# OpenROAD Resizer (`src/rsz`): Big Picture Architecture & Algorithms

This document provides the foundational engineering specification of OpenROAD's Resizer subsystem (`src/rsz`). It details the problem formulation, flow integration within OpenROAD Flow Scripts (ORFS), incremental static timing engine coupling, Tcl command dispatch hierarchy, end-to-end setup optimization algorithms, auxiliary repair engines, invariant contracts, and algorithmic evolution opportunities.

---

## 1. What Problem `rsz` Solves

### 1.1 Inputs and Outputs
The Resizer (`src/rsz`) is the post-placement and post-routing physical and timing optimization engine of OpenROAD. It operates directly on the core in-memory design database (`odb::dbDatabase`) coupled with the timing network (`sta::dbNetwork`, `sta::dbSta`).

- **Inputs**:
  - **Placed Design Database** (`.odb` or DEF format): Contains placed standard cells, fixed macros, I/O pads/pins, and physical net geometries. Cell instances possess assigned orientations, coordinates, and bounding boxes snapped to site rows (`odb::dbInst`, `odb::dbBTerm`, `odb::dbITerm`, `odb::dbNet`).
  - **Cell Timing and Functional Models** (Liberty `.lib` files): Contains cell-level timing tables (NLDM 2D lookup tables indexed by input slew and output capacitive load, or CCS/ECSM current waveforms), leakage and dynamic power tables, input pin capacitances ($C_{\text{pin}}$), and electrical design rule limits (`max_transition`, `max_capacitance`, `max_fanout`).
  - **Synopsys Design Constraints** (SDC): Defines clock domains, clock waveforms, clock uncertainties, input/output arrival delays, multicycle paths, false paths, and minimum/maximum path delay assertions.
  - **Process Technology Parameters and Parasitics**: Layer parameters specifying sheet resistance ($R_\square$) and unit capacitance ($C/\mu m$) across the metal stack (from `setRC.tcl` or LEF tech), used for FLUTE-derived Steiner tree estimation, or extracted detailed SPEF parasitics post-routing.
  - **Exclusion Lists**:
    - `dont_use` cell list: Specifies master cells that must never be instantiated as replacement drivers or repeaters (e.g., delay cells, clock buffers with excessive duty cycle distortion, or obsolete footprint variations).
    - `dont_touch` netlist assertions: Marks critical clock nets, reset trees, analog interfaces, or customer-defined hierarchical blocks as strictly read-only.
- **Outputs**:
  - Resized standard cells: Instances swapped to higher or lower drive strengths (`size_up`, `size_down`), or swapped across threshold-voltage offerings (`vt_swap`: LVT, NVT, HVT) without footprint alteration.
  - Buffered and re-buffered net topologies: Repeater buffer trees inserted along long high-resistance interconnects, load-splitting buffers separating critical from non-critical sinks, and cloned gates driving partitioned fanout branches.
  - Re-legalized cell placements: All relocated or resized standard cells legalized using OpenDP (`dpl::Opendp::legalCellPos (called from Resizer.cc:3165)`), maintaining zero overlaps and site alignment.
  - Closed or minimized setup/hold timing slacks ($WNS \ge 0, TNS \ge 0$) and eliminated electrical Design Rule Violations (DRVs) across all specified active analysis corners.

### 1.2 The Meaning of "Repair"
In OpenROAD physical synthesis, "repair" represents the progressive transformation of an unconstrained or failing physical netlist into an electrically viable, timing-closed implementation:
1. **Design Rule Violation (DRV) Repair (`repair_design`)**: Fixes violations of hard physical and electrical limits—ensuring signal transition times (`max_slew`), net capacitances (`max_capacitance`), and fanout counts (`max_fanout`) do not exceed library cell thresholds or wire length bounds (`max_wire_length`).
2. **Setup Timing Repair (`repair_timing -setup`)**: Advances signal transitions along worst-slack data paths so data arrives before the clock capture edge ($T_{\text{arrival}} \le T_{\text{required}}$), eliminating negative setup slack ($WNS \ge 0, TNS \ge 0$).
3. **Hold Timing Repair (`repair_timing -hold`)**: Delays data transitions on fast paths so new data does not race through and overwrite old data before the capture clock edge holds ($T_{\text{arrival}} \ge T_{\text{required}}$), achieved without degrading setup slack.

### 1.3 Why the Problem is NP-Hard and Heuristic
Simultaneous gate sizing, threshold-voltage assignment, and buffer insertion is NP-hard. In a modern standard-cell design with $N$ gates and $M$ library drive choices per gate, the discrete sizing search space alone is $\mathcal{O}(M^N)$. Furthermore:
- **Interconnect Coupling**: Changing the drive strength or input capacitance of gate $G_i$ alters both the load capacitance seen by its driver $G_{i-1}$ and the input slew delivered to its receivers $G_{i+1}$, shifting downstream delays across fanout cones.
- **Conflicting Multi-Objective Landscape**: Reducing propagation delay via cell sizing increases cell area and dynamic/leakage power, and risks creating downstream placement overlaps and hold-time race conditions.
Because exact combinatorial optimization is intractable, `rsz` implements sophisticated greedy heuristics, analytical delay approximations (Elmore and slew-bias models), dynamic programming buffer trees (van Ginneken / Lillis style), and iterative phase-based optimization policies.

---

## 2. Where `rsz` Sits in the ORFS Flow

In OpenROAD-flow-scripts (ORFS), `rsz` is invoked at multiple critical junctures across the physical implementation flow, orchestrated via Tcl helper scripts (`external/OpenROAD-flow-scripts/flow/scripts/`):

### 2.1 Post-Placement Optimization (`flow/scripts/resize.tcl`)
Invoked immediately after Global Placement (`3_3_place_gp.odb`):
- `estimate_parasitics -placement`: Estimates interconnect RC from placement coordinates using FLUTE-derived Steiner trees.
- `set_opt_config -set_early_sizing_cap_ratio`: Configures capacitance ratios if early sizing heuristics are activated.
- `replace_arith_modules` / `global_placement -incremental`: Optional logic-level arithmetic operator restructuring (`SWAP_ARITH_OPERATORS`).
- `repair_design_helper`: Executes `repair_design -verbose -max_wire_length ... -slew_margin ... -cap_margin ...` to clean electrical DRVs (slew and load caps) prior to full timing optimization.
- `repair_timing_helper`: If `ENABLE_PLACE_REPAIR_TIMING=1`, runs `repair_timing -setup -hold -verbose -repair_tns $TNS_END_PERCENT` under placement-estimated parasitics.
- `detailed_placement_helper`: Re-legalizes cells after buffer insertion and sizing before saving `3_4_place_resized.odb`.

### 2.2 Clock Tree Synthesis (`flow/scripts/cts.tcl`)
Invoked during clock synthesis (`3_place.odb` to `4_1_cts.odb`):
- `repair_clock_inverters`: Clones clock tree inverters directly adjacent to register clock inputs so downstream CTS does not attempt to buffer inverted clock lines.
- `clock_tree_synthesis`: Builds the clock tree.
- `detailed_placement_helper`: Legalizes clock buffer cells.
- `repair_timing_helper`: Post-CTS timing repair (`repair_timing -setup -hold`) running with real clock latency and propagated skew.
- `detailed_placement_helper` & `check_placement -placeable`: Final validation of layout legality.

### 2.3 Post-Global Routing Timing Optimization (`flow/scripts/global_route.tcl`)
Invoked after initial global routing:
- `repair_timing_helper`: Runs `repair_timing` using global-routing extracted parasitics (`estimate_parasitics -global_routing`).
- `global_route -start_incremental`: Reroutes nets modified by buffer insertions or cell swaps.
- `detailed_placement_helper`: Ensures no cell overlaps exist.
- Optional post-GRT WNS optimization: `repair_timing -setup -sequence "vt_swap reroute" -skip_last_gasp -repair_tns 0 -verbose`.
- `recover_power_helper`: If enabled, calls `recover_power` to downsize non-critical cells on paths with positive slack.

### 2.4 Detailed Helper Script Parameters (`flow/scripts/util.tcl`)
The `util.tcl` script encapsulates `rsz` invocation arguments via environment variables:
- `repair_timing_helper`:
  - `-setup_margin $::env(SETUP_SLACK_MARGIN)`: Artificial offset added to setup required times.
  - `-hold_margin $::env(HOLD_SLACK_MARGIN)`: Protection margin for hold required times.
  - `-sequence $::env(SETUP_MOVE_SEQUENCE)`: Custom ordered list of move types.
  - `-phases $::env(SETUP_REPAIR_PHASES)`: Policy phases (e.g. `PARALLEL_EVAL`, `WNS`, `TNS`).
  - `-repair_tns $::env(TNS_END_PERCENT)`: Percentage TNS reduction stopping condition.
  - Flags: `-skip_pin_swap`, `-skip_gate_cloning`, `-skip_buffer_removal`, `-skip_last_gasp`, `-skip_vt_swap`, `-skip_crit_vt_swap`, `-match_cell_footprint`, `-verbose`.
- `repair_design_helper`:
  - `-cap_margin $::env(CAP_MARGIN)`: Percentage capacitance margin (e.g. 10% = 0.1).
  - `-slew_margin $::env(SLEW_MARGIN)`: Percentage slew limit margin.
  - `-match_cell_footprint`: Restricts buffer/inverter selection to matching physical cell footprints.

---

## 3. The Resizer <-> Timer Loop

The resizer interacts with OpenSTA via the `sta::dbSta` and `sta::dbNetwork` layers.

```
+--------------------------------------------------------------------------+
|                          OpenROAD Resizer (rsz)                          |
|                                                                          |
|  +---------------------------+        +-------------------------------+  |
|  |   OptimizationPolicy      | -----> |   MoveGenerators & Moves      |  |
|  |   (WNS, TNS, PARALLEL)    |        |   (SizeUp, Buffer, Rebuffer)  |  |
|  +---------------------------+        +-------------------------------+  |
|               ^                                       |                  |
|               | queries arrivals/slacks               v applies ECO      |
|  +--------------------------------------------------------------------+  |
|  |             OpenSTA / dbSta In-Memory Incremental Timer            |  |
|  |                                                                    |  |
|  |   +-----------------------+           +------------------------+   |  |
|  |   | Graph & Levelizer     |           | GraphDelayCalc / Dcalc |   |  |
|  |   +-----------------------+           +------------------------+   |  |
|  |   +-----------------------+           +------------------------+   |  |
|  |   | Arrival / Required    | <-------> | Parasitics / RC Model  |   |  |
|  |   +-----------------------+           +------------------------+   |  |
|  +--------------------------------------------------------------------+  |
+--------------------------------------------------------------------------+
```

### 3.1 Parasitics Management (`est::EstimateParasitics`)
- **Initial Estimation**: `rsz` calls `estimate_parasitics -placement` (implemented in `est/src/EstimateParasitics.cc:estimateParasiticsPlacement`). This builds Steiner trees using the FLUTE package (`rsz::SteinerTree`), models wire segments, and annotates lumped or distributed $\pi$-model RC parasitics onto `sta::Parasitic` objects attached to each net.
- **Incremental Invalidation**: When a net topology is altered (e.g. buffer inserted or net split), `est::IncrementalParasiticsGuard` ensures parasitic networks on affected nets are marked dirty. Re-estimation updates delays only along touched nets.

### 3.2 Incremental Timing Queries
- **Graph Updates**: Moves modify OpenDB objects (`odb::dbInst`, `odb::dbITerm`, `odb::dbNet`). `dbStaCbk` callbacks notify OpenSTA to disconnect and reconnect graph edges.
- **Levelized Arrival/Required Updates**: Rather than re-timing the entire chip, OpenSTA performs incremental levelized timing updates:
  - `sta::Sta::findDelays()` recalculates gate delays across modified vertices.
  - `sta::Sta::updateTiming()` propagates arrival times forward from modified pins to downstream endpoints, and required times backward from endpoints.
  - `sta::Vertex::slack()` returns the difference between data required and arrival times ($T_{\text{required}} - T_{\text{arrival}}$).
- **Fast Estimation via `rsz::DelayEstimator`**: To avoid invoking OpenSTA's full incremental timer for every candidate move, `rsz::DelayEstimator` (`src/DelayEstimator.cc`) computes fast first-moment Elmore delay deltas and empirical slew-bias models (`src/DelayEstimatorCache`) to prescreen candidate moves before applying them.

### 3.3 Precise Function Call Flow Between `rsz` and `sta`
1. **Target Identification**:
   - `rsz::RepairTargetCollector::collectPinsByPathEndpoint` calls `sta::Sta::worstSlack()` and `sta::Sta::findPathEnds()`.
   - Iterates over `sta::PathEnd` objects to extract critical endpoints and slacks.
2. **Path Traversal**:
   - `sta::PathExpanded::PathExpanded()` unrolls the worst-slack path from endpoint backwards to startpoint.
   - For each timing edge, queries `sta::Edge::delay()`, `sta::PathExpanded::slew()`, and `sta::Vertex::arrival()`.
3. **Move Application & Timing Refresh**:
   - Resizer swaps master cell: `odb::dbInst::swapMaster()`.
   - `sta::dbSta::connectPin()` / `sta::dbSta::disconnectPin()` updates STA netlist connectivity.
   - `rsz::MoveCommitter::updateTimingForObserver()` triggers local graph delay recalculation via `sta::Sta::findDelays(vertex)`.
   - `sta::Sta::updateTiming()` updates arrivals along downstream transitive fanout cones.

---

## 4. Command Map

Every Tcl command declared in `src/Resizer.tcl` binds directly to C++ entry points in `src/Resizer.cc` via SWIG bindings:

| Tcl Command | C++ Entry Point | Core Subsystem Files | Purpose |
| :--- | :--- | :--- | :--- |
| `repair_design` | `Resizer::repairDesign()` | `RepairDesign.cc`, `PreChecks.cc`, `BufferedNet.cc` | Fixes max slew, max cap, max fanout, and long wires. |
| `repair_timing` | `Resizer::repairSetup()`, `Resizer::repairHold()`, `Resizer::recoverPower()` | `Optimizer.cc`, `policy/*`, `move/*`, `RepairHold.cc`, `RecoverPower.cc` | Main timing closure driver for setup, hold, and power recovery. |
| `repair_clock_nets` | `Resizer::repairClkNets()` | `RepairDesign.cc`, `BufferedNet.cc` | Inserts repeaters along high-fanout, high-capacitance clock nets pre-CTS. |
| `repair_clock_inverters` | `Resizer::repairClkInverters()` | `Resizer.cc:repairClkInverters` | Clones clock inverters close to register loads. |
| `repair_tie_fanout` | `Resizer::repairTieFanout()` | `Resizer.cc:repairTieFanout` | Disconnects high-fanout tie-high/tie-low nets and instantiates local tie cells. |
| `buffer_ports` | `Resizer::bufferInputs()`, `Resizer::bufferOutputs()` | `Resizer.cc` | Inserts isolation buffers on top-level input and output design ports. |
| `remove_buffers` | `Resizer::removeBuffers()` | `Resizer.cc`, `move/UnbufferGenerator.cc` | Deletes unneeded repeater buffers and restores direct net connections. |
| `balance_row_usage` | `Resizer::balanceRowUsage()` | `Resizer.cc` | Redistributes standard cells across rows to relieve localized placement density. |
| `set_opt_config` | `set_opt_config` (Resizer.tcl:699) -> OptimizationPolicyConfig | `OptimizationPolicyConfig.cc` | Sets sizing area/leakage limits, VT/site preservation, and cap ratios. |
| `report_design_area` | `Resizer::designArea()`, `Resizer::utilization()` | `Resizer.cc` | Reports total cell area ($\mu m^2$) and die core utilization percentage. |
| `report_floating_nets` | `Resizer::findFloatingNets()` | `Resizer.cc` | Audits design for unconnected floating nets and pins. |
| `report_overdriven_nets` | `Resizer::findOverdrivenNets()` | `Resizer.cc` | Detects nets driven by multiple conflicting output drivers. |
| `report_long_wires` | `Resizer::reportLongWires()` | `Resizer.cc` | Reports nets exceeding length thresholds based on bounding box or Steiner estimates. |

### 4.1 Internal Call Hierarchy from Tcl to Engine
```
repair_timing (Tcl)
  --> rsz::repair_setup (C++ SWIG binding in Resizer.i)
        --> Resizer::repairSetup (Resizer.cc:5401)
              --> rsz::Optimizer::configure (Optimizer.cc:44)
              --> rsz::Optimizer::run (Optimizer.cc:161)
                    --> Optimizer::makePolicyForPhase (Optimizer.cc:74)
                          --> SetupLegacyPolicy / SetupWnsPolicy / SetupParallelEvalPolicy
                    --> OptimizationPolicy::iterate()
                          --> RepairTargetCollector::collectPinsByPathEndpoint (RepairTargetCollector.cc)
                          --> MoveGenerator::generate (move/*Generator.cc)
                          --> DelayEstimator::estimate (DelayEstimator.cc)
                          --> MoveCommitter::commitTrackedMoves (MoveCommitter.cc)
                                --> MoveTracker::beginJournal (MoveTracker.cc)
                                --> dpl::Opendp::legalCellPos (called from Resizer.cc:3165)
```

---

## 5. The `repair_timing -setup` Algorithm End to End

The core setup timing repair algorithm in `rsz::Optimizer` (`src/Optimizer.cc`) executes through a coordinated pipeline of policy objects, candidate move generators, and transactional committers.

### 5.1 Architecture & Flow

```
+--------------------------------------------------------------------------+
|                            rsz::Optimizer::run()                         |
|                                                                          |
| 1. Initialize Preamble: resizer_.runRepairSetupPreamble();               |
| 2. Incremental Parasitics: est::IncrementalParasiticsGuard;              |
| 3. Parse Phase Tokens: LEGACY, WNS, TNS, PARALLEL_EVAL, etc.             |
|                                                                          |
| For each phase in pipeline:                                              |
|   +--------------------------------------------------------------------+ |
|   | OptimizationPolicy::start()                                        | |
|   | while (!OptimizationPolicy::converged()):                          | |
|   |   OptimizationPolicy::iterate()                                    | |
|   |     a. Collect violating targets: RepairTargetCollector            | |
|   |     b. Generate candidates: MoveGenerator (SizeUp, Buffer, etc.)   | |
|   |     c. Rank moves via fast DelayEstimator                          | |
|   |     d. Speculative apply -> Legalize (OpenDP) -> Sta::updateTiming | |
|   |     e. Check acceptance: if slack improves -> Commit               | |
|   |                          else -> MoveTracker::restore (Rollback)   | |
|   | OptimizationPolicy::finish()                                       | |
|   +--------------------------------------------------------------------+ |
| 4. Final Reporting: ProgressReporter::printFinal();                      |
+--------------------------------------------------------------------------+
```

### 5.2 End-to-End Pseudo-Code with Real Function Names

```python
def Optimizer_run(config):
    # Optimizer.cc:161
    resizer.runRepairSetupPreamble()
    committer.init()
    parasitics_guard = est.IncrementalParasiticsGuard(resizer.estimateParasitics())
    
    # Resolve phase pipeline (e.g. WNS, TNS, LAST_GASP, CRIT_VT_SWAP)
    # Optimizer.cc:184
    phases = appendImplicitCritVtSwapForLegacyPhases(parseTokens(config.phases))
    setup_context = RepairSetupContext(resizer)
    
    for phase_index, phase_name in enumerate(phases):
        # Optimizer.cc:204
        policy = makePolicyForPhase(phase_name, setup_context)
        if not policy.start():
            break
            
        while not policy.converged():
            # policy/SetupLegacyBase.cc:iterate()
            
            # 1. Target Collection
            # RepairTargetCollector.cc:collectPinsByPathEndpoint()
            targets = RepairTargetCollector(resizer)
            targets.init(config.setup_slack_margin, path_group)
            violating_endpoints = targets.getViolatingPins()
            if violating_endpoints.empty():
                break
                
            # Check TNS stopping condition
            # SetupLegacyBase.cc:terminateProgress()
            if targets.getTns() >= initial_tns * config.repair_tns_end_percent:
                break
                
            # 2. Iterate across critical paths
            for endpoint in violating_endpoints:
                if policy.endpointBudgetExceeded():
                    break
                
                # Expand critical path back from endpoint
                # PathExpanded.cc:PathExpanded()
                expanded_path = PathExpanded(endpoint, sta)
                driver_pins = targets.collectExpandedPathDriverPins(expanded_path)
                
                # 3. Candidate Generation across active move generators
                candidate_moves = []
                for generator in policy.activeMoveGenerators():
                    # MoveGenerator.cc:generate()
                    # Invokes: SizeUpGenerator, BufferGenerator, VtSwapGenerator,
                    #          SwapPinsGenerator, SplitLoadGenerator, CloneGenerator
                    candidates = generator.generate(driver_pins, expanded_path, setup_context)
                    candidate_moves.extend(candidates)
                    
                # 4. Fast Heuristic Prescreening via DelayEstimator
                # DelayEstimator.cc:estimate()
                scored_moves = []
                for candidate in candidate_moves:
                    gain = delay_estimator.estimateGain(candidate)
                    if gain > 0:
                        scored_moves.append((gain, candidate))
                sort_descending_by_gain(scored_moves)
                
                # 5. Speculative Move Execution and Journaling
                for gain, candidate in scored_moves:
                    # MoveCommitter.cc:commit()
                    committer.beginJournal()  # MoveTracker::beginJournal()
                    success = committer.applyMove(candidate)
                    
                    if success:
                        # Re-legalize placed cells in local window
                        # dpl::Opendp::legalCellPos
                        resizer.legalCellPos(candidate.instance())
                        
                        # Incremental timer recalculation
                        # Sta.cc:updateTiming()
                        sta.updateTiming()
                        new_slack = sta.pinSlack(endpoint)
                        
                        # 6. Acceptance Criteria Test
                        # policy/SetupWnsPolicy.cc:acceptsMove()
                        if policy.acceptsMove(candidate, old_slack, new_slack):
                            committer.commitTrackedMoves()
                            policy.recordAcceptedMove(candidate)
                            break  # Accepted beneficial move; proceed to next endpoint
                        else:
                            # Revert netlist and placement
                            committer.abortJournalScope()  # MoveTracker::restore()
                    else:
                        committer.abortJournalScope()
                        
            policy.stepPass()
            
        policy.finish()
        
    # Optimizer.cc:227
    reportRunResult(setup_context)
```

---

## 6. The Other Algorithms

### 6.1 Design Rule Violation Repair (`rsz::RepairDesign`)
- **Input**: Placed netlist with unconstrained or DRC-violating slews, load capacitances, and wire lengths.
- **Heuristic**:
  - `PreChecks::checkSlewLimit`: Computes driver output transition time against `max_slew`.
  - `RepairDesign::needRepairCap`: Compares total lumped load capacitance against `max_capacitance`.
  - If violated, searches library buffer table for minimum-sized buffer satisfying slew/cap bounds (`findBufferUnderSlew`).
  - Inserts buffers along Steiner wire branches (`repairDriverSlew`) or performs load splitting.
- **Output**: Netlist free of maximum transition, capacitance, and fanout violations.
- **Known Weaknesses**: Greedy top-down insertion can over-buffer short high-fanout nets, causing placement congestion and area inflation.

### 6.2 Hold Timing Repair (`rsz::RepairHold`)
- **Input**: Post-CTS or post-route design with negative hold slack ($WNS_{\text{hold}} < 0$).
- **Heuristic**:
  - Collects violating endpoints sorted from worst to least negative hold slack (`RepairHold::findHoldViolations + RepairHold::repairHoldPass`).
  - Identifies candidate insertion points on non-critical data paths.
  - Evaluates inserting delay buffers (`insertHoldBuffer`) while checking setup slack guard bands (`setup_margin`).
  - Rejects buffer additions that degrade setup slack beyond allowable margins.
- **Output**: Hold-clean design with minimal setup slack penalty.
- **Known Weaknesses**: In dense layouts, hold buffers placed without global congestion awareness can create unresolvable routing hotspots.

### 6.3 Rebuffering & Van Ginneken Trees (`rsz::Rebuffer` & `rsz::BufferedNet`)
- **Input**: High-fanout or long-distance critical net with existing sub-optimal repeaters.
- **Heuristic**:
  - `removeBuffers`: Strips existing buffer trees back to original driver and sinks.
  - `BufferedNet`: Constructs an optimal routing Steiner tree using FLUTE.
  - Evaluates candidate buffer locations at Steiner junctions and along wire segments.
  - Computes $(C, T_{\text{required}})$ trade-off curves bottom-up from sinks, pruning dominated configurations.
  - Selects the tree topology maximizing driver slack.
- **Output**: Newly buffered net with minimum Elmore propagation delay.
- **Known Weaknesses**: Static wire RC assumptions without layer assignment can deviate significantly from post-detailed route parasitics.

### 6.4 Gate Cloning (`rsz::CloneGenerator`)
- **Input**: High-fanout driver on a timing-critical path with spatially distributed loads.
- **Heuristic**: Instantiates a duplicate copy of the driver gate (`odb::dbInst::create`), partitions sink loads geometrically, and re-connects half the sinks to the clone.
- **Output**: Two parallel drivers with halved capacitive load.
- **Known Weaknesses**: Increases local cell area and pin density; sub-optimal partitioning can worsen routing wirelength.

### 6.5 Split Load (`rsz::SplitLoadGenerator`)
- **Input**: Gate driving both timing-critical sinks and non-critical side-loads.
- **Heuristic**: Inserts an isolation buffer between the driver and the non-critical sinks, removing side-load capacitance from the critical path.
- **Output**: Reduced effective capacitance on the critical net.
- **Known Weaknesses**: Adds extra buffer cell delay to side paths, potentially converting them into new critical paths.

### 6.6 Size Down Fanout (`rsz::SizeDownFanoutGenerator`)
- **Input**: Driver with side-branch fanout cells possessing positive timing slack.
- **Heuristic**: Downsizes side-load cells to smaller footprint equivalents, decreasing their input pin capacitance ($C_{\text{in}}$).
- **Output**: Lightened total load capacitance on the driver, speeding up the critical transition.
- **Known Weaknesses**: Degrades slew on the downsized side paths, risking secondary DRV violations.

### 6.7 VT Swapping (`rsz::VtSwapGenerator` & `SetupCritVtSwapPolicy`)
- **Input**: Critical paths with cells available in multiple threshold voltage libraries (e.g. LVT, NVT, HVT).
- **Heuristic**: Swaps standard or high-VT cells on negative-slack paths to low-VT equivalents possessing higher drive current without changing cell area or placement footprint.
- **Output**: Significant path delay reduction with zero placement disturbance.
- **Known Weaknesses**: Causes super-linear increases in subthreshold leakage power consumption.

### 6.8 Pin Swapping (`rsz::SwapPinsGenerator`)
- **Input**: Multi-input gates (e.g. NAND2, NOR2, AOI21) where inputs exhibit asymmetric internal pin delays.
- **Heuristic**: Queries `SwapPinsEquivalence` to determine logical pin symmetries. Permutes inputs so the critical timing signal connects to the fastest internal stage.
- **Output**: Improved delay with zero area, placement, or power overhead.
- **Known Weaknesses**: Limited applicability (only feasible on symmetric logic pins).

### 6.9 Power Recovery (`rsz::RecoverPower`)
- **Input**: Timing-closed design with positive setup slacks.
- **Heuristic**: Traverses cells in reverse topological order. Iteratively downsizes cells or swaps to higher-VT alternatives as long as path slacks remain positive (`slack >= recover_power_slack_margin`).
- **Output**: Substantially reduced dynamic and leakage power.
- **Known Weaknesses**: Consumes timing margins needed to absorb downstream detailed routing parasitics.

### 6.10 Sequential Timing & Skew Budgeting (`rsz::SkewBudget`)
- **Input**: Sequential loops bounded by clock skew tolerances.
- **Heuristic**: Computes intentional clock skew budgets (`computeSkewBudget`) to borrow time from adjacent positive-slack cycles, shifting clock arrival targets at registers.
- **Output**: Redistributed timing slack across sequential pipelines.
- **Known Weaknesses**: Highly sensitive to post-CTS clock tree variations and cross-corner OCV/PVT shifts.

---

## 7. Data Structures and Invariants

To prevent catastrophic database corruption or invalid optimization states, every algorithm in `rsz` must adhere to strict invariant contracts:

1. **Transactional Journaling (`rsz::MoveTracker` / `rsz::MoveCommitter`)**:
   - Every modification to `odb::dbDatabase` (pin disconnection, cell resize, instance creation/deletion) must be registered in the active `MoveTracker` journal.
   - If an evaluation fails or slacks degrade, `committer.abortJournalScope()` must roll back the database to the exact pre-move state without leaving orphan nets or phantom terminals.
2. **`dont_touch` and `dont_use` Sanctity**:
   - Instances, nets, or ports marked with `dont_touch` must never be sized, disconnected, buffered, or deleted.
   - Masters marked with `dont_use` must never be instantiated as replacement cells or repeater buffers.
3. **OpenDB and OpenSTA Synchronicity**:
   - The topological representation in `sta::dbNetwork` must remain strictly synchronized with the physical representation in `odb::dbBlock`. Any call modifying OpenDB structures must trigger corresponding `dbStaCbk` updates.
4. **Placement Legality & Non-Overlapping Invariants**:
   - Newly inserted or upsized cells must be placed within core boundaries and snapped to valid site rows.
   - Overlaps introduced during sizing must be legalizable via OpenDP (`opendp::checkPlacement`).
5. **Parasitics Validity**:
   - Structural net mutations invalidate existing parasitics. The incremental parasitic cache (`est::IncrementalParasiticsGuard`) must be notified to prevent evaluating stale RC constants.
6. **Execution Determinism**:
   - Move generation, target sorting, and tie-breaking must use deterministic criteria (e.g., cell IDs or canonical hierarchical pin names) rather than memory pointer addresses.

---

## 8. What a Better Algorithm Could Change

Coding and planning agents seeking to evolve `src/rsz` can target fundamental algorithmic paradigms rather than superficial constant tuning:

| Subsystem | File & Function | Current Limitation | Algorithmic Evolution Opportunity |
| :--- | :--- | :--- | :--- |
| **Global Path Selection** | `policy/BatchSelector.cc:selectBatch` | Greedy single-path extraction; ignores overlapping path interactions. | **Hypergraph Centrality & Cut Pruning**: Select disjoint target path bundles simultaneously using max-flow min-cut or spectral clustering. |
| **Slack Budget Allocation** | `policy/SetupWnsPolicy.cc:acceptsMove` | Greedy single-move acceptance based solely on local endpoint delta. | **Global Zero-Slack / Lagrangian Relaxation**: Distribute explicit delay reduction budgets ($\Delta D$) globally across logic stages. |
| **Candidate Sizing Search** | `move/SizeUpGenerator.cc:generate` | Tests nearest drive strengths sequentially from single library family. | **Multi-Stage Sizing & Sensitivity Heuristics**: Multi-variable TILOS-style continuous optimization mapped to nearest discrete cells. |
| **Buffer Tree Topology** | `BufferedNet.cc:buildSteinerTree` | Static FLUTE Steiner tree; unaware of timing criticality during tree creation. | **Timing-Driven Steiner Routing**: Construct A-Tree or P-Tree topologies that bias buffer insertion directly toward critical sinks. |
| **Coupled Move Generation** | `policy/OptimizationPolicy.cc:buildMoveGenerators` | Evaluates move types independently (size up, then buffer, then pin swap). | **Composite Move Operators**: Simultaneously execute coupled moves (e.g., upsize driver + downsize side-loads + swap critical pins in one atomic transaction). |
| **Analytical Delay Models** | `DelayEstimator.cc:estimate` | Simplified first-order Elmore delay approximation. | **Higher-Order Moment Matching**: Arnoldi or D2M delay modeling inside the rapid prescreener to evaluate deep sub-micron RC interconnects accurately. |
