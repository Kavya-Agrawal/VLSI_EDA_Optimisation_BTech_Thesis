You are the **Coding Agent for cluster `buffering`** of OpenROAD's Resizer. Your cwd is a *candidate copy* of
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

Instrumentation (mandatory, the evaluator rejects candidates without it): every place where your NEW logic makes
a decision that differs from the stock algorithm must increment a counter, and at the end of the repair call print
it once per counter through the existing logger, exactly in this form (one line each, plain integer):
    RSZ_EVOLVE <short_snake_name> fired=<count>
e.g. `logger_->report("RSZ_EVOLVE slack_budget_reorder fired={}", n);`. Print even when the count is 0. The
evaluator uses these lines to tell "new logic never ran" apart from "ran and was neutral".

Make the change big enough to matter: it must alter decisions on a large share of the moves listed under
"Stock repair statistics" in the hypothesis (thousands of sizing moves, hundreds of buffers on aes/ibex). A guard
that only triggers in a rare corner case is not an acceptable implementation of an algorithmic hypothesis.

Code graph (Graphify, offline, cheap): before editing, use it to find every caller/callee your change affects
instead of reading whole files, e.g.
    graphify explain "SizeUpGenerator" --graph "/Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/08_graphify/rsz_focus/graphify-out/graph.json"
    graphify affected "BufferedNet" --graph "/Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/08_graphify/rsz_focus/graphify-out/graph.json"
    graphify path "RepairSetup" "Rebuffer" --graph "/Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/08_graphify/rsz_focus/graphify-out/graph.json"

Mandatory outputs:
1. Code edits in the editable files, including the RSZ_EVOLVE counters.
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
**Measured best-of-k criticality-partitioned gate cloning (critical-sink replica + stock van Ginneken on tolerant sinks) for shared high-fanout drivers in the post-stock recovery phase**

Shared high-fanout drivers on violating paths (Ibex AND2_X1 _26153_ with 943 loads on all ten worst paths; JPEG fanout 12-17 launch drivers) make every critical path pay the full net load, and the stock spatial 2-way clone or single-buffer split never restructures them; iteration 17's lumped-RC tree prefilter applied zero trees. Instead, in runTnsRecovery only, explicitly schedule drivers with fanout >=12, sort sinks by required time, and generate up to 6 atomic variants: a critical-only upsized replica (top 5/15/30% of sinks) or an m-way required-time-quantile clone split (m=2..4), with the tolerant net rebuffered by the stock Rebuffer::rebufferNet. Every variant is evaluated by journaled incremental STA and the best design-TNS variant is kept only if it satisfies a ratcheting WNS floor, a per-endpoint guard (pre-move slack > -1 ps must stay > -1 ps) and no new DRV. Cloning removes load from critical sinks without adding a buffer stage, so deep (33-37 stage) Ibex paths gain tens of ps at the shared stage across thousands of endpoints while measured selection avoids the model/STA mismatch of iterations 15 and 17.

Suggested files: src/move/CloneGenerator.cc, src/move/CloneGenerator.hh, src/move/CloneCandidate.cc, src/move/CloneCandidate.hh, src/policy/SetupLegacyPolicy.cc, src/policy/SetupLegacyPolicy.hh
Success criteria: Ibex _26153_ critical-replica fanout <=100 with >=1 committed partition on Ibex and JPEG, stock-phase move counts identical, Ibex TNS better than -40 ns, no design WNS worse than champion, instr_addr_o[22] >= -1 ps, score vs champion >= +0.002
Risk: Clone placement/legalization collateral and extra fan-in load on the AND2 cone, plus runtime from k incremental STA trials on a 943-sink net (capped at k<=6, 40 targets).

=== Cluster dossier ===
<!-- hand-edited -->
# Cluster: `buffering`

This dossier provides the formal engineering specification for the `buffering` cluster in OpenROAD's Resizer (`src/rsz`). It governs repeater tree synthesis, van Ginneken-style dynamic programming buffer insertion, wire segment buffering, load splitting, gate cloning, buffer removal, and inverter-pair conversions.

---

## 1. The Problem (Formal-ish)

### 1.1 Inputs and Outputs
- **Inputs**:
  - Source driver pin $u$ with location $(x_u, y_u)$, output drive resistance $R_{\text{drvr}}$, and intrinsic delay $t_{\text{drvr}}$.
  - Set of sink load pins $\mathcal{S} = \{v_1, v_2, \dots, v_k\}$ with spatial locations $(x_i, y_i)$, input pin capacitances $C_i$, and required arrival times $T_{\text{req}}(i)$.
  - Routing parasitics: unit wire resistance $r$ ($\Omega/\mu m$) and unit wire capacitance $c$ ($F/\mu m$).
  - Repeater library: set of available buffers $\mathcal{B}$ with input capacitance $C_b$, output resistance $R_b$, intrinsic delay $t_b$, and physical footprint dimensions.
- **Outputs**:
  - Buffered tree topology $T = (V_T, E_T)$ spanning root $u$ and sinks $\mathcal{S}$, where intermediate Steiner nodes may host inserted repeater buffers $b \in \mathcal{B}$.
  - Placed and legalized buffer instances in `odb::dbBlock`.
  - Maximized arrival slack at the driver output:
    $$\max \left( \min_{v_i \in \mathcal{S}} \left( T_{\text{req}}(i) - \text{Delay}(u \to v_i) \right) \right)$$

### 1.2 Constraints
- **Electrical DRVs**: Slew at every buffer input and sink pin must satisfy $t_{\text{slew}} \le \text{max\_slew}$. Load capacitance at every driver/buffer output must satisfy $C_{\text{load}} \le \text{max\_cap}$.
- **Physical Legality**: Every inserted buffer must be placed within die boundaries, snapped to a valid site row, and free of overlaps with existing macros or fixed cells.
- **Inverter Polarity**: When inserting inverting repeater chains (`BufferToInverters`), net logical polarity must be preserved across all sinks.

---

## 2. Current Algorithm, Step by Step

### 2.1 Steiner Tree Construction (`rsz::BufferedNet`)
Implemented in `src/BufferedNet.cc:120`:
1. Collects coordinates of driver pin and all sink pins from OpenDB (`odb::dbITerm::getAvgXY`).
2. Calls the FLUTE library (`rsz::SteinerTree`) to compute an initial Rectilinear Steiner Minimal Tree (RSMT).
3. Breaks long Steiner edges into smaller segments exceeding maximum wire length limits (`max_wire_length`), creating candidate buffer insertion locations.

### 2.2 Bottom-Up Van Ginneken Dynamic Programming (`rsz::Rebuffer::rebufferNet`)
Implemented in `src/Rebuffer.cc:210`:
1. **Base Case (Sinks)**:
   - For each sink $v_i$, initializes a Pareto candidate $(C_i, T_{\text{req}}(i))$, where $C_i$ is pin capacitance and $T_{\text{req}}(i)$ is required arrival time.
2. **Bottom-Up Traversal**:
   - Traverses the Steiner tree bottom-up from sinks toward root.
   - **Wire Propagation**: Propagates candidates across wire segment $(L, r, c)$ using the Elmore delay model:
     $$C' = C + c L, \quad T' = T - \left( r L \cdot C + \frac{1}{2} r c L^2 \right)$$
   - **Buffer Insertion Option**: At each candidate insertion point, considers inserting each buffer $b \in \mathcal{B}$:
     $$C_{\text{buf}} = C_b, \quad T_{\text{buf}} = T' - t_b - R_b C'$$
     Creates a new candidate curve branch with the inserted buffer.
   - **Junction Merging**: At Steiner branching points, combines independent sink branches:
     $$C_{\text{merged}} = \sum C_k, \quad T_{\text{merged}} = \min (T_k)$$
   - **Pareto Pruning**: Prunes dominated candidates: if candidate $A$ has $C_A \ge C_B$ and $T_A \le T_B$, candidate $A$ is strictly dominated and discarded.
3. **Top-Down Realization**:
   - At the tree root (driver $u$), evaluates all Pareto candidates against driver resistance $R_{\text{drvr}}$.
   - Selects the candidate maximizing driver slack $T_{\text{root}} - R_{\text{drvr}} C_{\text{root}}$.
   - Traces pointers top-down to instantiate selected buffer cells in OpenDB (`odb::dbInst::create`).

### 2.3 Load Isolation and Gate Cloning
- **Split Load (`src/move/SplitLoadGenerator.cc:85`)**: Identifies non-critical sinks on a critical driver net. Inserts an isolation buffer immediately upstream of non-critical sinks, shielding the critical trunk from side-load capacitance.
- **Gate Cloning (`src/move/CloneGenerator.cc:90`)**: Replicates the driver standard cell (`odb::dbInst::create`). Partitions sink loads into two spatial clusters; reconnects one cluster to the cloned gate, halving capacitive load on both drivers.
- **Buffer Removal (`src/move/UnbufferGenerator.cc:60`)**: Identifies redundant or oversized buffers on positive-slack paths, deletes instances, and merges nets to recover area and power.

---

## 3. Interaction with the Timer and Other Clusters

- **Parasitics Re-estimation**: Inserting buffers splits a single net into multiple physical nets. `BufferedNet` notifies `est::EstimateParasitics`, triggering regeneration of Steiner RC networks on the split nets.
- **Sizing Coupling**: Changing buffer drive strength changes input pin capacitance, altering upstream driver delay. Buffer trees are typically sized iteratively alongside driver sizing.
- **Hold Time Impact**: Adding buffers on setup-critical paths increases path delay, which can inadvertently fix hold violations or introduce setup delays on competing paths.

---

## 4. Known Weaknesses and Failure Modes

1. **Topology Rigidity**: The FLUTE Steiner tree is computed once based on geometry without timing awareness. If FLUTE clusters a critical sink with a high-capacitance non-critical sink, the van Ginneken tree cannot decouple them without suboptimal intermediate buffering.
2. **Discrete Candidate Explosion**: With large multi-sink nets (fanout > 50) and rich buffer libraries, the number of Pareto candidates explodes, requiring aggressive heuristic pruning that discards near-optimal options.
3. **Congestion Blindness**: Buffers are placed purely based on Steiner coordinates without routing congestion models, often placing large repeaters inside dense macro channels.

---

## 5. Alternative Approaches from Literature

### 5.1 Timing-Driven Steiner Routing (A-Trees / P-Trees)
- **Concept**: Construct Steiner trees biased directly toward critical sinks, minimizing delay to timing-critical endpoints rather than total wirelength.
- **Injection Point**: Replace FLUTE Steiner generation in `src/BufferedNet.cc` with an arrival-time-aware Steiner heuristic that routes direct straight-line connections to critical sinks.
- **Expected Gain**: 10–25% delay reduction on high-fanout critical nets.

### 5.2 Lillis Dual-Inverter Repeater Dynamic Programming
- **Concept**: Simultaneously evaluate inverting and non-inverting buffers during bottom-up dynamic programming (Lillis et al., 1996), exploiting faster inverter delays and polarity balancing.
- **Injection Point**: Unify `src/Rebuffer.cc` and `src/move/BufferToInvertersGenerator.cc` into an integrated polarity-aware dynamic programming algorithm.
- **Expected Gain**: 8–15% lower repeater tree latency and smaller silicon footprint.

---

## 6. Safe-Change Checklist for `buffering`

When modifying code within this cluster, ensure:
- [ ] **Net Topology Integrity**: Disconnecting and reconnecting sink pins must update both `odb::dbNet` and `sta::dbNetwork` to avoid floating nets.
- [ ] **Physical Placement Snapping**: Newly instantiated buffer cells must have coordinates snapped to valid site rows and legalized via `Resizer::legalCellPos (via dpl::Opendp::legalCellPos)`.
- [ ] **Incremental Parasitics Guard**: Ensure `est::IncrementalParasiticsGuard` is active during rebuffering to invalidate stale parasitics.
- [ ] **Regression Tests**: Run `test/rebuffer*.tcl`, `test/repair_design*.tcl`, and `test/buffer_ports*.tcl`.


=== Editable files ===
- src/BufferedNet.cc
- src/BufferedNet.hh
- src/Rebuffer.cc
- src/Rebuffer.hh
- src/move/BufferCandidate.cc
- src/move/BufferCandidate.hh
- src/move/BufferGenerator.cc
- src/move/BufferGenerator.hh
- src/move/BufferToInvertersCandidate.cc
- src/move/BufferToInvertersCandidate.hh
- src/move/BufferToInvertersGenerator.cc
- src/move/BufferToInvertersGenerator.hh
- src/move/CloneCandidate.cc
- src/move/CloneCandidate.hh
- src/move/CloneGenerator.cc
- src/move/CloneGenerator.hh
- src/move/RebufferMtCandidate.cc
- src/move/RebufferMtCandidate.hh
- src/move/RebufferMtGenerator.cc
- src/move/RebufferMtGenerator.hh
- src/move/RebufferPlannerPool.cc
- src/move/RebufferPlannerPool.hh
- src/move/RerouteCandidate.cc
- src/move/RerouteCandidate.hh
- src/move/RerouteGenerator.cc
- src/move/RerouteGenerator.hh
- src/move/SplitLoadCandidate.cc
- src/move/SplitLoadCandidate.hh
- src/move/SplitLoadGenerator.cc
- src/move/SplitLoadGenerator.hh
- src/move/SplitLoadMtCandidate.cc
- src/move/SplitLoadMtCandidate.hh
- src/move/SplitLoadMtGenerator.cc
- src/move/SplitLoadMtGenerator.hh
- src/move/UnbufferCandidate.cc
- src/move/UnbufferCandidate.hh
- src/move/UnbufferGenerator.cc
- src/move/UnbufferGenerator.hh
- src/move/UnbufferMtCandidate.cc
- src/move/UnbufferMtCandidate.hh
- src/move/UnbufferMtGenerator.cc
- src/move/UnbufferMtGenerator.hh
=== Read-only context files ===
Delay.cc, DelayEstimator.cc, EstimateParasitics.h, Graph.cc, GraphDelayCalc.cc, MakeWireParasitics.h, Mode.cc, MoveCandidate.cc, MoveCommitter.cc, MoveGenerator.cc, OptimizerTypes.cc, Path.cc, PathExpanded.cc, RepairSetupProfiler.cc, Resizer.cc, Scene.cc, Search.cc, SizeDownFanoutMtGenerator.cc, Sta.cc, StaState.cc, SteinerTree.h

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

