"""GFlowNet / supervised training scaffold for POLYPHONY.

No GPU required to import. Training loops are scaffolds: they run a few
fake steps if torch is present, otherwise print guidance.
"""

from __future__ import annotations

import argparse
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from config import PolyConfig
from verifier import Program, is_equivalent, xor_truth, eval_truth


def reward(prog: Program, target: int, seen_hashes: set) -> float:
    if not is_equivalent(prog, target):
        return 0.0
    size_pen = math_exp(-PolyConfig.alpha_size * prog.n_gates)
    h = (tuple(prog.lit_a), tuple(prog.lit_b), prog.out_lit)
    novelty = 1.0 + (PolyConfig.beta_novelty if h not in seen_hashes else 0.0)
    seen_hashes.add(h)
    return size_pen * novelty


def math_exp(x: float) -> float:
    import math
    return math.exp(x)


def fallback_sample(n_vars: int, target: int) -> list[Program]:
    """Tiny deterministic fallback diversity (mirrors C polySynth ideas)."""
    out: list[Program] = []

    def keep(p: Program):
        if is_equivalent(p, target):
            out.append(p)

    for v in range(n_vars):
        for c in (0, 1):
            keep(Program(n_vars=n_vars, out_lit=(v << 1) | c))

    for a in range(n_vars):
        for b in range(a + 1, n_vars):
            for ca in (0, 1):
                for cb in (0, 1):
                    la, lb = (a << 1) | ca, (b << 1) | cb
                    # AND
                    keep(Program(n_vars=n_vars, lit_a=[la], lit_b=[lb], out_lit=n_vars << 1))
                    # OR = ~(~a & ~b)
                    keep(Program(
                        n_vars=n_vars, lit_a=[la ^ 1], lit_b=[lb ^ 1],
                        out_lit=(n_vars << 1) | 1))
                    # XOR = (a|b) & ~(a&b) = ~g1 & ~g0 where g0=a&b, g1=~a&~b
                    g0, g1 = n_vars, n_vars + 1
                    keep(Program(
                        n_vars=n_vars,
                        lit_a=[la, la ^ 1, (g0 << 1) | 1],
                        lit_b=[lb, lb ^ 1, (g1 << 1) | 1],
                        out_lit=(n_vars + 2) << 1))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--n-vars", type=int, default=3)
    ap.add_argument("--steps", type=int, default=5)
    ap.add_argument("--mode", choices=["gflownet", "supervised", "demo"], default="demo")
    args = ap.parse_args()

    target = xor_truth(args.n_vars)
    print(f"[polyphony] n_vars={args.n_vars} target_xor=0x{target:x} mode={args.mode}")

    seen = set()
    progs = fallback_sample(args.n_vars, target)
    print(f"[polyphony] fallback found {len(progs)} verified equivalents")
    for i, p in enumerate(progs[:8]):
        r = reward(p, target, seen)
        print(f"  #{i} gates={p.n_gates} out={p.out_lit} R={r:.4f} tt=0x{eval_truth(p):x}")

    if args.mode == "demo":
        print("[polyphony] demo done (no torch required).")
        return

    try:
        import torch
        from models.generator import PolyGenerator
    except Exception as e:
        print(f"[polyphony] torch/model unavailable ({e}); scaffold only.")
        return

    cfg = PolyConfig()
    model = PolyGenerator(cfg)
    opt = torch.optim.Adam(model.parameters(), lr=cfg.lr)
    max_tt = 1 << cfg.max_vars
    for step in range(args.steps):
        bits = torch.zeros(1, max_tt)
        for i in range(1 << args.n_vars):
            bits[0, i] = float((target >> i) & 1)
        n_oh = torch.zeros(1, cfg.max_vars)
        n_oh[0, args.n_vars - 1] = 1.0
        cond = model.encode(bits, n_oh)
        # dummy sequence
        lit_seq = torch.zeros(1, 1, dtype=torch.long)
        la, lb, lo, st = model.step(cond, lit_seq)
        # trajectory-balance / CE scaffold: push stop toward 0, random target lit
        loss = st.pow(2).mean() + la.pow(2).mean() * 0.0
        opt.zero_grad()
        loss.backward()
        opt.step()
        print(f"  step {step} loss={float(loss):.6f}")
    print("[polyphony] scaffold training steps finished.")


if __name__ == "__main__":
    main()
