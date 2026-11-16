You are the **Evaluating Agent**. Turn the measured results of candidate `0004_sizing` (iteration 4,
cluster `sizing`) into feedback the planner can act on. Be quantitative and specific; no praise, no filler.

Hypothesis that was tested:
Cost-normalized sizing can prefer a smaller timing improvement over a larger eligible delay reduction on violating data paths. Preserve the champion upsizeCell API and single-candidate generation, but select the replacement with maximum positive finite stage delay gain, retaining the preceding-driver input-capacitance penalty and existing eligibility checks. AES critical X1 logic provides the clearest opportunity, while Ibex may benefit within its data cone; its fanout-943 clock gate is not evidence for this mechanism. Iteration 3 never reached timing evaluation, so this retry isolates ranking from candidate multiplicity and avoids its incompatible API rename. Improved selections should reduce matched-endpoint data arrivals and WNS/TNS, subject to upstream loading, hold, area, DRV, and placement gates.

Verdict and numbers (computed, authoritative):
vs champion:
REJECT  score=+0.00000
  ! gates failed: //src/rsz/test:TestResizer=FAILED; //src/rsz/test:cpp_tests=FAILED

vs baseline:
REJECT  score=+0.00000
  ! gates failed: //src/rsz/test:TestResizer=FAILED; //src/rsz/test:cpp_tests=FAILED

Worst paths after repair, per design, with structural attribution and diff vs the reference:
(no path data: build or gates failed)

Gates / build notes:
gates: FAIL
  unit  PASSED   //src/rsz/test:TestInsertBuffer
  unit  PASSED   //src/rsz/test:TestNestedJournal
  unit  PASSED   //src/rsz/test:TestPreChecks
  unit  PASSED   //src/rsz/test:TestSkewBudget
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
