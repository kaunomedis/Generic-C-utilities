#ifndef _DEFTBL_H_e4c26ca7_
#define _DEFTBL_H_e4c26ca7_

/* This file is in the public domain. */

#define DEF_UNKNOWN (instr_def_n+1)
#define DEF_UNUSED (instr_def_n+2)

extern void deftbl_init(void);
extern int get_deftbl(word);

#endif
