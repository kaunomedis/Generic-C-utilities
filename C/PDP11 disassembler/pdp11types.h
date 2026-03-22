#ifndef _PDP11TYPES_H_c839b12a_
#define _PDP11TYPES_H_c839b12a_

/* This file isin the public domain. */

typedef unsigned char byte;
typedef unsigned short int word;
typedef struct { unsigned long int f; unsigned long int m; } dfword;
typedef struct { word par; word pdr; } pagedesc;
typedef struct { word lsb; word msb; } ubamap;

#endif
