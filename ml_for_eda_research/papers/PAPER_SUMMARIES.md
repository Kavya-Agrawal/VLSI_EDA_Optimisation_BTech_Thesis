# Paper Summaries — Read Me First

This is the **guided index** to every paper in this collection. **Each PDF has a matching `.md` file** right next to it that explains the paper in plain English (TL;DR, the problem, the key idea, how it works, results, why it matters, and a mini-glossary).

- 📄 = the original paper (PDF)
- 📝 = the easy-to-understand summary (Markdown, ~2-min read)
- **26 papers** across 6 domains.

> New here? Read the two **surveys** first for the big picture, then dive into your domain.

---

## ⭐ Suggested reading order (fastest path to understanding)

1. **Big picture:** `surveys/ML_for_EDA_Survey_TODAES2021.md` → `surveys/ML_Placement_Routing_Overview_2022.md`
2. **Placement story (in order):** ChipPlacement_DeepRL (Google, the origin) → MaskPlace (your base) → ChiPFormer (transfer) → WireMask-BBO & MacroRegulator (ordering/refinement) → ChipDiffusion (newest) → AutoDMP (autotuning) → DeepPlace / DelvingMacroPlacement (context).
3. **Logic synthesis:** DRiLLS → OpenABC-D → Rethinking-RL → LogicSynthesisMeetsML.
4. **Cross-stage prediction:** CircuitNet → Net2 → PGR-DRC.
5. **LLM-for-EDA:** VeriGen → VerilogEval → RTLCoder → RTLLM → ChipNeMo → ChatEDA → MAGE.
6. **Routing:** DeepRL_GlobalRouting.

---

## 1. Placement & Macro Placement  *(your BTP core — 9 papers)*

| Paper | Venue | 📄 PDF | 📝 Summary |
|---|---|---|---|
| Chip Placement with Deep RL (the origin) | Google/Nature '20–'21 | [PDF](placement/ChipPlacement_DeepRL_Google2020.pdf) | [Summary](placement/ChipPlacement_DeepRL_Google2020.md) |
| **MaskPlace** (your base) | NeurIPS '22 | [PDF](placement/MaskPlace_NeurIPS2022.pdf) | [Summary](placement/MaskPlace_NeurIPS2022.md) |
| ChiPFormer (transferable, offline RL) | ICML '23 | [PDF](placement/ChiPFormer_ICML2023.pdf) | [Summary](placement/ChiPFormer_ICML2023.md) |
| WireMask-BBO (ordering via black-box opt) | NeurIPS '23 | [PDF](placement/WireMaskBBO_NeurIPS2023.pdf) | [Summary](placement/WireMaskBBO_NeurIPS2023.md) |
| MacroRegulator (RL as refiner) | NeurIPS '24 | [PDF](placement/MacroRegulator_NeurIPS2024.pdf) | [Summary](placement/MacroRegulator_NeurIPS2024.md) |
| ChipDiffusion (diffusion, zero-shot) | ICML '25 | [PDF](placement/ChipDiffusion_ICML2025.pdf) | [Summary](placement/ChipDiffusion_ICML2025.md) |
| AutoDMP (GPU + Bayesian autotuning) | ISPD '23 | [PDF](placement/AutoDMP_ISPD2023.pdf) | [Summary](placement/AutoDMP_ISPD2023.md) |
| DeepPlace/DeepPR (joint place+route) | NeurIPS '21 | [PDF](placement/DeepPlace_JointPlaceRoute_NeurIPS2021.pdf) | [Summary](placement/DeepPlace_JointPlaceRoute_NeurIPS2021.md) |
| Delving into Macro Placement w/ RL | ISPD '22 | [PDF](placement/DelvingMacroPlacement_ISPD2022.pdf) | [Summary](placement/DelvingMacroPlacement_ISPD2022.md) |

## 2. Logic Synthesis (RL over ABC — 4 papers)

| Paper | Venue | 📄 PDF | 📝 Summary |
|---|---|---|---|
| **DRiLLS** (canonical RL-for-synthesis) | ASP-DAC '20 | [PDF](logic_synthesis/DRiLLS_ASPDAC2020.pdf) | [Summary](logic_synthesis/DRiLLS_ASPDAC2020.md) |
| OpenABC-D (the dataset) | 2021 | [PDF](logic_synthesis/OpenABC-D_2021.pdf) | [Summary](logic_synthesis/OpenABC-D_2021.md) |
| Rethinking RL-based Logic Synthesis (myth-busting) | 2022 | [PDF](logic_synthesis/RethinkingRL_LogicSynthesis_2022.pdf) | [Summary](logic_synthesis/RethinkingRL_LogicSynthesis_2022.md) |
| Logic Synthesis Meets ML (circuit as classifier) | IWLS '20 | [PDF](logic_synthesis/LogicSynthesisMeetsML_2020.pdf) | [Summary](logic_synthesis/LogicSynthesisMeetsML_2020.md) |

## 3. Cross-stage Prediction — Timing / Power / Congestion / DRC (3 papers)

| Paper | Venue | 📄 PDF | 📝 Summary |
|---|---|---|---|
| **CircuitNet** (the go-to dataset) | TCAD '23 | [PDF](timing_power_routability/CircuitNet_TCAD2023.pdf) | [Summary](timing_power_routability/CircuitNet_TCAD2023.md) |
| Net2 (pre-placement net length) | ASP-DAC '21 | [PDF](timing_power_routability/Net2_NetLength_ASPDAC2021.pdf) | [Summary](timing_power_routability/Net2_NetLength_ASPDAC2021.md) |
| PGR-DRC (unsupervised DRC prediction) | 2025 | [PDF](timing_power_routability/PGR-DRC_UnsupervisedDRC_2025.pdf) | [Summary](timing_power_routability/PGR-DRC_UnsupervisedDRC_2025.md) |

## 4. LLM for EDA (RTL generation & agents — 7 papers)

| Paper | Venue | 📄 PDF | 📝 Summary |
|---|---|---|---|
| VeriGen (first Verilog fine-tuning study) | DATE '23 | [PDF](llm_for_eda/VeriGen_Benchmarking_DATE2023.pdf) | [Summary](llm_for_eda/VeriGen_Benchmarking_DATE2023.md) |
| **VerilogEval** (the standard benchmark) | ICCAD '23 | [PDF](llm_for_eda/VerilogEval_ICCAD2023.pdf) | [Summary](llm_for_eda/VerilogEval_ICCAD2023.md) |
| RTLCoder (open 7B, beats GPT-3.5) | TCAD '25 | [PDF](llm_for_eda/RTLCoder_TCAD2025.pdf) | [Summary](llm_for_eda/RTLCoder_TCAD2025.md) |
| RTLLM (design-scale benchmark + Self-Planning) | ASP-DAC '24 | [PDF](llm_for_eda/RTLLM_ASPDAC2024.pdf) | [Summary](llm_for_eda/RTLLM_ASPDAC2024.md) |
| ChipNeMo (domain-adapted LLMs) | NVIDIA '23 | [PDF](llm_for_eda/ChipNeMo_2023.pdf) | [Summary](llm_for_eda/ChipNeMo_2023.md) |
| ChatEDA (LLM agent for RTL→GDSII) | MLCAD '23 | [PDF](llm_for_eda/ChatEDA_MLCAD2023.pdf) | [Summary](llm_for_eda/ChatEDA_MLCAD2023.md) |
| MAGE (multi-agent RTL generation) | 2024 | [PDF](llm_for_eda/MAGE_MultiAgentRTL_2024.pdf) | [Summary](llm_for_eda/MAGE_MultiAgentRTL_2024.md) |

## 5. Routing (1 paper)

| Paper | Venue | 📄 PDF | 📝 Summary |
|---|---|---|---|
| A Deep RL Approach for Global Routing | J. Mech. Design '19 | [PDF](routing/DeepRL_GlobalRouting_2019.pdf) | [Summary](routing/DeepRL_GlobalRouting_2019.md) |

## 6. Surveys — start here (2 papers)

| Paper | Venue | 📄 PDF | 📝 Summary |
|---|---|---|---|
| ML for EDA: A Survey (whole flow) | TODAES '21 | [PDF](surveys/ML_for_EDA_Survey_TODAES2021.pdf) | [Summary](surveys/ML_for_EDA_Survey_TODAES2021.md) |
| ML for Placement & Routing: Overview | 2022 | [PDF](surveys/ML_Placement_Routing_Overview_2022.pdf) | [Summary](surveys/ML_Placement_Routing_Overview_2022.md) |

---

## How each summary is structured
Every 📝 file follows the same layout so you can skim fast:
**TL;DR → The problem → Key idea → How it works → Results → Why it matters for your BTP → Limitations → Mini-glossary.**

*Collection assembled & summarized 2026-07-18. See `DOWNLOAD_INDEX.md` for the raw file/arXiv map and `../download_papers.ps1` to re-download.*
