"""Seeded tree evolution with disjoint training, validation and sealed test sets."""
from __future__ import annotations

import random

from .metrics import Rejected, assess
from .policy import Policy, mutate


def evolve(campaign, generations, population):
    if type(generations) is not int or type(population) is not int or min(generations,population)<1:
        raise ValueError("generations and population must be positive integers")
    cfg = campaign.config
    rng = random.Random(cfg["seed"])
    train = cfg["train"]
    baseline = campaign.baseline(train)  # failure stops the experiment
    parents = [(0.0, Policy.stock())]
    visited = {Policy.stock().id}
    champion = None
    seeds = ["load", ["add","load",["mul",0.25,"fanout"]],
             ["sub","load",["mul",0.25,"fanout"]],
             ["add","load",["mul",0.25,"position"]]]
    for generation in range(generations):
        for slot in range(population):
            parent = rng.choice(parents)[1]
            policy = Policy.from_dict({"enabled":True,"expression":seeds.pop(0)}) if seeds else mutate(parent,rng)
            for _ in range(100):
                if policy.id not in visited:
                    break
                policy = mutate(parent,rng)
            else:
                raise RuntimeError("search exhausted unique proposals")
            visited.add(policy.id)
            context = {"generation":generation,"slot":slot,"parent_id":parent.id,"policy_id":policy.id}
            campaign.archive({**context,"status":"proposed","policy":policy.data()})
            try:
                rows = campaign.evaluate(policy,train)
                report = assess(baseline,rows,train,cfg,require_improvement=False)
                parents.append((report["score"],policy))
                parents.sort(key=lambda item:(-item[0],item[1].id))
                parents = parents[:population]
                if report["worst_repeat_gain"] > cfg["min_improvement"]:
                    if champion is None or report["score"] > champion[0]:
                        champion = (report["score"],policy)
                campaign.archive({**context,"status":"feasible","report":report})
            except (Rejected, RuntimeError, ValueError) as exc:
                campaign.archive({**context,"status":"rejected","reason":str(exc)})
            campaign.write("checkpoint.json", {"generation":generation,"slot":slot,
                           "visited":sorted(visited),"rng_state":rng.getstate(),
                           "parents":[{"score":s,"policy":p.data()} for s,p in parents]})
    if champion is None:
        result = {"status":"no_improving_policy","certified":False,
                  "reason":"No candidate passed repeatable training improvement"}
        campaign.write("result.json",result)
        return result
    # Freeze the training-selected policy before opening any held-out results.
    policy = champion[1]
    campaign.write("frozen-finalist.json", {"policy":policy.data(),"policy_id":policy.id})
    result = {"policy_id":policy.id,"certified":False,"status":"held_out_rejected"}
    try:
        for split in ("validation","test"):
            # No holdout feedback is ever returned to the evolutionary parent pool.
            campaign.write(f"{split}-opened.json", {"policy_id":policy.id,"designs":cfg[split]})
            base = campaign.baseline(cfg[split])
            rows = campaign.evaluate(policy,cfg[split])
            result[split] = assess(base,rows,cfg[split],cfg,require_improvement=False)
        result.update(status="experiment_passed",certified=True)
    except (Rejected,RuntimeError,ValueError) as exc:
        result["reason"] = str(exc)
    campaign.write("result.json",result)
    return result
