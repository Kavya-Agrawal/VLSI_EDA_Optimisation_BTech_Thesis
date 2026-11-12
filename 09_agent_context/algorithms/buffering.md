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
