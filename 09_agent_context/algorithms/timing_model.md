<!-- hand-edited -->
# Cluster: `timing_model`

This dossier provides the formal engineering specification for the `timing_model` cluster in OpenROAD's Resizer (`src/rsz`). It governs rapid analytical delay approximations, buffer-tree delay estimators, sequential timing allocators, and intentional clock skew budgeting.

---

## 1. The Problem (Formal-ish)

### 1.1 Inputs and Outputs
- **Inputs**:
  - Net topology and physical wire parasitic segments ($R, C$).
  - Standard cell gate characteristics: driver effective output resistance $R_{\text{eff}}$, input pin capacitance $C_{\text{pin}}$, and input signal transition time $t_{\text{in\_slew}}$.
  - Sequential pipeline graph: launch registers, capture registers, and intervening combinational logic paths.
- **Outputs**:
  - Ultra-fast analytical delay and slew estimates ($\Delta D_{\text{est}}, \Delta S_{\text{est}}$) enabling rapid screening of hundreds of candidate moves per second without full static timing updates.
  - Skew budgets ($\Delta T_{\text{skew}}$) allocated across sequential clock pins to redistribute slack.

---

## 2. Current Algorithm, Step by Step

### 2.1 Fast Buffer Tree Estimation (`src/DelayEstimatorBufferTree.cc`)
Implemented in `src/DelayEstimatorBufferTree.cc:85`:
- Computes analytical Elmore delays across tree branches:
  $$D_{\text{branch}} = \sum_{k \in \text{path}} R_k \cdot C_{\text{downstream}}(k)$$
- Incorporates empirical slew-bias corrections (`src/DelayEstimatorCache`) to account for nonlinear waveform degradation on sub-micron interconnects without calling heavy tabular interpolation engines.

### 2.2 Sequential Timing & Skew Budgeting (`src/SkewBudget.cc`)
Implemented in `src/SkewBudget.cc:60`:
- Analyzes sequential loops where one pipeline stage has negative setup slack while adjacent stages possess positive slack margin.
- Calculates an intentional clock skew target:
  $$T_{\text{skew}}(R_{\text{capture}}) = \min \left( \Delta_{\text{max}}, \frac{s_{\text{capture}} - s_{\text{launch}}}{2} \right)$$
- Offsets the clock arrival target at the capture register, effectively "borrowing" cycle time from the succeeding stage to close timing on the current stage.

---

## 3. Interaction with the Timer and Other Clusters

- **Prescreener for Move Generators**: Used directly by `SizeUpGenerator`, `Rebuffer`, and `SplitLoadGenerator` to rank candidate moves before invoking OpenSTA.
- **Error Bounding**: If the analytical estimate deviates significantly from the true OpenSTA post-commit timing, `rsz::DelayEstimatorReporter` logs calibration statistics to adjust internal damping factors.

---

## 4. Known Weaknesses and Failure Modes

1. **Elmore Pessimism / Optimism**: Elmore delay neglects resistive shielding effects on deep sub-micron wires, leading to inaccurate ranking of buffer insertion candidates on long nets.
2. **Sequential Skew Drift**: Intentional skew budgeting relies on ideal clock models; post-CTS clock tree variations can easily disrupt narrow skew margins.

---

## 5. Alternative Approaches from Literature

### 5.1 Higher-Order Moment Matching (D2M / Arnoldi)
- **Concept**: Use two-pole (D2M) or Krylov-subspace Arnoldi reduction models inside the analytical delay estimator to capture resistive shielding on multi-GHz RC trees.
- **Injection Point**: Enhance `src/DelayEstimator.cc:elmoreDelay` with a two-pole approximation kernel.
- **Expected Gain**: 20–30% higher correlation with signoff STA delay metrics.

---

## 6. Safe-Change Checklist for `timing_model`

When modifying code within this cluster, ensure:
- [ ] **Conservative Ranking**: Ensure analytical estimators are monotonic with respect to true delay tables to prevent discarding genuinely beneficial moves.
- [ ] **Thread Safety**: Analytical cache structures must support concurrent multi-threaded access for `SetupParallelEvalPolicy`.
- [ ] **Regression Tests**: Run `test/repair_setup*.tcl` and `test/report_delay_estimator*.tcl`.
