#include "regdef.h"
#include "m32c0.h"

.extern _main

.section .text.init_main

init_main:
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
	//la	k0,0xbfb40000
	//nop
	//lw	k1,0x0(k0)
	//nop
	//la	t0,0x40400
	//nop
	//or	k1,k1,t0
	//nop
	//sw	k1,(k0)
	nop
	nop
	nop
	j _main
	nop

