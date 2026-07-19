"""Smoke tests for RL gate sizing."""

from __future__ import annotations

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))


def test_env_and_policy():
    import torch
    from gym_env.sizing_env import MockSizingEnv
    from models.policy import PolicyConfig, SizingActorCritic

    env = MockSizingEnv(n_inst=24, max_steps=3, seed=2)
    st = env.reset()
    pol = SizingActorCritic(PolicyConfig(node_dim=st.x.size(1), n_actions=env.n_size_levels))
    out = pol(st.x, st.edge_index)
    assert out["inst_logits"].shape[0] == st.x.shape[0]
    assert out["action_logits"].shape == (st.x.shape[0], env.n_size_levels)
    step = pol.act(st.x, st.edge_index)
    st2, rew, done, info = env.step(step["instance"], step["action"])
    assert isinstance(rew, float)
    print("PASS test_env_and_policy", info, "reward", rew)


def test_openroad_stub():
    from openroad_api.sizing_hooks import swap_master

    assert swap_master(None, "u1", "BUF_X2") is False
    print("PASS test_openroad_stub")


if __name__ == "__main__":
    test_env_and_policy()
    test_openroad_stub()
    print("ALL PASS")
