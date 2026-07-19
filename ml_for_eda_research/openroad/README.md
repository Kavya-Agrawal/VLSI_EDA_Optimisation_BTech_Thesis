# OpenROAD — ML / RL / DL Research Landscape for BTP

Deep survey of where machine learning can be applied inside / on top of
**OpenROAD** + **OpenROAD-flow-scripts (ORFS)** + **CircuitOps** + **OpenSTA**.

**Branch:** `docs/openroad-ml-landscape`  
**Companion model branches:**
| Branch | Focus |
|--------|--------|
| `feature/openroad-timing-gnn` | GNN pre-route / net-delay / endpoint-slack prediction |
| `feature/openroad-rl-gatesize` | RL agent for gate sizing with OpenSTA rewards |
| `feature/openroad-congestion-cnn` | CNN/UNet congestion + IR-drop heatmap models |

---

## 1. What OpenROAD is (mental model)

```
RTL / gate netlist
        │
        ▼
   Yosys (synthesis)          ← often outside OpenROAD binary
        │
        ▼
┌──────────────────────────────────────────────────────────┐
│ OpenROAD application                                      │
│  OpenDB  = design database (instances, nets, geometry)    │
│  OpenSTA = static timing analysis engine                  │
│  Tools: floorplan, place (RePlAce/Triton*), CTS,          │
│         global/detail route (FastRoute/TritonRoute),      │
│         optimize (gate size, buffer, repair), tapcell…    │
│  APIs: Tcl + **Python** (import openroad; live DB access) │
└──────────────────────────────────────────────────────────┘
        │
        ▼
   ORFS = Makefile/Tcl wrappers + PDKs (nangate45, asap7, sky130…)
        │
        ▼
   GDS / DEF / SPEF / metrics (METRICS2.1)
```

**Why ML fits here:** almost every physical-design stage uses **heuristics** on
NP-hard problems (placement, routing, gate sizing, buffering). OpenROAD’s
**Python API** lets you run an ML/RL loop *inside* the same process as OpenDB +
OpenSTA — no Tcl↔file I/O ping-pong (ASP-DAC’24 tutorial / VTS’24 paper).

---

## 2. Core open-source repos to clone

| Repo | Role | Clone |
|------|------|-------|
| [The-OpenROAD-Project/OpenROAD](https://github.com/The-OpenROAD-Project/OpenROAD) | Main app (place/route/CTS/opt + Python) | `git clone --recursive` |
| [OpenROAD-flow-scripts](https://github.com/The-OpenROAD-Project/OpenROAD-flow-scripts) | RTL→GDS flow + **AutoTuner** | |
| [NVlabs/CircuitOps](https://github.com/NVlabs/CircuitOps) | IR tables + LPG for ML datasets | |
| [ASU-VDA-Lab/ASP-DAC24-Tutorial](https://github.com/ASU-VDA-Lab/ASP-DAC24-Tutorial) | Official ML demos (IR-drop CNN, RL sizing) | |
| [ASU-VDA-Lab/2024_ICCAD_Contest_Gate_Sizing_Benchmark](https://github.com/ASU-VDA-Lab/2024_ICCAD_Contest_Gate_Sizing_Benchmark) | Gate-sizing contest data + OpenROAD scripts | |
| [circuitnet/CircuitNet](https://github.com/circuitnet/CircuitNet) | Congestion / DRC / IR / net-delay dataset | |
| [NVlabs/AutoDMP](https://github.com/NVlabs/AutoDMP) | Bayesian macro-placement on DREAMPlace | |
| [ABKGroup/DG-RePlAce-AutoDMP](https://github.com/ABKGroup/DG-RePlAce-AutoDMP) | AutoDMP-style tuner for OpenROAD GPU placer | |
| [ieee-ceda-datc/datc-rdf-flow-tuner](https://github.com/ieee-ceda-datc/datc-rdf-flow-tuner) | Generic ORFS AutoTuner / METRICS2.1 | |

---

## 3. OpenROAD stages × ML opportunity map

Legend: 🔴 crowded · 🟠 partly explored · 🟢 open / high novelty for BTP

### 3.1 Flow-level parameter tuning (AutoTuner)  🔴
- **Problem:** ORFS has dozens of knobs (density, padding, CTS, repair…). Manual
  tuning is expert-heavy; search space is combinatorial.
- **Existing:** ORFS `tools/AutoTuner` — Ray Tune with HyperOpt, Optuna, PBT,
  Nevergrad, AxSearch; METRICS2.1 PPA rewards.
- **Still open 🟠:** learned *warm-start* of search from circuit features (GNN
  encodes netlist → prior over knobs); multi-fidelity / early-stop predictors.

### 3.2 Macro / standard-cell placement  🔴/🟠
- **OpenROAD tools:** RePlAce / TritonPart / detailed placer; GPU DG-RePlAce.
- **Existing ML:** AlphaChip, MaskPlace, ChiPFormer, ChipDiffusion, AutoDMP,
  MacroRegulator (see your `macroPlace/` + placement papers).
- **OpenROAD-specific 🟢:** learned density/penalty schedules *inside* RePlAce
  iterations; RL refine of ORFS floorplan macros with real ORFS PPA reward
  (not HPWL-only).

### 3.3 Timing prediction (pre-route / cross-stage)  🟠 → **our timing-gnn branch**
- **Problem:** STA after routing is slow/expensive; early stages use optimistic
  wire models → metric mismatch.
- **Existing:** CircuitNet net-delay GNNs; TimingGCN / “timing engine inspired
  GNN” (DAC’22); GR↔DR timing consistency ML (TODAES’23).
- **Open 🟢:** OpenSTA-in-the-loop **calibration** of predicted net delays;
  multi-corner multi-mode heads; uncertainty-aware slack for ECO prioritization.

### 3.4 Gate sizing / Vt / buffering (opt)  🟠 → **our rl-gatesize branch**
- **Problem:** discrete library sizing under TNS/WNS/power is combinatorial;
  OpenROAD `repair_timing` / sizing is heuristic.
- **Existing:** RL-Sizer (DAC’21); ASP-DAC’24 OpenROAD RL demo; ICCAD’24
  Contest C (gate sizing) with CircuitOps + OpenROAD Python; IR-aware ECO RL
  (MLCAD’24).
- **Open 🟢:** *physically-aware* multi-action agent (size + buffer + pin-swap)
  matching ReSynthAI / MLCAD’25 contest framing; GNN policy with OpenSTA
  incremental reward.

### 3.5 Congestion / routability / DRC prediction  🟠 → **our congestion-cnn branch**
- **Problem:** detailed routing + DRC is the long pole; early prediction guides
  placement density.
- **Existing:** RouteNet, CircuitNet congestion/DRC CNNs, LEAP-style filters,
  PGR-DRC unsupervised (2025), AiDRC.
- **Open 🟢:** OpenROAD FastRoute overflow → learnable density adjustment
  feedback into place; multi-task congestion+IR+power UNet trained on ORFS runs.

### 3.6 IR drop / power integrity  🟠
- **Existing:** ICCAD’23 Problem C style image IR-drop; ASP-DAC’24 UNet demo
  on OpenROAD power maps.
- **Open 🟢:** joint IR+timing ECO; physics-informed nets.

### 3.7 Clock tree synthesis (CTS)  🟢
- **Problem:** clock skew/power/latency tradeoffs; mostly heuristic tree builders
  (TritonCTS).
- **Open 🟢:** almost no mature ML-in-OpenROAD CTS work; GNN sink clustering /
  topology policy is a strong novelty angle.

### 3.8 Global / detailed routing  🟠
- **Tools:** FastRoute, TritonRoute.
- **Existing:** Dr.Guide (MLCAD’25), PRNet, DeepRL global routing (older).
- **Open 🟢:** learned route-guide generation plugged into TritonRoute via
  OpenROAD APIs; RL net ordering for detailed route.

### 3.9 Physically-aware logic resynthesis / ECO  🟢 (hot 2025)
- **Contests:** MLCAD’25 ReSynthAI — post-floorplan netlist transforms evaluated
  with OpenROAD place+GR+timing; CircuitOps IRs provided.
- **Open 🟢:** excellent BTP: RL/GNN over {resize, buffer, swap, rewrite} with
  OpenROAD PPA reward — sits between your ABC SYNAPSE/POLYPHONY work and PD.

### 3.10 LLM agents for OpenROAD Tcl/Python flows  🟢
- **Existing:** ChipNeMo, ChatEDA, EDA Copilot ideas.
- **Open 🟢:** agent that writes ORFS config.mk / repair scripts, grounded on
  METRICS2.1 logs (tool-use RL).

---

## 4. Infrastructure patterns (how to integrate ML)

### Pattern A — Offline dataset (CircuitOps / CircuitNet)
1. Run ORFS or OpenROAD Tcl/Python → dump IR tables / heatmaps / graphs.  
2. Train PyTorch models offline.  
3. Inference can stay offline or be called from Python.

### Pattern B — Online in-tool loop (preferred for RL)
```python
# Conceptual (requires built OpenROAD with Python)
from openroad import Tech, Design
# ... load LEF/DEF/LIB/SDC ...
# state = extract_gnn_features(design)
# action = agent.act(state)          # e.g. swapMaster(inst, new_cell)
# design.getSta().updateTiming()     # incremental OpenSTA
# reward = compute_tns_power(design)
```
ASP-DAC’24 Demo2 is the reference for this pattern.

### Pattern C — AutoTuner / Ray outer loop
Wrap entire ORFS make flow; optimize PPA metrics. Good for flow knobs, not for
per-instance micro-actions.

---

## 5. Recommended BTP angles (ranked)

1. **RL physically-aware gate sizing / ECO** on ICCAD’24 Contest C + OpenROAD
   Python (clear baseline, official scripts, metrics).  
2. **Timing GNN calibrated to OpenSTA** for pre-route slack → guide repair.  
3. **Congestion CNN → density feedback** into OpenROAD placement.  
4. **ReSynthAI-style multi-op agent** (2025 contest direction).  
5. **CTS topology learning** (highest novelty, harder eval).

---

## 6. Papers & tutorials to read first

| Paper / tutorial | Why |
|------------------|-----|
| OpenROAD + CircuitOps (VTS’24 / ICCAD’23 CircuitOps) | Infrastructure bible |
| ASP-DAC’24 Tutorial (ASU-VDA-Lab) | Runnable IR-drop + RL sizing demos |
| RL-Sizer (DAC’21) | Classic RL gate sizing |
| ICCAD’24 Contest C writeups / benchmark repo | Gate sizing data |
| CircuitNet TCAD’23 | Congestion/IR/timing dataset |
| TODAES’23 GR–DR timing consistency | Cross-stage timing ML |
| DATC RDF-2025 invited | ReSynthAI, DALI-PD, roadmap |
| AutoDMP (ISPD’23) | Bayesian placement (ties to your macro work) |

PDFs for many of these already live under `ml_for_eda_research/papers/`.

---

## 7. Local workspace layout (this repo)

```
ml_for_eda_research/openroad/     ← this landscape (docs branch)
openroad_ml/                      ← model code (feature branches)
  timing_gnn/
  rl_gatesize/
  congestion_cnn/
```

OpenROAD itself should be cloned separately (large):  
`git clone --recursive https://github.com/The-OpenROAD-Project/OpenROAD.git`
