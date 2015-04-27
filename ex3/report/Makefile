.PHONY: all auto ex3-report.pdf

all: ex3-report.pdf

auto:
	while true; do \
		$(MAKE); \
		inotifywait -e close_write -r main.tex bib.tex sections/ fig/; \
	done;

ex3-report.pdf:
	xelatex -halt-on-error -shell-escape -jobname=$(basename $@) main.tex
