# Iteration 3 — Delay-gain driven multi-candidate gate sizing to eliminate critical-path slew degradation

cluster: `sizing`

# Plan: Iteration 3

## Observation

Analysis of the stock baseline results ([SUMMARY.md](file:///Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/05_baseline_results/SUMMARY.md)) under stressed SDC constraints reveals that negative setup slack across all three tier-A benchmarks is overwhelmingly dominated by signal transition degradation on timing-critical drivers:

1. **`nangate45/aes`** (WNS post: -0.1083 ns, TNS post: -14.773 ns):
   - 100% of the 40 worst paths exhibit the `slow_slew` tag.
   - The worst paths are bottlenecked by weak drive-strength complex logic gates (`AOI221_X1`, `XOR2_X1`, `OAI22_X1`, `OAI33_X1`) driving multi-sink loads with output slews between 27 ps and 63 ps.
2. **`nangate45/gcd`** (WNS post: -0.1742 ns, TNS post: -7.626 ns):
   - Stock repair achieved virtually no progress on WNS (improving by a negligible 0.8 ps from -0.1750 ns to -0.1742 ns across 72 endpoints).
   - 38/38 worst paths are tagged `slow_slew`, stalled on under-driven gates such as `NOR2_X2`, `INV_X1`, and `XNOR2_X2`.
3. **`nangate45/ibex`** (WNS post: -0.2994 ns, TNS post: -416.273 ns):
   - 61/61 worst paths are tagged `slow_slew` and `high_fanout`.
   - The top critical paths terminate in the register file array and are bottlenecked by an `AND2_X1` gate (`_26153_/ZN`) driving 943 sinks with an extreme 2.08 ns transition slew.

In summary, the pervasive failure mode across the benchmark suite is that drivers on setup-critical paths remain trapped at weak drive strengths ($X1$ and $X2$).

---

## Cluster Choice and Why

- **Selected Cluster**: `sizing`
- **Why `sizing`**:
  - The dominant path attribution across all benchmarks is weak cell drive strength resulting in slow slews.
  - While `setup_strategy` visits the critical drivers in topological and delay order, the decision made *at the driver* by the sizing engine fails to deploy adequate drive strength.
  - `buffering` cannot address the multi-stage logic paths in AES and GCD where fanouts are moderate (3 to 8) and logic gates must be sized up.
  - `hold` and `drv` are not the active bottlenecks (hold WNS is positive across all designs, ranging from +0.045 ns to +0.102 ns).
- **Durable Memory & Prior Iterations**:
  - Records #1 and #2 in [EXPERIENCE.md](file:///Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/10_agent_knowledge/EXPERIENCE.md) are marked `[infra/no-code]` (iteration 1 crashed during directory copying; iteration 2 was rejected with 0 code changes due to a quota timeout).
  - No valid code experiments exist yet in the ledger. Sizing has 0 prior attempts and addresses the primary physical cause of timing failure.

---

## Hypothesis

- **Problem**:
  Standard cells along timing-critical paths remain trapped at minimal drive strengths ($X1$ and $X2$), producing severe transition slew degradation and excessive gate delays.
- **Current Heuristic**:
  In `src/move/SizeUpGenerator.cc:upsizeCell` ([SizeUpGenerator.cc](file:///Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/01_openroad_original/rsz_snapshot/src/move/SizeUpGenerator.cc#L280-L325)), candidate cells are ranked by:
  $$\text{score} = \frac{\text{delay} - \text{swappable\_delay}}{\max(1.0, \text{cost\_ratio})}$$
  where $\text{cost\_ratio} = \text{new\_area} / \text{old\_area}$. This heuristic penalizes larger drive strengths ($X4, X8$) by dividing the stage delay improvement by the cell area inflation ratio, greedily favoring the smallest replacement ($X2$) even when an $X4$ or $X8$ cell provides far greater delay reduction.
  Furthermore, `SizeUpGenerator::generate()` returns at most **one single candidate** per target. If that candidate fails OpenDP legalization or input-pin max-cap checks, sizing aborts completely for that target, leaving the gate under-sized.
- **New Approach**:
  1. **Delay-Gain Driven Selection on Timing-Critical Targets**: In `SizeUpGenerator::upsizeCell`, on setup-violating targets, rank candidate cells by net stage delay reduction ($\Delta D = \text{delay} - \text{swappable\_delay}$) without penalizing larger drive strengths with the linear area-ratio divisor.
  2. **Multi-Candidate Ranked Search**: Modify `SizeUpGenerator::generate()` to emit a ranked list of viable replacement candidates (top 3 drive strengths sorted by $\Delta D$ descending). The transactional committer in `SetupLegacyBase::tryCandidateSequence` will attempt the highest-gain cell first; if OpenDP legalization fails due to local row density, it will automatically fall back to the next viable candidate rather than discarding the move.
- **Why WNS/TNS Improves**:
  Resizing critical path drivers to their true delay-optimal drive strengths ($X4, X8$) will sharpen signal transitions and reduce gate delays across critical paths. Multi-candidate generation prevents local placement congestion from blocking sizing moves.
- **Risks**:
  Upsizing gates increases their input capacitance, which could degrade upstream delay. This is safely bounded because:
  1. `swappable_delay` already accounts for upstream load via $\text{prev\_drive} \times C_{\text{in\_new}}$;
  2. `replacementPreservesMaxCap` guards upstream nets from electrical violations;
  3. Journaled transactions roll back any move that degrades global chip slack;
  4. Only instances on critical paths are upsized, keeping total chip area growth well within the 10.0% tolerance.

---

## Implementation Sketch

- **Target Files**:
  - `src/move/SizeUpGenerator.hh`: Update declaration to return multiple ranked candidates from `generate()`, and add helper signatures for collecting ranked candidate cells.
  - `src/move/SizeUpGenerator.cc`:
    - Refactor `upsizeCell` to collect all eligible swappable cells that improve drive resistance and reduce stage delay ($\text{swappable\_delay} < \text{delay}$).
    - Sort eligible cells in descending order of delay reduction $\Delta D = \text{delay} - \text{swappable\_delay}$ (delay-optimal ranking for setup closure).
    - In `generate()`, iterate through the sorted replacements, verify `replacementPreservesMaxCap`, and instantiate `SizeUpCandidate` objects for up to 3 distinct legal drive strengths.
- **Key Functions Involved**:
  - `rsz::SizeUpGenerator::generate(const Target& target)`
  - `rsz::SizeUpGenerator::upsizeCell(...)`
  - `rsz::SetupLegacyBase::tryCandidateSequence(...)`

---

## Success Criteria

- **Score Gain**: $\ge +0.00200$ vs champion (required acceptance threshold).
- **WNS Improvements**:
  - `nangate45/gcd`: WNS improves beyond -0.1742 ns (breaking the stock baseline stall).
  - `nangate45/aes`: WNS improves from -0.1083 ns towards $\ge -0.095$ ns, with measurable reductions in driver slews on `AOI221`, `XOR2`, and `OAI` instances.
  - `nangate45/ibex`: Significant reduction of the 2.08 ns transition slew on the register file fanin cone.
- **Safety Gates**: Total area growth $\le 10.0\%$, zero detailed placement violations, zero new DRV violations, and hold WNS degradation $\le 0.005$ ns.

---

## Fallback If It Fails

If pure delay-gain sorting causes localized placement legalization failures or excessive upstream delay on tight paths, damp the area term using a fractional power $\Delta D / (\text{cost\_ratio})^{0.5}$ and cap candidate generation to at most 2 sizes. If single-gate sizing is constrained by upstream driver limits, transition in Iteration 4 to `setup_strategy` to enable multi-stage driver-receiver pair sizing within a single pass.

---

```json
{"cluster": "sizing", "title": "Delay-gain driven multi-candidate gate sizing to eliminate critical-path slew degradation", "hypothesis": "Timing-critical paths across all benchmark designs suffer from severe transition slew degradation because SizeUpGenerator penalizes higher drive strengths by dividing delay gain by the cell area inflation ratio, forcing minimally sized replacements (X2) or leaving gates at X1. Furthermore, SizeUpGenerator generates only a single candidate per target, so any local placement legalization failure aborts sizing completely. By scoring candidate cells on timing-critical paths by pure stage delay reduction and returning a ranked multi-candidate set of viable drive strengths, the optimizer can evaluate and commit higher drive strengths (X4/X8) while gracefully falling back if OpenDP legalization fails. This directly sharpens transition slews on critical drivers and reduces both WNS and TNS.", "files": ["src/move/SizeUpGenerator.cc", "src/move/SizeUpGenerator.hh"], "evidence_iterations": [1, 2], "success_criteria": "Score gain >= +0.00200 vs champion with WNS improvement across aes, gcd, and ibex and area growth <= 10.0%", "risk": "Larger cell pin capacitances could increase load on upstream drivers if not bounded by stage delay and max-cap checks", "rule_updates": ""}
```

