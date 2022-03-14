
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IOMngr.h"

int main() {

    // TEST 1
    if(openFiles("testSourceFile.txt", "testListingFile.txt")) {

        while(getNextSourceChar() != EOF) {

        }

        closeFiles();

        printf("Test 1 Done.\n");
    } else {
        printf("Test 1 Skipped.\n");
    }

    // TEST 2
    if(openFiles("testSourceFile.txt", NULL)) {

        while(getNextSourceChar() != EOF) {

        }

        closeFiles();

        printf("Test 2 done.\n");
    } else {
        printf("Test 2 skipped.\n");
    }

    // TEST 3
    if(openFiles("testSourceFile.txt", "testListingFile.txt")) { // Test with listing file and NULL: "testListingFile.txt" | NULL
        char c = getNextSourceChar();
        while(c != EOF) {
            if(c == 'p') {
                int current_column_number = getCurrentColumnNum();
                printf("current column: %d\n", current_column_number);
                writeIndicator(current_column_number);
                writeMessage("Here is a p!");
            }
            c = getNextSourceChar();
        }

        closeFiles();

        printf("Test 3 done.\n");
    }
    else {
        printf("Test 3 skipped\n");
    }
}
