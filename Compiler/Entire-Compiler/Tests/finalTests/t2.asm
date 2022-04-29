	.text	
	.globl		main
main:
	li		$t0, 3
	sw		$t0, i
	li		$t0, 8
	sw		$t0, j
	li		$t0, 2
	sw		$t0, k
	lw		$t0, i
	lw		$t1, j
	lw		$t2, k
	mul		$t3, $t1, $t2
	add		$t1, $t0, $t3
	sw		$t1, m
	lw		$t0, m
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S1
	syscall	
	lw		$t0, j
	lw		$t1, i
	div		$t2, $t0, $t1
	lw		$t0, k
	add		$t1, $t2, $t0
	sw		$t1, m
	lw		$t0, m
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S2
	syscall	
	lw		$t0, k
	lw		$t1, j
	mul		$t2, $t0, $t1
	lw		$t0, i
	div		$t1, $t2, $t0
	mfhi		$t1
	sw		$t1, m
	lw		$t0, m
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S3
	syscall	
	lw		$t0, j
	lw		$t1, k
	lw		$t2, i
	move		$t3, $t1
	move		$t4, $t2
	move		$t5, $t2
	sub		$t5, $t5, 1
	beq		$zero, $t5, L3
	sub		$t4, $t4, 1
L1:
	beq		$zero, $t4, L2
	mul		$t3, $t3, $t1
	subi		$t4, $t4, 1
	j		L1
L3:
	move		$t3, $t1
L2:
	move		$t1, $t0
	move		$t2, $t3
	move		$t4, $t3
	sub		$t4, $t4, 1
	beq		$zero, $t4, L6
	sub		$t2, $t2, 1
L4:
	beq		$zero, $t2, L5
	mul		$t1, $t1, $t0
	subi		$t2, $t2, 1
	j		L4
L6:
	move		$t1, $t0
L5:
	sw		$t1, m
	lw		$t0, m
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S4
	syscall	
	li		$v0, 4
	la		$a0, S5
	syscall	
	li		$v0, 10
	syscall	
	.data	
	.align		4
_nl:	.asciiz		"\n"
_spc:	.asciiz		" "
S5:	.asciiz		"\nTest 2 completed."
S4:	.asciiz		" = 8 ^ 2 ^ 3\n"
S3:	.asciiz		" = 2 * 8 % 3\n"
S2:	.asciiz		" = 8 / 3 + 2\n"
S1:	.asciiz		" = 3 + 8 * 2\n"
i:	.word		0
j:	.word		0
k:	.word		0
m:	.word		0
