"""SYNAPSE task heads.

All heads consume node embeddings produced by the shared encoder. Keeping the
heads tiny is deliberate: the encoder runs once per circuit snapshot, then the
heads are evaluated many times in ABC's hot loops (see docs/DESIGN.md section 5).
"""

from __future__ import annotations

import torch
import torch.nn as nn


class PotentialHead(nn.Module):
    """Non-myopic node value: expected contribution to *final* QoR.

    Trained on Monte-Carlo returns (discounted final node reduction attributed
    back to each node touched during the recipe). This is the credit-assignment
    signal that lets the model see past ABC's one-step-greedy gain metric.
    """

    def __init__(self, cfg):
        super().__init__()
        self.net = nn.Sequential(
            nn.Linear(cfg.emb_dim, cfg.head_hidden), nn.ReLU(),
            nn.Linear(cfg.head_hidden, 1),
        )

    def forward(self, emb):
        return torch.sigmoid(self.net(emb)).squeeze(-1)


class RankHead(nn.Module):
    """Candidate scorer for divisor / cut / window ranking.

    Input is [root_emb || cand_emb || pair_feats]; output is a scalar score
    (higher = try first). Trained with a pairwise learning-to-rank loss on
    labels harvested from stock ABC (which candidate was accepted/best).
    """

    def __init__(self, cfg):
        super().__init__()
        self.net = nn.Sequential(
            nn.Linear(cfg.rank_input_dim(), cfg.head_hidden), nn.ReLU(),
            nn.Linear(cfg.head_hidden, cfg.head_hidden // 2), nn.ReLU(),
            nn.Linear(cfg.head_hidden // 2, 1),
        )

    def forward(self, root_emb, cand_emb, pair_feats):
        x = torch.cat([root_emb, cand_emb, pair_feats], dim=-1)
        return self.net(x).squeeze(-1)


class PolicyHead(nn.Module):
    """Per-node transform selector over {rewrite, refactor, resub, skip}.

    Used by the orchestration hook and as the actor in optional PPO fine-tuning.
    """

    ACTIONS = ("rewrite", "refactor", "resub", "skip")

    def __init__(self, cfg):
        super().__init__()
        self.net = nn.Sequential(
            nn.Linear(cfg.emb_dim, cfg.head_hidden), nn.ReLU(),
            nn.Linear(cfg.head_hidden, len(self.ACTIONS)),
        )

    def forward(self, emb):
        return self.net(emb)  # logits
