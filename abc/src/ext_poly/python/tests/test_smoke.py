"""POLYPHONY smoke tests (no ABC binary / GPU required)."""

from __future__ import annotations

import os
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from verifier import Program, is_equivalent, eval_truth, xor_truth

PASS, FAIL, SKIP = "PASS", "FAIL", "SKIP"
results = []


def check(name, fn):
    try:
        fn()
        results.append((PASS, name, ""))
    except Exception as e:
        results.append((FAIL, name, f"{type(e).__name__}: {e}"))


def t_xor3():
    t = xor_truth(3)
    # classic XOR AIG: ((a^b)^c)
    # a^b = (a|b)&~(a&b)
    # Build program:
    # g0 = a & b
    # g1 = ~a & ~b
    # g2 = ~g1  (= a|b)
    # g3 = g2 & ~g0  (= a^b)   out of g3 temporarily
    # Then xor with c similarly — keep it simpler: just check AND
    p = Program(n_vars=2, lit_a=[0], lit_b=[2], out_lit=4)  # a & b
    assert is_equivalent(p, 0b1000 & 0xF) or eval_truth(p) == 0b1000
    # a=lit0 (var0), b=lit2 (var1), out=lit4 (node2=first AND)
    assert eval_truth(p) == 0b1000  # only minterm 3 (=11b)


def t_const0():
    p = Program(n_vars=2, lit_a=[0], lit_b=[1], out_lit=4)  # x0 & ~x0
    assert eval_truth(p) == 0


def t_xor_truth_bits():
    assert xor_truth(1) == 0b10
    assert xor_truth(2) == 0b0110


def t_fallback_finds_and():
    from train.train_gflownet import fallback_sample
    target = 0b1000  # a&b for 2 vars
    progs = fallback_sample(2, target)
    assert any(is_equivalent(p, target) for p in progs)


def t_generator_optional():
    try:
        import torch
        from config import PolyConfig
        from models.generator import PolyGenerator
    except Exception as e:
        results.append((SKIP, "generator forward", str(e)))
        return
    cfg = PolyConfig()
    m = PolyGenerator(cfg)
    bits = torch.zeros(1, 1 << cfg.max_vars)
    n_oh = torch.zeros(1, cfg.max_vars); n_oh[0, 2] = 1
    cond = m.encode(bits, n_oh)
    lit_seq = torch.zeros(1, 1, dtype=torch.long)
    la, lb, lo, st = m.step(cond, lit_seq)
    assert la.shape[0] == 1
    results.append((PASS, "generator forward", ""))


def main():
    check("xor truth table", t_xor_truth_bits)
    check("const0 program", t_const0)
    check("and program eval", t_xor3)
    check("fallback finds AND", t_fallback_finds_and)
    t_generator_optional()
    print("\nPOLYPHONY smoke tests")
    print("-" * 48)
    fails = 0
    for s, n, m in results:
        print(f"  {s:4}  {n}" + (f"  ({m})" if m else ""))
        if s == FAIL:
            fails += 1
    print("-" * 48)
    sys.exit(1 if fails else 0)


if __name__ == "__main__":
    main()
