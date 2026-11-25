# Feedback for iteration 12 (0012_setup_strategy, cluster setup_strategy)

```
vs champion:
REJECT  score=-0.00493
  nangate45/gcd      WNS -0.0234 -> -0.0260 ns  TNS -0.475 -> -0.491 ns  score -0.00379
  nangate45/aes      WNS -0.0258 -> -0.0445 ns  TNS -1.141 -> -1.361 ns  score -0.01278
  nangate45/ibex     WNS -0.0794 -> -0.0839 ns  TNS -65.665 -> -54.039 ns  score -0.00061
  nangate45/jpeg     WNS -0.0866 -> -0.0918 ns  TNS -32.403 -> -31.506 ns  score -0.00254
  ! score -0.00493 below required gain +0.00200

vs baseline:
ACCEPT  score=-0.00493
  nangate45/gcd      WNS -0.0234 -> -0.0260 ns  TNS -0.475 -> -0.491 ns  score -0.00379
  nangate45/aes      WNS -0.0258 -> -0.0445 ns  TNS -1.141 -> -1.361 ns  score -0.01278
  nangate45/ibex     WNS -0.0794 -> -0.0839 ns  TNS -65.665 -> -54.039 ns  score -0.00061
  nangate45/jpeg     WNS -0.0866 -> -0.0918 ns  TNS -32.403 -> -31.506 ns  score -0.00254
```

Cannot save `feedback.md`: this session permits only filesystem reads. The complete report follows.

# 1. Outcome

**REJECT against champion.** Score **−0.00493**, missing the required **+0.00200** gain by **0.00693**. The authoritative baseline verdict is **ACCEPT** with the same negative score; it does not establish a performance improvement.

Deltas below use the unrounded values in `verdict_vs_champion.json`. Positive deltas mean improvement.

| Design | WNS reference → candidate (ns) | ΔWNS (ps) | TNS reference → candidate (ns) | ΔTNS (ns) | Score |
|---|---:|---:|---:|---:|---:|
| gcd | −0.023366 → −0.025981 | −2.616 | −0.474810 → −0.491290 | −0.016479 | −0.00379 |
| aes | −0.025841 → −0.044526 | −18.685 | −1.140959 → −1.361219 | −0.220261 | −0.01278 |
| ibex | −0.079412 → −0.083932 | −4.520 | −65.665448 → −54.038542 | +11.626906 | −0.00061 |
| jpeg | −0.086623 → −0.091800 | −5.178 | −32.403059 → −31.506414 | +0.896645 | −0.00254 |

Every design loses WNS and has a negative score. AES contributes approximately **65%** of the aggregate score loss.

All supplied unit and smoke gates passed. Functional gates do not resolve the QoR regressions. Evaluation covers one stressed replicate per design.

# 2. Did the hypothesis do what it predicted?

| Prediction | Observation | Assessment |
|---|---|---|
| Ibex TNS improves by more than 10 ns | +11.626906 ns; violation magnitude falls 17.71% | Numerical prediction met |
| AES TNS stops regressing | −0.220261 ns; violation magnitude grows 19.30%; WNS loses 18.685 ps | Failed |
| JPEG stays near stock | TNS improves 2.77%, but WNS loses 5.178 ps and score is −0.00254 | Mixed; fails the scored objective |
| Stock ranking/generation prevents trajectory collapse | AES has 10 matched regressions, zero matched improvements, and 10 entries entering/leaving the reported worst list | Keeping generators stock did not preserve the trajectory |

The acceptance logic ran:

| Design | Pass evaluations | Accepted contrary to stock | Guard rejects* | TNS-loss vetoes |
|---|---:|---:|---:|---:|
| gcd | 610 | 5 | 1 | 1 |
| aes | 3,948 | 15 | 127 | 585 |
| ibex | 2,192 | 4 | 133 | 94 |
| jpeg | 1,794 | 6 | 67 | 247 |

\*The implementation increments the guard counter only when stock would have accepted; these are not counts of every guard failure.

The source narrows the causal interpretation:

- `src/rsz/src/policy/SetupLegacyPolicy.cc::pathImproved()` already prioritizes design WNS, then endpoint slack when WNS is equal. The hypothesis’s description of stock as endpoint-only is incomplete.
- `passAccepted()` controls **pass checkpoint promotion**, potentially covering several changes. A rejected pass can remain speculative during subsequent decreasing-slack passes; rejection does not immediately roll back each move.
- The 1 ps allowance compares against the previous promoted checkpoint. It provides neither a cumulative WNS budget nor protection relative to the final stock result.
- The claimed exact reduction to stock when `dTNS == dEndpoint` is false generally: the added guard and WNS tolerance change decisions independently of that equality.

Ibex’s four acceptance flips coincide with 93 inserted buffers and 193 resizes versus no reported buffer insertions and 149 resizes in stock. This supports retaining a narrowly controlled TNS-aware experiment. It does **not** establish that `_26153_` was repaired: that trunk remains on all ten listed worst Ibex paths at fanout 943, and three matched register-file endpoints regress.

# 3. Where the remaining negative slack comes from

The **five worst endpoints globally are all JPEG endpoints**. In this table, endpoint names have the common prefix `fdct_zigzag.dct_mod.`.

| Endpoint suffix | Slack (ns) | Structure and likely cause | Relevant moves; likely limitation |
|---|---:|---|---|
| `dct_block_2.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D` | −0.091800 | 22 stages, fanout 12; deep arithmetic logic and loaded `HA_X1@_113899_/S` | Size up the HA/upstream drivers; split loads or buffer branches. Acceptance changes cannot generate a missing structural candidate. |
| `dct_block_2.dct_unit_4.macu.mult_res[16]$_DFFE_PP_/D` | −0.090052 | 24 stages, fanout 12; same HA bottleneck plus `OAI21_X1@_084819_` | Coordinated sizing and pin swaps; load isolation. Single-pass gains can shift delay upstream without removing the shared bottleneck. |
| `dct_block_2.dct_unit_2.macu.mult_res[16]$_DFFE_PP_/D` | −0.089319 | 22 stages, fanout 9; `FA_X1@_109990_` and `HA_X1@_114253_` | Arithmetic-cell sizing, cloning or load splitting where legal. Deep carry/sum logic limits isolated sizing gains. |
| `dct_block_2.dct_unit_4.macu.mult_res[14]$_DFFE_PP_/D` | −0.088659 | 22 stages, fanout 12; `XNOR2_X1@_084834_` and shared HA | Size up weak drivers and isolate shared loads. Fixing one branch can increase input capacitance or disadvantage sibling paths. |
| `dct_block_0.dct_unit_3.macu.mult_res[18]$_DFFE_PP_/D` | −0.088588 | 22 stages, fanout 25; `HA_X1@_114513_` and shared `ddin[8]` launch driver | Split-load/buffer-tree repair and legal cloning, followed by sizing. Existing search did not retain structural load relief. |

JPEG reports **357 resizes and 149 pin swaps**, but no buffer insertions or clones, versus 282 resizes and 117 swaps in stock. More sizing did not remove the deepest shared arithmetic bottlenecks. The supplied evidence cannot distinguish candidate-generation filtering, legality rejection, and timing rejection.

Long-wire delay, IO constraints, and clock skew are not established causes for these five internal D endpoints. The reported slew scale is inconsistent with ordinary timing units; use the driver ordering and `slow_slew` tags, not converted physical slew values.

# 4. Regressions

Endpoint changes below use the rounded reference path values; they differ from design-level WNS deltas.

| Design | Regressed endpoints | Approximate slack loss | Probable mechanism |
|---|---|---:|---|
| gcd | `dpath.a_reg.out[5,4,6,1,3]` D pins | 2.6, 2.8, 2.8, 2.2, 3.1 ps | Shared `_604_`/`_501_` cone redistributes delay across bits. Resizes increase from 24 to 58; upstream capacitance and sibling-path effects are plausible. |
| aes | `sa23_sr[0,5,4]` D pins | 20.3, 14.3, 13.5 ps | Shared XOR/OAI/AOI cones remain weak or loaded; altered checkpoint decisions divert repair effort from these branches. |
| aes | `sa11_sr[3]`, `sa20_sr[7]` D pins | 5.0, 5.9 ps | Broad trajectory change, extending beyond the `sa23` cone. |
| ibex | `rf_reg[982,854,662]` D pins | 5.5, 5.6, 5.6 ps | Aggregate gains coexist with unresolved `_26153_` fanout and worse critical register-file branches. |
| jpeg | block/unit/result `[2/4/18]`, `[2/2/16]`, `[0/3/18]`, `[6/4/18]` | 7.5, 6.8, 6.4, 1.9 ps | Arithmetic-cone gains trade against other MAC endpoints; no reported buffering/cloning relieves shared loads. |

AES executes 316 additional resizes, 93 additional buffer insertions, and 44 additional pin swaps, yet finishes worse. Its **585 TNS-loss vetoes** show that the veto is active; they do not show that it protects final QoR. Blocking intermediate improvements and changing subsequent search states are plausible explanations requiring checkpoint traces.

Pre-repair improvement must not be confused with improvement over stock: AES `sa23_sr[0]` improves from −0.064183 to −0.044526 ns during repair, but stock reaches approximately −0.0242 ns.

# 5. Recommendation for the next iteration

Ranked options:

1. **`setup_strategy`: replace rolling WNS tolerance with a cumulative checkpoint budget.** Start from champion. Anchor the budget to the best refreshed design WNS, permit at most 1 ps cumulative loss, and restore the best checkpoint at endpoint/phase completion. Log checkpoint WNS, TNS, endpoint slack, and decision reason. This directly targets the all-design WNS regression.

2. **`setup_strategy`: isolate TNS acceptance flips from stock vetoes.** Restore stock decisions for stock-accepted passes; add only the TNS-based promotion of stock-rejected passes under the cumulative WNS guard. Test the loss veto separately afterward. This separates Ibex’s four flips from its 94 vetoes and AES’s 15 flips from 585 vetoes.

3. **`buffering`: generate bounded shared-trunk candidates with stock acceptance.** Deduplicate high-fanout trunks and evaluate a fixed small set of split-load/buffer-tree candidates for `_26153_`. Record candidate eligibility and rejection reasons. Require improvement on the critical register-file branches as well as TNS; do not infer trunk repair from total TNS alone.

**Do not try again:** globally deploy the same rolling 1 ps guard, violator-weighted endpoint term, and 2× loss veto with only threshold tuning. This experiment does not isolate which component produces Ibex’s gain or AES’s regression.

```json
{
  "recommended_cluster": "setup_strategy",
  "dominant_cause": "high_fanout",
  "lesson": "TNS-aware pass promotion improved Ibex TNS by 11.627 ns, but rolling checkpoint guards and stock-pass vetoes worsened WNS on every design and failed to protect AES.",
  "dead_end": "Do not repeat the combined rolling 1 ps guard, violator-weighted acceptance, and 2x TNS-loss veto as a global threshold-tuning experiment.",
  "good_changes": [
    "Design-TNS-aware checkpoint promotion in src/rsz/src/policy/SetupLegacyPolicy.cc coincided with Ibex's 11.627 ns TNS gain; isolate its four acceptance flips before retaining it."
  ],
  "bad_changes": [
    "Rolling 1 ps WNS tolerance in src/rsz/src/policy/SetupLegacyPolicy.cc does not impose a cumulative WNS budget.",
    "Stock-pass TNS-loss veto in src/rsz/src/policy/SetupLegacyPolicy.cc fired 585 times on AES without preventing worse final WNS and TNS.",
    "Combined acceptance changes altered repair trajectories despite unchanged target ranking and move generators."
  ],
  "files_to_revisit": [
    "src/rsz/src/policy/SetupLegacyPolicy.cc",
    "src/rsz/src/policy/SetupLegacyPolicy.hh",
    "src/rsz/src/policy/SetupLegacyBase.cc",
    "src/rsz/src/policy/SetupLegacyBase.hh"
  ],
  "files_to_avoid": [
    "src/rsz/src/RepairTargetCollector.cc",
    "src/rsz/src/move/SizeUpGenerator.cc",
    "src/rsz/src/policy/SetupParallelEvalPolicy.cc"
  ]
}
```
