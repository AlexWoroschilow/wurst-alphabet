#ifndef BASIC_TYPES_H
#define BASIC_TYPES_H

#ifdef __CYGWIN__ 

	#define CRLF '\r'

#else
	#define CRLF ' '
#endif

typedef unsigned char Uchar;
typedef unsigned int Uint;
typedef signed int Sint;
typedef unsigned char BOOL;

#define True 1
#define False 0

 typedef struct {
	int  a, 
		 b;
 } PairSint; 


#endif

