"""An isolated OpenROAD worktree that keeps upstream submodules pristine."""

from __future__ import annotations

from hashlib import sha256
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

    @staticmethod
    def _output(args: list[str], *, cwd: Path) -> str:
        return subprocess.run(args, cwd=cwd, check=True, text=True, capture_output=True).stdout

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
        temporary = self.header_path.with_suffix(".h.tmp")
        try:
            temporary.write_text(policy.to_header())
            temporary.replace(self.header_path)
        finally:
            temporary.unlink(missing_ok=True)

    def assert_integrity(self, expected_policy: MirrorPolicy | None = None) -> None:
        """Reject any source state beyond the fixed patch and generated header.

        This is the source-containment boundary. The search never applies a
        model-proposed diff: a candidate may only replace the generated header
        after this method confirms the pinned upstream commit, every nested
        submodule, the safety guard, and the allowed dirty-file set.
        """
        head = self._output(["git", "rev-parse", "HEAD"], cwd=self.source_dir).strip()
        if head != self.config.pinned_openroad_revision:
            raise RuntimeError(
                "OpenROAD worktree revision differs from the configured pinned revision: "
                f"{head} != {self.config.pinned_openroad_revision}"
            )
        orfs_head = self._output(["git", "rev-parse", "HEAD"], cwd=self.config.orfs_root).strip()
        if orfs_head != self.config.pinned_orfs_revision:
            raise RuntimeError(
                "ORFS revision differs from the configured pinned revision: "
                f"{orfs_head} != {self.config.pinned_orfs_revision}"
            )
        orfs_diff = subprocess.run(
            ["git", "diff", "--quiet"], cwd=self.config.orfs_root, text=True
        ).returncode
        if orfs_diff != 0:
            raise RuntimeError("ORFS tracked files are modified; evaluation requires the pinned flow")
        submodules = self._output(
            ["git", "submodule", "status", "--recursive"], cwd=self.source_dir
        ).splitlines()
        invalid_submodules = [line for line in submodules if line and line[0] != " "]
        if invalid_submodules:
            raise RuntimeError("uninitialized or changed OpenROAD submodule: " + invalid_submodules[0])

        target = self.source_dir / "src/dpl/src/OptMirror.cpp"
        source = target.read_text()
        actual_hash = sha256(source.encode()).hexdigest()
        if actual_hash != self.config.pinned_opt_mirror_sha256:
            raise RuntimeError("OptMirror.cpp differs from the pinned fixed safety seam")
        required = (
            "EvolvedMirrorPolicy.h",
            "EvolvedMirrorPolicy::enabled()",
            "if (hpwl_after > hpwl_before)",
            "isEdgeSpacingLegal(cell, orient_my)",
        )
        missing = [item for item in required if item not in source]
        if missing:
            raise RuntimeError("OptMirror safety seam is incomplete: " + ", ".join(missing))

        status = self._output(["git", "status", "--porcelain"], cwd=self.source_dir).splitlines()
        allowed = {
            " M src/dpl/src/OptMirror.cpp",
            "?? src/dpl/src/EvolvedMirrorPolicy.h",
        }
        unexpected = [line for line in status if line not in allowed]
        if unexpected:
            raise RuntimeError("unexpected source mutation in evaluation worktree: " + unexpected[0])
        if expected_policy is not None:
            header = self.header_path.read_text() if self.header_path.exists() else ""
            if header != expected_policy.to_header():
                raise RuntimeError("generated policy header does not match the candidate contract")
        self._run(["git", "diff", "--check"], cwd=self.source_dir)
