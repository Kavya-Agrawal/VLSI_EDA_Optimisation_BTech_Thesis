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
