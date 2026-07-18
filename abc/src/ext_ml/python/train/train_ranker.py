"""Train the RankHead for resub-divisor / cut / window candidate ordering.

SCAFFOLD (run on GPU with data). Uses a pairwise learning-to-rank objective on
decision CSVs collected from ABC via `ml_config -c data.csv`. Each accepted /
best candidate should score above the rejected ones for the same decision.

Usage:
    python -m train.train_ranker --csv data/resub_divs.csv --task 1
"""

from __future__ import annotations

import argparse
import os
import sys

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from config import SynapseConfig, DIV_FEAT_DIM   # noqa: E402
from data.dataset import DecisionCSV             # noqa: E402


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--csv", default="data/resub_divs.csv")
    ap.add_argument("--task", type=int, default=1)
    ap.add_argument("--epochs", type=int, default=30)
    ap.add_argument("--out", default="checkpoints/ranker.pt")
    args = ap.parse_args()

    cfg = SynapseConfig(epochs=args.epochs)

    try:
        import torch
        import torch.nn as nn
    except Exception as e:  # pragma: no cover
        print(f"[synapse] torch not available ({e}); scaffold only.")
        return

    if not os.path.exists(args.csv):
        print(f"[synapse] no CSV at {args.csv}; collect data first "
              f"(ml_config -c {args.csv}). Scaffold only.")
        return

    ds = DecisionCSV(args.csv, task=args.task)
    print(f"[synapse] {len(ds)} candidate rows for task {args.task}")

    # A standalone pair-feature ranker (no embeddings) matching the fast path
    # in mlInfer.c. Once the encoder is trained, swap this for the full RankHead.
    net = nn.Sequential(
        nn.Linear(DIV_FEAT_DIM, cfg.head_hidden), nn.ReLU(),
        nn.Linear(cfg.head_hidden, 1),
    )
    opt = torch.optim.Adam(net.parameters(), lr=cfg.lr)

    feats = torch.stack([ds[i][2] for i in range(len(ds))]) if len(ds) else torch.zeros((0, DIV_FEAT_DIM))
    labels = torch.stack([ds[i][1] for i in range(len(ds))]) if len(ds) else torch.zeros((0,))

    for epoch in range(cfg.epochs):
        net.train()
        scores = net(feats).squeeze(-1)
        # pairwise: sample positive (label=1) vs negative (label=0) pairs
        pos = (labels > 0.5).nonzero(as_tuple=True)[0]
        neg = (labels <= 0.5).nonzero(as_tuple=True)[0]
        if len(pos) == 0 or len(neg) == 0:
            print("[synapse] need both accepted and rejected rows; check labels.")
            break
        k = min(len(pos), len(neg))
        loss = nn.functional.margin_ranking_loss(
            scores[pos[:k]], scores[neg[:k]],
            torch.ones(k), margin=0.5)
        opt.zero_grad(); loss.backward(); opt.step()
        print(f"epoch {epoch:03d}  rank_loss={float(loss):.5f}")

    os.makedirs(os.path.dirname(args.out) or ".", exist_ok=True)
    torch.save(net.state_dict(), args.out)
    print(f"[synapse] saved {args.out}")


if __name__ == "__main__":
    main()
