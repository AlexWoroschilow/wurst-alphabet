#ifndef MULTRIALIGN_H_
#define MULTRIALIGN_H_

#include "pair_set.h"
#include "score_mat_i.h"

struct prob_vec *
pvec_avg(struct prob_vec *p_vec1,
             struct prob_vec *p_vec2,
             struct pair_set *p_set,
             const size_t cur_step);

struct pair_set *
merge_alignments(struct pair_set *align1, struct pair_set *align2, struct pair_set *alignment);

struct pair_set *
remove_seq(struct pair_set *align, int idx);

struct pair_set *
split_multal(struct pair_set *align, int a, int b);

#endif /*MULTRIALIGN_H_*/
