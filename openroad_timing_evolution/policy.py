"""Bounded generated C++ priority policies, never eval() or free-form patches."""
from __future__ import annotations

import hashlib
import json
import math
import random
from dataclasses import dataclass
from pathlib import Path

FEATURES = ("load", "fanout", "position")
OPS = ("add", "sub", "mul", "min", "max")
PROGRAM_OPS = (
    "load_pressure",
    "fanout_shock",
    "late_path_focus",
    "frontload_relief",
    "nonlinear_blend",
    "stability_damper",
)

PROGRAM_CPP = {
    "load_pressure": "score += f.load;",
    "fanout_shock": "score += 0.35 * f.load * std::log1p(f.fanout);",
    "late_path_focus": "if (f.position > 0.65) { score += 0.20 * f.load; }",
    "frontload_relief": "if (f.position < 0.20) { score -= 0.10 * f.fanout; }",
    "nonlinear_blend": "score += 0.15 * std::sqrt(std::abs(f.load)) * (1.0 + f.fanout);",
    "stability_damper": "score -= 0.05 * f.position * f.position;",
}

HEURISTIC_NAMES = {
    "load_pressure": "Load Pressure",
    "fanout_shock": "Fanout Shock Path Pressure",
    "late_path_focus": "Late-Path Focus",
    "frontload_relief": "Front-Loaded Relief",
    "nonlinear_blend": "Nonlinear Slack-Load Blend",
    "stability_damper": "Stability Damper",
}


def program_segments(program):
    if type(program) is not list or not program:
        return []
    out = []

    def visit(start, end, name):
        out.append((start, end, name))
        if end - start <= 1:
            return
        mid = start + (end - start) // 2
        visit(start, mid, name + "L")
        visit(mid, end, name + "R")

    visit(0, len(program), "S")
    return out


def describe_program(program):
    names = [HEURISTIC_NAMES.get(op, op) for op in program]
    segments = [f"{name}[{start}:{end}]" for start, end, name in program_segments(program)]
    return "blocks=" + " -> ".join(names) + "; segment-tree=" + ", ".join(segments)


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


def validate_program(program):
    if type(program) is not list or not program:
        raise ValueError("program must be a nonempty list")
    if len(program) > 16:
        raise ValueError("program may contain at most 16 statements")
    for op in program:
        if op not in PROGRAM_OPS:
            raise ValueError(f"unknown program operation: {op}")


def program_body(program, cpp=False):
    if not cpp:
        return list(program)
    return (
        "// Segmented Semantic Program Evolution: "
        + describe_program(program)
        + "\n  double score = 0.0;\n  "
        + "\n  ".join(PROGRAM_CPP[op] for op in program)
        + "\n  return score;"
    )


def evaluate_program(program, features):
    load, fanout, position = features
    score = 0.0
    for op in program:
        if op == "load_pressure":
            score += load
        elif op == "fanout_shock":
            score += 0.35 * load * math.log1p(fanout)
        elif op == "late_path_focus":
            if position > 0.65:
                score += 0.20 * load
        elif op == "frontload_relief":
            if position < 0.20:
                score -= 0.10 * fanout
        elif op == "nonlinear_blend":
            score += 0.15 * math.sqrt(abs(load)) * (1.0 + fanout)
        elif op == "stability_damper":
            score -= 0.05 * position * position
        else:
            raise ValueError("unknown program operation")
    return score


@dataclass(frozen=True)
class Policy:
    enabled: bool
    code_json: str

    @classmethod
    def from_dict(cls, data):
        if type(data) is not dict or "enabled" not in data:
            raise ValueError("policy requires enabled plus expression or program")
        if type(data["enabled"]) is not bool:
            raise ValueError("enabled must be boolean")
        keys = set(data)
        if keys == {"enabled", "expression"}:
            validate_expr(data["expression"])
            if not data["enabled"] and data["expression"] != "load":
                raise ValueError("disabled policy must be the canonical stock control")
            code = {"kind": "expression", "value": data["expression"]}
        elif keys == {"enabled", "program"}:
            validate_program(data["program"])
            if not data["enabled"] and data["program"] != ["load_pressure"]:
                raise ValueError("disabled policy must be the canonical stock control")
            code = {"kind": "program", "value": data["program"]}
        else:
            raise ValueError("policy requires exactly enabled and one of expression/program")
        return cls(data["enabled"], canonical(code))

    @classmethod
    def stock(cls):
        return cls.from_dict({"enabled": False, "program": ["load_pressure"]})

    @classmethod
    def read(cls, path):
        if Path(path).stat().st_size > 8192:
            raise ValueError("policy file exceeds 8 KiB")
        return cls.from_dict(json.loads(Path(path).read_text()))

    def data(self):
        code = json.loads(self.code_json)
        return {"enabled": self.enabled, code["kind"]: code["value"]}

    @property
    def id(self):
        return hashlib.sha256(canonical(self.data()).encode()).hexdigest()[:16]

    def header(self):
        # Template and validator are trusted evaluator code, not evolved artifacts.
        template = (Path(__file__).parent / "cpp/policy.h.in").read_text()
        code = json.loads(self.code_json)
        if code["kind"] == "expression":
            body = "return " + expression(code["value"], True) + ";"
        else:
            body = program_body(code["value"], True)
        return template.replace("@ENABLED@", str(self.enabled).lower()).replace(
            "@PRIORITY_BODY@", body).replace("@ID@", self.id)

    def score(self, features):
        code = json.loads(self.code_json)
        if code["kind"] == "expression":
            return evaluate_expr(code["value"], features)
        return evaluate_program(code["value"], features)


def random_tree(rng, depth=0):
    if depth >= 3 or rng.random() < 0.5:
        return rng.choice([*FEATURES, -2.0, -1.0, -0.5, 0.0, 0.5, 1.0, 2.0])
    return [rng.choice(OPS), random_tree(rng, depth+1), random_tree(rng, depth+1)]


def mutate(parent, rng: random.Random):
    for _ in range(100):
        data = parent.data()
        if "program" in data:
            program = list(data["program"])
            action = rng.choice(("replace", "insert", "delete", "swap", "segment_reverse", "segment_duplicate"))
            if action == "replace" and program:
                program[rng.randrange(len(program))] = rng.choice(PROGRAM_OPS)
            elif action == "insert" and len(program) < 16:
                program.insert(rng.randrange(len(program) + 1), rng.choice(PROGRAM_OPS))
            elif action == "delete" and len(program) > 1:
                del program[rng.randrange(len(program))]
            elif action == "swap" and len(program) > 1:
                a, b = rng.sample(range(len(program)), 2)
                program[a], program[b] = program[b], program[a]
            elif action == "segment_reverse" and len(program) > 2:
                start, end, _ = rng.choice([s for s in program_segments(program) if s[1] - s[0] > 1])
                program[start:end] = reversed(program[start:end])
            elif action == "segment_duplicate" and len(program) < 16:
                start, end, _ = rng.choice(program_segments(program))
                fragment = program[start:end][: 16 - len(program)]
                program[start:start] = fragment
            try:
                return Policy.from_dict({"enabled": True, "program": program})
            except ValueError:
                continue
        tree = data["expression"]
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
