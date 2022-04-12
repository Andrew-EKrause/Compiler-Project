	.text	
	.globl		main
main:

	li		$v0, 5
	syscall	
	sw		$v0, num1
	li		$v0, 5
	syscall	
	sw		$v0, num2
	li		$v0, 5
	syscall	
	sw		$v0, num3
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
	lw		$t0, num3
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
num3:	.word		0
