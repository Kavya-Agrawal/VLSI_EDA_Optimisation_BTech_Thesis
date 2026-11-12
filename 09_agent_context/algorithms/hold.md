<!-- hand-edited -->
# Cluster: `hold` (Hold Timing Repair)

This dossier provides the formal engineering specification for the `hold` cluster in OpenROAD's Resizer (`src/rsz`). It governs the resolution of minimum path delay and hold-time race conditions by inserting delay buffers on fast timing paths while strictly protecting setup timing slacks.

---

## 1. The Problem (Formal-ish)

### 1.1 Inputs and Outputs
- **Inputs**:
  - Post-CTS or post-route design database with extracted clock skew and latency (`odb::dbBlock`, `sta::dbSta`).
  - Active hold timing constraints across all flip-flops and latches:
    $$s_{\text{hold}}(p) = T_{\text{arrival}}(p) - T_{\text{required\_hold}}(p) < 0$$
  - User safety margins: `-hold_margin` (target positive hold buffer) and `-setup_margin` (maximum allowed setup degradation).
- **Outputs**:
  - Inserted delay buffers along fast data paths that eliminate hold violations ($s_{\text{hold}}(p) \ge 0$) without creating new setup timing violations ($s_{\text{setup}}(p) \ge 0$).

---

## 2. Current Algorithm, Step by Step

### 2.1 Hold Repair Traversal (`rsz::RepairHold::repairHold`)
Implemented in `src/RepairHold.cc:120`:
1. **Target Identification**:
   - Calls `sta::Sta::findPathEnds` targeting minimum path delay (`sta::MinMax::min()`).
   - Filters endpoints where hold slack $s_{\text{hold}} < \text{hold\_margin}$.
   - Sorts endpoints by hold slack ascending (worst hold violation first).
2. **Buffer Candidate Selection**:
   - For each violating endpoint, traces the combinational data path back from the capture register toward the launch register.
   - Evaluates available delay buffer cells in the library, prioritizing buffers characterized with high intrinsic delay and low area footprint.
3. **Setup Slack Margin Guard Banding**:
   - Before inserting a hold buffer, queries current setup slack on the path:
     $$s_{\text{avail}} = s_{\text{setup}}(p) - \text{setup\_margin}$$
   - If $s_{\text{avail}} \le 0$, buffer insertion is rejected to prevent turning a hold violation into a fatal setup violation.
4. **Buffer Insertion and Placement**:
   - Inserts the buffer into OpenDB (`odb::dbInst::create`), reconnects net wiring, and places the cell close to the capture register to minimize physical wire displacement.
   - Legalizes the buffer via OpenDP (`dpl::Opendp::legalCellPos (called from Resizer.cc:3165)`).

---

## 3. Interaction with the Timer and Other Clusters

- **CRPR (Clock Reconvergence Pessimism Removal)**:
  - During hold repair, clock reconvergence pessimism removal is critical; artificial clock tree skews between launch and capture registers can trigger false hold repairs. `repair_timing` manages CRPR state via `sta::set_crpr_enabled`.
- **Setup-Hold Balance**: Setup repair speeds up paths (reducing delay), while hold repair slows down paths (increasing delay). They act as antagonistic optimization forces.

---

## 4. Known Weaknesses and Failure Modes

1. **Ping-Pong Oscillations**: Sizing up a gate to fix setup slack on path $A$ accelerates an overlapping path $B$, creating a new hold violation. Repairing hold on path $B$ subsequently degrades setup on path $A$.
2. **Buffer Bloat**: In dense multi-corner flows (e.g. fast-fast vs. slow-slow corners), excessive hold buffers are inserted, inflating total chip leakage power and routing congestion.

---

## 5. Alternative Approaches from Literature

### 5.1 Joint Setup-Hold Lagrangian Formulation
- **Concept**: Concurrently bound both setup and hold delay equations inside a unified multi-objective multiplier formulation, preventing oscillatory repair loops.
- **Injection Point**: Implement dual-multiplier tracking in `src/policy/GlobalSizingPolicy.cc` that balances minimum and maximum delay constraints simultaneously.

---

## 6. Safe-Change Checklist for `hold`

When modifying code within this cluster, ensure:
- [ ] **Setup Violation Invariant**: Never commit a hold buffer that reduces setup slack below the user-specified `-setup_margin`.
- [ ] **Placement Legality**: Ensure all inserted hold buffers are snapped to site rows and legalized.
- [ ] **Regression Tests**: Run `test/repair_hold*.tcl` (specifically `repair_hold1.tcl` through `repair_hold15.tcl`).
