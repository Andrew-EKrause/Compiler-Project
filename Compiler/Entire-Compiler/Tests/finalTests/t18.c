int x;
int y;
int z;

x = 1;
y = 0;

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
