"""Export a dummy POLYPHONY generator to ONNX (smoke path)."""

from __future__ import annotations

import argparse
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", default="polyphony.onnx")
    ap.add_argument("--dummy", action="store_true")
    args = ap.parse_args()
    try:
        import torch
        import torch.nn as nn
        from config import PolyConfig
        from models.generator import PolyGenerator
    except Exception as e:
        print(f"[polyphony] cannot export ({e})")
        return

    cfg = PolyConfig()
    model = PolyGenerator(cfg)
    model.eval()

    class Wrap(nn.Module):
        def __init__(self):
            super().__init__()
            self.m = model

        def forward(self, truth_bits, n_vars_oh, lit_seq):
            cond = self.m.encode(truth_bits, n_vars_oh)
            la, lb, lo, st = self.m.step(cond, lit_seq)
            return la, lb, lo, st

    w = Wrap()
    max_tt = 1 << cfg.max_vars
    truth = torch.zeros(1, max_tt)
    n_oh = torch.zeros(1, cfg.max_vars); n_oh[0, 2] = 1
    lit_seq = torch.zeros(1, 1, dtype=torch.long)
    torch.onnx.export(
        w, (truth, n_oh, lit_seq), args.out,
        input_names=["truth_bits", "n_vars_oh", "lit_seq"],
        output_names=["logits_a", "logits_b", "logits_out", "stop"],
        opset_version=17,
    )
    print(f"[polyphony] exported {args.out}")


if __name__ == "__main__":
    main()
