int numbers[30];
int count;
int i;
int s;
int p;
int temp;

printString("Enter the number of ints (30 or less) in the array: ");
read(count);

i = 0;
while (i < count) {

	printString("Enter an int: ");
	read(numbers[i]);
	i = i + 1;
}

printString("\n\n");

for (i = 0; i < count; i = i + 1) {
	numbers[i] = 123;
	print(numbers[i]);
}

printString("\n");
printString("Test 8 completed.");