int numbers[30];

int readNums() {

    int i;
    int count;

    printString("Enter the number of ints (30 or less) in the array: ");
    read(count);

    i = 0;
    while (i < count) {

        printString("Enter an int: ");
        read(numbers[i]);
        i++;
    }

    return count;
}

void sort(int size) {

    int i;
    int j;
    int temp;

    i = 1;
    while (i < size) {

        j = i-1;
        temp = numbers[i];

        while (j >= 0 && numbers[j] < temp) {

            numbers[j+1] = numbers[j];
            j = j - 1;
        }

        numbers[j+1] = temp;
        i = i + 1;
    }
}

void printNums(int size) {

    int i;
    printString("\n\n");

    for (i = 0; i < size; i++) {

        print(numbers[i]);
    }
    printString("\n");
}

int count;
count = readNums();
sort(count);
printNums(count);

printString("\nTest 15 completed.");