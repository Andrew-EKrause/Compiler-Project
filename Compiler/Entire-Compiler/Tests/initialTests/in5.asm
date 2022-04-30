	.text	
	.globl		main
main:
	li		$t0, 2
	sw		$t0, x
	li		$t0, 4
	sw		$t0, z
	li		$t0, 6
	sw		$t0, w
	li		$t0, 8
	sw		$t0, y
	li		$t0, 10
	sw		$t0, a
	li		$t0, 12
	sw		$t0, b
	li		$t0, 14
	sw		$t0, c
	li		$t0, 2
	lw		$t1, x
	mul		$t2, $t0, $t1
	add		$a0, $t2, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	lw		$t0, x
	li		$t1, 3
	move		$t3, $t0
	move		$t4, $t1
	move		$t5, $t1
	sub		$t5, $t5, 1
	beq		$zero, $t5, L3
	sub		$t4, $t4, 1
L1:
	beq		$zero, $t4, L2
	mul		$t3, $t3, $t0
	subi		$t4, $t4, 1
	j		L1
L3:
	move		$t3, $t0
L2:
	lw		$t0, z
	lw		$t1, w
	mul		$t4, $t0, $t1
	mul		$t0, $t3, $t4
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	lw		$t1, a
	lw		$t3, b
	add		$t4, $t1, $t3
	lw		$t1, c
	add		$t3, $t4, $t1
	lw		$t1, x
	lw		$t4, y
	add		$t5, $t1, $t4
	lw		$t1, z
	add		$t4, $t5, $t1
	div		$t1, $t3, $t4
	add		$a0, $t1, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	lw		$t3, c
	add		$a0, $t3, $zero
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
c:	.word		0
w:	.word		0
x:	.word		0
y:	.word		0
z:	.word		0
a:	.word		0
b:	.word		0
