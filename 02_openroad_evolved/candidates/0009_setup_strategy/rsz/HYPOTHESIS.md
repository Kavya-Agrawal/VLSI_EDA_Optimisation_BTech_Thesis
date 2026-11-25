# Hypothesis: rank repair targets by shared criticality

## Problem
Stock `SetupLegacyBase::repairPath` ranks the drivers of a single endpoint's worst path by local load-dependent delay only. A driver shared by hundreds of violating endpoints (e.g. Ibex `_26153_/ZN`, fanout 943) gets no priority over one that sits on a single path.

## Current heuristic
`src/policy/SetupLegacyBase.cc: rankPathDrivers` (load delay minus intrinsic delay per driver) and the `stable_sort` of `ranked_targets` in `repairPath`.

## New approach
`buildSharedCriticality()` takes the top 400 violating endpoints (sorted by slack, then endpoint name). It expands each worst path and adds the endpoint's normalised negative slack (slack / worst slack, in [0,1]) to every driver pin on that path. The result is a lookup-only map from pin to share. It is rebuilt every 25 `repairPath` calls. In `repairPath` the ranking key becomes `load_delay * (1 + share)`. Generators, acceptance and the repair budget are unchanged.

## Why WNS/TNS should improve
A move on a high-share driver improves many endpoints at once, so TNS should fall faster on Ibex and JPEG. AES has diffuse sharing, so it should stay close to stock.

## What to look for in the path report
Drivers with large fanout or reconvergent trunks on the worst paths should be upsized, buffered or cloned. Look for fewer endpoints failing through the same trunk driver. Also look for lost slack on non-violating sinks of reloaded nets.

## Risks
- Over-focus on a shared driver that no generator can improve. Stock behaviour is retained because the other drivers still follow in order.
- Collateral slack loss on non-violating sinks of reloaded nets.
- Extra STA path queries (up to 400 per build).

## Counters (printed once at the end of the run)
- `shared_rank_builds`: number of map builds.
- `shared_rank_paths_expanded`: number of paths expanded during builds.
- `shared_rank_passes`: number of `repairPath` calls that were re-ranked.
- `shared_rank_reordered_targets`: number of targets whose key was scaled.
- `shared_rank_changed_first`: number of passes where the top-ranked driver differs from stock.

## Files changed
- `src/policy/SetupLegacyBase.cc`: the shared map build, the re-ranking in `repairPath`, and the counters.
- `src/policy/SetupLegacyBase.hh`: declarations and state for the map and counters.
- `src/Optimizer.cc`: prints the RSZ_EVOLVE lines after the phase loop and on early exit.
