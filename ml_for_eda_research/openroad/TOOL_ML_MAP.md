# OpenROAD tool → heuristic → ML injection cheat sheet

| Stage | OpenROAD / ORFS component | Heuristic / NP-hard core | ML approach | Openness |
|-------|---------------------------|--------------------------|-------------|----------|
| Flow knobs | ORFS AutoTuner | Combinatorial parameter search | BO / PBT / HyperOpt (exists); GNN warm-start | 🟠 |
| Floorplan | `initialize_floorplan`, macro place | NP-hard packing | RL / diffusion / BO (crowded outside OR) | 🟠 |
| Global place | RePlAce / DG-RePlAce | Nonlinear density+WL | Learned force schedules; congestion-aware ML | 🟢 in-OR |
| Legalize / detail | OpenDP / Triton | Matching / local search | Imitation of legalizer moves | 🟢 |
| CTS | TritonCTS | Tree construction heuristics | GNN clustering / RL topology | 🟢 |
| Timing opt | `repair_timing`, sizing, buffer | Discrete sizing NP-hard | **RL + GNN + OpenSTA reward** | 🟠 |
| Global route | FastRoute | Maze / pattern route | Congestion predict → guide | 🟠 |
| Detail route | TritonRoute | NP-hard DRC-aware | Route guides (Dr.Guide); DRC CNN | 🟠 |
| STA | OpenSTA | Exact but expensive incremental | **GNN net/path delay surrogates** | 🟠 |
| Power / IR | PDN + analysis | PDE / grid solve | **UNet IR maps** | 🟠 |
| ECO / resynth | manual + contests | Multi-op combinatorial | Multi-action RL (ReSynthAI) | 🟢 |

## Python API hooks (names to look up in OpenROAD docs)
- Design DB: instances, nets, block, tech  
- `swapMaster` / liberty cell change → gate sizing action  
- OpenSTA: `updateTiming`, arrival/required/slack queries  
- Placement: instance location get/set  
- Metrics: TNS, WNS, area, power (via liberty + STA)

Exact symbol names vary by OpenROAD version — always check the version you build
and the ASP-DAC’24 tutorial scripts.
