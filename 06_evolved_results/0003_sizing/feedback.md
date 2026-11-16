# Feedback for iteration 3 (0003_sizing, cluster sizing)

```
vs champion:
REJECT  score=+0.00000
  ! gates failed: //src/rsz/test:TestInsertBuffer=FAILED; //src/rsz/test:TestNestedJournal=FAILED; //src/rsz/test:TestPreChecks=FAILED; //src/rsz/test:TestResizer=FAILED; //src/rsz/test:cpp_tests=FAILED

vs baseline:
REJECT  score=+0.00000
  ! gates failed: //src/rsz/test:TestInsertBuffer=FAILED; //src/rsz/test:TestNestedJournal=FAILED; //src/rsz/test:TestPreChecks=FAILED; //src/rsz/test:TestResizer=FAILED; //src/rsz/test:cpp_tests=FAILED
```

Cannot save `feedback.md` because this session permits only filesystem reads. File content:

# 1. Outcome

**REJECTED**, score **+0.00000** against both champion and baseline. Rejection is due to failed gates; the score does not establish unchanged timing.

| Design | ΔWNS vs champion / baseline (ns) | ΔTNS vs champion / baseline (ns) |
|---|---:|---:|
| nangate45/gcd | unavailable / unavailable | unavailable / unavailable |
| nangate45/aes | unavailable / unavailable | unavailable / unavailable |
| nangate45/ibex | unavailable / unavailable | unavailable / unavailable |

The authoritative verdict contains no per-design measurements. Five of six unit gate entries failed. The underlying log identifies **five compiler errors** in `TestResizer.cc`: the tests reference `upsizeCell`, but the candidate declares `upsizeCells`. No unit tests executed in this invocation; the sole passing result was cached.

All **10/10** smoke tests are labeled `ok`, but every smoke log reports missing `helpers.tcl` during initial sourcing. These labels provide no evidence that repair ran successfully.

# 2. Did the hypothesis do what it predicted?

**Unverified.** No candidate path report exists.

| Prediction | Observed evidence |
|---|---|
| Delay-only ranking selects X4/X8 more often | No replacement counts or committed drive-strength data |
| Ranked alternatives recover after legalization failure | No failed-first/successful-fallback trace |
| Stronger drivers reduce transition slew | No before/after slew measurements |
| Improved slews reduce WNS and TNS | No candidate WNS/TNS measurements |

The API rename is evidenced by the compiler diagnostics. It does not demonstrate correct ranking, candidate iteration, rollback, or timing improvement. Neither the original slew diagnosis nor the proposed remedy has been validated.

# 3. Where the remaining negative slack comes from

**Zero of the requested five worst endpoints can be identified:** candidate endpoint names, slacks, and structural attribution are absent. Do not substitute prior-iteration endpoints as candidate observations.

No supported classification among deep logic, high fanout, weak driver, long wire, IO constraint, or clock skew is possible. The immediate evaluation blocker is compilation failure, not a measured inability of sizing to repair a particular path.

For the rerun, classify the five worst endpoints using cell/net delay, fanout, capacitance, slew, logic depth, and clock arrival data. Weak drivers suggest sizing; high fanout suggests buffering or cloning; long wires suggest buffering or placement; deep logic suggests restructuring; IO constraints and clock skew require constraint or clock analysis. The current evidence cannot establish which applies.

# 4. Regressions

**Endpoint regressions are unmeasured.** No endpoint can be reported as improved, unchanged, or worse.

The confirmed integration regression is the incompatible `SizeUpGenerator` API change: `TestResizer.cc:103` imports the removed method, and four subsequent calls fail compilation. The other failed gate labels must not be interpreted as independent runtime failures.

The smoke harness also reports success for scripts that fail during initialization. Its provenance is unknown; it cannot be attributed to the sizing change.

# 5. Recommendation for the next iteration

**Recommended cluster: `sizing`.** Repair validation before changing optimization policy again.

1. **Restore API compatibility.** Retain an `upsizeCell` wrapper returning the highest-ranked eligible cell, or migrate all test callers to `upsizeCells` and assert ranked-list semantics. Require successful compilation and execution of the unit gates.
2. **Repair smoke execution and failure detection.** Supply the Tcl helper environment and make Tcl initialization errors fail the gate. Rerun all ten scripts.
3. **Verify fallback transaction behavior.** Exercise a first candidate that fails legalization followed by a viable candidate; verify rollback and successful commitment of the alternative.
4. **Measure the sizing mechanism.** Record generated, attempted, and committed drive strengths; rejection reasons; legalization failures; and before/after slew, WNS, and TNS. Separate ranking changes from candidate multiplicity when assessing causality.

**Do not repeat:** renaming the sizing helper without updating its callers and submitting the candidate before unit compilation succeeds.

```json
{
  "recommended_cluster": "sizing",
  "dominant_cause": "build_api_mismatch",
  "lesson": "Candidate 0003 produced no timing evidence because the upsizeCell-to-upsizeCells API change broke test compilation, and all ten smoke logs failed during helper initialization.",
  "dead_end": "Repeating the incompatible API rename without migrating callers will fail gates before timing evaluation.",
  "good_changes": [],
  "bad_changes": [
    "SizeUpGenerator.hh replaced upsizeCell with upsizeCells while TestResizer.cc retained the old API, producing five compiler errors.",
    "Smoke success reporting accepted ten logs containing missing helpers.tcl errors."
  ],
  "files_to_revisit": [
    "src/rsz/src/move/SizeUpGenerator.hh",
    "src/rsz/src/move/SizeUpGenerator.cc",
    "src/rsz/test/cpp/TestResizer.cc"
  ],
  "files_to_avoid": []
}
```
