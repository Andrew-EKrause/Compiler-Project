int i;
int j;
int k;
int m;

printString("Enter 4 integers. The second integer must be positive:\n");

read(i, j, k, m);
print(i, j, k, m);

printSpaces(8);

print(i ^ j * k + m);
printString(" = i ^ j * k + m");

printSpaces(8);

print(m + k * i ^ j);
printString(" = m + k * i ^ j");

printString("\n");