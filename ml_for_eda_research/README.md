# ML for EDA — BTP Research Compendium

> A curated, structured survey of **open-source code + research papers** in the
> Machine-Learning-for-EDA (Electronic Design Automation) space, assembled to
> support a B.Tech Project (BTP) on applying ML to chip-design flows
> (placement, routing, logic synthesis, timing/power, LLM-for-RTL, etc.).

**Last updated:** 2026-07-19

> **OpenROAD deep-dive:** see [`openroad/README.md`](openroad/README.md) (branch
> `docs/openroad-ml-landscape`) and model code branches
> `feature/openroad-timing-gnn`, `feature/openroad-rl-gatesize`,
> `feature/openroad-congestion-cnn`.

---

## 0. How to use this document

- 📝 **New:** every downloaded paper now has a **plain-English summary** (a `.md` file next to
  its PDF) explaining it in ~2 minutes: *TL;DR → problem → key idea → how it works → results →
  why it matters → glossary*. **Start at [`papers/PAPER_SUMMARIES.md`](papers/PAPER_SUMMARIES.md)**
  for a guided, ordered index of all **26 papers**.
- Each domain section lists **open-source repos you can `git clone`** (with a one-line
  "why it matters" + license + language) followed by the **key papers**.
- Papers marked **[PDF]** have been downloaded into `papers/<domain>/` for offline reading.
  See [`papers/DOWNLOAD_INDEX.md`](papers/DOWNLOAD_INDEX.md) for the file map.
- Repos are ordered roughly **most-relevant / most-recent first**.
- Your existing `macroPlace/` work (modified MaskPlace actor-critic with expanded action
  space + better macro ordering) sits under the **Placement** domain — everything there is
  directly extensible from the repos in Section 2.

### Quick recommendation for where to apply ML in your BTP
1. **Placement / macro placement** (your current strength) → Section 2. Most active RL/diffusion research, easiest to show novelty.
2. **Cross-stage prediction** (congestion / DRC / IR-drop / timing) using **CircuitNet** → Section 5. Lowest infra barrier — it's a ready ML dataset, pure PyTorch.
3. **Logic synthesis sequence optimization** (RL over ABC) → Section 4. Clean RL formulation, small compute.
4. **LLM-for-RTL / LLM-for-EDA-scripts** → Section 6. Hot area, lots of low-hanging fruit.

---

## 1. Foundational infrastructure (clone these first)

These are the tools the whole ecosystem builds on. You will almost certainly need OpenROAD + ORFS and DREAMPlace.

| Repo | Why it matters | Lang | License |
|---|---|---|---|
| [The-OpenROAD-Project/OpenROAD](https://github.com/The-OpenROAD-Project/OpenROAD) | The leading open-source RTL→GDSII engine (place, route, CTS, STA). The backbone for almost every ML-EDA evaluation. Tcl + Python API. | C++ | BSD-3 |
| [The-OpenROAD-Project/OpenROAD-flow-scripts (ORFS)](https://github.com/The-OpenROAD-Project/OpenROAD-flow-scripts) | Autonomous RTL→GDS flow wrapper w/ open PDKs (nangate45, asap7, sky130). Where you plug ML in and measure PPA. | Tcl/Py | BSD-3 |
| [limbo018/DREAMPlace](https://github.com/limbo018/DREAMPlace) | GPU analytical placer, ~30× faster than CPU RePlAce. Used as the standard-cell placer / legalizer in nearly all RL macro-placement papers (incl. MaskPlace, macro-regulator). | C++/CUDA/Py | BSD-3 |
| [NYU-MLDA/DREAMPlace](https://github.com/NYU-MLDA/DREAMPlace) | Fork with 2-stage macro (BB-step, ICCAD'23) additions. | C++/CUDA | BSD-3 |
| [SiliconCompiler](https://github.com/siliconcompiler/siliconcompiler) | Distributed silicon-compilation framework; nice Python-first flow control. | Py | Apache-2 |
| [OSCC-Project/iEDA](https://github.com/OSCC-Project/iEDA) | Full open-source EDA infrastructure (Chinese OSCC); pairs with iPD toolchain. Good alt to OpenROAD. | C++ | MulanPSL |

---

## 2. Placement & Macro Placement  *(your BTP core)*

### Open-source code
| Repo | Method / Venue | Why it matters | Lang | License |
|---|---|---|---|---|
| [laiyao1/maskplace](https://github.com/laiyao1/maskplace) | **MaskPlace** (NeurIPS'22 Spotlight) | RL + visual (wiremask) representation for macro placement. **This is the base you modified in `macroPlace/`.** | Py | — |
| [laiyao1/ChiPFormer](https://github.com/laiyao1/chipformer) | **ChiPFormer** (ICML'23) | Offline RL via Decision Transformer → *transferable* placement, fast fine-tuning. Strong next step from MaskPlace. | Py | — |
| [lamda-bbo/macro-regulator](https://github.com/lamda-bbo/macro-regulator) | **MaskRegulate** (NeurIPS'24) | Reframes RL as a *refiner* of existing placements (not from-scratch) + regularity metric. Denser rewards, better PPA. Very relevant to "better ordering / action space" ideas. | C++/Py/CUDA | — |
| [vint-1/chipdiffusion](https://github.com/vint-1/chipdiffusion) | **ChipDiffusion** (ICML'25) | Diffusion model w/ guided sampling → zero-shot transfer, no online RL. The newest paradigm. | Jupyter/Py | — |
| [google-research/circuit_training](https://github.com/google-research/circuit_training) | **AlphaChip** (Nature'21) | Google's distributed RL floorplanner (the paper that started the field). GNN value net + edge/orientation. | Py | Apache-2 |
| [TILOS-AI-Institute/MacroPlacement](https://github.com/TILOS-AI-Institute/MacroPlacement) | Benchmark / reproducibility | Transparent re-implementation & assessment of AlphaChip vs SA vs commercial. Benchmarks + flows. | Py/Tcl | BSD-3/Apache |
| [NVlabs/AutoDMP](https://github.com/NVlabs/AutoDMP) | **AutoDMP** (ISPD'23) | DREAMPlace + multi-objective Bayesian optimization (MOTPE) autotuning of macro placement. GPU. | Py/CUDA | BSD-3 |
| [Thinklab-SJTU/EDA-AI](https://github.com/Thinklab-SJTU/EDA-AI) | DeepPlace / PRNet (NeurIPS'21,'22) | Joint learning of placement + routing; policy-gradient placement + generative routing. | Py | — |

### Key papers  (downloaded → `papers/placement/`, each with a 📝 `.md` summary)
- **Chip Placement with Deep Reinforcement Learning** — Mirhoseini et al. Google 2020 → Nature 2021. [arXiv 2004.10746] **[PDF]** *(the origin of the field)*
- **MaskPlace: Fast Chip Placement via Reinforced Visual Representation Learning** — Lai, Mu, Luo. NeurIPS 2022 (Spotlight). [arXiv 2211.13382] **[PDF]** *(your base)*
- **ChiPFormer: Transferable Chip Placement via Offline Decision Transformer** — Lai et al. ICML 2023. [arXiv 2306.14744] **[PDF]**
- **Macro Placement by Wire-Mask-Guided Black-Box Optimization** — Shi et al. NeurIPS 2023. [arXiv 2306.16844] **[PDF]**
- **Reinforcement Learning Policy as Macro Regulator Rather than Macro Placer** — NeurIPS 2024. [arXiv 2412.07167] **[PDF]**
- **Chip Placement with Diffusion Models** — ICML 2025. [arXiv 2407.12282] **[PDF]**
- **AutoDMP: Automated DREAMPlace-based Macro Placement** — Agnesina et al. ISPD 2023 (not on arXiv; ACM/public mirror). **[PDF]**
- **On Joint Learning for Solving Placement and Routing in Chip Design (DeepPlace/DeepPR)** — NeurIPS 2021. [arXiv 2111.00234] **[PDF]**
- **Delving into Macro Placement with Reinforcement Learning** — Jiang et al. ISPD 2022. [arXiv 2109.02587] **[PDF]**
- **A Graph Placement Methodology for Fast Chip Design (AlphaChip)** — Mirhoseini et al. Nature 2021. [nature link — see index]

---

## 3. Routing (global / detailed) & DRC-driven routing

### Open-source code
| Repo | Method / Venue | Why it matters | Lang | License |
|---|---|---|---|---|
| [cuhk-eda/Dr-Guide](https://github.com/cuhk-eda/Dr-Guide) | **Dr. Guide** (MLCAD'25) | Generative (flow-matching) AI producing co-planned route guides for many nets. Newest generative-routing work. | C++ | BSD-3 |
| [OSCC-Project/iPCL-R](https://github.com/OSCC-Project/iPCL-R) | **iPCL-R** | Pre-training foundation model treating routing patterns as sequences (LLM-style). DEF output. | Py | — |
| [Thinklab-SJTU/EDA-AI (PRNet/DSBRouter)](https://github.com/Thinklab-SJTU/EDA-AI) | Generative routing | End-to-end learned global routing. | Py | — |

### Key papers  (downloaded → `papers/routing/`, with a 📝 `.md` summary)
- **A Deep Reinforcement Learning Approach for Global Routing** — Liao et al. J. Mech. Design 2019. [arXiv 1906.08809] **[PDF]**
- **Dr. Guide: AI-Guided Detailed Routing** — Wang, Lau, Ho, Young, Wong. MLCAD 2025.
- **AiDRC: Accelerating Detailed Routing by AI-Driven DRV Prediction and Checking** — TODAES 2025. (ResNet + crisscross attention; 16×/293× speedups.)
- **RouteNet: Routability Prediction for Mixed-Size Designs Using CNN** — ICCAD 2018. (Classic; DRC-hotspot CNN.)

---

## 4. Logic Synthesis (RL over ABC / sequence optimization)

### Open-source code
| Repo | Method / Venue | Why it matters | Lang | License |
|---|---|---|---|---|
| [scale-lab/DRiLLS](https://github.com/scale-lab/DRiLLS) | **DRiLLS** (ASPDAC'20) | A2C agent that learns ABC optimization recipes (area under timing constraint). The canonical RL-for-synthesis repo. | Py/Tcl | BSD-3 |
| [NYU-MLDA/ABC-RL](https://github.com/NYU-MLDA/ABC-RL) | **ABC-RL** (ICLR'24) | Retrieval-guided RL + GNN + MCTS for Boolean circuit minimization. State-of-the-art recipe search. | Py | GPL-3 |
| [Gabriel-in-Toronto/RL4LS](https://github.com/Gabriel-in-Toronto/RL4LS) | **RL4LS** (ASPDAC'23) | Area-driven FPGA synthesis; per-circuit recipe via Stable-Baselines3. Easy to run. | Py | — |
| [berkeley-abc/abc](https://github.com/berkeley-abc/abc) | ABC engine | The synthesis tool everything drives. `abc_py` gives Python bindings. | C | MIT-like |
| [krzhu/abc_py](https://github.com/krzhu/abc_py) | Python bindings for ABC | Needed for the RL loops above. | C++/Py | — |

### Key papers  (downloaded → `papers/logic_synthesis/`, each with a 📝 `.md` summary)
- **DRiLLS: Deep Reinforcement Learning for Logic Synthesis** — Hosny et al. ASPDAC 2020. [arXiv 1911.04021] **[PDF]**
- **OpenABC-D: A Large-Scale Dataset for ML-Guided IC Synthesis** — 2021. [arXiv 2110.11292] **[PDF]**
- **Rethinking Reinforcement Learning based Logic Synthesis** — Wang et al. (Huawei) 2022. [arXiv 2205.07614] **[PDF]** *(myth-busting; read before over-engineering RL)*
- **Logic Synthesis Meets Machine Learning: Trading Exactness for Generalization** — IWLS 2020. [arXiv 2012.02530] **[PDF]**
- **Retrieval-Guided Reinforcement Learning for Boolean Circuit Minimization (ABC-RL)** — ICLR 2024. [OpenReview 0t1O8ziRZp]
- **Area-Driven FPGA Logic Synthesis Using Reinforcement Learning** — ASPDAC 2023.

---

## 5. Cross-stage prediction — Timing / Power / Congestion / DRC / IR-drop

> This is the **lowest-barrier entry point**: CircuitNet gives you ready ML-ready tensors,
> so you can do pure PyTorch without running a full EDA flow.

### Datasets + code
| Repo | What | Why it matters | License |
|---|---|---|---|
| [circuitnet/CircuitNet](https://github.com/circuitnet/CircuitNet) | **CircuitNet 1.0/2.0/N14/N28** | 20K+ samples for congestion, DRC, IR-drop, net-delay prediction. Image (CNN) + graph (GNN) features. The go-to ML-EDA dataset. | BSD-3 |
| [NVlabs/CircuitOps](https://github.com/NVlabs/CircuitOps) | Labeled Property Graphs | Netlist→graph IR for GNN-based EDA ML, integrated w/ OpenROAD. | — |

### Key papers  (downloaded → `papers/timing_power_routability/`, each with a 📝 `.md` summary)
- **CircuitNet: An Open-Source Dataset for ML Applications in EDA** — TCAD 2023. [arXiv 2208.01040] **[PDF]** *(the go-to dataset)*
- **Net2: A Graph Attention Network for Pre-Placement Net Length Estimation** — Xie et al. ASPDAC 2021. [arXiv 2011.13522] **[PDF]**
- **PGR-DRC: Pre-Global-Routing DRC Violation Prediction Using Unsupervised Learning** — 2025. [arXiv 2507.13355] **[PDF]**
- **CircuitNet 2.0: Advanced Dataset for Realistic Chip Design** — 2023.
- **A Timing Engine Inspired GNN Model for Pre-Routing Slack Prediction** — DAC 2022 (github.com/TimingPredict). (Basis of net-delay GNN.)
- **RouteNet** (see routing) — congestion/DRC CNN.

---

## 6. LLM for EDA (RTL generation, EDA-script agents)

### Open-source code
| Repo | Method | Why it matters | License |
|---|---|---|---|
| [hkust-zhiyao/RTL-Coder](https://github.com/hkust-zhiyao/RTL-Coder) | **RTLCoder** (TCAD'25) | 7B open LLM + 27K-sample dataset for Verilog gen; beats GPT-3.5, 4-bit fits on a laptop. Full data+train+model open. | — |
| [NVlabs/verilog-eval](https://github.com/NVlabs/verilog-eval) | **VerilogEval** | The standard benchmark for LLM Verilog generation. | — |
| [hkust-zhiyao/RTLLM](https://github.com/hkust-zhiyao/RTLLM) | **RTLLM** | Open benchmark of RTL design problems. | — |

### Key papers  (downloaded → `papers/llm_for_eda/`, each with a 📝 `.md` summary)
- **Benchmarking LLMs for Automated Verilog RTL Code Generation (VeriGen)** — Thakur et al. DATE 2023. [arXiv 2212.11140] **[PDF]**
- **VerilogEval: Evaluating LLMs for Verilog Code Generation** — Liu et al. (NVIDIA) ICCAD 2023. [arXiv 2309.07544] **[PDF]** *(the standard benchmark)*
- **RTLCoder: Fully Open-Source and Efficient LLM-Assisted RTL Code Generation** — TCAD 2025. [arXiv 2312.08617] **[PDF]**
- **RTLLM: An Open-Source Benchmark for Design RTL Generation** — Lu et al. ASPDAC 2024. [arXiv 2308.05345] **[PDF]**
- **ChipNeMo: Domain-Adapted LLMs for Chip Design** — NVIDIA 2023. [arXiv 2311.00176] **[PDF]**
- **ChatEDA: An LLM-Powered Autonomous Agent for EDA** — MLCAD 2023. [arXiv 2308.10204] **[PDF]**
- **MAGE: A Multi-Agent Engine for Automated RTL Code Generation** — 2024. [arXiv 2412.07822] **[PDF]**

---

## 7. Analog / Mixed-signal layout (bonus domain)

| Repo / Paper | Method | Note |
|---|---|---|
| **SACPlace** (DATE'25) | Multi-agent DRL for symmetry-aware analog placement | HPWL + symmetry constraints |
| **Analog ICs Floorplanning w/ Relational GNN + RL** (DATE'25) | R-GCN + RL, cross-topology transfer | 67% layout-time reduction |
| CLARA / ALIGN / MAGICAL | Open analog layout frameworks | Good infra if you pivot to analog |

---

## 8. Curated meta-lists (keep these bookmarked — updated continuously)

| List | Scope |
|---|---|
| [ai4eda/awesome-AI4EDA](https://github.com/ai4eda/awesome-AI4EDA) → [website](https://ai4eda.github.io) | BibTeX-backed, categorized by flow stage (HLS, logic-syn, place, CTS, route, timing, OPC, analog, testing, datasets). |
| [Thinklab-SJTU/awesome-ai4eda](https://github.com/Thinklab-SJTU/awesome-ai4eda) | Problem-oriented list w/ code links (DeepPlace, PRNet, etc.). |
| [OSCC-Project/awesome-AIEDA-works](https://github.com/OSCC-Project/awesome-AIEDA-works) | Structured: placement, routing, timing/power, DRC, datasets, foundation models. |

### Survey papers (downloaded → `papers/surveys/`, each with a 📝 `.md` summary — read these first)
- **Machine Learning for EDA: A Survey** — TODAES 2021. [arXiv 2102.03357] **[PDF]**
- **Towards ML for Placement and Routing in Chip Design: A Methodological Overview** — 2022. [arXiv 2202.13564] **[PDF]**
- **A Survey of GNNs for EDA** — MLCAD 2021.

---

## 9. Suggested BTP directions (building on your MaskPlace work)

1. **Extend the ChiPFormer / diffusion paradigm** to your expanded action space — offline-RL or diffusion may generalize your macro-ordering gains across benchmarks without per-design retraining.
2. **MaskRegulate-style refinement head** on top of your placer — add a regularity reward, close the loop to real PPA via ORFS.
3. **Cross-stage reward** — replace HPWL proxy with a CircuitNet-trained congestion/timing predictor as a fast differentiable reward (LaMPlace-style).
4. **Autotuning wrapper** — wrap your placer in AutoDMP-style MOBO for multi-objective PPA.
5. **End-to-end eval** — always report through OpenROAD/ORFS (routed WL, DRC, timing), not just HPWL, to match `ChiPBench` methodology.

---

*Generated as part of BTP research setup. Repo/paper links verified 2026-07-18. Paper collection expanded to 26 papers, each with a plain-English summary — see [`papers/PAPER_SUMMARIES.md`](papers/PAPER_SUMMARIES.md).*
