int x;

int fact(int n) {

    if (n <= 1) {
        return 1;
    }
    return n * fact(n-1);
}

printString("Enter an int: ");
read(x);

print(fact(x));
printString(" = ");
print(x);
printString("!\n");

print(2 * fact(2 * x));
printString(" = 2 * (2 * ");
print(x);
printString(")!\n");
