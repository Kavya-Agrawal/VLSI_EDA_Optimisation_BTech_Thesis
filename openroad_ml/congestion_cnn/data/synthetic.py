"""Synthetic CircuitNet-style feature / label maps."""

from __future__ import annotations

import torch


def make_synthetic_maps(
    batch: int = 4,
    channels: int = 4,
    height: int = 32,
    width: int = 32,
    seed: int = 0,
) -> dict[str, torch.Tensor]:
    g = torch.Generator().manual_seed(seed)
    x = torch.rand(batch, channels, height, width, generator=g)
    # labels correlated with pin+density channels
    congestion = torch.sigmoid(2 * x[:, 0:1] + x[:, 1:2] - 1.0)
    ir_drop = torch.sigmoid(x[:, 2:3] + 0.5 * congestion)
    drc = (congestion > 0.7).float()
    return {
        "x": x,
        "congestion": congestion,
        "ir_drop": ir_drop,
        "drc": drc,
    }


class SyntheticMapDataset(torch.utils.data.Dataset):
    def __init__(self, n: int = 32, **kwargs):
        self.items = [make_synthetic_maps(batch=1, seed=i, **kwargs) for i in range(n)]

    def __len__(self) -> int:
        return len(self.items)

    def __getitem__(self, idx: int) -> dict[str, torch.Tensor]:
        item = self.items[idx]
        return {k: v.squeeze(0) if k != "x" and v.dim() == 4 else v.squeeze(0) for k, v in item.items()}
