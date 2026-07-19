"""Train TimingGNN on synthetic (default) or CircuitOps-style graphs."""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

import torch
import torch.nn.functional as F

# Allow `python -m train.train` from package root
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

from data.synthetic import SyntheticTimingDataset
from models.timing_gnn import TimingGNN, TimingGNNConfig


def train_one_epoch(model: TimingGNN, loader, opt, device) -> float:
    model.train()
    total = 0.0
    n = 0
    for batch in loader:
        x = batch["x"].to(device)
        ei = batch["edge_index"].to(device)
        ea = batch["edge_attr"].to(device)
        y_d = batch["net_delay"].to(device)
        y_s = batch["slack"].to(device)
        mask = batch["endpoint_mask"].to(device)
        opt.zero_grad()
        out = model(x, ei, ea, mask)
        loss = F.mse_loss(out["net_delay"], y_d) + F.mse_loss(out["slack"], y_s)
        loss.backward()
        opt.step()
        total += float(loss.item())
        n += 1
    return total / max(n, 1)


def main():
    p = argparse.ArgumentParser()
    p.add_argument("--epochs", type=int, default=5)
    p.add_argument("--lr", type=float, default=1e-3)
    p.add_argument("--synthetic", action="store_true", default=True)
    p.add_argument("--device", default="cpu")
    args = p.parse_args()

    device = torch.device(args.device)
    ds = SyntheticTimingDataset(n_graphs=16)
    # Single-graph batches (variable size graphs)
    loader = [(ds[i]) for i in range(len(ds))]
    model = TimingGNN(TimingGNNConfig()).to(device)
    opt = torch.optim.Adam(model.parameters(), lr=args.lr)

    for ep in range(args.epochs):
        loss = train_one_epoch(model, loader, opt, device)
        print(f"epoch {ep+1}/{args.epochs}  loss={loss:.4f}")

    out = Path("checkpoints")
    out.mkdir(exist_ok=True)
    torch.save({"model": model.state_dict(), "cfg": model.cfg.__dict__}, out / "timing_gnn.pt")
    print(f"wrote {out / 'timing_gnn.pt'}")


if __name__ == "__main__":
    main()
