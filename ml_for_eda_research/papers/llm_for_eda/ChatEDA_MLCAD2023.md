# ChatEDA: A Large Language Model Powered Autonomous Agent for EDA

- **Authors:** Haoyuan Wu, Zhuolun He, Xinyun Zhang, Xufeng Yao, Su Zheng, Haisheng Zheng, Bei Yu (CUHK + Shanghai AI Lab)
- **Venue / Year:** **MLCAD 2023**
- **PDF:** `ChatEDA_MLCAD2023.pdf`
- **Link:** https://arxiv.org/abs/2308.10204

---

## TL;DR (one breath)
An **LLM-powered agent** that lets you drive the whole **RTL-to-GDSII** flow with **plain English**. You say what you want; ChatEDA **plans the tasks, generates the tool scripts, and runs them** — using a fine-tuned model (AutoMage) that beats GPT-4 at this job.

## The problem (plain English)
Modern flows (OpenROAD, commercial tools) have **hundreds of commands and parameters**, driven by fiddly **Tcl scripts**. Writing and maintaining these scripts is tedious and error-prone, especially across multiple vendors' tools.

## Key idea — LLM as an autonomous "flow orchestrator"
ChatEDA separates **brain** from **hands**:
- **Brain:** an LLM (**AutoMage**, fine-tuned for EDA) that understands the request.
- **Hands:** the EDA tools that actually execute.
The agent does **task decomposition → script generation → task execution**, looping until the goal is met.

## How it works
1. User gives a natural-language requirement.
2. AutoMage **decomposes** it into ordered sub-tasks.
3. It **generates the scripts/API calls** for each tool step.
4. Tools execute; results feed back for the next step.

## Results
- Fine-tuned **AutoMage outperforms GPT-4** and other LLMs at EDA task planning + script generation.
- Handles diverse RTL-to-GDSII requests end-to-end.

## Why it matters for your BTP
- The reference design for an **"agentic" EDA assistant** — relevant if you want a tooling/automation contribution rather than a core-algorithm one.
- Pairs naturally with **OpenROAD/ORFS** (which this repo already points you toward).

## Limitations
- Reliability depends on the LLM's script correctness; complex flows still need human oversight.
- Bounded by the tools' APIs and the fine-tuning data.

## Mini-glossary
- **RTL-to-GDSII:** the full flow from Verilog to a manufacturable layout.
- **Agent:** an LLM that plans and takes actions (calls tools), not just chats.
- **Tcl:** the scripting language most EDA tools are controlled with.
