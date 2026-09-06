# VerilogEval: Evaluating Large Language Models for Verilog Code Generation

- **Authors:** Mingjie Liu, Nathaniel Pinckney, Brucek Khailany, Haoxing Ren (NVIDIA)
- **Venue / Year:** **ICCAD 2023**
- **PDF:** `VerilogEval_ICCAD2023.pdf`
- **Link:** https://arxiv.org/abs/2309.07544 · Code: https://github.com/NVlabs/verilog-eval
- **The standard benchmark** for LLM Verilog generation.

---

## TL;DR (one breath)
The "HumanEval for hardware." A **standard benchmark of 156 Verilog problems** (from HDLBits) where an LLM's generated code is **automatically simulated against a golden solution** to check **functional correctness** — giving everyone a fair, reproducible way to compare models.

## The problem it fixes
Before this, "our LLM writes good Verilog" claims were **unmeasurable** — no shared benchmark, no automatic correctness check. Progress couldn't be compared.

## Key idea — automatic, simulation-based scoring
- **156 curated tasks**, from simple combinational circuits to complex **finite-state machines**.
- For each task, the LLM's output is **simulated** and its transient outputs compared to a **golden reference** → pass/fail.
- Report **pass@k** (probability at least one of k samples is correct), following software's HumanEval.

## Extra contribution
Shows that **supervised fine-tuning** with **LLM-generated synthetic problem–code pairs** improves a model's Verilog ability (a bootstrapping trick).

## Results
- Provides the **first widely-adopted functional benchmark** for Verilog LLMs.
- Reveals big gaps between models (and between hardware vs software coding ability).

## Why it matters for your BTP
- **Use it as your evaluation harness** for any LLM-for-RTL work — reviewers expect VerilogEval numbers.
- The synthetic-data bootstrapping idea complements **RTLCoder**'s data generation.

## Limitations
- HDLBits-style tasks are **relatively small**; may not reflect large real designs (later **VerilogEval v2** and RTLLM extend to spec-to-RTL).
- Functional correctness only — doesn't measure PPA/synthesizability quality.

## Mini-glossary
- **pass@k:** fraction of problems solved if you allow k attempts.
- **Golden solution:** the known-correct reference to compare against.
- **FSM:** Finite-State Machine — a common sequential-logic design.
- **Testbench:** simulation code that drives inputs and checks outputs.
