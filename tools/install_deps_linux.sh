#!/usr/bin/env bash
# tools/install_deps_linux.sh — one-time dependency install on Ubuntu/Debian (run with sudo for apt lines).
# Bazel is hermetic, so only a few system packages are needed.
set -euo pipefail
SUDO=""; [ "$(id -u)" -ne 0 ] && SUDO="sudo"
$SUDO apt-get update
$SUDO apt-get install -y --no-install-recommends git curl ca-certificates rsync jq python3 python3-venv python3-pip pipx \
  libc6-dev libxml2 libtinfo6 zlib1g libstdc++6 \
  yosys
# bazelisk
if ! command -v bazelisk >/dev/null; then
  arch=$(uname -m); [ "$arch" = "aarch64" ] && arch=arm64 || arch=amd64
  curl -fsSL -o /tmp/bazelisk "https://github.com/bazelbuild/bazelisk/releases/download/v1.28.1/bazelisk-linux-${arch}"
  $SUDO install -m 0755 /tmp/bazelisk /usr/local/bin/bazelisk
fi
pipx ensurepath >/dev/null 2>&1 || true
export PATH="$HOME/.local/bin:$PATH"
pipx list 2>/dev/null | grep -q graphifyy || pipx install graphifyy
command -v claude >/dev/null || echo "Claude Code CLI not found. Install: curl -fsSL https://claude.ai/install.sh | bash"
echo "Linux deps done. Next: make setup"
