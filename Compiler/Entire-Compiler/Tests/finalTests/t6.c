int low;
int mid;
int high;
int temp;
int count;

printString("Enter the number of triples to be processed: \n");
read(count);

while (count > 0) {

    printString("Enter three integers: \n");
    read(low, mid, high);

    if (low > mid) {
        temp = low;
        low = mid;
        mid = temp;
    }
    if (low > high) {
        temp = low;
        low = high;
        high = temp;
    }
    if (mid > high) {
        temp = mid;
        mid = high;
        high = temp;
    }

    print(low, mid, high);
    printString("\n");
    
    count = count - 1;
}
