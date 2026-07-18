"""Train the non-myopic PotentialHead (and pretrain the shared encoder).

This is a SCAFFOLD: it wires up the full training loop but is intended to be
run on a GPU machine with real data. It does nothing destructive if run without
data (it just reports that no data was found).

Label generation (done on the ABC side, see docs/INTEGRATION.md):
  1. For each training circuit, run the full recipe (e.g. resyn2) and record,
     per node touched at step t, the discounted share of the *final* total node
     reduction (Monte-Carlo return with discount gamma). That return is the
     regression target -- the credit-assignment signal.
  2. Dump per-snapshot graphs via `ml_features` and the per-node returns.

Usage:
    python -m train.train_potential --graphs data/graphs --labels data/returns.npz
"""

from __future__ import annotations

import argparse
import os
import sys

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from config import SynapseConfig            # noqa: E402
from data.dataset import load_graph_dir     # noqa: E402


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--graphs", default="data/graphs")
    ap.add_argument("--labels", default="data/returns.npz")
    ap.add_argument("--encoder", default="aigconv")
    ap.add_argument("--epochs", type=int, default=50)
    ap.add_argument("--out", default="checkpoints/potential.pt")
    args = ap.parse_args()

    cfg = SynapseConfig(encoder=args.encoder, epochs=args.epochs)

    try:
        import torch
        from models.synapse import SynapseModel
    except Exception as e:  # pragma: no cover
        print(f"[synapse] torch not available ({e}); this is a scaffold.")
        return

    cfg.device = "cuda" if torch.cuda.is_available() else "cpu"
    if not os.path.isdir(args.graphs):
        print(f"[synapse] no graph dir at {args.graphs}; nothing to train.")
        print("          generate data first (see docs/INTEGRATION.md).")
        return

    graphs = load_graph_dir(args.graphs)
    print(f"[synapse] loaded {len(graphs)} graphs; device={cfg.device}")

    model = SynapseModel(cfg).to(cfg.device)
    opt = torch.optim.Adam(model.parameters(), lr=cfg.lr, weight_decay=cfg.weight_decay)

    labels = None
    if os.path.exists(args.labels):
        import numpy as np
        labels = dict(np.load(args.labels, allow_pickle=True))

    for epoch in range(cfg.epochs):
        model.train()
        total = 0.0
        for gi, (x, edge_index, edge_attr, id_map) in enumerate(graphs):
            x = x.to(cfg.device); edge_index = edge_index.to(cfg.device)
            edge_attr = edge_attr.to(cfg.device)
            emb = model.encode(x, edge_index, edge_attr)
            pred = model.potential(emb)
            if labels is not None and str(gi) in labels:
                import numpy as np
                tgt = torch.from_numpy(np.asarray(labels[str(gi)], dtype="float32")).to(cfg.device)
                loss = torch.nn.functional.mse_loss(pred[: tgt.shape[0]], tgt)
            else:
                # self-supervised warm-up: predict normalized MFFC proxy (feat 7)
                loss = torch.nn.functional.mse_loss(pred, x[:, 7])
            opt.zero_grad(); loss.backward(); opt.step()
            total += float(loss)
        print(f"epoch {epoch:03d}  loss={total / max(1, len(graphs)):.5f}")

    os.makedirs(os.path.dirname(args.out) or ".", exist_ok=True)
    torch.save({"model": model.state_dict(), "cfg": cfg.__dict__}, args.out)
    print(f"[synapse] saved {args.out}")


if __name__ == "__main__":
    main()
