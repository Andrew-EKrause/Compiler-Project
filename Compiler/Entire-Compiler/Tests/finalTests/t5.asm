	.text	
	.globl		main
main:
	li		$v0, 4
	la		$a0, S1
	syscall	
	li		$v0, 4
	la		$a0, S2
	syscall	
	li		$v0, 4
	la		$a0, S3
	syscall	
	li		$v0, 4
	la		$a0, S4
	syscall	
	li		$v0, 5
	syscall	
	sw		$v0, forLoop1
	li		$v0, 4
	la		$a0, S5
	syscall	
	li		$v0, 5
	syscall	
	sw		$v0, forLoop2
	li		$v0, 4
	la		$a0, S6
	syscall	
	li		$v0, 5
	syscall	
	sw		$v0, forLoop3
	li		$v0, 4
	la		$a0, S7
	syscall	
	li		$v0, 5
	syscall	
	sw		$v0, forLoop4
	li		$v0, 4
	la		$a0, S8
	syscall	
	li		$v0, 4
	la		$a0, S9
	syscall	
	li		$v0, 4
	la		$a0, S10
	syscall	
	li		$t0, 0
	sw		$t0, i
L5:
	lw		$t0, i
	lw		$t1, forLoop1
	slt		$t2, $t0, $t1
	beq		$zero, $t2, L6
	li		$v0, 4
	la		$a0, S11
	syscall	
	lw		$t0, i
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S12
	syscall	
	li		$t0, 0
	sw		$t0, j
L3:
	lw		$t0, j
	lw		$t1, forLoop1
	slt		$t3, $t0, $t1
	beq		$zero, $t3, L4
	li		$v0, 4
	la		$a0, S13
	syscall	
	lw		$t0, i
	lw		$t1, j
	add		$t4, $t0, $t1
	add		$a0, $t4, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S14
	syscall	
	li		$t0, 0
	sw		$t0, k
L1:
	lw		$t0, k
	lw		$t1, forLoop1
	slt		$t4, $t0, $t1
	beq		$zero, $t4, L2
	lw		$t0, i
	lw		$t1, j
	add		$t5, $t0, $t1
	lw		$t0, k
	add		$t1, $t5, $t0
	add		$a0, $t1, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S15
	syscall	
	lw		$t0, k
	li		$t1, 1
	add		$t5, $t0, $t1
	sw		$t5, k
	j		L1
L2:
	lw		$t0, j
	li		$t1, 1
	add		$t4, $t0, $t1
	sw		$t4, j
	j		L3
L4:
	lw		$t0, i
	li		$t1, 1
	add		$t3, $t0, $t1
	sw		$t3, i
	j		L5
L6:
	li		$v0, 4
	la		$a0, S16
	syscall	
	li		$v0, 4
	la		$a0, S17
	syscall	
	li		$v0, 4
	la		$a0, S18
	syscall	
	li		$t0, 0
	sw		$t0, l
L7:
	lw		$t0, l
	lw		$t1, forLoop4
	slt		$t2, $t0, $t1
	beq		$zero, $t2, L8
	li		$v0, 4
	la		$a0, S19
	syscall	
	lw		$t0, l
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S20
	syscall	
	lw		$t0, l
	li		$t1, 1
	add		$t3, $t0, $t1
	sw		$t3, l
	j		L7
L8:
	li		$v0, 4
	la		$a0, S21
	syscall	
	li		$v0, 10
	syscall	
	.data	
	.align		4
_nl:	.asciiz		"\n"
_spc:	.asciiz		" "
S21:	.asciiz		"\nTest 5 completed."
S20:	.asciiz		"\n"
S19:	.asciiz		"Single for loop iteration number: "
S18:	.asciiz		"===========================================\n"
S17:	.asciiz		"Single for loop:\n"
S16:	.asciiz		"\n===========================================\n"
S15:	.asciiz		"\n"
S14:	.asciiz		"\n"
S13:	.asciiz		"Inner for loop values:\n"
S12:	.asciiz		"\n"
S11:	.asciiz		"Outer for loop values:\n"
S10:	.asciiz		"===========================================\n"
S9:	.asciiz		"Nested for loops:\n"
S8:	.asciiz		"\n===========================================\n"
S7:	.asciiz		"Enter a positive integer for the single for loop:\n"
S6:	.asciiz		"Enter the third positive integer:\n"
S5:	.asciiz		"Enter the second positive integer:\n"
S4:	.asciiz		"\nEnter the first positive integer:\n"
S3:	.asciiz		"===========================================\n"
S2:	.asciiz		"<Tests for Nested For-Loops and For Loops>\n"
S1:	.asciiz		"===========================================\n"
i:	.word		0
j:	.word		0
k:	.word		0
l:	.word		0
forLoop1:	.word		0
forLoop2:	.word		0
forLoop3:	.word		0
forLoop4:	.word		0
