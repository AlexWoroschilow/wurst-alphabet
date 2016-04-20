/*
 * 22 Feb 2002
 * Secondary structure routines, interface.
 * The detailed definitions live in sec_s.h
 * rscid = $Id: sec_s_i.h,v 1.1 2002/03/01 05:13:33 torda Exp $
 */
#ifndef SEC_S_I_H
#define SEC_S_I_H
struct coord;
int  char2ss (char c);
char ss2char (int sec_typ);
float        * coord_2_pnlty (struct coord *c, float value);

#endif /* SEC_S_I_H */
