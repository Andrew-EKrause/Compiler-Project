#include <stdio.h>
#include <stddef.h>
#include "IOMngr.h"

int main(){

    // TEST 1
    if(openFiles("sample_source.txt", "test_listing.txt")){

        while(getNextSourceChar() != EOF){

        }

        closeFiles();

        printf("Test 1 Done.\n");
    } else {
        printf("Test 1 Skipped.\n");
    }


    // TEST 2
    if(openFiles("sample_source.txt", NULL)){

        while(getNextSourceChar() != EOF){

        }

        closeFiles();

        printf("Test 2 done.\n");
    } else {
        printf("Test 2 skipped.\n");
    }

    // TEST 3
    if(openFiles("sample_source.txt", "test_listing.txt")){

        char c = getNextSourceChar();
        while(c != EOF){
            // printf("source char: %c\n", c); // --> TEST PRINT STATMENT
            if(c == 'p'){
                // printf("p char: %c\n", c); // --> TEST PRINT STATEMENT
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
