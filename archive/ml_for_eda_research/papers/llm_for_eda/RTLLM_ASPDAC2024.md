# RTLLM: An Open-Source Benchmark for Design RTL Generation with Large Language Model

- **Authors:** Yao Lu, Shang Liu, Qijun Zhang, Zhiyao Xie (HKUST)
- **Venue / Year:** **ASP-DAC 2024**
- **PDF:** `RTLLM_ASPDAC2024.pdf`
- **Link:** https://arxiv.org/abs/2308.05345 · Code: https://github.com/hkust-zhiyao/RTLLM

---

## TL;DR (one breath)
A benchmark of **larger, more realistic design tasks** for LLM-generated RTL — going beyond tiny snippets to actual **design-scale** problems. It also introduces **"Self-Planning"**, a prompting trick where the LLM first drafts a plan, which noticeably improves generated-RTL quality.

## The problem it fixes
Early benchmarks (VeriGen, VerilogEval) use **small** problems. Real hardware modules are bigger and need **spec-to-design** reasoning. There was no open benchmark at that scale, and no easy way to measure **syntax + functionality + design quality** together.

## Key idea — a scaled-up, 3-axis benchmark + a prompting method
- **RTLLM benchmark:** 30 designs (later expanded) spanning arithmetic, control, memory, etc., each with a natural-language spec, a reference, and testbenches.
- Evaluate three things: **syntax** correctness, **functional** correctness, and **design quality**.
- **Self-Planning prompting:** ask the LLM to **plan the design in words first**, then write the Verilog → better results even without fine-tuning.

## Results
- Provides a **harder, more realistic** open benchmark than predecessors.
- **Self-Planning** measurably improves correctness of generated RTL.

## Why it matters for your BTP
- Use RTLLM (with VerilogEval) to evaluate LLM-for-RTL work at a **more realistic scale**.
- **Self-Planning** is a cheap, model-agnostic technique you can apply immediately.

## Limitations
- Still far from full SoC-scale designs.
- "Design quality" metrics are proxies, not full sign-off PPA.

## Mini-glossary
- **Spec-to-RTL:** generate hardware code from a natural-language specification.
- **Self-Planning:** prompt the model to outline a solution before coding it.
- **Testbench:** simulation harness that checks functional correctness.
