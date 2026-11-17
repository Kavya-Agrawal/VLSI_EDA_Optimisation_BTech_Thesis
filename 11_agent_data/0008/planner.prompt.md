You are the **Planning Agent** of an evolution loop that improves OpenROAD's Resizer (`src/rsz`) so that
`repair_timing` leaves better WNS/TNS on placed designs. You do not write C++. You choose ONE algorithm
cluster and write a hypothesis that a coding sub-agent will implement in this iteration.

Iteration: 8. Champion so far: original rsz (no accepted change yet).
Benchmarks (tier A): nangate45/gcd, nangate45/aes, nangate45/ibex. Spend so far: spent $0.94 / 20.00, 4,225,815 tokens over 22 calls.

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
- Be concrete: name files and functions from the cluster dossier; say what decision the algorithm makes today and
  what it should make instead; predict the observable effect in the path report.

Available material (read them; cwd is 09_agent_context):
- 00_BIG_PICTURE.md, algorithms/<cluster>.md, files/*.md, EVAL_CONTRACT.md, clusters.json
- 10_agent_knowledge/{rulebase,lessons,hypotheses_ledger,dead_ends}.md
- 10_agent_knowledge/iterations/*.json and EXPERIENCE.md (durable quantitative experiment memory)
- Latest evaluator feedback (below) and 05_baseline_results/SUMMARY.md

=== Latest evaluator feedback ===
# Feedback for iteration 7 (0007_buffering, cluster buffering)

```
vs champion:
REJECT  score=-0.00156
  nangate45/gcd      WNS -0.1742 -> -0.1742 ns  TNS -7.626 -> -7.626 ns  score +0.00000
  nangate45/aes      WNS -0.1083 -> -0.1136 ns  TNS -14.773 -> -15.758 ns  score -0.00467
  nangate45/ibex     WNS -0.2994 -> -0.2994 ns  TNS -416.273 -> -416.273 ns  score +0.00000
  ! score -0.00156 below required gain +0.00200

vs baseline:
ACCEPT  score=-0.00156
  nangate45/gcd      WNS -0.1742 -> -0.1742 ns  TNS -7.626 -> -7.626 ns  score +0.00000
  nangate45/aes      WNS -0.1083 -> -0.1136 ns  TNS -14.773 -> -15.758 ns  score -0.00467
  nangate45/ibex     WNS -0.2994 -> -0.2994 ns  TNS -416.273 -> -416.273 ns  score +0.00000
```

Could not save `feedback.md`: this session permits read-only filesystem access. Complete contents follow.

## 1. Outcome

**REJECT vs champion.** Score **−0.001557**, missing the required **+0.002000** by **0.003557**. The authoritative baseline verdict is **ACCEPT**, despite the same negative score; it does not establish a timing gain.

Deltas below are candidate minus champion; negative means worse.

| Design | WNS reference → candidate (ns) | ΔWNS (ns) | TNS reference → candidate (ns) | ΔTNS (ns) | Score |
|---|---:|---:|---:|---:|---:|
| nangate45/gcd | −0.174175 → −0.174175 | 0 | −7.626171 → −7.626171 | 0 | 0 |
| nangate45/aes | −0.108289 → −0.113630 | −0.005341 | −14.773421 → −15.758012 | −0.984591 | −0.004672 |
| nangate45/ibex | −0.299412 → −0.299412 | 0 | −416.272895 → −416.272895 | 0 | 0 |

AES negative-slack magnitude increased **6.665%**. Both replicates were deterministic. All six unit targets and ten smoke tests passed; functional gates did not detect the timing regression.

## 2. Did the hypothesis do what it predicted?

**The implementation follows the proposed selection mechanism; measured results contradict its expected benefit.**

Only `src/rsz/src/move/SplitLoadGenerator.cc` differs from champion. It retains the focus sink, searches prefixes of the eligible ranked loads, estimates capacitance and target-slew buffer size, evaluates both transitions, rejects predicted moved-load violations, and ranks predicted worst-load slack gain with aggregate negative-slack gain as tie-breaker.

Observed effects:

- **GCD and Ibex:** identical WNS, TNS, and reported endpoint lists. No incremental shared-load repair benefit.
- **AES:** zero improved matched reported endpoints, eight regressed, and twelve entries replaced in the worst list. Multiple endpoints deteriorated together.
- AES `sa23_sr[4]` improved **35.671 ps** from its own pre-repair slack, but finished **9.768 ps worse than reference**. Similarly, `sa23_sr[0]` improved **33.711 ps** during repair yet lost **7.233 ps** against reference. These are repair-flow gains, not gains attributable to iteration 7.

The predictor uses HPWL capacitance and driver/buffer gate-delay changes. It retrieves wire resistance but does not use it, and does not propagate changed sink slew through downstream logic. Application independently calls `resizeToTargetSlew()` on the inserted net; predicted and realized cell/load agreement is unverified.

The logs do not attribute retained splits or report predicted versus realized endpoint deltas. Therefore, the evidence cannot distinguish inaccurate predictions from suppression of useful champion splits or subsequent repair-sequence changes.

## 3. Where the remaining negative slack comes from

The five worst endpoints globally are all Ibex endpoints; selecting one per design would omit worse paths.

| Endpoint | Slack (ns) | Likely cause | Applicable moves | Why this candidate likely did not resolve it |
|---|---:|---|---|---|
| `gen_regfile_ff.register_file_i.rf_reg[703]$_DFFE_PN0P_/D` | −0.299412 | Shared high fanout/weak drive; deep logic | Buffer tree, driver cloning, targeted sizing; logic-depth reduction | Prefix selection alone did not change final timing; retained-action attribution absent |
| `gen_regfile_ff.register_file_i.rf_reg[607]$_DFFE_PN0P_/D` | −0.299021 | Same shared bottleneck | Same | No measured change to the shared bottleneck |
| `gen_regfile_ff.register_file_i.rf_reg[831]$_DFFE_PN0P_/D` | −0.298793 | Same shared bottleneck | Same | A single added branch cannot be assumed sufficient for this load |
| `gen_regfile_ff.register_file_i.rf_reg[799]$_DFFE_PN0P_/D` | −0.298775 | Same shared bottleneck | Same | Existing eligibility and repair scheduling remain unchanged |
| `gen_regfile_ff.register_file_i.rf_reg[895]$_DFFE_PN0P_/D` | −0.298720 | Same shared bottleneck | Same | No verified reduction in driver delay or downstream arrival |

All five paths have **35 stages**, maximum fanout **943**, and the same reported worst driver, `AND2_X1@_26153_/ZN`, with raw slew **2,087,753,088**. Their slack spread is only **0.692 ps**, supporting investigation of a common bottleneck. Confirm whether the extreme-fanout net is a legal data-repair target before proposing a transformation.

The reports also tag these paths `io_constrained`, but attribution records startpoint `clk`; that tag alone does not establish an IO-budget cause. Long-wire delay and clock skew are unproven without RC and clock-arrival decomposition. Raw slew units require validation before physical interpretation.

For context, GCD’s worst paths have fanout at most eight, while split-load eligibility requires **fanout > 8**. This directly limits the changed mechanism’s reach there.

## 4. Regressions

All eight matched reported regressions occur in AES.

| Endpoint | Reference slack (ns) | Candidate slack (ns) | Loss (ps) |
|---|---:|---:|---:|
| `sa23_sr[4]$_DFF_P_/D` | −0.103862 | −0.113630 | 9.768 |
| `sa23_sr[7]$_DFF_P_/D` | −0.105271 | −0.112934 | 7.663 |
| `sa23_sr[0]$_DFF_P_/D` | −0.105239 | −0.112472 | 7.233 |
| `sa23_sr[5]$_DFF_P_/D` | −0.105222 | −0.111829 | 6.607 |
| `sa32_sr[7]$_DFF_P_/D` | −0.102820 | −0.111042 | 8.222 |
| `sa20_sr[7]$_DFF_P_/D` | −0.104571 | −0.110636 | 6.065 |
| `sa33_sr[1]$_DFF_P_/D` | −0.104054 | −0.109630 | 5.576 |
| `sa33_sr[3]$_DFF_P_/D` | −0.107356 | −0.109618 | 2.262 |

The four `sa23` paths share reported slow-driver structures around `_13069_` and `_13050_`; the worst path also contains `BUF_X1@place7593`. This is consistent with shared-cone collateral or lost repair opportunities, but does not identify a particular inserted buffer as responsible.

Probable mechanisms are omitted wire-resistance/downstream-slew effects, predicted versus applied sizing mismatch, and changed candidate availability affecting later repairs. The prediction-only moved-load guard cannot establish post-legalization endpoint safety. Worst-list turnover is not proof that departing endpoints improved.

## 5. Recommendation for the next iteration

**Recommended cluster: buffering.** Start from champion.

1. **Add measured split retention and attribution.** Record driver, moved sinks, predicted cell/gains, applied cell, and matched endpoint deltas. After parasitic refresh and legalization, reject moved-negative endpoint losses, newly negative moved endpoints, and affected-cone WNS/TNS regressions. Reproduce AES first.
2. **Compare selection policies under identical verification.** Evaluate champion’s half split and the proposed prefixes through journaled trials. This separates rejected useful splits from inaccurate positive predictions. Include actual downstream slew propagation; use the analytical estimate for ordering.
3. **Investigate the Ibex shared driver within existing eligibility.** Establish why `_26153_/ZN` receives no effective retained repair. If legally bufferable, compare a staged buffer tree with cloning using matched endpoint measurements; the first five endpoints should respond together if the attribution is correct.

**Do not repeat:** replacing champion’s selector with another prediction-only prefix policy without retained-split and post-legalization evidence. Do not revive iteration 5’s feasible-runner-up sizing fallback.

```json
{
  "recommended_cluster": "buffering",
  "dominant_cause": "high_fanout",
  "lesson": "Capacitance-aware prefix selection with predicted moved-load safety regressed AES WNS by 5.341 ps and TNS by 0.984591 ns, so split retention requires measured affected-endpoint checks after legalization.",
  "dead_end": "Do not repeat prediction-only prefix replacement without attributing retained splits and verifying post-legalization collateral.",
  "good_changes": [],
  "bad_changes": [
    "src/rsz/src/move/SplitLoadGenerator.cc: prefix selection replacement regressed AES and produced no measured GCD or Ibex benefit",
    "src/rsz/src/move/SplitLoadGenerator.cc: HPWL capacitance and gate-delay prediction omits wire resistance and downstream slew propagation"
  ],
  "files_to_revisit": [
    "src/rsz/src/move/SplitLoadGenerator.cc",
    "src/rsz/src/move/SplitLoadCandidate.cc",
    "src/rsz/src/Optimizer.cc"
  ],
  "files_to_avoid": [
    "src/rsz/src/move/SizeUpGenerator.cc",
    "src/rsz/src/move/SizeUpCandidate.cc"
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
=== Durable cross-iteration experience ===
# Durable cross-iteration memory
All 7 records remain on disk. 5 are valid code experiments; 0 were accepted. Records marked infrastructure/no-code are not evidence about heuristic quality.

## Cluster portfolio
- buffering: 2 valid experiments, 0 accepted, best score -0.00039
- setup_strategy: 0 valid experiments, 0 accepted, best score +0.00000
- sizing: 3 valid experiments, 0 accepted, best score +0.00000

## Complete compact history
- #1 [infra/no-code] crashed : score +0.00000; files none; Error: [('/Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/02_openroad_evolved/champion/rsz/test/save_defok', '/Users/kavyaagrawal/Desktop/G
- #2 [infra/no-code] rejected setup_strategy: score +0.00000; files none; You've hit your 5-hour limit · resets 7:50am (Asia/Calcutta)
- #3 [valid] rejected sizing: score +0.00000; files src/move/SizeUpGenerator.cc, src/move/SizeUpGenerator.hh, src/move/SizeUpCandidate.hh, HYPOTHESIS.md; Delay-gain driven multi-candidate gate sizing to eliminate critical-path slew degradation
- #4 [valid] rejected sizing: score +0.00000; files src/move/SizeUpGenerator.cc, HYPOTHESIS.md; Isolate absolute delay-gain ranking with API-compatible single-candidate sizing
- #5 [valid] rejected sizing: score +0.00000; files src/move/SizeUpGenerator.cc, src/move/SizeUpGenerator.hh, HYPOTHESIS.md; Recover suppressed sizing moves with cost-ranked feasible replacement selection
- #6 [valid] rejected buffering: score -0.00039; files src/move/BufferGenerator.cc, src/move/BufferGenerator.hh, HYPOTHESIS.md; Enable shared-critical-data rebuffering beyond the blanket fanout cutoff
- #7 [valid] rejected buffering: score -0.00156; files src/move/SplitLoadGenerator.cc, HYPOTHESIS.md; Choose split-load partitions by branch slack budgets instead of half the sink count

## File outcome history
- src/move/SizeUpGenerator.cc: 3 tries, 0 accepted, best +0.00000
- src/move/SizeUpGenerator.hh: 2 tries, 0 accepted, best +0.00000
- HYPOTHESIS.md: 5 tries, 0 accepted, best +0.00000
- src/move/SizeUpCandidate.hh: 1 tries, 0 accepted, best +0.00000
- src/move/BufferGenerator.cc: 1 tries, 0 accepted, best -0.00039
- src/move/BufferGenerator.hh: 1 tries, 0 accepted, best -0.00039
- src/move/SplitLoadGenerator.cc: 1 tries, 0 accepted, best -0.00156

## Detailed most recent 7 records
## Iteration 1: crashed · unassigned
- **Evidence status:** infrastructure/no-code record; do not infer heuristic quality
- **Hypothesis:** Error: [('/Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/02_openroad_evolved/champion/rsz/test/save_defok', '/Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/02_openroad_evolved/candidates/0001_buffering/rsz/test/save_defok', "[Errno 2] No such file or directory: '/Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/02_openroad_evolved/champion/rsz/test/save_defok'"), ('/Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/02_openroad_evolved/
- **Score:** vs champion +0.00000; vs baseline +0.00000
- **Files planned:** (not recorded)
- **Files changed:** (none)

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
