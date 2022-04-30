	.text	
	.globl		main
main:
	li		$t0, 555
	sw		$t0, num1
	li		$t0, 777
	sw		$t0, num2
	li		$t0, 5
	sw		$t0, num3
	lw		$t0, num1
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$t0, 2
	lw		$t1, num3
	mul		$t2, $t0, $t1
	move		$t0, $t2
	beq		$zero, $t0, L2
L1:
	li		$v0, 4
	la		$a0, _spc
	syscall	
	subi		$t0, $t0, 1
	bne		$zero, $t0, L1
L2:
	lw		$t0, num2
	add		$a0, $t0, $zero
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
num1:	.word		0
num2:	.word		0
num3:	.word		0
