# ABC Codebase Reference (LaTeX)

A concise, complete engineering reference to the Berkeley ABC codebase, written
as a compilable LaTeX book.

## Structure

```
abc_latex_docs/
├── main.tex          # integrator: \input's every chapter
├── preamble.tex      # shared packages, colors, macros, listing styles
├── chapters/
│   ├── 01_introduction.tex
│   ├── 02_architecture_command.tex
│   ├── 03_data_structures.tex
│   ├── 04_aig_gia.tex
│   ├── 05_io_frontends.tex
│   ├── 06_optimization.tex
│   ├── 07_mapping.tex
│   ├── 08_proof_verification.tex
│   ├── 09_sat.tex
│   ├── 10_bool_misc_utilities.tex
│   └── 11_recipes_embedding.tex
└── README.md
```

## Build

```bash
cd abc_latex_docs
latexmk -pdf main.tex        # preferred
# or:
pdflatex main.tex            # run 2-3 times for TOC / refs
```

Output: `main.pdf`.

## Authoring conventions (used by every chapter)

- `\file{path}`  — a source path in the ABC tree
- `\cmd{name}`   — a shell / REPL command
- `\id{Name}`    — a C identifier (function, struct, field)
- `\pkg{dir}`    — a package directory
- `\glance{...}` — a boxed "at a glance" summary
- Code: `\begin{lstlisting}[style=abccode]` (C) or `[style=abcshell]` (REPL)

Chapter files contain **no** preamble — they start at `\chapter{...}` and rely on
`preamble.tex`.
