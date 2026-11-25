You are the **Planning Agent** of an evolution loop that improves OpenROAD's Resizer (`src/rsz`) so that
`repair_timing` leaves better WNS/TNS on placed designs. You do not write C++. You choose ONE algorithm
cluster and write a hypothesis that a coding sub-agent will implement in this iteration.

Iteration: 13. Champion so far: original rsz (no accepted change yet).
Benchmarks (tier A): nangate45/gcd, nangate45/aes, nangate45/ibex, nangate45/jpeg. Spend so far: spent $4.51 / 20.00, 7,688,881 tokens over 37 calls.

Hard rules:
- The goal is a *different heuristic / approximation / search strategy*, not micro-optimisation, not data-structure
  changes, not runtime. Changes that only tune a constant are allowed only if the hypothesis says why the constant
  is the lever.
- Pick exactly one cluster from: `setup_strategy` (which endpoints/paths to attack, in what order, how many mov...), `sizing` (how a cell size / VT / pin assignment is chosen for a driver...), `buffering` (how buffer trees are built/selected for a net (van Ginneken ...), `hold` (how hold violations are fixed with minimal setup damage...), `drv` (how slew / capacitance / fanout / long-wire violations are r...), `timing_model` (the estimates used to rank moves and budget skew/sequential ...). Respect `10_agent_knowledge/dead_ends.md` and the ledger: do not
  repeat a failed idea without a new reason.
- Ground the choice in the evaluator feedback below (dominant path causes, which designs regress/improve).
- Use the durable cross-iteration memory, not only the latest feedback. Once two valid experiments exist, cite at
  least two iteration numbers: one supporting the new direction and one failure/dead end the plan avoids. Records
  marked infrastructure/no-code are not algorithmic evidence.
- **Novelty requirement.** The hypothesis must replace or restructure a *decision procedure* (how targets are ranked,
  how a move is chosen, how cost/delay is estimated, how the search proceeds, when to stop) with a named different
  paradigm: e.g. global slack-budgeting instead of greedy worst-path-first; Lagrangian-relaxation / sensitivity-based
  sizing instead of one-cell-at-a-time upsizing; multi-endpoint path-sharing (fix the cell that sits on the most
  violating paths) instead of per-endpoint repair; lookahead or beam search over move sequences instead of first
  improving move; TNS-weighted acceptance instead of WNS-only acceptance; buffer-tree construction with slack-aware
  cost instead of the current fixed recipe. Corner-case guards, API tidying and "recover a rejected runner-up"
  fixes are NOT acceptable.
- **Trigger estimate.** Using the stock repair statistics below (how many resizes / buffers / clones / swaps the
  stock run makes per design), state how many decisions per design your change will alter. If the estimate is
  under ~5 % of the relevant moves on aes and ibex, choose a bigger idea.
- **No retreat.** After a rejection, do not propose a narrower variant of the same idea. Either change paradigm or
  change cluster. Rotate clusters: do not choose the same cluster more than twice in a row.
- Worst paths are tagged by structure (deep_logic, high_fanout, slow_slew, io_constrained); `launch_clock` paths are
  register-to-register, not IO paths.
- Be concrete: name files and functions from the cluster dossier; say what decision the algorithm makes today and
  what it should make instead; predict the observable effect in the path report.

Available material (read them; cwd is 09_agent_context):
- 00_BIG_PICTURE.md, algorithms/<cluster>.md, files/*.md, EVAL_CONTRACT.md, clusters.json
- 10_agent_knowledge/{rulebase,lessons,hypotheses_ledger,dead_ends}.md
- 10_agent_knowledge/iterations/*.json and EXPERIENCE.md (durable quantitative experiment memory)
- Latest evaluator feedback (below) and 05_baseline_results/SUMMARY.md

=== Stock repair statistics per design (baseline) ===
- nangate45/gcd: period 0.375 ns, endpoints 72, WNS -0.0250 -> -0.0234, TNS -0.73 -> -0.47, stock moves {'resized': 24, 'pins_swapped': 1}
- nangate45/aes: period 0.738 ns, endpoints 1248, WNS -0.0790 -> -0.0258, TNS -8.12 -> -1.14, stock moves {'buffers_removed': 7, 'buffers_inserted': 481, 'resized': 1388, 'pins_swapped': 132, 'cloned': 70}
- nangate45/ibex: period 1.98 ns, endpoints 5565, WNS -0.1925 -> -0.0794, TNS -164.02 -> -65.67, stock moves {'resized': 149, 'pins_swapped': 14, 'cloned': 9}
- nangate45/jpeg: period 1 ns, endpoints 8355, WNS -0.1165 -> -0.0866, TNS -48.30 -> -32.40, stock moves {'resized': 282, 'pins_swapped': 117}
=== Latest evaluator feedback ===
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

=== Knowledge ===
--- dead_ends.md ---
# Dead ends

Ideas that were tried and failed, with the reason. Check before proposing something similar.

## iteration 3 (sizing)

Repeating the incompatible API rename without migrating callers will fail gates before timing evaluation.

## iteration 4 (sizing)

Repeating the same gate-failing absolute-gain selector without resolving its selection contract cannot produce evaluable timing evidence.

## iteration 5 (sizing)

Do not repeat feasible-runner-up sizing selection without measured recovery opportunities and attributable endpoint gains.

## iteration 6 (buffering)

Do not repeat fanout eligibility expansion without retained-driver attribution and post-legalization collateral checks.

## iteration 7 (buffering)

Do not repeat prediction-only prefix replacement without attributing retained splits and verifying post-legalization collateral.

## iteration 8 (setup_strategy)

Do not repeat uncapped exhaustive journaled search with graph-wide electrical scans and one winner per pass without execution counters and final-placement validation.

## iteration 9 (setup_strategy)

Applying load_delay*(1+share) broadly while keeping acceptance and generators stock does not preserve the move mix or protect QoR.

## iteration 10 (sizing)

Repeating capped input-capacitance penalty tuning within unchanged stock eligibility does not address the measured Ibex and JPEG bottlenecks.

## iteration 11 (buffering)

Do not repeat global endpoint reordering or promote uninstrumented root-only V reranking as a substitute for three-dimensional Pareto retention.

## iteration 12 (setup_strategy)

Do not repeat the combined rolling 1 ps guard, violator-weighted acceptance, and 2x TNS-loss veto as a global threshold-tuning experiment.


--- lessons.md ---
# Lessons

Appended by the planner after each iteration. Newest at the bottom.

## iteration 3 (sizing)

Candidate 0003 produced no timing evidence because the upsizeCell-to-upsizeCells API change broke test compilation, and all ten smoke logs failed during helper initialization.

## iteration 4 (sizing)

Absolute stage-gain ranking changed rising-edge replacement selection and failed unit gates before any benchmark timing benefit could be measured.

## iteration 5 (sizing)

Moving upstream max-capacitance feasibility into sizing selection preserved compatibility but produced zero incremental tier-A timing benefit.

## iteration 6 (buffering)

High-fanout eligibility reduced Ibex TNS by 3.52% but failed promotion because AES regressed and retained repairs on the intended drivers were not established.

## iteration 7 (buffering)

Capacitance-aware prefix selection with predicted moved-load safety regressed AES WNS by 5.341 ps and TNS by 0.984591 ns, so split retention requires measured affected-endpoint checks after legalization.

## iteration 8 (setup_strategy)

Shared-cone repair coincided with a 57.554 ns Ibex TNS gain, but uninstrumented local monotonic trials did not establish final-placement safety or runtime feasibility.

## iteration 9 (setup_strategy)

Shared-criticality ranking reduced Ibex TNS magnitude by 52.28% but changed repair trajectories enough to worsen AES and JPEG, so sharing needs bounded influence and evidence of structural concentration.

## iteration 10 (sizing)

Neighbour weighting activated on 5078 of 5086 size selections but changed only 23 choices, improving AES TNS by 0.007183 ns without WNS gain; prioritize shared-net topology repair.

## iteration 11 (buffering)

Root-only sink-violation reranking left Ibex unchanged and traded a 0.047038 ns JPEG TNS gain for a 0.150839 ns AES loss; verify activation and actual endpoint TNS before testing V-aware Pareto retention.

## iteration 12 (setup_strategy)

TNS-aware pass promotion improved Ibex TNS by 11.627 ns, but rolling checkpoint guards and stock-pass vetoes worsened WNS on every design and failed to protect AES.


--- rulebase.md ---
# Rulebase (self-evolving)

The planner may add, relax or tighten rules here after each iteration. Keep rules short and testable.
Rules marked [fixed] are safety constraints and cannot be removed by agents.

## Safety [fixed]
- Only files under the candidate `rsz/` tree may be edited. Never touch OpenSTA, odb, dbSta or other modules.
- The resizer must keep the design logically equivalent: no change to the netlist function, only sizing,
  buffering (insert/remove), cloning, pin swapping on commutative pins and VT swaps.
- Any move must keep the placement legalizable (`detailed_placement` must succeed) and must not create DRV
  violations beyond the reference.
- No non-determinism: no unordered iteration over pointer-keyed containers that changes results, no
  wall-clock-dependent decisions, no threads whose scheduling changes the outcome.
- Do not spend the iteration on runtime micro-optimisation or data-structure refactoring; the objective is
  WNS/TNS after `repair_timing`, judged by the evaluator.

## Method
- One hypothesis per iteration, written down before coding: problem -> current heuristic -> new approach ->
  why WNS/TNS should improve -> risks -> how we will see it in the path report.
- Prefer changes to *what* the algorithm decides (ordering, selection, acceptance, search strategy, cost
  model) over changes to *how fast* it does it.
- Read the evaluator's worst-path attribution before choosing a cluster; attack the dominant cause.

## proposed by planner, iteration 4

Treat gate-failed candidates as timing-unverified, preserve helper API compatibility, and require smoke logs to demonstrate successful initialization and repair execution before timing interpretation.

## proposed by planner, iteration 5

For feasibility-fallback hypotheses, measure rejected winners and profitable feasible alternatives; zero benchmark opportunities falsifies applicability without justifying relaxed safety checks.

## proposed by planner, iteration 6

Before using path maximum-fanout or worst-slew tags to justify data-net repair, locate the attributed driver relative to launch CK/Q and capture D.

## proposed by planner, iteration 7

For partition-search experiments, report opportunities reached, partitions selected, and finally retained topology; distinguish immediate-load slack proxies from endpoint TNS.

## proposed by planner, iteration 8

For measured move comparisons, verify identical restored checkpoints and regenerated STA targets; report trial, endpoint-retained, and final post-legalization gains separately.

## proposed by planner, iteration 9

Every candidate must print RSZ_EVOLVE counters showing how often the new decision differed from stock; candidates adding per-move trials must report per-phase runtime and finish JPEG within the timeout.

## proposed by planner, iteration 10

Sizing-selection changes must reduce to the stock ranking when no neighbouring arc violates, so unit-test master contracts stay intact, and must print the fraction of selections that differ from stock.

## proposed by planner, iteration 11

Multi-objective selection changes must use a WNS tolerance band whose width is printed, and must reduce exactly to stock when at most one objective term is active.

## proposed by planner, iteration 12

Acceptance-rule changes must print evaluated/flipped_to_accept/flipped_to_reject counts and the summed predicted dTNS of flipped moves, and must leave target ranking and generators stock so the effect can be attributed.

=== Ledger (last entries) ===
# Hypotheses ledger

| iter | cluster | hypothesis (short) | verdict | score vs champion | note |
|---|---|---|---|---|---|
| 2 | setup_strategy | You've hit your 5-hour limit · resets 7:50am (Asia/Calcutta) | rejected | +0.00000 | score +0.00000 below required gain +0.00200 |
| 3 | sizing | Delay-gain driven multi-candidate gate sizing to eliminate critical-path slew degradation | rejected | +0.00000 | gates failed: //src/rsz/test:TestInsertBuffer=FAILED; //src/rsz/test:TestNestedJournal=FAILED; //src/rsz/test:TestPreChe |
| 4 | sizing | Isolate absolute delay-gain ranking with API-compatible single-candidate sizing | rejected | +0.00000 | gates failed: //src/rsz/test:TestResizer=FAILED; //src/rsz/test:cpp_tests=FAILED |
| 5 | sizing | Recover suppressed sizing moves with cost-ranked feasible replacement selection | rejected | +0.00000 | score +0.00000 below required gain +0.00200 |
| 6 | buffering | Enable shared-critical-data rebuffering beyond the blanket fanout cutoff | rejected | -0.00039 | score -0.00039 below required gain +0.00200 |
| 7 | buffering | Choose split-load partitions by branch slack budgets instead of half the sink count | rejected | -0.00156 | score -0.00156 below required gain +0.00200 |
| 8 | setup_strategy | Select LEGACY path repairs by journaled measured WNS/TNS gain | rejected | +0.00063 | nangate45/jpeg: candidate evaluation failed (timeout); score +0.00063 below required gain +0.00200; instrumentation miss |
| 9 | setup_strategy | Rank repair targets by slack-weighted count of violating endpoints sharing each driver (multi-endpoint path-sharing) instead of per-path loa | rejected | -0.00276 | score -0.00276 below required gain +0.00200 |
| 10 | sizing | Criticality-weighted (Lagrangian-style) cell selection that charges upstream and side-load delay by their violation weight | rejected | +0.00000 | score +0.00000 below required gain +0.00200 |
| 11 | buffering | TNS-aware van Ginneken: carry per-option total sink violation and choose the lowest-TNS tree among those within epsilon of the best worst-si | rejected | -0.00004 | score -0.00004 below required gain +0.00200; instrumentation missing: no RSZ_EVOLVE counter lines printed, cannot tell i |
| 12 | setup_strategy | TNS-weighted lexicographic acceptance (WNS guard band + design TNS gain) replacing endpoint-only slack acceptance in the LEGACY repair loop | rejected | -0.00493 | score -0.00493 below required gain +0.00200 |
=== Durable cross-iteration experience ===
# Durable cross-iteration memory
All 12 records remain on disk. 10 are valid code experiments; 0 were accepted. Records marked infrastructure/no-code are not evidence about heuristic quality.

## Cluster portfolio
- buffering: 3 valid experiments, 0 accepted, best score -0.00004
- setup_strategy: 3 valid experiments, 0 accepted, best score +0.00063
- sizing: 4 valid experiments, 0 accepted, best score +0.00000

## Complete compact history
- #1 [infra/no-code] crashed : score +0.00000; files none; Error: [('/Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/02_openroad_evolved/champion/rsz/test/save_defok', '/Users/kavyaagrawal/Desktop/G
- #2 [infra/no-code] rejected setup_strategy: score +0.00000; files none; You've hit your 5-hour limit · resets 7:50am (Asia/Calcutta)
- #3 [valid] rejected sizing: score +0.00000; files src/move/SizeUpGenerator.cc, src/move/SizeUpGenerator.hh, src/move/SizeUpCandidate.hh, HYPOTHESIS.md; Delay-gain driven multi-candidate gate sizing to eliminate critical-path slew degradation
- #4 [valid] rejected sizing: score +0.00000; files src/move/SizeUpGenerator.cc, HYPOTHESIS.md; Isolate absolute delay-gain ranking with API-compatible single-candidate sizing
- #5 [valid] rejected sizing: score +0.00000; files src/move/SizeUpGenerator.cc, src/move/SizeUpGenerator.hh, HYPOTHESIS.md; Recover suppressed sizing moves with cost-ranked feasible replacement selection
- #6 [valid] rejected buffering: score -0.00039; files src/move/BufferGenerator.cc, src/move/BufferGenerator.hh, HYPOTHESIS.md; Enable shared-critical-data rebuffering beyond the blanket fanout cutoff
- #7 [valid] rejected buffering: score -0.00156; files src/move/SplitLoadGenerator.cc, HYPOTHESIS.md; Choose split-load partitions by branch slack budgets instead of half the sink count
- #8 [valid] rejected setup_strategy: score +0.00063; files src/policy/SetupLegacyPolicy.cc, src/policy/SetupLegacyPolicy.hh, HYPOTHESIS.md; Select LEGACY path repairs by journaled measured WNS/TNS gain
- #9 [valid] rejected setup_strategy: score -0.00276; files src/policy/SetupLegacyBase.cc, src/policy/SetupLegacyBase.hh, src/Optimizer.cc, HYPOTHESIS.md; Rank repair targets by slack-weighted count of violating endpoints sharing each driver (multi-endpoint path-sharing) instead of per-path load delay
- #10 [valid] rejected sizing: score +0.00000; files src/move/SizeUpGenerator.cc, src/move/SizeUpGenerator.hh, HYPOTHESIS.md; Criticality-weighted (Lagrangian-style) cell selection that charges upstream and side-load delay by their violation weight
- #11 [valid] rejected buffering: score -0.00004; files src/Rebuffer.cc, src/Rebuffer.hh, src/move/RebufferMtGenerator.cc, HYPOTHESIS.md; TNS-aware van Ginneken: carry per-option total sink violation and choose the lowest-TNS tree among those within epsilon of the best worst-sink slack
- #12 [valid] rejected setup_strategy: score -0.00493; files src/policy/SetupLegacyPolicy.cc, src/policy/SetupLegacyPolicy.hh, src/policy/SetupLegacyBase.hh, HYPOTHESIS.md; TNS-weighted lexicographic acceptance (WNS guard band + design TNS gain) replacing endpoint-only slack acceptance in the LEGACY repair loop

## File outcome history
- HYPOTHESIS.md: 10 tries, 0 accepted, best +0.00063
- src/policy/SetupLegacyPolicy.cc: 2 tries, 0 accepted, best +0.00063
- src/policy/SetupLegacyPolicy.hh: 2 tries, 0 accepted, best +0.00063
- src/move/SizeUpGenerator.cc: 4 tries, 0 accepted, best +0.00000
- src/move/SizeUpGenerator.hh: 3 tries, 0 accepted, best +0.00000
- src/move/SizeUpCandidate.hh: 1 tries, 0 accepted, best +0.00000
- src/Rebuffer.cc: 1 tries, 0 accepted, best -0.00004
- src/Rebuffer.hh: 1 tries, 0 accepted, best -0.00004
- src/move/RebufferMtGenerator.cc: 1 tries, 0 accepted, best -0.00004
- src/move/BufferGenerator.cc: 1 tries, 0 accepted, best -0.00039
- src/move/BufferGenerator.hh: 1 tries, 0 accepted, best -0.00039
- src/move/SplitLoadGenerator.cc: 1 tries, 0 accepted, best -0.00156
- src/policy/SetupLegacyBase.cc: 1 tries, 0 accepted, best -0.00276
- src/policy/SetupLegacyBase.hh: 2 tries, 0 accepted, best -0.00276
- src/Optimizer.cc: 1 tries, 0 accepted, best -0.00276

## Detailed most recent 8 records
## Iteration 5: rejected · sizing
- **Evidence status:** valid algorithm experiment
- **Hypothesis:** Recover suppressed sizing moves with cost-ranked feasible replacement selection
- **Score:** vs champion +0.00000; vs baseline +0.00000
- **Files planned:** src/move/SizeUpGenerator.cc, test/cpp/TestResizer.cc
- **Files changed:** src/move/SizeUpGenerator.cc, src/move/SizeUpGenerator.hh, HYPOTHESIS.md
- **Patch scope:** 1 files, +115/-17 lines
- **Verdict reasons:** score +0.00000 below required gain +0.00200
- **nangate45/gcd: score +0.00000; WNS -0.1742->-0.1742 ns (d +0.0000); TNS -7.626->-7.626 ns (d +0.000)**
- **nangate45/aes: score +0.00000; WNS -0.1083->-0.1083 ns (d +0.0000); TNS -14.773->-14.773 ns (d +0.000)**
- **nangate45/ibex: score +0.00000; WNS -0.2994->-0.2994 ns (d +0.0000); TNS -416.273->-416.273 ns (d +0.000)**
- **Dominant cause:** high_fanout
- **Lesson:** Moving upstream max-capacitance feasibility into sizing selection preserved compatibility but produced zero incremental tier-A timing benefit.
- **Dead end:** Do not repeat feasible-runner-up sizing selection without measured recovery opportunities and attributable endpoint gains.
- **Recommended next cluster:** buffering
- **Good changes:** src/move/SizeUpGenerator.cc and src/move/SizeUpGenerator.hh preserved the protected upsizeCell API; all supplied unit and smoke gates passed, but no timing benefit was measured.
- **Bad changes:** src/move/SizeUpGenerator.cc moved replacementPreservesMaxCap into contender selection with zero measured WNS, TNS, or reported endpoint improvement.
- **Files to revisit:** src/move/SplitLoadGenerator.cc, src/move/BufferGenerator.cc, src/move/CloneGenerator.cc, src/policy/SetupLegacyPolicy.cc
- **Files to avoid:** src/move/SizeUpGenerator.cc, src/move/SizeUpGenerator.hh

## Iteration 6: rejected · buffering
- **Evidence status:** valid algorithm experiment
- **Hypothesis:** Enable shared-critical-data rebuffering beyond the blanket fanout cutoff
- **Score:** vs champion -0.00039; vs baseline -0.00039
- **Files planned:** src/move/BufferGenerator.cc
- **Files changed:** src/move/BufferGenerator.cc, src/move/BufferGenerator.hh, HYPOTHESIS.md
- **Patch scope:** 1 files, +120/-7 lines
- **Verdict reasons:** score -0.00039 below required gain +0.00200
- **nangate45/gcd: score +0.00000; WNS -0.1742->-0.1742 ns (d +0.0000); TNS -7.626->-7.626 ns (d +0.000)**
- **nangate45/aes: score -0.00236; WNS -0.1083->-0.1112 ns (d -0.0029); TNS -14.773->-15.027 ns (d -0.253)**
- **nangate45/ibex: score +0.00119; WNS -0.2994->-0.2978 ns (d +0.0016); TNS -416.273->-401.637 ns (d +14.636)**
- **Dominant cause:** deep_logic
- **Lesson:** High-fanout eligibility reduced Ibex TNS by 3.52% but failed promotion because AES regressed and retained repairs on the intended drivers were not established.
- **Dead end:** Do not repeat fanout eligibility expansion without retained-driver attribution and post-legalization collateral checks.
- **Recommended next cluster:** buffering
- **Good changes:** src/rsz/src/move/BufferGenerator.cc preserves low-fanout eligibility, net protections, and clock exclusion; GCD timing remained identical., The eligibility-only candidate reduced Ibex TNS by 14.636 ns, but the specific retained rebuffer mechanism remains unverified.
- **Bad changes:** src/rsz/src/move/BufferGenerator.cc enables high-fanout candidates by default without demonstrating post-legalization benefit across affected branches; AES WNS and TNS regressed., Reusing BufferCandidate and Rebuffer unchanged did not establish retained repairs on fanout-22/31/45 targets or meet the 20 ps Ibex WNS target.
- **Files to revisit:** src/rsz/src/move/BufferGenerator.cc, src/rsz/src/move/BufferCandidate.cc, src/rsz/src/Rebuffer.cc, src/rsz/src/Optimizer.cc, src/rsz/src/RepairTargetCollector.cc
- **Files to avoid:** src/rsz/src/move/BufferGenerator.hh

## Iteration 7: rejected · buffering
- **Evidence status:** valid algorithm experiment
- **Hypothesis:** Choose split-load partitions by branch slack budgets instead of half the sink count
- **Score:** vs champion -0.00156; vs baseline -0.00156
- **Files planned:** src/move/SplitLoadGenerator.cc
- **Files changed:** src/move/SplitLoadGenerator.cc, HYPOTHESIS.md
- **Patch scope:** 1 files, +231/-36 lines
- **Verdict reasons:** score -0.00156 below required gain +0.00200
- **nangate45/gcd: score +0.00000; WNS -0.1742->-0.1742 ns (d +0.0000); TNS -7.626->-7.626 ns (d +0.000)**
- **nangate45/aes: score -0.00467; WNS -0.1083->-0.1136 ns (d -0.0053); TNS -14.773->-15.758 ns (d -0.985)**
- **nangate45/ibex: score +0.00000; WNS -0.2994->-0.2994 ns (d +0.0000); TNS -416.273->-416.273 ns (d +0.000)**
- **Dominant cause:** high_fanout
- **Lesson:** Capacitance-aware prefix selection with predicted moved-load safety regressed AES WNS by 5.341 ps and TNS by 0.984591 ns, so split retention requires measured affected-endpoint checks after legalization.
- **Dead end:** Do not repeat prediction-only prefix replacement without attributing retained splits and verifying post-legalization collateral.
- **Recommended next cluster:** buffering
- **Bad changes:** src/rsz/src/move/SplitLoadGenerator.cc: prefix selection replacement regressed AES and produced no measured GCD or Ibex benefit, src/rsz/src/move/SplitLoadGenerator.cc: HPWL capacitance and gate-delay prediction omits wire resistance and downstream slew propagation
- **Files to revisit:** src/rsz/src/move/SplitLoadGenerator.cc, src/rsz/src/move/SplitLoadCandidate.cc, src/rsz/src/Optimizer.cc
- **Files to avoid:** src/rsz/src/move/SizeUpGenerator.cc, src/rsz/src/move/SizeUpCandidate.cc

## Iteration 8: rejected · setup_strategy
- **Evidence status:** valid algorithm experiment
- **Hypothesis:** Select LEGACY path repairs by journaled measured WNS/TNS gain
- **Score:** vs champion +0.00063; vs baseline +0.00063
- **Files planned:** src/policy/SetupLegacyPolicy.cc, src/policy/SetupLegacyPolicy.hh
- **Files changed:** src/policy/SetupLegacyPolicy.cc, src/policy/SetupLegacyPolicy.hh, HYPOTHESIS.md
- **Patch scope:** 1 files, +305/-20 lines
- **Verdict reasons:** nangate45/jpeg: candidate evaluation failed (timeout); score +0.00063 below required gain +0.00200; instrumentation missing: no RSZ_EVOLVE counter lines printed, cannot tell if the new logic ran
- **nangate45/gcd: score +0.00616; WNS -0.0234->-0.0201 ns (d +0.0032); TNS -0.475->-0.376 ns (d +0.099)**
- **nangate45/aes: score -0.01167; WNS -0.0258->-0.0426 ns (d -0.0168); TNS -1.141->-1.689 ns (d -0.548)**
- **nangate45/ibex: score +0.00739; WNS -0.0794->-0.0605 ns (d +0.0189); TNS -65.665->-8.111 ns (d +57.554)**
- **Dominant cause:** high_fanout
- **Lesson:** Shared-cone repair coincided with a 57.554 ns Ibex TNS gain, but uninstrumented local monotonic trials did not establish final-placement safety or runtime feasibility.
- **Dead end:** Do not repeat uncapped exhaustive journaled search with graph-wide electrical scans and one winner per pass without execution counters and final-placement validation.
- **Recommended next cluster:** setup_strategy
- **Good changes:** Global TNS-aware scoring and checkpoint promotion in src/policy/SetupLegacyPolicy.cc remain plausible mechanisms for shared-endpoint benefit; causal attribution is unverified., Winner regeneration and measured replay in src/policy/SetupLegacyPolicy.cc provide a verification point that needs explicit counters.
- **Bad changes:** Exhaustive regeneration, timing refresh, and graph-wide DRV scans in src/policy/SetupLegacyPolicy.cc create a plausible runtime bottleneck; JPEG timed out at 1800.95 seconds., Strict isolated-move admission and one winner per pass in src/policy/SetupLegacyPolicy.cc may suppress useful AES repair sequences., Local acceptance in src/policy/SetupLegacyPolicy.cc does not enforce gain survival after final detailed placement.
- **Files to revisit:** src/policy/SetupLegacyPolicy.cc, src/policy/SetupLegacyPolicy.hh, src/MoveCommitter.cc, src/move/CloneGenerator.cc, src/move/BufferGenerator.cc, src/move/SizeUpGenerator.cc
- **Files to avoid:** src/move/SizeUpMtGenerator.cc, src/move/RebufferMtGenerator.cc

## Iteration 9: rejected · setup_strategy
- **Evidence status:** valid algorithm experiment
- **Hypothesis:** Rank repair targets by slack-weighted count of violating endpoints sharing each driver (multi-endpoint path-sharing) instead of per-path load delay
- **Score:** vs champion -0.00276; vs baseline -0.00276
- **Files planned:** src/policy/SetupLegacyBase.cc, src/policy/SetupLegacyBase.hh, src/policy/SetupLegacyPolicy.cc, src/policy/SetupLegacyPolicy.hh
- **Files changed:** src/policy/SetupLegacyBase.cc, src/policy/SetupLegacyBase.hh, src/Optimizer.cc, HYPOTHESIS.md
- **Patch scope:** 1 files, +168/-0 lines
- **Verdict reasons:** score -0.00276 below required gain +0.00200
- **nangate45/gcd: score -0.00232; WNS -0.0234->-0.0255 ns (d -0.0022); TNS -0.475->-0.443 ns (d +0.031)**
- **nangate45/aes: score -0.01025; WNS -0.0258->-0.0404 ns (d -0.0146); TNS -1.141->-1.816 ns (d -0.675)**
- **nangate45/ibex: score +0.00498; WNS -0.0794->-0.0659 ns (d +0.0135); TNS -65.665->-31.338 ns (d +34.327)**
- **nangate45/jpeg: score -0.00344; WNS -0.0866->-0.0931 ns (d -0.0064); TNS -32.403->-36.094 ns (d -3.691)**
- **Dominant cause:** deep_logic
- **Lesson:** Shared-criticality ranking reduced Ibex TNS magnitude by 52.28% but changed repair trajectories enough to worsen AES and JPEG, so sharing needs bounded influence and evidence of structural concentration.
- **Dead end:** Applying load_delay*(1+share) broadly while keeping acceptance and generators stock does not preserve the move mix or protect QoR.
- **Recommended next cluster:** setup_strategy
- **Good changes:** src/rsz/src/policy/SetupLegacyBase.cc: shared-criticality target ranking coincided with Ibex TNS improving by 34.327145 ns and increased resizing and cloning, src/rsz/src/policy/SetupLegacyBase.cc: changed-first counters establish that the new ranking executed and materially affected target selection
- **Bad changes:** src/rsz/src/policy/SetupLegacyBase.cc: uncapped-influence share multiplication changed JPEG's first target on 92.8% of ranking passes while resizes fell from 282 to 54, src/rsz/src/policy/SetupLegacyBase.cc: broad shared ranking failed the AES near-stock prediction, with TNS magnitude increasing 59.17%, src/rsz/src/policy/SetupLegacyBase.hh: the 400-path cap and 25-call refresh bound path expansion but do not ensure repairability, freshness, or measured build cost
- **Files to revisit:** src/rsz/src/policy/SetupLegacyBase.cc, src/rsz/src/policy/SetupLegacyBase.hh
- **Files to avoid:** src/rsz/src/MoveCommitter.cc, src/rsz/src/move/SizeUpGenerator.cc, src/rsz/src/move/BufferGenerator.cc, src/rsz/src/move/CloneGenerator.cc

## Iteration 10: rejected · sizing
- **Evidence status:** valid algorithm experiment
- **Hypothesis:** Criticality-weighted (Lagrangian-style) cell selection that charges upstream and side-load delay by their violation weight
- **Score:** vs champion +0.00000; vs baseline +0.00000
- **Files planned:** src/move/SizeUpGenerator.cc, src/DelayEstimator.cc, src/DelayEstimator.hh, src/LRSubproblem.cc
- **Files changed:** src/move/SizeUpGenerator.cc, src/move/SizeUpGenerator.hh, HYPOTHESIS.md
- **Patch scope:** 1 files, +152/-14 lines
- **Verdict reasons:** score +0.00000 below required gain +0.00200
- **nangate45/gcd: score +0.00000; WNS -0.0234->-0.0234 ns (d +0.0000); TNS -0.475->-0.475 ns (d +0.000)**
- **nangate45/aes: score +0.00000; WNS -0.0258->-0.0258 ns (d +0.0000); TNS -1.141->-1.134 ns (d +0.007)**
- **nangate45/ibex: score +0.00000; WNS -0.0794->-0.0794 ns (d +0.0000); TNS -65.665->-65.665 ns (d +0.000)**
- **nangate45/jpeg: score +0.00000; WNS -0.0866->-0.0866 ns (d +0.0000); TNS -32.403->-32.403 ns (d +0.000)**
- **Dominant cause:** high_fanout
- **Lesson:** Neighbour weighting activated on 5078 of 5086 size selections but changed only 23 choices, improving AES TNS by 0.007183 ns without WNS gain; prioritize shared-net topology repair.
- **Dead end:** Repeating capped input-capacitance penalty tuning within unchanged stock eligibility does not address the measured Ibex and JPEG bottlenecks.
- **Recommended next cluster:** buffering
- **Good changes:** src/rsz/src/move/SizeUpGenerator.cc: counters distinguish weighted-score activation from actual master-choice changes., src/rsz/src/move/SizeUpGenerator.cc: retaining stock eligibility and zero-neighbour scoring fallback preserved passing compatibility gates.
- **Bad changes:** src/rsz/src/move/SizeUpGenerator.cc: capped aggregate neighbour weighting changed no JPEG choices and yielded no Ibex timing improvement., src/rsz/src/move/SizeUpGenerator.cc: selecting a replacement despite a negative weighted score prevents explicit rejection of predicted collateral loss.
- **Files to revisit:** src/rsz/src/move/SplitLoadGenerator.cc, src/rsz/src/move/BufferGenerator.cc, src/rsz/src/Rebuffer.cc, src/rsz/src/move/CloneGenerator.cc, src/rsz/src/move/SizeUpGenerator.cc
- **Files to avoid:** src/rsz/src/move/SizeUpMatchGenerator.cc, src/rsz/src/move/SizeUpMtGenerator.cc

## Iteration 11: rejected · buffering
- **Evidence status:** valid algorithm experiment
- **Hypothesis:** TNS-aware van Ginneken: carry per-option total sink violation and choose the lowest-TNS tree among those within epsilon of the best worst-sink slack
- **Score:** vs champion -0.00004; vs baseline -0.00004
- **Files planned:** src/Rebuffer.cc, src/Rebuffer.hh, src/BufferedNet.cc, src/BufferedNet.hh
- **Files changed:** src/Rebuffer.cc, src/Rebuffer.hh, src/move/RebufferMtGenerator.cc, HYPOTHESIS.md
- **Patch scope:** 1 files, +182/-16 lines
- **Verdict reasons:** score -0.00004 below required gain +0.00200; instrumentation missing: no RSZ_EVOLVE counter lines printed, cannot tell if the new logic ran
- **nangate45/gcd: score +0.00000; WNS -0.0234->-0.0234 ns (d +0.0000); TNS -0.475->-0.475 ns (d +0.000)**
- **nangate45/aes: score -0.00015; WNS -0.0258->-0.0259 ns (d -0.0001); TNS -1.141->-1.292 ns (d -0.151)**
- **nangate45/ibex: score +0.00000; WNS -0.0794->-0.0794 ns (d +0.0000); TNS -65.665->-65.665 ns (d +0.000)**
- **nangate45/jpeg: score -0.00000; WNS -0.0866->-0.0866 ns (d -0.0000); TNS -32.403->-32.356 ns (d +0.047)**
- **Dominant cause:** deep_logic
- **Lesson:** Root-only sink-violation reranking left Ibex unchanged and traded a 0.047038 ns JPEG TNS gain for a 0.150839 ns AES loss; verify activation and actual endpoint TNS before testing V-aware Pareto retention.
- **Dead end:** Do not repeat global endpoint reordering or promote uninstrumented root-only V reranking as a substitute for three-dimensional Pareto retention.
- **Recommended next cluster:** buffering
- **Bad changes:** src/rsz/src/Rebuffer.cc: chooseLowestTnsOption reranking coincided with AES TNS regression and no Ibex timing benefit; causality is unverified., src/rsz/src/Rebuffer.cc: V is evaluated only on surviving root options, leaving two-dimensional pruning unchanged., src/rsz/src/move/RebufferMtGenerator.cc: added counter reporting produced no captured RSZ_EVOLVE lines.
- **Files to revisit:** src/rsz/src/Rebuffer.cc, src/rsz/src/Rebuffer.hh, src/rsz/src/BufferedNet.hh, src/rsz/src/BufferedNet.cc, src/rsz/src/move/RebufferMtGenerator.cc, src/rsz/src/move/RebufferMtCandidate.cc, src/rsz/src/move/SizeUpGenerator.cc, src/rsz/src/move/CloneGenerator.cc
- **Files to avoid:** src/rsz/src/RepairSetupAnalysisTarget.cc

## Iteration 12: rejected · setup_strategy
- **Evidence status:** valid algorithm experiment
- **Hypothesis:** TNS-weighted lexicographic acceptance (WNS guard band + design TNS gain) replacing endpoint-only slack acceptance in the LEGACY repair loop
- **Score:** vs champion -0.00493; vs baseline -0.00493
- **Files planned:** src/policy/SetupLegacyPolicy.cc, src/policy/SetupLegacyPolicy.hh, src/policy/SetupLegacyBase.cc, src/policy/SetupLegacyBase.hh
- **Files changed:** src/policy/SetupLegacyPolicy.cc, src/policy/SetupLegacyPolicy.hh, src/policy/SetupLegacyBase.hh, HYPOTHESIS.md
- **Patch scope:** 1 files, +108/-9 lines
- **Verdict reasons:** score -0.00493 below required gain +0.00200
- **nangate45/gcd: score -0.00379; WNS -0.0234->-0.0260 ns (d -0.0026); TNS -0.475->-0.491 ns (d -0.016)**
- **nangate45/aes: score -0.01278; WNS -0.0258->-0.0445 ns (d -0.0187); TNS -1.141->-1.361 ns (d -0.220)**
- **nangate45/ibex: score -0.00061; WNS -0.0794->-0.0839 ns (d -0.0045); TNS -65.665->-54.039 ns (d +11.627)**
- **nangate45/jpeg: score -0.00254; WNS -0.0866->-0.0918 ns (d -0.0052); TNS -32.403->-31.506 ns (d +0.897)**
- **Dominant cause:** high_fanout
- **Lesson:** TNS-aware pass promotion improved Ibex TNS by 11.627 ns, but rolling checkpoint guards and stock-pass vetoes worsened WNS on every design and failed to protect AES.
- **Dead end:** Do not repeat the combined rolling 1 ps guard, violator-weighted acceptance, and 2x TNS-loss veto as a global threshold-tuning experiment.
- **Recommended next cluster:** setup_strategy
- **Good changes:** Design-TNS-aware checkpoint promotion in src/rsz/src/policy/SetupLegacyPolicy.cc coincided with Ibex's 11.627 ns TNS gain; isolate its four acceptance flips before retaining it.
- **Bad changes:** Rolling 1 ps WNS tolerance in src/rsz/src/policy/SetupLegacyPolicy.cc does not impose a cumulative WNS budget., Stock-pass TNS-loss veto in src/rsz/src/policy/SetupLegacyPolicy.cc fired 585 times on AES without preventing worse final WNS and TNS., Combined acceptance changes altered repair trajectories despite unchanged target ranking and move generators.
- **Files to revisit:** src/rsz/src/policy/SetupLegacyPolicy.cc, src/rsz/src/policy/SetupLegacyPolicy.hh, src/rsz/src/policy/SetupLegacyBase.cc, src/rsz/src/policy/SetupLegacyBase.hh
- **Files to avoid:** src/rsz/src/RepairTargetCollector.cc, src/rsz/src/move/SizeUpGenerator.cc, src/rsz/src/policy/SetupParallelEvalPolicy.cc

=== Deterministic cluster-to-code map ===
## setup_strategy
Decision: which endpoints/paths to attack, in what order, how many moves per pass, acceptance criteria, TNS vs WNS budgeting, stopping rules, move-sequence policy
Editable implementation surface (59 files): MoveCommitter.cc, MoveCommitter.hh, MoveTracker.cc, MoveTracker.hh, OptimizationPolicyConfig.cc, OptimizationPolicyConfig.hh, Optimizer.cc, Optimizer.hh, OptimizerTypes.cc, OptimizerTypes.hh, PathGroupFilter.cc, PathGroupFilter.hh, RepairSetupAnalysisReport.cc, RepairSetupAnalysisReport.hh, RepairSetupAnalysisTarget.cc, RepairSetupAnalysisTarget.hh, RepairSetupContext.hh, RepairSetupMoveSampler.cc, RepairSetupMoveSampler.hh, RepairSetupMoveSnapshot.cc, RepairSetupMoveSnapshot.hh, RepairSetupProfiler.cc, RepairSetupProfiler.hh, RepairTargetCollector.cc, RepairTargetCollector.hh, move/MoveCandidate.cc, move/MoveCandidate.hh, move/MoveGenerator.cc, move/MoveGenerator.hh, policy/BatchSelector.cc, policy/BatchSelector.hh, policy/BottleneckAnalysis.cc, policy/BottleneckAnalysis.hh, policy/GlobalSizingPolicy.cc, policy/GlobalSizingPolicy.hh, policy/OptimizationPolicy.cc, policy/OptimizationPolicy.hh, policy/ParallelEvalState.cc, policy/ParallelEvalState.hh, policy/ProgressReporter.cc, policy/ProgressReporter.hh, policy/SetupCritVtSwapPolicy.cc, policy/SetupCritVtSwapPolicy.hh, policy/SetupDirectionalPolicy.cc, policy/SetupDirectionalPolicy.hh, policy/SetupLastGaspPolicy.cc, policy/SetupLastGaspPolicy.hh, policy/SetupLegacyBase.cc, policy/SetupLegacyBase.hh, policy/SetupLegacyPolicy.cc, policy/SetupLegacyPolicy.hh, policy/SetupParallelEvalPolicy.cc, policy/SetupParallelEvalPolicy.hh, policy/SetupReroutePolicy.cc, policy/SetupReroutePolicy.hh, policy/SetupTnsPolicy.cc, policy/SetupTnsPolicy.hh, policy/SetupWnsPolicy.cc, policy/SetupWnsPolicy.hh
Key read-only dependencies: BufferGenerator.cc, BufferToInvertersGenerator.cc, BufferedNet.cc, CloneGenerator.cc, Delay.cc, DelayEstimator.cc, EstimateParasitics.h, Graph.cc, GraphDelayCalc.cc, LRSubproblem.cc, MakeWireParasitics.h, Mode.cc, Opendp.h, Path.cc, PathEnd.cc, PathExpanded.cc, PathGroup.cc, Rebuffer.cc, RebufferMtCandidate.cc, RebufferMtGenerator.cc, RerouteGenerator.cc, Resizer.cc, Scene.cc, Search.cc, SizeDownFanoutGenerator.cc, SizeDownFanoutMtGenerator.cc, SizeUpMatchGenerator.cc, SizeUpMtCandidate.cc, SizeUpMtGenerator.cc, SplitLoadGenerator.cc
Mapped regression tests: 98

## sizing
Decision: how a cell size / VT / pin assignment is chosen for a driver (greedy slack-driven today) and how the resulting delay is estimated
Editable implementation surface (46 files): DelayEstimator.cc, DelayEstimator.hh, DelayEstimatorBufferTree.cc, DelayEstimatorInternal.hh, DelayEstimatorReporter.cc, DelayEstimatorReporter.hh, LRSubproblem.cc, LRSubproblem.hh, SwapPinsEquivalence.cc, SwapPinsEquivalence.hh, move/SizeDownFanoutCandidate.cc, move/SizeDownFanoutCandidate.hh, move/SizeDownFanoutGenerator.cc, move/SizeDownFanoutGenerator.hh, move/SizeDownFanoutMtCandidate.cc, move/SizeDownFanoutMtCandidate.hh, move/SizeDownFanoutMtGenerator.cc, move/SizeDownFanoutMtGenerator.hh, move/SizeUpCandidate.cc, move/SizeUpCandidate.hh, move/SizeUpGenerator.cc, move/SizeUpGenerator.hh, move/SizeUpMatchCandidate.cc, move/SizeUpMatchCandidate.hh, move/SizeUpMatchGenerator.cc, move/SizeUpMatchGenerator.hh, move/SizeUpMtCandidate.cc, move/SizeUpMtCandidate.hh, move/SizeUpMtGenerator.cc, move/SizeUpMtGenerator.hh, move/SwapPinsCandidate.cc, move/SwapPinsCandidate.hh, move/SwapPinsGenerator.cc, move/SwapPinsGenerator.hh, move/SwapPinsMtCandidate.cc, move/SwapPinsMtCandidate.hh, move/SwapPinsMtGenerator.cc, move/SwapPinsMtGenerator.hh, move/VtSwapCandidate.cc, move/VtSwapCandidate.hh, move/VtSwapGenerator.cc, move/VtSwapGenerator.hh, move/VtSwapMtCandidate.cc, move/VtSwapMtCandidate.hh, move/VtSwapMtGenerator.cc, move/VtSwapMtGenerator.hh
Key read-only dependencies: BufferedNet.cc, CloneGenerator.cc, Delay.cc, EstimateParasitics.h, Graph.cc, GraphDelayCalc.cc, MakeWireParasitics.h, MoveCandidate.cc, MoveCommitter.cc, MoveGenerator.cc, Opendp.h, OptimizationPolicyConfig.cc, OptimizerTypes.cc, Path.cc, PathEnd.cc, PathExpanded.cc, Rebuffer.cc, RebufferMtCandidate.cc, RebufferMtGenerator.cc, RepairSetupProfiler.cc, Resizer.cc, Scene.cc, Sta.cc
Mapped regression tests: 112

## buffering
Decision: how buffer trees are built/selected for a net (van Ginneken style today), when to clone or split a load, where to insert, when to remove
Editable implementation surface (42 files): BufferedNet.cc, BufferedNet.hh, Rebuffer.cc, Rebuffer.hh, move/BufferCandidate.cc, move/BufferCandidate.hh, move/BufferGenerator.cc, move/BufferGenerator.hh, move/BufferToInvertersCandidate.cc, move/BufferToInvertersCandidate.hh, move/BufferToInvertersGenerator.cc, move/BufferToInvertersGenerator.hh, move/CloneCandidate.cc, move/CloneCandidate.hh, move/CloneGenerator.cc, move/CloneGenerator.hh, move/RebufferMtCandidate.cc, move/RebufferMtCandidate.hh, move/RebufferMtGenerator.cc, move/RebufferMtGenerator.hh, move/RebufferPlannerPool.cc, move/RebufferPlannerPool.hh, move/RerouteCandidate.cc, move/RerouteCandidate.hh, move/RerouteGenerator.cc, move/RerouteGenerator.hh, move/SplitLoadCandidate.cc, move/SplitLoadCandidate.hh, move/SplitLoadGenerator.cc, move/SplitLoadGenerator.hh, move/SplitLoadMtCandidate.cc, move/SplitLoadMtCandidate.hh, move/SplitLoadMtGenerator.cc, move/SplitLoadMtGenerator.hh, move/UnbufferCandidate.cc, move/UnbufferCandidate.hh, move/UnbufferGenerator.cc, move/UnbufferGenerator.hh, move/UnbufferMtCandidate.cc, move/UnbufferMtCandidate.hh, move/UnbufferMtGenerator.cc, move/UnbufferMtGenerator.hh
Key read-only dependencies: Delay.cc, DelayEstimator.cc, EstimateParasitics.h, Graph.cc, GraphDelayCalc.cc, MakeWireParasitics.h, Mode.cc, MoveCandidate.cc, MoveCommitter.cc, MoveGenerator.cc, OptimizerTypes.cc, Path.cc, PathExpanded.cc, RepairSetupProfiler.cc, Resizer.cc, Scene.cc, Search.cc, SizeDownFanoutMtGenerator.cc, Sta.cc, StaState.cc, SteinerTree.h
Mapped regression tests: 63

## hold
Decision: how hold violations are fixed with minimal setup damage
Editable implementation surface (2 files): RepairHold.cc, RepairHold.hh
Key read-only dependencies: BufferedNet.cc, ClkNetwork.cc, Delay.cc, EstimateParasitics.h, Graph.cc, GraphDelayCalc.cc, MakeWireParasitics.h, Opendp.h, Path.cc, PathExpanded.cc, PathGroupFilter.cc, Search.cc, SearchPred.cc, TestRepairHold.cc
Mapped regression tests: 20

## drv
Decision: how slew / capacitance / fanout / long-wire violations are repaired before timing repair
Editable implementation surface (4 files): PreChecks.cc, PreChecks.hh, RepairDesign.cc, RepairDesign.hh
Key read-only dependencies: BufferedNet.cc, ClkNetwork.cc, Delay.cc, EstimateParasitics.h, Graph.cc, GraphDelayCalc.cc, MakeWireParasitics.h, Mode.cc, Path.cc, Search.cc, SearchPred.cc
Mapped regression tests: 58

## timing_model
Decision: the estimates used to rank moves and budget skew/sequential timing
Editable implementation surface (6 files): DelayEstimatorBufferTree.cc, DelayEstimatorInternal.hh, SequentialTimingEstimator.cc, SequentialTimingEstimator.hh, SkewBudget.cc, SkewBudget.hh
Key read-only dependencies: ClkNetwork.cc, Delay.cc, DelayEstimator.cc, EstimateParasitics.h, Graph.cc, GraphDelayCalc.cc, MakeWireParasitics.h, Mode.cc, OptimizerTypes.cc, Path.cc, PathExpanded.cc, PocvMode.cc, Rebuffer.cc, RepairSetupProfiler.cc, Resizer.cc, Scene.cc
Mapped regression tests: 98

Write your plan as Markdown with sections: Observation, Cluster choice and why, Hypothesis (problem -> current
heuristic -> new approach -> why WNS/TNS improves -> risks), Implementation sketch (files/functions), Success
criteria (numbers to look for), Fallback if it fails. Then END with a JSON block:

```json
{"cluster": "<name>", "title": "<one line>", "hypothesis": "<3-6 sentences>", "files": ["src/...", ...],
 "evidence_iterations": [1, 2],
 "success_criteria": "<one line>", "risk": "<one line>", "rule_updates": "<optional: a rule to add/relax in rulebase.md or empty>"}
```
