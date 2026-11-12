Write the algorithm dossier for the Resizer cluster **{{CLUSTER}}** (Markdown, 300-700 lines). This document is
the main context a coding agent gets before it tries to replace or redesign this algorithm, so it must explain
the *problem*, the *current method* and its *trade-offs* so well that an engineer could propose a different
approach without re-reading the code.

Question this cluster answers: {{QUESTION}}

Files the cluster owns (editable by the agent):
{{EDITABLE}}
Read-only context files it depends on: {{READONLY}}
Related regression tests: {{TESTS}}

Required sections:
# Cluster {{CLUSTER}}
## 1. The problem (formal-ish)
Inputs, outputs, objective (what in WNS/TNS/area terms), constraints, where it is called from and how often.
## 2. Current algorithm, step by step
Pseudo-code with real function names; every heuristic, threshold, magic constant and ordering decision called out
(file:line). Complexity. What it is greedy about. What it never considers.
## 3. Interaction with the timer and other clusters
What timing is queried, what gets invalidated, how results feed the next move.
## 4. Known weaknesses and failure modes (from the code and from the tests)
## 5. Alternative approaches from the literature
Short, concrete: e.g. Lagrangian-relaxation gate sizing, TILOS-style sensitivity, slack budgeting, van Ginneken /
Lillis buffering with cost, timing-driven ECO, global vs local search, lookahead, machine-learned cost models.
For each: what would change in this code, expected gain, risk.
## 6. Safe-change checklist for this cluster
What must stay true (journaling, legality, determinism, equivalence), which tests to run, how to see the effect
in the evaluator's path report.

Per-file cards (already written; use them, verify against code when in doubt):
{{CARDS}}
Output only the Markdown.
