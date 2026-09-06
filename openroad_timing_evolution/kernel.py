"""Compile the actual generated header and differential-test the C++ policy."""
import json
import math
from pathlib import Path
import random
import subprocess

from .policy import evaluate_expr
from .workspace import ROOT, run


def check(policy, directory, samples=500):
    directory = Path(directory)
    directory.mkdir(parents=True, exist_ok=True)
    (directory/"EvolvedPathDriverPolicy.h").write_text(policy.header())
    cpp = ROOT / "cpp/check.cpp"
    binary = directory/"check"
    run(["g++", "-std=c++17", "-O1", "-g", "-Wall", "-Wextra", "-Werror",
         "-fsanitize=address,undefined", "-fno-omit-frame-pointer", "-fno-pie", "-no-pie",
         "-I", str(directory), str(cpp), "-o", str(binary)], directory/"compile.log", 60)
    rng = random.Random(20260907)
    cases = [[], [(0.0,0.0,0.0)], [(0.0,0.0,0.0)]*8,
             [(-1.0,1.0,1.0),(1.0,1.0,1.0)]]
    for _ in range(samples):
        scale = rng.choice([1e-300, 1e-9, 1.0, 1e100, 1e300])
        cases.append([(rng.uniform(-1,1)*scale, float(rng.randrange(100)), float(rng.randrange(100)))
                      for _ in range(rng.randrange(33))])
    data = "".join(str(len(c))+"\n"+"".join(" ".join(map(repr,f))+"\n" for f in c) for c in cases)
    result = subprocess.run([str(binary)], input=data, text=True, capture_output=True, timeout=30)
    (directory/"run.log").write_text(result.stdout + result.stderr)
    if result.returncode:
        raise RuntimeError(f"kernel/sanitizer failure; see {directory/'run.log'}")
    lines = result.stdout.splitlines()
    if len(lines) != len(cases):
        raise RuntimeError("kernel result count mismatch")
    for c, line in zip(cases, lines):
        actual = list(map(int, line.split()))
        if policy.enabled:
            dl = max((abs(f[0]) for f in c), default=0) or 1
            df = max((f[1] for f in c), default=0) or 1
            dp = max((f[2] for f in c), default=0) or 1
            scores = [evaluate_expr(json.loads(policy.tree_json), (f[0]/dl,f[1]/df,f[2]/dp)) for f in c]
            if not all(math.isfinite(s) for s in scores):
                raise RuntimeError("reference produced non-finite priority")
            expected = sorted(range(len(c)), key=lambda i: (-scores[i],i))
        else:
            expected = list(range(len(c)))
        if actual != expected:
            raise RuntimeError("C++ / Python ranking mismatch")
    summary = {"policy_id": policy.id, "cases": len(cases), "asan": True,
               "ubsan": True, "differential_pass": True}
    (directory/"result.json").write_text(json.dumps(summary, indent=2)+"\n")
    return summary
