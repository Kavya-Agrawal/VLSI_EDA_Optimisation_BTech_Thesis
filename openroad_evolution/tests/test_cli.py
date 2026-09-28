import json
from pathlib import Path
import tempfile
import unittest

from openroad_evolution.candidate import MirrorPolicy
from openroad_evolution.cli import _load_archived_policy


class CliTest(unittest.TestCase):
    def test_load_archived_policy_uses_top_level_identifier(self):
        policy = MirrorPolicy(1.25, -0.5, enabled=True)
        with tempfile.TemporaryDirectory() as tmp:
            archive = Path(tmp) / "archive.jsonl"
            archive.write_text(json.dumps({"identifier": policy.identifier, "policy": policy.to_dict()}) + "\n")
            self.assertEqual(_load_archived_policy(archive, policy.identifier), policy)


if __name__ == "__main__":
    unittest.main()
