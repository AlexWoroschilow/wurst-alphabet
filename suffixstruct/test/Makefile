CC=gcc
LD=${CC} 
CFLAGS= -O3 -DDONT_SEE_RCS -Wall -pedantic -I.. -I ../../gnuplot_i-2.10/src/ -I../../libs/ -I../../wurst/src/wurstsrc/ -L../../wurst/src/wurstsrc/ -L.. -L../../libs/  
LDFLAGS=-lm -lwurst -lc 
CTAGS=ctags > tags
LIBS=-lob



PROBVECTESTOBJ = ../prob_vec.o\
				../mprintf.o\
				../../libs/memman.o\
				../../libs/vtprogressbar.o\
				../e_malloc.o\
				../fio.o\
				../matrix.o\
				../mgc_num.o\
				../scratch.o\
				../../libs/sort.o\
				../../libs/cantor.o\
				../../libs/stack.o\
				../../libs/mathematics.o\
				../../libs/stringutils.o\
				../../libs/fileio.o\
				../falphabet.o\
				../createalphabet.o\
				../encodeprobvec.o\
				../intsequence.o\
				probvec_test.o
				


CONVERTPROBVECOBJ = ../prob_vec.o\
				../mprintf.o\
				../../libs/memman.o\
				../../libs/vtprogressbar.o\
				../e_malloc.o\
				../fio.o\
				../matrix.o\
				../mgc_num.o\
				../scratch.o\
				../../libs/sort.o\
				../../libs/cantor.o\
				../../libs/stack.o\
				../../libs/mathematics.o\
				../../libs/stringutils.o\
				../../libs/fileio.o\
				../falphabet.o\
				../createalphabet.o\
				../encodeprobvec.o\
				../intsequence.o\
				convertprobvec.o

READPROBSEQOBJ   = ../prob_vec.o\
				../mprintf.o\
				../../libs/memman.o\
				../../libs/vtprogressbar.o\
				../e_malloc.o\
				../fio.o\
				../matrix.o\
				../mgc_num.o\
				../scratch.o\
				../../libs/sort.o\
				../../libs/cantor.o\
				../../libs/stack.o\
				../../libs/mathematics.o\
				../../libs/stringutils.o\
				../../libs/fileio.o\
				../falphabet.o\
				../createalphabet.o\
				../encodeprobvec.o\
				../intsequence.o\
				readprobseq.o

BMPROBSEQOBJ   = ../../libs/memman.o\
				 ../prob_vec.o\
				../mprintf.o\
				../../libs/vtprogressbar.o\
				../e_malloc.o\
				../fio.o\
				../matrix.o\
				../mgc_num.o\
				../scratch.o\
				../../libs/sort.o\
				../../libs/cantor.o\
				../../libs/stack.o\
				../../libs/mathematics.o\
				../../libs/stringutils.o\
				../../libs/boyermoore.o\
				../../libs/fileio.o\
				../falphabet.o\
				../createalphabet.o\
				../encodeprobvec.o\
				../intsequence.o\
				bmprobseq.o


SUFPROBSEQOBJ   = ../../gnuplot_i-2.10/gnuplot_i.o\
				../../libs/memman.o\
				../../libs/list.o\
				../prob_vec.o\
				../mprintf.o\
				../../libs/vtprogressbar.o\
				../e_malloc.o\
				../fio.o\
				../matrix.o\
				../mgc_num.o\
				../scratch.o\
				../../libs/sort.o\
				../../libs/cantor.o\
				../../libs/stack.o\
				../../libs/mathematics.o\
				../../libs/stringutils.o\
				../../libs/boyermoore.o\
				../../libs/fileio.o\
				../../libs/dpalign.o\
				../falphabet.o\
				../createalphabet.o\
				../encodeprobvec.o\
				../intsequence.o\
				../sufarray.o\
				../depictseqs.o\
				../mm.o\
				../sufmatch.o\
				../multiseq.o\
				sufprobseq.o


ALPHABETTESTOBJ = alphabet_test.o\
				../../libs/stringutils.o\
				../../libs/fileio.o\
				../../libs/sort.o\
				../../libs/stack.o\
				../../libs/cantor.o\
				../../libs/mathematics.o\
				../createalphabet.o\
				../falphabet.o\

WURSTIMBISSOBJ   = ../../gnuplot_i-2.10/gnuplot_i.o\
				../../libs/memman.o\
				../../libs/list.o\
				../../libs/vtprogressbar.o\
				../../libs/sort.o\
				../../libs/cantor.o\
				../../libs/stack.o\
				../../libs/mathematics.o\
				../../libs/stringutils.o\
				../../libs/boyermoore.o\
				../../libs/fileio.o\
				../../libs/dpalign.c\
				../../libs/hash.c\
				../falphabet.o\
				../createalphabet.o\
				../encodeprobvec.o\
				../intsequence.o\
				../sufarray.o\
				../depictseqs.o\
				../mm.o\
				../sufmatch.o\
				../multiseq.o\
				../salami.o\
				../probseqscore.c\
				../blaststat.c\
				../imbissblast.c\
				wurstimbiss.o\

IMSUBSTOBJ    = ../prob_vec.o\
				../mprintf.o\
				../../libs/memman.o\
				../../libs/vtprogressbar.o\
				../e_malloc.o\
				../fio.o\
				../matrix.o\
				../mgc_num.o\
				../scratch.o\
				../../libs/sort.o\
				../../libs/cantor.o\
				../../libs/stack.o\
				../../libs/mathematics.o\
				../../libs/stringutils.o\
				../../libs/fileio.o\
				../falphabet.o\
				../createalphabet.o\
				../encodeprobvec.o\
				../intsequence.o\
				../imsubst.o\
				createsubmatrix.o



all: readprobseq.x bmprobseq.x probvectest.x convertprobvec.x sufprobseq.x wurstimbiss.x createsubmatrix.x 


mathematicstest.x: ${MATHEMATICSTESTOBJ}
					gcc $(CFLAGS) ${MATHEMATICSTESTOBJ} -o $@

alphabettest.x: ${ALPHABETTESTOBJ}
					gcc $(CFLAGS) ${ALPHABETTESTOBJ} -o $@

probvectest.x: ${PROBVECTESTOBJ}
					gcc $(CFLAGS) ${PROBVECTESTOBJ} -o $@ $(LDFLAGS)

readprobseq.x: ${READPROBSEQOBJ}
					gcc $(CFLAGS) ${READPROBSEQOBJ} -o $@ $(LDFLAGS)


sufprobseq.x: ${SUFPROBSEQOBJ}
					gcc $(CFLAGS) ${SUFPROBSEQOBJ} -o $@ $(LDFLAGS)


bmprobseq.x: ${BMPROBSEQOBJ}
					gcc $(CFLAGS) ${BMPROBSEQOBJ} -o $@ $(LDFLAGS)



createsubmatrix.x: ${IMSUBSTOBJ}
					gcc $(CFLAGS) ${IMSUBSTOBJ} -o $@ $(LDFLAGS)


convertprobvec.x: ${CONVERTPROBVECOBJ}
					gcc $(CFLAGS) ${CONVERTPROBVECOBJ} -o $@ $(LDFLAGS)


wurstimbiss.x: ${WURSTIMBISSOBJ}
					gcc $(CFLAGS) ${WURSTIMBISSOBJ} -o $@ $(LDFLAGS)

clean: 
	rm ../*.o
	rm ../../libs/*.o
	rm *.o


