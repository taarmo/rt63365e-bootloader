#include "regdef.h"

.extern exception_handler
.extern exception_handlers
.extern irq_handler

.set noreorder
.set noat


.macro save_context
	subu	sp, sp, FR_SIZE

	//sw	zero, FR_FIR(sp) 
	//sw	zero, FR_FSR(sp) 
	sw	ra, FR_REG31(sp)
	sw	s8, FR_REG30(sp)
	sw	sp, FR_REG29(sp)
	sw	gp, FR_REG28(sp)     
	sw	k1, FR_REG27(sp)
	sw	k0, FR_REG26(sp)
	sw	t9, FR_REG25(sp)
	sw	t8, FR_REG24(sp)
	sw	s7, FR_REG23(sp)
	sw	s6, FR_REG22(sp)
	sw	s5, FR_REG21(sp)
	sw	s4, FR_REG20(sp)
	sw	s3, FR_REG19(sp)
	sw	s2, FR_REG18(sp)
	sw	s1, FR_REG17(sp)
	sw	s0, FR_REG16(sp)
	sw	t7, FR_REG15(sp)
	sw	t6, FR_REG14(sp)
	sw	t5, FR_REG13(sp)
	sw	t4, FR_REG12(sp)
	sw	t3, FR_REG11(sp)
	sw	t2, FR_REG10(sp)
	sw	t1, FR_REG9(sp)
	sw	t0, FR_REG8(sp)
	sw	a3, FR_REG7(sp)
	sw	a2, FR_REG6(sp)
	sw	a1, FR_REG5(sp)
	sw	a0, FR_REG4(sp)
	sw	v1, FR_REG3(sp)
	sw	v0, FR_REG2(sp)
	sw	at, FR_REG1(sp)
	sw	zero, FR_REG0(sp)   

	mfc0	k0, C0_CAUSE	
	sw	k0, FR_CAUSE(sp)  
	mfc0	k0, C0_BADVADDR
	sw	k0, FR_BADVADDR(sp)  
	mfhi	k0        
	sw	k0, FR_HI(sp)
	mflo	k0        
	sw	k0, FR_LO(sp)
	mfc0	k0, C0_STATUS 
	sw	k0, FR_STATUS(sp)

	mfc0	k0, C0_EPC	
	sw	k0, FR_EPC(sp)

	mfc0	k0, C0_INDEX
	sw	k0, FR_CP0_INDEX(sp)
.endm

.macro unsave_context

	lw	zero, FR_REG0(sp)
	lw	at, FR_REG1(sp)
	lw	v0, FR_REG2(sp)
	lw	v1, FR_REG3(sp)
	lw	a0, FR_REG4(sp)
	lw	a1, FR_REG5(sp)
	lw	a2, FR_REG6(sp)
	lw	a3, FR_REG7(sp)
	lw	t0, FR_REG8(sp)
	lw	t1, FR_REG9(sp)
	lw	t2, FR_REG10(sp)
	lw	t3, FR_REG11(sp)
	lw	t4, FR_REG12(sp)
	lw	t5, FR_REG13(sp)
	lw	t6, FR_REG14(sp)
	lw	t7, FR_REG15(sp)
	lw	s0, FR_REG16(sp)
	lw	s1, FR_REG17(sp)
	lw	s2, FR_REG18(sp)
	lw	s3, FR_REG19(sp)
	lw	s4, FR_REG20(sp)
	lw	s5, FR_REG21(sp)
	lw	s6, FR_REG22(sp)
	lw	s7, FR_REG23(sp)
	lw	t8, FR_REG24(sp)
	lw	t9, FR_REG25(sp)
	lw	k0, FR_REG26(sp)
	lw	k1, FR_REG27(sp)
	lw	gp, FR_REG28(sp)
	lw	sp, FR_REG29(sp)
	lw	s8, FR_REG30(sp)
	lw	ra, FR_REG31(sp)

	lw	k0, FR_STATUS(sp) 
	mtc0	k0, C0_STATUS
	sync.p
	lw	k0, FR_LO(sp) 
	mtlo	k0
	sync.p
	lw	k0, FR_HI(sp) 
	mthi	k0
	sync.p
	lw	k0, FR_BADVADDR(sp) 
	mtc0	k0, C0_BADVADDR
	sync.p
	lw	k0, FR_CAUSE(sp) 
	mtc0	k0, C0_CAUSE
	sync.p
	lw	k0, FR_EPC(sp) 
	add	k0, 0x4
	mtc0	k0, C0_EPC
	sync.p
	lw	k0, FR_CP0_INDEX(sp) 
	mtc0	k0, C0_INDEX
	sync.p

	//lw  fsr, FR_FSR(sp) //fsr
	//lw  fir, FR_FIR(sp) //fir
	addu	sp, sp, FR_SIZE

.endm	

.global exception_dispatcher
exception_dispatcher:
	save_context	
	jal exception_handler
	unsave_context
	eret
	nop

.global trampoline_irq
trampoline_irq:
	mfc0	k1, C0_CAUSE
	andi	k1, k1, 0xff00
	srl	k1, k1, 10
	subu	k1, k1, 1
	move	a0, k1
	jal	irq_handler
	nop

.global trampoline_exception
trampoline_exception:
	mfc0	k1, C0_CAUSE
	la 	k0, exception_handlers
	andi	k1, k1, 0x7c
	addu	k0, k0, k1
	lw	k0, 0x0(k0)
	nop
	jr	k0
	nop

