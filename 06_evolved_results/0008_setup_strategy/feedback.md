# Feedback for iteration 8 (0008_setup_strategy, cluster setup_strategy)

```
vs champion:
REJECT  score=+0.00063
  nangate45/gcd      WNS -0.0234 -> -0.0201 ns  TNS -0.475 -> -0.376 ns  score +0.00616
  nangate45/aes      WNS -0.0258 -> -0.0426 ns  TNS -1.141 -> -1.689 ns  score -0.01167
  nangate45/ibex     WNS -0.0794 -> -0.0605 ns  TNS -65.665 -> -8.111 ns  score +0.00739
  ! nangate45/jpeg: candidate evaluation failed (timeout)
  ! score +0.00063 below required gain +0.00200
  ! instrumentation missing: no RSZ_EVOLVE counter lines printed, cannot tell if the new logic ran

vs baseline:
REJECT  score=+0.00063
  nangate45/gcd      WNS -0.0234 -> -0.0201 ns  TNS -0.475 -> -0.376 ns  score +0.00616
  nangate45/aes      WNS -0.0258 -> -0.0426 ns  TNS -1.141 -> -1.689 ns  score -0.01167
  nangate45/ibex     WNS -0.0794 -> -0.0605 ns  TNS -65.665 -> -8.111 ns  score +0.00739
  ! nangate45/jpeg: candidate evaluation failed (timeout)
  ! instrumentation missing: no RSZ_EVOLVE counter lines printed, cannot tell if the new logic ran
```

Cannot save `feedback.md`: this session permits read-only filesystem access. Draft follows.

## 1. Outcome

**REJECT** versus champion and baseline. Score **+0.00063**, short of the required **+0.00200** by **0.00137**. JPEG timed out; execution of the new selector is unverified because no `RSZ_EVOLVE` counters appeared.

Positive deltas mean improvement. All timing values are ns; both reference comparisons have identical reported values.

| Design | Reference WNS | Candidate WNS | ΔWNS | Reference TNS | Candidate TNS | ΔTNS | Score |
|---|---:|---:|---:|---:|---:|---:|---:|
| gcd | -0.0234 | -0.0201 | +0.0033 | -0.475 | -0.376 | +0.099 | +0.00616 |
| aes | -0.0258 | -0.0426 | -0.0168 | -1.141 | -1.689 | -0.548 | -0.01167 |
| ibex | -0.0794 | -0.0605 | +0.0189 | -65.665 | -8.111 | +57.554 | +0.00739 |
| jpeg | — | timeout | — | — | timeout | — | — |

All six listed unit targets and ten smoke checks passed. These gates do not establish timing monotonicity, selector execution, or runtime feasibility.

## 2. Did the hypothesis do what it predicted?

**Shared-endpoint benefit is consistent with the results; safe selection and final-placement survival are not established.**

- **Ibex:** WNS improves 18.9 ps and TNS improves 57.554 ns, reducing negative-TNS magnitude by approximately 87.6%. This exceeds the hypothesis targets of +10 ps WNS and +15 ns TNS. Multiple register-file endpoints sharing `_26153_/ZN` improve by approximately 17.8–17.9 ps versus reference. This supports investigating shared-cone repair, but missing counters prevent attributing the improvement to journaled selection.
- **GCD:** WNS improves 3.3 ps and TNS improves 0.099 ns. Fifteen compared endpoints improve and eight regress. Global WNS/TNS floors do not protect every endpoint; `resp_msg[8]` crosses from positive to negative slack.
- **AES:** The +5 ps WNS target is missed: WNS instead loses 16.8 ps and TNS loses 0.548 ns. Among matched reported endpoints, zero improve and seven regress; thirteen enter and thirteen leave the worst list. Improving from the candidate’s own pre-repair state does not establish improvement over the reference.
- **Runtime:** JPEG fails at **1,800.95 seconds**. Exhaustive candidate regeneration, timing refresh, and graph-wide electrical checks are plausible contributors; phase timing is needed to establish the cause.

The patch implements local measured admission and winner replay in `src/policy/SetupLegacyPolicy.cc`. It explicitly leaves final detailed-placement verification to the evaluator. Consequently, the requested end-to-end survival condition is not enforced by this implementation.

Determinism, equivalent trial checkpoints, and replay fidelity remain unverified without trial traces.

## 3. Where the remaining negative slack comes from

The five globally worst reported endpoints are all in Ibex. Their common prefix is `gen_regfile_ff.register_file_i.`.

| Rank | Endpoint | Final slack (ns) | Likely cause | Move types that should address it | Why residual slack likely remains |
|---|---|---:|---|---|---|
| 1 | `rf_reg[982]$_DFFE_PN0P_/D` | -0.060493 | High fanout, weak driver, deep logic | Clone/load partition, buffer tree, driver sizing | A single accepted move may leave most shared load and serial delay intact |
| 2 | `rf_reg[854]$_DFFE_PN0P_/D` | -0.059940 | Same shared bottleneck | Clone/load partition and buffering | Independent endpoint passes may repeatedly encounter the same unresolved cone |
| 3 | `rf_reg[662]$_DFFE_PN0P_/D` | -0.059857 | Same shared bottleneck | Coordinated clone/buffer/size sequence | Strict positive gain for each isolated move can reject enabling moves |
| 4 | `rf_reg[566]$_DFFE_PN0P_/D` | -0.059855 | High fanout plus deep logic | Load isolation followed by sizing or pin swap | Load repair alone cannot remove 42 stages of logic |
| 5 | `rf_reg[694]$_DFFE_PN0P_/D` | -0.059765 | Same shared bottleneck | Shared-driver repair benefiting multiple sinks | Existing candidate scope may not construct an adequate partition or tree |

All five paths have **42 stages**, maximum fanout **943**, and the same reported worst driver, **`AND2_X1@_26153_/ZN`**. The accompanying `NOR3_X1@_20302_/ZN` is another reported slow driver. The shared structure makes high fanout the strongest actionable cause, with deep logic contributing residual delay.

Ibex records 191 inserted buffers and 218 resizes, but cloning remains nine, equal to baseline. More buffering did not eliminate the common bottleneck. These counts describe reported repair activity, not verified selector winners.

The supplied slew values have unverified units; use them comparatively. No wire-delay breakdown or clock-arrival data establishes long wire or clock skew as the dominant cause.

## 4. Regressions

| Design | Endpoint | Reference → candidate slack (ns) | Δslack |
|---|---|---:|---:|
| aes | `sa23_sr[0]$_DFF_P_/D` | -0.0242 → -0.0426 | -18.4 ps |
| aes | `sa23_sr[5]$_DFF_P_/D` | -0.0234 → -0.0403 | -16.9 ps |
| aes | `sa33_sr[3]$_DFF_P_/D` | -0.0258 → -0.0300 | -4.2 ps |
| aes | `sa02_sr[7]$_DFF_P_/D` | -0.0211 → -0.0274 | -6.3 ps |
| aes | `sa10_sr[3]$_DFF_P_/D` | -0.0227 → -0.0261 | -3.4 ps |
| gcd | `resp_msg[8]` | +0.0212 → -0.0001 | -21.3 ps |
| gcd | `resp_msg[9]` | +0.0032 → +0.0012 | -2.0 ps |
| gcd | `resp_msg[14]` | -0.0119 → -0.0130 | -1.1 ps |
| gcd | `resp_msg[11]` | -0.0064 → -0.0075 | -1.1 ps |
| gcd | `dpath.a_reg.out[11]$_DFFE_PP_/D` | -0.0141 → -0.0148 | -0.7 ps |
| ibex | `instr_addr_o[12]` | +0.1280 → +0.1145 | -13.5 ps |
| ibex | `instr_addr_o[25]` | +0.0931 → +0.0891 | -4.0 ps |
| ibex | `instr_addr_o[24]` | +0.0305 → +0.0293 | -1.2 ps |

**AES mechanism:** Repair activity shifts toward buffering: 706 insertions versus 481 baseline, while resizes fall from 1,388 to 612, pin swaps from 132 to two, and clones from 70 to thirteen. Remaining worst paths contain weak X1 compound gates and fanouts up to eighteen. Strict isolated-move admission and one winner per pass may suppress useful sequences or exhaust pass budgets. Placement changes may also erase local gains. Stage-separated measurements are required to distinguish these mechanisms.

**GCD and Ibex mechanism:** Collateral loading or placement changes can reduce nonfocus endpoint slack while preserving aggregate WNS/TNS. GCD demonstrates an actual new violation; the three listed Ibex regressions retain positive slack. Aggregate floors do not prohibit either outcome.

AES being worse than the reference does not itself prove a local admission-floor violation: a monotonic trajectory can still finish below a different repair trajectory.

## 5. Recommendation for the next iteration

1. **`setup_strategy`: instrument and bound measured selection.** Emit `RSZ_EVOLVE` counts for entry, legal trials, rejection reasons, restores, replay failures, and retained winners. Record timing-refresh and electrical-check costs. Use a deterministic candidate-count cap, reuse generator preparation within an unchanged checkpoint, and keep exact STA evaluation for shortlisted candidates. Require JPEG completion before expanding search.
2. **`setup_strategy`: verify checkpoint restoration and placement survival.** Compare metrics immediately after restore, trial, replay, and final detailed placement. Check structural restoration and record all admission metrics. Retain a pre-repair database checkpoint so the evaluation flow can restore it when final WNS or TNS regresses.
3. **`buffering`: target Ibex’s shared `_26153_/ZN` cone.** Trial legal sink partitions and clone/buffer/size bundles atomically. Apply monotonic admission to the completed bundle, allowing enabling internal steps. Measure affected endpoint count and shared-cone TNS explicitly.
4. **`sizing`: recover AES’s weak-driver alternatives.** Compare bounded sizing and pin-swap candidates against buffering on the reported X1 gates. Log whether alternatives fail legality, timing floors, electrical guards, or pass limits before changing their generators.

**Do not repeat:** uncapped exhaustive trials with full graph electrical scans and one winner per pass, without execution counters or final-placement validation.

```json
{
  "recommended_cluster": "setup_strategy",
  "dominant_cause": "high_fanout",
  "lesson": "Shared-cone repair coincided with a 57.554 ns Ibex TNS gain, but uninstrumented local monotonic trials did not establish final-placement safety or runtime feasibility.",
  "dead_end": "Do not repeat uncapped exhaustive journaled search with graph-wide electrical scans and one winner per pass without execution counters and final-placement validation.",
  "good_changes": [
    "Global TNS-aware scoring and checkpoint promotion in src/policy/SetupLegacyPolicy.cc remain plausible mechanisms for shared-endpoint benefit; causal attribution is unverified.",
    "Winner regeneration and measured replay in src/policy/SetupLegacyPolicy.cc provide a verification point that needs explicit counters."
  ],
  "bad_changes": [
    "Exhaustive regeneration, timing refresh, and graph-wide DRV scans in src/policy/SetupLegacyPolicy.cc create a plausible runtime bottleneck; JPEG timed out at 1800.95 seconds.",
    "Strict isolated-move admission and one winner per pass in src/policy/SetupLegacyPolicy.cc may suppress useful AES repair sequences.",
    "Local acceptance in src/policy/SetupLegacyPolicy.cc does not enforce gain survival after final detailed placement."
  ],
  "files_to_revisit": [
    "src/policy/SetupLegacyPolicy.cc",
    "src/policy/SetupLegacyPolicy.hh",
    "src/MoveCommitter.cc",
    "src/move/CloneGenerator.cc",
    "src/move/BufferGenerator.cc",
    "src/move/SizeUpGenerator.cc"
  ],
  "files_to_avoid": [
    "src/move/SizeUpMtGenerator.cc",
    "src/move/RebufferMtGenerator.cc"
  ]
}
```
