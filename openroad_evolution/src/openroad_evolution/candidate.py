"""Candidate representation and C++ source rendering for OptMirror evolution."""

from __future__ import annotations

from dataclasses import asdict, dataclass, field
from hashlib import sha256
import json
import math

PROGRAM_OPS = (
    "hpwl_log",
    "degree_log",
    "mirror_entropy_temper",
    "fanout_shock_penalty",
    "hpwl_degree_cross",
    "deterministic_phase",
)

CODE_SNIPPETS = {
    "hpwl_log": "score += std::log1p(static_cast<double>(hpwl));",
    "degree_log": "score += 0.35 * std::log1p(static_cast<double>(degree));",
    "mirror_entropy_temper": (
        "const double entropy = std::log1p(static_cast<double>(degree));\n"
        "    score += std::log1p(static_cast<double>(hpwl)) / (1.0 + entropy);"
    ),
    "fanout_shock_penalty": (
        "if (degree > 8) {\n"
        "      score -= 0.20 * std::log1p(static_cast<double>(degree - 8));\n"
        "    }"
    ),
    "hpwl_degree_cross": (
        "score += 0.05 * std::sqrt(std::log1p(static_cast<double>(hpwl)))\n"
        "           * std::log1p(static_cast<double>(degree));"
    ),
    "deterministic_phase": "score += static_cast<double>(stable_id % 17) * 1e-9;",
}

HEURISTIC_NAMES = {
    "hpwl_log": "Local HPWL Pressure",
    "degree_log": "Pin-Degree Pressure",
    "mirror_entropy_temper": "Mirror Entropy Tempering",
    "fanout_shock_penalty": "Fanout Shock Guard",
    "hpwl_degree_cross": "HPWL-Degree Cross Pressure",
    "deterministic_phase": "Deterministic Phase Tie Shaper",
}

BLOCK_META = {
    "hpwl_log": {"reads": ("hpwl",), "writes": ("score",), "control": "straight_line", "role": "physical_pressure"},
    "degree_log": {"reads": ("degree",), "writes": ("score",), "control": "straight_line", "role": "connectivity_pressure"},
    "mirror_entropy_temper": {"reads": ("hpwl", "degree"), "writes": ("entropy", "score"), "control": "derived_value", "role": "semantic_tempering"},
    "fanout_shock_penalty": {"reads": ("degree",), "writes": ("score",), "control": "conditional", "role": "legality_risk_guard"},
    "hpwl_degree_cross": {"reads": ("hpwl", "degree"), "writes": ("score",), "control": "straight_line", "role": "feature_interaction"},
    "deterministic_phase": {"reads": ("stable_id",), "writes": ("score",), "control": "tie_breaker", "role": "deterministic_diversity"},
}


def program_segments(program: tuple[str, ...] | list[str]) -> list[tuple[int, int, str]]:
    """Return a binary segment tree over generated-code leaves.

    Each leaf is one audited C++ statement block. Internal nodes are contiguous
    source-code regions that can be mutated together, which makes the search
    look like code evolution at the block/subtree level while keeping the
    generated source bounded and reviewable.
    """
    items = list(program)
    if not items:
        return []
    out: list[tuple[int, int, str]] = []

    def visit(start: int, end: int, name: str) -> None:
        out.append((start, end, name))
        if end - start <= 1:
            return
        mid = start + (end - start) // 2
        visit(start, mid, name + "L")
        visit(mid, end, name + "R")

    visit(0, len(items), "S")
    return out


def relation_graph(program: tuple[str, ...] | list[str]) -> dict[str, object]:
    """Build a semantic relation graph for the generated code blocks.

    This graph is intentionally lightweight, but it is real metadata consumed
    by mutation. Edges are added when code blocks are nearby in source order,
    consume or produce the same variables, or share a control-flow role.
    """
    items = list(program)
    nodes = []
    edges = []
    for index, op in enumerate(items):
        meta = BLOCK_META[op]
        nodes.append(
            {
                "id": f"n{index}",
                "op": op,
                "name": HEURISTIC_NAMES[op],
                "reads": list(meta["reads"]),
                "writes": list(meta["writes"]),
                "control": meta["control"],
                "role": meta["role"],
            }
        )
    for i, left in enumerate(items):
        left_meta = BLOCK_META[left]
        for j, right in enumerate(items[i + 1 :], i + 1):
            right_meta = BLOCK_META[right]
            reasons = []
            distance = j - i
            if distance == 1:
                reasons.append("source_locality")
            left_vars = set(left_meta["reads"]) | set(left_meta["writes"])
            right_vars = set(right_meta["reads"]) | set(right_meta["writes"])
            shared = sorted(left_vars & right_vars)
            if shared:
                reasons.append("data_flow:" + ",".join(shared))
            if left_meta["control"] == right_meta["control"]:
                reasons.append("control_role:" + str(left_meta["control"]))
            if reasons:
                edges.append({"from": f"n{i}", "to": f"n{j}", "distance": distance, "reasons": reasons})
    return {"nodes": nodes, "edges": edges}


def related_indices(program: tuple[str, ...] | list[str]) -> list[tuple[int, int]]:
    pairs = []
    for edge in relation_graph(program)["edges"]:
        left = int(str(edge["from"])[1:])
        right = int(str(edge["to"])[1:])
        pairs.append((left, right))
    return pairs


def describe_program(program: tuple[str, ...] | list[str]) -> str:
    names = [HEURISTIC_NAMES.get(op, op) for op in program]
    segments = [f"{name}[{start}:{end}]" for start, end, name in program_segments(program)]
    graph = relation_graph(program)
    edge_summary = [
        f"{edge['from']}->{edge['to']}({'+'.join(edge['reasons'])})"
        for edge in graph["edges"]
    ]
    return (
        "blocks="
        + " -> ".join(names)
        + "; segment-tree="
        + ", ".join(segments)
        + "; semantic-relation-graph="
        + ", ".join(edge_summary)
    )


@dataclass(frozen=True)
class MirrorPolicy:
    """A small generated C++ policy that only ranks legal mirror attempts.

    The upstream acceptance check and cell-edge spacing check are deliberately
    outside this policy. A candidate can therefore alter a non-commutative
    heuristic decision, but never approve an illegal action by itself.
    """

    hpwl_weight: float = 1.0
    degree_weight: float = 0.0
    enabled: bool = True
    program: tuple[str, ...] = field(default_factory=lambda: ("hpwl_log",))

    @classmethod
    def baseline(cls) -> "MirrorPolicy":
        """Return the stock algorithm: candidate order is not changed."""
        return cls(enabled=False, program=())

    def validate(self) -> None:
        for name, value in asdict(self).items():
            if name in ("enabled", "program"):
                continue
            if not math.isfinite(value) or abs(value) > 5.0:
                raise ValueError(f"{name} must be finite and in [-5, 5]")
        if type(self.program) is not tuple:
            raise ValueError("program must be an immutable tuple")
        if len(self.program) > 16:
            raise ValueError("program may contain at most 16 statements")
        for op in self.program:
            if op not in PROGRAM_OPS:
                raise ValueError(f"unknown program operation: {op}")
        if self.enabled and not self.program:
            raise ValueError("an enabled policy must contain generated code")

    @property
    def identifier(self) -> str:
        payload = json.dumps(self.to_dict(), sort_keys=True, separators=(",", ":"))
        return sha256(payload.encode()).hexdigest()[:12]

    def to_dict(self) -> dict[str, float | bool | list[str]]:
        return {
            "hpwl_weight": self.hpwl_weight,
            "degree_weight": self.degree_weight,
            "enabled": self.enabled,
            "program": list(self.program),
        }

    @classmethod
    def from_dict(cls, value: dict[str, float | bool | list[str]]) -> "MirrorPolicy":
        data = dict(value)
        if "program" not in data:
            data["program"] = [] if data.get("enabled") is False else ["hpwl_log"]
        data["program"] = tuple(data["program"])  # type: ignore[index]
        policy = cls(**data)
        policy.validate()
        return policy

    def _score_body(self) -> str:
        if not self.enabled:
            return "return 0.0;"
        lines = ["double score = 0.0;"]
        if self.hpwl_weight or self.degree_weight:
            lines += [
                f"score += {self.hpwl_weight:.17g} * std::log1p(static_cast<double>(hpwl));",
                f"score += {self.degree_weight:.17g} * std::log1p(static_cast<double>(degree));",
            ]
        for op in self.program:
            lines.append(CODE_SNIPPETS[op])
        lines.append("return score;")
        return "\n    ".join(lines)

    def to_header(self) -> str:
        """Render the only source file varied by the search.

        Using a generated header keeps a candidate reviewable (roughly 25
        lines), makes incremental builds cheap, and gives every archive record
        a direct source artifact rather than an opaque parameter list.
        """
        self.validate()
        enabled = "true" if self.enabled else "false"
        segment_comment = describe_program(self.program) if self.program else "stock-order baseline"
        return f"""// Generated by openroad_evolution; candidate {self.identifier}.
// Do not edit: the experiment runner rewrites this file per candidate.
// Segmented Semantic Program Evolution: {segment_comment}
#pragma once

#include <cmath>
#include <cstdint>

namespace dpl {{
class EvolvedMirrorPolicy
{{
 public:
  static constexpr bool enabled() {{ return {enabled}; }}

  static double score(const int64_t hpwl,
                      const uint32_t degree,
                      const uint32_t stable_id)
  {{
    {self._score_body()}
  }}

  static bool isHigherPriority(const int64_t lhs_hpwl,
                               const uint32_t lhs_degree,
                               const uint32_t lhs_id,
                               const int64_t rhs_hpwl,
                               const uint32_t rhs_degree,
                               const uint32_t rhs_id)
  {{
    const double lhs_score = score(lhs_hpwl, lhs_degree, lhs_id);
    const double rhs_score = score(rhs_hpwl, rhs_degree, rhs_id);
    if (lhs_score != rhs_score) {{
      return lhs_score > rhs_score;
    }}
    return lhs_id < rhs_id;
  }}
}};
}}  // namespace dpl
"""
