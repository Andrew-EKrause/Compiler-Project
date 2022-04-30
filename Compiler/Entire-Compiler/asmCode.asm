	.text	
	.globl		main
main:
	li		$v0, 4
	la		$a0, S1
	syscall	
	li		$v0, 5
	syscall	
	sw		$v0, count
	li		$t0, 0
	sw		$t0, i
L1:
	lw		$t0, i
	lw		$t1, count
	slt		$t2, $t0, $t1
	beq		$zero, $t2, L2
	li		$v0, 4
	la		$a0, S2
	syscall	
	lw		$t0, i
	sll		$t0, $t0, 2
	li		$v0, 5
	syscall	
	sw		$v0, numbers($t0)
	lw		$t0, i
	li		$t1, 1
	add		$t3, $t0, $t1
	sw		$t3, i
	j		L1
L2:
	li		$v0, 4
	la		$a0, S3
	syscall	
	li		$t0, 0
	sw		$t0, i
L3:
	lw		$t0, i
	lw		$t1, count
	slt		$t2, $t0, $t1
	beq		$zero, $t2, L4
	lw		$t0, i
	sll		$t0, $t0, 2
	lw		$t0, numbers($t0)
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	lw		$t0, i
	li		$t1, 1
	add		$t3, $t0, $t1
	sw		$t3, i
	j		L3
L4:
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
numbers:	.space		120
S5:	.asciiz		"Test 8 completed."
S4:	.asciiz		"\n"
S3:	.asciiz		"\n\n"
S2:	.asciiz		"Enter an int: "
S1:	.asciiz		"Enter the number of ints (30 or less) in the array: "
i:	.word		0
temp:	.word		0
p:	.word		0
s:	.word		0
count:	.word		0
