#include "regdef.h"

.macro disp_character
	la      t3, 0xbfbf0000
wait:
        lb      t4, 0x17(t3)
        nop
        andi    t4, 0x20
        beqz    t4, wait
        nop
        sb      t5, 0x03(t3)
        nop
.endm disp_character


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
#ifdef DEBUG
	li	t5, 'T'
	disp_character
#endif
	nop
	nop
	nop
	nop
	nop
	nop
	j _main
	nop

