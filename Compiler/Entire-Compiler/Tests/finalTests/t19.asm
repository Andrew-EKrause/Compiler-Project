	.text	
	.globl		main
main:
	li		$v0, 4
	la		$a0, S1
	syscall	
	li		$t0, 0
	sw		$t0, i
L3:
	lw		$t0, i
	li		$t1, 5
	slt		$t2, $t0, $t1
	beq		$zero, $t2, L4
	li		$t0, 0
	sw		$t0, j
L1:
	lw		$t0, j
	li		$t1, 4
	slt		$t3, $t0, $t1
	beq		$zero, $t3, L2
	li		$v0, 5
	syscall	
	sw		$v0, k
	lw		$t0, i
	sll		$t0, $t0, 2
	lw		$t1, j
	mul		$t1, $t1, 5
	sll		$t1, $t1, 2
	add		$t0, $t0, $t1
	lw		$t4, k
	sw		$t4, twoD($t0)
	lw		$t0, j
	li		$t1, 1
	add		$t4, $t0, $t1
	sw		$t4, j
	j		L1
L2:
	lw		$t0, i
	li		$t1, 1
	add		$t3, $t0, $t1
	sw		$t3, i
	j		L3
L4:
	li		$t0, 0
	sw		$t0, i
L7:
	lw		$t0, i
	li		$t1, 5
	slt		$t2, $t0, $t1
	beq		$zero, $t2, L8
	li		$t0, 0
	sw		$t0, j
	lw		$t0, i
	sll		$t0, $t0, 2
	li		$t1, 0
	sw		$t1, rowSums($t0)
L5:
	lw		$t0, j
	li		$t1, 4
	slt		$t3, $t0, $t1
	beq		$zero, $t3, L6
	lw		$t0, i
	sll		$t0, $t0, 2
	lw		$t1, i
	sll		$t1, $t1, 2
	lw		$t1, rowSums($t1)
	lw		$t4, i
	sll		$t4, $t4, 2
	lw		$t5, j
	mul		$t5, $t5, 5
	sll		$t5, $t5, 2
	add		$t4, $t4, $t5
	lw		$t4, twoD($t4)
	add		$t5, $t1, $t4
	sw		$t5, rowSums($t0)
	lw		$t0, j
	li		$t1, 1
	add		$t4, $t0, $t1
	sw		$t4, j
	j		L5
L6:
	lw		$t0, i
	li		$t1, 1
	add		$t3, $t0, $t1
	sw		$t3, i
	j		L7
L8:
	li		$t0, 0
	sw		$t0, j
L11:
	lw		$t0, j
	li		$t1, 4
	slt		$t2, $t0, $t1
	beq		$zero, $t2, L12
	li		$t0, 0
	sw		$t0, i
L9:
	lw		$t0, i
	li		$t1, 5
	slt		$t3, $t0, $t1
	beq		$zero, $t3, L10
	lw		$t0, j
	sll		$t0, $t0, 2
	lw		$t1, j
	sll		$t1, $t1, 2
	lw		$t1, colSums($t1)
	lw		$t4, i
	sll		$t4, $t4, 2
	lw		$t5, j
	mul		$t5, $t5, 5
	sll		$t5, $t5, 2
	add		$t4, $t4, $t5
	lw		$t4, twoD($t4)
	add		$t5, $t1, $t4
	sw		$t5, colSums($t0)
	lw		$t0, i
	li		$t1, 1
	add		$t4, $t0, $t1
	sw		$t4, i
	j		L9
L10:
	lw		$t0, j
	li		$t1, 1
	add		$t3, $t0, $t1
	sw		$t3, j
	j		L11
L12:
	li		$t0, 0
	sw		$t0, i
L15:
	lw		$t0, i
	li		$t1, 5
	slt		$t2, $t0, $t1
	beq		$zero, $t2, L16
	li		$t0, 0
	sw		$t0, j
	lw		$t0, i
	sll		$t0, $t0, 2
	lw		$t0, rowSums($t0)
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S2
	syscall	
L13:
	lw		$t0, j
	li		$t1, 4
	slt		$t3, $t0, $t1
	beq		$zero, $t3, L14
	lw		$t0, i
	sll		$t0, $t0, 2
	lw		$t1, j
	mul		$t1, $t1, 5
	sll		$t1, $t1, 2
	add		$t0, $t0, $t1
	lw		$t0, twoD($t0)
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
	li		$t1, 1
	add		$t4, $t0, $t1
	sw		$t4, j
	j		L13
L14:
	li		$v0, 4
	la		$a0, S4
	syscall	
	lw		$t0, i
	li		$t1, 1
	add		$t3, $t0, $t1
	sw		$t3, i
	j		L15
L16:
	li		$t0, 0
	sw		$t0, j
	li		$v0, 4
	la		$a0, S5
	syscall	
L17:
	lw		$t0, j
	li		$t1, 4
	slt		$t2, $t0, $t1
	beq		$zero, $t2, L18
	lw		$t0, j
	sll		$t0, $t0, 2
	lw		$t0, colSums($t0)
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S6
	syscall	
	lw		$t0, j
	li		$t1, 1
	add		$t3, $t0, $t1
	sw		$t3, j
	j		L17
L18:
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
twoD:	.space		80
colSums:	.space		16
rowSums:	.space		20
S8:	.asciiz		"Test 19 completed."
S7:	.asciiz		"\n\n"
S6:	.asciiz		"\t"
S5:	.asciiz		"\t"
S4:	.asciiz		"\n"
S3:	.asciiz		"\t"
S2:	.asciiz		":\t"
S1:	.asciiz		"Enter 20 ints: \n"
i:	.word		0
j:	.word		0
k:	.word		0
