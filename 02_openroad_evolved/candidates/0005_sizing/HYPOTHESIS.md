# Recover suppressed sizing moves with feasible replacement selection

## Problem

An upstream max-capacitance violation in the highest-scoring replacement can
suppress a profitable, feasible runner-up for the same instance.

## Current heuristic (file:function)

`src/move/SizeUpGenerator.cc:upsizeCell` ranks equivalent masters by estimated
stage-delay gain divided by the larger of one and the replacement/current cost
ratio. Cost uses the first mutually available metric: leakage, LEF area, or
Liberty area. Stage delay includes the preceding driver's resistance times the
critical input capacitance; candidates must not weaken either transition's drive
resistance. Previously, `generate` checked instance-level upstream capacitance
only after selecting the winner, returning no candidate if that winner failed.

## New approach

Pass the target instance into the private `selectReplacement` search. Before a
candidate can improve the best score, call the existing
`Resizer::replacementPreservesMaxCap` with that instance, nominal replacement,
and active scene mode. Reject infeasible contenders without updating the best
score, allowing the highest-scoring feasible master to win. Preserve the exact
protected `upsizeCell` API as a library-only wrapper with no instance constraint.
The production generator uses the instance-aware search by default and still
emits at most one candidate. Scoring, upstream loading penalties, transition
guards, equivalent-cell filtering, replacement, and journaling remain unchanged.

## Why WNS/TNS should improve

Recovered replacements retain positive estimated stage gain after the upstream
loading penalty and the original cost normalization. They may reduce data-path
arrival times at affected AES or Ibex endpoints without adding logic stages.
This is a hypothesis, not measured timing evidence. If tier A has no recovered
feasible-runner-up opportunities, reject the mechanism as inapplicable.

## What to look for in the path report

Compare matched startpoint/endpoint paths for changed drive-strength masters,
lower data arrival times, and unchanged logic depth. Check upstream slew and
capacitance along with downstream delay. With `RSZ size_up_move` debugging at
level 3, an infeasible-contender message followed by an accepted size-up at the
same instance helps identify recovery; compare with the reference to establish
that its highest-scoring master was infeasible. Target AES dWNS >= +0.005 ns and
at least 1% lower TNS magnitude, nonregressing Ibex, gcd WNS loss <= 0.001 ns
with no TNS regression, and mean score >= +0.00200.

## Risks

Feasible runner-ups may be absent. Estimated local gains may disappear after
upstream loading, legalization, hold repair, or area constraints. The existing
max-capacitance predicate and transition guards are preserved rather than
extended; all electrical, logical-equivalence, placement, hold, and area gates
still require parent evaluation. Candidate iteration order and strict score
comparison are unchanged, preserving deterministic tie handling. No speculative
netlist mutations occur during selection; moves retain the existing undo path.
No builds, OpenROAD runs, or tests were run under the resource rule; verification
is limited to formatting and lightweight source checks.

## Files changed

- `src/move/SizeUpGenerator.cc`: Rank feasible replacements within the search
  while preserving the library-only sizing API and single-candidate generation.
- `src/move/SizeUpGenerator.hh`: Add instance context to the private selection
  helper without changing the protected `upsizeCell` signature.
- `HYPOTHESIS.md`: Record the mechanism, expected timing evidence, and risks.
