int n;
int x;

int fact() {

    if (n <= 1) {
        return 1;
    }
    
    n = n - 1;
    return (n + 1) * fact();
}

printString("Enter an int: ");
read(n);

x = n;
print(fact());
printString(" = ");
print(x);

printString("\n");
printString("Test 12 completed.");