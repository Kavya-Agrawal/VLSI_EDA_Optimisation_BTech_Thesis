# Branch map — OpenROAD ML work

```
master
 ├── docs/openroad-ml-landscape          ← research docs only (this branch family)
 ├── feature/openroad-timing-gnn          ← timing / slack GNN models + trainers
 ├── feature/openroad-rl-gatesize         ← RL gate-sizing gym + GNN policy
 ├── feature/openroad-congestion-cnn      ← congestion / IR-drop CNN-UNet
 ├── feature/synapse-ml-abc               ← (prior) ABC SYNAPSE
 └── feature/genesis-neural-synthesis    ← (prior) ABC POLYPHONY
```

## Naming convention
- `docs/...` — documentation / surveys, no experimental code required  
- `feature/openroad-<topic>` — one ML idea per branch, self-contained under `openroad_ml/<topic>/`

## How to switch
```powershell
git checkout docs/openroad-ml-landscape
git checkout feature/openroad-timing-gnn
git checkout feature/openroad-rl-gatesize
git checkout feature/openroad-congestion-cnn
```
