<!-- hand-edited -->
# OpenROAD Resizer & OpenSTA Glossary

One-line precise definitions with the primary command or function where each term appears.

| Term | Command / Function | Definition |
| :--- | :--- | :--- |
| **Arrival Time** | `sta::Vertex::arrival()` (`Sta.cc`) | Latest (or earliest) time a signal transition arrives at a timing vertex relative to the active clock launch edge. |
| **Required Time** | `sta::Vertex::required()` (`Sta.cc`) | Latest time a signal transition may arrive at a timing vertex without violating a setup (or hold) constraint. |
| **Slack** | `sta::Vertex::slack()` / `rsz::slack()` (`Resizer.cc`) | Difference between required time and arrival time; negative slack denotes a timing violation. |
| **WNS (Worst Negative Slack)** | `sta::worstSlack()` (`Resizer.cc:printProgress`) | Most negative slack across all constrained timing endpoints in the design or path group. |
| **TNS (Total Negative Slack)** | `sta::totalNegativeSlack()` (`Resizer.cc:printProgress`) | Sum of all negative slacks across all violating timing endpoints in the design or path group. |
| **Endpoint** | `rsz::RepairTargetCollector::collectPinsByPathEndpoint` (`RepairTargetCollector.cc`) | A timing destination pin: a sequential data input pin (D/SI), or a primary design output port. |
| **Startpoint** | `sta::Search::findStartpoints` / `PathEnd::pathEnd()` (`PathEnd.cc`) | A timing launch origin: a sequential clock pin (CK) or a primary design input port. |
| **Path Group** | `rsz::PathGroupFilter::endpointInGroup` (`PathGroupFilter.cc`) | Named grouping of timing paths (e.g., clock domains, `async2sync`, `in2reg`) scored independently. |
| **Slew (Transition Time)** | `rsz::PreChecks::checkSlewLimit` (`PreChecks.cc`) | Time required for an electrical waveform to transition between specified logic thresholds (e.g., 20% to 80%). |
| **Max Slew Violation** | `rsz::RepairDesign::repairDriverSlew` (`RepairDesign.cc`) | Condition where transition time on a pin exceeds library or user-defined limits (`max_transition`). |
| **Max Cap Violation** | `rsz::RepairDesign::needRepairCap` (`RepairDesign.cc`) | Condition where the total load capacitance on a net exceeds the driver's maximum allowable limit (`max_capacitance`). |
| **Max Fanout Violation** | `rsz::RepairDesign::repairFanout` (`RepairDesign.cc`) | Condition where the number of sink load pins driven by a single output pin exceeds library or user limits. |
| **DRV (Design Rule Violation)** | `rsz::repair_design` (`Resizer.tcl`) | Collective term for maximum slew, maximum capacitance, and maximum fanout limit infractions. |
| **Parasitics (Placement)** | `est::estimate_parasitics -placement` (`EstimateParasitics.cc`) | Wire resistance and capacitance derived from placement locations using Steiner trees without detailed routes. |
| **Parasitics (Global Route)** | `est::estimate_parasitics -global_routing` (`EstimateParasitics.cc`) | Wire resistance and capacitance extracted from global routing guides. |
| **Wire RC** | `rsz::BufferedNet::wireRC` (`BufferedNet.cc`) | Unit resistance ($R$) and capacitance ($C$) models assigned per layer or average platform metal stack. |
| **Steiner Tree** | `rsz::SteinerTree::SteinerTree` (`SteinerTree.cc`) | Minimum or rectilinearly optimized tree connecting a driver and its load pins with intermediate Steiner branching points. |
| **Buffer Tree** | `rsz::Rebuffer::rebuffer` (`Rebuffer.cc`) | Tree topology of inserted repeater buffers that isolates large capacitive loads and balances branch propagation delays. |
| **Rebuffer** | `rsz::Rebuffer::rebufferNet` (`Rebuffer.cc`) | Dynamic programming routine that strips existing repeaters and constructs a delay-optimal buffer tree over a net. |
| **Gate Cloning** | `rsz::CloneGenerator::generate` (`move/CloneGenerator.cc`) | Duplication of a gate to partition high-fanout sink loads between identical parallel drivers, reducing load delay. |
| **Split Load** | `rsz::SplitLoadGenerator::generate` (`move/SplitLoadGenerator.cc`) | Insertion of an intermediate buffer to isolate non-critical fanout branches from the critical timing path. |
| **Size Up** | `rsz::SizeUpGenerator::generate` (`move/SizeUpGenerator.cc`) | Replacement of a standard cell with a higher-drive equivalent from the same footprint family to reduce cell delay. |
| **Size Down** | `rsz::SizeDownFanoutGenerator::generate` (`move/SizeDownFanoutGenerator.cc`) | Downsizing non-critical side-load gates to decrease load capacitance presented to an upstream critical driver. |
| **VT Swap** | `rsz::VtSwapGenerator::generate` (`move/VtSwapGenerator.cc`) | Swapping a cell between high-VT (low-leakage, slower) and low-VT (fast, high-leakage) library variants. |
| **Swap Pins** | `rsz::SwapPinsGenerator::generate` (`move/SwapPinsGenerator.cc`) | Permuting logically equivalent input pins on a multi-input gate to connect the critical net to the fastest internal pin. |
| **Journal (MoveTracker)** | `rsz::MoveTracker::beginJournal` (`MoveTracker.cc`) | Transactional record of netlist and placement mutations enabling incremental rollbacks on rejected speculative moves. |
| **MoveCommitter** | `rsz::MoveCommitter::commitTrackedMoves` (`MoveCommitter.cc`) | Subsystem responsible for legalizing cell positions with OpenDP and committing verified beneficial moves to OpenDB. |
| **dont_touch** | `rsz::Resizer::dontTouch` (`Resizer.cc`) | Attribute marking instances or nets that the resizer is strictly forbidden from modifying, sizing, or buffering. |
| **dont_use** | `rsz::Resizer::dontUse` (`Resizer.cc`) | Attribute specifying library master cells that must never be selected during sizing or repeater insertion. |
| **Last Gasp** | `rsz::SetupLastGaspPolicy::execute` (`policy/SetupLastGaspPolicy.cc`) | Final aggressive optimization phase that applies speculative multi-move combinations on persistent failing endpoints. |
| **TNS End Percent** | `rsz::repair_setup` (`Resizer.tcl:repair_timing`) | Convergence threshold: stops optimization passes when total negative slack reduction drops below this fraction of initial TNS. |
| **repair_tns** | `rsz::repair_timing -repair_tns` (`Resizer.tcl`) | Command argument controlling the stopping threshold percentage for TNS optimization during setup repair passes. |
| **Setup Margin** | `rsz::repair_timing -setup_margin` (`Resizer.tcl`) | Additional timing margin (in time units) added as an artificial offset to setup required times during repair. |
| **Hold Margin** | `rsz::repair_timing -hold_margin` (`Resizer.tcl`) | Safety timing margin added to hold required times to prevent setup repair from creating downstream hold violations. |
| **CRPR (Clock Reconvergence Pessimism Removal)** | `sta::crpr_enabled` (`Resizer.tcl:repair_timing`) | OpenSTA analysis removing artificial delay differences between launch and capture paths on shared clock tree branches. |
| **Path Group Count** | `rsz::PathGroupFilter::pathGroupCount` (`PathGroupFilter.cc`) | Number of distinct active path groups evaluated during multi-group setup repair passes. |
| **Parallel Eval Policy** | `rsz::SetupParallelEvalPolicy::execute` (`policy/SetupParallelEvalPolicy.cc`) | Multithreaded evaluation policy exploring independent move candidates concurrently on disjoint timing subgraphs. |
| **Bottleneck Analysis** | `rsz::BottleneckAnalysis::findBottlenecks` (`policy/BottleneckAnalysis.cc`) | Identification of high-centrality cells and nets traversed by large clusters of critical negative-slack paths. |
| **Elmore Delay** | `rsz::DelayEstimator::elmoreDelay` (`DelayEstimator.cc`) | First-moment approximation of RC interconnect network delay used for rapid heuristic candidate scoring. |
| **DelayEstimator** | `rsz::DelayEstimator::estimate` (`DelayEstimator.cc`) | Analytical proxy calculating expected delay and slew delta before executing expensive full-timer recalculations. |
| **Skew Budget** | `rsz::SkewBudget::computeBudget` (`SkewBudget.cc`) | Sequential timing allocator redistributing clock arrival boundaries across registers via intentional clock skew or latency. |
| **Recover Power** | `rsz::RecoverPower::recoverPower` (`RecoverPower.cc`) | Post-timing pass downsizing or VT-swapping non-critical gates on paths with positive slack to reclaim leakage and dynamic power. |
| **Balance Row Usage** | `rsz::Resizer::balanceRowUsage` (`Resizer.cc`) | Spatial legalization routine redistributing cell placements to equalize cell density across standard cell rows. |
