# pv_resizer_evolve — one Makefile to run everything. `make` or `make help` lists targets.
# Knobs (override on the command line):  N=5 BUDGET_USD=20 TIER=A BAZEL_JOBS=8 CLAUDE_BIN=... PYTHON=...
SHELL := /bin/bash
.DEFAULT_GOAL := help
ROOT  := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
export ROOT
export PATH := /opt/homebrew/bin:/usr/local/bin:$(HOME)/.local/bin:$(PATH)

# ---- knobs ---------------------------------------------------------------
N          ?= 1          # iterations for `make evolve`
BUDGET_USD ?= 10         # stop when cumulative claude spend exceeds this
MAX_TOKENS ?= 0          # 0 = no token cap (USD cap still applies)
TIER       ?= A          # benchmark tier for the loop: A | B | C
REPLICATES ?= 2          # evaluation repeats per design (baseline uses 3)
BAZEL_JOBS ?= 8
export N BUDGET_USD MAX_TOKENS TIER REPLICATES BAZEL_JOBS

ENV  := source "$(ROOT)/tools/env.sh" &&
PY   := $(ENV) cd "$(ROOT)/03_evolution_framework" && { [ -x .venv/bin/python ] && P=.venv/bin/python || P=$$PYTHON; } && $$P -m rszevolve
FW_VENV := $(ROOT)/03_evolution_framework/.venv

# ---- help ----------------------------------------------------------------
.PHONY: help
help: ## show this help
	@echo "pv_resizer_evolve — evolve OpenROAD's Resizer (rsz) with planning / coding / evaluating agents"
	@echo
	@echo "Setup (once):     make env-check setup build-openroad snapshot"
	@echo "Phase 1 (once):   make graphify context"
	@echo "Evaluation prep:  make checkpoints baseline"
	@echo "Evolve:           make evolve N=5 BUDGET_USD=20 TIER=A      (or: make evolve-one / evolve-resume)"
	@echo "Look at results:  make report viz show-champion"
	@echo
	@grep -hE '^[a-zA-Z0-9_-]+:.*?## ' $(MAKEFILE_LIST) | awk 'BEGIN{FS=":.*?## "}{printf "  \033[36m%-20s\033[0m %s\n", $$1, $$2}'

# ---- environment ---------------------------------------------------------
.PHONY: env-check deps setup lock-versions
env-check: ## verify tools, pinned sources, binaries, RAM/disk
	@"$(ROOT)/tools/check_env.sh"

deps: ## install OS packages (brew on macOS, apt on Linux)
	@if [ "$$(uname -s)" = Darwin ]; then $(ROOT)/tools/install_deps_macos.sh; else $(ROOT)/tools/install_deps_linux.sh; fi

setup: ## clone OpenROAD + ORFS at the pinned commits, create framework venv
	@"$(ROOT)/tools/setup_sources.sh"


lock-versions: ## append exact tool versions seen here to VERSIONS.lock
	@"$(ROOT)/tools/lock_versions.sh"

# ---- build ---------------------------------------------------------------
.PHONY: build-openroad build-stock build-evolved restore-rsz test-rsz snapshot
build-openroad: build-stock ## build stock OpenROAD with Bazel -> build/bin/openroad_stock (1-2 h first time)
build-stock:
	@"$(ROOT)/tools/build_openroad.sh" stock
build-evolved: ## build with RSZ=<dir> overlaid on src/rsz -> build/bin/openroad_evolved
	@"$(ROOT)/tools/build_openroad.sh" evolved "$(or $(RSZ),$(ROOT)/02_openroad_evolved/champion/rsz)"
restore-rsz: ## put the pristine rsz snapshot back into external/OpenROAD/src/rsz
	@"$(ROOT)/tools/build_openroad.sh" restore
test-rsz: ## run rsz regression tests (FILTER=repair_setup to narrow)
	@"$(ROOT)/tools/build_openroad.sh" test-rsz $(FILTER)
snapshot: ## freeze external/OpenROAD/src/rsz into 01_openroad_original/rsz_snapshot (+ sta headers)
	@"$(ROOT)/tools/snapshot_rsz.sh"


# ---- phase 1: graphify + context ------------------------------------------
.PHONY: graphify context
graphify: ## build knowledge graphs (full OpenROAD + rsz-focused) into 08_graphify/
	@$(PY) graphify $(if $(SCOPE),--scope $(SCOPE),)
context: ## generate 09_agent_context/ (big picture, file cards, algorithm dossiers, clusters.json)
	@$(PY) context $(if $(ONLY),--only $(ONLY),)

# ---- evaluation prep -------------------------------------------------------
.PHONY: checkpoints baseline
checkpoints: ## run ORFS up to detailed placement and store placed checkpoints in 04_benchmarks/ (TIER=A|B|C|all)
	@$(PY) checkpoints --tier $(TIER)
baseline: ## evaluate stock openroad on checkpoints -> 05_baseline_results/ (3 replicates)
	@$(PY) baseline --tier $(TIER) --replicates 3

# ---- evolution -------------------------------------------------------------
.PHONY: evolve evolve-one evolve-resume validate-champion eval-candidate
evolve: ## run N iterations (plan -> code -> build -> gate -> evaluate -> feedback) within BUDGET_USD
	@$(PY) evolve --iterations $(N) --budget-usd $(BUDGET_USD) --max-tokens $(MAX_TOKENS) --tier $(TIER) --replicates $(REPLICATES)
evolve-one: ## exactly one iteration
	@$(MAKE) evolve N=1
evolve-resume: ## continue from lineage.json with the same knobs
	@$(PY) evolve --resume --iterations $(N) --budget-usd $(BUDGET_USD) --max-tokens $(MAX_TOKENS) --tier $(TIER) --replicates $(REPLICATES)
validate-champion: ## full Tier C evaluation of the current champion
	@$(PY) evaluate --rsz 02_openroad_evolved/champion/rsz --tier C --replicates 3 --tag champion_tierC
eval-candidate: ## evaluate an arbitrary rsz tree: make eval-candidate RSZ=path/to/rsz
	@$(PY) evaluate --rsz $(RSZ) --tier $(TIER) --replicates $(REPLICATES) --tag manual

# ---- results ---------------------------------------------------------------
.PHONY: report viz show-champion status
report: ## print summary tables (baseline vs champion vs iterations, cost per iteration)
	@$(PY) report
viz: ## render 07_visualizations/index.html + plots
	@$(PY) viz
show-champion: ## diff champion vs original rsz
	@diff -ruN 01_openroad_original/rsz_snapshot 02_openroad_evolved/champion/rsz > 02_openroad_evolved/champion.patch; head -200 02_openroad_evolved/champion.patch; echo "... full patch in 02_openroad_evolved/champion.patch"
status: ## where am I? iterations done, champion score, spend
	@$(PY) status

# ---- framework tests ----------------------------------------------------------
.PHONY: test
test: ## unit tests for the framework (stubbed openroad/claude; no build needed)
	@$(ENV) cd 03_evolution_framework && { [ -x .venv/bin/python ] && P=.venv/bin/python || P=$$PYTHON; } && $$P -m pytest -q tests

# ---- docker (portability) ------------------------------------------------------
.PHONY: docker-build docker-shell
docker-build: ## build the Linux image with all deps
	docker build -t pv-rsz-evolve -f tools/Dockerfile .
docker-shell: ## shell inside the image with the repo mounted at /work
	docker run --rm -it -v "$(ROOT)":/work -v pv-rsz-bazel-cache:/root/.cache/bazel -w /work pv-rsz-evolve bash

# ---- cleaning -------------------------------------------------------------------
.PHONY: clean-results clean-build
clean-results: ## delete evolved results, candidates, agent data (keeps baseline + context). Asks first.
	@read -p "Delete 06_evolved_results 11_agent_data 02_openroad_evolved/candidates lineage? [y/N] " a; [ "$$a" = y ] || exit 0; \
	rm -rf 06_evolved_results/* 11_agent_data/* 02_openroad_evolved/candidates/* 02_openroad_evolved/lineage.json 07_visualizations/index.html; \
	git checkout -- 06_evolved_results/README.md 11_agent_data/README.md 2>/dev/null || true
clean-build: ## remove copied binaries (Bazel cache is kept)
	rm -rf build
