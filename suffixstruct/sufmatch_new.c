
/*
 *  sufmatch.c
 *  functions for matching in suffixarrays
 *
 *  @author Steve Hoffmann
 *  @email shoffmann@zbh.uni-hamburg.de
 *  @date 12/19/06 15:13:18 CET
 *  
 */


 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>
 #include <math.h>
 #include "basic-types.h"
 #include "memory.h"
 #include "mathematics.h"
 #include "sufarray.h"
 #include "sufmatch.h"
 #include "mm.h"
 #include "intsequence.h"
 #include "list.h"
 #include "depictseqs.h"
 #include "gnuplot_i.h"
 #include "dpalign.h"
 #include "cantor.h"
 #include "wurstimbiss.h"
 #include "falphabet.h"

/*------------------------------- suffixscore --------------------------------
 *    
 * scoring function for sw alignments of structure sequences 
 * 
 */
 
int
suffixscore (symtype a, symtype b, void* info)
{
   double* scores;

   scores = (double*) info;
   if (a == b) return 3;
   
	return -2;
}


/*------------------------------- sufSubstring -------------------------------
 *    
 * retrieve the longest substring matches in a suffixarray
 * 
 */
 
PairSint*
sufSubstring (void *space, Suffixarray *arr, Uint *pattern, 
			  Uint len, Uint sublen)
{
  	Uint i;
	PairSint *res, d;

	if (len <= sublen) 
	{
	  return NULL;
	}
	
	res = ALLOCMEMORY(space, NULL, PairSint, len-sublen);
	for(i=0; i < len-sublen; i++) 
	{
		d=mmsearch(arr, &pattern[i], sublen, 0, 0, arr->numofsuffixes-1);
		res[i].a=d.a;
	  	res[i].b=d.b;	  
	}
	
	return res;
}


/*------------------------------ reportSufmatch ------------------------------
 *    
 * returns a beautified match string
 * 
 */
 
void
reportSufmatch (Suffixarray *a, PairSint *matches, 
				Uint len, Uint threshold,
				IntSequence **s)
{
    Uint i, j, idx;
	char *info;

	for (i=0; i < len; i++) {
	   if (matches[i].b >= ((matches[i].a)+threshold)) {
		   /*valid matches*/
		  for (j=matches[i].a; j <= matches[i].b; j++) {	
             idx = getMultiSeqIndex(a->seq, a->suffixptr[a->suftab[j]]);
			 info = s[idx]->description;
			 printf("[%d]:\t %s\n", j, info);
		  }
	   }
    }
	
    return ;
}


/*---------------------------------- cmp_* -----------------------------------
 *    
 * compare functions for clibs's qsort and bsearch
 * 1. cmp_suffixno : used in rankSufmatch to sort sequence numbers
 * 2. cmp_ranks    : used in rankSufmatch to sort sequence ranks
 * 3. cmp_ranks_ptr: used in rankSufmatchList to sort sequence ranks
 * 
 */

int
cmp_blast(const void *a, const void *b) {
    Matchtype *first = (Matchtype*)a;
    Matchtype *second =(Matchtype*)b;	
    double frac_first, frac_second;

	
	frac_first = (double) first->blast ;
	frac_second = (double) second->blast ;

	if(frac_first > frac_second) return 1;
	if(frac_first < frac_second) return -1;
	
	return 0;
}


int
cmp_swscore(const void *a, const void *b) {
    Matchtype *first = (Matchtype*)a;
    Matchtype *second =(Matchtype*)b;	
    double frac_first, frac_second;

	if (first->swscore == 0 && second->swscore == 0) {
		if(first->count > second->count) return 1;
		if(first->count < second->count) return -1;
	}
	
	frac_first = (double) first->swscore ;
	frac_second = (double) second->swscore ;

	if(frac_first > frac_second) return 1;
	if(frac_first < frac_second) return -1;
	
	return 0;
}

int
cmp_score(const void *a, const void *b) {
    Matchtype *first = (Matchtype*)a;
    Matchtype *second =(Matchtype*)b;	
    double frac_first, frac_second;

	if (first->score == 0 && second->score == 0) {
		if(first->count > second->count) return 1;
		if(first->count < second->count) return -1;
	}
	
	frac_first = (double) first->score ;
	frac_second = (double) second->score;

	if(frac_first > frac_second) return 1;
	if(frac_first < frac_second) return -1;
	
	return 0;
}


int 
cmp_suffixno(const void *a, const void* b) {
    Matchtype *first = (Matchtype*)a;
    Matchtype *second =(Matchtype*)b;	
 
	
	if(first->id > second->id) return 1;
	if(first->id < second->id) return -1;

	return 0;
}


int 
cmp_ranks(const void *a, const void* b) {
    Matchtype *first = (Matchtype*)a;
    Matchtype *second =(Matchtype*)b;	
  
	if(first->count > second->count) return 1;
	if(first->count < second->count) return -1;

	return 0;
}

int 
cmp_rank_ptr(const void *a, const void* b) {
    Matchtype **first =  (Matchtype**)a;
    Matchtype **second = (Matchtype**)b;	
  
	if(first[0]->count > second[0]->count) return 1;
	if(first[0]->count < second[0]->count) return -1;

	return 0;
}




/*------------------------------ freeMatchtype -------------------------------
 *    
 * a function to delete Matchtypes in a list
 * 
 */
 
void
freeMatchtype (void *space, void *data)
{
    Matchtype *d = (Matchtype*)data;

	FREEMEMORY(space, d->pos);
	FREEMEMORY(space, data);
}


/*---------------------------------- subscr ----------------------------------
 *    
 * a function that assigns scores from a substitution matrix for matches 
 * and mismatches given in info matrix
 * 
 */
 
int
subscr (symtype a, symtype b, void *info )
{
  	double* M;	
	FAlphabet *alphabet;
	imbissinfo *p;
	int val;
	
	
	p = (imbissinfo*) info;
	alphabet = p->alphabet;
	M = (double*) p->sub;

/*	ad = alphabet->mapdomain[(Uint)a];
	bd = alphabet->mapdomain[(Uint)b];
	printf("decoding %d and %d", ad, bd);
	tupela = decodeCantor(NULL, ad, 2);
	tupelb = decodeCantor(NULL, bd, 2);	
	printf("... ended ... to %d and %d \n", VECTOR(tupela,0), VECTOR(tupelb,0));
	val =  MATRIX2D(M, 309, VECTOR(tupela, 0), VECTOR(tupelb,0));
*/
	val = MATRIX2D(M, 308, a ,b);
	if (val < -10) val = -10;
	
	return val;
}



/*-------------------------------- getEntropy --------------------------------
 *    
 * calculates the entropy of a sequence, given probabilities.
 * 
 */
 
double
getEntropy(void *space, Uint* sequence, Uint l, double* prob) {
	int i;
	double sum;
	
	for(i=0; i < l; i++) {
		sum += prob[sequence[i]]*log2(prob[sequence[i]]);
	}

	return sum;
}


/*------------------------------- rankSufmatchFct ------------------------------
 *    
 * ranks matches 
 * given in an array of PairSint of length len. Sorting is done
 * by several calls to clib's qsort. For each item of the sorted
 * array a handler-function is invoked.
 * 
 */

void
rankSufmatchFct(void *space, Suffixarray *a, PairSint *matches, 
			 Uint len, Uint threshold, Uint K, Uint S, IntSequence **s,
			 void (*handler)(void *, Matchtype *, IntSequence **, Uint, 
			   				 Uint, void *), 
			 IntSequence *queryseq, void *info, double *scores, 
			 unsigned char depictsw)
{
	Matchtype key, *cur, *occ=NULL;
	int r;	
	Sint i, j, l, k=0;
	int *swres; 
	/*int *align;*/
	int swscores[2]={3,-2};
	/*int alignsize;
	char* alignstr=NULL;*/
	Uint *ptr;
	float temp;
	double norm;
	double sum;
	char *constr;
	int *consensus;
	double *consensus_double;
	  
	double temp2;
	IntSequence *consensusSequence;
	gnuplot_ctrl *h;
	
	int *hashTable;
	

	hashTable = ALLOCMEMORY(space, NULL, int, 20000);
	memset(hashTable, -1, sizeof(int)*20000);
	  
	consensus = ALLOCMEMORY(space, NULL, Uint, len);
	memset(consensus, 0, sizeof(Uint)*len);
	
	for(i=0; i < len; i++) {
		if(matches[i].b >= ((matches[i].a))) {
		
		  	for(j=matches[i].a; j <= matches[i].b; j++) {
		        key.id = getMultiSeqIndex(a->seq, a->suffixptr[a->suftab[j]]);	
				r = hashTable[key.id];
					
				if (r == -1) {
				    occ = ALLOCMEMORY(space, occ, Matchtype, k+1);
					hashTable[key.id]=(&occ[k])-(occ);
					
				    occ[k].id = key.id;
					occ[k].count = 1;
					occ[k].pos = ALLOCMEMORY(space, NULL, Uint, 1);
					occ[k].org = ALLOCMEMORY(space, NULL, Uint, 1);
					occ[k].pos[0] = i;
					occ[k].org[0] = i;
					occ[k].m=0;
					occ[k].blast=0;
					occ[k].score = 0;
					occ[k].swscore = 0;

					/*score the matches if no < K*/
					if ((matches[i].b-matches[i].a) < K) {
					    ptr = (a->suffixptr[a->suftab[j]]);
						temp2=0;
						for (l=0; l < S; l++){
							temp = ((imbissinfo*)info)->score[(Uint)*ptr];
							temp2 += temp;
							occ[k].score += temp;	
							ptr++;
						}
						if(temp2>0){
							occ[k].blast = temp2;
							occ[k].m=1;
						}
						consensus[i]+= (int)
						  ((double)((imbissinfo*)info)->lambda*temp2);
					}			
		
					k++; 
				
				} else {
				    cur=((Matchtype*)(occ+r));
					cur->count++;
					if (cur->count == threshold) {
					
						swres = swgapless(space, 
							queryseq->sequence, queryseq->length, 
							s[cur->id]->sequence, s[cur->id]->length, 
							//suffixscore,((imbissinfo*)info)->score
							//subscr, info
							constscr, swscores
						);	    
		
						cur->swscore= swres[arraymax(swres, 
	  						(queryseq->length+1)*(s[cur->id]->length+1))];
		
			 			FREEMEMORY(space, swres);
				
					}
							
					cur->pos = ALLOCMEMORY(space, cur->pos, Uint, cur->count);
					cur->org = ALLOCMEMORY(space, cur->org, Uint, cur->count);
					cur->pos[(cur->count)-1]=i;
					cur->org[(cur->count)-1]=i;
					
					/*score matches if no < K*/
					  ptr = (a->suffixptr[a->suftab[j]]);
					  temp2=0;
					  for (l=0; l < S; l++) {
						
						temp = ((imbissinfo*)info)->score[(Uint)*ptr];
						temp2 += temp;
						cur->score += temp;
						ptr++;
					  }	
					  cur->blast = cur->blast > temp2 ? cur->blast : temp2;
					  consensus[i] += (int)
						((double)((imbissinfo*)info)->lambda*temp2);
				}
			}
		}
	}
	
	qsort(occ, k, sizeof(Matchtype), cmp_blast);
	l=0;
/*
	for (i=k; i > 0 && l < 1000; i--) {
		if (occ[i-1].count >= threshold) {
					
					swres = swgapless(space, 
							queryseq->sequence, queryseq->length, 
							s[occ[i-1].id]->sequence, s[occ[i-1].id]->length, 
							//subscr, info
							//constscr, swscores
						);	    
				
					occ[i-1].swscore= swres[arraymax(swres, 
	  						(queryseq->length+1)*(s[occ[i-1].id]->length+1))];
	
			 		FREEMEMORY(space, swres);
		} else {
			occ[i-1].swscore = 0;
		}
		l++;
    }*/

	qsort(occ, k, sizeof(Matchtype), cmp_blast);
	l=0;
	for (i=k; i > 0 && l<=100; i--) {

	if (occ[i-1].count >= threshold) {
			
	  		l++;
			handler(space, &occ[i-1], s, len, l, info);
	
			/*local alignment*/
			/*printf("max sw score: %f\n", occ[i-1].swscore);
			
			
	  		swres = swmatrix(space, queryseq->sequence, queryseq->length, 
				s[occ[i-1].id]->sequence, s[occ[i-1].id]->length, 
				-5, constscr, swscores);	    
		
			
			printf("max sw score: %d\n", swres[arraymax(swres, 
	  			(queryseq->length+1)*(s[occ[i-1].id]->length+1))]);
			
			align = swgaplesstraceback(space, swres,  
					queryseq->sequence, queryseq->length, 
					s[occ[k].id]->sequence, s[occ[k].id]->length,
					//suffixscore,((imbissinfo*)info)->score 
					-5, 
					constscr, swscores,
					&alignsize);
			 
			if (depictsw) {
			   	alignstr = printAlignment(space, align, alignsize,
				  		queryseq, s[occ[i-1].id], 80);
				printf("%s\n", alignstr);
				FREEMEMORY(space, alignstr);
				FREEMEMORY(space, align); 
			}*/
			 
		}
	}
   
	FREEMEMORY(space, hashTable);

	
	consensusSequence = initSequence(space);
	consensusSequence->sequence = consensus;
	consensusSequence->length = len;
	constr = printSequence(space, consensusSequence, 60);
	printf("%s\n", constr);
	FREEMEMORY(space, constr);
	
    consensus_double = ALLOCMEMORY(space, NULL, double, len);
	h = gnuplot_init();
	gnuplot_setstyle(h, "lines");
	sum = 0;
	for(i=0; i < len; i++) {
		sum += consensus[i];
	}
	
	for(i=0; i < len; i++) {
	  norm = consensus[i]/sum;
	  consensus_double[i] = 
		log10(((imbissinfo*)info)->K*3000000*len*exp(-(double)consensus[i]));
	  if (consensus_double[i] < -600) consensus_double[i]=-600;
	}

	gnuplot_plot_x(h, consensus_double, len, "blaPlot");

	for(i=0; i < k; i++) {
		FREEMEMORY(space, occ[i].pos);
		FREEMEMORY(space, occ[i].org);
	}

	FREEMEMORY(space, occ);    
	FREEMEMORY(space, consensus_double);
	FREEMEMORY(space, consensus);
	FREEMEMORY(space, consensusSequence);
}

/*------------------------------- rankSufmatch -------------------------------
 *    
 * ranks matches with a suffix array
 * given in an array of PairSint of length len. Sorting is done
 * by several calls to clib's qsort.
 * 
 */

void
rankSufmatch(void *space, Suffixarray *a, PairSint *matches, 
			 Uint len, Uint threshold, IntSequence **s)
{
	Matchtype key, *cur, 
			  *occ=NULL;
	void *r;
	char *seq;
	Sint i, j, k=0;
		
	for(i=0; i < len; i++) {
		if(matches[i].b >= ((matches[i].a))) {
		
		  	for(j=matches[i].a; j <= matches[i].b; j++) {
		        key.id = getMultiSeqIndex(a->seq, a->suffixptr[a->suftab[j]]);	
				r=bsearch(&key, occ, k, sizeof(Matchtype), cmp_suffixno);
			
				if (r == NULL) {
				    occ = ALLOCMEMORY(space, occ, Matchtype, k+1);
				    occ[k].id = key.id;
					occ[k].count = 1;
					occ[k].pos = ALLOCMEMORY(space, NULL, Uint, 1);		
					occ[k].pos[0] = i;
					occ[k].score = (double) s[key.id]->sequence[i]/len;
					k++; 
					qsort(occ, k, sizeof(Matchtype), cmp_suffixno);
				} else {
					cur=((Matchtype*)r);
					cur->count++;
					cur->pos = ALLOCMEMORY(space, cur->pos, Uint, cur->count);
					cur->pos[(cur->count)-1]=i;
					cur->score = (double) s[cur->id]->sequence[i]/len;
				}
			}
		}
	}
	
	qsort(occ, k, sizeof(Matchtype), cmp_ranks);
	
	for (i=k; i > 0; i--) {
	    if (occ[i-1].count > threshold) {
	    printf("%d\t%s\t%d\t", occ[i-1].id, s[occ[i-1].id]->url, 
		 				  occ[i-1].count);
	    seq= depictSequence(space, len, 20, occ[i-1].pos, occ[i-1].count,'*');
		printf("[%s]\n", seq);
		printf("%s\n", s[occ[i-1].id]->description);
		
		FREEMEMORY(space, seq);
		}
	    FREEMEMORY(space, occ[i-1].pos);
	}
	FREEMEMORY(space, occ);
	
	printf("found %d (partial) matches of %d.\n", k, len);
    
}



