You are the **Planning Agent** of an evolution loop that improves OpenROAD's Resizer (`src/rsz`) so that
`repair_timing` leaves better WNS/TNS on placed designs. You do not write C++. You choose ONE algorithm
cluster and write a hypothesis that a coding sub-agent will implement in this iteration.

Iteration: 6. Champion so far: original rsz (no accepted change yet).
Benchmarks (tier A): nangate45/gcd, nangate45/aes, nangate45/ibex. Spend so far: spent $0.94 / 20.00, 1,838,745 tokens over 16 calls.

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
# Feedback for iteration 5 (0005_sizing, cluster sizing)

```
vs champion:
REJECT  score=+0.00000
  nangate45/gcd      WNS -0.1742 -> -0.1742 ns  TNS -7.626 -> -7.626 ns  score +0.00000
  nangate45/aes      WNS -0.1083 -> -0.1083 ns  TNS -14.773 -> -14.773 ns  score +0.00000
  nangate45/ibex     WNS -0.2994 -> -0.2994 ns  TNS -416.273 -> -416.273 ns  score +0.00000
  ! score +0.00000 below required gain +0.00200

vs baseline:
ACCEPT  score=+0.00000
  nangate45/gcd      WNS -0.1742 -> -0.1742 ns  TNS -7.626 -> -7.626 ns  score +0.00000
  nangate45/aes      WNS -0.1083 -> -0.1083 ns  TNS -14.773 -> -14.773 ns  score +0.00000
  nangate45/ibex     WNS -0.2994 -> -0.2994 ns  TNS -416.273 -> -416.273 ns  score +0.00000
```

Cannot save `feedback.md`: this session’s filesystem permissions are read-only. Completed content follows.

# 1. Outcome

**REJECT versus champion.** Score **+0.00000**, below the required **+0.00200**. Baseline verdict is **ACCEPT at parity**, with no measured improvement.

Deltas are candidate minus reference; positive timing deltas indicate improvement. Champion and baseline values are identical.

| Design | Reference → candidate WNS (ns) | ΔWNS (ns) | Reference → candidate TNS (ns) | ΔTNS (ns) |
|---|---:|---:|---:|---:|
| nangate45/gcd | -0.1742 → -0.1742 | 0.00000 | -7.626 → -7.626 | 0.00000 |
| nangate45/aes | -0.1083 → -0.1083 | 0.00000 | -14.773 → -14.773 | 0.00000 |
| nangate45/ibex | -0.2994 → -0.2994 | 0.00000 | -416.273 → -416.273 | 0.00000 |

Both replicates produced identical timing for each design. All six unit targets and ten smoke tests passed. API compatibility is no longer the blocker; timing effectiveness is.

# 2. Did the hypothesis do what it predicted?

**No measured incremental effect.**

The patch in `src/move/SizeUpGenerator.cc` checks `replacementPreservesMaxCap` before an improving contender updates the best score. The protected `upsizeCell` signature remains intact through a library-only wrapper; production generation supplies instance context and still emits at most one candidate.

Predicted evidence was recovered feasible replacements, changed drive strengths, and lower matched AES/Ibex data arrivals without additional logic stages. Observed reference comparisons show **zero improved, zero regressed, zero newly listed, and zero removed paths in every design**. No incremental arrival reduction or depth benefit is demonstrated.

AES’s implementation target was ΔWNS ≥ **+0.005 ns** and at least **1% lower TNS magnitude**—approximately **0.148 ns** less negative TNS. Both measured deltas are zero.

Pre/post-repair gains belong to the complete repair flow and are also achieved by the reference. For example, AES `sa23_sr[0]$_DFF_P_/D` improves by **0.040944 ns** during repair; this is not evidence for the new selection rule.

The available logs do not count suppressed winners, feasible runner-ups, or committed recoveries. Therefore, zero opportunities cannot be established: opportunities could be absent, rejected later, or timing-neutral. Reject the mechanism for promotion on tier A; its proposed causal explanation remains unverified.

# 3. Where the remaining negative slack comes from

The five worst reported endpoints across designs are all in Ibex.

| Endpoint | Slack (ns) | Stages / maximum fanout | Likely cause | Moves that should address it; likely limitation |
|---|---:|---:|---|---|
| `gen_regfile_ff.register_file_i.rf_reg[703]$_DFFE_PN0P_/D` | -0.299412 | 35 / 943 | High fanout, weak reported driver, deep logic | Buffering, load splitting, cloning, selective sizing. Master selection alone cannot partition the shared load or shorten the logic cone. |
| `gen_regfile_ff.register_file_i.rf_reg[607]$_DFFE_PN0P_/D` | -0.299021 | 35 / 943 | Same shared bottleneck | Split critical sinks from noncritical load; existing move eligibility, ordering, or acceptance may leave the bottleneck intact. |
| `gen_regfile_ff.register_file_i.rf_reg[831]$_DFFE_PN0P_/D` | -0.298793 | 35 / 943 | Same shared bottleneck | Clone or buffer the shared driver with upstream-loading checks. Feasible-runner-up ranking creates no new topology. |
| `gen_regfile_ff.register_file_i.rf_reg[799]$_DFFE_PN0P_/D` | -0.298775 | 35 / 943 | Same shared bottleneck | Criticality-aware buffering/load splitting; local sizing gain may be exhausted before shared-load relief occurs. |
| `gen_regfile_ff.register_file_i.rf_reg[895]$_DFFE_PN0P_/D` | -0.298720 | 35 / 943 | Same shared bottleneck | Load isolation first; logic restructuring if cell-delay decomposition confirms depth dominates afterward. |

All five list `AND2_X1@_26153_/ZN` as the worst-slew driver and `AOI221_X2@_22445_/ZN` second. Reported slew values are **2087753088.0** and **57608004.0**, respectively—a **36.2×** ratio. Treat these as raw report values until units and extraction are validated.

Ibex has **60 high-fanout tags among 61 reported paths**, and **40 deep-logic tags**. Its TNS contributes approximately **94.9%** of the combined three-design TNS magnitude. This makes shared-load repair the highest-priority experiment.

The `io_constrained` tags do not establish an IO-delay root cause for these register endpoints. Long-wire delay and clock skew are also unproven without net-delay and clock-arrival decomposition. Verify that `_26153_` belongs to the relevant data-path segment before targeting it.

# 4. Regressions

**No candidate-induced endpoint regressions versus the reference were reported.** All three reference comparisons have zero regressed paths.

A separate pre/post-repair regression appears in GCD:

| Endpoint | Pre-repair slack (ns) | Post-repair slack (ns) | Δslack |
|---|---:|---:|---:|
| `dpath.a_reg.out[12]$_DFFE_PP_/D` | -0.172143 | -0.173529 | **-0.001386 ns** |

The path reports `NOR2_X2@_950_/ZN` and `INV_X1@_977_/ZN` among its slowest drivers. Shared-load changes, upstream loading from sizing, or placement changes are plausible mechanisms; the report does not distinguish them. The reference has the same result, so this regression cannot be attributed to iteration 5.

# 5. Recommendation for the next iteration

1. **Buffering/load-splitting cluster:** target Ibex’s shared high-fanout cone after confirming data-path membership. In `src/move/SplitLoadGenerator.cc` and `src/move/BufferGenerator.cc`, prioritize partitions by critical-sink slack and capacitance. Measure matched arrivals, upstream slew, WNS/TNS, area, and hold effects against the champion.

2. **Cloning cluster:** inspect `src/move/CloneGenerator.cc` for eligibility and rejection reasons around the shared driver. Test duplication that separates critical register-file sinks from other loads; include the extra upstream input capacitance in acceptance.

3. **Setup-strategy cluster:** inspect why existing buffer/clone/split moves leave this cone unresolved. Record generated, rejected, committed, and rolled-back moves by type and instance before changing move order. Test shared-load repair earlier only if those records identify an ordering barrier.

**Do not repeat feasible-runner-up sizing selection on tier A without evidence of recovered opportunities.** Any revisit must count infeasible reference winners, profitable feasible alternatives, committed replacements, and their matched endpoint timing effects. Preserve the existing `upsizeCell` API.

```json
{
  "recommended_cluster": "buffering",
  "dominant_cause": "high_fanout",
  "lesson": "Moving upstream max-capacitance feasibility into sizing selection preserved compatibility but produced zero incremental tier-A timing benefit.",
  "dead_end": "Do not repeat feasible-runner-up sizing selection without measured recovery opportunities and attributable endpoint gains.",
  "good_changes": [
    "src/move/SizeUpGenerator.cc and src/move/SizeUpGenerator.hh preserved the protected upsizeCell API; all supplied unit and smoke gates passed, but no timing benefit was measured."
  ],
  "bad_changes": [
    "src/move/SizeUpGenerator.cc moved replacementPreservesMaxCap into contender selection with zero measured WNS, TNS, or reported endpoint improvement."
  ],
  "files_to_revisit": [
    "src/move/SplitLoadGenerator.cc",
    "src/move/BufferGenerator.cc",
    "src/move/CloneGenerator.cc",
    "src/policy/SetupLegacyPolicy.cc"
  ],
  "files_to_avoid": [
    "src/move/SizeUpGenerator.cc",
    "src/move/SizeUpGenerator.hh"
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


--- lessons.md ---
# Lessons

Appended by the planner after each iteration. Newest at the bottom.

## iteration 3 (sizing)

Candidate 0003 produced no timing evidence because the upsizeCell-to-upsizeCells API change broke test compilation, and all ten smoke logs failed during helper initialization.

## iteration 4 (sizing)

Absolute stage-gain ranking changed rising-edge replacement selection and failed unit gates before any benchmark timing benefit could be measured.

## iteration 5 (sizing)

Moving upstream max-capacitance feasibility into sizing selection preserved compatibility but produced zero incremental tier-A timing benefit.


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

=== Ledger (last entries) ===
# Hypotheses ledger

| iter | cluster | hypothesis (short) | verdict | score vs champion | note |
|---|---|---|---|---|---|
| 2 | setup_strategy | You've hit your 5-hour limit · resets 7:50am (Asia/Calcutta) | rejected | +0.00000 | score +0.00000 below required gain +0.00200 |
| 3 | sizing | Delay-gain driven multi-candidate gate sizing to eliminate critical-path slew degradation | rejected | +0.00000 | gates failed: //src/rsz/test:TestInsertBuffer=FAILED; //src/rsz/test:TestNestedJournal=FAILED; //src/rsz/test:TestPreChe |
| 4 | sizing | Isolate absolute delay-gain ranking with API-compatible single-candidate sizing | rejected | +0.00000 | gates failed: //src/rsz/test:TestResizer=FAILED; //src/rsz/test:cpp_tests=FAILED |
| 5 | sizing | Recover suppressed sizing moves with cost-ranked feasible replacement selection | rejected | +0.00000 | score +0.00000 below required gain +0.00200 |
=== Durable cross-iteration experience ===
# Durable cross-iteration memory
All 5 records remain on disk. 3 are valid code experiments; 0 were accepted. Records marked infrastructure/no-code are not evidence about heuristic quality.

## Cluster portfolio
- setup_strategy: 0 valid experiments, 0 accepted, best score +0.00000
- sizing: 3 valid experiments, 0 accepted, best score +0.00000

## Complete compact history
- #1 [infra/no-code] crashed : score +0.00000; files none; Error: [('/Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/02_openroad_evolved/champion/rsz/test/save_defok', '/Users/kavyaagrawal/Desktop/G
- #2 [infra/no-code] rejected setup_strategy: score +0.00000; files none; You've hit your 5-hour limit · resets 7:50am (Asia/Calcutta)
- #3 [valid] rejected sizing: score +0.00000; files src/move/SizeUpGenerator.cc, src/move/SizeUpGenerator.hh, src/move/SizeUpCandidate.hh, HYPOTHESIS.md; Delay-gain driven multi-candidate gate sizing to eliminate critical-path slew degradation
- #4 [valid] rejected sizing: score +0.00000; files src/move/SizeUpGenerator.cc, HYPOTHESIS.md; Isolate absolute delay-gain ranking with API-compatible single-candidate sizing
- #5 [valid] rejected sizing: score +0.00000; files src/move/SizeUpGenerator.cc, src/move/SizeUpGenerator.hh, HYPOTHESIS.md; Recover suppressed sizing moves with cost-ranked feasible replacement selection

## File outcome history
- src/move/SizeUpGenerator.cc: 3 tries, 0 accepted, best +0.00000
- src/move/SizeUpGenerator.hh: 2 tries, 0 accepted, best +0.00000
- HYPOTHESIS.md: 3 tries, 0 accepted, best +0.00000
- src/move/SizeUpCandidate.hh: 1 tries, 0 accepted, best +0.00000

## Detailed most recent 5 records
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
