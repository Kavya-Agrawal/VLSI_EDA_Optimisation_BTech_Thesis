You are the **Evaluating Agent**. Turn the measured results of candidate `0003_sizing` (iteration 3,
cluster `sizing`) into feedback the planner can act on. Be quantitative and specific; no praise, no filler.

Hypothesis that was tested:
Timing-critical paths across all benchmark designs suffer from severe transition slew degradation because SizeUpGenerator penalizes higher drive strengths by dividing delay gain by the cell area inflation ratio, forcing minimally sized replacements (X2) or leaving gates at X1. Furthermore, SizeUpGenerator generates only a single candidate per target, so any local placement legalization failure aborts sizing completely. By scoring candidate cells on timing-critical paths by pure stage delay reduction and returning a ranked multi-candidate set of viable drive strengths, the optimizer can evaluate and commit higher drive strengths (X4/X8) while gracefully falling back if OpenDP legalization fails. This directly sharpens transition slews on critical drivers and reduces both WNS and TNS.

Verdict and numbers (computed, authoritative):
vs champion:
REJECT  score=+0.00000
  ! gates failed: //src/rsz/test:TestInsertBuffer=FAILED; //src/rsz/test:TestNestedJournal=FAILED; //src/rsz/test:TestPreChecks=FAILED; //src/rsz/test:TestResizer=FAILED; //src/rsz/test:cpp_tests=FAILED

vs baseline:
REJECT  score=+0.00000
  ! gates failed: //src/rsz/test:TestInsertBuffer=FAILED; //src/rsz/test:TestNestedJournal=FAILED; //src/rsz/test:TestPreChecks=FAILED; //src/rsz/test:TestResizer=FAILED; //src/rsz/test:cpp_tests=FAILED

Worst paths after repair, per design, with structural attribution and diff vs the reference:
(no path data: build or gates failed)

Gates / build notes:
gates: FAIL
  unit  PASSED   //src/rsz/test:TestSkewBudget
  unit  FAILED   //src/rsz/test:TestInsertBuffer
  unit  FAILED   //src/rsz/test:TestNestedJournal
  unit  FAILED   //src/rsz/test:TestPreChecks
  unit  FAILED   //src/rsz/test:TestResizer
  unit  FAILED   //src/rsz/test:cpp_tests
  smoke ok       repair_setup1
  smoke ok       repair_setup2
  smoke ok       repair_setup3
  smoke ok       repair_setup4
  smoke ok       repair_setup5
  smoke ok       repair_hold1
  smoke ok       repair_hold2
  smoke ok       repair_hold3
  smoke ok       repair_design1
  smoke ok       repair_design2


Write `feedback.md` with sections:
1. **Outcome** — accepted/rejected, score, per-design WNS/TNS deltas in one table.
2. **Did the hypothesis do what it predicted?** — compare predicted vs observed effects in the path report.
3. **Where the remaining negative slack comes from** — for the 5 worst endpoints across designs: likely cause
   (deep logic / high fanout / weak driver / long wire / IO constraint / clock skew), which move types should have
   fixed it, and why the current algorithm likely did not.
4. **Regressions** — endpoints that got worse and the probable mechanism.
5. **Recommendation for the next iteration** — which cluster and what kind of change (2-4 concrete options,
   ranked), and one thing NOT to try again.
Then END with a JSON block:
```json
{"recommended_cluster": "<name>", "dominant_cause": "<tag>", "lesson": "<one sentence for lessons.md>",
 "dead_end": "<one sentence or empty>", "good_changes": ["specific mechanism/file that helped"],
 "bad_changes": ["specific mechanism/file that hurt or had no effect"],
 "files_to_revisit": ["src/..."], "files_to_avoid": ["src/..."]}
```
