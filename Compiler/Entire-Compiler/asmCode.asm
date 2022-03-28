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
	bne		$t1, $t3, L1
	lw		$t0, num1
	li		$v0, 1
	move		$a0, $t0
	syscall	
	li		$v0, 4
	la		$a0, _nl
	syscall	
	lw		$t0, num2
	li		$v0, 1
	move		$a0, $t0
	syscall	
	li		$v0, 4
	la		$a0, _nl
	syscall	
L1:
	lw		$t0, num1
	li		$v0, 1
	move		$a0, $t0
	syscall	
	li		$v0, 4
	la		$a0, _nl
	syscall	
	lw		$t0, num2
	li		$v0, 1
	move		$a0, $t0
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
