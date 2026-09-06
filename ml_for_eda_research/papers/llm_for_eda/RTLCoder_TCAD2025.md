# RTLCoder: Outperforming GPT-3.5 in Design RTL Generation with an Open-Source Dataset and Lightweight Solution

- **Authors:** Shang Liu, Wenji Fang, Yao Lu, Qijun Zhang, Hongce Zhang, Zhiyao Xie (HKUST)
- **Venue / Year:** **TCAD 2025** (arXiv 2023)
- **PDF:** `RTLCoder_TCAD2025.pdf`
- **Link:** https://arxiv.org/abs/2312.08617 · Code: https://github.com/hkust-zhiyao/RTL-Coder
- **Fully open:** data + training + model weights.

---

## TL;DR (one breath)
A **small (7B), fully open** LLM that writes **Verilog** better than GPT-3.5 — enabled by an **automatically-generated 27k-sample instruction dataset**. Small enough to run locally (4-bit fits on a laptop), and everything (data + recipe + weights) is public.

## The problem it fixes
LLMs can write software code, but **Verilog/RTL** is scarce in their training data, so open models were weak. Commercial models (GPT-4) are closed, costly, and can't be fine-tuned or deployed privately (a concern for proprietary chip IP).

## Key idea — make the data, then fine-tune a small model
1. **Automated dataset generation:** use an LLM + a pipeline to synthesize **27k high-quality (instruction → Verilog)** training pairs with good diversity and correctness.
2. **Fine-tune a 7B model** on this data with a training method robust to the fact that many instructions have **multiple valid RTL answers**.

## How it works
- Generate instruction–code pairs and filter for quality/compileability.
- Fine-tune with a loss that handles **non-unique correct outputs**.
- Ship a model that runs cheaply (quantized 4-bit).

## Results (headline numbers)
- **Beats GPT-3.5** on Verilog generation benchmarks (VerilogEval, RTLLM).
- **7B, open, laptop-deployable** — a practical open baseline.

## Why it matters for your BTP
- If you touch **LLM-for-RTL**, this is your **open, reproducible base model + dataset**.
- The **automated data-generation** methodology is the reusable contribution (data scarcity is the core issue in this space).

## Limitations
- Still weaker than the very best closed models on hard designs.
- Correctness ≠ good PPA; generated RTL may synthesize poorly.

## Mini-glossary
- **RTL:** Register-Transfer Level — the Verilog/VHDL abstraction of hardware behavior.
- **Instruction tuning:** fine-tuning on (instruction, desired output) pairs.
- **Quantization (4-bit):** compressing model weights to run on modest hardware.
