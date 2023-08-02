#include "regdef.h"

.global config_dmc


.section .init.dmc

config_dmc:
	lui	v1, 0xbfb0
	li 	t0, 0x0
	sw 	t0, 0x40(v1)

	lui	v1, 0xbfb2

#ifdef RAM32 
	li	t0, 0x25222719
	sw	t0, 0x40(v1)
	li	t0, 0x202e2424
	sw	t0, 0x44(v1)
#endif
#ifdef RAM64
	li	t0, 0x35222719
	sw	t0, 0x40(v1)
	li	t0, 0x30322424
	sw	t0, 0x44(v1)
#endif
	jr	ra
	nop

