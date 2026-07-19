"""GNN actor-critic for discrete gate sizing."""

from __future__ import annotations

from dataclasses import dataclass

import torch
import torch.nn as nn
import torch.nn.functional as F


@dataclass
class PolicyConfig:
    node_dim: int = 12
    hidden: int = 64
    n_actions: int = 5  # e.g. -2,-1,0,+1,+2 size steps
    layers: int = 2


class MeanAgg(nn.Module):
    def __init__(self, dim: int):
        super().__init__()
        self.lin = nn.Linear(dim * 2, dim)

    def forward(self, x: torch.Tensor, edge_index: torch.Tensor) -> torch.Tensor:
        src, dst = edge_index[0], edge_index[1]
        agg = torch.zeros_like(x)
        agg.index_add_(0, dst, x[src])
        deg = torch.zeros(x.size(0), 1, device=x.device, dtype=x.dtype)
        deg.index_add_(0, dst, torch.ones(dst.size(0), 1, device=x.device, dtype=x.dtype))
        return F.relu(self.lin(torch.cat([x, agg / deg.clamp(min=1.0)], dim=-1)))


class SizingActorCritic(nn.Module):
    def __init__(self, cfg: PolicyConfig | None = None):
        super().__init__()
        self.cfg = cfg or PolicyConfig()
        c = self.cfg
        self.enc = nn.Linear(c.node_dim, c.hidden)
        self.layers = nn.ModuleList([MeanAgg(c.hidden) for _ in range(c.layers)])
        self.actor = nn.Linear(c.hidden, c.n_actions)
        self.critic = nn.Linear(c.hidden, 1)
        self.inst_score = nn.Linear(c.hidden, 1)  # which instance to touch

    def encode(self, x: torch.Tensor, edge_index: torch.Tensor) -> torch.Tensor:
        h = F.relu(self.enc(x))
        for layer in self.layers:
            h = layer(h, edge_index)
        return h

    def forward(self, x: torch.Tensor, edge_index: torch.Tensor) -> dict[str, torch.Tensor]:
        h = self.encode(x, edge_index)
        inst_logits = self.inst_score(h).squeeze(-1)
        # Broadcast global context: pick instance then action on that node emb
        # For simplicity return per-node action logits + value from mean pool
        action_logits = self.actor(h)  # [N, A]
        value = self.critic(h.mean(dim=0, keepdim=True)).squeeze()
        return {
            "inst_logits": inst_logits,
            "action_logits": action_logits,
            "value": value,
            "node_emb": h,
        }

    def act(self, x: torch.Tensor, edge_index: torch.Tensor):
        out = self.forward(x, edge_index)
        inst_dist = torch.distributions.Categorical(logits=out["inst_logits"])
        inst = inst_dist.sample()
        act_dist = torch.distributions.Categorical(logits=out["action_logits"][inst])
        action = act_dist.sample()
        logp = inst_dist.log_prob(inst) + act_dist.log_prob(action)
        return {
            "instance": int(inst.item()),
            "action": int(action.item()),
            "logp": logp,
            "value": out["value"],
        }
