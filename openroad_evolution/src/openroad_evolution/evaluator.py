"""Compile, test, and evaluate bounded policies through isolated ORFS flows."""

from __future__ import annotations

from dataclasses import dataclass, field
from datetime import datetime, timezone
from hashlib import sha256
import json
from pathlib import Path
import subprocess

from .candidate import MirrorPolicy
from .config import ExperimentConfig
from .metrics import (
    FlowMetrics,
    PromotionDecision,
    assess_promotion,
    median_metrics,
    score_candidate,
    verify_correctness,
)
from .workspace import OpenRoadWorkspace


@dataclass(frozen=True)
class Evaluation:
    policy: MirrorPolicy
    valid: bool
    score: float | None
    reasons: list[str]
    metrics: dict | None
    directory: Path
    replicas: list[dict] = field(default_factory=list)
    promotion: dict | None = None


class FlowEvaluator:
    """Serial evaluator with a transactional source worktree and replica runs.

    The only per-candidate source file is a generated policy header. ORFS
    receives a unique flow variant for every candidate and replica, preventing
    cached databases, reports, or metrics from one evaluation contaminating
    another.
    """

    def __init__(self, config: ExperimentConfig):
        self.config = config
        self.workspace = OpenRoadWorkspace(config)
        self.results_dir = (
            config.workspace.parent
            / ".evolution"
            / "runs"
            / config.platform
            / config.design_name
        )

    def prepare(self) -> None:
        self.workspace.prepare()
        self.workspace.assert_integrity(MirrorPolicy.baseline())
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

    def evaluate(self, policy: MirrorPolicy, baseline: Evaluation | None = None) -> Evaluation:
        self.prepare()
        run_dir = self.results_dir / policy.identifier
        run_dir.mkdir(parents=True, exist_ok=True)
        self.workspace.write_policy(policy)
        self.workspace.assert_integrity(policy)
        # The shared worktree header changes on the next candidate. Archive the
        # exact C++ source that this evaluation compiled.
        (run_dir / "EvolvedMirrorPolicy.h").write_text(policy.to_header())
        self._write_manifest(policy, run_dir)
        context = dict(source_dir=self.workspace.source_dir, build_dir=self.workspace.build_dir)

        build = self.config.format(self.config.build_command, **context, candidate_id=policy.identifier)
        if self._command(build, run_dir / "build.log") != 0:
            return self._record(policy, run_dir, ["OpenROAD compilation failed"])

        unit = self.config.format(self.config.unit_test_command, **context, candidate_id=policy.identifier)
        if self._command(unit, run_dir / "unit.log") != 0:
            return self._record(policy, run_dir, ["OptMirror regression suite failed"])

        reference_replicas = self._baseline_replicas(baseline)
        if baseline is not None and len(reference_replicas) != self.config.replicates:
            return self._record(
                policy,
                run_dir,
                [
                    "baseline replica count does not match the configured flow-seed set "
                    f"({len(reference_replicas)} != {self.config.replicates})"
                ],
            )
        replica_metrics: list[FlowMetrics] = []
        reasons: list[str] = []
        for replica in range(self.config.replicates):
            replica_dir = run_dir / f"replica-{replica:02d}"
            replica_dir.mkdir(parents=True, exist_ok=True)
            flow = self.config.format(
                self.config.flow_command,
                **context,
                candidate_id=policy.identifier,
                replica=replica,
            )
            if self.config.full_flow and self._command(flow, replica_dir / "flow.log") != 0:
                reasons.append(f"replica {replica}: complete ORFS RTL-to-GDS flow failed")
                continue

            metrics_path = Path(
                self.config.format(
                    self.config.metrics_path_template,
                    **context,
                    candidate_id=policy.identifier,
                    replica=replica,
                )
            )
            if not metrics_path.exists():
                reasons.append(f"replica {replica}: ORFS metadata missing: {metrics_path}")
                continue
            try:
                metrics = FlowMetrics.load(metrics_path)
                # Parse all mandatory fields before accepting a metadata file.
                metrics.required_values()
            except (OSError, ValueError, KeyError, json.JSONDecodeError) as exc:
                reasons.append(f"replica {replica}: invalid ORFS metadata: {exc}")
                continue
            (replica_dir / "metadata.json").write_text(
                json.dumps(metrics.raw, indent=2, sort_keys=True)
            )
            reference = reference_replicas[replica] if reference_replicas else metrics
            replica_errors = verify_correctness(metrics, reference)
            reasons.extend(f"replica {replica}: {error}" for error in replica_errors)
            replica_metrics.append(metrics)

        if len(replica_metrics) != self.config.replicates:
            return self._record(policy, run_dir, reasons, replicas=[item.raw for item in replica_metrics])
        aggregate = median_metrics(replica_metrics)
        promotion: PromotionDecision | None = None
        score: float | None = None
        if baseline is not None and reference_replicas and not reasons:
            promotion = assess_promotion(
                replica_metrics,
                reference_replicas,
                timing_absolute_tolerance=self.config.timing_absolute_tolerance,
                max_relative_wirelength_regression=self.config.max_relative_wirelength_regression,
                max_relative_runtime_regression=self.config.max_relative_runtime_regression,
                minimum_lower_bound=self.config.promotion_min_score,
                bootstrap_samples=self.config.bootstrap_samples,
                seed=self.config.seed + int(policy.identifier[:8], 16),
            )
            score = score_candidate(aggregate, median_metrics(reference_replicas))
        return self._record(
            policy,
            run_dir,
            reasons,
            metrics=aggregate.raw,
            score=score,
            replicas=[item.raw for item in replica_metrics],
            promotion=None if promotion is None else {
                "promotable": promotion.promotable,
                "median_score": promotion.median_score,
                "lower_confidence_bound": promotion.lower_confidence_bound,
                "reasons": promotion.reasons,
            },
        )

    @staticmethod
    def _baseline_replicas(baseline: Evaluation | None) -> list[FlowMetrics]:
        if baseline is None:
            return []
        if baseline.replicas:
            return [FlowMetrics(item) for item in baseline.replicas]
        if baseline.metrics is not None:
            return [FlowMetrics(baseline.metrics)]
        raise ValueError("baseline evaluation does not contain metrics")

    def _write_manifest(self, policy: MirrorPolicy, directory: Path) -> None:
        """Persist the complete reproducibility and containment contract."""
        header = policy.to_header().encode()
        manifest = {
            "candidate": policy.to_dict(),
            "candidate_id": policy.identifier,
            "candidate_header_sha256": sha256(header).hexdigest(),
            "config_path": str(self.config.path),
            "config_sha256": self.config.fingerprint,
            "openroad_revision": self.config.pinned_openroad_revision,
            "orfs_revision": self.config.pinned_orfs_revision,
            "opt_mirror_sha256": self.config.pinned_opt_mirror_sha256,
            "design_config": self.config.design_config,
            "platform": self.config.platform,
            "design_name": self.config.design_name,
            "flow_seeds": self.config.flow_seeds,
            "created_at": datetime.now(timezone.utc).isoformat(),
        }
        (directory / "manifest.json").write_text(json.dumps(manifest, indent=2, sort_keys=True))

    def _record(
        self,
        policy: MirrorPolicy,
        directory: Path,
        reasons: list[str],
        *,
        metrics: dict | None = None,
        score: float | None = None,
        replicas: list[dict] | None = None,
        promotion: dict | None = None,
    ) -> Evaluation:
        result = Evaluation(
            policy,
            not reasons,
            score,
            reasons,
            metrics,
            directory,
            replicas or [],
            promotion,
        )
        (directory / "result.json").write_text(
            json.dumps(
                {
                    "policy": policy.to_dict(),
                    "identifier": policy.identifier,
                    "valid": result.valid,
                    "score": score,
                    "reasons": reasons,
                    "metrics": metrics,
                    "replicas": result.replicas,
                    "promotion": promotion,
                    "finished_at": datetime.now(timezone.utc).isoformat(),
                },
                indent=2,
                sort_keys=True,
            )
        )
        return result
