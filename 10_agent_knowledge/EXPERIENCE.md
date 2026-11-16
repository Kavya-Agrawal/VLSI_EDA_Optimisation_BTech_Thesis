# Experiment experience index

This is a derived, agent-friendly index. The durable source records are `iterations/<NNNN>.json`; raw evidence
remains in `02_openroad_evolved`, `06_evolved_results`, and `11_agent_data`. Regenerating this file never deletes
an iteration record.

Recorded iterations: **5** · valid algorithm experiments: **3**

## Iteration 1: crashed · unassigned
- **Evidence status:** infrastructure/no-code record; do not infer heuristic quality
- **Hypothesis:** Error: [('/Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/02_openroad_evolved/champion/rsz/test/save_defok', '/Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/02_openroad_evolved/candidates/0001_buffering/rsz/test/save_defok', "[Errno 2] No such file or directory: '/Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/02_openroad_evolved/champion/rsz/test/save_defok'"), ('/Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/02_openroad_evolved/
- **Score:** vs champion +0.00000; vs baseline +0.00000
- **Files planned:** (not recorded)
- **Files changed:** (none)

## Iteration 2: rejected · setup_strategy
- **Evidence status:** infrastructure/no-code record; do not infer heuristic quality
- **Hypothesis:** You've hit your 5-hour limit · resets 7:50am (Asia/Calcutta)
- **Score:** vs champion +0.00000; vs baseline +0.00000
- **Files planned:** (not recorded)
- **Files changed:** (none)
- **Verdict reasons:** score +0.00000 below required gain +0.00200
- **nangate45/gcd: score +0.00000; WNS -0.1742->-0.1742 ns (d +0.0000); TNS -7.626->-7.626 ns (d +0.000)**
- **nangate45/aes: score +0.00000; WNS -0.1083->-0.1083 ns (d +0.0000); TNS -14.773->-14.773 ns (d +0.000)**
- **nangate45/ibex: score +0.00000; WNS -0.2994->-0.2994 ns (d +0.0000); TNS -416.273->-416.273 ns (d +0.000)**

## Iteration 3: rejected · sizing
- **Evidence status:** valid algorithm experiment
- **Hypothesis:** Delay-gain driven multi-candidate gate sizing to eliminate critical-path slew degradation
- **Score:** vs champion +0.00000; vs baseline +0.00000
- **Files planned:** src/move/SizeUpGenerator.cc, src/move/SizeUpGenerator.hh
- **Files changed:** src/move/SizeUpGenerator.cc, src/move/SizeUpGenerator.hh, src/move/SizeUpCandidate.hh, HYPOTHESIS.md
- **Patch scope:** 1 files, +153/-165 lines
- **Verdict reasons:** gates failed: //src/rsz/test:TestInsertBuffer=FAILED; //src/rsz/test:TestNestedJournal=FAILED; //src/rsz/test:TestPreChecks=FAILED; //src/rsz/test:TestResizer=FAILED; //src/rsz/test:cpp_tests=FAILED
- **Dominant cause:** build_api_mismatch
- **Lesson:** Candidate 0003 produced no timing evidence because the upsizeCell-to-upsizeCells API change broke test compilation, and all ten smoke logs failed during helper initialization.
- **Dead end:** Repeating the incompatible API rename without migrating callers will fail gates before timing evaluation.
- **Recommended next cluster:** sizing
- **Bad changes:** SizeUpGenerator.hh replaced upsizeCell with upsizeCells while TestResizer.cc retained the old API, producing five compiler errors., Smoke success reporting accepted ten logs containing missing helpers.tcl errors.
- **Files to revisit:** src/rsz/src/move/SizeUpGenerator.hh, src/rsz/src/move/SizeUpGenerator.cc, src/rsz/test/cpp/TestResizer.cc

## Iteration 4: rejected · sizing
- **Evidence status:** valid algorithm experiment
- **Hypothesis:** Isolate absolute delay-gain ranking with API-compatible single-candidate sizing
- **Score:** vs champion +0.00000; vs baseline +0.00000
- **Files planned:** src/move/SizeUpGenerator.cc, test/cpp/TestResizer.cc
- **Files changed:** src/move/SizeUpGenerator.cc, HYPOTHESIS.md
- **Patch scope:** 1 files, +64/-73 lines
- **Verdict reasons:** gates failed: //src/rsz/test:TestResizer=FAILED; //src/rsz/test:cpp_tests=FAILED
- **Dominant cause:** unit_test_selection_contract_mismatch
- **Lesson:** Absolute stage-gain ranking changed rising-edge replacement selection and failed unit gates before any benchmark timing benefit could be measured.
- **Dead end:** Repeating the same gate-failing absolute-gain selector without resolving its selection contract cannot produce evaluable timing evidence.
- **Recommended next cluster:** sizing
- **Bad changes:** src/rsz/src/move/SizeUpGenerator.cc: replacing cost-normalized ranking with absolute gain conflicts with two existing rising-edge master assertions; timing impact is unmeasured.
- **Files to revisit:** src/rsz/src/move/SizeUpGenerator.cc, src/rsz/test/cpp/TestResizer.cc
- **Files to avoid:** src/rsz/src/move/SizeUpGenerator.hh, src/rsz/src/move/SizeUpCandidate.cc

## Iteration 5: rejected · sizing
- **Evidence status:** valid algorithm experiment
- **Hypothesis:** Recover suppressed sizing moves with cost-ranked feasible replacement selection
- **Score:** vs champion +0.00000; vs baseline +0.00000
- **Files planned:** src/move/SizeUpGenerator.cc, test/cpp/TestResizer.cc
- **Files changed:** src/move/SizeUpGenerator.cc, src/move/SizeUpGenerator.hh, HYPOTHESIS.md
- **Patch scope:** 1 files, +115/-17 lines
- **Verdict reasons:** score +0.00000 below required gain +0.00200
- **nangate45/gcd: score +0.00000; WNS -0.1742->-0.1742 ns (d +0.0000); TNS -7.626->-7.626 ns (d +0.000)**
- **nangate45/aes: score +0.00000; WNS -0.1083->-0.1083 ns (d +0.0000); TNS -14.773->-14.773 ns (d +0.000)**
- **nangate45/ibex: score +0.00000; WNS -0.2994->-0.2994 ns (d +0.0000); TNS -416.273->-416.273 ns (d +0.000)**
- **Dominant cause:** high_fanout
- **Lesson:** Moving upstream max-capacitance feasibility into sizing selection preserved compatibility but produced zero incremental tier-A timing benefit.
- **Dead end:** Do not repeat feasible-runner-up sizing selection without measured recovery opportunities and attributable endpoint gains.
- **Recommended next cluster:** buffering
- **Good changes:** src/move/SizeUpGenerator.cc and src/move/SizeUpGenerator.hh preserved the protected upsizeCell API; all supplied unit and smoke gates passed, but no timing benefit was measured.
- **Bad changes:** src/move/SizeUpGenerator.cc moved replacementPreservesMaxCap into contender selection with zero measured WNS, TNS, or reported endpoint improvement.
- **Files to revisit:** src/move/SplitLoadGenerator.cc, src/move/BufferGenerator.cc, src/move/CloneGenerator.cc, src/policy/SetupLegacyPolicy.cc
- **Files to avoid:** src/move/SizeUpGenerator.cc, src/move/SizeUpGenerator.hh
