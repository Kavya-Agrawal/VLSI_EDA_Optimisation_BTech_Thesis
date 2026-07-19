"""Gate-sizing environments: mock STA surrogate + OpenROAD stub."""

from __future__ import annotations

from dataclasses import dataclass, field

import torch


@dataclass
class SizingState:
    x: torch.Tensor
    edge_index: torch.Tensor
    sizes: torch.Tensor  # int size index per instance
    tns: float
    wns: float
    power: float
    area: float


@dataclass
class MockSizingEnv:
    """
    Analytic mock of OpenSTA rewards for smoke RL.
    Larger size → better delay proxy, higher power/area.
    """

    n_inst: int = 48
    node_dim: int = 12
    n_size_levels: int = 5
    max_steps: int = 20
    seed: int = 0
    step_count: int = 0
    state: SizingState | None = field(default=None, init=False)

    def reset(self) -> SizingState:
        g = torch.Generator().manual_seed(self.seed)
        x = torch.rand(self.n_inst, self.node_dim, generator=g)
        # chain-ish timing graph
        src = torch.arange(0, self.n_inst - 1)
        dst = src + 1
        edge_index = torch.stack([src, dst], dim=0)
        sizes = torch.ones(self.n_inst, dtype=torch.long)
        self.step_count = 0
        self.state = SizingState(
            x=x,
            edge_index=edge_index,
            sizes=sizes,
            tns=0.0,
            wns=0.0,
            power=0.0,
            area=0.0,
        )
        self._refresh_metrics()
        return self.state

    def _refresh_metrics(self) -> None:
        assert self.state is not None
        s = self.state
        # delay proxy decreases with size, criticality from feature 0
        delay = (s.x[:, 0] + 0.2) / (s.sizes.float() + 1.0)
        slack = 0.5 - delay
        s.wns = float(slack.min().item())
        s.tns = float(slack.clamp(max=0).sum().item())
        s.power = float((s.sizes.float() ** 1.5).sum().item())
        s.area = float(s.sizes.float().sum().item())

    def step(self, instance: int, action: int) -> tuple[SizingState, float, bool, dict]:
        """action in {0..n_actions-1} mapped to size delta -2..+2."""
        assert self.state is not None
        prev_tns, prev_wns = self.state.tns, self.state.wns
        prev_p, prev_a = self.state.power, self.state.area
        delta = action - (self.n_size_levels // 2)  # center = 0
        new_sz = int(self.state.sizes[instance].item()) + delta
        new_sz = max(0, min(self.n_size_levels - 1, new_sz))
        self.state.sizes[instance] = new_sz
        # bump drive feature lightly
        self.state.x[instance, 1] = new_sz / max(1, self.n_size_levels - 1)
        self._refresh_metrics()
        self.step_count += 1
        reward = (
            1.0 * (self.state.tns - prev_tns)
            + 0.5 * (self.state.wns - prev_wns)
            - 0.01 * (self.state.power - prev_p)
            - 0.005 * (self.state.area - prev_a)
        )
        done = self.step_count >= self.max_steps
        info = {"tns": self.state.tns, "wns": self.state.wns, "power": self.state.power}
        return self.state, float(reward), done, info
