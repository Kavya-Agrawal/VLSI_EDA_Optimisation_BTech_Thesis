# TNS-weighted lexicographic acceptance in the LEGACY setup loop

## Problem
Stock LEGACY repair promotes a pass only if design WNS improves, or WNS is
equal and the targeted endpoint's slack improves. Moves that help many
violating endpoints through a shared cone (Ibex trunk) but do not move the
target are rolled back, while locally helpful moves that damage side paths
(AES) can be kept.

## Current heuristic
`src/policy/SetupLegacyPolicy.cc: SetupLegacyPolicy::pathImproved`, used in
`repairEndpoint` to choose between `saveImprovedCheckpoint` and the
decreasing-slack counter / `restoreEndpointState`.

## New approach
`SetupLegacyPolicy::passAccepted` (called in place of `pathImproved`), using
OpenSTA's incrementally maintained design TNS read after each pass:
1. Reject if design WNS or the endpoint slack worsens by more than 1 ps
   (guard band).
2. Veto a pass if its TNS loss exceeds 2x its endpoint gain (+1 ps).
3. Otherwise accept iff `dTNS + lambda * dEndpointSlack > 0`, with
   `lambda = max(1, violators/4)`.
When dTNS equals the endpoint's own change this reduces to stock behaviour.
Target ranking, generators and journaling are unchanged; a rejected pass takes
the existing non-improving path (counter, force_single_repair, restore).
`EndpointRepairState::prev_pass_tns` holds TNS at the last checkpoint.

## Why WNS/TNS should improve
Shared-trunk moves with large aggregate TNS gain are kept; moves that trade
side-path slack for a small endpoint gain are dropped, so AES TNS stops
regressing. The 1 ps band keeps WNS from degrading.

## What to look for in the path report
Ibex trunk (`_26153_`) cell upsized/buffered and several endpoints improving
together; fewer AES side-path regressions. Lines `RSZ_EVOLVE ... fired=`.

## Risks
TNS-driven accepts may allow up to 1 ps WNS loss per accepted pass and may
stall per-endpoint progress; one TNS query per pass adds a little runtime.

## Files changed
- src/policy/SetupLegacyPolicy.cc: `passAccepted`, counters, RSZ_EVOLVE output, TNS checkpointing.
- src/policy/SetupLegacyPolicy.hh: declaration and counter members.
- src/policy/SetupLegacyBase.hh: `prev_pass_tns` in `EndpointRepairState`.
