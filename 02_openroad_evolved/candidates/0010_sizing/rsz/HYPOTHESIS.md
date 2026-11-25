# Hypothesis: criticality-weighted size-up selection

## Problem
Stock SizeUpGenerator ranks eligible masters by (own-stage gain minus upstream input-cap penalty) per unit cost. The upstream penalty is charged at a fixed weight of 1, whatever the slack of the upstream driver or of the other sinks on the input net. Upsizing a gate in a shared cone therefore slows critical neighbours (e.g. AES `_13069_/Z`).

## Current heuristic
`src/move/SizeUpGenerator.cc: SizeUpGenerator::upsizeCell`. Score = (delay_old - delay_new) / cost_ratio, where delay = gateDelay + prev_drive * in_cap.

## New approach
In `upsizeCell` we compute lambda = clamp(max(0, -slack) / |WNS|, 0, 1) for the upstream driver and each side load of the input net, using live STA vertex slacks. The upstream penalty is charged by up_weight = 1 + min(sum lambda, 4). The new score is ((gate_old - gate_new) - up_weight * prev_drive * dCin) / cost_ratio.

- The stock eligibility test is unchanged, so the move count is preserved. The weighted score only picks among eligible masters, and it is allowed to go negative, so a move is never suppressed.
- With no violating neighbours up_weight = 1 and the score equals the stock score.

## Why WNS/TNS should improve
Masters with a large input-cap increase lose when the upstream driver or the other sinks are critical. Smaller steps win there, which protects shared cones. Where the upstream is slack-rich, stock ranking is kept.

## What to look for in the path report
- Fewer cases where a shared upstream driver's delay grows after an upsize.
- Smaller input-cap steps on cells fed by critical nets.
- The `RSZ_EVOLVE` lines: `sizing_choice_differs`, `sizing_neighbor_weighted` and `sizing_selections`.

## Risks
- Slacks can be stale between incremental timing updates.
- Weights are capped, and the stock eligibility rule is kept, to avoid a move-count collapse.
- Counters are printed from the generator destructor, so there may be one set of lines per policy or phase.

## Files changed
- `src/move/SizeUpGenerator.cc`: weighted selection, neighbour lambdas and counters.
- `src/move/SizeUpGenerator.hh`: destructor, counters, and `drvr_pin` parameter.
