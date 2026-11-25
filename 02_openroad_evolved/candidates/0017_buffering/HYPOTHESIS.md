# Required-time-ordered (LT-tree) fanout trees for shared high-fanout drivers

## Problem
Ibex's worst paths cross `AND2_X1 _26153_/ZN` with fanout 943. Stock `SplitLoadGenerator` only moves the less-critical half of the sinks behind ONE lowest-drive buffer, so the trunk keeps ~470 pins and a weak buffer drives the other ~470. Stock Rebuffer is limited to fanout < 20.

## Current heuristic
`src/move/SplitLoadGenerator.cc: chooseSplitLoads` (fanout > 8): sort sinks by slack, put the top half (most slack) behind one `lowestDriveBufferCell()` at the driver location.

## New approach
For drivers with fanout >= 40, `generateFanoutTree` (SplitLoadGenerator.cc) builds a Touati-style tree:
1. Sinks are sorted by STA slack (equivalent to required time, same driver arrival), most critical first.
2. The most critical sinks stay directly on the driver, up to a cap budget of 3/8/15/30% of the total sink pin cap.
3. The rest are cut into 1..4 contiguous groups of equal pin cap (still slack ordered). Each group gets its own buffer at the group centroid. The buffer is chosen from ALL non-dont-use buffer masters, minimising `t_intr + R_buf*C_group + R_drvr*Cin_buf`, with the group cap limited to 90% of the buffer max-cap.
4. All 16 (fraction, groups) variants are scored with a lumped model: gain = `R_drvr * (C_offloaded - sum Cin_buf)`. The predicted min slack is the min of (critical slack + gain) and (group slack + gain - buffer delay). The best variant is used only if the predicted min-slack gain is >= 1 ps; otherwise the stock half-split is used (`fanout_tree_stock_fallback`).
5. `SplitLoadCandidate::applyFanoutTree` inserts the buffers with `Resizer::insertBufferBeforeLoads`. The move is a kSplitLoad MoveResult, so the existing commit, journal and rollback path covers it. Acceptance stays with the caller (the endpoint loop or the bottleneck recovery's WNS-floor/TNS check, which journals and restores).

## Why WNS/TNS should improve
Removing hundreds of pins of load from the critical trunk cuts the driver stage delay and output slew for all critical sinks, and the buffer cost is paid only by sinks with slack to spare. Thousands of Ibex endpoints share this trunk.

## What to look for in the path report
`_26153_/ZN` max fanout < 100, new `fotree*` buffers on the net, lower slew on critical sinks. `RSZ_EVOLVE fanout_tree_built` > 0.

## Risks
- The model ignores wire RC and slew effects, so some trees are worse than predicted. The recovery phase's journal rejects those, but in the stock endpoint loop a bad tree is only reverted by the pass-level "better" check.
- SplitLoad runs in the stock phase too. `SetupLegacyPolicy.cc` is not editable, so I could not gate the move on the recovery phase. The stock trajectory therefore changes for nets with fanout >= 40 (it stays byte-identical elsewhere).
- Buffers placed at centroids may be displaced by legalisation.
- Per-tree measured STA selection (several trees judged inside a journal) is NOT implemented. Variants are ranked by the analytic model only, because nested journals are unsafe.

## Counters (printed by `~SplitLoadGenerator`, then cleared)
`fanout_tree_built`, `fanout_tree_buffers`, `fanout_tree_sinks_isolated`, `fanout_tree_stock_fallback`.

## Files changed
- `src/move/SplitLoadGenerator.cc`: tree synthesis, variant scoring, counter printing, hookup in `generate`.
- `src/move/SplitLoadGenerator.hh`: destructor declaration.
- `src/move/SplitLoadCandidate.cc`: tree-form constructor, `applyFanoutTree`, stats storage.
- `src/move/SplitLoadCandidate.hh`: `FanoutTreeStats`, `FanoutTreeGroup`, new constructor and members.
