"""Token / USD accounting across every `claude -p` call.

Persisted at 11_agent_data/budget.json so `make evolve-resume` continues the running total.
`charge()` records a call; `exhausted()` tells the orchestrator to stop cleanly before starting
the next iteration (an iteration in flight is always finished)."""
from __future__ import annotations

from dataclasses import dataclass, field
from pathlib import Path
from typing import Any

from .util import now_iso, read_json, write_json


@dataclass
class Budget:
    path: Path
    budget_usd: float = 0.0        # 0 = unlimited
    max_tokens: int = 0            # 0 = unlimited (input + output + cache-creation; cache reads excluded)
    spent_usd: float = 0.0
    spent_tokens: int = 0
    calls: list[dict[str, Any]] = field(default_factory=list)

    @classmethod
    def load(cls, path: Path, budget_usd: float = 0.0, max_tokens: int = 0, reset: bool = False) -> "Budget":
        d = {} if reset else (read_json(path, {}) or {})
        b = cls(path=path, budget_usd=budget_usd, max_tokens=max_tokens,
                spent_usd=float(d.get("spent_usd", 0.0)), spent_tokens=int(d.get("spent_tokens", 0)),
                calls=list(d.get("calls", [])))
        return b

    def save(self) -> None:
        write_json(self.path, {"spent_usd": round(self.spent_usd, 6), "spent_tokens": self.spent_tokens,
                               "budget_usd": self.budget_usd, "max_tokens": self.max_tokens,
                               "updated": now_iso(), "calls": self.calls[-500:]})

    @staticmethod
    def tokens_of(usage: dict[str, Any] | None) -> int:
        if not usage:
            return 0
        return int(usage.get("input_tokens", 0)) + int(usage.get("output_tokens", 0)) + \
            int(usage.get("cache_creation_input_tokens", 0))

    def charge(self, *, role: str, iteration: int, result: dict[str, Any]) -> dict[str, Any]:
        usd = float(result.get("total_cost_usd") or 0.0)
        toks = self.tokens_of(result.get("usage"))
        rec = {"ts": now_iso(), "role": role, "iteration": iteration, "usd": round(usd, 6), "tokens": toks,
               "turns": result.get("num_turns"), "session_id": result.get("session_id"),
               "duration_ms": result.get("duration_ms"), "model": next(iter((result.get("modelUsage") or {}).keys()), None)}
        self.spent_usd += usd
        self.spent_tokens += toks
        self.calls.append(rec)
        self.save()
        return rec

    def exhausted(self) -> str | None:
        if self.budget_usd and self.spent_usd >= self.budget_usd:
            return f"USD budget reached: spent {self.spent_usd:.2f} >= {self.budget_usd:.2f}"
        if self.max_tokens and self.spent_tokens >= self.max_tokens:
            return f"token budget reached: {self.spent_tokens} >= {self.max_tokens}"
        return None

    def remaining_usd(self) -> float | None:
        return None if not self.budget_usd else max(0.0, self.budget_usd - self.spent_usd)

    def per_iteration(self) -> dict[int, dict[str, float]]:
        out: dict[int, dict[str, float]] = {}
        for c in self.calls:
            it = int(c.get("iteration", 0))
            o = out.setdefault(it, {"usd": 0.0, "tokens": 0})
            o["usd"] += c["usd"]; o["tokens"] += c["tokens"]
        return out

    def summary(self) -> str:
        cap = f" / {self.budget_usd:.2f}" if self.budget_usd else ""
        return f"spent ${self.spent_usd:.2f}{cap}, {self.spent_tokens:,} tokens over {len(self.calls)} calls"
