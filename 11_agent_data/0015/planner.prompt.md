You are the **Planning Agent** of an evolution loop that improves OpenROAD's Resizer (`src/rsz`) so that
`repair_timing` leaves better WNS/TNS on placed designs. You do not write C++. You choose ONE algorithm
cluster and write a hypothesis that a coding sub-agent will implement in this iteration.

Iteration: 15. Champion so far: iteration 13 (score vs baseline +0.0021): Every in-loop change so far (iters 8, 9, 12) found large Ibex TNS gains from shared-cone/TNS-aware repair but perturbed the stock trajectory and lost WNS on AES/gcd/JPEG. Instead of modifying the gree.
Benchmarks (tier A): nangate45/gcd, nangate45/aes, nangate45/ibex, nangate45/jpeg. Spend so far: spent $6.42 / 30.00, 8,665,071 tokens over 43 calls.

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
# Feedback for iteration 14 (0014_sizing, cluster sizing)

```
vs champion:
REJECT  score=-0.00038
  nangate45/gcd      WNS -0.0222 -> -0.0222 ns  TNS -0.342 -> -0.339 ns  score +0.00001
  nangate45/aes      WNS -0.0241 -> -0.0241 ns  TNS -0.999 -> -0.992 ns  score +0.00000
  nangate45/ibex     WNS -0.0742 -> -0.0794 ns  TNS -44.399 -> -34.985 ns  score -0.00089
  nangate45/jpeg     WNS -0.0853 -> -0.0866 ns  TNS -31.151 -> -31.095 ns  score -0.00064
  ! score -0.00038 below required gain +0.00200

vs baseline:
ACCEPT  score=+0.00168
  nangate45/gcd      WNS -0.0234 -> -0.0222 ns  TNS -0.475 -> -0.339 ns  score +0.00401
  nangate45/aes      WNS -0.0258 -> -0.0241 ns  TNS -1.141 -> -0.992 ns  score +0.00124
  nangate45/ibex     WNS -0.0794 -> -0.0794 ns  TNS -65.665 -> -34.985 ns  score +0.00138
  nangate45/jpeg     WNS -0.0866 -> -0.0866 ns  TNS -32.403 -> -31.095 ns  score +0.00009
```

The workspace is read-only, so I could not create `feedback.md`. Its complete contents follow.

# 1. Outcome

**REJECT versus champion:** score **−0.000378**, below the required **+0.002000** gain by **0.002378**. Retain champion `0013_setup_strategy`.

**ACCEPT versus stock baseline:** score **+0.001682**. Baseline improvement does not justify replacing champion.

Deltas below are candidate minus reference; positive means improvement. Values use the verdict JSON precision.

| Design | Final WNS (ns) | Final TNS (ns) | ΔWNS vs champion (ps) | ΔTNS vs champion (ns) | ΔWNS vs baseline (ps) | ΔTNS vs baseline (ns) |
|---|---:|---:|---:|---:|---:|---:|
| gcd | −0.022241 | −0.339386 | −0.026 | +0.002628 | +1.125 | +0.135424 |
| aes | −0.024128 | −0.992136 | 0.000 | +0.006682 | +1.713 | +0.148823 |
| ibex | −0.079444 | −34.984699 | −5.205 | +9.414660 | −0.033 | +30.680749 |
| jpeg | −0.086591 | −31.094616 | −1.289 | +0.055902 | +0.032 | +1.308443 |

All six unit targets and ten smoke tests passed. Functional gates do not address the timing regression.

# 2. Did the hypothesis do what it predicted?

**The joint search executed, but did not produce the predicted WNS recovery or higher recovery keep rate on JPEG. Ibex gained TNS while losing champion WNS.**

| Design | DP examined | Predicted-gain trials | Assignments differing from greedy | DP kept | DP keep rate | WNS rejects | TNS rejects |
|---|---:|---:|---:|---:|---:|---:|---:|
| gcd | 224 | 131 | 122 | 6 | 4.6% | 67 | 58 |
| aes | 226 | 75 | 40 | 11 | 14.7% | 20 | 44 |
| ibex | 67 | 41 | 30 | 15 | 36.6% | 14 | 12 |
| jpeg | 80 | 75 | 68 | 14 | 18.7% | 49 | 12 |

For JPEG, the estimator predicted gain in 75/80 examined windows, yet STA rejected 61/75 trials. WNS rejection accounts for 49/75 trials, or **65.3%**. Joint planning therefore did not remove the dominant acceptance barrier.

`bottleneck_kept` includes DP keeps; these counters must not be added together:

- JPEG kept **34 total recovery moves**, unchanged from champion; 14 were DP moves. Counted recovery trials increased from **169 to 226** including DP. Keeps per counted trial fell from **20.1% to 15.0%**. Fallback WNS rejects remained **74**, versus champion’s **77**, with another **49** DP WNS rejects.
- Ibex kept **30 total recovery moves**, unchanged from champion; 15 were DP moves. Keeps per counted trial were approximately unchanged: **10.4% → 10.5%**. TNS magnitude decreased **21.20%** versus champion, but WNS worsened **5.205 ps**.
- These are aggregate counters, not paired experiments proving that particular rejected single moves became accepted joint moves.

The critical structures persist: Ibex’s top ten paths still share fanout-943 `AND2_X1@_26153_/ZN`; JPEG’s worst paths still contain HA_X1/FA_X1 chains. The reported 215 JPEG stage changes count proposed assignments before acceptance, not retained adjacent upsizes.

The implementation explains the mismatch:

- `planWindow` uses `gateDelay` without propagating actual input slew.
- Its side-load penalty uses resistance, capacitance increment and fanout; it does **not** explicitly weight side endpoints by their violation severity as hypothesized.
- Sequential stages receive no alternative masters, leaving shared launch-register drive unchanged.
- The fixed pre-recovery WNS floor permits surrendering WNS gains made earlier in recovery. Preserving the stock phase does not preserve champion’s recovery trajectory.
- Accepted DP moves skip fallback attempts for that driver and consume the shared recovery budget.

# 3. Where the remaining negative slack comes from

The **five worst endpoints across all four designs are all JPEG endpoints**. Their reported clock skew is zero. Deep arithmetic logic, weak arithmetic drivers and shared loading are supported causes; long-wire dominance and IO constraints are not established for these five register endpoints. Slew values below retain the report’s raw units.

| Endpoint | Slack; structure | Likely cause | Applicable moves and likely limitation |
|---|---|---|---|
| `fdct_zigzag.dct_mod.dct_block_6.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D` | −86.591 ps; 21 stages; max fanout 12 | Deep FA/HA chain; `HA_X1@_115901_/S` slew 35,598,000 and `FA_X1@_108721_/S` 24,679,000 | Coordinated sizing of legal surrounding cells, arithmetic input-pin reassignment where equivalent, and selective load isolation. Four-stage master swaps cannot reduce logic depth or split loads; slew propagation is omitted. `_067046_` remains INV_X1 versus champion’s INV_X2. |
| `fdct_zigzag.dct_mod.dct_block_5.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D` | −85.302 ps; 22 stages; max fanout 15 | Shared launch drive plus HA delay: `ddin[8]/Q` DFFR_X2 and `HA_X1@_114238_/S` | Buffer or partition shared launch loads, then size the affected branch. DP freezes sequential masters and cannot introduce a branch buffer. Slack is unchanged versus champion. |
| `fdct_zigzag.dct_mod.dct_block_7.dct_unit_4.macu.mult_res[15]$_DFFE_PP_/D` | −84.674 ps; 20 stages; max fanout 15 | `HA_X1@_115122_/S` slew 40,669,004, plus shared `ddin[8]/Q` loading | Isolate noncritical loads and evaluate critical HA input arcs with propagated slew. Master-only search cannot redistribute fanout. Slack is unchanged versus champion. |
| `fdct_zigzag.dct_mod.dct_block_4.dct_unit_7.macu.mult_res[16]$_DFFE_PP_/D` | −84.582 ps; 21 stages; max fanout 12 | Shared launch loading and `HA_X1@_114347_/S` delay | Branch buffering/load splitting followed by local sizing. A short window optimizes one path while leaving shared topology intact; launch-cell alternatives are excluded. |
| `fdct_zigzag.dct_mod.dct_block_7.dct_unit_2.macu.mult_res[18]$_DFFE_PP_/D` | −84.084 ps; 22 stages; max fanout 17 | Deep arithmetic cone: `FA_X1@_109354_/S` and `HA_X1@_115805_/S` | Load isolation, equivalent pin swaps and legal neighboring-cell sizing. A four-stage window covers only part of the chain and omits other inputs/outputs from its path cost. Slack is 0.190 ps worse than champion despite substantial pre-repair improvement. |

Verify that stronger swappable HA/FA masters actually exist before treating arithmetic-cell upsizing as an available remedy.

Ibex remains the principal cross-design fanout target: **39-stage paths**, fanout **943**, and raw slew **2,087,753,088** at `_26153_/ZN`. Buffer trees, load splitting or legal cloning directly address this structure; joint master selection leaves the topology intact.

# 4. Regressions

The supplied “vs reference” endpoint comparisons differ from the champion comparison. Keep those reference frames separate.

**Versus champion:**

- JPEG’s block-6/unit-4 `mult_res[18]` endpoint worsened **−83.447 → −86.591 ps**, a **3.144 ps** loss, and became the worst endpoint. Its common path pins show `_067046_` as **INV_X2 → INV_X1** relative to champion. This is consistent with displaced recovery sizing; it does not prove that the upsizing-only DP directly downsized the inverter.
- Ibex `rf_reg[703]/D` worsened **−73.038 → −79.444 ps**, a **6.406 ps** loss. Common path masters are unchanged. Changed side loads or upstream arrival conditions are plausible; move-level attribution is unavailable.
- The fixed stock floor allows both regressions while aggregate TNS improves.

**Versus the supplied path reference:**

| Endpoints | Observed loss | Probable mechanism |
|---|---:|---|
| gcd `resp_msg[9,8,5,3,2]` | 2.4, 16.9, 2.2, 3.0, 0.7 ps | Shared-cone loading or changed recovery allocation; positive-slack output losses do not contribute to TNS. |
| aes `sa10_sr[3]/D` | approximately 1.4 ps | Critical-path migration into a slow OAI33/XNOR cone. Other endpoints’ gains can offset this loss. |
| Ibex `rf_reg[703,607,831,799,895]/D` | Small losses in the supplied reference comparison; several hidden by rounding | Shared fanout-943 trunk remains unresolved while address-output paths improve. |
| JPEG block-1/unit-2 bits 16 and 18, block-3/unit-3 bit 16, block-2/unit-2 bit 16 | approximately 0.1, 0.1, 0.3, 0.2 ps | Added upstream capacitance or side-path slew degradation missed by the estimator. |
| JPEG `ddin[3]/RN` | approximately 0.1 ps; still strongly positive | Noncritical collateral change permitted by global acceptance. |

# 5. Recommendation for the next iteration

1. **`setup_strategy`: preserve achieved WNS during recovery.** Start from champion. Compare each trial against current committed WNS, retain the fixed stock floor as an additional guard, and evaluate final timing after legalization. Record endpoint identities for WNS losses. This directly targets the 5.205 ps Ibex and 1.289 ps JPEG losses versus champion.

2. **`buffering`: repair the shared structures explicitly.** Prioritize Ibex `_26153_/ZN`; evaluate partitioned buffering, load splitting and legal cloning. For JPEG, isolate loads on the shared `ddin[8]` launch cone. Require measured WNS/TNS gains and inspect sibling endpoints. Preserve the stock phase.

3. **`sizing`: replace the estimator before expanding the search.** If joint sizing is retained, propagate transition-specific slew, use the actual traversed arc, account for HA/FA secondary outputs and other inputs, and weight affected endpoints by slack. Log predicted versus measured gains and retained master assignments. The immediate target is JPEG’s **65.3% DP WNS-rejection rate**, not more windows.

**Do not try again:** enabling the same default-slew, four-stage DP ahead of every fallback attempt under only the fixed stock-WNS floor. It displaced recovery moves, retained the critical structures and reduced the champion score.

```json
{
  "recommended_cluster": "setup_strategy",
  "dominant_cause": "high_fanout",
  "lesson": "Joint sizing under a fixed stock-WNS floor displaced recovery moves and improved Ibex TNS by 21.20% versus champion while surrendering 5.205 ps of Ibex WNS and 1.289 ps of JPEG WNS.",
  "dead_end": "Do not repeat default-slew four-stage master-only DP before fallback recovery under only a fixed stock-WNS floor; JPEG rejected 49 of 75 DP trials for WNS and retained the same 34 total recovery moves.",
  "good_changes": [
    "src/rsz/src/policy/SetupLegacyPolicy.cc compound journals and measured STA acceptance retained 15 Ibex and 14 JPEG DP trials, though their isolated TNS contribution is unmeasured",
    "src/rsz/src/policy/SetupLegacyPolicy.cc window_dp counters expose predicted-gain failures and distinguish joint proposals from retained moves"
  ],
  "bad_changes": [
    "src/rsz/src/policy/SetupLegacyPolicy.cc::planWindow omits propagated input slew and explicit endpoint-violation weighting of side loads",
    "src/rsz/src/policy/SetupLegacyPolicy.cc::runTnsRecovery tries DP first, skips fallback after acceptance and consumes the shared recovery budget",
    "src/rsz/src/policy/SetupLegacyPolicy.cc fixed stock-WNS acceptance permits losing WNS gains already achieved during recovery"
  ],
  "files_to_revisit": [
    "src/rsz/src/policy/SetupLegacyPolicy.cc",
    "src/rsz/src/move/BufferGenerator.cc",
    "src/rsz/src/move/SplitLoadGenerator.cc",
    "src/rsz/src/move/CloneGenerator.cc"
  ],
  "files_to_avoid": [
    "src/rsz/src/policy/SetupLegacyBase.cc",
    "src/rsz/src/move/SizeUpGenerator.cc",
    "src/rsz/src/SkewBudget.cc"
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

## iteration 13 (setup_strategy)

Do not reintroduce shared-cone/TNS ranking inside the stock greedy loop: iterations 8, 9 and 12 traded Ibex gains for AES/gcd/JPEG WNS losses.

## iteration 14 (sizing)

Do not repeat default-slew four-stage master-only DP before fallback recovery under only a fixed stock-WNS floor; JPEG rejected 49 of 75 DP trials for WNS and retained the same 34 total recovery moves.


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

## iteration 13 (setup_strategy)

A separate journaled TNS recovery phase with a fixed stock-WNS floor improved WNS on all four designs and reduced Ibex TNS by 32.39%, while still permitting individual endpoint regressions.

## iteration 14 (sizing)

Joint sizing under a fixed stock-WNS floor displaced recovery moves and improved Ibex TNS by 21.20% versus champion while surrendering 5.205 ps of Ibex WNS and 1.289 ps of JPEG WNS.

## iteration 8 (setup_strategy), measured later with a long timeout
The iteration-8 candidate (setup policy rewrite) gave the largest TNS gains seen so far: ibex TNS -65.7 -> -8.1 ns (-88%), jpeg -32.4 -> -24.4 ns (-25%), gcd also better, but aes WNS worse and repair time grew 15-115x (jpeg 36 s -> 69 min, beyond the 10-min evaluation cap). Promising direction: keep its aggressive TNS recovery but bound its effort (iteration/time budget, or only on endpoints sharing bottleneck cells) so it fits the cap and does not degrade WNS.


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

## proposed by planner, iteration 13

Once in-loop changes have perturbed stock trajectories in two or more iterations, prefer post-stock phases with an absolute (non-rolling) WNS floor anchored to the stock final state, and print the floor value and per-phase kept/rejected counts.

## proposed by planner, iteration 14

New move generators should first be introduced only inside the post-stock recovery phase, with stock-phase move counts printed to prove the stock trajectory is byte-identical.

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
| 13 | setup_strategy | Two-phase repair: unchanged stock LEGACY loop, then a bottleneck-driven TNS-recovery phase with a hard post-stock WNS floor | accepted | +0.00206 |  |
| 14 | sizing | Joint path-window sizing by dynamic programming as a compound move inside the post-stock TNS-recovery phase | rejected | -0.00038 | score -0.00038 below required gain +0.00200 |
=== Durable cross-iteration experience ===
# Durable cross-iteration memory
All 14 records remain on disk. 12 are valid code experiments; 1 were accepted. Records marked infrastructure/no-code are not evidence about heuristic quality.

## Cluster portfolio
- buffering: 3 valid experiments, 0 accepted, best score -0.00004
- setup_strategy: 4 valid experiments, 1 accepted, best score +0.00206
- sizing: 5 valid experiments, 0 accepted, best score +0.00000

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
- #13 [valid] accepted setup_strategy: score +0.00206; files src/policy/SetupLegacyPolicy.cc, src/policy/SetupLegacyPolicy.hh, HYPOTHESIS.md; Two-phase repair: unchanged stock LEGACY loop, then a bottleneck-driven TNS-recovery phase with a hard post-stock WNS floor
- #14 [valid] rejected sizing: score -0.00038; files src/policy/SetupLegacyPolicy.cc, HYPOTHESIS.md; Joint path-window sizing by dynamic programming as a compound move inside the post-stock TNS-recovery phase

## File outcome history
- HYPOTHESIS.md: 12 tries, 1 accepted, best +0.00206
- src/policy/SetupLegacyPolicy.cc: 4 tries, 1 accepted, best +0.00206
- src/policy/SetupLegacyPolicy.hh: 3 tries, 1 accepted, best +0.00206
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

## Iteration 13: accepted · setup_strategy
- **Evidence status:** valid algorithm experiment
- **Hypothesis:** Two-phase repair: unchanged stock LEGACY loop, then a bottleneck-driven TNS-recovery phase with a hard post-stock WNS floor
- **Score:** vs champion +0.00206; vs baseline +0.00206
- **Files planned:** src/policy/SetupLegacyPolicy.cc, src/policy/SetupLegacyPolicy.hh, src/policy/BottleneckAnalysis.cc, src/policy/BottleneckAnalysis.hh, src/Optimizer.cc
- **Files changed:** src/policy/SetupLegacyPolicy.cc, src/policy/SetupLegacyPolicy.hh, HYPOTHESIS.md
- **Patch scope:** 1 files, +201/-0 lines
- **nangate45/gcd: score +0.00399; WNS -0.0234->-0.0222 ns (d +0.0012); TNS -0.475->-0.342 ns (d +0.133)**
- **nangate45/aes: score +0.00124; WNS -0.0258->-0.0241 ns (d +0.0017); TNS -1.141->-0.999 ns (d +0.142)**
- **nangate45/ibex: score +0.00227; WNS -0.0794->-0.0742 ns (d +0.0052); TNS -65.665->-44.399 ns (d +21.266)**
- **nangate45/jpeg: score +0.00074; WNS -0.0866->-0.0853 ns (d +0.0013); TNS -32.403->-31.151 ns (d +1.253)**
- **Dominant cause:** high_fanout
- **Lesson:** A separate journaled TNS recovery phase with a fixed stock-WNS floor improved WNS on all four designs and reduced Ibex TNS by 32.39%, while still permitting individual endpoint regressions.
- **Dead end:** Do not reintroduce shared-cone/TNS ranking inside the stock greedy loop: iterations 8, 9 and 12 traded Ibex gains for AES/gcd/JPEG WNS losses.
- **Recommended next cluster:** setup_strategy
- **Good changes:** src/rsz/src/policy/SetupLegacyPolicy.cc::runTnsRecovery preserves the stock trajectory and ranks shared drivers for a separate recovery phase, Fixed stock-WNS acceptance, measured incremental TNS acceptance and journal rollback filter harmful recovery trials
- **Bad changes:** Global WNS/TNS acceptance permits local losses, including Ibex instr_addr_o[22] becoming violating, Top-50 coverage, three attempts per driver and fixed within-round ranking may limit search; this is not established as the cause of endpoint regressions
- **Files to revisit:** src/rsz/src/policy/SetupLegacyPolicy.cc, src/rsz/src/policy/SetupLegacyPolicy.hh
- **Files to avoid:** src/rsz/src/policy/SetupLegacyBase.cc, src/rsz/src/move/SizeUpGenerator.cc, src/rsz/src/move/CloneGenerator.cc, src/rsz/src/Rebuffer.cc, src/rsz/src/SkewBudget.cc

## Iteration 14: rejected · sizing
- **Evidence status:** valid algorithm experiment
- **Hypothesis:** Joint path-window sizing by dynamic programming as a compound move inside the post-stock TNS-recovery phase
- **Score:** vs champion -0.00038; vs baseline +0.00168
- **Files planned:** src/move/PathWindowSizingGenerator.cc, src/move/PathWindowSizingGenerator.hh, src/LRSubproblem.cc, src/LRSubproblem.hh, src/policy/SetupLegacyPolicy.cc
- **Files changed:** src/policy/SetupLegacyPolicy.cc, HYPOTHESIS.md
- **Patch scope:** 1 files, +410/-17 lines
- **Verdict reasons:** score -0.00038 below required gain +0.00200
- **nangate45/gcd: score +0.00001; WNS -0.0222->-0.0222 ns (d -0.0000); TNS -0.342->-0.339 ns (d +0.003)**
- **nangate45/aes: score +0.00000; WNS -0.0241->-0.0241 ns (d +0.0000); TNS -0.999->-0.992 ns (d +0.007)**
- **nangate45/ibex: score -0.00089; WNS -0.0742->-0.0794 ns (d -0.0052); TNS -44.399->-34.985 ns (d +9.415)**
- **nangate45/jpeg: score -0.00064; WNS -0.0853->-0.0866 ns (d -0.0013); TNS -31.151->-31.095 ns (d +0.056)**
- **Dominant cause:** high_fanout
- **Lesson:** Joint sizing under a fixed stock-WNS floor displaced recovery moves and improved Ibex TNS by 21.20% versus champion while surrendering 5.205 ps of Ibex WNS and 1.289 ps of JPEG WNS.
- **Dead end:** Do not repeat default-slew four-stage master-only DP before fallback recovery under only a fixed stock-WNS floor; JPEG rejected 49 of 75 DP trials for WNS and retained the same 34 total recovery moves.
- **Recommended next cluster:** setup_strategy
- **Good changes:** src/rsz/src/policy/SetupLegacyPolicy.cc compound journals and measured STA acceptance retained 15 Ibex and 14 JPEG DP trials, though their isolated TNS contribution is unmeasured, src/rsz/src/policy/SetupLegacyPolicy.cc window_dp counters expose predicted-gain failures and distinguish joint proposals from retained moves
- **Bad changes:** src/rsz/src/policy/SetupLegacyPolicy.cc::planWindow omits propagated input slew and explicit endpoint-violation weighting of side loads, src/rsz/src/policy/SetupLegacyPolicy.cc::runTnsRecovery tries DP first, skips fallback after acceptance and consumes the shared recovery budget, src/rsz/src/policy/SetupLegacyPolicy.cc fixed stock-WNS acceptance permits losing WNS gains already achieved during recovery
- **Files to revisit:** src/rsz/src/policy/SetupLegacyPolicy.cc, src/rsz/src/move/BufferGenerator.cc, src/rsz/src/move/SplitLoadGenerator.cc, src/rsz/src/move/CloneGenerator.cc
- **Files to avoid:** src/rsz/src/policy/SetupLegacyBase.cc, src/rsz/src/move/SizeUpGenerator.cc, src/rsz/src/SkewBudget.cc

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
