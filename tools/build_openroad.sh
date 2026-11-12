#!/usr/bin/env bash
# tools/build_openroad.sh — build OpenROAD with Bazel and copy the binary out of bazel-bin.
# Identical on macOS, Linux and inside the Docker image (Bazel downloads its own LLVM/Tcl/zlib).
#
# Usage:
#   tools/build_openroad.sh stock                 # build external/OpenROAD as-is  -> build/bin/openroad_stock
#   tools/build_openroad.sh evolved <rsz_dir>     # overlay <rsz_dir> onto src/rsz -> build/bin/openroad_evolved
#   tools/build_openroad.sh restore               # put the pristine rsz snapshot back into src/rsz
#   tools/build_openroad.sh test-rsz [filter]     # bazelisk test //src/rsz/test/... (optionally filtered)
#
# Env: BAZEL_JOBS (default 8), BAZEL_CONFIG (e.g. --config=release), OPENROAD_SRC, BUILD_DIR
set -euo pipefail
source "$(dirname "${BASH_SOURCE[0]}")/env.sh"
export PATH="/opt/homebrew/bin:/usr/local/bin:$HOME/.local/bin:$PATH"

SNAPSHOT="$ROOT/01_openroad_original/rsz_snapshot"
SLOT="$OPENROAD_SRC/src/rsz"
mode="${1:-stock}"
mkdir -p "$BUILD_DIR/bin" "$BUILD_DIR/logs"

bazel_build() { # $1 = out binary path, $2 = log name
  local out="$1" log="$BUILD_DIR/logs/$2.log" t0 t1
  t0=$(date +%s)
  echo "[build] bazelisk build --jobs=$BAZEL_JOBS $BAZEL_CONFIG //:openroad   (log: $log)"
  ( cd "$OPENROAD_SRC" && bazelisk build --jobs="$BAZEL_JOBS" $BAZEL_CONFIG --config=no-werror //:openroad ) 2>&1 | tee "$log" | grep -E --line-buffered "ERROR|error:|FAILED|Build completed|Elapsed|INFO: Found|Analyzed" || true
  if ! grep -q "Build completed successfully" "$log"; then echo "[build] FAILED — see $log"; exit 2; fi
  cp -f "$OPENROAD_SRC/bazel-bin/openroad" "$out"
  t1=$(date +%s)
  echo "[build] ok: $out  ($((t1-t0)) s)  $("$out" -version 2>/dev/null | head -1)"
}

restore_slot() {
  if [ ! -d "$SNAPSHOT/src" ]; then echo "[build] no snapshot at $SNAPSHOT (run: make snapshot)"; return 1; fi
  rsync -a --delete "$SNAPSHOT/" "$SLOT/"
  # sanity: slot must be byte-identical to the git tree
  if ! git -C "$OPENROAD_SRC" diff --quiet -- src/rsz; then echo "[build] WARNING: src/rsz still differs from git after restore"; git -C "$OPENROAD_SRC" status --short -- src/rsz | head; fi
}

case "$mode" in
  stock)
    if [ -d "$SNAPSHOT/src" ]; then restore_slot; fi
    bazel_build "$OPENROAD_STOCK" "build_stock_$(date +%Y%m%d_%H%M%S)"
    ;;
  evolved)
    cand="${2:?usage: build_openroad.sh evolved <rsz_dir>}"
    [ -d "$cand/src" ] || { echo "[build] $cand does not look like an rsz tree (no src/)"; exit 1; }
    [ -d "$SNAPSHOT/src" ] || { echo "[build] need 01_openroad_original/rsz_snapshot first (make snapshot)"; exit 1; }
    echo "[build] overlaying $cand -> $SLOT"
    rsync -a --delete "$cand/" "$SLOT/"
    trap 'echo "[build] restoring pristine rsz"; restore_slot' EXIT
    bazel_build "$OPENROAD_EVOLVED" "build_evolved_$(date +%Y%m%d_%H%M%S)"
    ;;
  restore)
    restore_slot && echo "[build] src/rsz restored from snapshot"
    ;;
  test-rsz)
    filt="${2:-}"
    cd "$OPENROAD_SRC"
    if [ -n "$filt" ]; then
      targets=$(bazelisk query "filter(\"$filt\", kind(\".*_test rule\", //src/rsz/test/...))" 2>/dev/null)
    else
      targets="//src/rsz/test/..."
    fi
    bazelisk test --jobs="$BAZEL_JOBS" $BAZEL_CONFIG --config=no-werror --test_output=errors --test_tag_filters=-py $targets
    ;;
  *) echo "unknown mode $mode"; sed -n 2,12p "$0"; exit 1;;
esac
