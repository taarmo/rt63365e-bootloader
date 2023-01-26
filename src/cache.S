#include "regdef.h"
#include "m32c0.h"

.globl config_cache

.section .init.cache

config_cache:
	move       t4,ra
	bal        FUN_bfc006bc
	nop
	move       t2,v0
	bal        FUN_bfc006e0
	nop
	multu      t2,v0
	mflo       t3
	bal        FUN_bfc00720 
	nop
	move       t0,v0
	bal        FUN_bfc00744
	nop
	multu      t0,v0
	mflo       t1
	move       a0,t3
	move       a1,t2
	bal        FUN_bfc00654 
	nop
	move       a0,t1
	move       a1,t0
	bal        FUN_bfc00688
	nop
	jr         t4
	add        v0,zero,zero


FUN_bfc006bc:
	mfc0       t9,C0_CONFIG1
	lui        t8,0x38
	and        t8,t8,t9
	li         t7,0x13
	srlv       t8,t8,t7
	li         t7,0x2
	sllv       v0,t7,t8
	jr         ra
	nop

FUN_bfc006e0:  
	mfc0       t9,C0_CONFIG1
	lui        t8,0x7
	and        t8,t8,t9
	li         t7,0x10
	srlv       t8,t8,t7
	addiu      t8,t8,0x1
	lui        t7,0x1c0
	and        t7,t7,t9
	li         t9,0x16
	srlv       t7,t7,t9
	li         t9,0x40
	sllv       t7,t9,t7
	multu      t8,t7
	mflo       v0
	jr         ra
	nop

FUN_bfc00720:
	mfc0       t9,C0_CONFIG1
	li         t8,0x1c00
	and        t8,t8,t9
	li         t7,0xa
	srlv       t8,t8,t7
	li         t7,0x2
	sllv       v0,t7,t8
	jr         ra
	nop

FUN_bfc00744:
	mfc0       t9,C0_CONFIG1
	li         t8,0x380
	and        t8,t8,t9
	li         t7,0x7
	srlv       t8,t8,t7
	addiu      t8,t8,0x1
	ori        t7,zero,0xe000
	and        t7,t7,t9
	li         t9,0xd
	srlv       t7,t7,t9
	li         t9,0x40
	sllv       t7,t9,t7
	multu      t8,t7
	mflo       v0
	jr         ra
	nop

FUN_bfc00654:
	mtc0       zero,C0_TAGLO,0x0
	ssnop
	ssnop
	ssnop
	ehb
	lui        a2,0x8000
	addu       a3,a2,a0
	subu       a3,a3,a1
	whilecachea:                         
	cache      0x8,0x0(a2)
	addu       a2,a2,a1
	bne        a2,a3,whilecachea
	nop
	jr         ra
	nop

FUN_bfc00688: 
	mtc0       zero,C0_TAGLO,0x2
	ssnop
	ssnop
	ssnop
	ehb
	lui        a2,0x8000
	addu       a3,a2,a0
	subu       a3,a3,a1
	whilecacheb:
	cache      0x9,0x0(a2)
	addu       a2,a2,a1
	bne        a2,a3,whilecacheb
	nop
	jr         ra
	nop

