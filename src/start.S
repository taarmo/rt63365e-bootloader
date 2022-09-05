#include "regdef.h"
#include "m32c0.h"

.extern __stack_addr
.extern __global_pointer
.extern _eirq
.extern _stext
.extern _edata

.global __start

.section .init

__start:
	//reset 0xbfc00000
	j         	 ini 
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
	mtc0     	 zero,C0_WATCHLO,0x0 
	mtc0         zero,C0_WATCHHI,0x0 //disable wathcpoint

	mfc0         k0,C0_STATUS
	li           k1,-0x1a
	and          k0,k0,k1
	mtc0         k0,C0_STATUS,0x0
	lui          k0,0x80
	mtc0         k0,C0_CAUSE,0x0

	mfc0         t0,C0_CONFIG
	lui          t1,0x8000
	ori          t1,t1,0xffff
	and          t0,t0,t1
	lui          t1,0x3604
	or           t0,t0,t1
	mtc0         t0,C0_CONFIG,0x0
	mfc0         t0,C0_STATUS
	lui          t1,0xfffc
	ori          t1,t1,0xffff
	and          t0,t0,t1
	li           t1,0x0
	or           t0,t0,t1
	mtc0         t0,C0_STATUS,0x0
	mfc0         t0,C0_STATUS
	lui          t1,0x3
	and          t0,t0,t1
	lui          t1,0x440
	or           t0,t0,t1
	mtc0         t0,C0_STATUS,0x0
	mfc0         t0,C0_CONFIG
	lui          t1,0x7fff
	and          t0,t0,t1
	li           t1,0x3
	or           t0,t0,t1
	mtc0         t0,C0_CONFIG,0x0
	add          v0,zero,zero
	//stack
	//	lui 		 sp,0x8000
	//	addiu		 sp,sp,__stack_addr
	////global pointer
	//	lui 		 gp,0x8000
	//	addiu		 gp,gp,__global_pointer
	nop
	nop
	//config
	jal        config_dmc
	nop
	jal        config_cache
	nop
	lui        k0,0xbfc0
	addiu      k0,k0,_eirq
	lui        k1,0xbfc0
	addiu      k1,k1,_edata
	lui        t1,0x8000
memcpy:
	lw         t0,0x0(k0)
	nop
	sw         t0,0x0(t1)
	addiu      k0,k0,0x4
	addiu      t1,t1,0x4
	bne        k1,k0,memcpy
	nop
	lui        t1,0x8000
	lui        t2,0x8002

sincr:
	cache      0x19,0x0(t1)
	sync       0x0
	cache      0x10,0x0(t1)
	addiu      t1,t1,0x20
	bne        t2,t1,sincr
	nop
	//jmp ram
	lui        k0,0x8000
	or         k0,0x0020
	jr         k0
	nop



