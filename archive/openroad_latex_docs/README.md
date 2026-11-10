# OpenROAD Codebase Reference (LaTeX)

A concise, complete engineering reference to the OpenROAD RTL-to-GDSII
application, written as a compilable LaTeX book. The embedded Berkeley ABC at
`src/abc` is intentionally out of scope (see `abc_latex_docs/`).

## Structure

```
openroad_latex_docs/
├── main.tex          # integrator: \input's every chapter
├── preamble.tex      # shared packages, colors, macros, listing styles
├── build.ps1         # one-command build
├── README.md
└── chapters/
    ├── 01_introduction.tex
    ├── 02_architecture_framework.tex
    ├── 03_opendb.tex
    ├── 04_timing_parasitics.tex
    ├── 05_floorplan.tex
    ├── 06_placement.tex
    ├── 07_cts.tex
    ├── 08_routing.tex
    ├── 09_resizing.tex
    ├── 10_power_signoff.tex
    ├── 11_logic_synthesis_dft.tex
    └── 12_gui_flow.tex
```

## Build

```powershell
cd openroad_latex_docs
.\build.ps1
# or: latexmk -pdf main.tex
```

Requires a LaTeX toolchain (e.g. `winget install MiKTeX.MiKTeX`).

## Authoring conventions

- `\file{path}` — source path in the OpenROAD tree
- `\cmd{name}` — a Tcl / shell command
- `\id{Name}` — a C++ identifier
- `\pkg{src/mod}` — a module directory
- `\glance{...}` — boxed "at a glance" summary
- Code: `[style=orcode]` (C++) or `[style=ortcl]` (Tcl)
