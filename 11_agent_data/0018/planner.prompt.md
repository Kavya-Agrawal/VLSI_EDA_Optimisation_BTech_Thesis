You are the **Planning Agent** of an evolution loop that improves OpenROAD's Resizer (`src/rsz`) so that
`repair_timing` leaves better WNS/TNS on placed designs. You do not write C++. You choose ONE algorithm
cluster and write a hypothesis that a coding sub-agent will implement in this iteration.

Iteration: 18. Champion so far: iteration 13 (score vs baseline +0.0021): Every in-loop change so far (iters 8, 9, 12) found large Ibex TNS gains from shared-cone/TNS-aware repair but perturbed the stock trajectory and lost WNS on AES/gcd/JPEG. Instead of modifying the gree.
Benchmarks (tier A): nangate45/gcd, nangate45/aes, nangate45/ibex, nangate45/jpeg. Spend so far: spent $9.63 / 30.00, 10,260,165 tokens over 52 calls.

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
# Feedback for iteration 17 (0017_buffering, cluster buffering)

```
vs champion:
REJECT  score=+0.00000
  nangate45/gcd      WNS -0.0222 -> -0.0222 ns  TNS -0.342 -> -0.342 ns  score +0.00000
  nangate45/aes      WNS -0.0241 -> -0.0241 ns  TNS -0.999 -> -0.999 ns  score +0.00000
  nangate45/ibex     WNS -0.0742 -> -0.0742 ns  TNS -44.399 -> -44.399 ns  score +0.00000
  nangate45/jpeg     WNS -0.0853 -> -0.0853 ns  TNS -31.151 -> -31.151 ns  score +0.00000
  ! score +0.00000 below required gain +0.00200

vs baseline:
ACCEPT  score=+0.00206
  nangate45/gcd      WNS -0.0234 -> -0.0222 ns  TNS -0.475 -> -0.342 ns  score +0.00399
  nangate45/aes      WNS -0.0258 -> -0.0241 ns  TNS -1.141 -> -0.999 ns  score +0.00124
  nangate45/ibex     WNS -0.0794 -> -0.0742 ns  TNS -65.665 -> -44.399 ns  score +0.00227
  nangate45/jpeg     WNS -0.0866 -> -0.0853 ns  TNS -32.403 -> -31.151 ns  score +0.00074
```

Could not save `feedback.md`: the filesystem is read-only, and the write was rejected. The report follows.

## 1. Outcome

**REJECT versus champion:** score **+0.00000**, below the required **+0.00200**. All four designs match champion WNS/TNS.

**ACCEPT versus baseline:** score **+0.00206**. These gains are inherited from the champion.

Deltas are candidate minus comparator; positive means improvement. Units: ns.

| Design | Candidate WNS | Candidate TNS | ΔWNS vs champion | ΔTNS vs champion | ΔWNS vs baseline | ΔTNS vs baseline |
|---|---:|---:|---:|---:|---:|---:|
| GCD | -0.0222 | -0.342 | 0 | 0 | +0.0012 | +0.133 |
| AES | -0.0241 | -0.999 | 0 | 0 | +0.0017 | +0.142 |
| Ibex | -0.0742 | -44.399 | 0 | 0 | +0.0052 | +21.266 |
| JPEG | -0.0853 | -31.151 | 0 | 0 | +0.0013 | +1.252 |

Six unit targets and ten smoke cases passed. These checks do not establish activation of the new optimization.

## 2. Did the hypothesis do what it predicted?

**No tree effect was observed.** `evolve_counters.json` reports zero trees built, zero tree buffers, and zero sinks isolated on every design. Stock fallback fired twice on Ibex and once on JPEG.

Ibex’s ten listed worst paths still cross **AND2_X1 `_26153_/ZN`**, retain maximum fanout **943**, and report worst slew **2087753088.0** in the report’s unverified slew units. Nine paths have 37 stages; one has 33. Neither load isolation nor driver resizing is visible.

Source inspection identifies differences from the stated hypothesis:

- `src/rsz/src/move/SplitLoadGenerator.cc` evaluates **16 variants using a lumped RC model**, then returns at most one tree. It does not evaluate several trees through measured incremental STA.
- Sink ordering uses relative slack for one transition rather than explicit required-time ordering.
- Groups are limited to **four**, and each must fit below **90% of one buffer master’s maximum capacitance**. This is a plausible feasibility bottleneck at fanout 943, but rejection reasons were not logged.
- Screening excludes wire capacitance and slew-dependent delay and rejects predicted gains below **1 ps**.
- `SplitLoadCandidate.cc::applyFanoutTree` inserts buffers but does not resize the original driver.
- The shared generator has no recovery-only condition. Equal final metrics do not establish a byte-identical stock trajectory.
- `SetupLegacyPolicy.cc::runTnsRecovery` captures its WNS floor once. It neither ratchets that floor after commits nor implements the promised near-zero endpoint guard.

The built counter increments during application, before outer journal acceptance. Its zero value provides no evidence that a successfully inserted tree reached timing evaluation. The physical hypothesis remains untested by an applied tree.

## 3. Where the remaining negative slack comes from

The **five globally worst endpoints are all JPEG endpoints**. Names below omit the common prefix `fdct_zigzag.dct_mod.` and suffix `$_DFFE_PP_/D`.

| Endpoint | Slack (ns) | Likely cause | Applicable moves and likely reason unresolved |
|---|---:|---|---|
| `dct_block_5.dct_unit_4.macu.mult_res[18]` | -0.085302 | Deep logic: 22 stages; fanout 15; shared DFFR_X2 `ddin[8]/Q` and HA_X1 `_114238_/S` | Launch sizing/cloning, selective load splitting, HA sizing. Tree threshold 40 excludes the reported path fanout. |
| `dct_block_2.dct_unit_4.macu.mult_res[18]` | -0.085137 | Deep arithmetic logic: 19 stages; fanout 12; HA_X1 `_115515_/S`, NOR3_X2 `_106305_/ZN` | HA/NOR sizing, pin swaps, arithmetic remapping. High-fanout trees do not shorten the arithmetic chain. |
| `dct_block_7.dct_unit_4.macu.mult_res[15]` | -0.084674 | Deep logic and shared launch load: 20 stages; fanout 15; HA_X1 `_115122_/S`, `ddin[8]/Q` | Coordinated HA and launch-cone sizing/cloning. Independent sizing may increase upstream capacitance enough to lose its downstream benefit. |
| `dct_block_7.dct_unit_2.macu.mult_res[18]` | -0.083894 | Deep carry/sum chain: 22 stages; fanout 17; FA_X1 `_109354_/S`, HA_X1 `_115805_/S` | Joint FA/HA sizing or arithmetic restructuring. Single-move trials may reject intermediate states before a beneficial sequence completes. |
| `dct_block_5.dct_unit_4.macu.mult_res[17]` | -0.083520 | Deep logic and weak/shared drive: 21 stages; fanout 15; OAI221_X1 `_095447_/ZN`, `ddin[8]/Q` | OAI sizing/pin assignment plus launch-load reduction. High-fanout-only generation misses this regime. |

These are structural inferences. The supplied evidence does not establish long wire, IO constraints, or clock skew as dominant causes for these five register endpoints.

Other design leaders need different treatment:

- **Ibex:** unresolved 943-load X1 trunk plus 33–37 stages.
- **AES:** slow-slew 14–16-stage cones, including OAI33_X1 `_19597_/ZN`; the worst path has fanout only 4.
- **GCD:** 14-stage paths with DFF_X1 launch drive and maximum fanout 8.

Ibex and JPEG contribute **75.550/76.891 ns ≈ 98.3%** of remaining absolute TNS.

## 4. Regressions

These are regressions against the supplied path reference, not demonstrated incremental damage versus champion. No tree was built. Shared-cone capacitance and slew changes are probable mechanisms; per-move traces are needed for attribution.

| Design | Endpoint | Reference → candidate slack (ns) | Loss |
|---|---|---:|---:|
| GCD | `resp_msg[8]` | +0.0212 → +0.0043 | 16.9 ps |
| GCD | `resp_msg[2]` | +0.0617 → +0.0610 | 0.7 ps |
| GCD | `resp_msg[3]` | +0.0255 → +0.0254 | 0.1 ps |
| GCD | `resp_msg[9]` | +0.0032 → +0.0032 | Hidden by rounding |
| AES | `sa10_sr[3]$_DFF_P_/D` | -0.0227 → -0.0241 | 1.4 ps |
| Ibex | `instr_addr_o[30]` | -0.0522 → -0.0587 | 6.5 ps |
| Ibex | `instr_addr_o[22]` | +0.0001 → -0.0155 | 15.6 ps |
| Ibex | `instr_addr_o[23]` | +0.0106 → +0.0033 | 7.3 ps |
| Ibex | `instr_addr_o[26]` | +0.0267 → +0.0102 | 16.5 ps |
| Ibex | `instr_addr_o[27]` | +0.0217 → +0.0155 | 6.2 ps |
| JPEG | Block2/unit4/result18 | -0.0843 → -0.0851 | 0.8 ps |
| JPEG | Block3/unit3/result16 | -0.0827 → -0.0828 | 0.1 ps |
| JPEG | Block2/unit2/result16 | -0.0825 → -0.0826 | 0.1 ps |
| JPEG | Block7/unit4/result17 | -0.0819 → -0.0825 | 0.6 ps |

GCD output slack consumption and Ibex address-output regressions indicate shared-cone tradeoffs that aggregate WNS/TNS checks permit. **`instr_addr_o[22]` crosses zero**, directly motivating endpoint protection. AES and JPEG show slack redistribution among competing critical cones.

The reference counts **4/1/13/4** regressed endpoints across GCD/AES/Ibex/JPEG. The examples supplied do not enumerate all 13 Ibex regressions.

## 5. Recommendation for the next iteration

1. **Buffering: make tree activation observable and feasible.** Explicitly schedule `_26153_/ZN` during recovery. Log target visitation, eligibility failures, max-cap infeasibility, model rejection, application failure, and STA rollback. Replace the four-group ceiling with capacitance-driven group counts or recursive trees. Measure several feasible variants in journals, including variants screened out by the approximate 1 ps threshold. Require an applied tree and reduced fanout before claiming the hypothesis was tested.

2. **Buffering: implement the stated recovery contract.** Restrict tree trials to recovery; evaluate driver resizing and tree insertion atomically. Ratchet WNS after accepted moves and protect initially near-zero endpoints, including `instr_addr_o[22]`. Verify connectivity, parasitics, and timing restoration after rollback.

3. **Sizing/arithmetic: target JPEG if functioning Ibex trees fail measured STA.** Evaluate small coordinated launch/HA/FA/OAI sizing bundles and selective splitting at fanouts **12–17**. JPEG retains **-31.151 ns TNS**; **77 of 169** recovery trials failed WNS, so diagnose upstream-load penalties before increasing trial budgets.

**Do not repeat** the same lumped-model-only, maximum-four-group search and interpret another zero-application result as evidence against timing-driven buffering.

```json
{
  "recommended_cluster": "buffering",
  "dominant_cause": "high_fanout",
  "lesson": "Zero applied trees and unchanged fanout 943 mean candidate 0017 did not test timing-driven load isolation; establish activation and measure feasible journaled variants before tuning the heuristic.",
  "dead_end": "The current maximum-four-group lumped-RC prefilter produced zero applied trees and zero gain versus champion.",
  "good_changes": [
    "Inherited src/rsz/src/policy/SetupLegacyPolicy.cc::runTnsRecovery retained 17/22/30/34 moves across GCD/AES/Ibex/JPEG; no new 0017 mechanism demonstrated benefit."
  ],
  "bad_changes": [
    "src/rsz/src/move/SplitLoadGenerator.cc screens 16 modeled variants but returns at most one and produced zero applied trees.",
    "src/rsz/src/move/SplitLoadCandidate.cc::applyFanoutTree does not resize the original driver.",
    "The shared generator lacks recovery-only gating, and recovery lacks the promised ratcheting WNS floor and near-zero endpoint guard."
  ],
  "files_to_revisit": [
    "src/rsz/src/move/SplitLoadGenerator.cc",
    "src/rsz/src/move/SplitLoadCandidate.cc",
    "src/rsz/src/move/SplitLoadCandidate.hh",
    "src/rsz/src/policy/SetupLegacyPolicy.cc"
  ],
  "files_to_avoid": [
    "src/rsz/src/RepairHold.cc"
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

## iteration 15 (buffering)

Do not repeat greedy-loop cut reranking with a first-order RC model and one lowest-drive buffer at the driver location.

## iteration 16 (setup_strategy)

Do not repeat the bundled lambda-sum recovery replacement with only higher price growth or larger search budgets.

## iteration 17 (buffering)

The current maximum-four-group lumped-RC prefilter produced zero applied trees and zero gain versus champion.


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

## iteration 15 (buffering)

Immediate-sink model-ranked SplitLoad cuts inside the stock loop regressed champion-relative score; test downstream-weighted cuts in an isolated measured phase with a monotonic WNS floor.

## iteration 16 (setup_strategy)

Multiplicative endpoint prices retained Ibex's shared-driver bias and worsened TNS magnitude by 28.53% versus champion; isolate cone diversity and structural move coverage before retuning prices.

## iteration 17 (buffering)

Zero applied trees and unchanged fanout 943 mean candidate 0017 did not test timing-driven load isolation; establish activation and measure feasible journaled variants before tuning the heuristic.


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

## proposed by planner, iteration 15

Topology-changing moves (split/clone/buffer) must be accepted only on measured STA under a dual WNS floor max(stock-final, last-commit) and must print predicted vs measured dTNS per committed move.

## proposed by planner, iteration 16

Post-stock recovery phases must use a ratcheting WNS floor (never below the best committed recovery WNS) and print lr/bottleneck counters showing how often target ranking differs from the champion's static ranking.

## proposed by planner, iteration 17

Structural tree rebuilds must print per-net fanout before/after and predicted vs measured dTNS, and must guard every endpoint whose pre-move slack is above -1 ps against falling below -1 ps, not only global WNS.

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
| 15 | buffering | TNS-weighted critical-sink isolation with measured cut-point search on shared bottleneck nets, inside the post-stock recovery phase | rejected | -0.00064 | score -0.00064 below required gain +0.00200 |
| 16 | setup_strategy | Lagrangian endpoint pricing with best-of-k measured moves and a ratcheting WNS floor in the post-stock TNS-recovery phase | rejected | -0.00014 | score -0.00014 below required gain +0.00200 |
| 17 | buffering | Required-time-ordered (LT-tree) fanout tree synthesis for shared high-fanout drivers as a measured move in the post-stock recovery phase | rejected | +0.00000 | score +0.00000 below required gain +0.00200 |
=== Durable cross-iteration experience ===
# Durable cross-iteration memory
All 17 records remain on disk. 15 are valid code experiments; 1 were accepted. Records marked infrastructure/no-code are not evidence about heuristic quality.

## Cluster portfolio
- buffering: 5 valid experiments, 0 accepted, best score +0.00000
- setup_strategy: 5 valid experiments, 1 accepted, best score +0.00206
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
- #15 [valid] rejected buffering: score -0.00064; files src/move/SplitLoadGenerator.cc, src/move/SplitLoadGenerator.hh, HYPOTHESIS.md; TNS-weighted critical-sink isolation with measured cut-point search on shared bottleneck nets, inside the post-stock recovery phase
- #16 [valid] rejected setup_strategy: score -0.00014; files src/policy/SetupLegacyPolicy.cc, src/policy/SetupLegacyPolicy.hh, HYPOTHESIS.md; Lagrangian endpoint pricing with best-of-k measured moves and a ratcheting WNS floor in the post-stock TNS-recovery phase
- #17 [valid] rejected buffering: score +0.00000; files src/move/SplitLoadGenerator.cc, src/move/SplitLoadGenerator.hh, src/move/SplitLoadCandidate.cc, src/move/SplitLoadCandidate.hh, HYPOTHESIS.md; Required-time-ordered (LT-tree) fanout tree synthesis for shared high-fanout drivers as a measured move in the post-stock recovery phase

## File outcome history
- HYPOTHESIS.md: 15 tries, 1 accepted, best +0.00206
- src/policy/SetupLegacyPolicy.cc: 5 tries, 1 accepted, best +0.00206
- src/policy/SetupLegacyPolicy.hh: 4 tries, 1 accepted, best +0.00206
- src/move/SizeUpGenerator.cc: 4 tries, 0 accepted, best +0.00000
- src/move/SizeUpGenerator.hh: 3 tries, 0 accepted, best +0.00000
- src/move/SizeUpCandidate.hh: 1 tries, 0 accepted, best +0.00000
- src/move/SplitLoadGenerator.cc: 3 tries, 0 accepted, best +0.00000
- src/move/SplitLoadGenerator.hh: 2 tries, 0 accepted, best +0.00000
- src/move/SplitLoadCandidate.cc: 1 tries, 0 accepted, best +0.00000
- src/move/SplitLoadCandidate.hh: 1 tries, 0 accepted, best +0.00000
- src/Rebuffer.cc: 1 tries, 0 accepted, best -0.00004
- src/Rebuffer.hh: 1 tries, 0 accepted, best -0.00004
- src/move/RebufferMtGenerator.cc: 1 tries, 0 accepted, best -0.00004
- src/move/BufferGenerator.cc: 1 tries, 0 accepted, best -0.00039
- src/move/BufferGenerator.hh: 1 tries, 0 accepted, best -0.00039
- src/policy/SetupLegacyBase.cc: 1 tries, 0 accepted, best -0.00276
- src/policy/SetupLegacyBase.hh: 2 tries, 0 accepted, best -0.00276
- src/Optimizer.cc: 1 tries, 0 accepted, best -0.00276

## Detailed most recent 8 records
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

## Iteration 15: rejected · buffering
- **Evidence status:** valid algorithm experiment
- **Hypothesis:** TNS-weighted critical-sink isolation with measured cut-point search on shared bottleneck nets, inside the post-stock recovery phase
- **Score:** vs champion -0.00064; vs baseline +0.00142
- **Files planned:** src/policy/SetupLegacyPolicy.cc, src/policy/SetupLegacyPolicy.hh, src/move/SplitLoadGenerator.cc, src/move/SplitLoadGenerator.hh, src/move/CloneGenerator.cc, src/move/CloneGenerator.hh
- **Files changed:** src/move/SplitLoadGenerator.cc, src/move/SplitLoadGenerator.hh, HYPOTHESIS.md
- **Patch scope:** 1 files, +186/-28 lines
- **Verdict reasons:** score -0.00064 below required gain +0.00200
- **nangate45/gcd: score +0.00000; WNS -0.0222->-0.0222 ns (d +0.0000); TNS -0.342->-0.342 ns (d +0.000)**
- **nangate45/aes: score -0.00128; WNS -0.0241->-0.0260 ns (d -0.0018); TNS -0.999->-1.057 ns (d -0.059)**
- **nangate45/ibex: score +0.00007; WNS -0.0742->-0.0740 ns (d +0.0002); TNS -44.399->-44.244 ns (d +0.155)**
- **nangate45/jpeg: score -0.00134; WNS -0.0853->-0.0880 ns (d -0.0027); TNS -31.151->-30.918 ns (d +0.233)**
- **Dominant cause:** deep_logic
- **Lesson:** Immediate-sink model-ranked SplitLoad cuts inside the stock loop regressed champion-relative score; test downstream-weighted cuts in an isolated measured phase with a monotonic WNS floor.
- **Dead end:** Do not repeat greedy-loop cut reranking with a first-order RC model and one lowest-drive buffer at the driver location.
- **Recommended next cluster:** buffering
- **Bad changes:** src/rsz/src/move/SplitLoadGenerator.cc: rankCutPoints changes stock-loop candidate ordering and yields score -0.00064 versus champion., src/rsz/src/move/SplitLoadGenerator.cc: immediate sink slack does not implement downstream violating-endpoint weighting., src/rsz/src/move/SplitLoadGenerator.cc: lowestDriveBufferCell and driver-location placement omit buffer-size and centroid searches.
- **Files to revisit:** src/rsz/src/policy/SetupLegacyPolicy.cc, src/rsz/src/move/SplitLoadGenerator.cc, src/rsz/src/move/SplitLoadCandidate.cc
- **Files to avoid:** src/rsz/src/policy/SetupParallelEvalPolicy.cc, src/rsz/src/SkewBudget.hh

## Iteration 16: rejected · setup_strategy
- **Evidence status:** valid algorithm experiment
- **Hypothesis:** Lagrangian endpoint pricing with best-of-k measured moves and a ratcheting WNS floor in the post-stock TNS-recovery phase
- **Score:** vs champion -0.00014; vs baseline +0.00192
- **Files planned:** src/policy/SetupLegacyPolicy.cc, src/policy/SetupLegacyPolicy.hh
- **Files changed:** src/policy/SetupLegacyPolicy.cc, src/policy/SetupLegacyPolicy.hh, HYPOTHESIS.md
- **Patch scope:** 1 files, +338/-17 lines
- **Verdict reasons:** score -0.00014 below required gain +0.00200
- **nangate45/gcd: score +0.00014; WNS -0.0222->-0.0222 ns (d -0.0000); TNS -0.342->-0.335 ns (d +0.007)**
- **nangate45/aes: score -0.00005; WNS -0.0241->-0.0242 ns (d -0.0001); TNS -0.999->-1.019 ns (d -0.020)**
- **nangate45/ibex: score -0.00067; WNS -0.0742->-0.0746 ns (d -0.0004); TNS -44.399->-57.068 ns (d -12.668)**
- **nangate45/jpeg: score +0.00003; WNS -0.0853->-0.0853 ns (d +0.0000); TNS -31.151->-30.637 ns (d +0.513)**
- **Dominant cause:** high_fanout
- **Lesson:** Multiplicative endpoint prices retained Ibex's shared-driver bias and worsened TNS magnitude by 28.53% versus champion; isolate cone diversity and structural move coverage before retuning prices.
- **Dead end:** Do not repeat the bundled lambda-sum recovery replacement with only higher price growth or larger search budgets.
- **Recommended next cluster:** setup_strategy
- **Good changes:** src/rsz/src/policy/SetupLegacyPolicy.cc: measured alternatives selected later moves on 17 of 57 JPEG commits; JPEG TNS improved 0.513403 ns versus champion, although causal contribution is not isolated., src/rsz/src/policy/SetupLegacyPolicy.cc: six-round/600-trial bounds completed all four measured runs.
- **Bad changes:** src/rsz/src/policy/SetupLegacyPolicy.cc: lambda-sum ranking over 400 paths and 50 drivers changed Ibex ordering in only one of six rounds., src/rsz/src/policy/SetupLegacyPolicy.cc: fixed 16-endpoint veto excludes most endpoints and initially nonviolating outputs., src/rsz/src/policy/SetupLegacyPolicy.cc: best-of-three move types does not ensure clone/split/buffer coverage.
- **Files to revisit:** src/rsz/src/policy/SetupLegacyPolicy.cc, src/rsz/src/move/CloneGenerator.cc, src/rsz/src/move/SplitLoadGenerator.cc, src/rsz/src/move/BufferGenerator.cc, src/rsz/src/move/SizeUpGenerator.cc
- **Files to avoid:** src/sta/, src/rsz/src/policy/SetupLegacyBase.cc, src/rsz/src/Optimizer.cc

## Iteration 17: rejected · buffering
- **Evidence status:** valid algorithm experiment
- **Hypothesis:** Required-time-ordered (LT-tree) fanout tree synthesis for shared high-fanout drivers as a measured move in the post-stock recovery phase
- **Score:** vs champion +0.00000; vs baseline +0.00206
- **Files planned:** src/Rebuffer.cc, src/Rebuffer.hh, src/move/BufferGenerator.cc, src/move/BufferGenerator.hh, src/policy/SetupLegacyPolicy.cc
- **Files changed:** src/move/SplitLoadGenerator.cc, src/move/SplitLoadGenerator.hh, src/move/SplitLoadCandidate.cc, src/move/SplitLoadCandidate.hh, HYPOTHESIS.md
- **Patch scope:** 1 files, +404/-19 lines
- **Verdict reasons:** score +0.00000 below required gain +0.00200
- **nangate45/gcd: score +0.00000; WNS -0.0222->-0.0222 ns (d +0.0000); TNS -0.342->-0.342 ns (d +0.000)**
- **nangate45/aes: score +0.00000; WNS -0.0241->-0.0241 ns (d +0.0000); TNS -0.999->-0.999 ns (d +0.000)**
- **nangate45/ibex: score +0.00000; WNS -0.0742->-0.0742 ns (d +0.0000); TNS -44.399->-44.399 ns (d +0.000)**
- **nangate45/jpeg: score +0.00000; WNS -0.0853->-0.0853 ns (d +0.0000); TNS -31.151->-31.151 ns (d +0.000)**
- **Dominant cause:** high_fanout
- **Lesson:** Zero applied trees and unchanged fanout 943 mean candidate 0017 did not test timing-driven load isolation; establish activation and measure feasible journaled variants before tuning the heuristic.
- **Dead end:** The current maximum-four-group lumped-RC prefilter produced zero applied trees and zero gain versus champion.
- **Recommended next cluster:** buffering
- **Good changes:** Inherited src/rsz/src/policy/SetupLegacyPolicy.cc::runTnsRecovery retained 17/22/30/34 moves across GCD/AES/Ibex/JPEG; no new 0017 mechanism demonstrated benefit.
- **Bad changes:** src/rsz/src/move/SplitLoadGenerator.cc screens 16 modeled variants but returns at most one and produced zero applied trees., src/rsz/src/move/SplitLoadCandidate.cc::applyFanoutTree does not resize the original driver., The shared generator lacks recovery-only gating, and recovery lacks the promised ratcheting WNS floor and near-zero endpoint guard.
- **Files to revisit:** src/rsz/src/move/SplitLoadGenerator.cc, src/rsz/src/move/SplitLoadCandidate.cc, src/rsz/src/move/SplitLoadCandidate.hh, src/rsz/src/policy/SetupLegacyPolicy.cc
- **Files to avoid:** src/rsz/src/RepairHold.cc

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
