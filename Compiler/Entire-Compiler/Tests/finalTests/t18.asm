	.text	
	.globl		main
main:
	li		$t0, 1
	sw		$t0, x
	li		$t0, 0
	sw		$t0, y
	li		$v0, 4
	la		$a0, S1
	syscall	
	lw		$t0, x
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S2
	syscall	
	li		$v0, 4
	la		$a0, S3
	syscall	
	lw		$t0, y
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S4
	syscall	
	lw		$t0, x
	lw		$t1, y
	sne		$t0, $t0, $zero
	sne		$t1, $t1, $zero
	and		$t2, $t0, $t1
	sw		$t2, z
	lw		$t0, z
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S5
	syscall	
	lw		$t0, x
	lw		$t1, y
	sne		$t0, $t0, $zero
	sne		$t1, $t1, $zero
	or		$t2, $t0, $t1
	sw		$t2, z
	lw		$t0, z
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S6
	syscall	
	lw		$t0, x
	seq		$t1, $t0, $zero
	sw		$t1, z
	lw		$t0, z
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S7
	syscall	
	lw		$t0, x
	lw		$t1, y
	sne		$t0, $t0, $zero
	sne		$t1, $t1, $zero
	and		$t2, $t0, $t1
	seq		$t0, $t2, $zero
	sw		$t0, z
	lw		$t0, z
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S8
	syscall	
	lw		$t0, x
	seq		$t1, $t0, $zero
	lw		$t0, y
	seq		$t2, $t0, $zero
	sne		$t1, $t1, $zero
	sne		$t2, $t2, $zero
	or		$t0, $t1, $t2
	sw		$t0, z
	lw		$t0, z
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S9
	syscall	
	lw		$t0, x
	seq		$t1, $t0, $zero
	seq		$t0, $t1, $zero
	sw		$t0, z
	lw		$t0, z
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S10
	syscall	
	li		$v0, 4
	la		$a0, S11
	syscall	
	li		$v0, 10
	syscall	
	.data	
	.align		4
_nl:	.asciiz		"\n"
_spc:	.asciiz		" "
S11:	.asciiz		"\nTest 18 completed."
S10:	.asciiz		" = !!x\n"
S9:	.asciiz		" = !x || !y\n"
S8:	.asciiz		" = !(x && y)\n"
S7:	.asciiz		" = !x\n"
S6:	.asciiz		" = x || y\n"
S5:	.asciiz		" = x && y\n"
S4:	.asciiz		"\n"
S3:	.asciiz		"y = "
S2:	.asciiz		"\n"
S1:	.asciiz		"x = "
x:	.word		0
y:	.word		0
z:	.word		0
