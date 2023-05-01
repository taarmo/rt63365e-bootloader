#include "regdef.h"

.extern gdb_handle_exception
.extern gdb_regs

.macro save_context
	
	.set	noreorder
	.set	noat

	sub 	sp, FR_SIZE

	la	k0, fgdb_regs
	//sw	zero, FR_FIR(k0) 
	//sw	zero, FR_FSR(k0) 
	mfc0	k1, C0_INDEX 
	sw	k1, FR_CP0_INDEX(k0)
	mfc0	k1, C0_EPC 	
	sw	k1, FR_EPC(k0)
	mfc0	k1, C0_CAUSE	
	sw	k1, FR_CAUSE(k0)  
	mfc0	k1, C0_BADVADDR	
	sw	k1, FR_BADVADDR(k0)  
	mfhi	k1        
	sw	k1, FR_HI(k0)
	mflo	k1        
	sw	k1, FR_LO(k0)
	mfc0	k1, C0_STATUS 
	sw	k1, FR_STATUS(k0)

	sw	ra, FR_REG31(k0)
	sw	s8, FR_REG30(k0)
	sw	sp, FR_REG29(k0)
	sw	gp, FR_REG28(k0)     
	//sw	k1, FR_REG27(k0)
	//sw	k0, FR_REG26(k0)
	sw	t9, FR_REG25(k0)
	sw	t8, FR_REG24(k0)
	sw	s7, FR_REG23(k0)
	sw	s6, FR_REG22(k0)
	sw	s5, FR_REG21(k0)
	sw	s4, FR_REG20(k0)
	sw	s3, FR_REG19(k0)
	sw	s2, FR_REG18(k0)
	sw	s1, FR_REG17(k0)
	sw	s0, FR_REG16(k0)
	sw	t7, FR_REG15(k0)
	sw	t6, FR_REG14(k0)
	sw	t5, FR_REG13(k0)
	sw	t4, FR_REG12(k0)
	sw	t3, FR_REG11(k0)
	sw	t2, FR_REG10(k0)
	sw	t1, FR_REG9(k0)
	sw	t0, FR_REG8(k0)
	sw	a3, FR_REG7(k0)
	sw	a2, FR_REG6(k0)
	sw	a1, FR_REG5(k0)
	sw	a0, FR_REG4(k0)
	sw	v1, FR_REG3(k0)
	sw	v0, FR_REG2(k0)
	sw	at, FR_REG1(k0)
	sw	zero, FR_REG0(k0)   

	move	a0, k0 
.endm

.macro unsave_context

	la	k0, fgdb_regs 

	lw	zero, FR_REG0(k0)
	lw	at, FR_REG1(k0)
	lw	v0, FR_REG2(k0)
	lw	v1, FR_REG3(k0)
	lw	a0, FR_REG4(k0)
	lw	a1, FR_REG5(k0)
	lw	a2, FR_REG6(k0)
	lw	a3, FR_REG7(k0)
	lw	t0, FR_REG8(k0)
	lw	t1, FR_REG9(k0)
	lw	t2, FR_REG10(k0)
	lw	t3, FR_REG11(k0)
	lw	t4, FR_REG12(k0)
	lw	t5, FR_REG13(k0)
	lw	t6, FR_REG14(k0)
	lw	t7, FR_REG15(k0)
	lw	s0, FR_REG16(k0)
	lw	s1, FR_REG17(k0)
	lw	s2, FR_REG18(k0)
	lw	s3, FR_REG19(k0)
	lw	s4, FR_REG20(k0)
	lw	s5, FR_REG21(k0)
	lw	s6, FR_REG22(k0)
	lw	s7, FR_REG23(k0)
	lw	t8, FR_REG24(k0)
	lw	t9, FR_REG25(k0)
	//k0
	//k1
	lw	gp, FR_REG28(k0)
	lw	sp, FR_REG29(k0)  
	lw	s8, FR_REG30(k0)
	lw	ra, FR_REG31(k0)

	lw	k1, FR_STATUS(k0) 
	mtc0	k1, C0_STATUS
	sync.p
	lw	k1, FR_LO(k0) 
	mtlo	k1
	sync.p
	lw	k1, FR_HI(k0) 
	mthi	k1
	sync.p
	lw	k1, FR_BADVADDR(k0) 
	mtc0	k1, C0_BADVADDR
	sync.p
	lw	k1, FR_CAUSE(k0) 
	mtc0	k1, C0_CAUSE
	sync.p
	lw	k1, FR_EPC(k0) 
	add	k1, 0x4
	mtc0	k1, C0_EPC
	sync.p

	//lw  fsr, FR_FSR(k0) //fsr
	//lw  fir, FR_FIR(k0) //fir

	lw	k1, FR_CP0_INDEX(k0) 
	mtc0	k1, C0_INDEX 
	sync.p

	add 	sp, FR_SIZE

.endm	

.global gdb_exception_dispatcher
gdb_exception_dispatcher:
	save_context	
	jal gdb_handle_exception
	unsave_context
	eret
	nop

