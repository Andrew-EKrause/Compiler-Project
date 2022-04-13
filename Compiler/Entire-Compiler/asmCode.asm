	.text	
	.globl		main
main:
	li		$t0, 10
	sw		$t0, num1
	li		$t0, 20
	sw		$t0, num2
	lw		$t0, num2
	li		$t1, 10
	add		$t2, $t0, $t1
	li		$t0, 10
	add		$t1, $t2, $t0
	li		$t0, 2
	lw		$t2, num2
	mul		$t3, $t0, $t2
	seq		$t0, $t1, $t3
	beq		$zero, $t0, L1
	lw		$t1, num1
	li		$v0, 1
	move		$a0, $t1
	syscall	
	li		$v0, 4
	la		$a0, _nl
	syscall	
	lw		$t1, num2
	li		$v0, 1
	move		$a0, $t1
	syscall	
	li		$v0, 4
	la		$a0, _nl
	syscall	
L1:

	lw		$t1, num1
	add		$a0, $t1, $zero
	li		$v0, 1
	syscall	
	li		$a0, 32
	li		$v0, 11
	syscall	
	lw		$t2, num2
	add		$a0, $t2, $zero
	li		$v0, 1
	syscall	
	li		$a0, 32
	li		$v0, 11
	syscall	

	li		$t1, 1
	move		$t2, $t1
	beq		$zero, $t2, L3
L2:
	li		$v0, 4
	la		$a0, _nl
	syscall	
	sub		$t2, $t2, 1
	bne		$zero, $t2, L2
L3:
	lw		$t1, num2
	li		$v0, 1
	move		$a0, $t1
	syscall	
	li		$v0, 4
	la		$a0, _nl
	syscall	
	li		$v0, 10
	syscall	
	.data	
	.align		4
_nl:	.asciiz		"\n"
num1:	.word		0
num2:	.word		0
