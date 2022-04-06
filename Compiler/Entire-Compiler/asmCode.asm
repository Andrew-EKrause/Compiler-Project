	.text	
	.globl		main
main:
	li		$t0, 555
	sw		$t0, num1
	li		$t0, 11
	li		$t1, 4
	sne		$t2, $t0, $t1
	beq		$zero, $t2, L1
	lw		$t0, num1
	lw		$t1, num2
	add		$t3, $t0, $t1
	li		$v0, 1
	move		$a0, $t3
	syscall	
	li		$v0, 4
	la		$a0, _nl
	syscall	
L1:
	li		$t0, 20
	li		$t1, 3
	mul		$t3, $t0, $t1
	lw		$t0, num1
	add		$t1, $t3, $t0
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
