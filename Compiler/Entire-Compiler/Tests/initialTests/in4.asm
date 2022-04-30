	.text	
	.globl		main
main:
	li		$v0, 5
	syscall	
	sw		$v0, val
	lw		$t0, val
	li		$t1, 2
	div		$t2, $t0, $t1
	mfhi		$t2
	li		$t0, 0
	seq		$t1, $t2, $t0
	beq		$zero, $t1, L1
	li		$t0, 1
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
L1:
	bne		$zero, $t1, L2
	li		$t0, 2
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
L2:
L3:
	lw		$t0, val
	li		$t1, 0
	sgt		$t2, $t0, $t1
	beq		$zero, $t2, L4
	lw		$t0, val
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	lw		$t0, val
	li		$t1, 1
	sub		$t3, $t0, $t1
	sw		$t3, val
	j		L3
L4:
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
	li		$t0, 0
	sw		$t0, val
L10:
	lw		$t0, val
	li		$t1, 10
	sle		$t2, $t0, $t1
	beq		$zero, $t2, L11
	lw		$t0, val
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$t0, 1
	move		$t1, $t0
	beq		$zero, $t1, L8
L7:
	li		$v0, 4
	la		$a0, _nl
	syscall	
	subi		$t1, $t1, 1
	bne		$zero, $t1, L7
L8:
	lw		$t0, val
	li		$t1, 5
	seq		$t3, $t0, $t1
	sne		$t0, $t3, $zero
	beq		$t0, $zero, L9
	li		$t0, 8
	sw		$t0, val
L9:
	lw		$t0, val
	li		$t1, 1
	add		$t3, $t0, $t1
	sw		$t3, val
	j		L10
L11:
	li		$v0, 10
	syscall	
	.data	
	.align		4
_nl:	.asciiz		"\n"
_spc:	.asciiz		" "
val:	.word		0
