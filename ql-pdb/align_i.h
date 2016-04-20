/*
 * 27 Aug 2001
 * rcsid = $Id: align_i.h,v 1.3 2007/02/12 17:03:55 tmargraf Exp $;
 */
#ifndef ALIGN2_H
#define ALIGN2_H

struct score_mat;
struct pair_set *
score_mat_sum_full ( struct score_mat **rmat, struct score_mat *smat,
                     float pgap_open, float pgap_widen,
                     float qgap_open, float qgap_widen,
                     float *p_mult,   float *q_mult,
                     const int algn_type, const struct pair_set *bias_set);
  

#endif  /* ALIGN2_H */
