char *__progname = "disas11";

/* This file is in the public domain. */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>


#define NEED_NAME
#define NEED_OPFORMATS
#define NEED_DEFS
#define NEED_ALT_DEFS
#include "instrtbl.h"


#include "disas.h"

#include "deftbl.h"


#include "heapsort.h"





unsigned char core[65536];
static unsigned char wrotecore[65536];

static const char *initialfn;

void bugchk(const char *, ...) __attribute__((__noreturn__));
void bugchk(const char *fmt, ...)
{
 va_list ap;

 va_start(ap,fmt);
 fprintf(stderr,"%s: INTERNAL BUG: ",__progname);
 vfprintf(stderr,fmt,ap);
 fprintf(stderr,"\n");
 va_end(ap);
 abort();
}

static void initcore(void)
{
 //bzero(&wrotecore[0],65536);
 memset (wrotecore,0,65536);
}

static void loadcore(const char *fn)
{
 FILE *f;
 unsigned long int addr;
 unsigned long int count;
 int value;

 f = fopen(fn,"r");
 if (f == 0)
  { fprintf(stderr,"%s: can't open %s for reading\n",__progname,fn);
    exit(1);
  }
 while (1)
  { if (fscanf(f,"%lx%lx",&addr,&count) != 2) break;
    for (;count>0;count--)
     { if (fscanf(f,"%x",&value) != 1) break;
       addr &= 0xffff;
       core[addr] = value & 0xff;
       wrotecore[addr] = 1;
       addr ++;
     }
  }
 fclose(f);
}

static void initinstrs(void)
{
 deftbl_init();
}

word fetchword(word addr, ASPACE space __attribute__((__unused__)))
{
 return(core[addr]|(core[addr+1]<<8));
}

void put(char c)
{
 putchar(c);
}

void put_s(const char *s)
{
 for (;*s;s++) put(*s);
}

void put_x8(unsigned long int val)
{
 int i;

 val &= 0xffffffff;
 for (i=28;i>=0;i-=4) put("0123456789abcdef"[(val>>i)&0xf]);
}

void put_6(word val)
{
 int i;

 val &= 0xffff;
 for (i=15;i>=0;i-=3) put('0'+((val>>i)&7));
}

void put_3(word val)
{
 put('0'+((val>>6)&3));
 put('0'+((val>>3)&7));
 put('0'+(val&7));
}

void put_2(word val)
{
 put('0'+((val>>3)&7));
 put('0'+(val&7));
}

word fps = 0;

static void dumpasm(void)
{
 unsigned long int addr;
 int addrinc;

 addrinc = 0;
 for (addr=0;addr<65536;addr+=2)
  { if (wrotecore[addr])
     { if (addrinc > 0)
	{ printf("%40s","");
	  disas(addr&0xfffe);
	}
       else
	{ addrinc = disas(addr&0xfffe);
	}
       printf("\n");
     }
    addrinc -= 2;
  }
}

int main(int, char **);
int main(int ac, char **av)
{
 int skip;
 int errs;
 int argno;

 if (0)
  {
usage:;
    fprintf(stderr,"Usage: %s initial-core-file\n",__progname);
    exit(1);
  }
 skip = 0;
 errs = 0;
 argno = 0;
 for (ac--,av++;ac;ac--,av++)
  { if (skip > 0)
     { skip --;
       continue;
     }
    if (**av == '-')
     { for (++*av;**av;++*av)
	{ fprintf(stderr,"%s: bad flag -%c\n",__progname,**av);
	  errs ++;
	}
     }
    else
     { switch (argno++)
	{ default:
	     fprintf(stderr,"%s: extra argument %s\n",__progname,*av);
	     errs ++;
	     break;
	  case 0:
	     initialfn = *av;
	     break;
	}
     }
  }
 if (errs) goto usage;
 if (! initialfn) goto usage;
 initcore();
 initinstrs();
 loadcore(initialfn);
 dumpasm();
 exit(0);
}
