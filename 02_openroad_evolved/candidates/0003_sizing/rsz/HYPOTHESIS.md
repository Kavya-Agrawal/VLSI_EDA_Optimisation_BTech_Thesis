# Delay-gain driven multi-candidate gate sizing

## Problem
Critical drivers can remain too weak when a larger delay reduction loses to a smaller replacement after cost normalization. Returning only one replacement also prevents trying another eligible size if that replacement is rejected.

## Current heuristic (file:function)
`src/move/SizeUpGenerator.cc:SizeUpGenerator::upsizeCell` previously selected one cell by estimated stage delay gain divided by a cost inflation ratio (leakage when available, otherwise LEF or Liberty area). The stage estimate includes the preceding driver's resistance times the selected input pin capacitance. Both output transition resistances must be no worse than the original. `SizeUpGenerator::generate` checked max-cap preservation only for that one winner.

## New approach
Rank every eligible replacement by positive, finite stage delay reduction, with no area or leakage divisor. Keep the upstream input-capacitance delay term and the existing rise/fall resistance eligibility checks. Preserve family, footprint, dont-use, site, VT, and configured area/leakage restrictions through `getSwappableCells`. Check `replacementPreservesMaxCap` separately for every ranked replacement and return all survivors as ordinary `SizeUpCandidate` moves.

The existing serial policy tries these moves in order and stops at the first accepted replacement. Generation performs no netlist edits; application still uses `Resizer::replaceCell` under the existing journal, preserving rollback and accounting. No flags or Tcl changes are introduced. Equal gains are ordered by cell name, then library name; a stable sort preserves original order for exact ties. Non-finite gains are excluded.

## Why WNS/TNS should improve
Ranking by timing gain allows stronger critical drivers to win when their larger delay improvement previously lost to cost normalization. Lower driver delay and potentially sharper output transitions should improve downstream arrival times. Charging the previous stage for additional input capacitance avoids selecting a stronger driver whose estimated upstream cost erases its benefit. Returning other viable sizes also avoids losing all sizing opportunities when the top choice fails the max-cap check or a reported replacement attempt.

## What to look for in the path report
Look for stronger cells on the critical stages, lower stage delays and output slews, and improved endpoint slack across aes, gcd, and ibex. Check preceding-stage delay and slew for regressions from increased input capacitance. Compare WNS, TNS, endpoint violations, hold slack, DRV counts, legal placement, and total area against the champion; the intended score gain is at least +0.00200 with area growth at most 10%.

## Risks
Removing cost normalization can increase area and leakage; configured per-replacement limits remain enforced, but this change adds no global 10% area budget. The resistance-based upstream estimate is approximate and does not guarantee improved slew, hold timing, side-path slack, or all-corner behavior. Larger cells can increase placement pressure. These require the parent evaluator's timing, DRV, area, and placement checks.

The provided `Resizer::replaceCell` calls OpenDP legalization for routed parasitic modes but does not propagate legalization failure as a rejected move; for placement parasitics, legalization occurs later in the evaluation flow. The ranked list supports fallback for failures reported through the existing replacement API, but cannot recover an unreported OpenDP failure. Changing that behavior would require edits outside the permitted files. Existing journaling and placement handling are preserved.

## Files changed
- `src/move/SizeUpGenerator.cc`: Replace cost-normalized single selection with deterministic delay-gain ranking and per-candidate max-cap filtering.
- `src/move/SizeUpGenerator.hh`: Declare multi-replacement selection helpers and document the candidate sequence.
- `src/move/SizeUpCandidate.hh`: Update the generator description to reflect ranked replacements.
- `HYPOTHESIS.md`: Record the algorithm, expected benefits, validation targets, and limitations.

## Validation
Only lightweight source inspection, formatting, and whitespace checks were performed. No builds, OpenROAD runs, unit tests, or benchmark commands were run; the parent orchestrator owns those checks.
