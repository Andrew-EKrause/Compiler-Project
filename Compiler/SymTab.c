/**
 * DESCRIPTION...
 * 
 * @file SymTab.c
 * @author Andrew Krause
 * @version 0.1
 * @date 2022-01-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// Include the standard I/O library,
// a second C library of functions,
// and the  SymTab.h file.
#include <stdio.h>
#include <stdlib.h>
#include "SymTab.h"

/**
 * The function creates a new Symbol table by allocating
 * space for the data structure, initializing the various
 * attributes of the table, and setting all values to NULL
 * at the start.
 */
SymTab *createSymTab(int size) {

    // Create space in memory for the symbol table.
    SymTab *symbolTable = malloc(sizeof(SymTab));
    
    // Set the attributes of the symbol table. The attributes
    // include the table size and the table contents. 
    // Create space in memory for the symbol table contents.
    symbolTable->size = size;
    symbolTable->contents = malloc(sizeof(SymEntry*) * symbolTable->size);

    // Create a for loop to set all of the entries in the symbol
    // table to NULL. The entries are encompassed in the 
    // contents attribute, which is an array of lists.
    int i;
    for(i = 0; i < symbolTable->size; i++) {

        // Set each content item to NULL.
        symbolTable->contents[i] = NULL;
    }

    // Set the current attribute to NULL.
    symbolTable->current = NULL;

    // Return the pointer to the new symbol table.
    return symbolTable;
}

/**
 * The function destroys the Symbol table by setting
 * the various attributes of the table to NULL as well
 * as by freeing all of the data attributes.
 */
void destroySymTab(SymTab *table) {

    // Create temporary variables to help free the 
    // different data attributes in the symbol table.
    SymEntry *currentSlot = NULL;
    SymEntry *nextEntryPoint = NULL;
    SymEntry *specificEntry = NULL;

    // Create a for loop to visit each entry in the
    // array of linked lists and free the data in order
    // to remove the Symbol Table and restore memory.
    int i;
    for(i = 0; i < table->size; i++) {

        // Set the currentSlot variable equal to a given 
        // slot in the symbol table. This process obtains
        // each linked list in each array slot of the symbol
        // table.
        currentSlot = table->contents[i];

        // The second variable is used to traverse each 
        // linked list in each the symbol table entry.
        specificEntry = currentSlot;

        // Until the end of the linked list is reached,
        // free each entry/node/SymEntry of the linked
        // list.
        while(specificEntry != NULL) {

            // Set one of the temp variables to the 
            // next node/entry in the linked list.
            nextEntryPoint = specificEntry->next;

            // Free the specific features of the
            // given SymEntry before freeing that
            // SymEntry itself.
            // --> CHECK LATER!!!
            free(specificEntry->name);
            free(specificEntry->attribute);
            free(specificEntry);

            // Set the specificEntry temp variable equal
            // to the other temp variable that was assigned
            // first in the while loop to continue the 
            // process of freeing memory. 
            specificEntry = nextEntryPoint;
        }

        // Make sure that the rest of the table
        // and any lingering data is destroyed.
        // --> CHECK LATER!!!
        free(nextEntryPoint);
        free(specificEntry);
        free(table->contents);
        free(table->current);
        free(table);
    }
}

/**
 * DESCRIPTION...
 */
// --> DELETE LATER --> NEED TO COMPLETE THE findName FUNCTION FIRST!!!
int enterName(SymTab *table, char *name) {

}
/*
    if name is not in the symbol table, a copy of name is added to the symbol table
    with a NULL attribute, set current to reference the new (name, attribute) pair
    and return 1
    if name is in the symbol table, set current to reference the (name, attribute)
    pair and return 0
*/

/**
 * DESCRIPTION...
 */
// --> DELETE LATER --> NEED TO COMPLETE THE findName FUNCTION FIRST!!!
int findName(SymTab *table, char *name) {

}
/*
    if name is in the symbol table, set current to reference the (name, attribute)
    pair and return 1
    otherwise do not change current and return 0
*/