# Architecture

## The problem being evolved

OpenROAD's Resizer (`src/rsz`) runs after placement. Given a placed netlist, liberty timing models,
constraints (SDC) and a wire RC model, it repairs the design so timing closes:

- `repair_design`: fix slew / capacitance / fanout / long-wire violations (DRVs) by sizing and buffering.
- `repair_timing -setup`: attack negative-slack endpoints with *moves* (size up, size down fanout,
  swap pins, buffer / rebuffer, clone, split load, VT swap, unbuffer) chosen by heuristics, re-timing
  incrementally with OpenSTA after each move.
- `repair_timing -hold`: insert delay so hold constraints pass without breaking setup.
- `recover_power`: give back area / power on paths with positive slack.

The resizer and the timer (OpenSTA via `dbSta`) form a loop: estimate parasitics from placement,
compute arrival/required times, pick a move, commit it, re-estimate, repeat, until slack targets or
iteration limits are met. The quality of the final WNS / TNS depends on *which* endpoints and *which*
moves are attempted in *what* order under *what* acceptance rules. Those decisions are the target.

## Pieces of this repo

```
                 09_agent_context  (what rsz does, per file, per algorithm)  <- 08_graphify + Claude pass
                        |
   10_agent_knowledge ->|<- 06_evolved_results/<i-1>/feedback.md
                        v
                  [ Planner agent ]  picks cluster, writes hypothesis_<i>.md
                        |
                        v
   02_openroad_evolved/candidates/<i>/rsz  <- copy of champion
                  [ Coding sub-agent for that cluster ]  edits rsz, writes HYPOTHESIS.md
                        |
                        v
   tools/build_openroad.sh evolved <cand>  -> build/bin/openroad_evolved   (Bazel, incremental)
                        |
                        v
   gates: rsz regression tests, check_placement, DRV/hold guards (rszevolve.eval.gates)
                        |
                        v
   eval_repair_timing.tcl on 04_benchmarks/designs/<tier>  (stock vs evolved, N replicates)
                        |
                        v
   rszevolve.eval.paths + score  ->  06_evolved_results/<i>/{metrics,paths,delta_*.json}
                        |
                        v
                  [ Evaluator agent ]  feedback.md: numbers + worst paths + attributed causes
                        |
                        v
   accept? -> champion updated, lineage.json, 10_agent_knowledge updated, 11_agent_data/<i>/usage.json
```

## Clusters (coding sub-agents)

| Cluster | Owns | Question it may re-answer |
|---|---|---|
| `setup_strategy` | `RepairSetup*`, `RepairTargetCollector`, `PathGroupFilter`, `Optimizer*`, `policy/`, `MoveTracker`, `MoveCommitter` | which endpoints/paths, in what order, how many moves, acceptance, TNS vs WNS budgeting, stopping |
| `sizing` | `move/SizeUp*`, `SizeDownFanout*`, `VtSwap*`, `SwapPins*`, `DelayEstimator*`, `LRSubproblem` | how a cell size is chosen (greedy vs sensitivity / Lagrangian / lookahead) |
| `buffering` | `Rebuffer*`, `BufferedNet`, `move/Buffer*`, `SplitLoad*`, `Clone*`, `Unbuffer*`, `BufferToInverters*` | buffer-tree construction, cloning vs splitting, insertion points |
| `hold` | `RepairHold*` | hold fixing with minimal setup damage |
| `drv` | `RepairDesign*` | slew / cap / fanout repair before timing repair |
| `timing_model` | `SequentialTimingEstimator`, `SkewBudget`, `DelayEstimatorBufferTree` | the estimates used to rank moves |

Final membership lives in `09_agent_context/clusters.json` (generated from the graph, hand-adjustable).

## Evaluation contract (short form; full text in 09_agent_context/EVAL_CONTRACT.md)

- Input: `placed.odb` (post detailed placement, pre-CTS, after ORFS `repair_design`), SDC
  (`nominal` or `stressed` = tightened clock so the baseline has real negative slack), platform RC.
- Commands: `read_db`, `read_sdc`, `source setRC.tcl`, `estimate_parasitics -placement`,
  pre-repair WNS/TNS, timed `repair_timing -setup -repair_tns 100`, `detailed_placement`,
  `estimate_parasitics -placement`, WNS/TNS/hold metrics, DRV violators, area, top-N worst paths.
- Score (paired vs baseline per design, then averaged over the tier):
  `0.5 * dWNS/period + 0.5 * dTNS/(period * endpoints)`; any hold or DRV regression beyond tolerance,
  or a build/test/legality failure, rejects the candidate regardless of score (fail-closed).

## Why Bazel

OpenROAD removed CMake on 2026-11-01. Bazel downloads its own LLVM toolchain, Tcl and libraries, so
`tools/build_openroad.sh` is the same command on macOS arm64, Linux x86-64 and in Docker. Bazel's
cache makes a candidate rebuild (rsz-only change) a few minutes. Binaries are copied out of
`bazel-bin` into `build/bin/` because `bazel-bin` is overwritten by the next build.
