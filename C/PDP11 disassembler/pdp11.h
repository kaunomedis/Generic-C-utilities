#ifndef _PDP11_H_b81538e2_
#define _PDP11_H_b81538e2_

/* This file is in the public domain. */

#include <setjmp.h>

#include "pdp11types.h"

#define CORESIZE 0x100000 /* 1Mb: bytes of core present in the machine */

/* there is code that assumes mode1<mode2 means mode1 is more priviliged than mode2 */
#define MODE_K 0
#define MODE_S 1
#define MODE_X 2 /* not used */
#define MODE_U 3

extern word genregs[2][6];
extern word *regset;
#define r0 (regset[0])
#define r1 (regset[1])
#define r2 (regset[2])
#define r3 (regset[3])
#define r4 (regset[4])
#define r5 (regset[5])
extern word sps[4];
extern word *spp;
extern word pc;
#define sp (*spp)
#define r6 sp
#define r7 pc
extern word *regs[8];
extern word psw;
#define PSW_CM  0140000
#define PSW_CM_SHIFT  14
#define PSW_PM  0030000
#define PSW_PM_SHIFT  12
#define PSW_RS  0004000
#define PSW_PRI 0000340
#define PSW_PRI_SHIFT  5
#define PSW_T   0000020
#define PSW_N   0000010
#define PSW_Z   0000004
#define PSW_V   0000002
#define PSW_C   0000001
#define PSW_MBZ 0003400
#define PSW_CC  (PSW_N|PSW_Z|PSW_V|PSW_C)
#define SET_N() (psw|=PSW_N)
#define SET_Z() (psw|=PSW_Z)
#define SET_V() (psw|=PSW_V)
#define SET_C() (psw|=PSW_C)
#define CLR_N() (psw&=~PSW_N)
#define CLR_Z() (psw&=~PSW_Z)
#define CLR_V() (psw&=~PSW_V)
#define CLR_C() (psw&=~PSW_C)
extern word cpu_error;
#define CPUERR_ILL_HALT 0000200
#define CPUERR_ADDR_ERR 0000100
#define CPUERR_NXM_ERR  0000040
#define CPUERR_IO_TIMO  0000020
#define CPUERR_Y_STACK  0000010
#define CPUERR_R_STACK  0000004
#define CPUERR_MBZ      0177403
extern word pirq;
extern word maint;
#define MAINT_BOOTADDR 0170000
#define MAINT_BOOTADDR_SHIFT 12
#define MAINT_FPAAVAIL 0000400
#define MAINT_MODULEID 0000360
#define MAINT_MODULEID_KDJ11A 0000040
#define MAINT_HALTOPT  0000010
#define MAINT_POWEROPT 0000006
#define MAINT_POWEROPT_TRAP24   0000000
#define MAINT_POWEROPT_ODT      0000002
#define MAINT_POWEROPT_173000   0000004
#define MAINT_POWEROPT_USERBOOT 0000006
#define MAINT_DCOK     0000001
#define MAINT_MBZ      0007000
extern word fps;
#define FPS_FER  0100000
#define FPS_FID  0040000
#define FPS_FIUV 0004000
#define FPS_FIU  0002000
#define FPS_FIV  0001000
#define FPS_FIC  0000400
#define FPS_FD   0000200
#define FPS_FL   0000100
#define FPS_FT   0000040
#define FPS_FN   0000010
#define FPS_FZ   0000004
#define FPS_FV   0000001
#define FPS_FC   0000001
#define FPS_MBZ  0030020
#define FPS_CC  (FPS_N|FPS_Z|FPS_V|FPS_C)
#define SET_FN() (fps|=FPS_FN)
#define SET_FZ() (fps|=FPS_FZ)
#define SET_FV() (fps|=FPS_FV)
#define SET_FC() (fps|=FPS_FC)
#define CLR_FN() (fps&=~FPS_FN)
#define CLR_FZ() (fps&=~FPS_FZ)
#define CLR_FV() (fps&=~FPS_FV)
#define CLR_FC() (fps&=~FPS_FC)
extern word fec;
#define FEC_INVOPC  2
#define FEC_DIV0    4
#define FEC_CIERR   6
#define FEC_OVER    8
#define FEC_UNDER  10
#define FEC_MINUS0 12
extern word fea;
extern dfword facc[6];
extern pagedesc pdesc[4][2][8]; /* access mode, i/d, page # */
typedef enum aspace ASPACE;
enum aspace {
  MMAN_ISPACE = 0,
  MMAN_DSPACE = 1
  } ;
#define PDR_NC  0100000
#define PDR_LEN 0077400
#define PDR_LEN_SHIFT 8
#define PDR_W   0000100
#define PDR_ED  0000010
#define PDR_ACC 0000006
#define PDR_ACC_NONRESIDENT 0000000
#define PDR_ACC_READONLY    0000002
#define PDR_ACC_READWRITE   0000006
#define PDR_MBZ 0000261
extern word mmr0;
#define MMR0_NONRES   0100000
#define MMR0_LEN_ERR  0040000
#define MMR0_RO_ERR   0020000
#define MMR0_ACCMODE  0000140
#define MMR0_ACCMODE_SHIFT 5
#define MMR0_ID_SPACE 0000020
#define MMR0_ID_SPACE_SHIFT 4
#define MMR0_PAGENO   0000016
#define MMR0_PAGENO_SHIFT 1
#define MMR0_MM_ENB   0000001
#define MMR0_MBZ      0017600
#define MMR0_RO       (MMR0_ACCMODE|MMR0_ID_SPACE|MMR0_PAGENO)
#define MMR0_FREEZE   (MMR0_ACCMODE|MMR0_ID_SPACE|MMR0_PAGENO)
extern word mmr1;
#define MMR1_CHANGE 0370
#define MMR1_REGNO  0007
extern word mmr2;
#define MMR_FROZEN (mmr0 & (MMR0_NONRES|MMR0_LEN_ERR|MMR0_RO_ERR))
extern word mmr3;
#define MMR3_UNINTERP 0000040
#define MMR3_22_BIT   0000020
#define MMR3_CSM_ENB  0000010
#define MMR3_MAPEN_K  0000004
#define MMR3_MAPEN_S  0000002
#define MMR3_MAPEN_U  0000001
#define MMR3_MBZ      0177700
extern word cache_control;
#define CACHECTL_TAG_WWP   0002000
#define CACHECTL_BYPASS    0001000
#define CACHECTL_FLUSH     0000400
#define CACHECTL_PE_ENB    0000200
#define CACHECTL_DATA_WWP  0000100
#define CACHECTL_UNINTERP  0000060
#define CACHECTL_FORCEMISS 0000014
#define CACHECTL_DIAG_MODE 0000002
#define CACHECTL_CPI_DIS   0000001
#define CACHECTL_MBZ       0174000
extern word hitmiss;
extern word mem_sys_err;
#define MEM_SYS_ERR_PE_ABORT 0100000
#define MEM_SYS_ERR_PE_HIGH  0000200
#define MEM_SYS_ERR_PE_LOW   0000100
#define MEM_SYS_ERR_TAG_PE   0000040
#define MEM_SYS_ERR_MBZ      0077437
extern word stack_limit;
extern word micro_break;
extern word console_switch;
extern ubamap ubam[8];

extern unsigned char core[];

extern int pswc_cm;
extern int pswc_pri;
#define KERNELMODE() (pswc_cm==MODE_K)

extern int pending;
#define PEND_TRACE  0x00000001
#define PEND_YSTACK 0x00000002
extern int halted;
extern int dma_inhibit;
extern int sigio_recvd;

extern int notraps;
extern jmp_buf notraps_jmp;

extern void checkpsw(void);
extern void clear1pac(ASPACE, int);
extern void trapto(word);
extern void bugchk(const char *, ...) __attribute__((__noreturn__));
extern void busreset(void);

#endif
