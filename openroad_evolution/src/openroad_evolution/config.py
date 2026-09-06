"""JSON configuration with paths resolved relative to the configuration file."""

from __future__ import annotations

from dataclasses import dataclass, replace
from hashlib import sha256
import json
import math
from pathlib import Path
import re


@dataclass(frozen=True)
class ExperimentConfig:
    path: Path
    openroad_source: Path
    orfs_root: Path
    workspace: Path
    patch: Path
    pinned_openroad_revision: str
    pinned_orfs_revision: str
    pinned_opt_mirror_sha256: str
    build_dir_template: str
    openroad_executable_template: str
    jobs: int
    build_command: str
    unit_test_command: str
    flow_command: str
    metrics_path_template: str
    full_flow: bool
    design_config: str
    rules_json: str
    platform: str
    design_name: str
    flow_seeds: tuple[int, ...]
    bootstrap_samples: int
    promotion_min_score: float
    timing_absolute_tolerance: float
    max_relative_wirelength_regression: float
    max_relative_runtime_regression: float
    seed: int

    @classmethod
    def load(cls, path: str | Path) -> "ExperimentConfig":
        path = Path(path).resolve()
        raw = json.loads(path.read_text())
        root = path.parent

        def resolve(name: str) -> Path:
            return (root / raw[name]).resolve()

        config = cls(
            path=path,
            openroad_source=resolve("openroad_source"),
            orfs_root=resolve("orfs_root"),
            workspace=resolve("workspace"),
            patch=resolve("patch"),
            pinned_openroad_revision=raw["pinned_openroad_revision"],
            pinned_orfs_revision=raw["pinned_orfs_revision"],
            pinned_opt_mirror_sha256=raw["pinned_opt_mirror_sha256"],
            build_dir_template=raw["build_dir"],
            openroad_executable_template=raw["openroad_executable"],
            jobs=int(raw.get("jobs", 4)),
            build_command=raw["build_command"],
            unit_test_command=raw["unit_test_command"],
            flow_command=raw["flow_command"],
            metrics_path_template=raw["metrics_path"],
            full_flow=bool(raw.get("full_flow", True)),
            design_config=str(raw["design_config"]),
            rules_json=str(raw["rules_json"]),
            platform=str(raw["platform"]),
            design_name=str(raw["design_name"]),
            flow_seeds=tuple(int(value) for value in raw["flow_seeds"]),
            bootstrap_samples=int(raw.get("bootstrap_samples", 2000)),
            promotion_min_score=float(raw.get("promotion_min_score", 0.002)),
            timing_absolute_tolerance=float(raw.get("timing_absolute_tolerance", 0.0)),
            max_relative_wirelength_regression=float(raw.get("max_relative_wirelength_regression", 0.005)),
            max_relative_runtime_regression=float(raw.get("max_relative_runtime_regression", 0.10)),
            seed=int(raw.get("seed", 1)),
        )
        config.validate()
        return config

    @property
    def replicates(self) -> int:
        return len(self.flow_seeds)

    @property
    def fingerprint(self) -> str:
        """Stable digest of the experiment contract recorded with every run."""
        return sha256(self.path.read_bytes()).hexdigest()

    def validate(self) -> None:
        revision = re.compile(r"[0-9a-f]{40}\Z")
        for name, value in (
            ("pinned_openroad_revision", self.pinned_openroad_revision),
            ("pinned_orfs_revision", self.pinned_orfs_revision),
        ):
            if not revision.fullmatch(value):
                raise ValueError(f"{name} must be a 40-character lowercase Git revision")
        if not re.fullmatch(r"[0-9a-f]{64}", self.pinned_opt_mirror_sha256):
            raise ValueError("pinned_opt_mirror_sha256 must be a SHA-256 digest")
        if self.jobs < 1:
            raise ValueError("jobs must be positive")
        if len(self.flow_seeds) < 5 or len(set(self.flow_seeds)) != len(self.flow_seeds):
            raise ValueError("flow_seeds must contain at least five unique seeds")
        if any(value < 0 for value in self.flow_seeds):
            raise ValueError("flow_seeds must be non-negative")
        if self.bootstrap_samples < 2_000:
            raise ValueError("bootstrap_samples must be at least 2000")
        finite_nonnegative = (
            ("promotion_min_score", self.promotion_min_score),
            ("timing_absolute_tolerance", self.timing_absolute_tolerance),
            ("max_relative_wirelength_regression", self.max_relative_wirelength_regression),
            ("max_relative_runtime_regression", self.max_relative_runtime_regression),
        )
        if any(not math.isfinite(value) or value < 0 for _, value in finite_nonnegative):
            raise ValueError("promotion thresholds and regression budgets must be finite and non-negative")
        if not all((self.design_config, self.rules_json, self.platform, self.design_name)):
            raise ValueError("design_config, rules_json, platform, and design_name are required")

    def with_design(
        self,
        *,
        design_config: str,
        rules_json: str,
        platform: str,
        design_name: str,
    ) -> "ExperimentConfig":
        """Return a checked evaluation contract for a held-out ORFS design."""
        config = replace(
            self,
            design_config=design_config,
            rules_json=rules_json,
            platform=platform,
            design_name=design_name,
        )
        config.validate()
        return config

    def format(
        self,
        template: str,
        *,
        source_dir: Path,
        build_dir: Path,
        candidate_id: str = "stock",
        replica: int = 0,
        flow_seed: int | None = None,
    ) -> str:
        return template.format(
            source_dir=source_dir,
            orfs_root=self.orfs_root,
            workspace=self.workspace,
            build_dir=build_dir,
            openroad_executable=self.openroad_executable_template.format(
                build_dir=build_dir
            ),
            jobs=self.jobs,
            candidate_id=candidate_id,
            replica=replica,
            flow_seed=self.flow_seeds[replica] if flow_seed is None else flow_seed,
            design_config=self.design_config,
            rules_json=self.rules_json,
            platform=self.platform,
            design_name=self.design_name,
        )
