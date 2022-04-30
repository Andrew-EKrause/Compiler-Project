int pizzaSize;
int pizzaType;
int numberOfPizzas;
int withBreadSticks;
int orderConfirmed;

int pizzaSizeCost;
int breadSticksCost;
int totalCostOrPizzaType;


printString("===========================================\n");
printString("<Simple Pizza Program>\n");
printString("===========================================\n");


printString("\nFirst, select the size of the pizza.\n");
printString("Enter the number corresponding to the pizza\n");
printString("size selection you want. Selections are listed\n");
printString("below:\n");

printString("===========================================\n");
printString("Pizza Size Selections:\n");
printString("===========================================\n");
printString("(1) = 8 inches - $5.00\n");
printString("(2) = 12 inches - $8.00\n");
printString("(3) = 16 inches - $12.00\n");
printString("(4) = 20 inches - $14.00\n");
printString("(5) = 24 inches - $16.00\n");
read(pizzaSize);


printString("\nNext, select the type of pizza you want.\n");
printString("Enter the number corresponding to the pizza\n");
printString("type selection. Selections are listed below:\n");

printString("===========================================\n");
printString("Pizza Type Selections:\n");
printString("===========================================\n");
printString("(1) = Pepperoni - $1.00\n");
printString("(2) = Sausage - $1.00\n");
printString("(3) = Cheese - $0.00\n");
printString("(4) = Sausage/Pepperoni - $2.00\n");
printString("(5) = Chicken - $2.00\n");
printString("(6) = Supreme - $3.00\n");
read(pizzaType);


printString("\nNow select the number of pizzas you want.\n");
printString("Enter the number corresponding to the number\n");
printString("of pizzas for your order. you want. Selections\n");
printString("are listed below (can order up to 10):\n");

printString("===========================================\n");
printString("Number of Pizzas Selections:\n");
printString("===========================================\n");
printString("(1) = 1 pizza\n");
printString("(2) = 2 pizzas\n");
printString("(3) = 3 pizzas\n");
printString("(4) = 4 pizzas\n");
printString("(5) = 5 pizzas\n");
printString("(6) = 6 pizzas\n");
printString("(7) = 7 pizzas\n");
printString("(8) = 8 pizzas\n");
printString("(9) = 9 pizzas\n");
printString("(10) = 10 pizzas\n");
read(numberOfPizzas);


printString("\nLastly, select whether you want breadsticks\n");
printString("with your pizza order. Selections are listed\n");
printString("below:\n");

printString("===========================================\n");
printString("With Breadsticks?\n");
printString("===========================================\n");
printString("(0) = No - $0.00\n");
printString("(1) = Yes - $5.00\n");
read(withBreadSticks);


if(pizzaSize == 1) {
    pizzaSizeCost = 5;
}
if(pizzaSize == 2) {
    pizzaSizeCost = 8;
}
if(pizzaSize == 3) {
    pizzaSizeCost = 12;
}
if(pizzaSize == 4) {
    pizzaSizeCost = 14;
}
if(pizzaSize == 5) {
    pizzaSizeCost = 16;
}


if(pizzaType == 1) {
    totalCostOrPizzaType = 1;
}
if(pizzaType == 2) {
    totalCostOrPizzaType = 1;
}
if(pizzaType == 3) {
    totalCostOrPizzaType = 0;
}
if(pizzaType == 4) {
    totalCostOrPizzaType = 2;
}
if(pizzaType == 5) {
    totalCostOrPizzaType = 2;
}
if(pizzaType == 6) {
    totalCostOrPizzaType = 3;
}


if(withBreadSticks == 0) {
    breadSticksCost = 0;
}
if(withBreadSticks == 1) {
    breadSticksCost = 5;
}


printString("\n===========================================\n");
printString("Confirm Order?\n");
printString("===========================================\n");
printString("(0) = No\n");
printString("(1) = Yes\n");
read(orderConfirmed);


if(orderConfirmed == 0) {

    printString("\nOrder was cancelled. Have a nice day!\n");

} else {
    
    printString("\n===========================================\n");
    printString("ORDER RECEIPT:\n");
    printString("===========================================\n");


    printString("-Size of Pizza(s): ");
    if(pizzaSize == 1) {
        printString("8 inches\n");
    }
    if(pizzaSize == 2) {
        printString("12 inches\n");
    }
    if(pizzaSize == 3) {
        printString("16 inches\n");
    }
    if(pizzaSize == 4) {
        printString("20 inches\n");
    }
    if(pizzaSize == 5) {
        printString("24 inches\n");
    }


    printString("-Type of Pizza: ");
    if(pizzaType == 1) {
        printString("Pepperoni\n");
    }
    if(pizzaType == 2) {
        printString("Sausage\n");
    }
    if(pizzaType == 3) {
        printString("Cheese\n");
    }
    if(pizzaType == 4) {
        printString("Sausage/Pepperoni\n");
    }
    if(pizzaType == 5) {
        printString("Chicken\n");
    }
    if(pizzaType == 6) {
        printString("Supreme\n");
    }


    printString("-Number of Pizzas: ");
    print(numberOfPizzas);
    printString("\n");


    printString("-With Breadsticks? ");
    if(withBreadSticks == 0) {
        printString("No\n");
    }
    if(withBreadSticks == 1) {
        printString("Yes\n");
    }


    totalCostOrPizzaType = (pizzaSizeCost * numberOfPizzas) + (totalCostOrPizzaType * numberOfPizzas) + breadSticksCost;
    printString("\nTotal Cost of Order: $");
    print(totalCostOrPizzaType);
    printString(".00");
    printString("\nThank you for your order. Have a nice day!\n");
}
printString("===========================================\n");

printString("\nTest 10 completed.");