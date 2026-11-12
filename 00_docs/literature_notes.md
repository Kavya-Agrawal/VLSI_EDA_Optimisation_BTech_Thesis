# Classical & Autonomous EDA Literature Notes

This document surveys the foundational classical physical design algorithms alongside modern autonomous code-evolution frameworks, detailing their concrete injection points in OpenROAD's `src/rsz` codebase.

---

### 1. Lagrangian-Relaxation Gate Sizing
- **Citation**: C. P. Chen, C. C. N. Chu, and D. F. Wong, "Fast and Exact Simultaneous Gate and Wire Sizing by Lagrangian Relaxation," *IEEE Transactions on Computer-Aided Design of Integrated Circuits and Systems*, vol. 18, no. 7, pp. 1014–1025, July 1999.
- **Summary**: Formulates the simultaneous gate and wire sizing problem as a convex optimization under posynomial delay models (Elmore delay). By relaxing the timing constraints into the objective function via Lagrange multipliers (representing path criticality or shadow prices of delay at each circuit node), the problem decomposes into separable subproblems that can be solved efficiently using Kuhn-Tucker conditions. Subgradient descent updates the multipliers until arrivals satisfy clock period requirements with minimum area or power.
- **What it would change in rsz**: Directly replaces the greedy, one-cell-at-a-time pass in `sizing` (`src/policy/GlobalSizingPolicy.cc` and `src/LRSubproblem.cc`) by formulating global multiplier updates across all timing arcs and guiding parallel cell selection based on optimal gate drive multipliers rather than local slack gradients.

---

### 2. TILOS (Timed Logic Synthesizer)
- **Citation**: J. P. Fishburn and A. E. Dunlop, "TILOS: A Posynomial Programming Approach to Transistor Sizing," *IEEE International Conference on Computer-Aided Design (ICCAD)*, pp. 326–328, Nov. 1985.
- **Summary**: TILOS pioneered sensitivity-based continuous gate and transistor sizing. It calculates the sensitivity of the worst critical path delay with respect to each device's size ($\partial \text{Delay} / \partial \text{Area}$ or $\partial \text{Slack} / \partial \text{Cap}$). In each iteration, it selects the driver yielding the largest delay reduction per unit increase in area, sizes it up incrementally, updates delays through topological traversal, and repeats until setup timing is met or area limits are reached.
- **What it would change in rsz**: In `sizing` (`src/move/SizeUpGenerator.cc` and `src/DelayEstimator.cc`), replaces the discrete heuristic search (which currently tests only immediate library neighbors in order) with a global sensitivity heap that prioritizes candidates with maximal $\Delta \text{Slack} / \Delta \text{Area}$ before invoking local candidate evaluation.

---

### 3. van Ginneken & Lillis Buffer Insertion
- **Citation**: L. P. P. P. van Ginneken, "Buffer Placement in Distributed RC-tree Networks for Minimal Elmore Delay," *International Symposium on Circuits and Systems (ISCAS)*, pp. 865–868, May 1990; and J. Lillis, C. K. Cheng, and T. T. Y. Lin, "Optimal Wire Sizing and Buffer Insertion for Low Power and a Generalized Delay Model," *IEEE Journal of Solid-State Circuits*, vol. 31, no. 3, pp. 437–447, Mar. 1996.
- **Summary**: van Ginneken formulated polynomial-time optimal buffer placement on a fixed Steiner tree using dynamic programming. Moving bottom-up from sinks to root, it constructs Pareto-optimal $(C, T)$ curves (input capacitance vs. required arrival time), pruning dominated pairs. Lillis extended this formulation to handle multiple buffer types, inverting repeaters, wire sizing, and area/power trade-offs.
- **What it would change in rsz**: In `buffering` (`src/BufferedNet.cc` and `src/Rebuffer.cc`), enriches the candidate buffer-tree generation by incorporating multi-buffer type libraries, polarity-aware inverting buffer chains, and capacitance-limit pruning directly within the bottom-up Steiner traversal, replacing the existing heuristic split-point enumeration.

---

### 4. Slack Budgeting & Zero-Slack Algorithm (ZSA)
- **Citation**: R. Nair, C. L. Berman, P. S. Hauge, and E. J. Yoffa, "Generation of Performance Constraints for Layout," *IEEE Transactions on Computer-Aided Design of Integrated Circuits and Systems*, vol. 8, no. 8, pp. 860–874, Aug. 1989.
- **Summary**: The Zero-Slack Algorithm (ZSA) distributes available timing slack across the nets and cells of a combinatorial network such that every path achieves zero slack, establishing upper bounds on individual net delays. It iteratively identifies the path with minimal positive slack, equally or proportionally allocates that slack among its constitutive elements, and fixes those delay bounds, freeing non-critical paths to downsize or conserve routing resources.
- **What it would change in rsz**: In `setup_strategy` (`src/policy/BottleneckAnalysis.cc` and `src/policy/SetupWnsPolicy.cc`), replaces the localized single-endpoint slack checks with a global slack budgeting pass that assigns explicit delay improvement targets ($\Delta D$) to each logic stage, preventing upstream sizing moves from thrashing downstream timing.

---

### 5. Timing-Driven ECO Gate Sizing
- **Citation**: O. Coudert, R. Haddad, and S. Manne, "New Algorithms for Gate Sizing: A Comparative Study," *ACM Transactions on Design Automation of Electronic Systems (TODAES)*, vol. 5, no. 2, pp. 113–135, Apr. 2000; and J. Cong and C. Koh, "Simultaneous Area and Slew Optimization in Timing-Driven ECO," *ICCAD*, 2001.
- **Summary**: Timing-driven Engineering Change Order (ECO) optimization focuses on recovering timing violations late in the physical design flow while minimizing physical disturbance (displacement, routing congestion, and pin perturbations). It balances aggressive local drive boosting on critical negative-slack paths with opportunistic downsizing on positive-slack side-fanouts to reclaim capacitance margin and reduce driver slew degradation.
- **What it would change in rsz**: In `sizing` (`src/move/SizeDownFanoutGenerator.cc` and `src/policy/SetupDirectionalPolicy.cc`), introduces coupled dual-action moves: whenever a high-fanout driver on a critical path is sized up, its non-critical side sinks are immediately downsized, minimizing total pin-load capacitance and avoiding secondary slew violations.

---

### 6. Autonomous Multi-Agent EDA Evolution: Self-Evolved ABC
- **Citation**: C. Yu and H. Ren, "Autonomous Evolution of EDA Tools: Multi-Agent Self-Evolved ABC," *63rd ACM/IEEE Design Automation Conference (DAC '26)*, arXiv:2604.15082 [cs.AR], Apr. 2026.
- **Summary**: Demonstrates the first self-evolving logic synthesis framework operating on the full, million-line ABC repository. A central Planning Agent coordinates three specialized coding agents (targeting flow scheduling, technology mapping, and logic minimization). Each cycle proposes C code modifications, compiles the tool, enforces combinational equivalence checking (CEC) via formal verification, and evaluates QoRs across multi-suite benchmarks. Guided by a self-evolving rulebase and structured Markdown documentation, the system discovered novel synthesis heuristics achieving up to 8.3% QoR gains.
- **What it would change in rsz**: Provides the foundational multi-agent architecture for `pv_resizer_evolve`: decomposing `src/rsz` into specialized sub-clusters (`setup_strategy`, `sizing`, `buffering`), driven by an automated cycle of planning, code generation, compilation gates, fast pre-route OpenSTA evaluation, and rulebase refinement.

---

### 7. SATLUTION: Repository-Scale SAT Solver Evolution
- **Citation**: C. Yu, R. Liang, C.-T. Ho, and H. Ren, "Autonomous Code Evolution Meets NP-Completeness: SATLUTION," *arXiv:2509.07367 [cs.AI]*, Sept. 2025.
- **Summary**: Introduces an LLM-driven autonomous code evolution framework capable of modifying entire SAT solver repositories (tens of thousands of C/C++ lines). Solvers are evolved through coordinated planning and coding agents constrained by strict formal validation (DRAT proof verification for UNSAT instances). The resulting self-evolved solvers discovered novel variable selection and clause learning heuristics that outperformed human-engineered champions of the International SAT Competition.
- **What it would change in rsz**: In `setup_strategy` (`src/policy/OptimizationPolicy.hh` and `src/MoveCommitter.cc`), introduces formal gatekeeper contracts, strict multi-stage verification (compilation, regression testing, and rollback journaling), ensuring that speculative algorithmic transformations never compromise placement validity or netlist integrity.

---

### 8. AlphaEvolve: Autonomous Algorithmic Discovery
- **Citation**: A. Novikov, N. Vu, M. Eisenberger, E. Dupont, P.-S. Huang, A. Z. Wagner, et al., "AlphaEvolve: A Coding Agent for Scientific and Algorithmic Discovery," *Google DeepMind Technical Report*, Apr. 2025.
- **Summary**: AlphaEvolve leverages iterative LLM prompting paired with an automated evaluation loop to explore, mutate, and optimize complex mathematical and algorithmic kernels (e.g., matrix multiplication, tensor decomposition, combinatorial optimization). By evaluating candidate procedures on benchmark sets, extracting granular performance signals, and prompting the model with comparative execution traces, AlphaEvolve autonomously converges to algorithms superior to existing human baselines.
- **What it would change in rsz**: In `timing_model` (`src/DelayEstimator.cc` and `src/DelayEstimatorBufferTree.cc`), enables autonomous kernel refinement for Elmore delay approximations and slew-bias prediction functions, evolving analytical models that match Signoff STA accuracy with orders of magnitude faster evaluation speed.
