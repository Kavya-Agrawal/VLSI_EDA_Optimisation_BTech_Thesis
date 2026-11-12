#!/usr/bin/env bash
# tools/install_deps_macos.sh — one-time dependency install on macOS (Apple Silicon or Intel).
# Safe to re-run. Does NOT use sudo.
set -euo pipefail
command -v brew >/dev/null || { echo "Homebrew missing: https://brew.sh"; exit 1; }
brew install bazelisk yosys python@3.12 pipx rsync jq
pipx ensurepath >/dev/null 2>&1 || true
export PATH="$HOME/.local/bin:$PATH"
pipx list 2>/dev/null | grep -q graphifyy || pipx install graphifyy
if ! command -v claude >/dev/null 2>&1 && ! ls "$HOME"/.vscode/extensions/anthropic.claude-code-*/resources/native-binary/claude >/dev/null 2>&1; then
  echo "Claude Code CLI not found. Install: curl -fsSL https://claude.ai/install.sh | bash   (or set CLAUDE_BIN)"
fi
echo "macOS deps done. Next: make setup"
