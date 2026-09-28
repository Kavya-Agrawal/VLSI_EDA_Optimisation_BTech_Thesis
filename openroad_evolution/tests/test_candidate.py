import unittest

from openroad_evolution.candidate import MirrorPolicy, describe_program, program_segments, relation_graph


class MirrorPolicyTest(unittest.TestCase):
    def test_baseline_disables_ordering(self):
        header = MirrorPolicy.baseline().to_header()
        self.assertIn("return false", header)

    def test_source_is_deterministic_and_identified(self):
        policy = MirrorPolicy(1.0, -0.25)
        header = policy.to_header()
        self.assertIn(policy.identifier, header)
        self.assertIn("Segmented Semantic Program Evolution", header)
        self.assertIn("score += -0.25 * std::log1p", header)
        self.assertIn("std::log1p", header)
        self.assertNotIn("kIdWeight", header)
        self.assertEqual(policy, MirrorPolicy.from_dict(policy.to_dict()))

    def test_rejects_invalid_policy(self):
        with self.assertRaises(ValueError):
            MirrorPolicy(float("inf"), 0.0).validate()
        MirrorPolicy(0.0, 0.0, program=("mirror_entropy_temper",)).validate()
        with self.assertRaises(ValueError):
            MirrorPolicy(5.01, 0.0).validate()
        with self.assertRaises(ValueError):
            MirrorPolicy(0.0, 0.0, program=("unknown",)).validate()

    def test_segment_tree_describes_generated_code(self):
        program = ("hpwl_log", "mirror_entropy_temper", "deterministic_phase")
        self.assertEqual(
            program_segments(program),
            [(0, 3, "S"), (0, 1, "SL"), (1, 3, "SR"), (1, 2, "SRL"), (2, 3, "SRR")],
        )
        description = describe_program(program)
        self.assertIn("Mirror Entropy Tempering", description)
        self.assertIn("S[0:3]", description)
        self.assertIn("semantic-relation-graph", description)

    def test_relation_graph_tracks_dataflow_and_control_roles(self):
        graph = relation_graph(("hpwl_log", "hpwl_degree_cross", "fanout_shock_penalty"))
        self.assertEqual(graph["nodes"][1]["reads"], ["hpwl", "degree"])
        reasons = [reason for edge in graph["edges"] for reason in edge["reasons"]]
        self.assertIn("source_locality", reasons)
        self.assertIn("data_flow:hpwl,score", reasons)
        self.assertIn("data_flow:degree,score", reasons)
