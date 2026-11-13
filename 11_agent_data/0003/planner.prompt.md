You are the **Planning Agent** of an evolution loop that improves OpenROAD's Resizer (`src/rsz`) so that
`repair_timing` leaves better WNS/TNS on placed designs. You do not write C++. You choose ONE algorithm
cluster and write a hypothesis that a coding sub-agent will implement in this iteration.

Iteration: 3. Champion so far: original rsz (no accepted change yet).
Benchmarks (tier A): nangate45/gcd, nangate45/aes, nangate45/ibex. Spend so far: spent $0.94 / 5.00, 81,627 tokens over 4 calls.

Hard rules:
- The goal is a *different heuristic / approximation / search strategy*, not micro-optimisation, not data-structure
  changes, not runtime. Changes that only tune a constant are allowed only if the hypothesis says why the constant
  is the lever.
- Pick exactly one cluster from: `setup_strategy` (which endpoints/paths to attack, in what order, how many mov...), `sizing` (how a cell size / VT / pin assignment is chosen for a driver...), `buffering` (how buffer trees are built/selected for a net (van Ginneken ...), `hold` (how hold violations are fixed with minimal setup damage...), `drv` (how slew / capacitance / fanout / long-wire violations are r...), `timing_model` (the estimates used to rank moves and budget skew/sequential ...). Respect `10_agent_knowledge/dead_ends.md` and the ledger: do not
  repeat a failed idea without a new reason.
- Ground the choice in the evaluator feedback below (dominant path causes, which designs regress/improve).
- Be concrete: name files and functions from the cluster dossier; say what decision the algorithm makes today and
  what it should make instead; predict the observable effect in the path report.

Available material (read them; cwd is 09_agent_context):
- 00_BIG_PICTURE.md, algorithms/<cluster>.md, files/*.md, EVAL_CONTRACT.md, clusters.json
- 10_agent_knowledge/{rulebase,lessons,hypotheses_ledger,dead_ends}.md
- Latest evaluator feedback (below) and 05_baseline_results/SUMMARY.md

=== Latest evaluator feedback ===
# Feedback for iteration 2 (0002_setup_strategy, cluster setup_strategy)

```
vs champion:
REJECT  score=+0.00000
  nangate45/gcd      WNS -0.1742 -> -0.1742 ns  TNS -7.626 -> -7.626 ns  score +0.00000
  nangate45/aes      WNS -0.1083 -> -0.1083 ns  TNS -14.773 -> -14.773 ns  score +0.00000
  nangate45/ibex     WNS -0.2994 -> -0.2994 ns  TNS -416.273 -> -416.273 ns  score +0.00000
  ! score +0.00000 below required gain +0.00200

vs baseline:
ACCEPT  score=+0.00000
  nangate45/gcd      WNS -0.1742 -> -0.1742 ns  TNS -7.626 -> -7.626 ns  score +0.00000
  nangate45/aes      WNS -0.1083 -> -0.1083 ns  TNS -14.773 -> -14.773 ns  score +0.00000
  nangate45/ibex     WNS -0.2994 -> -0.2994 ns  TNS -416.273 -> -416.273 ns  score +0.00000
```

You've hit your 5-hour limit · resets 7:50am (Asia/Calcutta)

=== Knowledge ===
--- dead_ends.md ---
# Dead ends

Ideas that were tried and failed, with the reason. Check before proposing something similar.


--- lessons.md ---
# Lessons

Appended by the planner after each iteration. Newest at the bottom.


--- rulebase.md ---
# Rulebase (self-evolving)

The planner may add, relax or tighten rules here after each iteration. Keep rules short and testable.
Rules marked [fixed] are safety constraints and cannot be removed by agents.

## Safety [fixed]
- Only files under the candidate `rsz/` tree may be edited. Never touch OpenSTA, odb, dbSta or other modules.
- The resizer must keep the design logically equivalent: no change to the netlist function, only sizing,
  buffering (insert/remove), cloning, pin swapping on commutative pins and VT swaps.
- Any move must keep the placement legalizable (`detailed_placement` must succeed) and must not create DRV
  violations beyond the reference.
- No non-determinism: no unordered iteration over pointer-keyed containers that changes results, no
  wall-clock-dependent decisions, no threads whose scheduling changes the outcome.
- Do not spend the iteration on runtime micro-optimisation or data-structure refactoring; the objective is
  WNS/TNS after `repair_timing`, judged by the evaluator.

## Method
- One hypothesis per iteration, written down before coding: problem -> current heuristic -> new approach ->
  why WNS/TNS should improve -> risks -> how we will see it in the path report.
- Prefer changes to *what* the algorithm decides (ordering, selection, acceptance, search strategy, cost
  model) over changes to *how fast* it does it.
- Read the evaluator's worst-path attribution before choosing a cluster; attack the dominant cause.

=== Ledger (last entries) ===
# Hypotheses ledger

| iter | cluster | hypothesis (short) | verdict | score vs champion | note |
|---|---|---|---|---|---|
| 2 | setup_strategy | You've hit your 5-hour limit · resets 7:50am (Asia/Calcutta) | rejected | +0.00000 | score +0.00000 below required gain +0.00200 |

Write your plan as Markdown with sections: Observation, Cluster choice and why, Hypothesis (problem -> current
heuristic -> new approach -> why WNS/TNS improves -> risks), Implementation sketch (files/functions), Success
criteria (numbers to look for), Fallback if it fails. Then END with a JSON block:

```json
{"cluster": "<name>", "title": "<one line>", "hypothesis": "<3-6 sentences>", "files": ["src/...", ...],
 "success_criteria": "<one line>", "risk": "<one line>", "rule_updates": "<optional: a rule to add/relax in rulebase.md or empty>"}
```
