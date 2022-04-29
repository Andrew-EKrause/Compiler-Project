int x;
int y;
int z;

x = 1;
y = 0;

printString("x = ");
print(x);
printString("\n");

printString("y = ");
print(y);
printString("\n");

z = x && y;
print(z);
printString(" = x && y\n");

z = x || y;
print(z);
printString(" = x || y\n");

z = !x;
print(z);
printString(" = !x\n");

z = !(x && y);
print(z);
printString(" = !(x && y)\n");

z = !x || !y;
print(z);
printString(" = !x || !y\n");

z = !!x;
print(z);
printString(" = !!x\n");

printString("\nTest 18 completed.");