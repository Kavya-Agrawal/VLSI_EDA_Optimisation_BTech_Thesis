"""Smoke tests for congestion UNet."""

from __future__ import annotations

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))


def test_unet_forward():
    import torch
    from data.synthetic import make_synthetic_maps
    from models.unet import CongestionUNet, UNetConfig, rudy_fallback

    batch = make_synthetic_maps(batch=2, height=32, width=32, seed=3)
    model = CongestionUNet(UNetConfig())
    pred = model(batch["x"])
    assert pred["congestion"].shape == batch["congestion"].shape
    assert pred["ir_drop"].shape == batch["ir_drop"].shape
    fb = rudy_fallback(batch["x"][:, 0:1], batch["x"][:, 1:2])
    assert fb.shape[2:] == batch["x"].shape[2:]
    loss = torch.nn.functional.mse_loss(pred["congestion"], batch["congestion"])
    loss.backward()
    print("PASS test_unet_forward", float(loss.detach()))


def test_openroad_stub():
    from openroad_api.maps import dump_feature_maps, suggest_density_padding
    import torch

    d = dump_feature_maps(None)
    assert d["status"] == "stub"
    pad = suggest_density_padding(torch.ones(1, 1, 4, 4))
    assert 0.0 <= pad <= 0.2
    print("PASS test_openroad_stub", d, pad)


if __name__ == "__main__":
    test_unet_forward()
    test_openroad_stub()
    print("ALL PASS")
