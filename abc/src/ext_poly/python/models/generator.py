"""Conditional AIG program generator (encoder-decoder Transformer).

Encoder embeds a k-input truth table; decoder emits gate tokens then an
output literal. A feasibility mask blocks forward references so every
sample is a syntactically valid program; Poly_ProgIsEquivalent (C) or
python/verifier.py checks functional exactness.
"""

from __future__ import annotations

import math
from typing import Optional, Tuple

try:
    import torch
    import torch.nn as nn
    import torch.nn.functional as F
    _HAS_TORCH = True
except Exception:  # pragma: no cover
    _HAS_TORCH = False


def tt_to_bits(truth: int, n_vars: int):
    """Return float tensor [2^n_vars] of bits."""
    import torch
    n = 1 << n_vars
    bits = torch.zeros(n)
    for i in range(n):
        bits[i] = float((truth >> i) & 1)
    return bits


if _HAS_TORCH:

    class TruthEncoder(nn.Module):
        def __init__(self, cfg):
            super().__init__()
            self.max_tt = 1 << cfg.max_vars
            self.proj = nn.Sequential(
                nn.Linear(self.max_tt + cfg.max_vars, cfg.d_model),
                nn.ReLU(),
                nn.Linear(cfg.d_model, cfg.d_model),
            )

        def forward(self, truth_bits, n_vars_oh):
            # truth_bits: [B, 2^Kmax] zero-padded; n_vars_oh: [B, Kmax]
            x = torch.cat([truth_bits, n_vars_oh], dim=-1)
            return self.proj(x)  # [B, d]

    class GateDecoder(nn.Module):
        """Autoregressive decoder over a flattened action stream.

        At each step we predict two literal indices (for an AND) or, at the
        end, one output literal. For the prototype we use an MLP policy head
        over a fixed max program length (simpler than full Transformer decode
        and enough to train a GFlowNet / PPO scaffold).
        """

        def __init__(self, cfg):
            super().__init__()
            self.cfg = cfg
            max_nodes = cfg.max_vars + cfg.max_gates
            self.max_lits = 2 * max_nodes
            self.embed = nn.Embedding(self.max_lits + 1, cfg.d_model)  # +PAD
            self.rnn = nn.GRU(cfg.d_model, cfg.d_model, num_layers=2, batch_first=True)
            self.head_a = nn.Linear(cfg.d_model, self.max_lits)
            self.head_b = nn.Linear(cfg.d_model, self.max_lits)
            self.head_out = nn.Linear(cfg.d_model, self.max_lits)
            self.stop = nn.Linear(cfg.d_model, 1)  # P(stop / emit OUT)

        def forward(self, cond, lit_seq):
            """
            cond: [B, d] from encoder
            lit_seq: [B, T] previous literal tokens (pad=max_lits)
            returns logits_a, logits_b, logits_out, stop_logit  (all [B, ...])
            """
            emb = self.embed(lit_seq.clamp(0, self.max_lits))
            h0 = cond.unsqueeze(0).repeat(2, 1, 1)  # 2 layers
            out, _ = self.rnn(emb, h0)
            h = out[:, -1, :]
            return self.head_a(h), self.head_b(h), self.head_out(h), self.stop(h).squeeze(-1)

    class PolyGenerator(nn.Module):
        def __init__(self, cfg):
            super().__init__()
            self.cfg = cfg
            self.enc = TruthEncoder(cfg)
            self.dec = GateDecoder(cfg)

        def encode(self, truth_bits, n_vars_oh):
            return self.enc(truth_bits, n_vars_oh)

        def step(self, cond, lit_seq):
            return self.dec(cond, lit_seq)

else:  # pragma: no cover
    class PolyGenerator:  # type: ignore
        def __init__(self, *a, **k):
            raise ImportError("torch required for PolyGenerator")
