"""Train multi-task congestion UNet on synthetic maps."""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

import torch
import torch.nn.functional as F

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

from data.synthetic import make_synthetic_maps
from models.unet import CongestionUNet, UNetConfig


def main():
    p = argparse.ArgumentParser()
    p.add_argument("--epochs", type=int, default=3)
    p.add_argument("--lr", type=float, default=1e-3)
    p.add_argument("--synthetic", action="store_true", default=True)
    p.add_argument("--device", default="cpu")
    args = p.parse_args()

    device = torch.device(args.device)
    model = CongestionUNet(UNetConfig()).to(device)
    opt = torch.optim.Adam(model.parameters(), lr=args.lr)

    for ep in range(args.epochs):
        batch = make_synthetic_maps(batch=8, seed=ep)
        x = batch["x"].to(device)
        opt.zero_grad()
        pred = model(x)
        loss = (
            F.mse_loss(pred["congestion"], batch["congestion"].to(device))
            + F.mse_loss(pred["ir_drop"], batch["ir_drop"].to(device))
            + F.binary_cross_entropy_with_logits(pred["drc"], batch["drc"].to(device))
        )
        loss.backward()
        opt.step()
        print(f"epoch {ep+1}/{args.epochs}  loss={float(loss):.4f}")

    out = Path("checkpoints")
    out.mkdir(exist_ok=True)
    torch.save({"model": model.state_dict(), "cfg": model.cfg.__dict__}, out / "congestion_unet.pt")
    print(f"wrote {out / 'congestion_unet.pt'}")


if __name__ == "__main__":
    main()
