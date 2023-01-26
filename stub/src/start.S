#include "regdef.h"
#include "m32c0.h"

.extern __main_stub

.global __start

.section .init

__start:
	//.cprestore 100
	//jal dest
	//nop
	j __main_stub
	nop

//dest:
//	move s0,ra
//	sub s0,s0,20 //AJUSTAR 
//	jr ra
