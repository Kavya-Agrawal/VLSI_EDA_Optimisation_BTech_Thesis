#!/usr/bin/env bash
# tools/env.sh — single place for paths and binaries. Sourced by every tool script and the Makefile.
# Override anything by exporting it before calling make, e.g.  CLAUDE_BIN=/opt/claude make evolve
ROOT="${ROOT:-$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)}"
export ROOT

export OPENROAD_SRC="${OPENROAD_SRC:-$ROOT/external/OpenROAD}"
export ORFS_SRC="${ORFS_SRC:-$ROOT/external/OpenROAD-flow-scripts}"
export BUILD_DIR="${BUILD_DIR:-$ROOT/build}"                 # copies of binaries live here (bazel-bin is volatile)
export OPENROAD_STOCK="${OPENROAD_STOCK:-$BUILD_DIR/bin/openroad_stock}"
export OPENROAD_EVOLVED="${OPENROAD_EVOLVED:-$BUILD_DIR/bin/openroad_evolved}"
export BAZEL_JOBS="${BAZEL_JOBS:-8}"                          # 16 GB machines: 6-8 is safe; raise on bigger hosts
export BAZEL_CONFIG="${BAZEL_CONFIG:-}"                       # e.g. "--config=release" for -O3+ThinLTO (slower link)

# Python used for the framework (>=3.10). Prefer brew python@3.12, fall back to python3.
if [ -z "${PYTHON:-}" ]; then
  for c in python3.12 python3.13 python3.11 python3.10 python3; do
    if command -v "$c" >/dev/null 2>&1 && "$c" -c 'import sys;sys.exit(0 if sys.version_info>=(3,10) else 1)' 2>/dev/null; then PYTHON="$c"; break; fi
  done
fi
export PYTHON="${PYTHON:-python3}"

# Claude Code CLI. Falls back to the copy bundled with the VS Code extension.
if [ -z "${CLAUDE_BIN:-}" ]; then
  if command -v claude >/dev/null 2>&1; then CLAUDE_BIN="$(command -v claude)"
  else CLAUDE_BIN="$(ls -d "$HOME"/.vscode/extensions/anthropic.claude-code-*/resources/native-binary/claude 2>/dev/null | sort -V | tail -1)"; fi
fi
export CLAUDE_BIN="${CLAUDE_BIN:-claude}"

# Headless-agent fallback chain. Each CLI uses its own existing login; credentials are never copied
# between providers. Override the order or models before invoking make when required.
export AGENT_PROVIDERS="${AGENT_PROVIDERS:-claude,codex,antigravity}"
if [ -z "${CODEX_BIN:-}" ]; then
  CODEX_BIN="$(command -v codex 2>/dev/null || ls -d "$HOME"/.vscode/extensions/openai.chatgpt-*/bin/macos-*/codex 2>/dev/null | sort -V | tail -1)"
fi
export CODEX_BIN="${CODEX_BIN:-codex}"
export CODEX_AGENT_MODEL="${CODEX_AGENT_MODEL:-gpt-6.1-sol}"
export ANTIGRAVITY_BIN="${ANTIGRAVITY_BIN:-$(command -v agy 2>/dev/null || echo "$HOME/.local/bin/agy")}"
export ANTIGRAVITY_AGENT_MODEL="${ANTIGRAVITY_AGENT_MODEL:-gemini-3.8-flash-high}"

export YOSYS_EXE="${YOSYS_EXE:-$(command -v yosys 2>/dev/null || echo /opt/homebrew/bin/yosys)}"
