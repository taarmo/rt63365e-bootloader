#include "regdef.h"
#include "m32c0.h"

.extern __stack_addr
.extern __global_pointer
.extern __rodata_end
.extern _fin_data_flash
.extern _gp
.extern _edata


.set noreorder

.macro sys_uart_init
	la	t3, 0xbfbf0000
	li	t4, 0x1
	sb	t4, 0x3(t3)
	li	t4, (0x0)
	sb	t4, 0x7(t3)
	li	t4, (0xf)

	sb	t4, 0xb(t3)
	li	t4, (0x3)
	sb	t4, 0xf(t3)
	li	t4, 0x0
	sb	t4, 0x13(t3)
	li	t4, (0x0)
	sb	t4, 0x27(t3)
	li	t4, 0xea00fde8
	sw	t4, 0x2c(t3)
	nop

.endm sys_uart_init



.global __start

.section .init

__start:
	//reset 0xbfc00000
	j	ini 
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
ini:
	mtc0	zero, C0_WATCHLO, 0x0 
	mtc0	zero, C0_WATCHHI, 0x0 //disable wathcpoint

	mfc0	k0, C0_STATUS
	li 	k1, -0x1a
	and	k0, k0,k1
	mtc0	k0, C0_STATUS, 0x0
	lui	k0, 0x80
	mtc0	k0, C0_CAUSE, 0x0

	mfc0	t0, C0_CONFIG
	lui	t1, 0x8000
	ori	t1, t1, 0xffff
	and	t0, t0, t1
	lui	t1, 0x3604
	or	t0, t0, t1
	mtc0	t0, C0_CONFIG, 0x0
	mfc0	t0, C0_STATUS
	lui	t1, 0xfffc
	ori 	t1, t1, 0xffff
	and 	t0, t0, t1
	li	t1, 0x0
	or	t0, t0, t1
	mtc0	t0, C0_STATUS, 0x0
	mfc0	t0, C0_STATUS
	lui	t1, 0x3
	and 	t0, t0, t1
	lui 	t1, 0x440
	or	t0, t0, t1
	mtc0	t0, C0_STATUS, 0x0
	mfc0	t0, C0_CONFIG
	lui	t1, 0x7fff
	and	t0, t0, t1
	li	t1, 0x3
	or	t0, t0, t1
	mtc0	t0, C0_CONFIG, 0x0
	sys_uart_init

	//config
	jal	config_dmc
	nop	
	jal	config_cache
	nop

	//stack
	la	sp, __stack_addr
	//global pointer
	la	gp, _gp

	lui	k0, 0x8000
	lui	k1, 0x8000
	addi	k1, 0x0300
fill_zero:
	sw	zero, 0x0(k0)
	addi	k0, k0, 0x4
	bne	k1, k0, fill_zero
	nop

	move	t1, k1
	lui	k0, 0xbfc0
	addi	k0, k0, _init_text_flash
	lui	k1, 0xbfc0
	addi	k1, k1, _fin_data_flash

memcpy:
	lw	t0, 0x0(k0)
	nop
	sw	t0, 0x0(t1)
	addi	k0, k0, 0x4
	addi	t1, t1, 0x4
	bne	k1, k0, memcpy
	nop	

	lui	t1, 0x8000
	lui	t2, 0x8002

sincr:
	cache	0x19, 0x0(t1)
	sync	0x0
	cache	0x10, 0x0(t1)
	add	t1, t1, 0x20
	bne	t2, t1, sincr
	nop	


	la 	t3, 0xbfb40000
	lw 	t4, 0x0(t3)
	nop	
	lui	t5, 0x4
	addi	t5, 0x0400 
	or	t4, t4, t5
	sw	t4, 0x0(t3)

	li	t5, 'C'
	jal	disp_character
	nop

	//jmp ram
	lui	k0, 0x8000
	or	k0, 0x0020

	jr	k0
	nop


.global disp_character
disp_character:
	la	t3, 0xbfbf0000
wait:
	lb	t4, 0x17(t3)
	nop
	andi	t4, 0x20
	beqz	t4, wait
	nop
	sb	t5, 0x03(t3)
	jr	ra
	nop
