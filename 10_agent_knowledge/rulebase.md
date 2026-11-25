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

## proposed by planner, iteration 18

A structural-move hypothesis is untested unless RSZ_EVOLVE counters show at least one committed application on the named target net; zero-application runs must be logged as infrastructure, not as evidence against the idea.

## proposed by planner, iteration 19

Recovery-phase target ranking must exclude clock-network pins (vertices before launch CK->Q) and print clock_stages_excluded; any comparison of alternatives must restore one identical checkpoint and print evaluated/committed counts per alternative type.
