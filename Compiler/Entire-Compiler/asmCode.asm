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
	beq		$zero, $t0, L3
	lw		$t1, num1
	add		$a0, $t1, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	lw		$t2, num1
	add		$a0, $t2, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$t1, 10
	move		$t2, $t1
	beq		$zero, $t2, L2
L1:
	li		$v0, 4
	la		$a0, _spc
	syscall	
	subi		$t2, $t2, 1
	bne		$zero, $t2, L1
L2:
	lw		$t1, num2
	add		$a0, $t1, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	lw		$t2, num2
	add		$a0, $t2, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
L3:
	li		$t1, 5
	move		$t2, $t1
	beq		$zero, $t2, L5
L4:
	li		$v0, 4
	la		$a0, _nl
	syscall	
	subi		$t2, $t2, 1
	bne		$zero, $t2, L4
L5:
	lw		$t1, num1
	add		$a0, $t1, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, _nl
	syscall	
	lw		$t1, num2
	add		$a0, $t1, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, _nl
	syscall	

	li		$v0, 4
	la		$a0, String1
	syscall	
	li		$v0, 10
	syscall	
	.data	
	.align		4
_nl:	.asciiz		"\n"
_spc:	.asciiz		" "
String1:	.asciiz		"Hello there!"
num1:	.word		0
num2:	.word		0
