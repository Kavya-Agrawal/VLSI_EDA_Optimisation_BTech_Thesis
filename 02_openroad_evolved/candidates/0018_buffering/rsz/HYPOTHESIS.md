# Hypothesis: criticality-partitioned critical-sink replica cloning

## Problem
Shared high-fanout drivers (Ibex AND2 `_26153_`, 943 loads; JPEG fanout 12-17 launch drivers) put the full net load
on every critical path through them. Stock cloning moves the *tolerant* half of the sinks to a half-power clone, which
leaves the critical sinks on a still-heavy net.

## Current heuristic
`src/move/CloneGenerator.cc:CloneGenerator::generate` -> `selectMovedLoads` (least critical half to a
`halfDrivingPowerCell` clone).

## New approach
Per driver with fanout >= 12, the first request keeps the stock behaviour. Repeat requests (the recovery phase in
`SetupLegacyPolicy::runTnsRecovery` re-targets a driver after a journaled trial is rejected) rotate through up to 6
variants: a same-strength replica that takes only the most critical sinks (top 5/15/30/50/33/25 % by slack delta).
Tolerant sinks stay on the original driver. At most 40 drivers get variants. The existing journaled trial in the
recovery loop is the measured selector (WNS floor + TNS gain), so bad variants are rolled back.
Departure from the planner's text: the policy file is not editable, so best-of-k is realised as sequential
trial/rollback rather than one multi-variant evaluation, and the tolerant net is not rebuffered.

## Why WNS/TNS should improve
Critical sinks see a replica with a small load (tens of ps saved at the shared stage), with no added buffer stage.

## Path report
Shared driver stage delay and fanout drop on the worst paths; a `clone` instance appears as the startpoint's driver.

## Risks
Placement/legalization of replicas, extra fan-in load on the AND2 cone, extra trials runtime. The first request on
any driver is unchanged so stock-phase behaviour is mostly preserved, but later stock requests for a driver also
rotate variants.

## Files changed
- src/move/CloneGenerator.cc: variant selection, counters, destructor printing `RSZ_EVOLVE` lines.
- src/move/CloneGenerator.hh: per-driver attempt map and counters.
