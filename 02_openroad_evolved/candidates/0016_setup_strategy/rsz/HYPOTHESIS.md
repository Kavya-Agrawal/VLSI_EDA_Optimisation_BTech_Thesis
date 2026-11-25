# Lagrangian endpoint pricing, best-of-k measured moves, ratcheting WNS floor

## Problem
The post-stock `runTnsRecovery` ranked drivers by a memoryless sum of endpoint violations. It accepted the first improving move against a fixed stock-WNS floor. It saturates on shared trunks (Ibex fanout-943), misses independent cones (JPEG), and gives back WNS.

## Current heuristic
`src/policy/SetupLegacyPolicy.cc: SetupLegacyPolicy::runTnsRecovery`. The stock loop (`runMainRepairLoop`) is unchanged. The old routine is kept as the unused `runTnsRecoveryStatic`.

## New approach
- Each violating endpoint has a price lambda_e. It starts at 1, is multiplied by (1 + 0.5 * slack/WNS) each round while the endpoint stays violated, and is halved once it is repaired.
- Drivers are ranked by the sum of lambda_e over the distinct downstream endpoints. These come from the worst-path expansion of up to 400 endpoints.
- Per driver, best-of-3: up to 3 distinct move types are measured from the same journal checkpoint, each rolled back. The best-TNS type is re-applied alone, re-verified and committed.
- A commit requires WNS >= max(stock-final, best-so-far), and none of the 16 highest-price endpoints may lose more than 0.2 ps.
- Drivers that fail are skipped in later rounds until something commits, so repricing reaches deeper drivers.
- Budget: 6 rounds and 600 trials.

## Why WNS/TNS should improve
Prices persistently focus effort on endpoints that stay violated (independent JPEG cones). Best-of-k avoids first-improving local traps. The ratchet and veto prevent WNS give-back.

## Path report
Look for fewer residual violators in deep cones and WNS never below stock. Check the `RSZ_EVOLVE lr_*` counters, especially `lr_rank_changed_vs_static`.

## Risks
Best-of-k adds runtime (capped at 600 trials). Gains may not survive detailed placement. The veto may block AES moves.

## Files changed
- src/policy/SetupLegacyPolicy.cc: new `runTnsRecovery` (LR pricing, best-of-k, ratchet, veto, counters). The old version is renamed `runTnsRecoveryStatic`.
- src/policy/SetupLegacyPolicy.hh: declares `runTnsRecoveryStatic`.
