
#define	zero		$0
#define ZERO		0
#define	at		$1
#define	AT		1
#define	v0		$2
#define	V0		2
#define	v1		$3
#define	V1		3
#define	a0		$4
#define	A0		4
#define	a1		$5
#define	A1		5
#define	a2		$6
#define	A2		6
#define	a3		$7
#define	A3		7

#define	t0		$8
#define	T0		8
#define	t1		$9
#define	T1		9
#define	t2		$10
#define	T2		10
#define	t3		$11
#define	T3		11
#define	t4		$12
#define	T4		12
#define	t5		$13
#define	T5		13
#define	t6		$14
#define	T6		14
#define	t7		$15
#define	T7		15

#define	s0		$16
#define	S0		16
#define	s1		$17
#define	S1		17
#define	s2		$18
#define	S2		18
#define	s3		$19
#define	S3		19
#define	s4		$20
#define	S4		20
#define	s5		$21
#define	S5		21
#define	s6		$22
#define	S6		22
#define	s7		$23
#define	S7		23

#define	t8		$24
#define	T8		24
#define	t9		$25
#define	T9		25
#define	k0		$26
#define	K0		26
#define	k1		$27
#define	K1		27
#define	gp		$28
#define	GP		28
#define	sp		$29
#define	SP		29
#define	s8		$30
#define	S8		30
#define	ra		$31
#define	RA		31

#define	sr		$32
#define	SR		32
#define	lo		$33
#define	LO		33
#define	hi		$34
#define	HI		34
#define	bad_va		$35
#define	BAD_VA		35
#define	cause		$36
#define	CAUSE		36
#define	pc		$37
#define	PC		37

#define	f0		$38
#define	f1		$39
#define	f2		$40
#define	f3		$41
#define	f4		$42
#define	f5		$43
#define	f6		$44
#define	f7		$45

#define	f8		$46
#define	f9		$47
#define	f10		$48
#define	f11		$49
#define	f12		$50
#define	f13		$51
#define	f14		$52
#define	f15		$53

#define	f16		$54
#define	f17		$55
#define	f18		$56
#define	f19		$57
#define	f20		$58
#define	f21		$59
#define	f22		$60
#define	f23		$61

#define	f24		$62
#define	f25		$63
#define	f26		$64
#define	f27		$65
#define	f28		$66
#define	f29		$67
#define	f30		$68
#define	f31		$69

#define	fcsr		$70
#define	firr		$71

#define	num_regs	72

#define reg_sp		$29
#define REG_SP 		29
#define reg_epc		$37
#define REG_EPC		37
#define reg_fp		$72
#define REG_FP 		72


#define C0_INDEX	$0
#define C0_INX		$0
#define C0_RANDOM	$1
#define C0_RAND		$1
#define C0_ENTRYLO0	$2
#define C0_TLBLO0	$2
#define C0_ENTRYLO1	$3
#define C0_TLBLO1	$3
#define C0_CONTEXT	$4
#define C0_CTXT		$4
#define C0_PAGEMASK	$5
#define C0_WIRED	$6
#define C0_BADVADDR 	$8
#define C0_VADDR 	$8
#define C0_COUNT 	$9
#define C0_ENTRYHI	$10
#define C0_TLBHI	$10
#define C0_COMPARE	$11
#define C0_STATUS	$12
#define C0_SR		$12
#define C0_INTCTL	$12//,1
#define C0_CAUSE	$13
#define C0_CR		$13
#define C0_EPC 		$14
#define C0_PRID		$15
#define C0_EBASE	$15//,1 
#define C0_CONFIG	$16
#define C0_CONFIG0	$16//,0
#define C0_CONFIG1	$16//,1
#define C0_CONFIG2	$16//,2
#define C0_CONFIG3	$16//,3
#define C0_LLADDR	$17
#define C0_WATCHLO	$18
#define C0_WATCHHI	$19
#define C0_DEBUG	$23
#define C0_DEPC		$24
#define C0_PERFCNT	$25
#define C0_ERRCTL	$26
#define C0_CACHEERR	$27
#define C0_TAGLO	$28
#define C0_DATALO	$28,1
#define C0_TAGHI	$29
#define C0_DATAHI	$29,1
#define C0_ERRPC	$30
#define C0_DESAVE	$31


#define NUMREGS			96

#define GPR_SIZE		4	

#define FR_REG0			(GPR_SIZE*5)			/* 0 */
#define FR_REG1			((FR_REG0)  + GPR_SIZE)		/* 1 */
#define FR_REG2			((FR_REG1)  + GPR_SIZE)		/* 2 */
#define FR_REG3			((FR_REG2)  + GPR_SIZE)		/* 3 */
#define FR_REG4			((FR_REG3)  + GPR_SIZE)		/* 4 */
#define FR_REG5			((FR_REG4)  + GPR_SIZE)		/* 5 */
#define FR_REG6			((FR_REG5)  + GPR_SIZE)		/* 6 */
#define FR_REG7			((FR_REG6)  + GPR_SIZE)		/* 7 */
#define FR_REG8			((FR_REG7)  + GPR_SIZE)		/* 8 */
#define FR_REG9	        	((FR_REG8)  + GPR_SIZE)		/* 9 */
#define FR_REG10		((FR_REG9)  + GPR_SIZE)		/* 10 */
#define FR_REG11		((FR_REG10) + GPR_SIZE)		/* 11 */
#define FR_REG12		((FR_REG11) + GPR_SIZE)		/* 12 */
#define FR_REG13		((FR_REG12) + GPR_SIZE)		/* 13 */
#define FR_REG14		((FR_REG13) + GPR_SIZE)		/* 14 */
#define FR_REG15		((FR_REG14) + GPR_SIZE)		/* 15 */
#define FR_REG16		((FR_REG15) + GPR_SIZE)		/* 16 */
#define FR_REG17		((FR_REG16) + GPR_SIZE)		/* 17 */
#define FR_REG18		((FR_REG17) + GPR_SIZE)		/* 18 */
#define FR_REG19		((FR_REG18) + GPR_SIZE)		/* 19 */
#define FR_REG20		((FR_REG19) + GPR_SIZE)		/* 20 */
#define FR_REG21		((FR_REG20) + GPR_SIZE)		/* 21 */
#define FR_REG22		((FR_REG21) + GPR_SIZE)		/* 22 */
#define FR_REG23		((FR_REG22) + GPR_SIZE)		/* 23 */
#define FR_REG24		((FR_REG23) + GPR_SIZE)		/* 24 */
#define FR_REG25		((FR_REG24) + GPR_SIZE)		/* 25 */
#define FR_REG26		((FR_REG25) + GPR_SIZE)		/* 26 */
#define FR_REG27		((FR_REG26) + GPR_SIZE)		/* 27 */
#define FR_REG28		((FR_REG27) + GPR_SIZE)		/* 28 */
#define FR_REG29		((FR_REG28) + GPR_SIZE)		/* 29 */
#define FR_REG30		((FR_REG29) + GPR_SIZE)		/* 30 */
#define FR_REG31		((FR_REG30) + GPR_SIZE)		/* 31 */

/*
 * Saved special registers... TODORMD :: Move all ps2 specific ones to the very end.
 */


#define FR_STATUS		((FR_REG31) + GPR_SIZE)		/* 32 */
#define FR_LO			((FR_STATUS) + GPR_SIZE)	/* 33 */
#define FR_HI			((FR_LO) + GPR_SIZE)		/* 34 */	
#define FR_BADVADDR		((FR_HI) + GPR_SIZE)		/* 35 */
#define FR_CAUSE		((FR_BADVADDR) + GPR_SIZE)	/* 36 */
#define FR_EPC			((FR_CAUSE) + GPR_SIZE)		/* 37 */

/*
 * Saved floating point registers
 */
#define FR_FPR0			((FR_EPC) + GPR_SIZE)		/* 38 */
#define FR_FPR1			((FR_FPR0) + GPR_SIZE)		/* 39 */
#define FR_FPR2			((FR_FPR1) + GPR_SIZE)		/* 40 */
#define FR_FPR3			((FR_FPR2) + GPR_SIZE)		/* 41 */
#define FR_FPR4			((FR_FPR3) + GPR_SIZE)		/* 42 */
#define FR_FPR5			((FR_FPR4) + GPR_SIZE)		/* 43 */
#define FR_FPR6			((FR_FPR5) + GPR_SIZE)		/* 44 */
#define FR_FPR7			((FR_FPR6) + GPR_SIZE)		/* 45 */
#define FR_FPR8			((FR_FPR7) + GPR_SIZE)		/* 46 */
#define FR_FPR9			((FR_FPR8) + GPR_SIZE)		/* 47 */
#define FR_FPR10		((FR_FPR9) + GPR_SIZE)		/* 48 */
#define FR_FPR11		((FR_FPR10) + GPR_SIZE)		/* 49 */
#define FR_FPR12		((FR_FPR11) + GPR_SIZE)		/* 50 */
#define FR_FPR13		((FR_FPR12) + GPR_SIZE)		/* 51 */
#define FR_FPR14		((FR_FPR13) + GPR_SIZE)		/* 52 */
#define FR_FPR15		((FR_FPR14) + GPR_SIZE)		/* 53 */
#define FR_FPR16		((FR_FPR15) + GPR_SIZE)		/* 54 */
#define FR_FPR17		((FR_FPR16) + GPR_SIZE)		/* 55 */
#define FR_FPR18		((FR_FPR17) + GPR_SIZE)		/* 56 */
#define FR_FPR19		((FR_FPR18) + GPR_SIZE)		/* 57 */
#define FR_FPR20		((FR_FPR19) + GPR_SIZE)		/* 58 */
#define FR_FPR21		((FR_FPR20) + GPR_SIZE)		/* 59 */
#define FR_FPR22		((FR_FPR21) + GPR_SIZE)		/* 60 */
#define FR_FPR23		((FR_FPR22) + GPR_SIZE)		/* 61 */
#define FR_FPR24		((FR_FPR23) + GPR_SIZE)		/* 62 */
#define FR_FPR25		((FR_FPR24) + GPR_SIZE)		/* 63 */
#define FR_FPR26		((FR_FPR25) + GPR_SIZE)		/* 64 */
#define FR_FPR27		((FR_FPR26) + GPR_SIZE)		/* 65 */
#define FR_FPR28		((FR_FPR27) + GPR_SIZE)		/* 66 */
#define FR_FPR29		((FR_FPR28) + GPR_SIZE)		/* 67 */
#define FR_FPR30		((FR_FPR29) + GPR_SIZE)		/* 68 */
#define FR_FPR31		((FR_FPR30) + GPR_SIZE)		/* 69 */

#define FR_FSR			((FR_FPR31) + GPR_SIZE)		/* 70 */
#define FR_FIR			((FR_FSR) + GPR_SIZE)		/* 71 */

#define FR_FRP			((FR_FIR) + GPR_SIZE)		/* 72 */
#define FR_DUMMY		((FR_FRP) + GPR_SIZE)		/* 73, unused ??? */

/*
 * Again, CP0 registers
 */
#define FR_CP0_INDEX		((FR_DUMMY) + GPR_SIZE)			/* 74 */
#define FR_CP0_RANDOM		((FR_CP0_INDEX) + GPR_SIZE)		/* 75 */
#define FR_CP0_ENTRYLO0		((FR_CP0_RANDOM) + GPR_SIZE)		/* 76 */
#define FR_CP0_ENTRYLO1		((FR_CP0_ENTRYLO0) + GPR_SIZE)		/* 77 */
#define FR_CP0_CONTEXT		((FR_CP0_ENTRYLO1) + GPR_SIZE)		/* 78 */
#define FR_CP0_PAGEMASK		((FR_CP0_CONTEXT) + GPR_SIZE)		/* 79 */
#define FR_CP0_WIRED		((FR_CP0_PAGEMASK) + GPR_SIZE)		/* 80 */
#define FR_CP0_REG7		((FR_CP0_WIRED) + GPR_SIZE)		/* 81 */
#define FR_CP0_REG8		((FR_CP0_REG7) + GPR_SIZE)		/* 82 */
#define FR_CP0_REG9		((FR_CP0_REG8) + GPR_SIZE)		/* 83 */
#define FR_CP0_ENTRYHI		((FR_CP0_REG9) + GPR_SIZE)		/* 84 */
#define FR_CP0_REG11		((FR_CP0_ENTRYHI) + GPR_SIZE)		/* 85 */
#define FR_CP0_REG12		((FR_CP0_REG11) + GPR_SIZE)		/* 86 */
#define FR_CP0_REG13		((FR_CP0_REG12) + GPR_SIZE)		/* 87 */
#define FR_CP0_REG14		((FR_CP0_REG13) + GPR_SIZE)		/* 88 */
#define FR_CP0_PRID		((FR_CP0_REG14) + GPR_SIZE)		/* 89 */

#define FR_SIZE			((FR_CP0_PRID) + 12) 

#ifndef __ASSEMBLER__

struct reg_struct {

	unsigned int pad0;
	unsigned int pad1;
	unsigned int pad2;
	unsigned int pad3;
	unsigned int pad4;
	/*
	 * saved main processor registers
	 */
	long	 reg0,  reg1,  reg2,  reg3,  reg4,  reg5,  reg6,  reg7;   //zero-a3
	long	 reg8,  reg9,  reg10, reg11, reg12, reg13, reg14, reg15;  //t0-t7
	long	 reg16, reg17, reg18, reg19, reg20, reg21, reg22, reg23;  //s0-s7
	long	 reg24, reg25, reg26, reg27, reg28, reg29, reg30, reg31;  //t8-ra
	long     reg32, reg33, reg34, reg35, reg36, reg37; 		  //cp0_status-pc
								          //cp0_cause <- reg36
	/*
	 * Saved floating point registers
	 */
	long	reg38, reg39, reg40, reg41, reg42, reg43, reg44, reg45;  //f0-f7
	long	reg46, reg47, reg48, reg49, reg50, reg51, reg52, reg53; //f8-f15
	long	reg54, reg55, reg56, reg57, reg58, reg59, reg60, reg61; //f16-f23
	long	reg62, reg63, reg64, reg65, reg66, reg67, reg68, reg69; //f24-f31


	long 	cp1_fsr, cp1_fir;
	long 	reg_fp;

	/*
	 * saved cp0 registers
	 */
	long 	cp0_index;
	long 	cp0_epc;
	long	cp0_random;
	long	cp0_entrylo0;
	long	cp0_entrylo1;
	long	cp0_context;
	long	cp0_pagemask;
	long	cp0_wired;
	long	cp0_reg7;
	long	cp0_reg8;
	long	cp0_reg9;
	long	cp0_entryhi;
	long	cp0_reg11;
	long	cp0_reg12;
	long	cp0_reg13;
	long	cp0_reg14;
	long	cp0_prid;
};

#endif

