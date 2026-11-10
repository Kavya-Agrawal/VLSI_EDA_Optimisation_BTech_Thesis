#!/usr/bin/env bash
# Run the OpenROAD Flow Scripts toolchain in its pinned Docker environment.
set -euo pipefail

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ORFS_ROOT="${PROJECT_ROOT}/external/OpenROAD-flow-scripts"
IMAGE="${ORFS_IMAGE:-openroad/flow-ubuntu22.04-dev:latest}"
OPENROAD_EXE="${ORFS_ROOT}/tools/install-host/OpenROAD/bin/openroad"

if ! command -v docker >/dev/null; then
  echo "Docker is required but was not found in PATH." >&2
  exit 1
fi

if ! docker info >/dev/null 2>&1; then
  cat >&2 <<'EOF'
Cannot access the Docker daemon. Log out and back in once so your docker-group
membership takes effect, then run this command again.
EOF
  exit 1
fi

if [[ ! -x "${OPENROAD_EXE}" ]]; then
  echo "Host-compatible OpenROAD binary is not installed at: ${OPENROAD_EXE}" >&2
  echo "Build it with the OpenROAD workflow setup before running this launcher." >&2
  exit 1
fi

mode="${1:-flow}"
if [[ $# -gt 0 ]]; then
  shift
fi

common_args=(
  --rm
  -u "$(id -u):$(id -g)"
  -v "${ORFS_ROOT}:/work"
  -w /work/flow
  -e FLOW_HOME=/work/flow
  -e WORK_HOME=/work/flow
  -e "OPENROAD_EXE=/work/tools/install-host/OpenROAD/bin/openroad"
  -e YOSYS_EXE=/usr/local/bin/yosys
  -e KLAYOUT_CMD=/usr/bin/klayout
)

case "${mode}" in
  flow)
    if [[ $# -eq 0 ]]; then
      set -- DESIGN_CONFIG=designs/nangate45/gcd/config.mk
    fi
    exec docker run -i "${common_args[@]}" "${IMAGE}" make "$@"
    ;;
  shell)
    exec docker run -it "${common_args[@]}" "${IMAGE}" bash
    ;;
  *)
    cat >&2 <<'EOF'
Usage:
  ./run-openroad-flow.sh flow [MAKE_VARIABLE_OR_TARGET ...]
  ./run-openroad-flow.sh shell

With no extra arguments, `flow` runs the full Nangate45 GCD RTL-to-GDSII
reference flow. Pass Make variables/targets to run your own design, for example:
  ./run-openroad-flow.sh flow DESIGN_CONFIG=designs/sky130hd/gcd/config.mk
EOF
    exit 2
    ;;
esac
