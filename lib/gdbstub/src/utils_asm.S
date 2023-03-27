#include "regs.h"


.globl gdb_read_byte
.type gdb_read_byte, @function
gdb_read_byte:
	lb	t0, (a0)
	sb	t0, (a1)
	li	v0, 0
	jr	ra

.globl gdb_write_byte
.type gdb_write_byte, @function
gdb_write_byte:
	sb	a0, (a1)
	li	v0, 0
	jr	ra
	

.globl gdb_read_word
.type gdb_read_word, @function
gdb_read_word:
	lw	t0, (a0)
	sw	t0, (a1)
	li	v0, 0
	jr	ra

.globl gdb_write_word
.type gdb_write_word, @function
gdb_write_word:
	sw	a0, (a1)
	li	v0, 0
	jr	ra


.globl gdb_memcpy32
.type gdb_memcpy32, @function
gdb_memcpy32:
	ja1:lw t0,0x0(a1)
	sw t0,0x0(a0)
	addiu a2,a2,-0x4
	addiu a0,a0,0x4
	addiu a1,a1,0x4
	bne a2,zero,ja1
	jr ra


