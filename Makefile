SHELL := /bin/bash

PYTHON ?= python3
JOBS ?= 4
GENERATIONS ?= 3
POPULATION ?= 4
FRAMEWORK ?=
ACTION ?= test
CANDIDATE ?=
DESIGN_CONFIG ?= designs/nangate45/gcd/config.mk

.DEFAULT_GOAL := help

.PHONY: help list status doctor setup test test-all framework branch \
	test-placement test-timing-evolution test-congestion-cnn test-rl-gatesize \
	test-timing-gnn test-synapse test-polyphony \
	prepare-placement evolve-placement verify-placement \
	doctor-timing-evolution prepare-timing-evolution baseline-timing-evolution evolve-timing-evolution \
	train-congestion-cnn train-rl-gatesize train-timing-gnn train-synapse train-polyphony \
	abc-build openroad-flow openroad-shell

help:
	@printf '%s\n' \
	  'VLSI EDA thesis workspace' \
	  '' \
	  'Start here:' \
	  '  make list                         Show frameworks and their branches' \
	  '  make test                         Test every framework on this branch' \
	  '  make framework FRAMEWORK=<name>   Test one framework' \
	  '  make branch FRAMEWORK=<name>      Switch to its recommended branch' \
	  '  make doctor                       Check local prerequisites' \
	  '  make setup                        Initialize pinned Git submodules' \
	  '' \
	  'Evolution runs:' \
	  '  make evolve-placement [GENERATIONS=3 POPULATION=4]' \
	  '  make evolve-timing-evolution [GENERATIONS=3 POPULATION=4]' \
	  '  make verify-placement CANDIDATE=<id>' \
	  '' \
	  'Other useful targets:' \
	  '  make abc-build [JOBS=4]' \
	  '  make train-<framework>' \
	  '  make openroad-flow [DESIGN_CONFIG=designs/.../config.mk]' \
	  '' \
	  'See PROJECT_GUIDE.md for examples and directory descriptions.'

list:
	@printf '%-22s %-40s %s\n' 'FRAMEWORK' 'RECOMMENDED BRANCH' 'AVAILABLE HERE'; \
	printf '%-22s %-40s %s\n' 'placement' 'research/openroad-evolution-suite' "$$(test -d openroad_evolution && echo yes || echo no)"; \
	printf '%-22s %-40s %s\n' 'timing-evolution' 'research/openroad-evolution-suite' "$$(test -d openroad_timing_evolution && echo yes || echo no)"; \
	printf '%-22s %-40s %s\n' 'congestion-cnn' 'research/openroad-evolution-suite' "$$(test -d openroad_ml/congestion_cnn && echo yes || echo no)"; \
	printf '%-22s %-40s %s\n' 'rl-gatesize' 'research/openroad-rl-gate-sizing' "$$(test -d openroad_ml/rl_gatesize && echo yes || echo no)"; \
	printf '%-22s %-40s %s\n' 'timing-gnn' 'research/openroad-timing-gnn' "$$(test -d openroad_ml/timing_gnn && echo yes || echo no)"; \
	printf '%-22s %-40s %s\n' 'synapse' 'research/abc-synapse' "$$(test -d abc/src/ext_ml && echo yes || echo no)"; \
	printf '%-22s %-40s %s\n' 'polyphony' 'research/abc-polyphony' "$$(test -d abc/src/ext_poly && echo yes || echo no)"

status:
	@git status --short --branch
	@$(MAKE) --no-print-directory list

doctor:
	@command -v git >/dev/null && git --version
	@command -v $(PYTHON) >/dev/null && $(PYTHON) --version
	@command -v make >/dev/null && make --version | head -n 1
	@command -v docker >/dev/null && docker --version || printf '%s\n' 'optional: Docker is not installed'
	@git submodule status 2>/dev/null || true

setup:
	git submodule update --init --recursive

# Generic entry point. Example: make framework FRAMEWORK=timing-gnn
framework:
	@if [[ -z "$(FRAMEWORK)" ]]; then \
		echo 'FRAMEWORK is required. Run `make list` for names.' >&2; exit 2; \
	fi
	@$(MAKE) --no-print-directory "$(ACTION)-$(FRAMEWORK)"

branch:
	@if [[ -z "$(FRAMEWORK)" ]]; then echo 'FRAMEWORK is required. Run `make list`.' >&2; exit 2; fi
	@case "$(FRAMEWORK)" in \
		placement|timing-evolution|congestion-cnn) target='research/openroad-evolution-suite' ;; \
		rl-gatesize) target='research/openroad-rl-gate-sizing' ;; \
		timing-gnn) target='research/openroad-timing-gnn' ;; \
		synapse) target='research/abc-synapse' ;; \
		polyphony) target='research/abc-polyphony' ;; \
		*) echo "Unknown framework: $(FRAMEWORK)" >&2; exit 2 ;; \
	esac; \
	git switch "$$target" 2>/dev/null || git switch --track "origin/$$target"

test: test-all

test-all:
	@set -e; found=0; \
	for item in \
		'openroad_evolution:test-placement' \
		'openroad_timing_evolution:test-timing-evolution' \
		'openroad_ml/congestion_cnn:test-congestion-cnn' \
		'openroad_ml/rl_gatesize:test-rl-gatesize' \
		'openroad_ml/timing_gnn:test-timing-gnn' \
		'abc/src/ext_ml:test-synapse' \
		'abc/src/ext_poly:test-polyphony'; do \
		dir="$${item%%:*}"; target="$${item#*:}"; \
		if [[ -d "$$dir" ]]; then found=1; $(MAKE) --no-print-directory "$$target"; fi; \
	done; \
	if [[ $$found -eq 0 ]]; then echo 'No research framework is present on this branch.'; fi

test-placement:
	@test -d openroad_evolution || { echo 'Unavailable here; run: make branch FRAMEWORK=placement' >&2; exit 2; }
	cd openroad_evolution && PYTHONPATH=src $(PYTHON) -m unittest discover -s tests -v

test-timing-evolution:
	@test -d openroad_timing_evolution || { echo 'Unavailable here; run: make branch FRAMEWORK=timing-evolution' >&2; exit 2; }
	$(PYTHON) -m openroad_timing_evolution selftest

test-congestion-cnn:
	@test -d openroad_ml/congestion_cnn || { echo 'Unavailable here; run: make branch FRAMEWORK=congestion-cnn' >&2; exit 2; }
	@if ! $(PYTHON) -c 'import torch' >/dev/null 2>&1; then \
		echo 'SKIP congestion-cnn: install openroad_ml/congestion_cnn/requirements.txt'; \
	else cd openroad_ml/congestion_cnn && $(PYTHON) -m tests.smoke_test; fi

test-rl-gatesize:
	@test -d openroad_ml/rl_gatesize || { echo 'Unavailable here; run: make branch FRAMEWORK=rl-gatesize' >&2; exit 2; }
	@if ! $(PYTHON) -c 'import torch' >/dev/null 2>&1; then \
		echo 'SKIP rl-gatesize: install openroad_ml/rl_gatesize/requirements.txt'; \
	else cd openroad_ml/rl_gatesize && $(PYTHON) -m tests.smoke_test; fi

test-timing-gnn:
	@test -d openroad_ml/timing_gnn || { echo 'Unavailable here; run: make branch FRAMEWORK=timing-gnn' >&2; exit 2; }
	@if ! $(PYTHON) -c 'import torch' >/dev/null 2>&1; then \
		echo 'SKIP timing-gnn: install openroad_ml/timing_gnn/requirements.txt'; \
	else cd openroad_ml/timing_gnn && $(PYTHON) -m tests.smoke_test; fi

test-synapse:
	@test -d abc/src/ext_ml/python || { echo 'Unavailable here; run: make branch FRAMEWORK=synapse' >&2; exit 2; }
	@if ! $(PYTHON) -c 'import numpy' >/dev/null 2>&1; then \
		echo 'SKIP synapse: install abc/src/ext_ml/python/requirements.txt'; \
	else cd abc/src/ext_ml/python && $(PYTHON) -m tests.test_smoke; fi

test-polyphony:
	@test -d abc/src/ext_poly/python || { echo 'Unavailable here; run: make branch FRAMEWORK=polyphony' >&2; exit 2; }
	cd abc/src/ext_poly/python && $(PYTHON) -m tests.test_smoke

prepare-placement:
	@test -d openroad_evolution || { echo 'Unavailable here; run: make branch FRAMEWORK=placement' >&2; exit 2; }
	cd openroad_evolution && PYTHONPATH=src $(PYTHON) -m openroad_evolution.cli --config config/default.json prepare

evolve-placement:
	@test -d openroad_evolution || { echo 'Unavailable here; run: make branch FRAMEWORK=placement' >&2; exit 2; }
	cd openroad_evolution && PYTHONPATH=src $(PYTHON) -m openroad_evolution.cli --config config/default.json evolve --generations $(GENERATIONS) --population $(POPULATION)

verify-placement:
	@test -n "$(CANDIDATE)" || { echo 'CANDIDATE is required.' >&2; exit 2; }
	cd openroad_evolution && PYTHONPATH=src $(PYTHON) -m openroad_evolution.cli --config config/default.json verify --candidate "$(CANDIDATE)"

doctor-timing-evolution:
	@test -d openroad_timing_evolution || { echo 'Unavailable here; run: make branch FRAMEWORK=timing-evolution' >&2; exit 2; }
	$(PYTHON) -m openroad_timing_evolution doctor

prepare-timing-evolution:
	@test -d openroad_timing_evolution || { echo 'Unavailable here; run: make branch FRAMEWORK=timing-evolution' >&2; exit 2; }
	$(PYTHON) -m openroad_timing_evolution prepare

baseline-timing-evolution:
	@test -d openroad_timing_evolution || { echo 'Unavailable here; run: make branch FRAMEWORK=timing-evolution' >&2; exit 2; }
	$(PYTHON) -m openroad_timing_evolution baseline

evolve-timing-evolution:
	@test -d openroad_timing_evolution || { echo 'Unavailable here; run: make branch FRAMEWORK=timing-evolution' >&2; exit 2; }
	$(PYTHON) -m openroad_timing_evolution evolve --generations $(GENERATIONS) --population $(POPULATION)

train-congestion-cnn:
	cd openroad_ml/congestion_cnn && $(PYTHON) -m train.train --epochs 2 --synthetic

train-rl-gatesize:
	cd openroad_ml/rl_gatesize && $(PYTHON) -m train.train_ppo --episodes 5 --mock

train-timing-gnn:
	cd openroad_ml/timing_gnn && $(PYTHON) -m train.train --epochs 2 --synthetic

train-synapse:
	cd abc/src/ext_ml/python && $(PYTHON) -m train.train_potential

train-polyphony:
	cd abc/src/ext_poly/python && $(PYTHON) -m train.train_gflownet --mode demo --n-vars 3

abc-build:
	$(MAKE) -C abc -j$(JOBS)

openroad-flow:
	./run-openroad-flow.sh flow DESIGN_CONFIG=$(DESIGN_CONFIG)

openroad-shell:
	./run-openroad-flow.sh shell
