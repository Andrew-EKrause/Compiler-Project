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
    symbolTable->contents = malloc(sizeof(SymEntry *) * symbolTable->size);

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