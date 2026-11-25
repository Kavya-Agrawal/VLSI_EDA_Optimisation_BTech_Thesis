# TNS-weighted cut-point search for SplitLoad isolation of shared bottleneck nets

## Problem
Shared high-fanout nets (Ibex `_26153_/ZN` fanout 943, JPEG `ddin[8]/Q`) dominate the remaining violations. Stock SplitLoad always moves the less critical *half* of the sinks (by count) behind one buffer, regardless of how many sinks are actually violating or how much capacitance the cut removes.

## Current heuristic
`src/move/SplitLoadGenerator.cc`: `chooseSplitLoads` (stock) used `fanout_slacks.size() / 2` as the cut. One candidate was emitted.

## New approach
`SplitLoadGenerator::generate` now calls `rankCutPoints`. It evaluates up to four cut points (number of critical sinks kept on the driver: count of negative-slack sinks, n/4, n/2 = stock, 3n/4), each moving the remaining less-critical sinks behind the buffer. Each cut is scored with a first-order model: the driver speeds up by `g = Rdrv*(Cmoved - Cbuf)`; kept sinks gain `g`; moved sinks gain `g - bufferDelay(Cmoved)`. Every sink contributes its own negative slack to the predicted dTNS. Cuts whose predicted worst slack is below the current worst are dropped. The remaining cuts are emitted as separate `SplitLoadCandidate`s in order of predicted dTNS, with the stock cut kept as a last resort. The existing move commit and journal are untouched, so every move is still undoable.

## Why WNS/TNS should improve
On a trunk with few violating sinks and a lot of slack-rich load, a larger cut removes more capacitance from the critical stage, so every violating endpoint behind the net speeds up. When too large a cut would push moved sinks below the critical slack, a smaller cut is chosen instead.

## What to look for in the path report
Fewer violating endpoints behind the big shared nets. Split buffers (`split*`) on `_26153_` and similar drivers, with a different moved fraction than 1/2.

## Risks
- **Deviation from the hypothesis:** `src/policy/*` is not in the editable list, so I did not add a separate post-loop trial phase. The cut-point search runs inside the generator, so it also affects the stock loop and the existing `runTnsRecovery`. Cut points are ranked by a model, not measured by journaled incremental STA per variant. The existing recovery phase does measure and roll back (WNS floor plus TNS gain), but only for the first accepted candidate.
- The model ignores wire RC and post-legalization displacement.
- Counters are printed when the last SplitLoadGenerator is destroyed. If generators are created and destroyed in several waves, the lines may print more than once.
- Nothing was built or run here.

## Counters
`split_cutpoint_reranked` (best cut differs from stock), `split_cutpoint_candidates` (candidates emitted), `split_cutpoint_dropped` (empty cuts). Printed as `RSZ_EVOLVE <name> fired=<n>`.

## Files changed
- src/move/SplitLoadGenerator.cc: cut-point ranking, multi-candidate emission, counters.
- src/move/SplitLoadGenerator.hh: destructor declaration (prints counters).
