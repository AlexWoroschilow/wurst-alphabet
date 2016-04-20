
/*
 *  bitArray.c
 *  implementations
 *
 *  @author Steve Hoffmann
 *  @email steve@bioinf.uni-leipzig.de
 *  @date 07/14/2007 04:15:14 PM CEST
 *  
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "basic-types.h"
#include "memory.h"
#include "bitArray.h"

bitarray
initbitarray(void *space, Uint len) {
  Uint n;
bitarray a;

  n = len/8;
  n += (len % 8 > 0) ? 1 : 0;
  a = ALLOCMEMORY(space, NULL, unsigned char, n);

  return a;
}

bitarray
resizebitarray(void *space, bitarray a, Uint len) {
  Uint n;

  n = len/8;
  n += (len % 8 > 0) ? 1 : 0;
  a = ALLOCMEMORY(space, a, unsigned char, n);

  return a;
}

void
setbitarray(bitarray a, Uint len, unsigned char val) {
  Uint n;

  n = len/8;
  n += (len % 8 > 0) ? 1 : 0;
  memset(a,((val) ? 255 :0), n);
}

unsigned char
valbitarray(bitarray a, Uint len, unsigned char val) {
    Uint i;
    char *array;

    array = (char*) a;

    for(i=0; i < (len/8); i++) {  
        if (array[i] != (char) 255) 
          return 0;
    }
    for(i=0; i < (len%8); i++){
        if (getbit(a, len-i-1)!= val) 
          return 0;
    }
    
    return 1;
}

void
dumpbitarray(bitarray a, Uint len) {
  Uint i;
 
  for(i=0; i < len; i++) {
    printf("%d ", getbit(a, i));    
  }
  printf("\n");
}

