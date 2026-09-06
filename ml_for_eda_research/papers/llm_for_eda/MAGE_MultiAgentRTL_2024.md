# MAGE: A Multi-Agent Engine for Automated RTL Code Generation

- **Authors:** Yujie Zhao*, Hejia Zhang*, Hanxian Huang, Zhongming Yu, Jishen Zhao (UC San Diego)
- **Venue / Year:** 2024 (arXiv)
- **PDF:** `MAGE_MultiAgentRTL_2024.pdf`
- **Link:** https://arxiv.org/abs/2412.07822 · Code: https://github.com/stable-lab/MAGE-A-Multi-Agent-Engine-for-Automated-RTL-Code-Generation

---

## TL;DR (one breath)
Instead of asking **one** LLM to do everything, MAGE uses a **team of specialized LLM agents** (coder, testbench writer, judge, debugger) that collaborate like a real hardware team. This multi-agent workflow hits **95.7%** correctness on VerilogEval-Human v2 — **+23.3%** over a single Claude-3.5-Sonnet.

## The problem it fixes
A single LLM agent must juggle **many roles** (write RTL, write tests, verify, debug) and switch between languages/domains — and it does each poorly. Single-agent RTL correctness is low even on simple tasks.

## Key idea — specialized agents + smart sampling + state checkpoints
Four agent types working in a recursive loop:
1. **RTL generation agent** — writes the Verilog.
2. **Testbench generation agent** — writes tests.
3. **Judge agent** — scores candidates.
4. **Debug agent** — fixes errors from precise feedback.

Two novel tricks:
- **High-temperature candidate sampling + debugging:** generate many diverse candidates (high temperature increases the chance a great one exists), then score by simulation.
- **Verilog-state checkpoint checking:** compare the design's internal state at checkpoints to catch **functional** errors early and give **targeted** fix feedback.

## Results (headline numbers)
- **95.7%** syntactic + functional correctness on **VerilogEval-Human v2**.
- **+23.3%** over state-of-the-art Claude-3.5-Sonnet.
- First **open-source** multi-agent engine for Verilog RTL.

## Why it matters for your BTP
- Shows the **multi-agent** frontier for LLM-for-RTL — a strong, modern approach to cite/build on.
- The **checkpoint-based verification feedback** idea is reusable for any code-gen-with-verification loop.
- *(Bonus paper: recovered while fixing a mislabeled download — it's a genuinely useful LLM-for-EDA reference.)*

## Limitations
- Multiple agents + many samples = **higher inference cost**.
- Still benchmarked on module-scale tasks, not full SoCs.

## Mini-glossary
- **Multi-agent system:** several LLMs with distinct roles cooperating.
- **Temperature:** randomness of LLM sampling; higher = more diverse outputs.
- **Checkpoint checking:** verifying internal signal states partway through simulation.
