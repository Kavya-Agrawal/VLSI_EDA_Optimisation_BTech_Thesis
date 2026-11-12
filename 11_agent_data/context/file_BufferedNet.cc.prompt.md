Write a precise Markdown "card" for the OpenROAD Resizer source file `src/BufferedNet.cc` (your cwd is the frozen
`src/rsz` tree; read the file and whatever it includes). Keep it factual and compact (80-250 lines).

Graph-derived relations (may be incomplete): calls -> Delay.cc, EstimateParasitics.h, MakeWireParasitics.h, SizeDownFanoutMtGenerator.cc, Sta.cc, SteinerTree.h ; called by -> AnalysisCorner.cc, ArcDelayCalc.cc, ArnoldiDelayCalc.cc, ArnoldiReduce.cc, BufferCandidate.cc, CcsCeffDelayCalc.cc, CheckCapacitances.cc, CheckFanouts.cc, CheckMaxSkews.cc, CheckMinPeriods.cc, CheckMinPulseWidths.cc, CheckSlews.cc, CheckTiming.cc, ClkInfo.cc, ClkNetwork.cc, CloneCandidate.cc, CloneGenerator.cc, Crpr.cc, DelayCalcBase.cc, DelayEstimator.cc, DelayEstimatorReporter.cc, DelayNoise.cc, DmpCeff.cc, DmpCeffLambertWDelayCalc.cc, DmpDelayCalc.cc, EstimateParasitics.cpp, FindRegister.cc, GatedClk.cc, Genclks.cc, Graph.cc, GraphDelayCalc.cc, Graphics.cc, LumpedCapDelayCalc.cc, MakeTimingModel.cc, MakeWireParasitics.h, MoveCandidate.cc, MoveCommitter.cc, MoveTracker.cc, OptimizationPolicy.cc, Optimizer.cc, OptimizerTypes.cc, Path.cc, PathEnum.cc, PathGroupFilter.cc, PreChecks.cc, PrimaDelayCalc.cc, Property.cc, Rebuffer.cc, RebufferMtCandidate.cc, RecoverPower.cc, RepairDesign.cc, RepairHold.cc, RepairSetupMoveSampler.cc, RepairSetupMoveSnapshot.cc, RepairSetupProfiler.cc, RepairTargetCollector.cc, ReportPath.cc, RerouteCandidate.cc, Resizer.cc, Search.cc, SetupCritVtSwapPolicy.cc, SetupLegacyBase.cc, SetupParallelEvalPolicy.cc, Sim.cc, SizeDownFanoutCandidate.cc, SizeDownFanoutGenerator.cc, SizeDownFanoutMtGenerator.cc, SizeUpCandidate.cc, SizeUpGenerator.cc, SizeUpMatchCandidate.cc, SizeUpMatchGenerator.cc, SplitLoadGenerator.cc, SplitLoadMtCandidate.cc, SplitLoadMtGenerator.cc, Sta.cc, SteinerTree.cpp, SteinerTree.h, SwapPinsGenerator.cc, Tag.cc, TestEstimateParasitics.cc, TestNestedJournal.cc, TestParallelEvalPolicy.cc, TestPreChecks.cc, TestResizer.cc, TestResizerMt.cc, TestSearchStaDesign.cc, TestSearchStaDesignB.cc, TestSkewBudgetRestore.cc, TestSplitLoadMt.cc, UnbufferGenerator.cc, UnbufferMtGenerator.cc, UnitDelayCalc.cc, VisitPathEnds.cc, VtSwapCandidate.cc, VtSwapGenerator.cc, dbEditHierarchy.cc, dbNetwork.cc, dbReadVerilog.cc, dbSdcNetwork.cc, dbSta.cc

Sections (exact headings):
# BufferedNet.cc
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
