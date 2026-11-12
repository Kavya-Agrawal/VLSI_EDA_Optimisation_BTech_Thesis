#!/usr/bin/env bash
# tools/snapshot_rsz.sh — freeze the pristine src/rsz (and the STA headers it uses) into 01_openroad_original/.
# Also initialises the champion to the original the first time.
set -euo pipefail
source "$(dirname "${BASH_SOURCE[0]}")/env.sh"
cd "$ROOT"
if ! git -C external/OpenROAD diff --quiet -- src/rsz; then
  echo "external/OpenROAD/src/rsz is modified; run: make restore-rsz" >&2; exit 1
fi
rsync -a --delete external/OpenROAD/src/rsz/ 01_openroad_original/rsz_snapshot/
mkdir -p 01_openroad_original/sta_interface_snapshot
rsync -a --delete --include='*/' --include='*.hh' --include='*.h' --exclude='*' external/OpenROAD/src/dbSta/include/ 01_openroad_original/sta_interface_snapshot/dbSta/
rsync -a --delete --include='*/' --include='*.hh' --exclude='*' external/OpenROAD/src/sta/include/sta/ 01_openroad_original/sta_interface_snapshot/sta/
git -C external/OpenROAD rev-parse HEAD > 01_openroad_original/UPSTREAM_COMMIT.txt
if [ ! -d 02_openroad_evolved/champion/rsz/src ]; then
  mkdir -p 02_openroad_evolved/champion
  rsync -a 01_openroad_original/rsz_snapshot/ 02_openroad_evolved/champion/rsz/
  echo "champion initialised = original"
fi
echo "snapshot @ $(cat 01_openroad_original/UPSTREAM_COMMIT.txt): $(find 01_openroad_original/rsz_snapshot -type f | wc -l | tr -d ' ') files"
