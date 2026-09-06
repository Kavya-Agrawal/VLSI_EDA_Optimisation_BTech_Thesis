# Build the ABC Codebase Reference PDF on Windows.
#
# Requires a LaTeX toolchain. If none is installed, install MiKTeX once:
#     winget install MiKTeX.MiKTeX
# then re-open the shell and run this script again.

$ErrorActionPreference = "Stop"
Set-Location -Path $PSScriptRoot

function Have($name) { [bool](Get-Command $name -ErrorAction SilentlyContinue) }

if (Have "latexmk") {
    Write-Host "Building with latexmk..."
    latexmk -pdf -interaction=nonstopmode main.tex
    latexmk -c            # clean aux files, keep the PDF
}
elseif (Have "pdflatex") {
    Write-Host "Building with pdflatex (3 passes for TOC/refs)..."
    pdflatex -interaction=nonstopmode main.tex
    pdflatex -interaction=nonstopmode main.tex
    pdflatex -interaction=nonstopmode main.tex
}
else {
    Write-Error "No LaTeX toolchain found. Install one, e.g.:  winget install MiKTeX.MiKTeX"
}

if (Test-Path "main.pdf") {
    Write-Host "`nDone -> $((Resolve-Path main.pdf).Path)"
}
