# CircuitNet: An Open-Source Dataset for Machine Learning Applications in EDA

- **Authors:** Zhuomin Chai, Yuxiang Zhao, Yibo Lin, Wei W. Xing, et al. (Peking Univ. et al.)
- **Venue / Year:** **Science China Information Sciences / TCAD, 2022–2023**
- **PDF:** `CircuitNet_TCAD2023.pdf`
- **Link:** https://arxiv.org/abs/2208.01040 · Project: https://circuitnet.github.io
- **The go-to ML-EDA dataset.** ⭐ Lowest-barrier entry point for your BTP.

---

## TL;DR (one breath)
The **first large public dataset** built specifically for ML-for-EDA. It gives **20k+ ready-to-train samples** (as images *and* graphs) for predicting **routing congestion, DRC violations, and IR-drop** — so you can do pure PyTorch research **without running a full chip-design flow**.

## The problem it fixes
ML-for-EDA had a **data drought**: EDA data is proprietary, hard to generate, and contest datasets weren't ML-ready. Everyone used tiny private sets → no reproducibility, high barrier to entry.

## Key idea — turn EDA layouts into ML tensors
Run real commercial flows on open-source RISC-V / accelerator designs, then package the outputs as **standardized features + labels** for common prediction tasks. Two feature styles:
- **Image-like** (2D maps) → feed to **CNNs**.
- **Graph** (netlist) → feed to **GNNs**.

## What's in it
- **20k+ samples**, multiple technology nodes: **CircuitNet-N28 (28nm), N14 (14nm), N45/ISPD15**.
- Tasks: **congestion prediction, DRC-violation prediction, IR-drop prediction, net delay**.
- Validated by reproducing results from prior task-specific papers (RouteNet, etc.).

## Why it matters for your BTP
- README calls this the **lowest-barrier direction**: you get labeled tensors and can train models immediately.
- Perfect for a **cross-stage prediction** thesis (predict congestion/timing early), or to build a **fast learned reward** for your placer (README idea #3, "LaMPlace-style").

## Limitations
- Data comes from specific flows/PDKs — domain shift to other tools possible.
- Large download; realistic but still a curated subset of real design space.

## Mini-glossary
- **Congestion:** where too many wires want to go through one region (routing hotspots).
- **DRC:** Design Rule Check — geometry/spacing rules a layout must satisfy.
- **IR-drop:** voltage drop across the power grid; too much causes failures.
- **CNN / GNN:** convolutional (for images) / graph neural networks.
