import tempfile
import unittest
from pathlib import Path

from openroad_timing_evolution.runner import load_config


class ConfigTests(unittest.TestCase):
    def test_config_rejects_overlapping_splits(self):
        text = (Path(__file__).parents[1] / "config/smoke.json").read_text()
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "bad.json"
            path.write_text(text.replace('"test": ["ibex"]', '"test": ["gcd"]'))
            with self.assertRaises(ValueError):
                load_config(path)

    def test_default_config_loads(self):
        cfg = load_config(Path(__file__).parents[1] / "config/smoke.json")
        self.assertEqual(cfg["train"], ["gcd"])
        self.assertGreaterEqual(cfg["replicates"], 3)


if __name__ == "__main__":
    unittest.main()
