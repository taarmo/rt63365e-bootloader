#include "regdef.h"
#include "m32c0.h"

.extern __cte1
.extern __cte2

.global config_dmc

.section .init_main

config_dmc:
	lui        v1,0xbfb0
	li         t0,0x0
	sw         t0,0x40(v1)

	lui        v1,0xbfb2

	lui        t0,0xbfc0
	addiu      t0,t0,__cte1
	lw         t0,0x0(t0)
	sw         t0,0x40(v1)

	lui        t0,0xbfc0
	addiu      t0,t0,__cte2
	lw         t0,0x0(t0)
	sw         t0,0x44(v1)
	jr         ra
	nop

