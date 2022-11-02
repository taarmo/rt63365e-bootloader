
#ifndef __REGS_H__
#define __REGS_H__

#include "regdef.h"
#include "m32c0.h"
#include "types.h"

struct reg_struct{
	u32 pc;
	u32 v0;
	u32 v1;
	u32 v2;
	u32 a0;
	u32 a1;
	u32 a2;
	u32 a3;
	u32 a4;
	u32 a5;
	u32 a6;
	u32 a7;
	u32 a8;
	u32 t0;
	u32 t1;
	u32 t2;
	u32 t3;
	u32 t4;
	u32 t5;
	u32 t6;
	u32 t7;
	u32 t8;
	u32 s0;
	u32 s1;
	u32 s2;
	u32 s3;
	u32 s4;
	u32 s5;
	u32 s6;
	u32 s7;
	u32 s8;
};

#endif
