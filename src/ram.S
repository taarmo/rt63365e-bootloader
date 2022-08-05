#include "regdef.h"
#include "m32c0.h"

.extern _main
.extern __global_pointer
.extern __stack_addr

.section .text

ram:
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
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	lui   gp,0x8000
	addiu gp,gp,__global_pointer
	lui   sp,0x8000
	addiu sp,sp,__stack_addr
	nop
	nop
	nop
	nop
	j _main
	nop
