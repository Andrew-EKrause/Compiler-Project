	.text	
	.globl		main
main:
	li		$t0, 555
	sw		$t0, num1
	li		$t0, 6
	li		$t1, 4
	slt		$t2, $t0, $t1
	li		$t0, 4
	li		$t1, 8
	slt		$t3, $t0, $t1
	and		$t0, $t2, $t3
	sll		$t0, $t0, 31
	srl		$t0, $t0, 31
	beq		$zero, $t0, L1
	lw		$t1, num1
	li		$t2, 2
	add		$t3, $t1, $t2
	li		$v0, 1
	move		$a0, $t3
	syscall	
	li		$v0, 4
	la		$a0, _nl
	syscall	
L1:
	li		$t1, 20
	li		$t2, 3
	mul		$t3, $t1, $t2
	lw		$t1, num1
	add		$t2, $t3, $t1
	sw		$t2, num2
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
	li		$v0, 10
	syscall	
	.data	
	.align		4
_nl:	.asciiz		"\n"
num1:	.word		0
num2:	.word		0
