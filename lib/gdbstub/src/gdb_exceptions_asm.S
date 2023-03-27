#include "regdef.h"

.extern gdb_handle_exception

.macro save_context
	subu	sp, sp, 0x100   

	sw	s8, FR_SIZE(sp)
	sw	zero, FR_FIR(sp) 
	sw	zero, FR_FSR(sp) 
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

	mfc0	k0, $13	
	sw	k0, FR_CAUSE(sp)  
	mfc0	k0, $8	
	sw	k0, FR_BADVADDR(sp)  
	mfhi	k0        
	sw	k0, FR_HI(sp)
	mflo	k0        
	sw	k0, FR_LO(sp)
	mfc0	k0,$12 
	sw	k0, FR_STATUS(sp)

	mfc0	k0,$14 	
	sw	k0, FR_EPC(sp)
	sw	k0, 148(sp) //pc

	mfc0	k0,$0 
	sw	k0, FR_CP0_INDEX(sp)

	move	a0,sp
.endm

.macro unsave_context

	la	k0, regs_ret
	li	k1, 0x0 
	//bne k0,k1, 1f

	lw	k0, FR_CP0_INDEX(sp) 
	mtc0	k0, $0
	lw	k0, FR_EPC(sp) 
	mtc0	k0, $14

	li	k0, 0xfabada //pc
	sw	k0, 148(sp)

	lw	k0, FR_CAUSE(sp) 
	mtc0	k0, $13
	lw	k0, FR_BADVADDR(sp) 
	mtc0	k0, $8
	lw	k0, FR_HI(sp) 
	mthi	k0
	lw	k0, FR_LO(sp) 
	mtlo	k0
	lw	k0, FR_STATUS(sp) 
	mtc0	k0, $12

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

	//lw  fsr, FR_FSR(sp) //fsr
	//lw  fir, FR_FIR(sp) //fir
	mfc0	k0, $12
	li	k1, 0x8
	and	k0, k0, k1
	mtc0	k0, $12

	lw	s8, FR_SIZE(sp)
	addu	sp, sp, 0x100 

.endm	

.global gdb_exception_dispatcher
gdb_exception_dispatcher:
	save_context	
	jal gdb_handle_exception
	unsave_context

