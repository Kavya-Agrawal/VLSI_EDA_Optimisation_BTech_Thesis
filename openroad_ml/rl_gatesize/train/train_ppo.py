"""Short PPO-style loop on MockSizingEnv (no GPU)."""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

import torch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

from gym_env.sizing_env import MockSizingEnv
from models.policy import PolicyConfig, SizingActorCritic


def train(episodes: int = 10, seed: int = 0):
    env = MockSizingEnv(seed=seed)
    cfg = PolicyConfig(n_actions=env.n_size_levels)
    policy = SizingActorCritic(cfg)
    opt = torch.optim.Adam(policy.parameters(), lr=3e-4)
    gamma = 0.95

    for ep in range(episodes):
        state = env.reset()
        logps, values, rewards = [], [], []
        done = False
        while not done:
            # fold size into features
            x = state.x.clone()
            x[:, 2] = state.sizes.float() / max(1, env.n_size_levels - 1)
            step = policy.act(x, state.edge_index)
            state, reward, done, info = env.step(step["instance"], step["action"])
            logps.append(step["logp"])
            values.append(step["value"])
            rewards.append(reward)

        # returns
        R = 0.0
        returns = []
        for r in reversed(rewards):
            R = r + gamma * R
            returns.insert(0, R)
        returns_t = torch.tensor(returns, dtype=torch.float32)
        values_t = torch.stack(values)
        logps_t = torch.stack(logps)
        adv = returns_t - values_t.detach()
        loss = -(logps_t * adv).mean() + 0.5 * torch.nn.functional.mse_loss(values_t, returns_t)
        opt.zero_grad()
        loss.backward()
        opt.step()
        print(
            f"ep {ep+1}/{episodes}  return={sum(rewards):.3f}  "
            f"tns={info['tns']:.3f}  wns={info['wns']:.3f}  loss={float(loss):.4f}"
        )

    out = Path("checkpoints")
    out.mkdir(exist_ok=True)
    torch.save({"model": policy.state_dict(), "cfg": cfg.__dict__}, out / "sizing_ac.pt")
    print(f"wrote {out / 'sizing_ac.pt'}")


def main():
    p = argparse.ArgumentParser()
    p.add_argument("--episodes", type=int, default=5)
    p.add_argument("--mock", action="store_true", default=True)
    p.add_argument("--seed", type=int, default=0)
    args = p.parse_args()
    train(episodes=args.episodes, seed=args.seed)


if __name__ == "__main__":
    main()
