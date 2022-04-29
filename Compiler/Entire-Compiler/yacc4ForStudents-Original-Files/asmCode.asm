	.text	
	.globl		main
main:
	li		$t0, 10
	li		$t1, 2
	add		$t2, $t0, $t1
	sw		$t2, num1
	li		$t0, 20
	li		$t1, 3
	mul		$t2, $t0, $t1
	lw		$t0, num1
	add		$t1, $t2, $t0
	sw		$t1, num2
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
