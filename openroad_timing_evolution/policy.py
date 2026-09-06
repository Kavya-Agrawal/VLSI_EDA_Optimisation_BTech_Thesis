"""A bounded expression grammar, never eval(), arbitrary C++, or model patches."""
from __future__ import annotations

import hashlib
import json
import math
import random
from dataclasses import dataclass
from pathlib import Path

FEATURES = ("load", "fanout", "position")
OPS = ("add", "sub", "mul", "min", "max")


def canonical(value) -> str:
    return json.dumps(value, sort_keys=True, separators=(",", ":"), allow_nan=False)


def validate_expr(node, depth=0) -> int:
    if depth > 5:
        raise ValueError("expression exceeds depth 5")
    if type(node) in (int, float):
        if not math.isfinite(node) or abs(node) > 4:
            raise ValueError("constant must be finite and in [-4,4]")
        return 1
    if type(node) is str and node in FEATURES:
        return 1
    if type(node) is not list or len(node) != 3 or node[0] not in OPS:
        raise ValueError("expected a feature, bounded number, or [op, left, right]")
    size = 1 + validate_expr(node[1], depth + 1) + validate_expr(node[2], depth + 1)
    if size > 31:
        raise ValueError("expression exceeds 31 nodes")
    return size


def expression(node, cpp=False):
    if type(node) in (int, float):
        return repr(float(node))
    if type(node) is str:
        return "f." + node if cpp else node
    op, a, b = node
    a, b = expression(a, cpp), expression(b, cpp)
    if op in ("min", "max"):
        return f"{'std::' if cpp else ''}{op}({a}, {b})"
    return "(" + a + " " + {"add": "+", "sub": "-", "mul": "*"}[op] + " " + b + ")"


def evaluate_expr(node, features):
    if type(node) in (int, float):
        return float(node)
    if type(node) is str:
        return features[FEATURES.index(node)]
    op, a, b = node
    a, b = evaluate_expr(a, features), evaluate_expr(b, features)
    return {"add": lambda: a+b, "sub": lambda: a-b, "mul": lambda: a*b,
            "min": lambda: min(a,b), "max": lambda: max(a,b)}[op]()


@dataclass(frozen=True)
class Policy:
    enabled: bool
    tree_json: str

    @classmethod
    def from_dict(cls, data):
        if type(data) is not dict or set(data) != {"enabled", "expression"}:
            raise ValueError("policy requires exactly enabled and expression")
        if type(data["enabled"]) is not bool:
            raise ValueError("enabled must be boolean")
        validate_expr(data["expression"])
        if not data["enabled"] and data["expression"] != "load":
            raise ValueError("disabled policy must be the canonical stock control")
        return cls(data["enabled"], canonical(data["expression"]))

    @classmethod
    def stock(cls):
        return cls.from_dict({"enabled": False, "expression": "load"})

    @classmethod
    def read(cls, path):
        if Path(path).stat().st_size > 8192:
            raise ValueError("policy file exceeds 8 KiB")
        return cls.from_dict(json.loads(Path(path).read_text()))

    def data(self):
        return {"enabled": self.enabled, "expression": json.loads(self.tree_json)}

    @property
    def id(self):
        return hashlib.sha256(canonical(self.data()).encode()).hexdigest()[:16]

    def header(self):
        # Template and validator are trusted evaluator code, not evolved artifacts.
        template = (Path(__file__).parent / "cpp/policy.h.in").read_text()
        return template.replace("@ENABLED@", str(self.enabled).lower()).replace(
            "@EXPRESSION@", expression(json.loads(self.tree_json), True)).replace("@ID@", self.id)


def random_tree(rng, depth=0):
    if depth >= 3 or rng.random() < 0.5:
        return rng.choice([*FEATURES, -2.0, -1.0, -0.5, 0.0, 0.5, 1.0, 2.0])
    return [rng.choice(OPS), random_tree(rng, depth+1), random_tree(rng, depth+1)]


def mutate(parent, rng: random.Random):
    for _ in range(100):
        tree = json.loads(parent.tree_json)
        paths = [()]
        def walk(n, p=()):
            if type(n) is list:
                for i in (1, 2):
                    paths.append(p+(i,))
                    walk(n[i], p+(i,))
        walk(tree)
        p = rng.choice(paths)
        if not p:
            tree = random_tree(rng)
        else:
            n = tree
            for i in p[:-1]:
                n = n[i]
            n[p[-1]] = random_tree(rng)
        try:
            return Policy.from_dict({"enabled": True, "expression": tree})
        except ValueError:
            continue
    raise RuntimeError("could not generate a valid mutation")
