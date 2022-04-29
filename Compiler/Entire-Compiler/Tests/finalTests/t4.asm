	.text	
	.globl		main
main:
	li		$v0, 4
	la		$a0, S1
	syscall	
	li		$v0, 5
	syscall	
	sw		$v0, start
	li		$v0, 5
	syscall	
	sw		$v0, end
	li		$v0, 5
	syscall	
	sw		$v0, inc
	lw		$t0, start
	sw		$t0, current

L1:
	lw		$t0, current
	lw		$t1, end
	sle		$t2, $t0, $t1
	beq		$zero, $t2, L2
	lw		$t0, current
	li		$t1, 32
	sub		$t3, $t0, $t1
	li		$t0, 5
	mul		$t1, $t3, $t0
	li		$t0, 9
	div		$t3, $t1, $t0
	sw		$t3, c
	lw		$t0, current
	li		$t1, 460
	add		$t3, $t0, $t1
	li		$t0, 5
	mul		$t1, $t3, $t0
	li		$t0, 9
	div		$t3, $t1, $t0
	sw		$t3, k
	lw		$t0, current
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	lw		$t1, c
	add		$a0, $t1, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	lw		$t3, k
	add		$a0, $t3, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S2
	syscall	
	lw		$t0, current
	lw		$t1, inc
	add		$t3, $t0, $t1
	sw		$t3, current
	j		L1
L2:
	li		$v0, 4
	la		$a0, S3
	syscall	
	li		$v0, 10
	syscall	
	.data	
	.align		4
_nl:	.asciiz		"\n"
_spc:	.asciiz		" "
S3:	.asciiz		"\nTest 4 completed."
S2:	.asciiz		"\n"
S1:	.asciiz		"Enter three integers: Starting temp, ending temp and a positive increment: \n"
c:	.word		0
k:	.word		0
current:	.word		0
end:	.word		0
inc:	.word		0
start:	.word		0
