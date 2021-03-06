/*
 * 22 March 2001
 * rcsid = $Id: str.h,v 1.4 2002/03/28 05:24:33 torda Exp $
 */
#ifndef STR_H
#define STR_H

char * str_up (char *s);
char * str_down (char *s);
char * save_str_append (char *dst, const char *src);
char * save_str (const char *src);
void * save_anything ( const void *p, size_t n);
const char *strip_path (const char *s);
char * strip_blank (char *s);
#endif /* STR_H */

