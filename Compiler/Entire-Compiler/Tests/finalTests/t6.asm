	.text	
	.globl		main
main:
	li		$v0, 4
	la		$a0, S1
	syscall	
	li		$v0, 5
	syscall	
	sw		$v0, count
L4:
	lw		$t0, count
	li		$t1, 0
	sgt		$t2, $t0, $t1
	beq		$zero, $t2, L5
	li		$v0, 4
	la		$a0, S2
	syscall	
	li		$v0, 5
	syscall	
	sw		$v0, low
	li		$v0, 5
	syscall	
	sw		$v0, mid
	li		$v0, 5
	syscall	
	sw		$v0, high
	lw		$t0, low
	lw		$t1, mid
	sgt		$t3, $t0, $t1
	sne		$t0, $t3, $zero
	beq		$t0, $zero, L1
	lw		$t0, low
	sw		$t0, temp
	lw		$t0, mid
	sw		$t0, low
	lw		$t0, temp
	sw		$t0, mid
L1:
	lw		$t0, low
	lw		$t1, high
	sgt		$t3, $t0, $t1
	sne		$t0, $t3, $zero
	beq		$t0, $zero, L2
	lw		$t0, low
	sw		$t0, temp
	lw		$t0, high
	sw		$t0, low
	lw		$t0, temp
	sw		$t0, high
L2:
	lw		$t0, mid
	lw		$t1, high
	sgt		$t3, $t0, $t1
	sne		$t0, $t3, $zero
	beq		$t0, $zero, L3
	lw		$t0, mid
	sw		$t0, temp
	lw		$t0, high
	sw		$t0, mid
	lw		$t0, temp
	sw		$t0, high
L3:
	lw		$t0, low
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	lw		$t1, mid
	add		$a0, $t1, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	lw		$t3, high
	add		$a0, $t3, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S3
	syscall	
	lw		$t0, count
	li		$t1, 1
	sub		$t3, $t0, $t1
	sw		$t3, count
	j		L4
L5:
	li		$v0, 4
	la		$a0, S4
	syscall	
	li		$v0, 10
	syscall	
	.data	
	.align		4
_nl:	.asciiz		"\n"
_spc:	.asciiz		" "
S4:	.asciiz		"\nTest 6 completed."
S3:	.asciiz		"\n"
S2:	.asciiz		"Enter three integers: \n"
S1:	.asciiz		"Enter the number of triples to be processed: \n"
low:	.word		0
temp:	.word		0
mid:	.word		0
high:	.word		0
count:	.word		0
