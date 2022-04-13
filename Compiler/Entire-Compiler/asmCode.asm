	.text	
	.globl		main
main:

	li		$v0, 5
	syscall	
	sw		$v0, val
	lw		$t0, val
	li		$t1, 2
	div		$t2, $t0, $t1
	mfhi		$t2
	li		$t0, 0
	seq		$t1, $t2, $t0
	beq		$zero, $t1, L1

	li		$t0, 1
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$a0, 32
	li		$v0, 11
	syscall	
	li		$v0, 4
	la		$a0, _nl
	syscall	
L1:
	bne		$zero, $t1, L2

	li		$t0, 2
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$a0, 32
	li		$v0, 11
	syscall	
	li		$v0, 4
	la		$a0, _nl
	syscall	
L2:

L3:
	lw		$t0, val
	li		$t2, 0
	sgt		$t3, $t0, $t2
	beq		$zero, $t3, L4

	lw		$t0, val
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$a0, 32
	li		$v0, 11
	syscall	
	li		$v0, 4
	la		$a0, _nl
	syscall	
	lw		$t0, val
	li		$t2, 1
	sub		$t4, $t0, $t2
	sw		$t4, val
	j		L3
L4:

	li		$t0, 1
	move		$t2, $t0
	beq		$zero, $t2, L6
L5:
	li		$v0, 4
	la		$a0, _nl
	syscall	
	sub		$t2, $t2, 1
	bne		$zero, $t2, L5
L6:

	li		$t0, 0
	sw		$t0, val
L10:
	lw		$t0, val
	li		$t2, 10
	sle		$t4, $t0, $t2
	beq		$zero, $t4, L11

	lw		$t0, val
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$a0, 32
	li		$v0, 11
	syscall	
	li		$v0, 4
	la		$a0, _nl
	syscall	

	li		$t0, 1
	move		$t2, $t0
	beq		$zero, $t2, L8
L7:
	li		$v0, 4
	la		$a0, _nl
	syscall	
	sub		$t2, $t2, 1
	bne		$zero, $t2, L7
L8:
	lw		$t0, val
	li		$t2, 5
	seq		$t5, $t0, $t2
	beq		$zero, $t5, L9
	li		$t0, 8
	sw		$t0, val
L9:
	lw		$t0, val
	li		$t2, 1
	add		$t5, $t0, $t2
	sw		$t5, val
	j		L10
L11:
	li		$v0, 10
	syscall	
	.data	
	.align		4
_nl:	.asciiz		"\n"
val:	.word		0
