#include "regdef.h"
#include "m32c0.h"

.section .text.irq

.macro save_context
	sub sp,96
	move a0,sp
	sw ra,0(sp)
	sw v0,4(sp)
	sw v1,8(sp)
	sw a0,12(sp)
	sw a1,16(sp)
	sw a2,20(sp)
	sw a3,24(sp)
	sw t0,28(sp)
	sw t1,32(sp)
	sw t2,36(sp)
	sw t3,40(sp)
	sw t4,44(sp)
	sw t5,48(sp)
	sw t6,52(sp)
	sw t7,56(sp)
	sw t8,60(sp)
	sw s0,64(sp)
	sw s1,68(sp)
	sw s2,72(sp)
	sw s3,76(sp)
	sw s4,80(sp)
	sw s5,84(sp)
	sw s6,88(sp)
	sw s7,92(sp)
	sw s8,96(sp)
.endm

.macro unsave_context
	lw s8,96(sp)
	lw s7,92(sp)
	lw s6,88(sp)
	lw s5,84(sp)
	lw s4,80(sp)
	lw s3,76(sp)
	lw s2,72(sp)
	lw s1,68(sp)
	lw s0,64(sp)
	lw t8,60(sp)
	lw t7,56(sp)
	lw t6,52(sp)
	lw t5,48(sp)
	lw t4,44(sp)
	lw t3,40(sp)
	lw t2,36(sp)
	lw t1,32(sp)
	lw t0,28(sp)
	lw a3,24(sp)
	lw a2,20(sp)
	lw a1,16(sp)
	lw a0,12(sp)
	lw v1,8(sp)
	lw v0,4(sp)
	lw ra,(sp)
	add sp,96
.endm	


trampoline_exception:
	  save_context
      mfc0       k1,C0_CAUSE
      lui        k0,0x8002
      andi       k1,k1,0x7c
      addu       k0,k0,k1
      lw         k0,0x0(k0)
      jr         k0
	  nop
	  unsave_context
	  jr         ra
	  nop


.global trampoline_irq
trampoline_irq:
	save_context
	mfc0	a0, C0_CAUSE
	andi	a0, a0, 0xff00
	srl 	a0, a0, 10
	subu	a0, a0, 1
	lui 	k0,0x8003
	jr 		k0
	unsave_context
	jr 		ra

//trampoline_irq:
//        mfc0       k0,C0_STATUS
//        sll        k0,k0,0x3
//        bltz       k0,ba
//        move      k1,sp
//        lui        k1,0x81fc
//        lw         k1,offset(k1)   
//		ba:
