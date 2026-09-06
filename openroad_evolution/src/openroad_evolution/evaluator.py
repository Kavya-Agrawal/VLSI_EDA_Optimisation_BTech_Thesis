"""Compile, regression-test, and run each policy through the full ORFS flow."""

from __future__ import annotations

from dataclasses import dataclass
from datetime import datetime, timezone
import json
from pathlib import Path
import subprocess
from typing import Callable

from .candidate import MirrorPolicy
from .config import ExperimentConfig
from .metrics import FlowMetrics, score_candidate, verify_correctness
from .workspace import OpenRoadWorkspace


@dataclass(frozen=True)
class Evaluation:
    policy: MirrorPolicy
    valid: bool
    score: float | None
    reasons: list[str]
    metrics: dict | None
    directory: Path


class FlowEvaluator:
    """Serial evaluator: one reusable build tree avoids cross-candidate races."""

    def __init__(self, config: ExperimentConfig):
        self.config = config
        self.workspace = OpenRoadWorkspace(config)
        self.results_dir = config.workspace.parent / ".evolution" / "runs"

    def prepare(self) -> None:
        self.workspace.prepare()
        self.results_dir.mkdir(parents=True, exist_ok=True)

    def _command(self, command: str, log: Path) -> int:
        completed = subprocess.run(
            command,
            shell=True,
            cwd=self.config.workspace,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
        )
        log.write_text(completed.stdout)
        return completed.returncode

    def evaluate(self, policy: MirrorPolicy, baseline: FlowMetrics | None = None) -> Evaluation:
        self.prepare()
        run_dir = self.results_dir / policy.identifier
        run_dir.mkdir(parents=True, exist_ok=True)
        self.workspace.write_policy(policy)
        # Archive the exact executable source, not merely its parameters.
        # The shared worktree header will be overwritten by the next candidate.
        (run_dir / "EvolvedMirrorPolicy.h").write_text(policy.to_header())
        context = dict(source_dir=self.workspace.source_dir, build_dir=self.workspace.build_dir)

        build = self.config.format(self.config.build_command, **context)
        if self._command(build, run_dir / "build.log") != 0:
            return self._record(policy, run_dir, ["OpenROAD compilation failed"])

        unit = self.config.format(self.config.unit_test_command, **context)
        if self._command(unit, run_dir / "unit.log") != 0:
            return self._record(policy, run_dir, ["OptMirror regression suite failed"])

        if self.config.full_flow:
            flow = self.config.format(self.config.flow_command, **context)
            if self._command(flow, run_dir / "flow.log") != 0:
                return self._record(policy, run_dir, ["complete ORFS RTL-to-GDS flow failed"])

        metrics_path = Path(self.config.format(self.config.metrics_path_template, **context))
        if not metrics_path.exists():
            return self._record(policy, run_dir, [f"ORFS metadata missing: {metrics_path}"])
        metrics = FlowMetrics.load(metrics_path)
        (run_dir / "metadata.json").write_text(json.dumps(metrics.raw, indent=2, sort_keys=True))

        reasons = [] if baseline is None else verify_correctness(metrics, baseline)
        score = None if baseline is None or reasons else score_candidate(metrics, baseline)
        return self._record(policy, run_dir, reasons, metrics=metrics.raw, score=score)

    def _record(
        self,
        policy: MirrorPolicy,
        directory: Path,
        reasons: list[str],
        *,
        metrics: dict | None = None,
        score: float | None = None,
    ) -> Evaluation:
        result = Evaluation(policy, not reasons, score, reasons, metrics, directory)
        (directory / "result.json").write_text(
            json.dumps(
                {
                    "policy": policy.to_dict(),
                    "identifier": policy.identifier,
                    "valid": result.valid,
                    "score": score,
                    "reasons": reasons,
                    "metrics": metrics,
                    "finished_at": datetime.now(timezone.utc).isoformat(),
                },
                indent=2,
                sort_keys=True,
            )
        )
        return result
