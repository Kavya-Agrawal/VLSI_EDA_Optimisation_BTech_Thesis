# Two-phase setup repair: stock LEGACY loop + bottleneck TNS recovery

## Problem
In-loop TNS-aware changes found large Ibex TNS gains but perturbed the stock greedy trajectory and lost WNS on AES/gcd/JPEG. Shared trunk drivers (e.g. Ibex `_26153_` fanout 943, JPEG HA/FA drivers) are only touched when they sit on the worst path of the endpoint currently being repaired.

## Current heuristic
`SetupLegacyPolicy::iterate` / `repairEndpoint` (src/policy/SetupLegacyPolicy.cc) walks violating endpoints worst-first and repairs each one's worst path via `SetupLegacyBase::repairPath`. Nothing ranks drivers by how many violating paths they serve.

## New approach
The stock loop is unchanged. After it, for the LEGACY phase only, `SetupLegacyPolicy::runTnsRecovery`:
1. Snapshots design WNS W* (absolute floor, never rolled).
2. Up to 5 rounds: re-collect violating endpoints, unroll the worst path of the top 400, and rank driver pins by sum of (-endpoint slack) over those paths.
3. For the top 50 drivers (resolved by name each time), open a journal, run the stock generator sequence via `tryRepairTarget` (up to 3 attempts, excluding move types already rejected for that driver), refresh parasitics/timing, then keep the move only if WNS >= W* and TNS improves by >= 0.5 ps. Otherwise `restoreJournal`.
4. Stops when a round keeps nothing, after 5 rounds, or at max(30, 10% of stock moves) kept moves.

## Why WNS/TNS should improve
Final WNS >= stock WNS by construction. Moves on shared trunks help many endpoints at once, so TNS rises. Moves on shared drivers of the worst cone can also raise WNS.

## What to look for in the path report
Fewer violating endpoints sharing a common upstream driver (upsized/buffered trunk); unchanged or better worst path; `RSZ_EVOLVE bottleneck_kept` > 0.

## Risks
TNS-only gains may be under-weighted by the score. Each trial needs a timing update, which may slow JPEG (bounded by 5 rounds x 50 drivers x 3 attempts). Pass count `bottleneck_rejected_*` shows how selective the floor is.

## Counters
`bottleneck_rounds`, `bottleneck_drivers_ranked`, `bottleneck_trials`, `bottleneck_kept`, `bottleneck_rejected_wns`, `bottleneck_rejected_tns` (printed as `RSZ_EVOLVE <name> fired=<n>`).

## Files changed
- src/policy/SetupLegacyPolicy.cc: `runTnsRecovery` and its call after the stock loop, plus counters.
- src/policy/SetupLegacyPolicy.hh: declaration of `runTnsRecovery`.
