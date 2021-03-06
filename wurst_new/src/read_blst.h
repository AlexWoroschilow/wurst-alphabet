/*
 * 13 nov 2003
 * rcsid = $Id: read_blst.h,v 1.4 2005/01/05 10:27:19 torda Exp $
 */
#ifndef READ_BLAST_H
#define READ_BLAST_H

struct seqprof;
void            seqprof_destroy (struct seqprof *profile);
char           *seqprof_str     (const struct seqprof  *profile);
struct seqprof *blst_chk_read (const char *fname);
struct seq     *seqprof_get_seq (struct seqprof *sp);
#ifdef want_blst_chk_write
    int             blst_chk_write (const char *fname, struct seqprof *chk);
#endif /* want_blst_chk_write */
#endif /* READ_BLAST_H */
