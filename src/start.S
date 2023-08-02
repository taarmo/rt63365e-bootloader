#include "regdef.h"

.extern _stack_addr
.extern _rodata_start
.extern _rodata_end
.extern _fin_data_flash
.extern _gp
.extern _edata
.extern _bss_start
.extern _bss_end


//.set noreorder

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

.macro disp_characters
        la      t3, 0xbfbf0000
wait:
        lb      t4, 0x17(t3)
        nop
        andi    t4, 0x20
        beqz    t4, wait
        nop
        sb      t5, 0x03(t3)
        nop
.endm disp_characters



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
	//enable cop1
	mfc0	t0, C0_STATUS, 0x0
	lui	t1, 0x2000
	or	t0, t0, t1   # Establecemos el bit en 1
	mtc0	t0, C0_STATUS, 0x0
	nop
	sys_uart_init

	//config
	jal	config_dmc
	nop	
	jal	config_cache
	nop

	//stack
	la	sp, _stack_addr
	//global pointer
	la	gp, _gp

	la	k0, _bss_start
	la	k1, _bss_end

fill_zero:
	sw	zero, 0x0(k0)
	addi	k0, k0, 0x4
	bne	k1, k0, fill_zero
	nop

	lui	k0, 0xbfc0
	addi	k0, k0, _init_rodata
	lui	k1, 0xbfc0
	addi	k1, k1, _fin_data_flash


	la	t0, 0x81e00000
	la	t1, _size_bootloader_ram

memcpy:
	lw	t2, 0x0(k0)
	sw	t2, 0x0(t0)
	addi	k0, k0, 0x4
	addi	t0, t0, 0x4
	addi	t1, t1, -0x4
	bnez	t1, memcpy
	nop	


	la	t0, 0x81e00000
	la	t1, _size_bootloader_ram

flushc:
	cache	0x19, 0x0(t0)
	sync	0x0
	cache	0x10, 0x0(t0)
	add	t0, t0, 0x20
	addi	t1, t1, -0x4
	bnez	t1, flushc
	nop	

	la 	t3, 0xbfb40000
	lw 	t4, 0x0(t3)
	la	t5, 0x40400
	or	t4, t4, t5
	sw	t4, 0x0(t3)
	nop

//#ifdef DEBUG
//	li	t5, 'T'
//	disp_characters
//#endif

	lui	k0, 0x81e0
	addi	k0, k0, _rodata_size

	jr	k0
	nop


