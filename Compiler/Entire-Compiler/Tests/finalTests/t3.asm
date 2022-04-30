	.text	
	.globl		main
main:
	li		$v0, 4
	la		$a0, S1
	syscall	
	li		$v0, 5
	syscall	
	sw		$v0, i
	li		$v0, 5
	syscall	
	sw		$v0, j
	li		$v0, 5
	syscall	
	sw		$v0, k
	li		$v0, 5
	syscall	
	sw		$v0, m
	lw		$t0, i
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	lw		$t1, j
	add		$a0, $t1, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	lw		$t2, k
	add		$a0, $t2, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	lw		$t3, m
	add		$a0, $t3, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$t0, 8
	move		$t1, $t0
	beq		$zero, $t1, L2
L1:
	li		$v0, 4
	la		$a0, _spc
	syscall	
	subi		$t1, $t1, 1
	bne		$zero, $t1, L1
L2:
	lw		$t0, i
	lw		$t1, j
	move		$t2, $t0
	move		$t3, $t1
	move		$t4, $t1
	sub		$t4, $t4, 1
	beq		$zero, $t4, L5
	sub		$t3, $t3, 1
L3:
	beq		$zero, $t3, L4
	mul		$t2, $t2, $t0
	subi		$t3, $t3, 1
	j		L3
L5:
	move		$t2, $t0
L4:
	lw		$t0, k
	mul		$t1, $t2, $t0
	lw		$t0, m
	add		$t2, $t1, $t0
	add		$a0, $t2, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S2
	syscall	
	li		$t0, 8
	move		$t1, $t0
	beq		$zero, $t1, L7
L6:
	li		$v0, 4
	la		$a0, _spc
	syscall	
	subi		$t1, $t1, 1
	bne		$zero, $t1, L6
L7:
	lw		$t0, m
	lw		$t1, k
	lw		$t2, i
	lw		$t3, j
	move		$t4, $t2
	move		$t5, $t3
	move		$t6, $t3
	sub		$t6, $t6, 1
	beq		$zero, $t6, L10
	sub		$t5, $t5, 1
L8:
	beq		$zero, $t5, L9
	mul		$t4, $t4, $t2
	subi		$t5, $t5, 1
	j		L8
L10:
	move		$t4, $t2
L9:
	mul		$t2, $t1, $t4
	add		$t1, $t0, $t2
	add		$a0, $t1, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S3
	syscall	
	li		$v0, 4
	la		$a0, S4
	syscall	
	li		$v0, 10
	syscall	
	.data	
	.align		4
_nl:	.asciiz		"\n"
_spc:	.asciiz		" "
S4:	.asciiz		"\nTest 3 completed."
S3:	.asciiz		" = m + k * i ^ j\n"
S2:	.asciiz		" = i ^ j * k + m"
S1:	.asciiz		"Enter 4 integers. The second integer must be positive:\n"
i:	.word		0
j:	.word		0
k:	.word		0
m:	.word		0
