You are documenting OpenROAD's Resizer (`src/rsz`) for other engineers and for coding agents that will later
redesign its algorithms. Your working directory is a frozen copy of `src/rsz` (`src/`, `include/`, `test/`,
`doc/`). Also available read-only: `../sta_interface_snapshot/` (dbSta + OpenSTA headers), the Graphify
knowledge graph under `08_graphify/rsz_focus/` (GRAPH_REPORT.md, GOD_NODES.txt) and ORFS flow scripts.

Write `00_BIG_PICTURE.md` (Markdown, 600-1200 lines is fine). Required sections, in this order:

1. **What problem rsz solves** — inputs (placed ODB, liberty, SDC, layer RC, dont-use) and outputs
   (resized/buffered netlist + legalized placement). What "repair" means. Why it is NP-hard and heuristic.
2. **Where it sits in the ORFS flow** — read `orfs_scripts/resize.tcl`, `cts.tcl`, `global_route.tcl`,
   `util.tcl` (repair_timing_helper / repair_design_helper). State exactly which commands run at which stage
   and with which arguments.
3. **The resizer <-> timer loop** — how rsz calls OpenSTA through dbSta: `estimate_parasitics`, incremental
   timing updates, arrival/required/slack queries, what is invalidated after a move, how parasitics are
   re-estimated after buffering. Name the exact functions.
4. **Command map** — for every Tcl command in `src/Resizer.tcl` (repair_design, repair_timing, repair_clock_nets,
   recover_power, buffer_ports, ...): the C++ entry point and the files it goes through.
5. **The repair_timing -setup algorithm end to end** — target collection, path groups, move generators and
   candidates (`src/move/`), the optimizer / policy layer (`Optimizer*`, `policy/`), journaling/rollback
   (`MoveTracker`, `MoveCommitter`), acceptance tests, passes/iterations limits, "last gasp", TNS end percent.
   Describe it as a pseudo-code loop with the real function names.
6. **The other algorithms** — repair_design (DRV), repair_hold, rebuffer (BufferedNet / van Ginneken-style),
   cloning, split load, size down fanout, VT swap, swap pins, recover_power, sequential timing / skew budget.
   One subsection each: input -> heuristic -> output -> known weaknesses.
7. **Data structures and invariants** that must not be broken (journal, dont_touch, dbNetwork/odb sync,
   parasitics validity, determinism).
8. **What a better algorithm could change** — list the decision points (ordering, selection, acceptance,
   cost models, search strategy) with the file:function where each lives.

Rules: cite file paths and function names precisely (grep them). Do not invent behaviour; if unsure, say what
you verified and what you inferred. No marketing language. Output only the Markdown document.

File index of src/ (with graph-derived callees where known):
{{FILE_INDEX}}

Most connected graph nodes:
{{GOD_NODES}}
