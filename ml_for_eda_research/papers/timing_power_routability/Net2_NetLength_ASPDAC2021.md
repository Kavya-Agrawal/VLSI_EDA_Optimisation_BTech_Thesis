# Net2: A Graph Attention Network Method Customized for Pre-Placement Net Length Estimation

- **Authors:** Zhiyao Xie, Rongjian Liang, Xiaoqing Xu, Jiang Hu, Yixiao Duan, Yiran Chen (Duke, TAMU, ARM)
- **Venue / Year:** **ASP-DAC 2021**
- **PDF:** `Net2_NetLength_ASPDAC2021.pdf`
- **Link:** https://arxiv.org/abs/2011.13522

---

## TL;DR (one breath)
Wire (net) length drives timing and power, but you normally don't know it until **after placement**. Net2 uses a **customized Graph Attention Network** to **predict each net's length *before* placement**, so earlier stages (like synthesis) can optimize for it. A fast version is **>1000× faster than actually placing**.

## The problem (plain English)
- **Interconnect** (wires) dominates modern chip delay (>1/3 of clock period) and power (~1/2 of dynamic power).
- But you only learn real wire lengths **after cell placement** — too late to influence synthesis. Estimating individual **net length pre-placement** is hard.

## Key idea — predict net length from the netlist graph
Use a **Graph Attention Network (GAT)** with EDA-specific customizations to read the netlist and predict, for each net, how long it will end up. Two versions:
- **Net2a** (accuracy-oriented): highest accuracy.
- **Net2f** (fast): slightly less accurate but blazing fast.

## How it works
- Treat cells/nets as a graph; **attention** weights neighbors by relevance.
- Custom features + architecture tuned to identify **long nets** and **long critical paths** (the ones that matter for timing).

## Results (headline numbers)
- **Net2a: ~15% better accuracy** than prior works at finding long nets / long critical paths.
- **Net2f: >1000× faster** than running placement, while still beating previous estimators.

## Why it matters for your BTP
- Example of the **"cross-stage prediction"** theme: use ML to see the future (post-placement metrics) early.
- Techniques transfer to building a **fast proxy reward** (predict wirelength/timing cheaply) for placement/synthesis loops.

## Limitations
- Predicts a **proxy** (net length), not final routed timing.
- Accuracy depends on design similarity to training data.

## Mini-glossary
- **Net:** a wire connecting a set of pins (a hyperedge in the netlist).
- **Critical path:** the slowest timing path that sets the max clock speed.
- **GAT (Graph Attention Network):** a GNN that learns how much each neighbor matters.
