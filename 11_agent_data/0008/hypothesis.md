# Iteration 8 — Select LEGACY path repairs by journaled measured WNS/TNS gain

cluster: `setup_strategy`

## Observation

The champion remains original `rsz`. Durable evidence points to shared-cone opportunity and unreliable local selection:

- **Iteration 6:** Ibex TNS improved by **14.636 ns (3.52%)**, but AES lost **2.899 ps WNS** and **0.253 ns TNS**. Shared-load transformations can help, although the retained drivers were not established.
- **Iteration 7:** prediction-only partition selection lost **5.341 ps WNS** and **0.985 ns TNS** on AES, with no GCD or Ibex improvement.
- **Iteration 5:** feasible-runner-up sizing produced exact timing parity, so that fallback has no demonstrated opportunity.

Ibex’s five worst endpoints share 35-stage paths and an attributed fanout-943 driver. That attribution requires checking against launch CK/Q and capture D before treating the driver as a legal data target. GCD’s worst-path fanout is at most eight, limiting split-load experiments.

Source inspection shows another decision worth changing: `SetupLegacyBase::repairPath()` ranks drivers by load delay, then `tryRepairTarget()` and `tryCandidateSequence()` stop at the first applicable move whose application succeeds. `SetupLegacyPolicy::pathImproved()` subsequently considers WNS and focus-endpoint slack, without a TNS condition.

## Cluster choice and why

**Exactly one cluster: `setup_strategy`.**

Test measured selection among existing moves on the current path. This addresses shared-cone benefit and collateral damage through search and acceptance decisions, while keeping champion buffer eligibility, partition construction, and sizing selection intact.

Iteration **6** supports looking for moves that benefit several endpoints together. Iteration **7** supplies the failure this plan avoids: trusting a local prediction without establishing endpoint benefit. This experiment does not assume that iteration 6 proved any particular buffering mechanism.

## Hypothesis

**Problem →** A first-success move on a high-delay stage can consume a repair opportunity even when another existing move produces greater shared endpoint benefit. Improving the focus endpoint or WNS alone can also hide worsening aggregate negative slack.

**Current heuristic →** Visit load-delay-ranked drivers, try generators in sequence, and retain progress using WNS/focus-endpoint comparisons.

**New approach →** For each LEGACY path repair, conduct a deterministic, journaled comparison of the existing legal candidates across that path. Apply each alternative from the same starting state, refresh placement-estimated parasitics and STA, then restore it. Include no change as an alternative. Admit only moves that preserve global WNS and TNS and do not worsen the focus endpoint; select the largest measured gain
\[
G=\Delta WNS+\Delta TNS/N,
\]
where \(N\) is the fixed number of constrained setup endpoints. Use existing STA comparison tolerances.

**Why WNS/TNS improves →** This objective matches the evaluator’s relative WNS/TNS weighting within a design because its period is a common factor. It can prefer shared-cone improvements over small isolated gains and reject collateral losses that a focus-endpoint check misses.

**Risks →** More STA trials may hit the timeout; strict monotonic admission can exclude useful multi-move sequences. Trial placement estimates can differ from final detailed placement, and incorrect rollback or stale STA references could invalidate comparisons.

## Implementation sketch (files/functions)

Start from champion. Planned implementation files, relative to the candidate `rsz/` tree:

- **`src/policy/SetupLegacyPolicy.hh`**: declare a LEGACY-specific `repairPath()` override and private trial-result helpers.
- **`src/policy/SetupLegacyPolicy.cc`**: implement measured candidate comparison; integrate retention with `repairEndpoint()` and its checkpoint handling.

Implementation details:

1. Reuse `rankPathDrivers()`, `makePinTargetOnPath()`, configured generators, and their existing legality checks. Respect explicit move sequences and skip options.
2. Snapshot stable driver/endpoint identities and candidate descriptors. Regenerate targets and candidates after every timing update or restore; never retain raw `sta::Path*` references across trials.
3. For each alternative, use existing `MoveCommitter::beginJournal()`, `commit()`, and `restoreJournal()`. Refresh through `Resizer::updateParasiticsAndTiming()` before measuring. Existing insertion/sizing placement hooks remain active.
4. Evaluate every alternative from the same parent checkpoint. Keep candidate generation pure; verify restoration also restores timing, move accounting, and any selection-affecting state.
5. Break equal measured scores by original driver rank, generator sequence, then candidate ordinal. Recreate and reapply the winner, verify its measured result again, and merge its journal into the endpoint journal.
6. Count only the retained winner against the repair budget. If another repair slot remains, rebuild the current path before searching again.
7. Record trial driver, move type, predicted gain, measured WNS/TNS/focus deltas, rejection reason, and whether the winner survives endpoint checkpointing.

Use `MoveCommitter` and `RepairTargetCollector` as read-only dependencies. Keep changes inside `setup_strategy`; do not edit move generators or sizing APIs.

Trial timing is **not** post-detailed-placement proof. Final attribution must compare matched endpoints after the evaluator’s detailed placement and parasitic refresh.

## Success criteria

Promotion requires the authoritative **score versus champion ≥ +0.002000**, deterministic replicates, and all functional, hold, DRV, area, and placement gates.

Diagnostic targets:

- **AES:** WNS improves by at least **5 ps**, reaching **≥ −0.103289 ns**; TNS is **≥ −14.773421 ns**.
- **Ibex:** WNS improves by at least **10 ps**, reaching **≥ −0.289412 ns**; TNS improves by at least **15 ns**, reaching **≥ −401.272895 ns**.
- **GCD:** no WNS/TNS regression.

These targets jointly imply approximately **+0.00247** under the baseline periods and endpoint counts.

Require at least one retained winner that differs from first-success selection, with attributable final endpoint improvement. On Ibex, predict several matched register-file endpoints improving together if the winner addresses their shared data cone. On AES, inspect the `sa23` group and all previously reported regressions; worst-list turnover alone does not count as improvement.

Run the six unit targets, ten smoke tests, and focused nested-journal, undo, move-sequence, and WNS-guard checks. Verify that rejected trials leave parent accounting and timing unchanged.

## Fallback if it fails

Reject the candidate and retain champion. If no alternative beats first-success selection, record that measured opportunity count rather than relaxing admission guards. If trial gains disappear after detailed placement, identify the retained move and matched endpoint losses before proposing another topology or prediction change. If strict monotonicity blocks progress, preserve the rejected-trial evidence for a later, separately scoped multi-move search experiment.

```json
{
  "cluster": "setup_strategy",
  "title": "Select LEGACY path repairs by journaled measured WNS/TNS gain",
  "hypothesis": "The champion tries load-delay-ranked drivers and accepts the first applicable move before comparing its endpoint impact with alternatives. Replace this decision in LEGACY path repair with deterministic journaled trials of existing legal candidates from the same checkpoint. After parasitic and STA refresh, admit only candidates that preserve global WNS, global TNS, and focus-endpoint slack, then maximize delta WNS plus delta TNS divided by the constrained endpoint count. Iteration 6 supports investigating shared endpoint benefit through its 14.636 ns Ibex TNS improvement, while iteration 7 demonstrates the collateral risk of prediction-only selection. Reapply and verify the winner, and require its gains to survive final detailed placement.",
  "files": [
    "src/policy/SetupLegacyPolicy.cc",
    "src/policy/SetupLegacyPolicy.hh"
  ],
  "evidence_iterations": [5, 6, 7],
  "success_criteria": "Score versus champion >= +0.002000 with all gates; target AES WNS +5 ps, Ibex WNS +10 ps and TNS +15 ns, with no design WNS/TNS regression.",
  "risk": "Extra STA trials may time out, monotonic admission may block useful move sequences, and final legalization may erase measured trial gains.",
  "rule_updates": "For measured move comparisons, verify identical restored checkpoints and regenerated STA targets; report trial, endpoint-retained, and final post-legalization gains separately."
}
```
