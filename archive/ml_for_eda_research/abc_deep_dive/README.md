# ABC Deep Dive — ML-for-Logic-Synthesis Research Pack

A complete study of the Berkeley ABC codebase (cloned at `hardware_eda/abc`),
built from a 3-way parallel source-code exploration + literature gap analysis.

**Read in this order:**

| # | File | What it gives you |
|---|------|-------------------|
| 1 | [`01_CODEBASE_GUIDE.md`](01_CODEBASE_GUIDE.md) | How ABC is structured, how to build it, how to read the code, and how to play with it hands-on (tutorial walkthroughs). |
| 2 | [`02_HEURISTIC_MAP.md`](02_HEURISTIC_MAP.md) | Every heuristic decision point inside ABC's algorithms — the "ML injection points" — with file/line references, current rules, and the features available at each point. |
| 3 | [`03_ML_RESEARCH_OPPORTUNITIES.md`](03_ML_RESEARCH_OPPORTUNITIES.md) | What ML work already exists (so you don't repeat it) and **concrete novel research directions** ranked by novelty × feasibility for a BTP. |
| 4 | [`04_ML_INTEGRATION_GUIDE.md`](04_ML_INTEGRATION_GUIDE.md) | Step-by-step engineering guide: build ABC as a library, add custom commands, extract features, wire in a PyTorch/ONNX model, and close the training loop. |

**TL;DR for the impatient:**
- ABC = two worlds: classic `Abc_Ntk_t` (commands like `rewrite`, `resyn2`) and modern GIA `Gia_Man_t` (commands prefixed `&`). One global frame holds both.
- Almost every optimization pass is a **greedy local search with hand-tuned constants** (cut size 4, keep 250 cuts, conflict limit 1000, window 300...). Each such greedy choice is a candidate for a learned policy.
- Crowded research areas: recipe-level RL (DRiLLS/ABC-RL), mapping cut-ranking (SLAP/LEAP/DeepCut). 
- Open areas: **learned resubstitution divisor selection, learned don't-care windowing (mfs), SAT-effort allocation in fraig/dch, node-level rewrite ordering, learned balancing for sharing** — all verified against 2024–26 literature.
