int numbers[30];
int count;
int i;
int j;
int temp;

void readNums() {

    printString("Enter the number of ints (30 or less) in the array: ");
    read(count);

    i = 0;
    while (i < count) {

        printString("Enter an int: ");
        read(numbers[i]);
        i++;
    }
}

void sort() {

    i = 1;
    while (i < count) {

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

void printNums() {

    printString("\n\n");

    for (i = 0; i < count; i++) {

        print(numbers[i]);
    }
    printString("\n");
}

readNums();
sort();
printNums();