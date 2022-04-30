	.text	
	.globl		main
main:
	li		$t0, 555
	sw		$t0, num1
	li		$t0, 777
	sw		$t0, num2
	li		$t0, 5
	sw		$t0, num3
	lw		$t0, num1
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$t0, 2
	lw		$t1, num3
	mul		$t2, $t0, $t1
	move		$t0, $t2
	beq		$zero, $t0, L2
L1:
	li		$v0, 4
	la		$a0, _spc
	syscall	
	subi		$t0, $t0, 1
	bne		$zero, $t0, L1
L2:
	lw		$t0, num2
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$t0, 2
	lw		$t1, num3
	mul		$t2, $t0, $t1
	move		$t0, $t2
	beq		$zero, $t0, L4
L3:
	li		$v0, 4
	la		$a0, _nl
	syscall	
	subi		$t0, $t0, 1
	bne		$zero, $t0, L3
L4:
	lw		$t0, num3
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$t0, 5
	li		$t1, 5
	mul		$t2, $t0, $t1
	mul		$t2, $t2, -1
	sw		$t2, num1
	li		$t0, 1
	move		$t1, $t0
	beq		$zero, $t1, L6
L5:
	li		$v0, 4
	la		$a0, _nl
	syscall	
	subi		$t1, $t1, 1
	bne		$zero, $t1, L5
L6:
	lw		$t0, num1
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 10
	syscall	
	.data	
	.align		4
_nl:	.asciiz		"\n"
_spc:	.asciiz		" "
num1:	.word		0
num2:	.word		0
num3:	.word		0
