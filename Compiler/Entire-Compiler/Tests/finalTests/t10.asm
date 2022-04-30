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
	li		$v0, 4
	la		$a0, S5
	syscall	
	li		$v0, 4
	la		$a0, S6
	syscall	
	li		$v0, 4
	la		$a0, S7
	syscall	
	li		$v0, 4
	la		$a0, S8
	syscall	
	li		$v0, 4
	la		$a0, S9
	syscall	
	li		$v0, 4
	la		$a0, S10
	syscall	
	li		$v0, 4
	la		$a0, S11
	syscall	
	li		$v0, 4
	la		$a0, S12
	syscall	
	li		$v0, 4
	la		$a0, S13
	syscall	
	li		$v0, 4
	la		$a0, S14
	syscall	
	li		$v0, 4
	la		$a0, S15
	syscall	
	li		$v0, 5
	syscall	
	sw		$v0, pizzaSize
	li		$v0, 4
	la		$a0, S16
	syscall	
	li		$v0, 4
	la		$a0, S17
	syscall	
	li		$v0, 4
	la		$a0, S18
	syscall	
	li		$v0, 4
	la		$a0, S19
	syscall	
	li		$v0, 4
	la		$a0, S20
	syscall	
	li		$v0, 4
	la		$a0, S21
	syscall	
	li		$v0, 4
	la		$a0, S22
	syscall	
	li		$v0, 4
	la		$a0, S23
	syscall	
	li		$v0, 4
	la		$a0, S24
	syscall	
	li		$v0, 4
	la		$a0, S25
	syscall	
	li		$v0, 4
	la		$a0, S26
	syscall	
	li		$v0, 4
	la		$a0, S27
	syscall	
	li		$v0, 5
	syscall	
	sw		$v0, pizzaType
	li		$v0, 4
	la		$a0, S28
	syscall	
	li		$v0, 4
	la		$a0, S29
	syscall	
	li		$v0, 4
	la		$a0, S30
	syscall	
	li		$v0, 4
	la		$a0, S31
	syscall	
	li		$v0, 4
	la		$a0, S32
	syscall	
	li		$v0, 4
	la		$a0, S33
	syscall	
	li		$v0, 4
	la		$a0, S34
	syscall	
	li		$v0, 4
	la		$a0, S35
	syscall	
	li		$v0, 4
	la		$a0, S36
	syscall	
	li		$v0, 4
	la		$a0, S37
	syscall	
	li		$v0, 4
	la		$a0, S38
	syscall	
	li		$v0, 4
	la		$a0, S39
	syscall	
	li		$v0, 4
	la		$a0, S40
	syscall	
	li		$v0, 4
	la		$a0, S41
	syscall	
	li		$v0, 4
	la		$a0, S42
	syscall	
	li		$v0, 4
	la		$a0, S43
	syscall	
	li		$v0, 4
	la		$a0, S44
	syscall	
	li		$v0, 5
	syscall	
	sw		$v0, numberOfPizzas
	li		$v0, 4
	la		$a0, S45
	syscall	
	li		$v0, 4
	la		$a0, S46
	syscall	
	li		$v0, 4
	la		$a0, S47
	syscall	
	li		$v0, 4
	la		$a0, S48
	syscall	
	li		$v0, 4
	la		$a0, S49
	syscall	
	li		$v0, 4
	la		$a0, S50
	syscall	
	li		$v0, 4
	la		$a0, S51
	syscall	
	li		$v0, 4
	la		$a0, S52
	syscall	
	li		$v0, 5
	syscall	
	sw		$v0, withBreadSticks
	lw		$t0, pizzaSize
	li		$t1, 1
	seq		$t2, $t0, $t1
	sne		$t0, $t2, $zero
	beq		$t0, $zero, L1
	li		$t0, 5
	sw		$t0, pizzaSizeCost
L1:
	lw		$t0, pizzaSize
	li		$t1, 2
	seq		$t2, $t0, $t1
	sne		$t0, $t2, $zero
	beq		$t0, $zero, L2
	li		$t0, 8
	sw		$t0, pizzaSizeCost
L2:
	lw		$t0, pizzaSize
	li		$t1, 3
	seq		$t2, $t0, $t1
	sne		$t0, $t2, $zero
	beq		$t0, $zero, L3
	li		$t0, 12
	sw		$t0, pizzaSizeCost
L3:
	lw		$t0, pizzaSize
	li		$t1, 4
	seq		$t2, $t0, $t1
	sne		$t0, $t2, $zero
	beq		$t0, $zero, L4
	li		$t0, 14
	sw		$t0, pizzaSizeCost
L4:
	lw		$t0, pizzaSize
	li		$t1, 5
	seq		$t2, $t0, $t1
	sne		$t0, $t2, $zero
	beq		$t0, $zero, L5
	li		$t0, 16
	sw		$t0, pizzaSizeCost
L5:
	lw		$t0, pizzaType
	li		$t1, 1
	seq		$t2, $t0, $t1
	sne		$t0, $t2, $zero
	beq		$t0, $zero, L6
	li		$t0, 1
	sw		$t0, totalCostOrPizzaType
L6:
	lw		$t0, pizzaType
	li		$t1, 2
	seq		$t2, $t0, $t1
	sne		$t0, $t2, $zero
	beq		$t0, $zero, L7
	li		$t0, 1
	sw		$t0, totalCostOrPizzaType
L7:
	lw		$t0, pizzaType
	li		$t1, 3
	seq		$t2, $t0, $t1
	sne		$t0, $t2, $zero
	beq		$t0, $zero, L8
	li		$t0, 0
	sw		$t0, totalCostOrPizzaType
L8:
	lw		$t0, pizzaType
	li		$t1, 4
	seq		$t2, $t0, $t1
	sne		$t0, $t2, $zero
	beq		$t0, $zero, L9
	li		$t0, 2
	sw		$t0, totalCostOrPizzaType
L9:
	lw		$t0, pizzaType
	li		$t1, 5
	seq		$t2, $t0, $t1
	sne		$t0, $t2, $zero
	beq		$t0, $zero, L10
	li		$t0, 2
	sw		$t0, totalCostOrPizzaType
L10:
	lw		$t0, pizzaType
	li		$t1, 6
	seq		$t2, $t0, $t1
	sne		$t0, $t2, $zero
	beq		$t0, $zero, L11
	li		$t0, 3
	sw		$t0, totalCostOrPizzaType
L11:
	lw		$t0, withBreadSticks
	li		$t1, 0
	seq		$t2, $t0, $t1
	sne		$t0, $t2, $zero
	beq		$t0, $zero, L12
	li		$t0, 0
	sw		$t0, breadSticksCost
L12:
	lw		$t0, withBreadSticks
	li		$t1, 1
	seq		$t2, $t0, $t1
	sne		$t0, $t2, $zero
	beq		$t0, $zero, L13
	li		$t0, 5
	sw		$t0, breadSticksCost
L13:
	li		$v0, 4
	la		$a0, S53
	syscall	
	li		$v0, 4
	la		$a0, S54
	syscall	
	li		$v0, 4
	la		$a0, S55
	syscall	
	li		$v0, 4
	la		$a0, S56
	syscall	
	li		$v0, 4
	la		$a0, S57
	syscall	
	li		$v0, 5
	syscall	
	sw		$v0, orderConfirmed
	lw		$t0, orderConfirmed
	li		$t1, 0
	seq		$t2, $t0, $t1
	beq		$zero, $t2, L27
	li		$v0, 4
	la		$a0, S58
	syscall	
L27:
	bne		$zero, $t2, L28
	li		$v0, 4
	la		$a0, S59
	syscall	
	li		$v0, 4
	la		$a0, S60
	syscall	
	li		$v0, 4
	la		$a0, S61
	syscall	
	li		$v0, 4
	la		$a0, S62
	syscall	
	lw		$t0, pizzaSize
	li		$t1, 1
	seq		$t3, $t0, $t1
	sne		$t0, $t3, $zero
	beq		$t0, $zero, L14
	li		$v0, 4
	la		$a0, S63
	syscall	
L14:
	lw		$t0, pizzaSize
	li		$t1, 2
	seq		$t3, $t0, $t1
	sne		$t0, $t3, $zero
	beq		$t0, $zero, L15
	li		$v0, 4
	la		$a0, S64
	syscall	
L15:
	lw		$t0, pizzaSize
	li		$t1, 3
	seq		$t3, $t0, $t1
	sne		$t0, $t3, $zero
	beq		$t0, $zero, L16
	li		$v0, 4
	la		$a0, S65
	syscall	
L16:
	lw		$t0, pizzaSize
	li		$t1, 4
	seq		$t3, $t0, $t1
	sne		$t0, $t3, $zero
	beq		$t0, $zero, L17
	li		$v0, 4
	la		$a0, S66
	syscall	
L17:
	lw		$t0, pizzaSize
	li		$t1, 5
	seq		$t3, $t0, $t1
	sne		$t0, $t3, $zero
	beq		$t0, $zero, L18
	li		$v0, 4
	la		$a0, S67
	syscall	
L18:
	li		$v0, 4
	la		$a0, S68
	syscall	
	lw		$t0, pizzaType
	li		$t1, 1
	seq		$t3, $t0, $t1
	sne		$t0, $t3, $zero
	beq		$t0, $zero, L19
	li		$v0, 4
	la		$a0, S69
	syscall	
L19:
	lw		$t0, pizzaType
	li		$t1, 2
	seq		$t3, $t0, $t1
	sne		$t0, $t3, $zero
	beq		$t0, $zero, L20
	li		$v0, 4
	la		$a0, S70
	syscall	
L20:
	lw		$t0, pizzaType
	li		$t1, 3
	seq		$t3, $t0, $t1
	sne		$t0, $t3, $zero
	beq		$t0, $zero, L21
	li		$v0, 4
	la		$a0, S71
	syscall	
L21:
	lw		$t0, pizzaType
	li		$t1, 4
	seq		$t3, $t0, $t1
	sne		$t0, $t3, $zero
	beq		$t0, $zero, L22
	li		$v0, 4
	la		$a0, S72
	syscall	
L22:
	lw		$t0, pizzaType
	li		$t1, 5
	seq		$t3, $t0, $t1
	sne		$t0, $t3, $zero
	beq		$t0, $zero, L23
	li		$v0, 4
	la		$a0, S73
	syscall	
L23:
	lw		$t0, pizzaType
	li		$t1, 6
	seq		$t3, $t0, $t1
	sne		$t0, $t3, $zero
	beq		$t0, $zero, L24
	li		$v0, 4
	la		$a0, S74
	syscall	
L24:
	li		$v0, 4
	la		$a0, S75
	syscall	
	lw		$t0, numberOfPizzas
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S76
	syscall	
	li		$v0, 4
	la		$a0, S77
	syscall	
	lw		$t0, withBreadSticks
	li		$t1, 0
	seq		$t3, $t0, $t1
	sne		$t0, $t3, $zero
	beq		$t0, $zero, L25
	li		$v0, 4
	la		$a0, S78
	syscall	
L25:
	lw		$t0, withBreadSticks
	li		$t1, 1
	seq		$t3, $t0, $t1
	sne		$t0, $t3, $zero
	beq		$t0, $zero, L26
	li		$v0, 4
	la		$a0, S79
	syscall	
L26:
	lw		$t0, pizzaSizeCost
	lw		$t1, numberOfPizzas
	mul		$t3, $t0, $t1
	lw		$t0, totalCostOrPizzaType
	lw		$t1, numberOfPizzas
	mul		$t4, $t0, $t1
	add		$t0, $t3, $t4
	lw		$t1, breadSticksCost
	add		$t3, $t0, $t1
	sw		$t3, totalCostOrPizzaType
	li		$v0, 4
	la		$a0, S80
	syscall	
	lw		$t0, totalCostOrPizzaType
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 11
	la		$a0, _spc
	syscall	
	li		$v0, 4
	la		$a0, S81
	syscall	
	li		$v0, 4
	la		$a0, S82
	syscall	
L28:
	li		$v0, 4
	la		$a0, S83
	syscall	
	li		$v0, 4
	la		$a0, S84
	syscall	
	li		$v0, 10
	syscall	
	.data	
	.align		4
_nl:	.asciiz		"\n"
_spc:	.asciiz		" "
S84:	.asciiz		"\nTest 10 completed."
S83:	.asciiz		"===========================================\n"
S82:	.asciiz		"\nThank you for your order. Have a nice day!\n"
S81:	.asciiz		".00"
S80:	.asciiz		"\nTotal Cost of Order: $"
S79:	.asciiz		"Yes\n"
S78:	.asciiz		"No\n"
S77:	.asciiz		"-With Breadsticks? "
S76:	.asciiz		"\n"
S75:	.asciiz		"-Number of Pizzas: "
S74:	.asciiz		"Supreme\n"
S73:	.asciiz		"Chicken\n"
S72:	.asciiz		"Sausage/Pepperoni\n"
S71:	.asciiz		"Cheese\n"
S70:	.asciiz		"Sausage\n"
S69:	.asciiz		"Pepperoni\n"
S68:	.asciiz		"-Type of Pizza: "
S67:	.asciiz		"24 inches\n"
S66:	.asciiz		"20 inches\n"
S65:	.asciiz		"16 inches\n"
S64:	.asciiz		"12 inches\n"
S63:	.asciiz		"8 inches\n"
S62:	.asciiz		"-Size of Pizza(s): "
S61:	.asciiz		"===========================================\n"
S60:	.asciiz		"ORDER RECEIPT:\n"
S59:	.asciiz		"\n===========================================\n"
S58:	.asciiz		"\nOrder was cancelled. Have a nice day!\n"
S57:	.asciiz		"(1) = Yes\n"
S56:	.asciiz		"(0) = No\n"
S55:	.asciiz		"===========================================\n"
S54:	.asciiz		"Confirm Order?\n"
S53:	.asciiz		"\n===========================================\n"
S52:	.asciiz		"(1) = Yes - $5.00\n"
S51:	.asciiz		"(0) = No - $0.00\n"
S50:	.asciiz		"===========================================\n"
S49:	.asciiz		"With Breadsticks?\n"
S48:	.asciiz		"===========================================\n"
S47:	.asciiz		"below:\n"
S46:	.asciiz		"with your pizza order. Selections are listed\n"
S45:	.asciiz		"\nLastly, select whether you want breadsticks\n"
S44:	.asciiz		"(10) = 10 pizzas\n"
S43:	.asciiz		"(9) = 9 pizzas\n"
S42:	.asciiz		"(8) = 8 pizzas\n"
S41:	.asciiz		"(7) = 7 pizzas\n"
S40:	.asciiz		"(6) = 6 pizzas\n"
S39:	.asciiz		"(5) = 5 pizzas\n"
S38:	.asciiz		"(4) = 4 pizzas\n"
S37:	.asciiz		"(3) = 3 pizzas\n"
S36:	.asciiz		"(2) = 2 pizzas\n"
S35:	.asciiz		"(1) = 1 pizza\n"
S34:	.asciiz		"===========================================\n"
S33:	.asciiz		"Number of Pizzas Selections:\n"
S32:	.asciiz		"===========================================\n"
S31:	.asciiz		"are listed below (can order up to 10):\n"
S30:	.asciiz		"of pizzas for your order. you want. Selections\n"
S29:	.asciiz		"Enter the number corresponding to the number\n"
S28:	.asciiz		"\nNow select the number of pizzas you want.\n"
S27:	.asciiz		"(6) = Supreme - $3.00\n"
S26:	.asciiz		"(5) = Chicken - $2.00\n"
S25:	.asciiz		"(4) = Sausage/Pepperoni - $2.00\n"
S24:	.asciiz		"(3) = Cheese - $0.00\n"
S23:	.asciiz		"(2) = Sausage - $1.00\n"
S22:	.asciiz		"(1) = Pepperoni - $1.00\n"
S21:	.asciiz		"===========================================\n"
S20:	.asciiz		"Pizza Type Selections:\n"
S19:	.asciiz		"===========================================\n"
S18:	.asciiz		"type selection. Selections are listed below:\n"
S17:	.asciiz		"Enter the number corresponding to the pizza\n"
S16:	.asciiz		"\nNext, select the type of pizza you want.\n"
S15:	.asciiz		"(5) = 24 inches - $16.00\n"
S14:	.asciiz		"(4) = 20 inches - $14.00\n"
S13:	.asciiz		"(3) = 16 inches - $12.00\n"
S12:	.asciiz		"(2) = 12 inches - $8.00\n"
S11:	.asciiz		"(1) = 8 inches - $5.00\n"
S10:	.asciiz		"===========================================\n"
S9:	.asciiz		"Pizza Size Selections:\n"
S8:	.asciiz		"===========================================\n"
S7:	.asciiz		"below:\n"
S6:	.asciiz		"size selection you want. Selections are listed\n"
S5:	.asciiz		"Enter the number corresponding to the pizza\n"
S4:	.asciiz		"\nFirst, select the size of the pizza.\n"
S3:	.asciiz		"===========================================\n"
S2:	.asciiz		"<Simple Pizza Program>\n"
S1:	.asciiz		"===========================================\n"
orderConfirmed:	.word		0
pizzaSize:	.word		0
totalCostOrPizzaType:	.word		0
numberOfPizzas:	.word		0
pizzaType:	.word		0
pizzaSizeCost:	.word		0
breadSticksCost:	.word		0
withBreadSticks:	.word		0
