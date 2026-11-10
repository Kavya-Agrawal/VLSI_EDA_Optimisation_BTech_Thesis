# AutoDMP: Automated DREAMPlace-based Macro Placement

- **Authors:** A. Agnesina, P. Rajvanshi, T. Yang, G. Pradipta, A. Jiao, B. Keller, B. Khailany, H. Ren (NVIDIA)
- **Venue / Year:** **ISPD 2023** (not on arXiv — PDF from a public course mirror)
- **PDF:** `AutoDMP_ISPD2023.pdf`
- **Link:** https://github.com/NVlabs/AutoDMP · Blog: https://developer.nvidia.com/blog/autodmp-optimizes-macro-placement-for-chip-design-with-ai-and-gpus/

---

## TL;DR (one breath)
AutoDMP is **not RL**. It takes the fast GPU placer **DREAMPlace** and wraps it in **multi-objective Bayesian optimization** that automatically **tunes the placer's knobs** to find great macro placements — balancing wirelength, density, and congestion — very fast on GPUs.

## The problem it fixes
Analytical placers like DREAMPlace are fast but have **many parameters** that hugely affect quality; tuning them by hand is tedious and design-specific. Also, macro + standard-cell **mixed-size** placement is hard to legalize.

## Key idea — autotune a strong placer instead of learning to place
- Use **Multi-Objective Bayesian Optimization (MOTPE / tree-structured Parzen estimator)** to search DREAMPlace's parameter space.
- Optimize **three proxy objectives** post-placement: **wirelength, cell density, routing congestion**.
- Everything runs **on GPUs**, so the search is fast.

## How it works
1. Pick a set of DREAMPlace parameters → run GPU mixed-size placement (macros + cells together).
2. Score the result on the 3 proxies; the Bayesian optimizer proposes the next parameters.
3. A **two-level evaluation**: only **Pareto-optimal** proxy candidates get evaluated inside a slow commercial EDA tool for true PPA.

## Results (headline numbers)
- Matches or beats **commercial tool** flows on PPA.
- Fully **automated** (no human in the loop) and **GPU-fast**.
- Validated on the TILOS macro-placement benchmark, integrated with a commercial flow on NVIDIA DGX/A100.

## Why it matters for your BTP
- README idea #4: *"wrap your placer in AutoDMP-style MOBO for multi-objective PPA."* This is the **autotuning** playbook.
- Great **baseline/complement** to your RL placer — you can compare against it or use MOBO on top of your method.

## Limitations
- Optimizes **proxies**, then verifies a shortlist with slow commercial tools.
- Quality is bounded by what DREAMPlace can express (it tunes, it doesn't invent new placement strategies).

## Mini-glossary
- **DREAMPlace:** GPU-accelerated analytical placer (~30× faster than CPU).
- **Bayesian Optimization (BO):** sample-efficient search for expensive black-box functions.
- **MOTPE:** Multi-Objective Tree-structured Parzen Estimator (a BO method).
- **Pareto-optimal:** solutions where you can't improve one objective without hurting another.
