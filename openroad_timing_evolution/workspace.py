"""Isolated local clones, byte-exact source containment, bounded subprocesses."""
from __future__ import annotations

import hashlib
import json
import os
from pathlib import Path
import signal
import subprocess
import time

ROOT = Path(__file__).resolve().parent
REPO = ROOT.parent
TARGET = "src/rsz/src/policy/SetupLegacyBase.cc"
HEADER = "src/rsz/src/policy/EvolvedPathDriverPolicy.h"


def sha(path):
    h = hashlib.sha256()
    with Path(path).open("rb") as f:
        for block in iter(lambda: f.read(1024*1024), b""):
            h.update(block)
    return h.hexdigest()


def output(args, cwd=None):
    return subprocess.check_output(args, cwd=cwd, text=True, stderr=subprocess.STDOUT).strip()


def run(args, log, timeout=7200, cwd=None):
    """No shell interpretation; kill the process group on timeout/interruption."""
    log = Path(log)
    log.parent.mkdir(parents=True, exist_ok=True)
    start = time.monotonic()
    with log.open("w") as stream:
        stream.write(json.dumps({"argv": [str(a) for a in args]}) + "\n")
        stream.flush()
        p = subprocess.Popen(args, stdout=stream, stderr=subprocess.STDOUT,
                             cwd=cwd, start_new_session=True)
        try:
            code = p.wait(timeout=timeout)
        except BaseException:
            os.killpg(p.pid, signal.SIGKILL)
            p.wait()
            raise
    if code:
        raise RuntimeError(f"command failed ({code}); see {log}")
    return time.monotonic() - start


def clone_local(source, dest, revision, recursive=True):
    """Clone only already available local commits; never fetch floating branches."""
    if not dest.exists():
        subprocess.run(["git", "clone", "--shared", "--no-checkout", str(source), str(dest)],
                       check=True, stdout=subprocess.DEVNULL)
        subprocess.run(["git", "checkout", "--detach", revision], cwd=dest, check=True,
                       stdout=subprocess.DEVNULL)
    if output(["git", "rev-parse", "HEAD"], dest) != revision:
        raise RuntimeError(f"wrong checkout: {dest}")
    if recursive:
        for line in output(["git", "ls-tree", "-r", "HEAD"], dest).splitlines():
            metadata, rel = line.split("\t", 1)
            mode, kind, commit = metadata.split()
            if mode == "160000":
                child = dest / rel
                if child.is_dir() and not any(child.iterdir()):
                    child.rmdir()
                clone_local(source / rel, child, commit)


class Workspace:
    def __init__(self, config):
        self.config = config
        self.work = ROOT / "work"
        self.source = self.work / "source"
        self.orfs = self.work / "orfs"
        self.work.mkdir(exist_ok=True)
        self.image = output(["docker", "image", "inspect", config["image"], "--format", "{{.Id}}"])
        if not self.image.startswith("sha256:"):
            raise RuntimeError("could not pin installed Docker image")

    def docker(self, argv, cwd="/experiment", name=None):
        args = ["docker", "run", "--rm", "--network", "none", "--cap-drop", "ALL",
                "--security-opt", "no-new-privileges", "--user", f"{os.getuid()}:{os.getgid()}",
                "--pids-limit", "1024", "--memory", "10g", "--cpus", str(self.config["jobs"]),
                "-e", "HOME=/tmp", "-v", f"{self.work}:/experiment",
                "-v", f"{ROOT}:/framework:ro", "-w", cwd]
        if name:
            args += ["--name", name]
        return args + [self.image, *argv]

    def execute(self, argv, log, cwd="/experiment", timeout=None):
        import uuid
        name = "rsz-evolve-" + uuid.uuid4().hex[:12]
        try:
            return run(self.docker(argv, cwd, name), log, timeout or self.config["timeout_seconds"])
        finally:
            # Killing a Docker CLI does not kill its container; explicitly clean it.
            subprocess.run(["docker", "rm", "-f", name], stdout=subprocess.DEVNULL,
                           stderr=subprocess.DEVNULL, timeout=30)

    def prepare(self):
        clone_local(REPO / "external/OpenROAD", self.source, self.config["openroad_revision"])
        clone_local(REPO / "external/OpenROAD-flow-scripts", self.orfs,
                    self.config["orfs_revision"], recursive=False)
        target = self.source / TARGET
        pristine = subprocess.check_output(["git", "show", "HEAD:"+TARGET], cwd=self.source)
        if target.read_bytes() == pristine:
            run(["git", "apply", "--check", str(ROOT / "patches/path_driver_policy.patch")], self.work/"patch-check.log", cwd=self.source)
            run(["git", "apply", str(ROOT / "patches/path_driver_policy.patch")], self.work/"patch.log", cwd=self.source)
        from .policy import Policy
        self.write_policy(Policy.stock())
        self.integrity(Policy.stock())

    def write_policy(self, policy):
        path = self.source / HEADER
        temporary = path.with_suffix(".tmp")
        temporary.write_text(policy.header())
        temporary.replace(path)

    def integrity(self, policy):
        if output(["git", "rev-parse", "HEAD"], self.source) != self.config["openroad_revision"]:
            raise RuntimeError("OpenROAD revision changed")
        expected_diff = (ROOT/"patches/path_driver_policy.patch").read_text().strip()
        if output(["git", "diff", "--no-ext-diff", "--no-color", "--", TARGET], self.source) != expected_diff:
            raise RuntimeError("source is not the byte-exact fixed seam")
        dirty = output(["git", "diff", "--name-only", "HEAD"], self.source).splitlines()
        if dirty != [TARGET]:
            raise RuntimeError(f"unexpected modified tracked source: {dirty}")
        untracked = output(["git", "ls-files", "--others", "--exclude-standard"], self.source).splitlines()
        if untracked != [HEADER]:
            raise RuntimeError(f"unexpected untracked source: {untracked}")
        if (self.source/HEADER).read_text() != policy.header():
            raise RuntimeError("generated header changed")
        def check_nested(path):
            for line in output(["git", "ls-tree", "-r", "HEAD"], path).splitlines():
                meta, rel = line.split("\t", 1)
                mode, _, commit = meta.split()
                if mode == "160000":
                    child = path/rel
                    if output(["git", "rev-parse", "HEAD"], child) != commit:
                        raise RuntimeError("nested source revision changed")
                    if output(["git", "status", "--porcelain", "--untracked-files=all"], child):
                        raise RuntimeError("nested source is dirty")
                    check_nested(child)
        check_nested(self.source)
        if output(["git", "rev-parse", "HEAD"], self.orfs) != self.config["orfs_revision"]:
            raise RuntimeError("ORFS revision changed")
        if output(["git", "diff", "HEAD"], self.orfs):
            raise RuntimeError("ORFS tracked input changed")

    def build(self, policy, directory):
        self.integrity(policy)
        self.execute(["cmake", "-S", "/experiment/source", "-B", "/experiment/build",
                      "-DCMAKE_BUILD_TYPE=Release", "-DENABLE_GUI=OFF", "-DENABLE_TESTS=ON",
                      "-DENABLE_GPU=OFF", "-DCMAKE_CXX_FLAGS=-march=x86-64 -mtune=generic"], directory/"configure.log")
        self.execute(["cmake", "--build", "/experiment/build", "--target", "openroad", "-j", str(self.config["jobs"])], directory/"build.log")
        binary = self.work/"build/bin/openroad"
        if binary.stat().st_size < 10000 or not os.access(binary, os.X_OK):
            raise RuntimeError("missing/empty/non-executable OpenROAD")
        self.execute(["/experiment/build/bin/openroad", "-version"], directory/"version.log", timeout=60)
        self.integrity(policy)
        return binary
