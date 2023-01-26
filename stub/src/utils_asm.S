
.section .text

.globl memcpy32
.type memcpy32, @function
memcpy32:
	ja1:lw $t0,0x0($a1)
	sw $t0,0x0($a0)
	addiu $a2,$a2,-0x4
	addiu $a0,$a0,0x4
	addiu $a1,$a1,0x4
	bne $a2,$zero,ja1
	jr $ra

