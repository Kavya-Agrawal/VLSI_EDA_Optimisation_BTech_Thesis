# OpenROAD workflow

This project uses OpenROAD Flow Scripts (ORFS) in Docker. The environment contains
OpenROAD, Yosys, KLayout, the reference PDKs, and the RTL-to-GDSII flow. It avoids
mixing host-package versions with the flow's pinned tools.

## First use

Docker is already installed and this user is in the `docker` group. Log out and
back in once before using Docker from a new terminal. Verify it with:

```bash
docker info
```

The compatible OpenROAD build is located under
`external/OpenROAD-flow-scripts/tools/install-host/OpenROAD`. It is built from the
pinned project source because the published `openroad/orfs:latest` binary requires
CPU instructions unavailable on this machine.

## Run a complete flow

From this directory:

```bash
./run-openroad-flow.sh flow
```

This runs the Nangate45 GCD reference design through synthesis, floorplanning,
placement, CTS, routing, DRC/LVS checks, and GDSII generation. Outputs are retained
in `external/OpenROAD-flow-scripts/flow/results/nangate45/gcd/base/`; logs and
reports are alongside them in `flow/logs/` and `flow/reports/`.

To run a different included configuration:

```bash
./run-openroad-flow.sh flow DESIGN_CONFIG=designs/sky130hd/gcd/config.mk
```

For an interactive shell with `openroad`, `yosys`, and `klayout` available:

```bash
./run-openroad-flow.sh shell
```

Use the ORFS `flow/designs/asap7/minimal/README.md` guide when bringing in a new RTL
design. Put its configuration under `flow/designs/<platform>/<design>/config.mk` and
invoke the launcher with that `DESIGN_CONFIG`.
