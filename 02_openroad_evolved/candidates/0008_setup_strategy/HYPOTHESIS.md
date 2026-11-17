# Problem

LEGACY commits the first applicable repair on load-delay-ranked path drivers.
Its local ranking can miss shared endpoint benefits or accept collateral timing
damage that becomes visible only after parasitic and STA refresh.

# Current heuristic (file:function)

`src/policy/SetupLegacyBase.cc:repairPath` ranks path drivers by load delay and
calls `tryRepairPathTarget`. `tryCandidateSequence` accepts the first legal
candidate whose application succeeds. `SetupLegacyPolicy::repairEndpoint`
promotes checkpoints using WNS and focus slack, overlooking TNS-only gains.

# New approach

Override path repair in LEGACY only. Collect the existing path-driver candidates,
including latch fanin segments, and trial each legal candidate inside a nested
MoveCommitter journal. Every trial starts from the same endpoint checkpoint and
is rolled back after parasitic and timing refresh. Regenerate targets and
candidates after rollback rather than retaining invalid STA paths.

Require nondecreasing global setup WNS, global setup TNS, focus endpoint slack,
global hold worst slack and hold TNS; also reject area-limit breaches and
increased max slew, capacitance or fanout violation counts. Among admitted
candidates maximize `delta WNS + delta TNS / constrained endpoint count`, using
negative slack clamped at zero for WNS. Require strictly positive measured gain.
Resolve ties by path traversal, configured generator order, then candidate order.
Recreate the winner and require its measured score to meet or exceed its trial
score before merging its journal into the undoable endpoint checkpoint.

Apply one winner per pass even when the configured repair budget permits more;
subsequent passes rebuild the path. Promote global TNS-only or WNS-only gains
through the existing endpoint checkpoint machinery, including path-group runs.
No Tcl options or new flags are introduced; LEGACY uses this behavior by default.

# Why WNS/TNS should improve

Actual global TNS rewards changes on shared timing cones. The normalized TNS
term makes broad endpoint benefit comparable to direct WNS improvement. Global
and focus slack floors prevent sacrificing one objective for a predicted gain.
Replaying the winner checks that regenerated candidates reproduce that gain.

# What to look for in the path report

Look for improved worst path slack and fewer violating endpoints sharing repaired
drivers, rather than just a faster isolated stage. Compare pre-repair and final
post-detailed-placement reports: target AES WNS +5 ps, Ibex WNS +10 ps and TNS
+15 ns versus champion, without design WNS/TNS, hold or DRV regressions. Gains
must survive the evaluator's final detailed placement and parasitic extraction.

# Risks

Full timing trials, electrical checks, regeneration and rollback add runtime and
can hit the evaluator timeout. Strict monotonic admission can block useful
multi-move sequences, and one winner per pass can reach iteration limits sooner.
Existing candidate legality, equivalence and placement behavior is retained.
Electrical guards compare violation counts, not individual violating pin sets.
Global hold floors do not guarantee every individual hold endpoint is unchanged.

Final detailed placement is an external command executed after repair returns;
these policy files cannot keep a journal alive across that command or verify its
result. Consequently, post-placement gain survival and placement legality remain
mandatory evaluator checks, not a guarantee made by the trial timing. No builds,
OpenROAD runs or tests were performed, per the resource rule; only lightweight
source and formatting checks were performed.

# Files changed

- `src/policy/SetupLegacyPolicy.cc`: Measure journaled alternatives, replay the
  best admitted repair, and retain global WNS/TNS gains in endpoint checkpoints.
- `src/policy/SetupLegacyPolicy.hh`: Declare the LEGACY path-repair override.
- `HYPOTHESIS.md`: Document the algorithm, expected report evidence and risks.
