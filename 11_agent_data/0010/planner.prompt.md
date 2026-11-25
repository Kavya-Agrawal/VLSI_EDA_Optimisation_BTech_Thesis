You are the **Planning Agent** of an evolution loop that improves OpenROAD's Resizer (`src/rsz`) so that
`repair_timing` leaves better WNS/TNS on placed designs. You do not write C++. You choose ONE algorithm
cluster and write a hypothesis that a coding sub-agent will implement in this iteration.

Iteration: 10. Champion so far: original rsz (no accepted change yet).
Benchmarks (tier A): nangate45/gcd, nangate45/aes, nangate45/ibex, nangate45/jpeg. Spend so far: spent $1.89 / 20.00, 6,517,719 tokens over 28 calls.

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
# Feedback for iteration 9 (0009_setup_strategy, cluster setup_strategy)

```
vs champion:
REJECT  score=-0.00276
  nangate45/gcd      WNS -0.0234 -> -0.0255 ns  TNS -0.475 -> -0.443 ns  score -0.00232
  nangate45/aes      WNS -0.0258 -> -0.0404 ns  TNS -1.141 -> -1.816 ns  score -0.01025
  nangate45/ibex     WNS -0.0794 -> -0.0659 ns  TNS -65.665 -> -31.338 ns  score +0.00498
  nangate45/jpeg     WNS -0.0866 -> -0.0931 ns  TNS -32.403 -> -36.094 ns  score -0.00344
  ! score -0.00276 below required gain +0.00200

vs baseline:
ACCEPT  score=-0.00276
  nangate45/gcd      WNS -0.0234 -> -0.0255 ns  TNS -0.475 -> -0.443 ns  score -0.00232
  nangate45/aes      WNS -0.0258 -> -0.0404 ns  TNS -1.141 -> -1.816 ns  score -0.01025
  nangate45/ibex     WNS -0.0794 -> -0.0659 ns  TNS -65.665 -> -31.338 ns  score +0.00498
  nangate45/jpeg     WNS -0.0866 -> -0.0931 ns  TNS -32.403 -> -36.094 ns  score -0.00344
```

Cannot save `feedback.md`: this session permits read-only filesystem access. Complete content follows.

## 1. Outcome

**REJECT vs champion.** Score **−0.00276**, below required **+0.00200** by **0.00476**. The authoritative baseline verdict is **ACCEPT** with the same score and reference measurements; this does not satisfy champion promotion.

Deltas below use unrounded verdict data; positive means improved slack.

| Design | WNS reference → candidate (ns) | ΔWNS (ns) | TNS reference → candidate (ns) | ΔTNS (ns) | Change in \|TNS\| | Score |
|---|---:|---:|---:|---:|---:|---:|
| gcd | −0.0234 → −0.0255 | −0.002179 | −0.475 → −0.443 | +0.031492 | −6.63% | −0.00232 |
| aes | −0.0258 → −0.0404 | −0.014585 | −1.141 → −1.816 | −0.675150 | +59.17% | −0.01025 |
| ibex | −0.0794 → −0.0659 | +0.013540 | −65.665 → −31.338 | +34.327145 | −52.28% | +0.00498 |
| jpeg | −0.0866 → −0.0931 | −0.006430 | −32.403 → −36.094 | −3.691213 | +11.39% | −0.00344 |

All six unit gates and ten smoke gates passed. Functional gates do not resolve the QoR rejection. Evaluation used one stressed replicate.

## 2. Did the hypothesis do what it predicted?

**Supported on Ibex; contradicted on JPEG and AES.**

| Design | Map builds | Paths expanded | First target changed / ranking passes | Observed repair-mix change vs baseline |
|---|---:|---:|---:|---|
| gcd | 28 | 1,126 | 279 / 678 = 41.2% | Resizes 24 → 36 |
| aes | 153 | 22,872 | 1,894 / 3,816 = 49.6% | Resizes 1,388 → 1,084; buffer removals 7 → 139 |
| ibex | 127 | 50,800 | 2,566 / 3,150 = 81.5% | Resizes 149 → 214; clones 9 → 21; pin swaps 14 → 47 |
| jpeg | 140 | 56,000 | 3,238 / 3,488 = 92.8% | Resizes 282 → 54; pin swaps 117 → 9 |

- **Ibex:** The predicted shared-cone benefit appears: TNS magnitude fell 52.28%, with WNS improving 13.54 ps. Register-file endpoints improved together; `rf_reg[982]` improved from −0.0784 to −0.0659 ns against reference. However, all ten reported worst paths still traverse `_26153_/ZN`, fanout 943, with 39 stages. The result supports shared-cone prioritization, but does not prove that this specific driver was repaired.
- **JPEG:** The predicted TNS reduction failed. First-target selection changed on 92.8% of passes, while resizes fell 80.9% and pin swaps fell 92.3%. Remaining paths span multiple arithmetic cones, with weak half-adder outputs and shared buffers. Sharedness did not identify sufficiently productive repair targets.
- **AES:** The prediction of near-stock behavior failed. Half the first targets changed; TNS magnitude increased 59.17%. `_13069_/Z` recurs across several worst `sa23_sr` paths, showing local sharing despite the diffuse-sharing premise. Keeping generators and acceptance stock did not preserve the move mix: buffer removals rose nearly 20×, while resizes fell 21.9%.
- **GCD:** Lower TNS accompanied worse WNS. The heuristic redistributed repair effort without protecting the worst endpoint.

Code inspection identifies two limitations. First, `load_delay*(1+share)` can amplify a key by up to 401×; the endpoint cap does not make the ranking perturbation small. Second, sharing measures path incidence, not achievable delay reduction or generator eligibility. The map can remain stale for 25 qualifying `repairPath` calls, which are not necessarily 25 distinct endpoints.

`shared_rank_reordered_targets` counts keys multiplied, not targets proven to change position. No map-build timing counter is implemented or reported. JPEG completed in 129.996 seconds; that total cannot establish ranking overhead. Each build still scans all endpoints and sorts violators before truncating to 400.

## 3. Where the remaining negative slack comes from

The five most negative reported endpoints across designs are **all JPEG**. Endpoint names below share prefix `fdct_zigzag.dct_mod.`.

| Endpoint suffix | Slack (ns) | Likely cause and evidence | Move types that should help | Why repair likely fell short |
|---|---:|---|---|---|
| `dct_block_0.dct_unit_7.macu.mult_res[18]$_DFFE_PP_/D` | −0.093053 | Deep logic: 22 stages; fanout 25; weak `HA_X1@_114235_/S`, plus `BUF_X4@place10742/Z` | SizeUpMove on eligible weak cells; BufferMove, CloneMove or SplitLoadMove on shared loads; SwapPinsMove where legal | Shared-buffer priority may displace local arithmetic repair. Endpoint improved 21.257 ps from its own pre-repair state, but remains worst. |
| `dct_block_0.dct_unit_3.macu.mult_res[18]$_DFFE_PP_/D` | −0.092710 | Deep logic: 21 stages; fanout 25; `HA_X1@_114513_/S` and the same `place10742/Z` | Local sizing/pin swapping; buffer sizing or load partitioning | Sharing does not distinguish repairable local arcs from a shared buffer with limited useful moves. Reference comparison regressed 10.5 ps. |
| `dct_block_6.dct_unit_6.macu.mult_res[15]$_DFFE_PP_/D` | −0.092364 | Deep logic: 21 stages; fanout 12; weak `HA_X1@_114812_/S` and `OAI21_X1@_098184_/ZN` | SizeUpMove and SwapPinsMove; buffering if load delay dominates | A separate arithmetic cone needs local attention. Broad shared-driver weighting can divert successful repair budget elsewhere. |
| `dct_block_0.dct_unit_2.macu.mult_res[15]$_DFFE_PP_/D` | −0.091415 | 18 stages; fanout 25; weak `HA_X1@_112836_/S` and `AOI22_X1@_077658_/ZN` | Eligible sizing/pin swaps; load splitting or cloning at overloaded drivers | Ranking cannot create stronger legal equivalents. Generator availability and rejection reasons are unreported. |
| `dct_block_7.dct_unit_3.macu.mult_res[16]$_DFFE_PP_/D` | −0.091141 | Deep logic: 23 stages; fanout 22; `AOI21_X1@_098640_/ZN` and `BUF_X4@place11023/Z` | AOI sizing/pin swapping; buffer resizing, cloning or splitting | Another shared buffer can dominate ranking while distributed logic delays remain. JPEG’s much smaller accepted move count supports reduced repair productivity. |

These are mechanism hypotheses, not traced move-level causes. Failed targets alone do not consume the successful-repair budget: the loop continues until enough changes succeed. Possible mechanisms include low-value accepted moves taking budget, repeated unsuccessful attempts interacting with outer stopping rules, and changed timing trajectories. Per-target attempt/rejection logs are needed to distinguish them.

Long-wire delay and clock skew are not established by these reports. The top five are register D endpoints without reported IO tags. Raw slew values have unclear scaling; use them comparatively, not as physical time measurements. JPEG reports zero electrical slew/capacitance/fanout violations despite the structural tags.

## 4. Regressions

Endpoint deltas here use the rounded reference path report.

- **AES:** `sa23_sr[0]` worsened 16.2 ps, `[4]` 16.5 ps, `[5]` 13.7 ps, `[7]` 8.7 ps; `sa31_sr[3]` worsened 17.4 ps. Eight matched endpoints regressed and none improved; twelve entered and twelve left the worst list. Repeated `_13069_/Z` implicates a shared local cone. Increased unbuffering and reduced sizing/cloning suggest that target order changed the accepted topology and displaced local improvements. They do not prove which removal caused a regression.
- **JPEG:** `dct_block_0.dct_unit_3...mult_res[18]` worsened 10.5 ps; `dct_block_2.dct_unit_4...mult_res[18]` worsened 4.6 ps. Two matched endpoints regressed, none improved, and fifteen entered/left the worst list. The strongest measured mechanism is loss of productive sizing and pin swapping under near-universal first-target changes.
- **Ibex:** `instr_addr_o[28]` worsened 16.1 ps; `[22]` crossed from +0.1 to −5.8 ps. Outputs `[27]` and `[26]` lost 9.7 and 6.9 ps while remaining positive. Register-file sharing dominates the capped map, plausibly deprioritizing output cones. Nine matched endpoints regressed despite aggregate improvement.
- **GCD:** `a_reg.out[10]` worsened 4.4 ps, `[13]` 2.7 ps, and `resp_msg[14]` 4.3 ps. Fifteen matched endpoints improved and fourteen regressed. A higher resize count did not prevent deterioration of a low-fanout NAND/INV path; aggregate sharing is insufficient protection for WNS.

Worst-list entry and disappearance are sampling changes, not proof of improvement or regression. Candidate improvements from pre-repair slack must not be substituted for comparisons against the repaired reference.

## 5. Recommendation for the next iteration

**Recommended cluster: `setup_strategy`.** Keep the next experiment focused on limiting shared-ranking influence; leave generators, acceptance and repair budget unchanged.

1. **Bound the perturbation.** In `src/rsz/src/policy/SetupLegacyBase.cc`, compare a capped multiplier such as `1 + min(0.25, share/400)` against using sharing only to break ties among drivers within 10% of the stock load-delay key. These are experimental settings. Measure first-target changes, accepted moves and QoR; reject variants that repeat JPEG’s move-count collapse.
2. **Require structural concentration before enabling sharing.** Measure the largest driver’s weighted endpoint coverage and its concentration relative to other drivers. Use stock ranking when no dominant shared cone exists. Choose thresholds from measured distributions, without design-name special cases. This directly tests whether Ibex’s benefit can survive while AES/JPEG revert toward stock.
3. **Discount targets after a full unsuccessful generator sweep.** Add an epoch-scoped failure cache in `SetupLegacyBase`; restore priority after relevant connectivity or timing changes. Instrument attempt, rejection and accepted-gain counts by target and move type. Add actual build-time measurement before changing refresh frequency or the 400-path cap.

Do **not** repeat broad `load_delay*(1+share)` ranking on every design, or add iteration 8’s admission/trial machinery to compensate. Candidate 9 already demonstrates that stock acceptance and generators cannot prevent ranking-induced move-mix degradation.

```json
{
  "recommended_cluster": "setup_strategy",
  "dominant_cause": "deep_logic",
  "lesson": "Shared-criticality ranking reduced Ibex TNS magnitude by 52.28% but changed repair trajectories enough to worsen AES and JPEG, so sharing needs bounded influence and evidence of structural concentration.",
  "dead_end": "Applying load_delay*(1+share) broadly while keeping acceptance and generators stock does not preserve the move mix or protect QoR.",
  "good_changes": [
    "src/rsz/src/policy/SetupLegacyBase.cc: shared-criticality target ranking coincided with Ibex TNS improving by 34.327145 ns and increased resizing and cloning",
    "src/rsz/src/policy/SetupLegacyBase.cc: changed-first counters establish that the new ranking executed and materially affected target selection"
  ],
  "bad_changes": [
    "src/rsz/src/policy/SetupLegacyBase.cc: uncapped-influence share multiplication changed JPEG's first target on 92.8% of ranking passes while resizes fell from 282 to 54",
    "src/rsz/src/policy/SetupLegacyBase.cc: broad shared ranking failed the AES near-stock prediction, with TNS magnitude increasing 59.17%",
    "src/rsz/src/policy/SetupLegacyBase.hh: the 400-path cap and 25-call refresh bound path expansion but do not ensure repairability, freshness, or measured build cost"
  ],
  "files_to_revisit": [
    "src/rsz/src/policy/SetupLegacyBase.cc",
    "src/rsz/src/policy/SetupLegacyBase.hh"
  ],
  "files_to_avoid": [
    "src/rsz/src/MoveCommitter.cc",
    "src/rsz/src/move/SizeUpGenerator.cc",
    "src/rsz/src/move/BufferGenerator.cc",
    "src/rsz/src/move/CloneGenerator.cc"
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
=== Durable cross-iteration experience ===
# Durable cross-iteration memory
All 9 records remain on disk. 7 are valid code experiments; 0 were accepted. Records marked infrastructure/no-code are not evidence about heuristic quality.

## Cluster portfolio
- buffering: 2 valid experiments, 0 accepted, best score -0.00039
- setup_strategy: 2 valid experiments, 0 accepted, best score +0.00063
- sizing: 3 valid experiments, 0 accepted, best score +0.00000

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

## File outcome history
- HYPOTHESIS.md: 7 tries, 0 accepted, best +0.00063
- src/policy/SetupLegacyPolicy.cc: 1 tries, 0 accepted, best +0.00063
- src/policy/SetupLegacyPolicy.hh: 1 tries, 0 accepted, best +0.00063
- src/move/SizeUpGenerator.cc: 3 tries, 0 accepted, best +0.00000
- src/move/SizeUpGenerator.hh: 2 tries, 0 accepted, best +0.00000
- src/move/SizeUpCandidate.hh: 1 tries, 0 accepted, best +0.00000
- src/move/BufferGenerator.cc: 1 tries, 0 accepted, best -0.00039
- src/move/BufferGenerator.hh: 1 tries, 0 accepted, best -0.00039
- src/move/SplitLoadGenerator.cc: 1 tries, 0 accepted, best -0.00156
- src/policy/SetupLegacyBase.cc: 1 tries, 0 accepted, best -0.00276
- src/policy/SetupLegacyBase.hh: 1 tries, 0 accepted, best -0.00276
- src/Optimizer.cc: 1 tries, 0 accepted, best -0.00276

## Detailed most recent 8 records
## Iteration 2: rejected · setup_strategy
- **Evidence status:** infrastructure/no-code record; do not infer heuristic quality
- **Hypothesis:** You've hit your 5-hour limit · resets 7:50am (Asia/Calcutta)
- **Score:** vs champion +0.00000; vs baseline +0.00000
- **Files planned:** (not recorded)
- **Files changed:** (none)
- **Verdict reasons:** score +0.00000 below required gain +0.00200
- **nangate45/gcd: score +0.00000; WNS -0.1742->-0.1742 ns (d +0.0000); TNS -7.626->-7.626 ns (d +0.000)**
- **nangate45/aes: score +0.00000; WNS -0.1083->-0.1083 ns (d +0.0000); TNS -14.773->-14.773 ns (d +0.000)**
- **nangate45/ibex: score +0.00000; WNS -0.2994->-0.2994 ns (d +0.0000); TNS -416.273->-416.273 ns (d +0.000)**

## Iteration 3: rejected · sizing
- **Evidence status:** valid algorithm experiment
- **Hypothesis:** Delay-gain driven multi-candidate gate sizing to eliminate critical-path slew degradation
- **Score:** vs champion +0.00000; vs baseline +0.00000
- **Files planned:** src/move/SizeUpGenerator.cc, src/move/SizeUpGenerator.hh
- **Files changed:** src/move/SizeUpGenerator.cc, src/move/SizeUpGenerator.hh, src/move/SizeUpCandidate.hh, HYPOTHESIS.md
- **Patch scope:** 1 files, +153/-165 lines
- **Verdict reasons:** gates failed: //src/rsz/test:TestInsertBuffer=FAILED; //src/rsz/test:TestNestedJournal=FAILED; //src/rsz/test:TestPreChecks=FAILED; //src/rsz/test:TestResizer=FAILED; //src/rsz/test:cpp_tests=FAILED
- **Dominant cause:** build_api_mismatch
- **Lesson:** Candidate 0003 produced no timing evidence because the upsizeCell-to-upsizeCells API change broke test compilation, and all ten smoke logs failed during helper initialization.
- **Dead end:** Repeating the incompatible API rename without migrating callers will fail gates before timing evaluation.
- **Recommended next cluster:** sizing
- **Bad changes:** SizeUpGenerator.hh replaced upsizeCell with upsizeCells while TestResizer.cc retained the old API, producing five compiler errors., Smoke success reporting accepted ten logs containing missing helpers.tcl errors.
- **Files to revisit:** src/rsz/src/move/SizeUpGenerator.hh, src/rsz/src/move/SizeUpGenerator.cc, src/rsz/test/cpp/TestResizer.cc

## Iteration 4: rejected · sizing
- **Evidence status:** valid algorithm experiment
- **Hypothesis:** Isolate absolute delay-gain ranking with API-compatible single-candidate sizing
- **Score:** vs champion +0.00000; vs baseline +0.00000
- **Files planned:** src/move/SizeUpGenerator.cc, test/cpp/TestResizer.cc
- **Files changed:** src/move/SizeUpGenerator.cc, HYPOTHESIS.md
- **Patch scope:** 1 files, +64/-73 lines
- **Verdict reasons:** gates failed: //src/rsz/test:TestResizer=FAILED; //src/rsz/test:cpp_tests=FAILED
- **Dominant cause:** unit_test_selection_contract_mismatch
- **Lesson:** Absolute stage-gain ranking changed rising-edge replacement selection and failed unit gates before any benchmark timing benefit could be measured.
- **Dead end:** Repeating the same gate-failing absolute-gain selector without resolving its selection contract cannot produce evaluable timing evidence.
- **Recommended next cluster:** sizing
- **Bad changes:** src/rsz/src/move/SizeUpGenerator.cc: replacing cost-normalized ranking with absolute gain conflicts with two existing rising-edge master assertions; timing impact is unmeasured.
- **Files to revisit:** src/rsz/src/move/SizeUpGenerator.cc, src/rsz/test/cpp/TestResizer.cc
- **Files to avoid:** src/rsz/src/move/SizeUpGenerator.hh, src/rsz/src/move/SizeUpCandidate.cc

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
