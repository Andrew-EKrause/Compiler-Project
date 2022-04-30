int forLoop1;
int forLoop2;
int forLoop3;
int forLoop4;

int i;
int j;
int k;
int l;

printString("===========================================\n");
printString("<Tests for Nested For-Loops and For Loops>\n");
printString("===========================================\n");

printString("\nEnter the first positive integer:\n");
read(forLoop1);

printString("Enter the second positive integer:\n");
read(forLoop2);

printString("Enter the third positive integer:\n");
read(forLoop3);

printString("Enter a positive integer for the single for loop:\n");
read(forLoop4);

printString("\n===========================================\n");
printString("Nested for loops:\n");
printString("===========================================\n");

for(i = 0; i < forLoop1; i = i + 1) {

    printString("Outer for loop values:\n");
    print(i);
    printString("\n");
    for(j = 0; j < forLoop1; j = j + 1) {

        printString("Inner for loop values:\n");
        print(i + j);
        printString("\n");
        for(k = 0; k < forLoop1; k = k + 1) {

            print(i + j + k);
            printString("\n");
        }
    }
}

printString("\n===========================================\n");
printString("Single for loop:\n");
printString("===========================================\n");

for(l = 0; l < forLoop4; l = l + 1) {

    printString("Single for loop iteration number: ");
    print(l);
    printString("\n");
}

printString("\nTest 5 completed.");