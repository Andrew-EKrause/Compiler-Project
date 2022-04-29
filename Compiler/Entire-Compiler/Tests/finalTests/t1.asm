	.text	
	.globl		main
main:
	li		$t0, 7
	sw		$t0, i
	li		$t0, 20
	sw		$t0, j
	lw		$t0, i
	lw		$t1, j
	add		$t2, $t0, $t1
	sw		$t2, k
	lw		$t0, k
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S1
	syscall	
	lw		$t0, i
	lw		$t1, j
	sub		$t2, $t0, $t1
	sw		$t2, k
	lw		$t0, k
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S2
	syscall	
	lw		$t0, i
	lw		$t1, j
	mul		$t2, $t0, $t1
	sw		$t2, k
	lw		$t0, k
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
	lw		$t1, i
	div		$t2, $t0, $t1
	sw		$t2, k
	lw		$t0, k
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S4
	syscall	
	lw		$t0, j
	lw		$t1, i
	div		$t2, $t0, $t1
	mfhi		$t2
	sw		$t2, k
	lw		$t0, k
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S5
	syscall	
	lw		$t0, i
	mul		$t0, $t0, -1
	sw		$t0, k
	lw		$t0, k
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S6
	syscall	
	lw		$t0, i
	li		$t1, 3
	move		$t2, $t0
	move		$t3, $t1
	move		$t4, $t1
	sub		$t4, $t4, 1
	beq		$zero, $t4, L3
	sub		$t3, $t3, 1
L1:
	beq		$zero, $t3, L2
	mul		$t2, $t2, $t0
	subi		$t3, $t3, 1
	j		L1
L3:
	move		$t2, $t0
L2:
	sw		$t2, k
	lw		$t0, k
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S7
	syscall	
	li		$v0, 4
	la		$a0, S8
	syscall	
	li		$v0, 10
	syscall	
	.data	
	.align		4
_nl:	.asciiz		"\n"
_spc:	.asciiz		" "
S8:	.asciiz		"\nTest 1 completed."
S7:	.asciiz		" = 7^3\n"
S6:	.asciiz		" = -7\n"
S5:	.asciiz		" = 20 % 7\n"
S4:	.asciiz		" = 20 / 7\n"
S3:	.asciiz		" = 7 * 20\n"
S2:	.asciiz		" = 7 - 20\n"
S1:	.asciiz		" = 7 + 20\n"
i:	.word		0
j:	.word		0
k:	.word		0
