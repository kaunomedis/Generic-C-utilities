#ifndef _INSTRTBL_H_9188d7bf_
#define _INSTRTBL_H_9188d7bf_

/* This file is in the public domain. */

#include "pdp11types.h"
#ifdef NEED_FUNCTIONS
#include "instr-fxns.h"
#endif

typedef enum instr_ops INSTR_OPS;
typedef struct instr_def INSTR_DEF;

enum instr_ops {
  OPS_NONE = 0,
  OPS_G0,
  OPS_R0,
  OPS_O30,
  OPS_B80,
  OPS_R6_G0,
  OPS_G0_R6,
  OPS_G6_G0,
  OPS_R6_B60,
  OPS_O80,
  OPS_O60,
  OPS_F0,
  OPS_FA6_F0,
  OPS_F0_FA6,
  OPS_FA6_G0,
  OPS_G0_FA6,
  OPS_D0,
  OPS_FA6_D0,
  OPS_D0_FA6
  } ;

struct instr_def {
  word mask;
  word value;
  const char *name;
  void (*fxn)(word);
  INSTR_OPS ops_format;
  } ;

#ifdef NEED_NAME
#define INSTRTBL_NAME(n) (n),
#else
#define INSTRTBL_NAME(n) 0,
#endif
#ifdef NEED_FUNCTIONS
#define INSTRTBL_FXN(f) (f),
#else
#define INSTRTBL_FXN(f) 0,
#endif
#ifdef NEED_OPFORMATS
#define INSTRTBL_OPFMT(o) (o),
#else
#define INSTRTBL_OPFMT(o) 0,
#endif
#define INSTRTBL_LINE(mask,value,name,fxn,ops) { mask, value, INSTRTBL_NAME(name) INSTRTBL_FXN(fxn) INSTRTBL_OPFMT(ops) }

#ifdef NEED_EXTERN
extern INSTR_DEF instr_defs[];
extern int instr_def_n;
#endif

#if defined(NEED_DEFS) || defined(NEED_ALT_DEFS)
INSTR_DEF instr_defs[]
= {
#endif
#ifdef NEED_DEFS
    INSTRTBL_LINE( 0177777, 0000000, "halt",   I_halt,     OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000001, "wait",   I_wait,     OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000002, "rti",    I_rti,      OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000003, "bpt",    I_bpt,      OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000004, "iot",    I_iot,      OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000005, "reset",  I_reset,    OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000006, "rtt",    I_rtt,      OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000007, "mfpt",   I_mfpt,     OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000010, "emhalt", I_emhalt,   OPS_NONE   ),
    INSTRTBL_LINE( 0177700, 0000100, "jmp",    I_jmp,      OPS_G0     ),
    INSTRTBL_LINE( 0177770, 0000200, "rts",    I_rts,      OPS_R0     ),
    INSTRTBL_LINE( 0177770, 0000230, "spl",    I_spl,      OPS_O30    ),
    INSTRTBL_LINE( 0177777, 0000240, "nop",    I_nop,      OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000241, "clc",    I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000242, "clv",    I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000243, "clvc",   I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000244, "clz",    I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000245, "clzc",   I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000246, "clzv",   I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000247, "clzvc",  I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000250, "cln",    I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000251, "clnc",   I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000252, "clnv",   I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000253, "clnvc",  I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000254, "clnz",   I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000255, "clnzc",  I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000256, "clnzv",  I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000257, "ccc",    I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000261, "sec",    I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000262, "sev",    I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000263, "sevc",   I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000264, "sez",    I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000265, "sezc",   I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000266, "sezv",   I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000267, "sezvc",  I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000270, "sen",    I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000271, "senc",   I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000272, "senv",   I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000273, "senvc",  I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000274, "senz",   I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000275, "senzc",  I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000276, "senzv",  I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0000277, "scc",    I_condcode, OPS_NONE   ),
    INSTRTBL_LINE( 0177700, 0000300, "swab",   I_swab,     OPS_G0     ),
    INSTRTBL_LINE( 0177400, 0000400, "br",     I_cbranch,  OPS_B80    ),
    INSTRTBL_LINE( 0177400, 0001000, "bne",    I_cbranch,  OPS_B80    ),
    INSTRTBL_LINE( 0177400, 0001400, "beq",    I_cbranch,  OPS_B80    ),
    INSTRTBL_LINE( 0177400, 0002000, "bge",    I_cbranch,  OPS_B80    ),
    INSTRTBL_LINE( 0177400, 0002400, "blt",    I_cbranch,  OPS_B80    ),
    INSTRTBL_LINE( 0177400, 0003000, "bgt",    I_cbranch,  OPS_B80    ),
    INSTRTBL_LINE( 0177400, 0003400, "ble",    I_cbranch,  OPS_B80    ),
    INSTRTBL_LINE( 0177000, 0004000, "jsr",    I_jsr,      OPS_R6_G0  ),
    INSTRTBL_LINE( 0177700, 0005000, "clr",    I_clr,      OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0005100, "com",    I_com,      OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0005200, "inc",    I_inc,      OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0005300, "dec",    I_dec,      OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0005400, "neg",    I_neg,      OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0005500, "adc",    I_adc,      OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0005600, "sbc",    I_sbc,      OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0005700, "tst",    I_tst,      OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0006000, "ror",    I_ror,      OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0006100, "rol",    I_rol,      OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0006200, "asr",    I_asr,      OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0006300, "asl",    I_asl,      OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0006400, "mark",   I_mark,     OPS_O60    ),
    INSTRTBL_LINE( 0177700, 0006500, "mfpd",   I_mfpd,     OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0006600, "mtpi",   I_mtpi,     OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0006700, "sxt",    I_sxt,      OPS_G0     ),
    INSTRTBL_LINE( 0177777, 0007100, "csm",    I_csm,      OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0007200, "tstset", I_tstset,   OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0007600, "wrtlck", I_wrtlck,   OPS_G0     ),
    INSTRTBL_LINE( 0170000, 0010000, "mov",    I_mov,      OPS_G6_G0  ),
    INSTRTBL_LINE( 0170000, 0020000, "cmp",    I_cmp,      OPS_G6_G0  ),
    INSTRTBL_LINE( 0170000, 0030000, "bit",    I_bit,      OPS_G6_G0  ),
    INSTRTBL_LINE( 0170000, 0040000, "bic",    I_bic,      OPS_G6_G0  ),
    INSTRTBL_LINE( 0170000, 0050000, "bis",    I_bis,      OPS_G6_G0  ),
    INSTRTBL_LINE( 0170000, 0060000, "add",    I_add,      OPS_G6_G0  ),
    INSTRTBL_LINE( 0177000, 0070000, "mul",    I_mul,      OPS_G0_R6  ),
    INSTRTBL_LINE( 0177000, 0071000, "div",    I_div,      OPS_G0_R6  ),
    INSTRTBL_LINE( 0177000, 0072000, "ash",    I_ash,      OPS_G0_R6  ),
    INSTRTBL_LINE( 0177000, 0073000, "ashc",   I_ashc,     OPS_G0_R6  ),
    INSTRTBL_LINE( 0177000, 0074000, "xor",    I_xor,      OPS_R6_G0  ),
#if 0
    INSTRTBL_LINE( 0177770, 0075000, "fadd",   I_fadd,     OPS_R0     ),
    INSTRTBL_LINE( 0177770, 0075010, "fsub",   I_fsub,     OPS_R0     ),
    INSTRTBL_LINE( 0177770, 0075020, "fmul",   I_fmul,     OPS_R0     ),
    INSTRTBL_LINE( 0177770, 0075030, "fdiv",   I_fdiv,     OPS_R0     ),
#endif
    INSTRTBL_LINE( 0177000, 0077000, "sob",    I_sob,      OPS_R6_B60 ),
    INSTRTBL_LINE( 0177400, 0100000, "bpl",    I_cbranch,  OPS_B80    ),
    INSTRTBL_LINE( 0177400, 0100400, "bmi",    I_cbranch,  OPS_B80    ),
    INSTRTBL_LINE( 0177400, 0101000, "bhi",    I_cbranch,  OPS_B80    ),
    INSTRTBL_LINE( 0177400, 0101400, "blos",   I_cbranch,  OPS_B80    ),
    INSTRTBL_LINE( 0177400, 0102000, "bvc",    I_cbranch,  OPS_B80    ),
    INSTRTBL_LINE( 0177400, 0102400, "bvs",    I_cbranch,  OPS_B80    ),
    INSTRTBL_LINE( 0177400, 0103000, "bhis",   I_cbranch,  OPS_B80    ),
    INSTRTBL_LINE( 0177400, 0103400, "blo",    I_cbranch,  OPS_B80    ),
    INSTRTBL_LINE( 0177400, 0104000, "emt",    I_emt,      OPS_O80    ),
    INSTRTBL_LINE( 0177400, 0104400, "trap",   I_trap,     OPS_O80    ),
    INSTRTBL_LINE( 0177700, 0105000, "clrb",   I_clr,      OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0105100, "comb",   I_com,      OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0105200, "incb",   I_inc,      OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0105300, "decb",   I_dec,      OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0105400, "negb",   I_neg,      OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0105500, "adcb",   I_adc,      OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0105600, "sbcb",   I_sbc,      OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0105700, "tstb",   I_tst,      OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0106000, "rorb",   I_ror,      OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0106100, "rolb",   I_rol,      OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0106200, "asrb",   I_asr,      OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0106300, "aslb",   I_asl,      OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0106400, "mtps",   I_mtps,     OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0106500, "mfpi",   I_mfpi,     OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0106600, "mtpd",   I_mtpd,     OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0106700, "mfps",   I_mfps,     OPS_G0     ),
    INSTRTBL_LINE( 0170000, 0110000, "movb",   I_mov,      OPS_G6_G0  ),
    INSTRTBL_LINE( 0170000, 0120000, "cmpb",   I_cmp,      OPS_G6_G0  ),
    INSTRTBL_LINE( 0170000, 0130000, "bitb",   I_bit,      OPS_G6_G0  ),
    INSTRTBL_LINE( 0170000, 0140000, "bicb",   I_bic,      OPS_G6_G0  ),
    INSTRTBL_LINE( 0170000, 0150000, "bisb",   I_bis,      OPS_G6_G0  ),
    INSTRTBL_LINE( 0170000, 0160000, "sub",    I_sub,      OPS_G6_G0  ),
    INSTRTBL_LINE( 0177777, 0170000, "cfcc",   I_cfcc,     OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0170001, "setf",   I_setf,     OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0170002, "seti",   I_seti,     OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0170011, "setd",   I_setd,     OPS_NONE   ),
    INSTRTBL_LINE( 0177777, 0170012, "setl",   I_setl,     OPS_NONE   ),
    INSTRTBL_LINE( 0177700, 0170100, "ldfps",  I_ldfps,    OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0170200, "stfps",  I_stfps,    OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0170300, "stst",   I_stst,     OPS_G0     ),
    INSTRTBL_LINE( 0177700, 0170400, "clrf",   I_clrf,     OPS_F0     ),
    INSTRTBL_LINE( 0177700, 0170500, "tstf",   I_tstf,     OPS_F0     ),
    INSTRTBL_LINE( 0177700, 0170600, "absf",   I_absf,     OPS_F0     ),
    INSTRTBL_LINE( 0177700, 0170700, "negf",   I_negf,     OPS_F0     ),
    INSTRTBL_LINE( 0177400, 0171000, "mulf",   I_mulf,     OPS_F0_FA6 ),
    INSTRTBL_LINE( 0177400, 0171400, "modf",   I_modf,     OPS_F0_FA6 ),
    INSTRTBL_LINE( 0177400, 0172000, "addf",   I_addf,     OPS_F0_FA6 ),
    INSTRTBL_LINE( 0177400, 0172400, "ldf",    I_ldf,      OPS_F0_FA6 ),
    INSTRTBL_LINE( 0177400, 0173000, "subf",   I_subf,     OPS_F0_FA6 ),
    INSTRTBL_LINE( 0177400, 0173400, "cmpf",   I_cmpf,     OPS_F0_FA6 ),
    INSTRTBL_LINE( 0177400, 0174000, "stf",    I_stf,      OPS_FA6_F0 ),
    INSTRTBL_LINE( 0177400, 0174400, "divf",   I_divf,     OPS_F0_FA6 ),
    INSTRTBL_LINE( 0177400, 0175000, "stexp",  I_stexp,    OPS_FA6_G0 ),
    INSTRTBL_LINE( 0177400, 0175400, "stcfi",  I_stcfi,    OPS_FA6_G0 ),
    INSTRTBL_LINE( 0177400, 0176000, "stcfd",  I_stcfd,    OPS_FA6_D0 ),
    INSTRTBL_LINE( 0177400, 0176400, "ldexp",  I_ldexp,    OPS_G0_FA6 ),
    INSTRTBL_LINE( 0177400, 0177000, "ldcif",  I_ldcif,    OPS_G0_FA6 ),
    INSTRTBL_LINE( 0177400, 0177400, "ldcdf",  I_ldcdf,    OPS_D0_FA6 ),
#endif
#ifdef NEED_ALT_DEFS
    INSTRTBL_LINE( 0177400, 0103000, "bcc",    I_cbranch,  OPS_B80    ),
    INSTRTBL_LINE( 0177400, 0103400, "bcs",    I_cbranch,  OPS_B80    ),
    INSTRTBL_LINE( 0177700, 0170400, "clrd",   I_clrf,     OPS_D0     ),
    INSTRTBL_LINE( 0177700, 0170500, "tstd",   I_tstf,     OPS_D0     ),
    INSTRTBL_LINE( 0177700, 0170600, "absd",   I_absf,     OPS_D0     ),
    INSTRTBL_LINE( 0177700, 0170700, "negd",   I_negf,     OPS_D0     ),
    INSTRTBL_LINE( 0177400, 0171000, "muld",   I_mulf,     OPS_D0_FA6 ),
    INSTRTBL_LINE( 0177400, 0171400, "modd",   I_modf,     OPS_D0_FA6 ),
    INSTRTBL_LINE( 0177400, 0172000, "addd",   I_addf,     OPS_D0_FA6 ),
    INSTRTBL_LINE( 0177400, 0172400, "ldd",    I_ldf,      OPS_D0_FA6 ),
    INSTRTBL_LINE( 0177400, 0173000, "subd",   I_subf,     OPS_D0_FA6 ),
    INSTRTBL_LINE( 0177400, 0173400, "cmpd",   I_cmpf,     OPS_D0_FA6 ),
    INSTRTBL_LINE( 0177400, 0174000, "std",    I_stf,      OPS_FA6_D0 ),
    INSTRTBL_LINE( 0177400, 0174400, "divd",   I_divf,     OPS_D0_FA6 ),
    INSTRTBL_LINE( 0177400, 0175400, "stcfl",  I_stcfi,    OPS_FA6_G0 ),
    INSTRTBL_LINE( 0177400, 0175400, "stcdi",  I_stcfi,    OPS_FA6_G0 ),
    INSTRTBL_LINE( 0177400, 0175400, "stcdl",  I_stcfi,    OPS_FA6_G0 ),
    INSTRTBL_LINE( 0177400, 0176000, "stcdf",  I_stcfd,    OPS_FA6_F0 ),
    INSTRTBL_LINE( 0177400, 0177000, "ldclf",  I_ldcif,    OPS_G0_FA6 ),
    INSTRTBL_LINE( 0177400, 0177000, "ldcid",  I_ldcif,    OPS_G0_FA6 ),
    INSTRTBL_LINE( 0177400, 0177000, "ldcld",  I_ldcif,    OPS_G0_FA6 ),
    INSTRTBL_LINE( 0177400, 0177400, "ldcfd",  I_ldcdf,    OPS_F0_FA6 ),
#endif
#if defined(NEED_DEFS) || defined(NEED_ALT_DEFS)
    };
int instr_def_n = (sizeof(instr_defs) / sizeof(instr_defs[0]));
#endif

#undef INSTRTBL_NAME
#undef INSTRTBL_FXN
#undef INSTRTBL_LINE
#undef INSTRTBL_OPFMT

#endif
