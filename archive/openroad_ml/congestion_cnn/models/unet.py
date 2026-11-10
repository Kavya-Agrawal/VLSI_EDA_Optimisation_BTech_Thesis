"""UNet backbone + multi-task heads for congestion / IR / DRC maps."""

from __future__ import annotations

from dataclasses import dataclass

import torch
import torch.nn as nn
import torch.nn.functional as F


@dataclass
class UNetConfig:
    in_ch: int = 4
    base: int = 32
    out_tasks: tuple[str, ...] = ("congestion", "ir_drop", "drc")


class ConvBlock(nn.Module):
    def __init__(self, cin: int, cout: int):
        super().__init__()
        self.net = nn.Sequential(
            nn.Conv2d(cin, cout, 3, padding=1),
            nn.BatchNorm2d(cout),
            nn.ReLU(inplace=True),
            nn.Conv2d(cout, cout, 3, padding=1),
            nn.BatchNorm2d(cout),
            nn.ReLU(inplace=True),
        )

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        return self.net(x)


class CongestionUNet(nn.Module):
    def __init__(self, cfg: UNetConfig | None = None):
        super().__init__()
        self.cfg = cfg or UNetConfig()
        b = self.cfg.base
        c = self.cfg.in_ch
        self.enc1 = ConvBlock(c, b)
        self.enc2 = ConvBlock(b, b * 2)
        self.enc3 = ConvBlock(b * 2, b * 4)
        self.pool = nn.MaxPool2d(2)
        self.bottleneck = ConvBlock(b * 4, b * 8)
        self.up3 = nn.ConvTranspose2d(b * 8, b * 4, 2, stride=2)
        self.dec3 = ConvBlock(b * 8, b * 4)
        self.up2 = nn.ConvTranspose2d(b * 4, b * 2, 2, stride=2)
        self.dec2 = ConvBlock(b * 4, b * 2)
        self.up1 = nn.ConvTranspose2d(b * 2, b, 2, stride=2)
        self.dec1 = ConvBlock(b * 2, b)
        self.heads = nn.ModuleDict(
            {name: nn.Conv2d(b, 1, 1) for name in self.cfg.out_tasks}
        )

    def forward(self, x: torch.Tensor) -> dict[str, torch.Tensor]:
        e1 = self.enc1(x)
        e2 = self.enc2(self.pool(e1))
        e3 = self.enc3(self.pool(e2))
        z = self.bottleneck(self.pool(e3))
        d3 = self.dec3(torch.cat([self.up3(z), e3], dim=1))
        d2 = self.dec2(torch.cat([self.up2(d3), e2], dim=1))
        d1 = self.dec1(torch.cat([self.up1(d2), e1], dim=1))
        return {name: head(d1) for name, head in self.heads.items()}


def rudy_fallback(pin_map: torch.Tensor, density: torch.Tensor) -> torch.Tensor:
    """Cheap analytic congestion proxy without a trained net."""
    return F.avg_pool2d(pin_map + 0.5 * density, kernel_size=3, stride=1, padding=1)
