#! /bin/sh

pdflatex refman
makeindex refman.idx
pdflatex refman
latex_count=8 ; \
	while egrep -s 'Rerun (LaTeX|to get cross-references right)' refman.log && [ $$latex_count -gt 0 ] ;\
		    do \
			          echo "Rerunning latex...." ;\
				        pdflatex refman ;\
					      latex_count=`expr $$latex_count - 1` ;\
					          done
makeindex refman.idx
pdflatex refman

