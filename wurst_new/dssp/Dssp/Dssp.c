/*
 * This file was generated automatically by xsubpp version 1.9508 from the
 * contents of Dssp.xs. Do not edit this file, edit Dssp.xs instead.
 *
 *	ANY CHANGES MADE HERE WILL BE LOST!
 *
 */

#line 1 "Dssp.xs"
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "dssp.h"

typedef struct coord Coord;
#line 18 "Dssp.c"
XS(XS_Dssp_dssp); /* prototype to pass -Wmissing-prototypes */
XS(XS_Dssp_dssp)
{
    dXSARGS;
    if (items != 1)
	Perl_croak(aTHX_ "Usage: Dssp::dssp(c)");
    {
	Coord *	c;
	int	RETVAL;
	dXSTARG;

	if (sv_derived_from(ST(0), "CoordPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    c = INT2PTR(Coord *,tmp);
	}
	else
	    Perl_croak(aTHX_ "c is not of type CoordPtr");
#line 15 "Dssp.xs"
        RETVAL = dssp (c);
        if (RETVAL == EXIT_FAILURE)
            XSRETURN_UNDEF;
        else
            RETVAL = 1;        
#line 42 "Dssp.c"
    }
    XSRETURN(1);
}

#ifdef __cplusplus
extern "C"
#endif
XS(boot_Dssp); /* prototype to pass -Wmissing-prototypes */
XS(boot_Dssp)
{
    dXSARGS;
    char* file = __FILE__;

    XS_VERSION_BOOTCHECK ;

        newXSproto("Dssp::dssp", XS_Dssp_dssp, file, "$");
    XSRETURN_YES;
}
