# TNS-aware root choice for van Ginneken rebuffering

## Problem
`Rebuffer` picks the root buffer-tree option by worst-sink slack only. On shared nets with
several violating sinks, trees with the same worst slack can differ a lot in total violation (TNS).

## Current heuristic
`src/Rebuffer.cc:Rebuffer::selectTimingOptions` (max_plans==1 branch, used by `rebufferPin` and
`bufferForTiming`) picks the first unconstrained option, else the strictly largest driver slack.
The multi-plan branch sorts with `Rebuffer::timingOrder` (slack, cap, area, buffer count).

## New approach
The option-level total violation V is computed per root option, not as a third Pareto dimension
in the DP. `Rebuffer::totalSinkViolation` walks the option tree and accumulates the delays the DP
already stored (`BufferedNet::delay()` on wire/buffer nodes) plus the driver correction.
Each load's slack at the driver is `load->slack() - path delay + correction`. V is the sum of
the negative ones, and a count of violating sinks comes with it.
`Rebuffer::chooseLowestTnsOption` takes the stock-best option. If it has >= 2 violating sinks,
it considers every evaluated root option with slack >= S* - eps, where
eps = min(1 ps, 5% |S*|). It then picks the one with strictly lowest V. Ties keep the stock
order. With <= 1 violating sink it returns the stock choice exactly. The multi-plan branch moves
the chosen option to the front of the ranked list.

This is a post-hoc V over the (cap, slack) Pareto root set rather than a 3-D DP front. It adds no
DP cost, but it can only choose among options the 2-D front kept.

## Why WNS/TNS should improve
Among near-equal worst slack options, the one that leaves fewer/shallower violating sinks lowers
endpoint TNS on shared-net cones, while WNS stays within 1 ps of the stock pick.

## What to look for in the path report
Lower TNS / fewer violating endpoints on high-fanout shared nets, with an unchanged worst path.
Log lines: `RSZ_EVOLVE root_evals`, `multi_viol`, `root_choice_changed`, `tns_reduced`.

## Risks
- The Elmore V can mis-rank trees. The 1 ps tolerance may add up along the critical cone.
- The 2-D Pareto front may already have pruned the true TNS winner.
- Counters are cumulative atomics, printed and cleared at the end of each rebuffer phase
  (`RebufferMtGenerator::finishPhase`), `fullyRebuffer` and `rebufferNet`. Sum them for totals.

## Files changed
- `src/Rebuffer.cc`: V computation, TNS-aware root choice, counters and report.
- `src/Rebuffer.hh`: declarations for the helpers and `reportEvolveCounters`.
- `src/move/RebufferMtGenerator.cc`: print the counters when a rebuffer phase finishes.
