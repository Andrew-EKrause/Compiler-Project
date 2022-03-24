#include <stdio.h>
#include <stdlib.h>
#include "SymTab.h"
#include "IOMngr.h"
#include "semantics.h"

void printSymbolTable(SymTab *table);
extern struct SymTab *table;

void printSymTab() {
    int hasMore = startIterator((SymTab (*))table);
    // Print out the first variable and value in the table.
    printf("\n%30s\n", "============");
    printf("%28s\n", "Output:");
    printf("%30s\n\n", "============");
    printf("%20s\t%10s\n", "Variable", "Value");
    while(hasMore) {
        printf("%20s\t%10s\n", getCurrentName((SymTab (*))table), getCurrentAttr((SymTab (*))table) ? "true" : "false");
        hasMore = nextEntry((SymTab (*))table);
    }
    printf("\n");
    // printSymbolTable((SymTab (*))table); // --> EXTRA PRINT STATEMENT
}

void storeVar(char *name, bool v) {
    enterName((SymTab (*))table, name);
    setCurrentAttr((SymTab (*))table, (void*)v);
}

bool getVal(char *name) {
    if(enterName((SymTab (*))table, name)) {
        writeIndicator(getCurrentColumnNum());
        writeMessage("Initialize variable to false.");
        setCurrentAttr((SymTab (*))table, (void*)false);
    }
    return (bool) getCurrentAttr((SymTab (*))table);
}

bool doOR(bool v1, bool v2) {
    return v1 || v2;
}

bool doAND(bool v1, bool v2) {
    return v1 && v2;
}

bool doNOT(bool v1) {
    return !v1;
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
