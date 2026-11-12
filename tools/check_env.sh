#!/usr/bin/env bash
# tools/check_env.sh — verify the machine can run the pv_resizer_evolve pipeline.
# Prints a PASS/WARN/FAIL table. Exit 1 if anything required FAILs.
# Usage: tools/check_env.sh            (same as `make env-check`)
set -u
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"
export PATH="/opt/homebrew/bin:/usr/local/bin:$HOME/.local/bin:$PATH"

# shellcheck source=tools/env.sh
source "$ROOT/tools/env.sh"

fail=0
row() { printf '%-6s %-22s %s\n' "$1" "$2" "$3"; }
need() { # need <name> <cmd to test> <hint>
  if out=$(eval "$2" 2>&1); then row PASS "$1" "$(echo "$out" | head -1)"; else row FAIL "$1" "$3"; fail=1; fi
}
want() { # optional
  if out=$(eval "$2" 2>&1); then row PASS "$1" "$(echo "$out" | head -1)"; else row WARN "$1" "$3"; fi
}
lock() { awk -F'=' -v k="$2" -v sec="[$1]" '$0==sec{s=1;next} /^\[/{s=0} s && $1 ~ "^"k" *$" {gsub(/ /,"",$2); sub(/#.*/,"",$2); print $2}' "$ROOT/VERSIONS.lock"; }

echo "pv_resizer_evolve environment check  ($(uname -s) $(uname -m), $(sysctl -n hw.ncpu 2>/dev/null || nproc) cores)"
echo "------------------------------------------------------------------"
need "git"        "git --version"                           "install git"
need "python>=3.10" "$PYTHON -c 'import sys;assert sys.version_info>=(3,10);print(sys.version.split()[0])'" "brew install python@3.12 (or set PYTHON=)"
need "bazelisk"   "bazelisk version 2>/dev/null | head -1 || bazelisk --version" "brew install bazelisk  /  tools/install_deps_linux.sh"
need "yosys"      "yosys -V"                                "brew install yosys (needed once, for checkpoints)"
need "claude CLI" "\"$CLAUDE_BIN\" --version"               "install Claude Code CLI or set CLAUDE_BIN=/path/to/claude"
want "graphify"   "graphify --version"                      "pipx install graphifyy"
want "docker"     "docker --version"                        "optional: only for make docker-*"

OR_SHA=$(lock openroad commit); ORFS_SHA=$(lock orfs commit)
if [ -e external/OpenROAD/.git ]; then
  cur=$(git -C external/OpenROAD rev-parse HEAD 2>/dev/null)
  if [ "$cur" = "$OR_SHA" ]; then row PASS "OpenROAD src" "${cur:0:12} (pinned)"; else row WARN "OpenROAD src" "at ${cur:0:12}, lock says ${OR_SHA:0:12}"; fi
else row FAIL "OpenROAD src" "run: make setup"; fail=1; fi
if [ -e external/OpenROAD-flow-scripts/.git ]; then
  cur=$(git -C external/OpenROAD-flow-scripts rev-parse HEAD 2>/dev/null)
  if [ "$cur" = "$ORFS_SHA" ]; then row PASS "ORFS src" "${cur:0:12} (pinned)"; else row WARN "ORFS src" "at ${cur:0:12}, lock says ${ORFS_SHA:0:12}"; fi
else row FAIL "ORFS src" "run: make setup"; fail=1; fi

if [ -x "$OPENROAD_STOCK" ]; then row PASS "openroad (stock)" "$("$OPENROAD_STOCK" -version 2>/dev/null | head -1)"; else row WARN "openroad (stock)" "run: make build-openroad"; fi
if [ -x "$OPENROAD_EVOLVED" ]; then row PASS "openroad (evolved)" "$("$OPENROAD_EVOLVED" -version 2>/dev/null | head -1)"; else row WARN "openroad (evolved)" "built on first make evolve"; fi

mem_gb=$(( $(sysctl -n hw.memsize 2>/dev/null || grep MemTotal /proc/meminfo | awk '{print $2*1024}') / 1073741824 ))
[ "$mem_gb" -ge 15 ] && row PASS "RAM" "${mem_gb} GB" || { row WARN "RAM" "${mem_gb} GB (<16: use BAZEL_JOBS=4)"; }
free_gb=$(df -g . 2>/dev/null | awk 'NR==2{print $4}'); [ -z "$free_gb" ] && free_gb=$(df -BG . | awk 'NR==2{print $4}' | tr -d G)
[ "$free_gb" -ge 40 ] && row PASS "disk free" "${free_gb} GB" || { row WARN "disk free" "${free_gb} GB (<40 GB: Bazel cache + checkpoints need room)"; }

echo "------------------------------------------------------------------"
[ $fail -eq 0 ] && echo "RESULT: ready" || { echo "RESULT: missing required pieces (see FAIL rows)"; exit 1; }
