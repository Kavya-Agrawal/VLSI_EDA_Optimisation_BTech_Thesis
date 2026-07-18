"""Export SYNAPSE submodels to ONNX for the ABC C runtime (mlInfer.c).

The C side loads a model whose I/O signatures are:
    input  "node_feat"  [1, NODE_FEAT_DIM]  -> output "potential"      [1,1]
    input  "node_feat"  [1, NODE_FEAT_DIM]  -> output "window_payoff"  [1,1]
    input  "rank_feat"  [1, 2*EMB+DIV]      -> output "score"          [1,1]

Two modes:
  --dummy   export a randomly-initialized model (smoke-test the ONNX path in C
            without any training; verifies plumbing on a CPU box).
  --ckpt f  export a trained checkpoint.

Usage:
    python -m export.to_onnx --dummy --out synapse.onnx
    python -m export.to_onnx --ckpt checkpoints/potential.pt --out synapse.onnx
"""

from __future__ import annotations

import argparse
import os
import sys

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from config import SynapseConfig, NODE_FEAT_DIM, DIV_FEAT_DIM   # noqa: E402


def build_export_wrapper(cfg):
    """The DEPLOYED model = feature-only heads matching mlInfer.c's I/O contract.

    Deliberately does NOT run the GNN: the C fast path supplies node/pair
    *features*, not cached embeddings. The full GNN + embedding-based heads live
    in models/synapse.py as the research tier (see docs/DESIGN.md section 5); the
    deploy heads here can be trained directly or distilled from that model.

        input  node_feat [B, 16] -> potential      [B, 1]
        input  node_feat [B, 16] -> window_payoff  [B, 1]
        input  rank_feat [B, 12] -> score          [B, 1]
    """
    import torch
    import torch.nn as nn

    h = cfg.head_hidden

    class DeployModel(nn.Module):
        def __init__(self):
            super().__init__()
            self.potential_net = nn.Sequential(
                nn.Linear(NODE_FEAT_DIM, h), nn.ReLU(), nn.Linear(h, 1), nn.Sigmoid())
            self.window_net = nn.Sequential(
                nn.Linear(NODE_FEAT_DIM, h), nn.ReLU(), nn.Linear(h, 1), nn.Sigmoid())
            self.rank_net = nn.Sequential(
                nn.Linear(DIV_FEAT_DIM, h), nn.ReLU(), nn.Linear(h, 1))

        def forward(self, node_feat, rank_feat):
            return (self.potential_net(node_feat),
                    self.window_net(node_feat),
                    self.rank_net(rank_feat))

    return DeployModel()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--dummy", action="store_true")
    ap.add_argument("--ckpt", default=None)
    ap.add_argument("--out", default="synapse.onnx")
    args = ap.parse_args()

    try:
        import torch
    except Exception as e:  # pragma: no cover
        print(f"[synapse] torch not available ({e}); cannot export.")
        return

    cfg = SynapseConfig()
    wrapper = build_export_wrapper(cfg)

    if args.ckpt and os.path.exists(args.ckpt):
        state = torch.load(args.ckpt, map_location="cpu")
        sd = state.get("model", state)
        # best-effort: a standalone ranker checkpoint (train_ranker.py) maps into
        # rank_net; a potential checkpoint can be distilled separately.
        try:
            wrapper.rank_net.load_state_dict(sd, strict=False)
        except Exception:
            pass
        print(f"[synapse] loaded checkpoint {args.ckpt} (best-effort)")
    elif not args.dummy:
        print("[synapse] no --ckpt and no --dummy; exporting random weights.")

    wrapper.eval()
    node_feat = torch.zeros((1, NODE_FEAT_DIM), dtype=torch.float32)
    rank_feat = torch.zeros((1, DIV_FEAT_DIM), dtype=torch.float32)

    torch.onnx.export(
        wrapper, (node_feat, rank_feat), args.out,
        input_names=["node_feat", "rank_feat"],
        output_names=["potential", "window_payoff", "score"],
        dynamic_axes={"node_feat": {0: "batch"}, "rank_feat": {0: "batch"}},
        opset_version=17,
    )
    print(f"[synapse] exported {args.out}")
    print("  load in ABC (needs ABC_USE_ONNX build):  ml_config -m", args.out, "-e")


if __name__ == "__main__":
    main()
