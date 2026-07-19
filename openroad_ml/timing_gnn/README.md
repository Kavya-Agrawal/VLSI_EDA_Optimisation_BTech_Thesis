# Timing / Slack GNN for OpenROAD

**Branch:** `feature/openroad-timing-gnn`

Predicts **net delay** and **endpoint slack** from a cell/net graph extracted
from OpenDB (or CircuitOps IR tables), so early PD stages can approximate
OpenSTA without a full route+SPEF loop.

## Idea
- Node features: cell type embedding, fanin/fanout, load estimate, placement
  coords (optional), liberty drive strength bucket.
- Edge features: net estimated length / capacitance proxy, pin capacitance.
- Message-passing GNN → heads for `net_delay`, `arrival`, `slack`.
- Train offline on CircuitNet / CircuitOps dumps; calibrate online against OpenSTA.

## Layout
```
openroad_ml/timing_gnn/
  README.md
  requirements.txt
  models/          # encoder + prediction heads
  data/            # graph builders + synthetic dataset
  train/           # training loop
  openroad_api/    # optional live OpenROAD hooks (stubs)
  tests/           # smoke tests (no GPU required)
```

## Quick start (no OpenROAD build needed)
```powershell
cd openroad_ml/timing_gnn
python -m pip install -r requirements.txt
python -m tests.smoke_test
python -m train.train --epochs 2 --synthetic
```

## OpenROAD integration (when built)
See `openroad_api/extract.py` — load Design, dump node/edge tensors, run
`TimingGNN.predict`, write predicted delays into a SPEF-like table or use
as repair prioritization scores.
