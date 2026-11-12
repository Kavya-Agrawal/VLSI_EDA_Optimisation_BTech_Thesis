Write a precise Markdown "card" for the OpenROAD Resizer source file `src/DelayEstimatorReporter.cc` (your cwd is the frozen
`src/rsz` tree; read the file and whatever it includes). Keep it factual and compact (80-250 lines).

Graph-derived relations (may be incomplete): calls -> BufferedNet.cc, Delay.cc, DelayEstimator.cc, Graph.cc, GraphDelayCalc.cc, MakeWireParasitics.h, MoveCommitter.cc, MoveGenerator.cc, Opendp.h, OptimizationPolicyConfig.cc, OptimizerTypes.cc, PathEnd.cc, Rebuffer.cc, RebufferMtCandidate.cc, RebufferMtGenerator.cc, Sta.cc ; called by -> Resizer.cc

Sections (exact headings):
# DelayEstimatorReporter.cc
## Purpose (2-4 sentences)
## Public entry points
For each public function/class method that matters: signature, what it is for, who calls it.
## Inputs and outputs, precisely
What state it reads (STA timing, odb netlist/placement, parasitics, options) and what it mutates / returns.
## Algorithm / control flow
Step-by-step of the non-trivial functions, with the heuristics, thresholds, constants and stopping rules named.
## Key data structures
## Callers and callees (verified by reading)
## Invariants and "do not break"
Journaling/rollback expectations, determinism, dont_touch, legality, parasitics validity.
## Weak spots / assumptions an algorithm designer should know
Output only the Markdown.
