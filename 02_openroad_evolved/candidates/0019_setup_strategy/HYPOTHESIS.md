# Hypothesis: measured depth-2 beam search in post-stock TNS recovery

## Problem
Remaining WNS/TNS sits on deep FA/HA/AOI data chains (Ibex six-FA_X1 chains, JPEG 20-23 stage multiplier paths). A single-stage upsize is rejected because its input-cap penalty needs a matching upstream or downstream resize. The previous recovery committed the first single move that improved TNS, so it never saw coupled gains. Earlier DP and greedy variants lost WNS or caused endpoint collateral.

## Current heuristic
`src/policy/SetupLegacyPolicy.cc: SetupLegacyPolicy::runGreedyTnsRecovery` (the previous `runTnsRecovery`). It ranks drivers by slack-weighted path count and keeps the first single move that improves TNS with WNS held.

## New approach
`SetupLegacyPolicy::runBeamRecovery` (called from `runTnsRecovery`, LEGACY phase only), after the unchanged stock loop:
1. Seeds are ranked by slack-weighted violating-endpoint coverage times arc delay. Arc delay is the arrival difference across the driver stage. Only data arcs from launch Q to D count; clock-network paths (`Path::isClock`) are skipped.
2. For the top 8 seeds, two single-move variants are tried (best move type, then the next type). Each variant is also paired with the upstream and the downstream path driver, giving depth-2 sequences.
3. Each trial runs in nested ECO journals with incremental STA, then is rolled back. Only the best-TNS sequence per round is replayed and committed. A replay that no longer passes is rolled back and ends the search.
4. Acceptance requires all of:
   - WNS >= a ratcheting floor (the post-stock WNS, raised to the current WNS after each commit);
   - TNS gain >= 0.5 ps;
   - no endpoint that was >= -1 ps ends below -1 ps.
5. The search runs up to 12 rounds, bounded by max(30, stock_moves/10) commits.

## Why WNS/TNS should improve
Coupled upsizes (stage plus the neighbour whose load or drive it changes) are measured as a unit, so the input-cap penalty is paid for by its partner. The WNS floor and the endpoint guard stop the WNS losses and endpoint collateral seen before.

## What to look for in the path report
- `RSZ_EVOLVE beam_committed_pair` >= 1 on ibex and jpeg.
- Fewer FA/HA stages with a large arc delay on the worst paths.
- No endpoint newly below -1 ps.
- `beam_rejected_guard` and `beam_rejected_wns` counts, which show how strict the guards were.

## Risks
- Incremental-STA trial cost on JPEG: about 8 seeds x 2 variants x 3 trials per round.
- Strict guards may leave few commits.
- Coupled upsizes may hurt side paths on shared arithmetic cones.
- Seed ranking uses the arrival-difference arc delay, which includes the wire delay of the input net.

## Files changed
- `src/policy/SetupLegacyPolicy.cc`: new `runBeamRecovery` with RSZ_EVOLVE counters; `runTnsRecovery` now calls it; the old greedy body is renamed `runGreedyTnsRecovery` and left unreferenced.
- `src/policy/SetupLegacyPolicy.hh`: declarations for the two functions.
