int x;

int fib(int n) {

    if (n <= 1) {
        return 1;
    }
    return fib(n - 2) + fib(n - 1);
}

printString("Enter an int: ");
read(x);

print(fib(x));
printString(" = ");
print(x);
printString("th Fibonacci number\n");
print(fib(2*x));
printString(" = ");
print(2 * x);
printString("th Fibonacci number\n");

printString("\nTest 14 completed.");