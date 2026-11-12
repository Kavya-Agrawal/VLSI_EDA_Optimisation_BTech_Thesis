#!/usr/bin/env bash
# tools/setup_sources.sh — clone/checkout OpenROAD and ORFS at the commits pinned in VERSIONS.lock,
# then create the framework's Python venv. Idempotent.
set -euo pipefail
source "$(dirname "${BASH_SOURCE[0]}")/env.sh"
export PATH="/opt/homebrew/bin:/usr/local/bin:$HOME/.local/bin:$PATH"
cd "$ROOT"
lock() { awk -F'=' -v k="$2" -v sec="[$1]" '$0==sec{s=1;next} /^\[/{s=0} s && $1 ~ "^"k" *$" {gsub(/ /,"",$2); sub(/#.*/,"",$2); print $2}' VERSIONS.lock; }
OR_SHA=$(lock openroad commit); ORFS_SHA=$(lock orfs commit)
OR_URL=$(lock openroad repo);   ORFS_URL=$(lock orfs repo)

if [ ! -e external/OpenROAD-flow-scripts/.git ]; then
  rm -rf external/OpenROAD-flow-scripts
  git clone --filter=blob:none "$ORFS_URL" external/OpenROAD-flow-scripts
fi
git -C external/OpenROAD-flow-scripts fetch -q origin "$ORFS_SHA"
git -C external/OpenROAD-flow-scripts checkout -q "$ORFS_SHA"

if [ ! -e external/OpenROAD/.git ]; then
  rm -rf external/OpenROAD
  git clone --filter=blob:none "$OR_URL" external/OpenROAD
fi
git -C external/OpenROAD fetch -q origin "$OR_SHA"
git -C external/OpenROAD checkout -q "$OR_SHA"
git -C external/OpenROAD submodule update --init --recursive --depth 1 2>/dev/null || git -C external/OpenROAD submodule update --init --recursive

VENV="$ROOT/03_evolution_framework/.venv"
[ -d "$VENV" ] || "$PYTHON" -m venv "$VENV"
"$VENV/bin/pip" install -q --upgrade pip
"$VENV/bin/pip" install -q -e "$ROOT/03_evolution_framework"
echo "setup done: OpenROAD @ $OR_SHA, ORFS @ $ORFS_SHA, venv at $VENV"
