#include "regdef.h"
#include "m32c0.h"

.section .text

//.global write_uart
.global config_uart

//write_uart:
//	seb        v1,a0
//	lui        a0,0xbfbf
//	ori        a1,a0,0x17
//	whilep:
//	lbu        v0,0x0(a1)
//	andi       v0,v0,0x20
//	beq        v0,zero,whilep
//	lui        v0,0xbfbf
//	andi       v1,v1,0xff
//	ori        v0,v0,0x3
//	sb         v1,0x0(v0)
//	jr         ra
//	nop

config_uart:
	lui        v1,0xbfbf
	ori        a0,v1,0xb
	li         v0,0xf
	sb         v0,0x0(a0)
	ori        v0,v1,0x13
	sb         zero,0x0(v0)
	ori        v0,v1,0x27
	sb         zero,0x0(v0)
	ori        a0,v1,0x7
	li         v0,0x1
	sb         v0,0x0(a0)
	ori        v1,v1,0xf
	li         v0,-0x80
	sb         v0,0x0(v1)
	lui        v0,0xbfb0
	ori        v0,v0,0x64
	lw         v0,0x0(v0)
	lui        v1,0xffff
	and        v0,v0,v1
	lui        v1,0x3
	ori        v0,zero,0xea00
	beq        v0,v1,conf_2
	nop
	lui        v0,0xbfb0
	ori        v0,v0,0x64
	lw         v0,0x0(v0)
	lui        v1,0xffff
	and        v0,v0,v1
	lui        v1,0x4
	ori        v0,zero,0xea00
	beq        v0,v1,conf_2
	nop
	conf_2:
	sll        v1,v0,0x10
	ori        v1,v1,0xfde8
	lui        v0,0xbfbf
	ori        v0,v0,0x2c
	sw         v1,0x0(v0)
	lui        v0,0xbfb0
	ori        v0,v0,0x64
	lw         v0,0x0(v0)
	lui        v1,0xffff
	and        v0,v0,v1
	lui        v1,0x3
	nop
	lui        v0,0xbfbf
	ori        a0,v0,0x3
	li         v1,0x1
	sb         v1,0x0(a0)
	ori        v0,v0,0x7
	sb         zero,0x0(v0)
	li         v1,0x3
	conf_1:
	lui        v0,0xbfbf
	ori        v0,v0,0xf
	sb         v1,0x0(v0)
	jr         ra
	nop

