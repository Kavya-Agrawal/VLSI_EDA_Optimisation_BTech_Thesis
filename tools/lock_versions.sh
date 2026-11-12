#!/usr/bin/env bash
# tools/lock_versions.sh — append the exact tool versions seen on this machine to VERSIONS.lock.
set -euo pipefail
source "$(dirname "${BASH_SOURCE[0]}")/env.sh"
export PATH="/opt/homebrew/bin:/usr/local/bin:$HOME/.local/bin:$PATH"
{
  echo ""
  echo "# recorded $(date -u +%Y-%m-%dT%H:%MZ) on $(uname -s) $(uname -m)"
  echo "openroad_head = $(git -C "$OPENROAD_SRC" rev-parse HEAD 2>/dev/null || echo missing)"
  echo "orfs_head     = $(git -C "$ORFS_SRC" rev-parse HEAD 2>/dev/null || echo missing)"
  echo "bazel         = $(cat "$OPENROAD_SRC/.bazelversion" 2>/dev/null || echo missing)"
  echo "yosys         = $(yosys -V 2>/dev/null | awk '{print $2}')"
  echo "python        = $($PYTHON --version 2>&1 | awk '{print $2}')"
  echo "graphify      = $(graphify --version 2>/dev/null | awk '{print $2}')"
  echo "claude        = $("$CLAUDE_BIN" --version 2>/dev/null | awk '{print $1}')"
  echo "openroad_bin  = $("$OPENROAD_STOCK" -version 2>/dev/null | head -1 || echo not-built)"
} >> "$ROOT/VERSIONS.lock"
tail -12 "$ROOT/VERSIONS.lock"
