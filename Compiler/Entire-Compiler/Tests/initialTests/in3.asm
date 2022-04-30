	.text	
	.globl		main
main:
	li		$v0, 4
	la		$a0, S1
	syscall	
	li		$t0, 10
	li		$t1, 2
	add		$t2, $t0, $t1
	sw		$t2, num1
	li		$t0, 20
	li		$t1, 3
	mul		$t2, $t0, $t1
	lw		$t0, num1
	add		$t1, $t2, $t0
	sw		$t1, num2
	lw		$t0, num2
	lw		$t1, num1
	sub		$t2, $t0, $t1
	sw		$t2, num3
	lw		$t0, num3
	li		$t1, 20
	div		$t2, $t0, $t1
	sw		$t2, num4
	lw		$t0, num3
	li		$t1, 21
	div		$t2, $t0, $t1
	mfhi		$t2
	sw		$t2, num5
	lw		$t0, num5
	lw		$t1, num4
	mul		$t1, $t1, -1
	add		$t2, $t0, $t1
	sw		$t2, num6
	li		$t0, 2
	mul		$t0, $t0, -1
	li		$t1, 9
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
	sw		$t2, num7
	lw		$t0, num1
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	lw		$t0, num2
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	lw		$t0, num3
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	lw		$t0, num4
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	lw		$t0, num4
	move		$t1, $t0
	beq		$zero, $t1, L5
L4:
	li		$v0, 4
	la		$a0, _nl
	syscall	
	subi		$t1, $t1, 1
	bne		$zero, $t1, L4
L5:
	lw		$t0, num1
	move		$t1, $t0
	beq		$zero, $t1, L7
L6:
	li		$v0, 4
	la		$a0, _spc
	syscall	
	subi		$t1, $t1, 1
	bne		$zero, $t1, L6
L7:
	lw		$t0, num5
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	lw		$t0, num5
	mul		$t0, $t0, -1
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	lw		$t0, num6
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	lw		$t0, num7
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	lw		$t0, num7
	li		$t1, 512
	mul		$t1, $t1, -1
	seq		$t2, $t0, $t1
	sne		$t0, $t2, $zero
	beq		$t0, $zero, L8
	lw		$t0, num7
	li		$t1, 2
	mul		$t3, $t0, $t1
	add		$a0, $t3, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
L8:
	li		$t0, 2
	li		$t1, 5
	li		$t2, 2
	move		$t3, $t1
	move		$t4, $t2
	move		$t5, $t2
	sub		$t5, $t5, 1
	beq		$zero, $t5, L11
	sub		$t4, $t4, 1
L9:
	beq		$zero, $t4, L10
	mul		$t3, $t3, $t1
	subi		$t4, $t4, 1
	j		L9
L11:
	move		$t3, $t1
L10:
	mul		$t1, $t0, $t3
	sw		$t1, num7
	lw		$t0, num7
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$t0, 2
	li		$t1, 5
	add		$t2, $t0, $t1
	li		$t0, 6
	mul		$t1, $t2, $t0
	sw		$t1, num7
	lw		$t0, num7
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S2
	syscall	
	li		$t0, 10
	sw		$t0, num8
	lw		$t0, num8
	li		$t1, 10
	seq		$t2, $t0, $t1
	sne		$t0, $t2, $zero
	beq		$t0, $zero, L12
	li		$v0, 4
	la		$a0, S3
	syscall	
L12:
	lw		$t0, num8
	li		$t1, 11
	slt		$t2, $t0, $t1
	sne		$t0, $t2, $zero
	beq		$t0, $zero, L13
	li		$v0, 4
	la		$a0, S4
	syscall	
L13:
	lw		$t0, num8
	li		$t1, 10
	sle		$t2, $t0, $t1
	sne		$t0, $t2, $zero
	beq		$t0, $zero, L14
	li		$v0, 4
	la		$a0, S5
	syscall	
L14:
	lw		$t0, num8
	li		$t1, 10
	sge		$t2, $t0, $t1
	sne		$t0, $t2, $zero
	beq		$t0, $zero, L15
	li		$v0, 4
	la		$a0, S6
	syscall	
L15:
	lw		$t0, num8
	li		$t1, 9
	sgt		$t2, $t0, $t1
	sne		$t0, $t2, $zero
	beq		$t0, $zero, L16
	li		$v0, 4
	la		$a0, S7
	syscall	
L16:
	lw		$t0, num8
	li		$t1, 11
	sne		$t2, $t0, $t1
	sne		$t0, $t2, $zero
	beq		$t0, $zero, L17
	li		$v0, 4
	la		$a0, S8
	syscall	
L17:
	li		$t0, 10
	sw		$t0, x
	li		$t0, 11
	sw		$t0, y
	lw		$t0, x
	li		$t1, 10
	seq		$t2, $t0, $t1
	lw		$t0, y
	li		$t1, 11
	sne		$t3, $t0, $t1
	sne		$t2, $t2, $zero
	sne		$t3, $t3, $zero
	or		$t0, $t2, $t3
	sne		$t1, $t0, $zero
	beq		$t1, $zero, L18
	li		$v0, 4
	la		$a0, S9
	syscall	
L18:
	lw		$t0, x
	li		$t1, 11
	slt		$t2, $t0, $t1
	lw		$t0, y
	li		$t1, 10
	sge		$t3, $t0, $t1
	sne		$t2, $t2, $zero
	sne		$t3, $t3, $zero
	and		$t0, $t2, $t3
	sne		$t1, $t0, $zero
	beq		$t1, $zero, L19
	li		$v0, 4
	la		$a0, S10
	syscall	
L19:
	lw		$t0, x
	li		$t1, 10
	seq		$t2, $t0, $t1
	lw		$t0, y
	li		$t1, 11
	sgt		$t3, $t0, $t1
	lw		$t0, x
	li		$t1, 10
	sge		$t4, $t0, $t1
	sne		$t3, $t3, $zero
	sne		$t4, $t4, $zero
	and		$t0, $t3, $t4
	sne		$t2, $t2, $zero
	sne		$t0, $t0, $zero
	and		$t1, $t2, $t0
	seq		$t0, $t1, $zero
	sne		$t1, $t0, $zero
	beq		$t1, $zero, L20
	li		$v0, 4
	la		$a0, S11
	syscall	
L20:
	lw		$t0, x
	li		$t1, 10
	sgt		$t2, $t0, $t1
	lw		$t0, x
	lw		$t1, y
	slt		$t3, $t0, $t1
	sne		$t2, $t2, $zero
	sne		$t3, $t3, $zero
	or		$t0, $t2, $t3
	seq		$t1, $t0, $zero
	seq		$t0, $t1, $zero
	sne		$t1, $t0, $zero
	beq		$t1, $zero, L21
	li		$v0, 4
	la		$a0, S12
	syscall	
L21:
	lw		$t0, x
	li		$t1, 10
	sgt		$t2, $t0, $t1
	seq		$t0, $t2, $zero
	sne		$t1, $t0, $zero
	beq		$t1, $zero, L22
	li		$v0, 4
	la		$a0, S13
	syscall	
L22:
	li		$t0, 1
	move		$t1, $t0
	beq		$zero, $t1, L24
L23:
	li		$v0, 4
	la		$a0, _nl
	syscall	
	subi		$t1, $t1, 1
	bne		$zero, $t1, L23
L24:
	lw		$t0, x
	lw		$t1, y
	add		$t2, $t0, $t1
	add		$a0, $t2, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	lw		$t0, num1
	li		$t1, 2
	move		$t3, $t0
	move		$t4, $t1
	move		$t5, $t1
	sub		$t5, $t5, 1
	beq		$zero, $t5, L27
	sub		$t4, $t4, 1
L25:
	beq		$zero, $t4, L26
	mul		$t3, $t3, $t0
	subi		$t4, $t4, 1
	j		L25
L27:
	move		$t3, $t0
L26:
	add		$a0, $t3, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	lw		$t0, num3
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$t0, 2
	move		$t1, $t0
	beq		$zero, $t1, L29
L28:
	li		$v0, 4
	la		$a0, _nl
	syscall	
	subi		$t1, $t1, 1
	bne		$zero, $t1, L28
L29:
	li		$t0, 0
	sw		$t0, tester
L30:
	lw		$t0, tester
	li		$t1, 5
	slt		$t2, $t0, $t1
	beq		$zero, $t2, L31
	li		$v0, 4
	la		$a0, S14
	syscall	
	lw		$t0, tester
	li		$t1, 1
	add		$t3, $t0, $t1
	sw		$t3, tester
	j		L30
L31:
	li		$t0, 1
	move		$t1, $t0
	beq		$zero, $t1, L33
L32:
	li		$v0, 4
	la		$a0, _nl
	syscall	
	subi		$t1, $t1, 1
	bne		$zero, $t1, L32
L33:
	li		$t0, 0
	sw		$t0, tester
L34:
	lw		$t0, tester
	li		$t1, 10
	slt		$t2, $t0, $t1
	beq		$zero, $t2, L35
	li		$v0, 4
	la		$a0, S15
	syscall	
	lw		$t0, tester
	li		$t1, 1
	add		$t3, $t0, $t1
	sw		$t3, tester
	j		L34
L35:
	li		$v0, 10
	syscall	
	.data	
	.align		4
_nl:	.asciiz		"\n"
_spc:	.asciiz		" "
S15:	.asciiz		"FOR LOOP!\n"
S14:	.asciiz		"TESTER!\n"
S13:	.asciiz		"True5\n"
S12:	.asciiz		"True4\n"
S11:	.asciiz		"True3\n"
S10:	.asciiz		"True2\n"
S9:	.asciiz		"True1\n"
S8:	.asciiz		"10 != 11, Good Job!\n"
S7:	.asciiz		"10 > 9, Good Job!\n"
S6:	.asciiz		"10 >= 10, Good Job!\n"
S5:	.asciiz		"10 <= 10, Good Job!\n"
S4:	.asciiz		"10 < 11, Good Job!\n"
S3:	.asciiz		"10 == 10, Good Job!\n"
S2:	.asciiz		"\nGoodbye!\n\n"
S1:	.asciiz		"Hello there!\n"
tester:	.word		0
x:	.word		0
y:	.word		0
num1:	.word		0
num2:	.word		0
num3:	.word		0
num4:	.word		0
num5:	.word		0
num6:	.word		0
num7:	.word		0
num8:	.word		0
