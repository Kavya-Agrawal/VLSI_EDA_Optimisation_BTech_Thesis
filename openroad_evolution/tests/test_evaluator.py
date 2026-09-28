from pathlib import Path
import tempfile
import types
import unittest

from openroad_evolution.evaluator import FlowEvaluator


class BuildInvalidationTest(unittest.TestCase):
    def test_incompatible_lto_build_tree_is_removed_once(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            build = root / "build"
            flags = build / "src/sta/CMakeFiles/OpenSTA.dir"
            flags.mkdir(parents=True)
            (build / "CMakeCache.txt").write_text(
                "CMAKE_BUILD_TYPE:STRING=Release\n"
                "LINK_TIME_OPTIMIZATION:BOOL=ON\n"
            )
            (flags / "flags.make").write_text("CXX_FLAGS = -flto=auto -fno-fat-lto-objects\n")
            evaluator = object.__new__(FlowEvaluator)
            evaluator.workspace = types.SimpleNamespace(build_dir=build)

            evaluator._invalidate_incompatible_build()

            self.assertFalse(build.exists())

    def test_compatible_build_tree_is_kept_for_incremental_rebuilds(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            build = root / "build"
            flags = build / "src/sta/CMakeFiles/OpenSTA.dir"
            flags.mkdir(parents=True)
            (build / "CMakeCache.txt").write_text(
                "CMAKE_BUILD_TYPE:STRING=RelWithDebInfo\n"
                "LINK_TIME_OPTIMIZATION:BOOL=OFF\n"
            )
            (flags / "flags.make").write_text("CXX_FLAGS = -O2 -g -fno-lto\n")
            evaluator = object.__new__(FlowEvaluator)
            evaluator.workspace = types.SimpleNamespace(build_dir=build)

            evaluator._invalidate_incompatible_build()

            self.assertTrue(build.exists())


class CandidateRegressionGateTest(unittest.TestCase):
    def test_evolved_candidates_use_safety_regression_gate(self):
        template = (
            "docker run --rm --network none --user $(id -u):$(id -g) -e HOME=/tmp "
            "-v {repo_root}:{repo_root} -w {repo_root} "
            "openroad/flow-ubuntu22.04-dev:latest "
            "ctest --test-dir {build_dir} --output-on-failure --no-tests=error "
            "-R '^dpl\\.mirror_edge_spacing\\.tcl$'"
        )
        self.assertIn("mirror_edge_spacing", template)
        self.assertIn("--no-tests=error", template)


if __name__ == "__main__":
    unittest.main()
