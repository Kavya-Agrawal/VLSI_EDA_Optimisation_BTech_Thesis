import unittest
from pathlib import Path

from openroad_evolution.config import ExperimentConfig


class ConfigTest(unittest.TestCase):
    def test_default_contract_formats_paired_seed_and_design(self):
        config = ExperimentConfig.load(Path("config/default.json"))
        self.assertEqual(config.replicates, 5)
        command = config.format(
            config.flow_command,
            source_dir=Path("/tmp/source"),
            build_dir=Path("/tmp/build"),
            candidate_id="candidate",
            replica=2,
        )
        self.assertIn("GPL_RANDOM_SEED=307", command)
        self.assertIn("DESIGN_CONFIG=designs/nangate45/gcd/config.mk", command)

    def test_held_out_contract_preserves_safety_parameters(self):
        config = ExperimentConfig.load(Path("config/default.json"))
        held_out = config.with_design(
            design_config="designs/nangate45/aes/config.mk",
            rules_json="designs/nangate45/aes/rules-base.json",
            platform="nangate45",
            design_name="aes",
        )
        self.assertEqual(held_out.flow_seeds, config.flow_seeds)
        self.assertEqual(held_out.design_name, "aes")
