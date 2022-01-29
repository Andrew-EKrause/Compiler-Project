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
// --> SEE IF THERE IS A MORE SIMPLE WAY TO DO THIS!!!
SymTab *createSymTab(int size) {

    // Create space in memory for the symbol table.
    SymTab *symbolTable = malloc(sizeof(SymTab));
    
    // Set the attributes of the symbol table. The attributes
    // include the table size and the table contents. 
    // Create space in memory for the symbol table contents.
    symbolTable->size = size;
    symbolTable->contents = malloc(sizeof(SymEntry*) * symbolTable->size); // MAY NEED TO ADD +1 FOR CURRENT

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
// --> SEE IF THERE IS A MORE SIMPLE WAY TO DO THIS!!!
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
 * The function inserts a new name into the symbol
 * table. If name is not in the symbol table, a copy 
 * of name is added to the symbol table with a NULL 
 * attribute, set current to reference the new (name, attribute) 
 * pair and return 1 if name is in the symbol table, 
 * set current to reference the (name, attribute) pair 
 * and return 0.
 */
// --> COMPLETE LATER!!!
int enterName(SymTab *table, char *name) {

    // If the name is not already in the symbol table,
    // make a copy of the name and add it to the
    // symbol table.
    if(findName(table, name) == 0) {

    } else {

        // If the name is already in the symbol table,
        // set current to reference the name attribute
        // pair and return 0.
        return 0;
    }
}

/**
 * If the name is in the symbol table, set current
 * to reference the (name, attribute) pair and return
 * 1. Otherwise, do not change current and return 0.
 */
int findName(SymTab *table, char *name) {

    // Create temporary variables to help
    // determine if the name is in the table.
    SymEntry *currentSlot = NULL;
    SymEntry *nextEntryPoint = NULL;
    SymEntry *specificEntry = NULL;

    // Create a for loop to visit each entry in the
    // array of linked lists and determine if the 
    // name is in the symbol table.
    int i;
    for(i = 0; i < table->size; i++) {

        // Move through each slot in the symbol table.
        currentSlot = table->contents[i]; 
        specificEntry = currentSlot; // --> SEE IF THIS VARIABLE NAME IS NECESSARY!!!

        // In any given row of the symbol, traverse  
        // until last entry is reached.
        while(specificEntry != NULL) {

            // If the name in the symbol table is found,
            // set current to reference the (name, attribute) 
            // pair and return 1.
            if(strcmp(specificEntry->name, name) == 0) {

                table->current = specificEntry;
                return 1;
            }

            // Move to the next entry in any 
            // given row of the symbole table.
            nextEntryPoint = specificEntry->next;
            specificEntry = nextEntryPoint;
        }
    }

    // If the name is not in the symbol table, 
    // do not change anything and return 0.
    return 0;
}

/**
 * The function checks if the current attribute of 
 * the Symbol Table references a name. If current
 * references a name, return 1. Otherwise, return 0.
 */
int hasCurrent(SymTab *table) {

    // If current references a name, indicating 
    // that it is not NULL, return 1. Otherwise,
    // return 0.
    if(table->current != NULL) {
        return 1;
    }
    return 0;
}

/**
 * The function sets the current attribute
 * in the symbol table to the specified
 * parameter attribute.
 */
void setCurrentAttr(SymTab *table, void * attr) {

    // PRE: hashCurrent() == 1
    // change the attribute value of the 
    // current (name, attribute) pair to attr
    table->current->attribute = attr;
}

/**
 * The function gets the current attribute
 * in the symbol table. 
 */
void * getCurrentAttr(SymTab *table) {

    // PRE: hasCurrent() == 1
    // return the attribute in the 
    // current (name, attribute) pair
    table->current->attribute;
}

/**
 * The function gets the name of the
 * current (name, attribute) pair in 
 * the symbol table. The value is 
 * returned from the function,
 */
char * getCurrentName(SymTab *table) {

    // PRE: hasCurrent() == 1
    // return the name in the 
    // current (name, attribute) pair
    return table->current->name;
}

/**
 * The function sets current to the "first" (name, attribute)
 * pair in the symbol table and return 1. Otherwise, if the
 * table is empty, return 0.
 */
int startIterator(SymTab *table) {

    // Create variables to help search through
    // the symbol table and set current.
    int i;
    SymEntry *currentSlot = NULL;

    // Loop through all the slots in the symbol table
    // until you find the "first" (name, attribute) pair.
    for(i = 0; i < table->size; i++) {

        // Set the temp variable equal to
        // each slot in the symbol table.
        currentSlot = table->contents[i];

        // If the slot is not NULL, then set values.
        if(currentSlot != NULL) {

            // Set current equal to the "first" name
            // attribute pair in the table and return 1.
            table->current = currentSlot;
            return 1;
        }
    }

    // If the table is empty, return 0.
    return 0;
}




int nextEntry(SymTab *table) {

}
/*
    if all (name, attribute) pairs have been visited since the last call to
    startIterator, return 0
    otherwise set current to the "next" (name, attribute) pair and return 1
*/
