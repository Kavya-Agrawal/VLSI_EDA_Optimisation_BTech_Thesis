# Iteration 7 — Choose split-load partitions by branch slack budgets instead of half the sink count

cluster: `buffering`

## Observation

Iteration **6** improved Ibex TNS by **14.636 ns (3.52%)**, but improved WNS by only **1.6 ps** and regressed AES WNS by **2.9 ps**. This supports investigating shared-load repair, while showing that expanded eligibility alone is insufficient. Retained repairs on the intended drivers were not established.

The remaining Ibex paths contain repeated FA/MUX stages and shared NOR/AOI drivers. Load isolation could reduce their load-dependent delay; it cannot remove their intrinsic logic depth. The reported fanout 943 may belong to launch-clock circuitry and is not evidence for data-net repair.

Iteration **5** passed gates but produced identical tier-A timing. This plan avoids its unproductive feasible-runner-up sizing search.

## Cluster choice and why

**Choose `buffering`: replace fixed-half split-load partitioning with a slack-budgeted partition search.**

The dossier’s load-isolation mechanism directly addresses shared driver loading. Source inspection shows that `SplitLoadGenerator.cc::chooseSplitLoads` sorts sinks by slack headroom, then moves exactly half behind a buffer. That partition ignores sink capacitance, inserted-buffer delay, and whether the moved branches can tolerate the delay.

Start from the original champion. Preserve existing fanout eligibility and move ordering; do not incorporate iteration 6’s rebuffer eligibility expansion.

## Hypothesis

**Problem →** A fixed-half split can isolate too little capacitance or delay branches that have insufficient timing headroom.

**Current heuristic →** Rank immediate loads by slack relative to the driver, isolate the first half, insert the lowest-drive buffer, and resize it toward target slew.

**New approach →** Evaluate every nonempty proper prefix of the eligible, headroom-ranked sinks. For each prefix, predict the buffer size produced by the existing target-slew rule, the resulting driver load reduction, and arrival changes on moved and retained branches. Keep the focus-path load directly connected. Reject partitions that predict worsening an already-negative moved-load slack or making a nonnegative moved-load slack negative, checking both transitions. Select the feasible partition with the greatest predicted improvement in worst immediate-load slack, breaking ties by aggregate negative-slack improvement and then smaller buffer area.

**Why WNS/TNS improves →** The selected partition should unload shared critical drivers while spending only available sibling-branch slack. Compared with half-count splitting, it can isolate a few large, tolerant loads or a larger tolerant group, reducing delay across multiple data paths.

**Risks →** Placement RC and downstream slew effects can invalidate predictions. Deep intrinsic cell delay may limit gains, and split-load may rarely be reached because earlier move types succeed.

## Implementation sketch

All paths below are relative to candidate `rsz/`.

- **`src/move/SplitLoadGenerator.cc`**
  - In `resolveDriverPin`, retain fanout `>8`, existing net protections, and explicitly exclude clock drivers.
  - Extend `collectRankedFanoutSlacks` to snapshot finite rise/fall slack, scene-correct pin capacitance, and locations. Identify and exclude the focus-path sink from movable loads. Retain deterministic name-based ties.
  - Replace `chooseSplitLoads` with prefix evaluation. Missing timing information must not establish eligibility for moving a sink.
  - In `generate`, build a local estimator context and return only the winning partition through the existing `SplitLoadCandidate` interface. If no partition qualifies, generate no split candidate.

Reuse, without editing, `DelayEstimator::buildContext`, `estimateLoadChange`, `findArcDelay`, and `findBufferDelay`. Use `SplitLoadMtGenerator.cc::buildLoadSplitModel` as the reference for wire-capacitance approximation and `findTargetCell` for predicting the buffer’s eventual size. Recompute for both transitions rather than assuming one transition’s budget protects the other.

For each load, predict `slack_after = slack_before − arrival_delta`. Aggregate negative slack over immediate loads is a **ranking proxy**, not endpoint TNS. Keep the existing insertion, resizing, parasitic invalidation, and journal ownership.

Record driver, moved pins, predicted versus applied buffer master, predicted branch changes, and selected prefix size. Correlate these with journal outcomes and final connectivity; an insertion log alone does not establish retention.

## Success criteria

Compare against the original champion after detailed placement and fresh placement parasitics:

- **Promotion:** tier-A score **≥ +0.00200**, with every evaluator gate passing and identical replicates.
- **Target:** Ibex WNS **≥ −0.279412 ns** and TNS **≥ −395.459 ns**: approximately **20 ps** and **5%** improvement. With unchanged AES/GCD, these yield approximately **+0.00225** averaged score.
- **Regression targets:** AES and GCD WNS/TNS do not worsen beyond numerical tolerance.
- **Mechanism evidence:** at least one finally retained split selects a different partition from the original half-count rule; at least two matched downstream endpoints improve after legalization. Their reports should show reduced data-driver delay/arrival, with no added buffer on the protected focus branch.
- Run the required C++ and smoke gates, plus split-load, hierarchical split-load, and journal rollback regressions. Test deterministic partition selection and insufficient-headroom rejection.

## Fallback if it fails

Reject without changing the champion. If no qualifying split is reached or retained, record the opportunity counts; do not lower fanout thresholds to manufacture activity. If predictions improve but legalized endpoints regress, record the model error and placement displacement before proposing another buffering experiment. If retained splits reduce loading but barely affect arrival, decompose data-cell versus wire delay before choosing the next iteration.

```json
{
  "cluster": "buffering",
  "title": "Choose split-load partitions by branch slack budgets instead of half the sink count",
  "hypothesis": "The champion isolates half the headroom-ranked sinks without evaluating their capacitance or inserted-buffer delay. Search nonempty proper prefixes while retaining the focus-path sink directly on the driver, predicting the existing target-slew buffer size and both-transition branch arrival changes. Reject partitions that worsen already-negative moved-load slack or create negative slack on previously nonnegative moved loads, then maximize predicted worst-load slack improvement with aggregate negative-slack improvement as a tie-breaker. Iteration 6 supports investigating shared-load repair but warns against eligibility expansion and unverified retention; iteration 5 establishes the sizing fallback dead end this plan avoids. Retained splits should reduce shared data-driver delay and improve multiple matched endpoints after legalization.",
  "files": ["src/move/SplitLoadGenerator.cc"],
  "evidence_iterations": [6, 5],
  "success_criteria": "Score >= +0.00200 with all gates passing; target Ibex +20 ps WNS and 5% lower TNS magnitude, unchanged AES/GCD, and retained-partition attribution.",
  "risk": "Few split-load opportunities, intrinsic logic delay, or inaccurate slew and placement-RC predictions may prevent post-legalization benefit.",
  "rule_updates": "For partition-search experiments, report opportunities reached, partitions selected, and finally retained topology; distinguish immediate-load slack proxies from endpoint TNS."
}
```
