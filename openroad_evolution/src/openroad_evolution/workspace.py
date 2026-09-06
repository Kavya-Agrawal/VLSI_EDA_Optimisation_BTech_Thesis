"""An isolated OpenROAD worktree that keeps upstream submodules pristine."""

from __future__ import annotations

from pathlib import Path
import subprocess

from .candidate import MirrorPolicy
from .config import ExperimentConfig


class OpenRoadWorkspace:
    def __init__(self, config: ExperimentConfig):
        self.config = config
        self.source_dir = config.workspace / "openroad-source"
        self.build_dir = Path(
            config.format(config.build_dir_template, source_dir=self.source_dir, build_dir=config.workspace / "build")
        )
        self.header_path = self.source_dir / "src/dpl/src/EvolvedMirrorPolicy.h"

    @staticmethod
    def _run(args: list[str], *, cwd: Path | None = None) -> None:
        subprocess.run(args, cwd=cwd, check=True, text=True)

    def prepare(self) -> None:
        if not self.config.openroad_source.exists():
            raise FileNotFoundError(f"OpenROAD source is missing: {self.config.openroad_source}")
        if not self.config.orfs_root.exists():
            raise FileNotFoundError(f"ORFS source is missing: {self.config.orfs_root}")
        if not self.config.patch.exists():
            raise FileNotFoundError(f"policy patch is missing: {self.config.patch}")

        self.config.workspace.mkdir(parents=True, exist_ok=True)
        if not self.source_dir.exists():
            self._run(
                [
                    "git",
                    "-C",
                    str(self.config.openroad_source),
                    "worktree",
                    "add",
                    "--detach",
                    str(self.source_dir),
                    "HEAD",
                ]
            )

        # A Git worktree has its own submodule working directories. The source
        # checkout may already have all submodules, but they are not present in
        # this worktree until explicitly initialized. CMake needs OpenSTA and
        # ABC from those paths, so make this part of preparation rather than an
        # undocumented manual prerequisite.
        self._run(
            ["git", "submodule", "update", "--init", "--recursive", "--jobs", "1"],
            cwd=self.source_dir,
        )

        target = self.source_dir / "src/dpl/src/OptMirror.cpp"
        marker = "EvolvedMirrorPolicy.h"
        if marker not in target.read_text():
            self._run(["git", "apply", "--check", str(self.config.patch)], cwd=self.source_dir)
            self._run(["git", "apply", str(self.config.patch)], cwd=self.source_dir)
        self.write_policy(MirrorPolicy.baseline())

    def write_policy(self, policy: MirrorPolicy) -> None:
        policy.validate()
        self.header_path.write_text(policy.to_header())
