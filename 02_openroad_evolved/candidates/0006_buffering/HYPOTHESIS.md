# Problem

The blanket fanout cutoff excludes shared setup-critical data nets, including
the planner's reported Ibex drivers with fanouts 22, 31, and 45. Their loads may
benefit together from a different buffer topology.

# Current heuristic (file:function)

`src/move/BufferGenerator.cc:BufferGenerator::isApplicable` admits path-driver
targets only when fanout is at least one and below 20 and `okToBufferNet` passes.
`BufferCandidate::apply` invokes the existing required-time-aware
`Rebuffer::rebufferPin` search through the normal move commit flow.

# New approach

Preserve eligibility below fanout 20. For fanout 20 or above, additionally require
a setup (max-analysis) target with a known driver transition and timing mode;
exclude clock drivers and clock source pins in that mode. Walk only immediate
wire edges from the driver and require at least two distinct load pins with
finite negative setup slack for the target transition. Reject STA's negative
infinity sentinel, IEEE infinities, and NaNs. Keep all existing net protection
checks and pass eligible targets to the same BufferCandidate and rebuffer search.
This behavior is enabled by default without new flags.

# Why WNS/TNS should improve

Required-time-aware tree selection can isolate or redistribute shared load
capacitance and reduce driver-to-load delay for multiple failing branches.
Admitting these nets creates opportunities to improve both the worst arrival
and arrivals at other violating endpoints. Eligibility alone does not establish
an improvement; committed repairs and post-legalization measurements must do so.

# What to look for in the path report

Identify committed BufferMove repairs on newly eligible data drivers, especially
the reported Ibex fanouts 22, 31, and 45. Match startpoints, endpoints, and
transitions before and after repair and legalization; inspect buffer stages,
shared driver delay, and data arrivals across at least two affected branches.
Check for Ibex WNS improvement of at least 0.020 ns, TNS magnitude reduction of
at least 1%, and overall score at least +0.00200 with all evaluation gates passing.
An accepted candidate log alone is insufficient evidence of a retained repair.

# Risks

Existing trees may already be near optimal. Larger searches can cost more time,
and candidate ordering can prevent newly eligible repairs from being attempted
or retained. Added buffers may increase area or upstream load, degrade other
paths, or lose timing gains after legalization. Setup-load qualification does
not itself guarantee hold or DRV safety; the existing rebuffer, journal,
rollback, and evaluator checks remain necessary. No topology mutation or
placement logic is changed here. Selection is deterministic: it tests whether
two distinct pins qualify, independent of edge traversal order, without ranking
ties, random choices, or new mutable state.

# Files changed

- `src/move/BufferGenerator.cc`: Add shared-critical setup-data qualification above the existing fanout cutoff.
- `src/move/BufferGenerator.hh`: Document high-fanout eligibility and existing protection checks.
- `HYPOTHESIS.md`: Record the hypothesis, evidence to inspect, and risks.

# Verification

Only lightweight source, formatting, and diff checks are performed in this
candidate. Builds, unit/Tcl tests, OpenROAD runs, legalization, and timing/DRV
measurements are reserved for the parent orchestrator as instructed.
