# Problem

Cost-normalized sizing can choose a smaller timing improvement over a larger
eligible delay reduction on a violating data path.

# Current heuristic (file:function)

`src/move/SizeUpGenerator.cc:SizeUpGenerator::upsizeCell` ranks replacements by
stage delay gain divided by the larger of one and the new/old cost ratio. Cost
uses the first shared available metric: leakage, LEF area, or Liberty area.
Stage delay includes the preceding driver's resistance times input capacitance.
`generate` emits at most one candidate and checks replacement max capacitance.

# New approach

Choose the maximum strictly positive finite stage delay gain directly. Retain
the input-capacitance penalty, scene and port checks, both-edge non-weakening
drive checks, and the existing swappable-cell policy restrictions, including
dont_use, equivalence, footprint, site, VT, area, and leakage policies. Cost
metadata is no longer needed for ranking or required to score a replacement.
Keep `upsizeCell` and single-candidate generation unchanged. Exact ties retain
the first cell in the existing swappable-cell order. No flags are added; this
ranking is the default. Replacement execution and journal/rollback paths are
unchanged.

# Why WNS/TNS should improve

Selecting the greatest estimated stage gain can reduce critical data arrival
more than selecting gain per unit cost. AES critical X1 logic is the primary
opportunity; Ibex may benefit within its data cone. The upstream loading penalty
remains part of the estimate. These are expected effects, pending evaluation.

# What to look for in the path report

Compare matched startpoint/endpoint data paths for replacement masters, reduced
stage delays and endpoint arrivals, upstream slew/loading changes, and setup
slack. Ibex's high-fanout clock gate is not evidence of this mechanism. Target
at least 0.010 ns WNS improvement on AES and Ibex, at least 2% and 5% TNS
magnitude reduction respectively, and at most 0.001 ns gcd WNS loss with no gcd
TNS regression. Require mean score at least +0.00200 and all evaluation gates.

# Risks

Absolute-gain ranking can increase area, upstream loading, placement pressure,
and hold damage. The local stage approximation may misrank full-path effects.
The existing max-cap rejection can discard the selected champion without trying
a runner-up; this behavior is preserved. Full timing, hold, DRV, placement,
area, and replicate-determinism checks remain the parent evaluator's work.
No builds or tests were run, per the resource rule; only source/diff checks
were performed. The suggested test file is outside the editable allowlist.

# Files changed

- `src/move/SizeUpGenerator.cc`: Replace cost-normalized scoring with maximum positive finite stage delay gain while preserving the API and move path.
- `HYPOTHESIS.md`: Record the hypothesis, implementation scope, expected path evidence, risks, and validation limits.
