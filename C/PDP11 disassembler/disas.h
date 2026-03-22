#ifndef _DISAS_H_a25bc09d_
#define _DISAS_H_a25bc09d_

/* This file is in the public domain. */

#include "pdp11.h"
#include "deftbl.h"

extern int disas(word);
extern void put(char);
extern void put_2(word);
extern void put_3(word);
extern void put_6(word);
extern void put_22(unsigned long int);
extern void put_x8(unsigned long int);
extern void put_s(const char *);
extern word fetchword(word, ASPACE);

#endif
