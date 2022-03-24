/**
 * The main.c file is used for running the 
 * SymTab.c and IOMngr.c files for the homework
 * 3 grammar. The main function contains a simple
 * check that determines if the listing file does
 * not exist. If the listing file does exist,
 * then the yyparse() function is called. If the
 * listing file does not exist, an error message 
 * is printed to the standard output.
 * 
 * @file main.c
 * @author Andrew Krause
 * @version 0.1
 * @date 2022-03-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// Include the standard libraries
// as well as the SymTab.h and
// IOMngr.h files.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SymTab.h"
#include "IOMngr.h"

// Include the parse function.
extern int yyparse();

// Create a global symbol table.
SymTab *table;

// Create an additional symbol table
// in order to ensure that memory
// is freed properly at the conclusion
// of the program.
SymTab *allTables;
int countTables = 0;

// Include function definitions.
void freeAllTables(SymTab *freeTable);
void printSymbolTable(SymTab *table);

// Creat a main function to help run
// the programs together and test
// input files.
int main(int argc, char *argv[]) {

    // Create a new symbol table (assign
    // the global variable) to begin testing.
    // The size value can change.
    table = createSymTab(17);

    // Create a symbol table to store the
    // references to the other symbol tables
    // that are created throughout the program.
    allTables = createSymTab(17);

    // Check if there are any files that
    // can be opened. If not, print out
    // message indicating file open failure.
    // Results are printed out to a file that
    // is created by the program called 
    // "listing".
    if(!openFiles(argv[1], "listing")) {
        
        // Print file opening failure 
        // message and exit.
        printf("open failed\n");
        exit(0);
    }

    // Call the parsing function.
    yyparse();

    // Print out the main table in the program.
    //
    // NOTE: This is used only for debugging 
    // purposes and should not be included in 
    // regular output.
    // printSymbolTable(table); // --> EXTRA PRINT CHECK.

    // Free all the tables at the conclusion
    // of the program.
    freeAllTables(allTables);
}

/**
 * The function frees all of the memory stored in
 * the symbol tables that were used and created in
 * the program. Throughout the execution of the 
 * program, the symbol tables created are stored 
 * in a large symbol table. The large symbol table
 * is then processed in this function to destroy
 * its contents, which are the other symbol tables.
 */
void freeAllTables(SymTab *freeTables) {

    // Create a variable for iterating through
    // the symbol table that tracks all the other
    // symbol tables.
    int hasMore = startIterator(freeTables);

    // While there are other entries in the symbol
    // table, continue to iterate through and destroy
    // the tables.
    while(hasMore) {

        // Destory a given symbol table through the destroy
        // function, set the current attribute to NULL, and 
        // move to the next entry (the next symbol table).
        destroySymTab((SymTab*)getCurrentAttr(freeTables));
        setCurrentAttr(freeTables, NULL);
        hasMore = nextEntry(freeTables);
    }

    // Destroy the symbol table that tracked all the 
    // other symbol tables in order to free up memory.
    destroySymTab(freeTables);
}

/**
 * The function prints out any symbol
 * table passed into it onto the terminal
 * screen. 
 * 
 * IMPORTANT: This function will usually
 * need to be placed in test files as a
 * separate function.
 */
void printSymbolTable(SymTab *table) {

    // Create a title for the symbol table.
    printf("==========================\n");
    printf("   Symbol Table Printed\n");
    printf("==========================\n\n");

    // Create temporary variables to help
    // determine if the name is in the table.
    SymEntry *currentSlot = NULL;
    SymEntry *nextEntryPoint = NULL;

    // Create a counter variable for the for loop.
    // Create a variable for printing out first arrow.
    int i;
    int firstArrow ;

    // Create a for loop to visit each entry in the
    // array of linked lists and determine if the 
    // name is in the symbol table.
    for(i = 0; i < table->size; i++) {

        // Move through each slot in the symbol table.
        // Print out the row number. Set the first arrow
        // variable to one on each iteration.
        currentSlot = table->contents[i]; 
        printf("Row %d: ", i);
        firstArrow = 1;

        // In any given row of the symbol, traverse  
        // until last entry is reached.
        while(currentSlot != NULL) {

            // Add the first arrow to each non-empty slot.
            if(firstArrow == 1) {
                printf("--> ");
                firstArrow = 0;
            }

            // Move to the next entry in any 
            // given row of the symbole table.
            nextEntryPoint = currentSlot->next;

            // Print the given entry name.
            // Then move to the next entry.
            printf("%s ", currentSlot->name);
            currentSlot = nextEntryPoint;

            // If the next entry is not NULL,
            // print out an arrow between entries. 
            if(currentSlot != NULL) {
                printf("--> ");
            }
        }
        // Print out an extra space.
        printf("\n");
    }

    // Print a final space between the 
    // table and the other content.
    printf("\n==========================\n\n");
}
