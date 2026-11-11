SHELL := /bin/bash
PYTHON ?= python3
OPENROAD ?= ../external/OpenROAD
.DEFAULT_GOAL := stats
.PHONY: stats graphs report verify test rebuild serve
stats report:
	@$(PYTHON) scripts/study_stats.py --root .
graphs:
	@$(PYTHON) scripts/study_stats.py --root .
	@$(PYTHON) scripts/render_graphs.py --root .
verify:
	@$(PYTHON) scripts/verify_bundle.py
test:
	@$(MAKE) --no-print-directory -C $(OPENROAD)/learning_evolution test
rebuild:
	@$(PYTHON) $(OPENROAD)/learning_evolution/tools/build_final.py
serve:
	@$(PYTHON) -m http.server 8000 --bind 127.0.0.1
