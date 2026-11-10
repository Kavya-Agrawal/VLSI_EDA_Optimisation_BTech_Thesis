.PHONY: all clean pdf

all: pdf

pdf: report.pdf

report.pdf: report.tex
	pdflatex -interaction=nonstopmode report.tex
	pdflatex -interaction=nonstopmode report.tex

clean:
	rm -f report.aux report.log report.out report.toc
