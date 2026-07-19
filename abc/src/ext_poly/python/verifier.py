"""Exact Python verifier mirroring polyTruth.c (k<=6)."""

from __future__ import annotations

from dataclasses import dataclass, field
from typing import List


@dataclass
class Program:
    n_vars: int
    lit_a: List[int] = field(default_factory=list)
    lit_b: List[int] = field(default_factory=list)
    out_lit: int = 0

    @property
    def n_gates(self) -> int:
        return len(self.lit_a)


_VAR_TT = [
    0xAAAAAAAAAAAAAAAA,
    0xCCCCCCCCCCCCCCCC,
    0xF0F0F0F0F0F0F0F0,
    0xFF00FF00FF00FF00,
    0xFFFF0000FFFF0000,
    0xFFFFFFFF00000000,
]


def _mask(n_vars: int) -> int:
    if n_vars >= 6:
        return (1 << 64) - 1
    return (1 << (1 << n_vars)) - 1


def lit_var(lit: int) -> int:
    return lit >> 1


def lit_compl(lit: int) -> int:
    return lit & 1


def eval_truth(prog: Program) -> int | None:
    n_vars, n_gates = prog.n_vars, prog.n_gates
    if not (1 <= n_vars <= 6) or n_gates > 32:
        return None
    node = list(_VAR_TT[:n_vars])
    for i in range(n_gates):
        a_lit, b_lit = prog.lit_a[i], prog.lit_b[i]
        av, bv = lit_var(a_lit), lit_var(b_lit)
        if av < 0 or av >= n_vars + i or bv < 0 or bv >= n_vars + i:
            return None
        a = node[av]
        b = node[bv]
        if lit_compl(a_lit):
            a = (~a) & ((1 << 64) - 1)
        if lit_compl(b_lit):
            b = (~b) & ((1 << 64) - 1)
        node.append(a & b)
    ov = lit_var(prog.out_lit)
    if ov < 0 or ov >= n_vars + n_gates:
        return None
    t = node[ov]
    if lit_compl(prog.out_lit):
        t = (~t) & ((1 << 64) - 1)
    return t & _mask(n_vars)


def is_equivalent(prog: Program, target: int) -> bool:
    got = eval_truth(prog)
    if got is None:
        return False
    return got == (target & _mask(prog.n_vars))


def xor_truth(n_vars: int) -> int:
    n = 1 << n_vars
    t = 0
    for m in range(n):
        bits = 0
        for v in range(n_vars):
            bits ^= (m >> v) & 1
        if bits:
            t |= 1 << m
    return t
