"""JSON configuration with paths resolved relative to the configuration file."""

from __future__ import annotations

from dataclasses import dataclass
import json
from pathlib import Path


@dataclass(frozen=True)
class ExperimentConfig:
    path: Path
    openroad_source: Path
    orfs_root: Path
    workspace: Path
    patch: Path
    build_dir_template: str
    openroad_executable_template: str
    jobs: int
    build_command: str
    unit_test_command: str
    flow_command: str
    metrics_path_template: str
    full_flow: bool
    seed: int

    @classmethod
    def load(cls, path: str | Path) -> "ExperimentConfig":
        path = Path(path).resolve()
        raw = json.loads(path.read_text())
        root = path.parent

        def resolve(name: str) -> Path:
            return (root / raw[name]).resolve()

        return cls(
            path=path,
            openroad_source=resolve("openroad_source"),
            orfs_root=resolve("orfs_root"),
            workspace=resolve("workspace"),
            patch=resolve("patch"),
            build_dir_template=raw["build_dir"],
            openroad_executable_template=raw["openroad_executable"],
            jobs=int(raw.get("jobs", 4)),
            build_command=raw["build_command"],
            unit_test_command=raw["unit_test_command"],
            flow_command=raw["flow_command"],
            metrics_path_template=raw["metrics_path"],
            full_flow=bool(raw.get("full_flow", True)),
            seed=int(raw.get("seed", 1)),
        )

    def format(self, template: str, *, source_dir: Path, build_dir: Path) -> str:
        return template.format(
            source_dir=source_dir,
            orfs_root=self.orfs_root,
            workspace=self.workspace,
            build_dir=build_dir,
            openroad_executable=self.openroad_executable_template.format(
                build_dir=build_dir
            ),
            jobs=self.jobs,
        )
