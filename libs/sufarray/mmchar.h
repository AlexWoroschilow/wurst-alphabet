#ifndef MMCHAR_H
#define MMCHAR_H

/*
 *
 *	mmchar.h
 *  declaration for searches manber myers style
 *  on enhanced suffix arrays
 * 
 *  @author Steve Hoffmann, shoffmann@zbh.uni-hamburg.de
 *  @company Center for Bioinformatics, Hamburg 
 *  @date 12/22/06 19:11:16 CET  
 *
 */
 
 #include "basic-types.h"
 #include "sufarray.h"

 int mmleft(Suffixarray *, char*, Uint, int, int, int);
 int mmright(Suffixarray *, char*, Uint, int, int, int);
 PairSint mmcompare(Suffixarray *, char*, Uint, int, int);
 PairSint mmsearch(Suffixarray *, char*, Uint, Uint, Uint, Uint);

#endif
