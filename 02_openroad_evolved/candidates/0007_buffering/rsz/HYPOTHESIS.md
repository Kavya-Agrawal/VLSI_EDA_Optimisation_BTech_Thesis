# Problem

Splitting a fixed half of a high-fanout driver's sinks can move too much
capacitance behind a buffer, consume the branch's slack, or miss a better split.

# Current heuristic (file:function)

`src/move/SplitLoadGenerator.cc:chooseSplitLoads` previously selected half of the
sinks ordered by descending slack headroom, excluding top-level ports. Buffer
sizing happened only when `SplitLoadCandidate::applySplitBuffer` inserted it.

# New approach

Keep the existing driver eligibility and deterministic headroom order. Search
nonempty proper prefixes of movable sinks, excluding the captured focus-path
load and top-level ports. Require a known focus-path load on the net.

For each prefix, accumulate scene-specific pin capacitance and estimate split
wire capacitance with driver-rooted bounding-box half-perimeters. Predict the
buffer size with the existing `findTargetCell` target-slew policy. Evaluate
original and reduced-load driver delays for rise and fall, then evaluate the
buffer with the predicted driver output slews. Existing sink wire delays are
held constant; driver delay relief and the new buffer delay change arrival.

Reject a partition if either transition predicts worsening an already-negative
moved-load slack or making a nonnegative moved-load slack negative. Among safe
partitions with positive worst-load slack improvement, maximize that improvement
and break ties by aggregate negative-slack improvement over load transitions.
Exact ties retain the first (shortest) prefix. Missing timing models do not fall
back to the fixed-half split. Selection performs no netlist edits; the existing
candidate still inserts, sizes, invalidates parasitics, and participates in the
existing journal/commit/rollback flow. No Tcl options change.

# Why WNS/TNS should improve

Shielding the focus driver from a capacitively heavy side branch can improve
its delay to several failing endpoints. Explicitly charging moved sinks for
buffer delay avoids spending slack they do not have. Searching prefix sizes
allows more useful isolation than sink count alone. These are predictions;
post-legalization WNS/TNS improvement must be established by the evaluator.

# What to look for in the path report

Compare matched endpoints before and after legalization. The focus sink should
remain directly connected to the original driver, with lower driver delay and
multiple improved shared-driver paths. Moved sinks should appear behind a
`split` buffer without new setup regressions. Correlate retained split instances
with the `split_load_move` level-2 selection diagnostic (load count, predicted
worst slack gain, aggregate negative-slack gain); selection or insertion alone
is not evidence that a move survived commit. Check Ibex WNS/TNS targets and
unchanged AES/GCD, plus hold, DRVs, area, and placement gates.

# Risks

Bounding-box capacitance omits Steiner topology and wire-delay redistribution.
Legalization changes wire lengths and slew; actual target-slew resizing can
choose a different cell from the estimate. Driver delay uses the existing
library helper's input-slew policy, and load slack budgets use STA's worst
setup mode rather than a complete per-path, per-scene sensitivity model.
Aggregate load-transition negative slack is a ranking proxy, not endpoint TNS.
Few eligible nets or conservative slack guards may limit gains. No build,
OpenROAD invocation, or tests were run, per the resource rule; the parent
orchestrator must verify all evaluation gates.

# Files changed

- `src/move/SplitLoadGenerator.cc`: Replace fixed-half selection with deterministic, capacitance- and delay-aware prefix scoring and moved-branch slack guards.
- `HYPOTHESIS.md`: Document the algorithm, expected path evidence, and modeling limits.
