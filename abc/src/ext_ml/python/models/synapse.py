"""SYNAPSE full model = shared encoder + multi-task heads.

The whole model trains jointly (shared encoder), but at deployment time we export
*small* submodels (the heads plus, optionally, a frozen embedding) so the C
runtime never runs the full GNN in a hot loop. See docs/DESIGN.md section 5.
"""

from __future__ import annotations

import torch
import torch.nn as nn

from .encoder import build_encoder
from .heads import PotentialHead, RankHead, PolicyHead


class SynapseModel(nn.Module):
    def __init__(self, cfg):
        super().__init__()
        self.cfg = cfg
        self.encoder = build_encoder(cfg)
        self.potential = PotentialHead(cfg)
        self.rank = RankHead(cfg)
        self.policy = PolicyHead(cfg)

    def encode(self, x, edge_index, edge_attr):
        return self.encoder(x, edge_index, edge_attr)

    def forward(self, batch):
        """batch is a torch_geometric-style object with x, edge_index, edge_attr."""
        emb = self.encode(batch.x, batch.edge_index, batch.edge_attr)
        out = {"emb": emb, "potential": self.potential(emb)}
        if getattr(batch, "cand_pairs", None) is not None:
            root_idx, cand_idx, pair = batch.cand_pairs
            out["rank"] = self.rank(emb[root_idx], emb[cand_idx], pair)
        out["policy"] = self.policy(emb)
        return out

    # ---- deployment submodels shipped to the ABC C runtime ----------------
    def export_potential_submodel(self):
        """A tiny module: node_feat -> potential (encoder folded to identity).

        For the fast path we actually export the head that consumes *cached*
        embeddings; but for the simplest ONNX (fallback-compatible) we also
        provide a direct node_feat->scalar path used by mlInfer.c's
        "node_feat"->"potential" signature.
        """
        return _PotentialProxy(self)

    def export_ranker_submodel(self):
        return _RankerProxy(self)


class _PotentialProxy(nn.Module):
    """node_feat[16] -> potential scalar, matching mlInfer.c ONNX I/O names."""

    def __init__(self, model: SynapseModel):
        super().__init__()
        self.model = model

    def forward(self, node_feat):
        # single-node "encode": treat the feature vector as a 1-node graph with
        # no edges; the AIGConv in_proj + out still yields a usable embedding.
        emb = torch.tanh(self.model.encoder.in_proj(node_feat)) \
            if hasattr(self.model.encoder, "in_proj") else node_feat
        emb = self.model.encoder.out(emb) if hasattr(self.model.encoder, "out") else emb
        return self.model.potential(emb)


class _RankerProxy(nn.Module):
    """rank_feat[2*emb + div] -> score, matching mlInfer.c ONNX I/O names.

    NOTE: for the concatenated-embedding path the caller must supply real
    cached embeddings. This proxy is primarily for exporting a smoke-test graph.
    """

    def __init__(self, model: SynapseModel):
        super().__init__()
        self.model = model
        self.cfg = model.cfg

    def forward(self, rank_feat):
        d = self.cfg.emb_dim
        root_emb = rank_feat[:, :d]
        cand_emb = rank_feat[:, d:2 * d]
        pair = rank_feat[:, 2 * d:]
        return self.model.rank(root_emb, cand_emb, pair)


def multitask_loss(cfg, out, targets):
    """Combine the task losses. `targets` provides whatever labels are present."""
    loss = out["emb"].new_zeros(())
    if "potential" in targets:
        loss = loss + cfg.w_potential * nn.functional.mse_loss(
            out["potential"], targets["potential"])
    if "rank" in out and "rank_pairs" in targets:
        # pairwise margin ranking: positive should score above negative
        pos, neg = targets["rank_pairs"]
        loss = loss + cfg.w_rank * nn.functional.margin_ranking_loss(
            out["rank"][pos], out["rank"][neg],
            torch.ones_like(out["rank"][pos]), margin=0.5)
    if "policy_target" in targets:
        loss = loss + cfg.w_policy * nn.functional.cross_entropy(
            out["policy"], targets["policy_target"])
    return loss
