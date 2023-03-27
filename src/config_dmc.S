#include "regdef.h"
#include "m32c0.h"

.global config_dmc

.section .init.dmc

config_dmc:
	lui	v1,0xbfb0
	li 	t0,0x0
	sw 	t0,0x40(v1)

	lui	v1,0xbfb2

	li	t0,0x25222719
	nop
	sw	t0,0x40(v1)

	li	t0,0x202e2424
	nop
	sw	t0,0x44(v1)
	jr	ra
	nop

