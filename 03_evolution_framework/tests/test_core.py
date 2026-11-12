"""Fast unit tests: no OpenROAD, no Claude. `make test`."""
import json
from pathlib import Path

from rszevolve.budget import Budget
from rszevolve.config import Knobs
from rszevolve.eval.build import _parse
from rszevolve.eval.paths import classify, diff_against
from rszevolve.eval.score import judge
from rszevolve.agents.claude_runner import extract_json_block


def agg(wns, tns, hold=0.05, drv=0, area=100.0, pv=0, det=True):
    return {"ok": True, "period_ns": 1.0, "endpoints": 100, "deterministic": det,
            "post": {"wns_setup": {"mean": wns}, "tns_setup": {"mean": tns}, "wns_hold": {"mean": hold}, "drv": drv,
                     "area_um2": {"mean": area}, "placement_violations": pv}}


def test_score_rejects_no_gain_and_accepts_gain():
    k = Knobs()
    ref = {"d": agg(-0.2, -10.0)}
    assert not judge({"d": agg(-0.2, -10.0)}, ref, k).accepted
    v = judge({"d": agg(-0.1, -5.0)}, ref, k)
    assert v.accepted and v.score > 0


def test_score_guards():
    k = Knobs()
    ref = {"d": agg(-0.2, -10.0)}
    assert "hold" in " ".join(judge({"d": agg(-0.1, -5.0, hold=-0.1)}, ref, k).reasons)
    assert "DRV" in " ".join(judge({"d": agg(-0.1, -5.0, drv=3)}, ref, k).reasons)
    assert "placement" in " ".join(judge({"d": agg(-0.1, -5.0, pv=2)}, ref, k).reasons)
    assert "area" in " ".join(judge({"d": agg(-0.1, -5.0, area=130.0)}, ref, k).reasons)
    assert "non-deterministic" in " ".join(judge({"d": agg(-0.1, -5.0, det=False)}, ref, k).reasons)
    assert "failed" in " ".join(judge({}, ref, k).reasons)


def test_budget_stops(tmp_path):
    b = Budget.load(tmp_path / "b.json", budget_usd=1.0)
    b.charge(role="planner", iteration=1, result={"total_cost_usd": 0.6, "usage": {"input_tokens": 10, "output_tokens": 5}})
    assert b.exhausted() is None
    b.charge(role="coder", iteration=1, result={"total_cost_usd": 0.5, "usage": {}})
    assert b.exhausted()
    assert Budget.load(tmp_path / "b.json").spent_usd > 1.0


def test_parse_compiler_errors():
    txt = "ERROR: foo\nsrc/rsz/src/RepairSetup.cc:12:5: error: use of undeclared identifier 'x'\n  x = 1;\n  ^\nsrc/rsz/src/A.cc:1:1: warning: unused\n"
    errs, warns = _parse(txt)
    assert len(errs) == 1 and "RepairSetup.cc:12:5" in errs[0] and "x = 1" in errs[0]
    assert len(warns) == 1


def test_path_classify_and_diff(tmp_path):
    p = {"stages": 20, "max_fanout": 10, "worst_slew": 0.1, "slack": -0.5, "startpoint": "a/Q", "endpoint": "b/D"}
    tags = classify(p, 1.0)
    assert {"deep_logic", "high_fanout", "slow_slew"} <= set(tags)
    c, r = tmp_path / "c", tmp_path / "r"
    c.mkdir(); r.mkdir()
    (c / "paths_post.json").write_text(json.dumps([{"endpoint": "e1", "slack": -0.1}, {"endpoint": "e3", "slack": -0.3}]))
    (r / "paths_post.json").write_text(json.dumps([{"endpoint": "e1", "slack": -0.2}, {"endpoint": "e2", "slack": -0.3}]))
    d = diff_against(c, r)
    assert d["improved"][0]["endpoint"] == "e1" and d["new_in_worst_list"] == ["e3"] and d["gone_from_worst_list"] == ["e2"]


def test_extract_json_block():
    assert extract_json_block("text\n```json\n{\"cluster\": \"sizing\"}\n```\n")["cluster"] == "sizing"
    assert extract_json_block("no json") is None
