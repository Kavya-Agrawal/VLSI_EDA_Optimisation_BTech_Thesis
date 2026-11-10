# OpenROAD Evolution Research Guide

This document records the repository and implementation context for the two
OpenROAD algorithm-evolution experiments: detailed-placement OptMirror
evolution and Resizer timing-closure evolution. It is intended both as a
research reference and as a handoff document for future contributors.

## Definitive Branch

The branch containing both complete frameworks is:

```text
research/openroad-evolution-suite
```

The current branch layout is:

| Branch or group | Contents | Relevance to these experiments |
| --- | --- | --- |
| `main` | Stable project guide, common documentation, and congestion CNN | Overview; not the definitive evolution implementation |
| `master` | Original ABC, macro-placement, and research workspace | Historical base |
| `research/openroad-evolution-suite` | OptMirror evolution, Resizer timing evolution, pinned OpenROAD/ORFS, tests, and presentations | Definitive branch for both experiments |
| `research/openroad-placement-safety` | Hardened OptMirror framework | Relevant milestone, superseded by the suite |
| `research/openroad-placement-evolution` | Initial OptMirror implementation | Pre-hardening historical milestone |
| `research/openroad-rl-gate-sizing` | PPO/GNN gate-sizing experiment | Related timing research, but not this evolutionary search |
| `research/openroad-timing-gnn` | Timing and slack prediction GNN | Prediction research, not this evolutionary search |
| `research/openroad-ml-landscape` | OpenROAD ML survey and branch map | Documentation only |
| `research/abc-synapse` | Neural-assisted ABC optimization | Unrelated to the two OpenROAD experiments |
| `research/abc-polyphony` | Generative/diverse ABC synthesis | Unrelated to the two OpenROAD experiments |
| `feature/*` | Older development versions of corresponding research branches | Prefer the clean `research/*` branches |
| `archive/*` | Initial imports and OpenROAD source snapshots | Historical only |

The placement code in `research/openroad-evolution-suite` matches the hardened
placement-safety branch, apart from retained presentation output. The suite is
the only branch that also contains the Resizer timing-evolution framework.

## Important Runtime Fact: No LLM Is Used

Neither framework currently invokes an LLM during proposal, mutation,
evaluation, ranking, or promotion. There are no OpenAI API calls, prompts,
model clients, or LLM judges in either implementation.

Both searches use deterministic, seeded mutations over constrained policy
representations. Compilation, tests, EDA flows, physical checks, timing
metrics, and formal tools evaluate candidates. An LLM or coding agent may have
helped author repository code, but it is not part of the runtime algorithm.

## Experiment 1: OptMirror Detailed-Placement Evolution

### OpenROAD algorithm being evolved

The target is OpenDP's `optimize_mirroring` detailed-placement heuristic,
specifically the order in which
`OptimizeMirroring::mirrorCandidates()` processes legal cell-mirroring
candidates.

The upstream implementation lives at:

```text
external/OpenROAD/src/dpl/src/OptMirror.cpp
```

The framework applies this fixed integration patch in an isolated worktree:

```text
openroad_evolution/patches/opt_mirror_policy.patch
```

The patch includes `EvolvedMirrorPolicy.h` and sorts `mirror_candidates` before
the existing loop. It does not replace candidate discovery, cell-edge-spacing
checks, or the existing non-increasing-HPWL acceptance rule.

The only per-candidate C++ artifact is generated at:

```text
openroad_evolution/work/openroad-source/src/dpl/src/EvolvedMirrorPolicy.h
```

Generated work and evidence are ignored by Git.

### Candidate representation

A candidate is a small generated C++ program assembled from audited statement
blocks. The current block library includes local-HPWL pressure, pin-degree
pressure, HPWL/degree cross terms, deterministic phase perturbation, and the
new **Mirror Entropy Tempering** heuristic:

```cpp
score += std::log1p(hpwl_delta);
score += -0.25 * std::log1p(std::fabs(static_cast<double>(pin_degree) - 4.0));
score += 0.12 * std::sin(static_cast<double>(stable_id % 97u));
```

The search evolves the source-level sequence of these blocks using insert,
delete, replace, swap, segment reverse, segment duplication, and numeric-weight
mutation. The segment operators implement **Segmented Semantic Program
Evolution**: each generated C++ block is a leaf, contiguous leaves form a
binary segment tree, and the search can mutate either a leaf or a whole subtree
of the generated program. Each leaf also carries typed metadata: variables read,
variables written, control role, and heuristic role. The framework builds a
semantic relation graph over the leaves, adding edges for source locality,
shared input/output variables, and matching control-flow roles. Graph-guided
mutation can swap related nodes or insert a bridge heuristic between related
nodes. Higher-priority candidates are attempted first.
Stable OpenDB instance ID is used only to break an exact tie. The generated
program is bounded to at most 16 audited blocks and finite weights in `[-5,
5]`. The disabled baseline preserves stock candidate order.

This is algorithm evolution rather than an ORFS knob sweep: it changes the
execution order of a non-commutative heuristic inside compiled OpenROAD code.
It cannot directly move cells, alter connectivity, create candidates, or
bypass the upstream legality and HPWL guards.

### Framework files

| File | Responsibility |
| --- | --- |
| `openroad_evolution/src/openroad_evolution/candidate.py` | `MirrorPolicy`, validation, IDs, and generated C++ header |
| `openroad_evolution/src/openroad_evolution/search.py` | Seeded mutation, population loop, parent selection, and archive writes |
| `openroad_evolution/src/openroad_evolution/evaluator.py` | Build, regressions, ORFS replicas, manifests, and results |
| `openroad_evolution/src/openroad_evolution/workspace.py` | Isolated OpenROAD worktree and source-integrity boundary |
| `openroad_evolution/src/openroad_evolution/metrics.py` | METRICS2.1 parsing, physical gates, scoring, and promotion |
| `openroad_evolution/src/openroad_evolution/config.py` | Validated experiment configuration and path resolution |
| `openroad_evolution/src/openroad_evolution/cli.py` | `prepare`, `evolve`, and `verify` commands |
| `openroad_evolution/config/default.json` | Pinned revisions, commands, designs, seeds, and thresholds |
| `openroad_evolution/tests/` | Fast framework tests that do not build OpenROAD |

### Evolution process

1. Evaluate the disabled stock-order baseline.
2. Begin with a short generated C++ policy such as `hpwl_log`.
3. Mutate either the numeric weights, one generated statement block, or a
   binary-tree source segment with insert, delete, replace, swap,
   segment-reverse, segment-duplicate, graph-swap, and graph-bridge operators.
4. Clamp weights to `[-5, 5]`, bound programs to 16 audited statements, and
   reject duplicate policy IDs.
5. Compile and evaluate every candidate against the paired stock baseline.
6. Rank all valid accumulated candidates by scalar score.
7. Retain up to the best four candidates as parents for the next generation.
8. Append baseline, successful candidates, and failures to
   `.evolution/archive.jsonl`.

The random seed is `41` in the default configuration.

### Correctness and containment process

Before measurement, the framework checks:

1. OpenROAD is exactly commit `63fe72c577ef12d2ac2a0a944bbd842f9af8a0a7`.
2. ORFS is exactly commit `68cc9bc974502b4786a68e9f51a092e0fcb56e82`.
3. Nested OpenROAD submodules are initialized, pinned, and clean.
4. `OptMirror.cpp` matches the configured SHA-256 after the fixed patch.
5. The safety seam still contains the policy call, HPWL rejection, and
   edge-spacing legality check.
6. The only allowed source changes are patched `OptMirror.cpp` and generated
   `EvolvedMirrorPolicy.h`.
7. The generated header exactly matches the candidate being evaluated.

Each candidate must then:

1. Compile into OpenROAD.
2. Pass `dpl.mirror1`, `mirror2`, `mirror3`, and `mirror_edge_spacing` tests.
3. Complete five paired, seed-controlled ORFS RTL-to-GDS runs.
4. Produce valid finite setup WNS/TNS, hold WNS/TNS, routed wirelength, and
   elapsed time.
5. Report zero detailed-placement violations, detailed-route DRC errors, and
   antenna-violating nets.

The five default flow seeds are `101`, `211`, `307`, `401`, and `503`. Training
uses Nangate45 `gcd`; held-out verification uses Nangate45 `aes` and `ibex`.

This is a strong empirical correctness screen, not a mathematical or formal
proof of logical equivalence.

### Fitness and promotion

The bounded scalar score is:

```text
0.30 * delta(setup WNS)
+ 0.25 * delta(setup TNS)
+ 0.15 * delta(hold WNS)
+ 0.15 * delta(hold TNS)
+ 0.10 * delta(routed wirelength)
+ 0.05 * delta(runtime)
```

Each signed normalized delta is clipped to `[-1, 1]`. Promotion additionally
requires no median setup/hold regression, no more than `0.5%` wirelength
regression, no more than `10%` runtime regression, a positive score on every
paired seed, and a paired 95% bootstrap lower bound greater than `0.002` using
at least 2,000 bootstrap samples.

### Evidence locations

```text
openroad_evolution/.evolution/archive.jsonl
openroad_evolution/.evolution/runs/<platform>/<design>/<candidate-id>/
openroad_evolution/work/openroad-source/
```

Each run archives the generated header, manifest, revision and configuration
hashes, logs, metrics, replicas, score, promotion decision, and rejection
reasons.

### Known OptMirror defect

The current held-out `verify` path has an archive lookup defect.
`EvolutionRun._append()` stores the ID in the top-level `identifier` field,
but `_load_archived_policy()` in `cli.py` checks
`record["policy"].get("identifier")`. The policy dictionary contains only
weights and `enabled`, so an otherwise valid candidate cannot be found.

The intended lookup is the top-level field:

```python
if record.get("identifier") == candidate_id:
```

Do not claim that held-out verification works until this is fixed and tested.

## Experiment 2: Resizer Timing-Closure Evolution

### OpenROAD algorithm being evolved

The target is the setup path-driver repair ordering inside OpenROAD Resizer's
`SetupLegacyBase::repairPath()`:

```text
external/OpenROAD/src/rsz/src/policy/SetupLegacyBase.cc
```

Stock code collects path repair targets and ranks them primarily by load
delay. The fixed patch inserts a generated policy after stock target
collection and reorders only the existing targets.

```text
openroad_timing_evolution/patches/path_driver_policy.patch
```

The generated header in the isolated source clone is:

```text
openroad_timing_evolution/work/source/src/rsz/src/policy/EvolvedPathDriverPolicy.h
```

The policy cannot create, delete, or mutate timing objects. Target identity,
repair budgets, move generators, timing checks, and rollback remain controlled
by upstream Resizer code. This experiment does not evolve CTS; clock skew is
measured only as audit evidence.

### Candidate representation

Each policy is a small generated C++ program over normalized:

- `load`: stock load-delay ranking feature
- `fanout`: driver fanout
- `position`: original position in the stock ordering

The default representation evolves an ordered list of audited C++ statement
blocks. The library includes load pressure, nonlinear blending, front-loaded
relief, late-path focus, stability damping, and the new **Fanout Shock Path
Pressure** heuristic. That heuristic deliberately gives extra priority to
targets where normalized fanout suggests a repair can propagate through a wider
downstream cone:

```cpp
score += 0.35 * std::log1p(std::max(0.0, fanout)) * (1.0 + 0.25 * load);
```

Mutation edits the program sequence with replace, insert, delete, swap,
segment-reverse, and segment-duplicate operators. These segment operators are
the timing version of **Segmented Semantic Program Evolution**: load, fanout,
late-path, and damping blocks are leaves in a binary source tree, and whole
subtrees can be moved or repeated as one source region. Each timing leaf also
has typed read/write/control metadata, so the semantic relation graph can link
nearby nodes, nodes that share `load`, `fanout`, `position`, or `score`, and
nodes with matching conditional or straight-line control roles. Graph-guided
mutation uses those edges to swap related repair heuristics or insert a bridge
heuristic between connected nodes. For compatibility with older archive
entries, the framework can still read and evaluate legacy bounded expression
trees, but new candidates are generated as C++ program blocks. There is no
Python `eval`, arbitrary C++, or free-form source patch in the candidate
representation.

The resulting scores are sorted descending. Original index is the immutable
tie-breaker, preserving a strict weak ordering.

### Framework files

| File | Responsibility |
| --- | --- |
| `openroad_timing_evolution/policy.py` | Grammar, validation, policy IDs, rendering, and mutation |
| `openroad_timing_evolution/search.py` | Population search and sealed train/validation/test procedure |
| `openroad_timing_evolution/runner.py` | Candidate build, regressions, ORFS, audits, and evidence archive |
| `openroad_timing_evolution/workspace.py` | Pinned local clones, Docker execution, timeouts, and integrity checks |
| `openroad_timing_evolution/kernel.py` | Sanitized C++ compilation and Python/C++ differential testing |
| `openroad_timing_evolution/metrics.py` | Fail-closed evidence validation and timing score |
| `openroad_timing_evolution/__main__.py` | CLI entry point |
| `openroad_timing_evolution/cpp/policy.h.in` | Trusted generated-header template |
| `openroad_timing_evolution/cpp/check.cpp` | Standalone policy-kernel checker |
| `openroad_timing_evolution/tcl/audit.tcl` | Frozen stock-binary STA and physical audit |
| `openroad_timing_evolution/config/smoke.json` | Pinned revisions, image, benchmark splits, and thresholds |
| `openroad_timing_evolution/tests/` | Grammar, metric, and runner configuration tests |

### Evolution process

1. Build and evaluate the disabled stock policy on training designs.
2. Seed the search with short generated C++ programs using load pressure,
   fanout shock, late-path focus, nonlinear blend, and stability damping.
3. Generate later candidates by mutating generated leaves or binary-tree source
   segments.
4. Reject duplicate candidate IDs and invalid generated programs.
5. Evaluate feasible candidates on training only.
6. Retain the best `population` candidates as parents.
7. Select a champion only when its worst observed training replicate gain is
   greater than `min_improvement`.
8. Freeze the champion before opening validation or test results.
9. Evaluate it on validation and then the sealed test split; held-out feedback
   never enters the parent population.

The default split is Nangate45 `gcd` for training, `aes` for validation, and
`ibex` for sealed testing, with three replicas per design.

### Correctness and evidence process

For every candidate, the framework performs:

1. Exact-key JSON parsing and bounded grammar validation.
2. Generation of the actual C++ header from a trusted template.
3. C++ compilation with ASan and UBSan.
4. More than 500 deterministic and randomized differential tests against the
   Python reference ordering.
5. Byte-exact validation of the fixed OpenROAD patch and generated header.
6. OpenROAD build inside a pinned, network-disabled Docker image.
7. Exact discovery and execution of five upstream Resizer regressions:
   `repair_setup_undo1`, `repair_setup_undo2`, `repair_setup_wns_guard`,
   `repair_hold1`, and `repair_hold2`.
8. A complete ORFS run producing synthesis Verilog, final Verilog, ODB, SDC,
   SPEF, and GDS.
9. Confirmation from logs that the candidate policy was actually exercised.
10. Independent STA and physical auditing with a frozen stock OpenROAD binary.
11. Yosys sequential formal equivalence between post-synthesis and final
    Verilog.
12. Parsing of a valid, empty KLayout DRC report.
13. Hash checks for the evaluator protocol, candidate binary, and frozen audit
    binary before and after measurement.

A candidate is rejected for any setup or hold WNS/TNS regression; any nonzero
placement, route DRC, antenna, maximum slew, maximum capacitance, or maximum
fanout violation; incomplete benchmark matrices; missing or nonfinite metrics;
or area, wirelength, and runtime beyond configured caps.

The smoke caps are `2%` area regression, `2%` wirelength regression, and `20%`
runtime regression. This is a single-corner Nangate45 experiment, not a full
MCMM signoff claim.

### Fitness

The paired setup-timing objective is:

```text
0.5 * delta(setup WNS) / clock_period
+ 0.5 * delta(setup TNS) / (clock_period * constrained_endpoint_count)
```

Per-design scores are replicate medians, and the reported score is the mean
across designs. The conservative observed lower value is the mean of each
design's worst replicate. It is not presented as a statistical confidence
interval.

### Evidence locations

```text
openroad_timing_evolution/work/runs/<campaign-id>/
```

The campaign stores its protocol, append-only archive, checkpoint, candidate
policies and headers, binaries and hashes, build/test/flow logs, metrics,
formal and DRC evidence, frozen finalist, split-opening records, and final
result.

The repository contains the framework and fast tests, but no committed proof
that a complete long-running timing QoR campaign has been executed. Generated
run evidence is intentionally ignored by Git.

## Running the Frameworks

Use Linux or WSL. The timing framework directly uses Linux APIs such as
`fcntl`, process groups, and `os.getuid()`, and it requires Docker. Native
Windows PowerShell is not a supported full-flow runtime.

First select the definitive branch and initialize pinned submodules:

```bash
git switch research/openroad-evolution-suite
git submodule update --init --recursive
make doctor
make list
```

For a first local branch creation from a remote-only checkout, use:

```bash
git switch --track origin/research/openroad-evolution-suite
```

### OptMirror commands

Fast framework tests:

```bash
make test-placement
```

Prepare the isolated patched OpenROAD worktree:

```bash
make prepare-placement
```

Run evolution:

```bash
make evolve-placement GENERATIONS=3 POPULATION=4
```

Equivalent direct commands from `openroad_evolution/` are:

```bash
PYTHONPATH=src python3 -m unittest discover -s tests -v
PYTHONPATH=src python3 -m openroad_evolution.cli --config config/default.json prepare
PYTHONPATH=src python3 -m openroad_evolution.cli --config config/default.json evolve --generations 3 --population 4
PYTHONPATH=src python3 -m openroad_evolution.cli --config config/default.json report
```

The intended held-out command is:

```bash
make verify-placement CANDIDATE=<training-promoted-id>
```

The archive lookup now uses the top-level candidate identifier recorded by the
search archive.

### Resizer timing-evolution commands

```bash
make test-timing-evolution
make doctor-timing-evolution
make prepare-timing-evolution
make baseline-timing-evolution
make evolve-timing-evolution GENERATIONS=3 POPULATION=4
```

Equivalent direct commands from the repository root are:

```bash
python3 -m openroad_timing_evolution selftest
python3 -m openroad_timing_evolution --config openroad_timing_evolution/config/smoke.json doctor
python3 -m openroad_timing_evolution --config openroad_timing_evolution/config/smoke.json prepare
python3 -m openroad_timing_evolution --config openroad_timing_evolution/config/smoke.json baseline
python3 -m openroad_timing_evolution --config openroad_timing_evolution/config/smoke.json evolve --generations 3 --population 4
python3 -m openroad_timing_evolution report
```

To create, check, and evaluate one explicit policy:

```bash
python3 -m openroad_timing_evolution propose --output candidate.json --seed 41
python3 -m openroad_timing_evolution check candidate.json
python3 -m openroad_timing_evolution evaluate candidate.json
```

The timing configuration expects the local Docker image
`openroad/flow-ubuntu22.04-dev:latest`. `doctor` pins its image ID and verifies
that CMake and Yosys are available inside it. The full runs are intentionally
long and require the complete ORFS/OpenROAD source submodules and PDK data.

## Research Interpretation

The central research claim should be phrased narrowly:

- OptMirror evolves an interpretable ordering policy for legal detailed-cell
  mirror attempts by compiling generated C++ policy code and evaluating it
  through repeated full physical-design runs.
- Resizer evolution searches generated C++ priority programs that reorder
  existing setup path-driver repair targets and uses formal, physical,
  electrical, and timing gates.
- The showpiece algorithm is Segmented Semantic Program Evolution: the evolved
  code is represented as audited C++ leaves plus a binary segment tree, so the
  search can evolve small code blocks and larger source regions without opening
  the door to arbitrary unsafe patches.
- The presentation-level extension is the semantic relation graph: code leaves
  are related by source locality, input/output sharing, and control-role
  similarity, giving the evolution loop a visible program-structure model
  without needing unrestricted C++ rewriting.
- Neither system performs unrestricted autonomous source-code rewriting.
- Neither system currently uses an LLM in the search loop.
- OptMirror validation is empirical and does not include formal equivalence.
- Resizer validation includes Yosys formal equivalence, but remains a
  single-corner experiment rather than a complete silicon-signoff proof.

These distinctions matter when describing novelty, correctness, or results in
a thesis, presentation, or paper.
