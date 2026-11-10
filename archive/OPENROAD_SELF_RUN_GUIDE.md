# OpenROAD Self-Run Guide

This guide shows how to run the OpenROAD RTL-to-GDSII flow yourself on this PC.
The flow is already set up through Docker and the project launcher script:

```bash
./run-openroad-flow.sh
```

## 1. Open the project

Open a new terminal and go to the project directory:

```bash
cd /home/kavya-kumar-agrawal/Desktop/hw_eda/VLSI_EDA_Optimisation_BTech_Thesis
```

## 2. Check Docker

Run:

```bash
docker info
```

If this gives a permission error, log out and log back in, then open a fresh
terminal and try again.

## 3. Run the complete reference flow

Run:

```bash
./run-openroad-flow.sh flow
```

This uses the default OpenROAD Flow Scripts design:

```text
designs/nangate45/gcd/config.mk
```

The flow stages are:

```text
RTL Verilog
Synthesis
Floorplanning
Placement
Clock tree synthesis
Routing
Final checks
GDSII layout
```

## 4. Check the final output

Final layout and design files are generated here:

```bash
external/OpenROAD-flow-scripts/flow/results/nangate45/gcd/base
```

Important final files:

```text
6_final.gds
6_final.def
6_final.v
6_final.spef
```

Reports are generated here:

```bash
external/OpenROAD-flow-scripts/flow/reports/nangate45/gcd/base
```

Useful reports to inspect:

```text
6_finish.rpt
5_route_drc.rpt
4_cts_final.rpt
```

## 5. Run a different included design

Use `DESIGN_CONFIG` to select another OpenROAD design:

```bash
./run-openroad-flow.sh flow DESIGN_CONFIG=designs/sky130hd/gcd/config.mk
```

General format:

```bash
./run-openroad-flow.sh flow DESIGN_CONFIG=designs/<platform>/<design>/config.mk
```

## 6. Run one stage at a time

This is useful when debugging.

```bash
./run-openroad-flow.sh flow DESIGN_CONFIG=designs/nangate45/gcd/config.mk synth
./run-openroad-flow.sh flow DESIGN_CONFIG=designs/nangate45/gcd/config.mk floorplan
./run-openroad-flow.sh flow DESIGN_CONFIG=designs/nangate45/gcd/config.mk place
./run-openroad-flow.sh flow DESIGN_CONFIG=designs/nangate45/gcd/config.mk cts
./run-openroad-flow.sh flow DESIGN_CONFIG=designs/nangate45/gcd/config.mk route
./run-openroad-flow.sh flow DESIGN_CONFIG=designs/nangate45/gcd/config.mk final
```

## 7. Open an interactive OpenROAD shell

Run:

```bash
./run-openroad-flow.sh shell
```

Inside this shell, OpenROAD, Yosys, KLayout, and the OpenROAD flow environment
are available.

Exit the shell with:

```bash
exit
```

## 8. Add your own Verilog design

Create a new design directory:

```bash
mkdir -p external/OpenROAD-flow-scripts/flow/designs/nangate45/my_design
```

Copy the existing GCD configuration as a starting point:

```bash
cp external/OpenROAD-flow-scripts/flow/designs/nangate45/gcd/config.mk external/OpenROAD-flow-scripts/flow/designs/nangate45/my_design/config.mk
```

Put your Verilog file here:

```text
external/OpenROAD-flow-scripts/flow/designs/nangate45/my_design/my_top_module.v
```

Create a constraint file here:

```text
external/OpenROAD-flow-scripts/flow/designs/nangate45/my_design/constraint.sdc
```

Example `constraint.sdc`:

```tcl
create_clock -name core_clock -period 10 [get_ports clk]
set_input_delay 1 -clock core_clock [remove_from_collection [all_inputs] [get_ports clk]]
set_output_delay 1 -clock core_clock [all_outputs]
```

Edit your new `config.mk` and update at least these lines:

```makefile
export DESIGN_NAME = my_top_module
export VERILOG_FILES = /work/flow/designs/nangate45/my_design/my_top_module.v
export SDC_FILE = /work/flow/designs/nangate45/my_design/constraint.sdc
```

Then run your design:

```bash
./run-openroad-flow.sh flow DESIGN_CONFIG=designs/nangate45/my_design/config.mk
```

## 9. Common problems

If Docker fails:

```bash
docker info
```

If it says permission denied, log out and log back in.

If synthesis fails, check:

```text
DESIGN_NAME matches your Verilog top module.
VERILOG_FILES points to the correct Verilog file.
Your Verilog has no syntax errors.
```

If placement fails, reduce density in `config.mk`:

```makefile
export CORE_UTILIZATION = 35
export PLACE_DENSITY = 0.50
```

If timing fails, increase the clock period in `constraint.sdc`:

```tcl
create_clock -name core_clock -period 20 [get_ports clk]
```

Timing violations do not always mean the setup is broken. The flow has completed
successfully if final files such as `6_final.gds` are produced.

## 10. Quick command summary

Run default flow:

```bash
./run-openroad-flow.sh flow
```

Run selected design:

```bash
./run-openroad-flow.sh flow DESIGN_CONFIG=designs/nangate45/my_design/config.mk
```

Enter shell:

```bash
./run-openroad-flow.sh shell
```

Check final GDS:

```bash
ls external/OpenROAD-flow-scripts/flow/results/nangate45/gcd/base/6_final.gds
```
