# ChipNeMo: Domain-Adapted LLMs for Chip Design

- **Authors:** Mingjie Liu, Teodor-Dumitru Ene, Robert Kirby, et al. (NVIDIA)
- **Venue / Year:** 2023 (arXiv)
- **PDF:** `ChipNeMo_2023.pdf`
- **Link:** https://arxiv.org/abs/2311.00176

---

## TL;DR (one breath)
NVIDIA's study on making LLMs genuinely useful **inside a chip company**. Rather than just prompting GPT-4, they **domain-adapt** open LLMs (LLaMA-2) to chip-design language and data, showing that a **smaller adapted model can match or beat a much larger general model** on real internal tasks — at lower cost.

## The problem it fixes
General LLMs don't know a company's **internal jargon, tools, and codebases**. Using huge closed models for every engineer is **expensive** and **leaks proprietary data**. Can domain adaptation give a cheaper, private, competitive model?

## Key idea — a recipe of domain adaptation techniques
Evaluate four techniques stacked together:
1. **Custom tokenizers** for hardware/EDA vocabulary.
2. **Domain-Adaptive Pre-Training (DAPT):** continue pre-training on chip-design text/code.
3. **Domain-specific instruction tuning (SFT).**
4. **Domain-adapted RAG** (Retrieval-Augmented Generation) to ground answers in internal docs.

## Three target applications
- **Engineering assistant chatbot** (answer design questions).
- **EDA script generation** (write tool scripts / Tcl).
- **Bug summarization and analysis.**

## Results (headline numbers)
- A **13B ChipNeMo** model **matches or beats LLaMA-2-70B** on these chip tasks — i.e., **domain adaptation beats raw size**.
- **RAG** substantially improves grounded correctness.

## Why it matters for your BTP
- The **blueprint for domain-adapting an open LLM** to EDA — directly reusable if you build an EDA assistant / script generator.
- Shows **DAPT + RAG** as the high-leverage moves (not just fine-tuning).

## Limitations
- Uses NVIDIA's **internal data** (not fully reproducible).
- Still needs careful evaluation; not a magic bullet for hard design tasks.

## Mini-glossary
- **DAPT:** Domain-Adaptive Pre-Training — extra pre-training on in-domain data.
- **SFT:** Supervised Fine-Tuning on instruction data.
- **RAG:** Retrieval-Augmented Generation — fetch relevant docs and feed them to the LLM.
- **Tokenizer:** splits text into tokens; a domain tokenizer handles jargon better.
