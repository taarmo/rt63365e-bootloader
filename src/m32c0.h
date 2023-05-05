/*
 * Copyright (c) 1999-2003 MIPS Technologies, Inc.  All rights reserved.
 * 
 * Unpublished rights (if any) reserved under the copyright laws of the
 * United States of America and other countries.
 * 
 * This code is proprietary to MIPS Technologies, Inc. ("MIPS
 * Technologies").  Any copying, reproducing, modifying or use of this
 * code (in whole or in part) that is not expressly permitted in writing
 * by MIPS Technologies or an authorized third party is strictly
 * prohibited.  At a minimum, this code is protected under unfair
 * competition and copyright laws.  Violations thereof may result in
 * criminal penalties and fines.
 * 
 * MIPS Technologies reserves the right to change this code to improve
 * function, design or otherwise.  MIPS Technologies does not assume any
 * liability arising out of the application or use of this code, or of
 * any error or omission in such code.  Any warranties, whether express,
 * statutory, implied or otherwise, including but not limited to the
 * implied warranties of merchantability or fitness for a particular
 * purpose, are excluded.  Except as expressly provided in any written
 * license agreement from MIPS Technologies or an authorized third party,
 * the furnishing of this code does not give recipient any license to any
 * intellectual property rights, including any patent rights, that cover
 * this code.
 * 
 * This code shall not be exported or transferred for the purpose of
 * reexporting in violation of any U.S. or non-U.S. regulation, treaty,
 * Executive Order, law, statute, amendment or supplement thereto.
 * 
 * This code constitutes one or more of the following: commercial
 * computer software, commercial computer software documentation or other
 * commercial items.  If the user of this code, or any related
 * documentation of any kind, including related technical data or
 * manuals, is an agency, department, or other entity of the United
 * States government ("Government"), the use, duplication, reproduction,
 * release, modification, disclosure, or transfer of this code, or any
 * related documentation of any kind, is restricted in accordance with
 * Federal Acquisition Regulation 12.212 for civilian agencies and
 * Defense Federal Acquisition Regulation Supplement 227.7202 for
 * military agencies.  The use of this code by the Government is further
 * restricted in accordance with the terms of the license agreement(s)
 * and/or applicable contract terms and conditions covering this code
 * from MIPS Technologies or an authorized third party.
 */

/*
 * m32c0.h : MIPS32 coprocessor 0 definitions
 */

#define _M32C0_H_


/* FPU Control/Status register fields */
#define	CSR_FS		0x01000000	/* Set to flush denormals to zero */
#define	CSR_C		0x00800000	/* Condition bit (set by FP compare) */

#define	CSR_CMASK	(0x3f<<12)
#define	CSR_CE		0x00020000
#define	CSR_CV		0x00010000
#define	CSR_CZ		0x00008000
#define	CSR_CO		0x00004000
#define	CSR_CU		0x00002000
#define	CSR_CI		0x00001000

#define	CSR_EMASK	(0x1f<<7)
#define	CSR_EV		0x00000800
#define	CSR_EZ		0x00000400
#define	CSR_EO		0x00000200
#define	CSR_EU		0x00000100
#define	CSR_EI		0x00000080

#define	CSR_FMASK	(0x1f<<2)
#define	CSR_FV		0x00000040
#define	CSR_FZ		0x00000020
#define	CSR_FO		0x00000010
#define	CSR_FU		0x00000008
#define	CSR_FI		0x00000004

#define	CSR_RMODE_MASK	(0x3<<0)
#define	CSR_RM		0x00000003
#define	CSR_RP		0x00000002
#define	CSR_RZ		0x00000001
#define	CSR_RN		0x00000000
#define	CAUSE_EXCMASK	0x0000003C	/* Cause code bits */
#define	CAUSE_EXCSHIFT	2

#define R_SZ 4


#define SIGHUP   1
#define SIGINT   2
#define SIGQUIT  3
#define SIGILL   4
#define SIGTRAP  5
#define SIGIOT   6
#define SIGFPE   8
#define SIGKILL  9
#define SIGBUS   10
#define SIGSEGV  11
#define SIGSYS   12
#define SIGTERM  15

/* MIPS32-specific MMU interface */
/*
 * MIPS32 Exception Codes
 */
#define EXC_INTR	0	/* interrupt */
#define EXC_MOD		1	/* tlb modification */
#define EXC_TLBL	2	/* tlb miss (load/i-fetch) */
#define EXC_TLBS	3	/* tlb miss (store) */
#define EXC_ADEL	4	/* address error (load/i-fetch) */
#define EXC_ADES	5	/* address error (store) */
#define EXC_IBE		6	/* bus error (i-fetch) */
#define EXC_DBE		7	/* data bus error (load/store) */
#define EXC_SYS		8	/* system call */
#define EXC_BP		9	/* breakpoint */
#define EXC_RI		10	/* reserved instruction */
#define EXC_CPU		11	/* coprocessor unusable */
#define EXC_OVF		12	/* integer overflow */
#define EXC_TRAP	13	/* trap exception */
#define EXC_RES14	14
#define EXC_FPE		15	/* floating point exception */
#define EXC_IS1		16	/* implementation-specific 1 */
#define EXC_IS2		17	/* implementation-specific 2 */
#define EXC_C2E		18	/* coprocessor 2 exception */
#define EXC_RES19	19
#define EXC_RES20	20
#define EXC_RES21	21
#define EXC_RES22	22
#define EXC_WATCH	23	/* watchpoint */
#define EXC_MCHECK	24	/* machine check */
#define EXC_RES25	25
#define EXC_RES26	26
#define EXC_RES27	27
#define EXC_RES28	28
#define EXC_RES29	29
#define EXC_RES30	30
#define EXC_RES31	31


/*
 * MIPS32 Cause Register (CP0 Register 13, Select 0)
 */
#define CR_BD		0x80000000	/* branch delay */
#define CR_TI		0x40000000	/* timer interrupt (r2) */
#define CR_CEMASK	0x30000000      /* coprocessor used */
#define CR_CESHIFT	28
#define CR_DC		0x08000000	/* disable count (r2) */
#define CR_PCI		0x04000000	/* performance counter i/u (r2) */
#define CR_IV		0x00800000	/* use special i/u vec */
#define CR_WP		0x00400000	/* deferred watchpoint */

/* interrupt pending bits */
#define CR_SINT0	0x00000100 	/* s/w interrupt 0 */
#define CR_SINT1	0x00000200	/* s/w interrupt 1 */
#define CR_HINT0	0x00000400	/* h/w interrupt 0 */
#define CR_HINT1	0x00000800	/* h/w interrupt 1 */
#define CR_HINT2	0x00001000	/* h/w interrupt 2 */
#define CR_HINT3	0x00002000	/* h/w interrupt 3 */
#define CR_HINT4	0x00004000	/* h/w interrupt 4 */
#define CR_HINT5	0x00008000	/* h/w interrupt 5 */

/* alternative interrupt pending bit naming */
#define CR_IP0		0x00000100
#define CR_IP1		0x00000200
#define CR_IP2		0x00000400
#define CR_IP3		0x00000800
#define CR_IP4		0x00001000
#define CR_IP5		0x00002000
#define CR_IP6		0x00004000
#define CR_IP7		0x00008000

#define CR_IMASK	0x0000ff00 	/* interrupt pending mask */
#define CR_XMASK	0x0000007c 	/* exception code mask */
#define CR_XCPT(x)	((x)<<2)


/*
 * MIPS32 Status Register  (CP0 Register 12, Select 0)
 */
#define SR_IE		0x00000001 	/* interrupt enable */
#define SR_EXL		0x00000002	/* exception level */
#define SR_ERL		0x00000004	/* error level */

#define SR_UM		0x00000010	/* user mode */
#define SR_KSU_MASK	0x00000018	/* ksu mode mask */
#define SR_KSU_USER	0x00000010	/* user mode */
#define SR_KSU_SPVS	0x00000008	/* supervisor mode */
#define SR_KSU_KERN	0x00000000	/* kernel mode */

/* interrupt mask bits */
#define SR_SINT0	0x00000100	/* enable s/w interrupt 0 */
#define SR_SINT1	0x00000200	/* enable s/w interrupt 1 */
#define SR_HINT0	0x00000400	/* enable h/w interrupt 1 */
#define SR_HINT1	0x00000800	/* enable h/w interrupt 2 */
#define SR_HINT2	0x00001000	/* enable h/w interrupt 3 */
#define SR_HINT3	0x00002000	/* enable h/w interrupt 4 */
#define SR_HINT4	0x00004000	/* enable h/w interrupt 5 */
#define SR_HINT5	0x00008000	/* enable h/w interrupt 6 */

/* alternative interrupt mask naming */
#define SR_IM0		0x00000100
#define SR_IM1		0x00000200
#define SR_IM2		0x00000400
#define SR_IM3		0x00000800
#define SR_IM4		0x00001000
#define SR_IM5		0x00002000
#define SR_IM6		0x00004000
#define SR_IM7		0x00008000

#define SR_IMASK	0x0000ff00

#define SR_NMI		0x00080000 	/* NMI occurred */
#define SR_SR		0x00100000	/* soft reset occurred */
#define SR_TS		0x00200000	/* TLB shutdown */
#define SR_BEV		0x00400000	/* boot exception vectors */
#define SR_PX		0x00800000	/* user 64-bit reg / 32-bit addr */
#define SR_MX		0x01000000	/* enable MDMX ASE */
#define SR_RE		0x02000000	/* reverse endian (user mode) */
#define SR_FR		0x04000000	/* 64-bit fpu registers */
#define SR_RP		0x08000000	/* reduce power */

#define SR_CU0		0x10000000	/* coprocessor 0 enable */
#define SR_CU1		0x20000000	/* coprocessor 1 enable */
#define SR_CU2		0x40000000	/* coprocessor 2 enable */
#define SR_CU3		0x80000000	/* coprocessor 3 enable */


/*
 * MIPS32 Config0 Register  (CP0 Register 16, Select 0)
 */
#define CFG0_M		0x80000000	/* Config1 implemented */
#define CFG0_BE		0x00008000	/* Big Endian */
#define CFG0_ATMASK	0x00006000	/* Architecture type: */
#define CFG0_AT_M32	 (0<<13)	 /* MIPS32 */
#define CFG0_AT_M64_A32 (1<<13)	 /* MIPS64, 32-bit addresses */
#define CFG0_AT_M64_A64 (2<<13)	 /* MIPS64, 64-bit addresses */
#define CFG0_AT_RES	 (3<<13)
#define CFG0_ARMASK	0x00001c00
#define CFG0_ARSHIFT	10
#define CFG0_MTMASK	0x00000380
#define CFG0_MT_NONE	 (0<<7)
#define CFG0_MT_TLB	 (1<<7)
#define CFG0_MT_BAT	 (2<<7)
#define CFG0_MT_NONSTD	 (3<<7)
#define CFG0_VI		0x00000008	/* Icache is virtual */
#define CFG0_K0MASK	0x00000007	/* KSEG0 coherency algorithm */

/*
 * R4000 compatibility Config Register (actually processor dependent)
 */
#define CFG_BE		CFG0_BE		/* Big Endian */
#define CFG_K0MASK	CFG0_K0MASK	/* KSEG0 coherency algorithm */

/*
 * MIPS32 Config1 Register (CP0 Register 16, Select 1)
 */
#define CFG1_M		0x80000000	/* Config2 implemented */
#define CFG1_MMUSMASK	0x7e000000	/* mmu size - 1 */
#define CFG1_MMUSSHIFT	25
#define CFG1_ISMASK	0x01c00000	/* icache lines 64<<n */
#define CFG1_ISSHIFT	22
#define CFG1_ILMASK	0x00380000	/* icache line size 2<<n */
#define CFG1_ILSHIFT	19
#define CFG1_IAMASK	0x00070000	/* icache ways - 1 */
#define CFG1_IASHIFT	16
#define CFG1_DSMASK	0x0000e000	/* dcache lines 64<<n */
#define CFG1_DSSHIFT	13
#define CFG1_DLMASK	0x00001c00	/* dcache line size 2<<n */
#define CFG1_DLSHIFT	10
#define CFG1_DAMASK	0x00000380	/* dcache ways - 1 */
#define CFG1_DASHIFT	7
#define CFG1_C2		0x00000040	/* Coprocessor 2 present */
#define CFG1_MD		0x00000020	/* MDMX implemented */
#define CFG1_PC		0x00000010	/* performance counters implemented */
#define CFG1_WR		0x00000008	/* watch registers implemented */
#define CFG1_CA		0x00000004	/* compression (mips16) implemented */
#define CFG1_EP		0x00000002	/* ejtag implemented */
#define CFG1_FP		0x00000001	/* fpu implemented */


/*
 * MIPS32r2 Config2 Register (CP0 Register 16, Select 2)
 */
#define CFG2_M		0x80000000	/* Config3 implemented */
#define CFG2_TUMASK	0x70000000	/* tertiary cache control */
#define CFG2_TUSHIFT	28
#define CFG2_TSMASK	0x0f000000	/* tcache sets per wway 64<<n */
#define CFG2_TSSHIFT	24
#define CFG2_TLMASK	0x00f00000	/* tcache line size 2<<n */
#define CFG2_TLSHIFT	20
#define CFG2_TAMASK	0x000f0000	/* tcache ways - 1 */
#define CFG2_TASHIFT	16
#define CFG2_SUMASK	0x0000f000	/* secondary cache control */
#define CFG2_SUSHIFT	12
#define CFG2_SSMASK	0x00000f00	/* scache sets per wway 64<<n */
#define CFG2_SSSHIFT	8
#define CFG2_SLMASK	0x000000f0	/* scache line size 2<<n */
#define CFG2_SLSHIFT	4
#define CFG2_SAMASK	0x0000000f	/* scache ways - 1 */
#define CFG2_SASHIFT	0

/*
 * MIPS32r2 Config2 Register (CP0 Register 16, Select 3)
 */
#define CFG3_M		0x80000000	/* Config4 implemented */
#define CFG3_LPA	0x00000080	/* Large physical addresses */
#define CFG3_VEIC	0x00000040	/* Vectored external i/u controller */
#define CFG3_VI		0x00000020	/* Vectored i/us */
#define CFG3_SP		0x00000010	/* Small page support */
#define CFG3_ISP	0x00000008	/* Instruction ScratchPad */
#define CFG3_DSP	0x00000004	/* Data ScratchPad */
#define CFG3_SM		0x00000002	/* SmartMIPS ASE */
#define CFG3_TL		0x00000001	/* Trace Logic */


/*
 * Primary cache mode
 */
#define CFG_C_WTHRU_NOALLOC	0
#define CFG_C_WTHRU_ALLOC	1
#define CFG_C_UNCACHED		2
#define CFG_C_WBACK		3
#define CFG_C_NONCOHERENT	3
#define CFG_C_COHERENTXCL	4
#define CFG_C_COHERENTXCLW	5 	
#define CFG_C_COHERENTUPD	6
#define CFG_C_UNCACHED_ACCEL	7


/* 
 * Primary Cache TagLo (CP0 Register 28, Select 0/2)
 */
#define TAG_PTAG_MASK           0xffffff00      /* Primary Tag */
#define TAG_PTAG_SHIFT          8
#define TAG_PSTATE_MASK         0x000000c0      /* Primary Cache State */
#define TAG_PSTATE_SHIFT        6
#define TAG_PSTATE_LOCK		0x00000020
#define TAG_PARITY_MASK         0x00000001      /* Primary Tag Parity */
#define TAG_PARITY_SHIFT        0

/* primary cache state (XXX actually implementation specific) */
#define PSTATE_INVAL		0
#define PSTATE_SHARED		1
#define PSTATE_CLEAN_EXCL	2
#define PSTATE_DIRTY_EXCL	3


/*
 * Cache operations
 */
#define Index_Invalidate_I               0x00        /* 0       0 */
#define Index_Writeback_Inv_D            0x01        /* 0       1 */
#define Index_Writeback_Inv_T            0x02        /* 0       2 */
#define Index_Writeback_Inv_S            0x03        /* 0       3 */
#define Index_Load_Tag_I                 0x04        /* 1       0 */
#define Index_Load_Tag_D                 0x05        /* 1       1 */
#define Index_Load_Tag_T                 0x06        /* 1       2 */
#define Index_Load_Tag_S                 0x07        /* 1       3 */
#define Index_Store_Tag_I                0x08        /* 2       0 */
#define Index_Store_Tag_D                0x09        /* 2       1 */
#define Index_Store_Tag_T                0x0A        /* 2       2 */
#define Index_Store_Tag_S                0x0B        /* 2       3 */
#define Hit_Invalidate_I                 0x10        /* 4       0 */
#define Hit_Invalidate_D                 0x11        /* 4       1 */
#define Hit_Invalidate_T                 0x12        /* 4       2 */
#define Hit_Invalidate_S                 0x13        /* 4       3 */
#define Fill_I                           0x14        /* 5       0 */
#define Hit_Writeback_Inv_D              0x15        /* 5       1 */
#define Hit_Writeback_Inv_T              0x16        /* 5       2 */
#define Hit_Writeback_Inv_S              0x17        /* 5       3 */
#define Hit_Writeback_D                  0x19        /* 6       1 */
#define Hit_Writeback_T                  0x1A        /* 6       1 */
#define Hit_Writeback_S                  0x1B        /* 6       3 */
#define Fetch_Lock_I                 	 0x1C        /* 7       0 */
#define Fetch_Lock_D                 	 0x1D        /* 7       1 */

/* MIPS32 WatchLo Register (CP0 Register 18) */
#define WATCHLO_VA		0xfffffff8
#define WATCHLO_I		0x00000004
#define WATCHLO_R		0x00000002
#define WATCHLO_W		0x00000001

/* MIPS32 WatchHi Register (CP0 Register 19) */
#define WATCHHI_M		0x80000000
#define WATCHHI_G		0x40000000
#define WATCHHI_ASIDMASK	0x00ff0000
#define WATCHHI_ASIDSHIFT	16
#define WATCHHI_MASK		0x00000ffc
#define WATCHHI_I		0x00000004
#define WATCHHI_R		0x00000002
#define WATCHHI_W		0x00000001

/* MIPS32 PerfCnt Register (CP0 Register 25) */
#define PERFCNT_M		0x80000000
#define PERFCNT_EVENTMASK	0x000007e0
#define PERFCNT_EVENTSHFT	5
#define PERFCNT_IE		0x00000010
#define PERFCNT_U		0x00000008
#define PERFCNT_S		0x00000004
#define PERFCNT_K		0x00000002
#define PERFCNT_EXL		0x00000001

