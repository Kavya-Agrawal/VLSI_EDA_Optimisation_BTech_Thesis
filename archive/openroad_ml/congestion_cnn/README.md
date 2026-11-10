# Congestion / IR-drop CNN-UNet for OpenROAD

**Branch:** `feature/openroad-congestion-cnn`

Image-to-image models that map early physical-design feature maps
(density, pin, RUDY, power) → **congestion**, **DRC hotspot**, or **IR-drop**
heatmaps — CircuitNet / ASP-DAC’24 UNet style.

## Idea
- Input tensor `B×C×H×W` (placement-aligned grid).
- Shared UNet backbone; task heads for congestion overflow, DRC count, IR max.
- Train on CircuitNet or ORFS-dumped maps; inference guides density padding /
  ECO prioritization back into OpenROAD.

## Layout
```
openroad_ml/congestion_cnn/
  README.md
  requirements.txt
  models/          # UNet + multi-task heads
  data/            # synthetic map generator + CircuitNet stub
  train/
  openroad_api/    # dump / inject density maps
  tests/
```

## Quick start
```powershell
cd openroad_ml/congestion_cnn
python -m pip install -r requirements.txt
python -m tests.smoke_test
python -m train.train --epochs 2 --synthetic
```
