# Benchmarking Large Language Models for Automated Verilog RTL Code Generation (VeriGen / VGen)

- **Authors:** Shailja Thakur, Baleegh Ahmad, Zhenxing Fan, Hammond Pearce, Benjamin Tan, Ramesh Karri, Brendan Dolan-Gavitt, Siddharth Garg (NYU + Univ. Calgary)
- **Venue / Year:** **DATE 2023**
- **PDF:** `VeriGen_Benchmarking_DATE2023.pdf`
- **Link:** https://arxiv.org/abs/2212.11140 · Code: https://github.com/shailja-thakur/VGen

---

## TL;DR (one breath)
One of the **first** studies to fine-tune LLMs specifically on **Verilog** (scraped from GitHub + textbooks) and measure the result. Finding: fine-tuning makes open models much better at Verilog, and a fine-tuned **open CodeGen model can beat commercial Codex** on functional correctness.

## The problem (plain English)
LLMs were great at Python/C but **untested on Verilog**. Could they write **synthesizable, functionally-correct** hardware? Nobody had systematically checked, and there was no fine-tuned open model.

## Key idea — fine-tune on real Verilog, then test rigorously
1. **Collect Verilog** from GitHub repos and textbooks.
2. **Fine-tune** several pre-trained LLMs (e.g., CodeGen at various sizes) on it.
3. Build an **evaluation framework**: testbenches for **functional** correctness + a flow to check **syntax**, across problems of varying difficulty.

## Results (headline numbers)
- Fine-tuning improves **syntactic correctness** by ~**25.9%** overall.
- A fine-tuned **open CodeGen model outperforms commercial Codex** on functionality (~**6.5%** overall).
- Releases scripts + model checkpoints (VGen).

## Why it matters for your BTP
- The **origin point** of the LLM-for-Verilog line — read alongside VerilogEval (the benchmark) and RTLCoder (the stronger open model).
- Demonstrates that **domain fine-tuning + honest simulation-based eval** is the right methodology.

## Limitations
- Early models are weak by today's standards.
- Small problem set; correctness ≠ good hardware quality.

## Mini-glossary
- **Verilog:** the dominant hardware description language.
- **Synthesizable code:** RTL that tools can turn into real gates.
- **CodeGen / Codex:** code LLMs (open / OpenAI's, respectively).
- **Fine-tuning:** further training a pre-trained model on domain data.
