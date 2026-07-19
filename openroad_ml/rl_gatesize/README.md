# RL Gate Sizing for OpenROAD + OpenSTA

**Branch:** `feature/openroad-rl-gatesize`

Discrete library gate-sizing agent: pick instance → pick larger/smaller/Vt
cell → incremental OpenSTA reward (ΔTNS, ΔWNS, Δpower, Δarea).

Inspired by RL-Sizer (DAC’21), ASP-DAC’24 OpenROAD RL demo, and ICCAD’24
Contest C.

## Idea
- State: GNN over critical subgraph (timing path neighborhood) + global TNS/WNS.
- Action: `(instance_id, size_delta)` or categorical library cell among legal
  masters for that footprint.
- Reward: `α·ΔTNS + β·ΔWNS − γ·Δpower − δ·Δarea` (configurable).
- Env modes: `mock` (analytic STA surrogate, default) and `openroad` (live API).

## Layout
```
openroad_ml/rl_gatesize/
  README.md
  requirements.txt
  env/             # gym-like sizing environment
  models/          # GNN actor-critic
  train/           # PPO-style trainer
  openroad_api/    # swapMaster + STA hooks
  tests/
```

## Quick start
```powershell
cd openroad_ml/rl_gatesize
python -m pip install -r requirements.txt
python -m tests.smoke_test
python -m train.train_ppo --episodes 5 --mock
```
