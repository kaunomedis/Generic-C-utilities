/* This file is in the public domain. */

#include <stdlib.h>

#define NEED_EXTERN
#include "instrtbl.h"

#include "deftbl.h"
#include "heapsort.h"

static short int deftbl[65536];

static int idcmp(void *idvp1, void *idvp2)
{
 return( (0xffff&(int)((INSTR_DEF *)idvp1)->value) -
	 (0xffff&(int)((INSTR_DEF *)idvp2)->value) );
}

void deftbl_init(void)
{
 int i;
 void **idvp;
 INSTR_DEF *idarr;

 idvp = malloc(instr_def_n*sizeof(void *));
 for (i=0;i<instr_def_n;i++) idvp[i] = &instr_defs[i];
 heap_sort(&idvp[0],instr_def_n,idcmp);
 idarr = malloc(instr_def_n*sizeof(INSTR_DEF));
 for (i=0;i<instr_def_n;i++) idarr[i] = * (INSTR_DEF *) idvp[i];
 for (i=0;i<instr_def_n;i++) instr_defs[i] = idarr[i];
 free(idvp);
 free(idarr);
 for (i=0;i<65536;i++) deftbl[i] = DEF_UNKNOWN;
}

int get_deftbl(word inst)
{
 int l;
 int m;
 int h;

 if (deftbl[inst] != DEF_UNKNOWN) return(deftbl[inst]);
 l = 0;
 h = instr_def_n - 1;
 while (h-l > 1)
  { m = (h + l) / 2;
    if (inst >= instr_defs[m].value)
     { l = m;
     }
    else
     { h = m;
     }
  }
 if ((inst & instr_defs[l].mask) != instr_defs[l].value) l = DEF_UNUSED;
 deftbl[inst] = l;
 return(l);
}
