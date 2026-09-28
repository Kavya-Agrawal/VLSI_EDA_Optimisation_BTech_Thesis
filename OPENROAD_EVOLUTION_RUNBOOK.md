# OpenROAD Evolution Runbook

This is the shortest path for running both real OpenROAD evolution frameworks and showing original-vs-evolved results.

## Sync and setup

```bash
git switch research/openroad-evolution-suite
git pull --ff-only --recurse-submodules
git submodule update --init --recursive
make doctor
make test-placement
make test-timing-evolution
```

## Run both full-flow evolutions

Run 40 new candidates for both frameworks:

```bash
make run-both N=40
```

Run 80 more later:

```bash
make run-both N=80
```

The second command continues from the archives. It does not overwrite the first 40 candidates. After both commands, the archives contain 120 attempted candidates per framework, plus stock baselines and held-out verification records where applicable.

You can also run one framework at a time:

```bash
make run-placement N=40
make run-timing N=40
```

## Show the results

```bash
make results
```

This prints and writes concise comparison reports:

- OptMirror placement: `openroad_evolution/.evolution/summary.md`
- Resizer timing: `openroad_timing_evolution/work/memory/summary.md`

Each report shows:

- original non-evolved policy summary
- evolved policy summary
- original source summary versus evolved generated C++ source summary
- candidate ID
- score or promotion status
- original-vs-evolved metrics from archived full-flow evidence
- evidence archive and run-directory locations

## Evidence locations

OptMirror placement:

```text
openroad_evolution/.evolution/archive.jsonl
openroad_evolution/.evolution/runs/
```

Resizer timing:

```text
openroad_timing_evolution/work/memory/archive.jsonl
openroad_timing_evolution/work/runs/
```

Both frameworks are append-only at the archive level. New runs add new records and unique run directories. Candidate IDs already present in the archive are skipped on later invocations.

## What actually evolves

OptMirror evolves the generated OpenROAD header:

```text
openroad_evolution/work/openroad-source/src/dpl/src/EvolvedMirrorPolicy.h
```

The generated C++ sequence changes real scoring statements, including the
novel Mirror Entropy Tempering block. The patch seam keeps OpenDP legality and
non-increasing-HPWL guards in upstream code.

Resizer timing evolves the generated OpenROAD header:

```text
openroad_timing_evolution/work/source/src/rsz/src/policy/EvolvedPathDriverPolicy.h
```

The generated C++ sequence changes the priority program used to order setup
path-driver repairs, including the novel Fanout Shock Path Pressure block.
The patch seam keeps target generation, repair legality, rollback, timing
analysis, and physical checks in upstream OpenROAD code.

## Longer manual commands

OptMirror:

```bash
make prepare-placement
make evolve-placement GENERATIONS=3 POPULATION=4
make verify-placement CANDIDATE=<promoted-training-id>
make report-placement
```

Resizer timing:

```bash
make doctor-timing-evolution
make prepare-timing-evolution
make baseline-timing-evolution
make evolve-timing-evolution GENERATIONS=3 POPULATION=4
make report-timing-evolution
```

The full-flow commands are intentionally long-running. Both frameworks use the
local Docker image `openroad/flow-ubuntu22.04-dev:latest`. OptMirror builds
OpenROAD and runs full ORFS replicas in Docker. Resizer timing builds OpenROAD
in Docker, runs ORFS, audits with a frozen stock binary, checks formal
equivalence and parses DRC evidence.
