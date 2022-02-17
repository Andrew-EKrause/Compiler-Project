/**
 * The file contains functions needed to create 
 * and interact with a Symbol Table data structure.
 * The different attributes within the file include
 * functions for creating the Symbol Table, destroying
 * it, adding a new name to the table, finding a name
 * in the table. Besides the functions listed above,
 * and others not listed that help maintain the 
 * Symbol Table, a function for creating a new hash
 * value is also included in the file.
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
#include <string.h>
#include "SymTab.h"

// Define functions not specified in the .h file here (internal functions). --> ASK QUINN!!!
// int createHashValue(int tableSize, char *name);
// void printSymbolTable(SymTab *table);

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
 * as freeing all of the data attributes.
 */
void destroySymTab(SymTab *table) {

    // Create temporary variables to help free the 
    // different data attributes in the symbol table.
    SymEntry *currentSlot = NULL;
    SymEntry *nextEntryPoint = NULL;

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

        // Until the end of the linked list is reached,
        // free each entry/node/SymEntry of the linked
        // list.
        while(currentSlot != NULL) {

            // Set one of the temp variables to the 
            // next node/entry in the linked list.
            nextEntryPoint = currentSlot->next;

            // Free the specific features of the
            // given SymEntry before freeing that
            // SymEntry itself.
            // free(currentSlot->attribute); // --> KEEP AN EYE ON THIS!!!
            free(currentSlot->name);
            free(currentSlot);

            // Set the specificEntry temp variable equal
            // to the other temp variable that was assigned
            // first in the while loop to continue the 
            // process of freeing memory. 
            currentSlot = nextEntryPoint;
        }
    }

    // Make sure that the rest of the table
    // and any lingering data is destroyed.
    free(table->contents); 
    free(table); 
}

/**
 * The function inserts a new name into the symbol
 * table. If name is not in the symbol table, a copy 
 * of name is added to the symbol table with a NULL 
 * attribute, and current is set to reference the new 
 * (name, attribute) pair and return 1. If name is in 
 * the symbol table, set current to reference the 
 * (name, attribute) pair and return 0.
 * 
 * The way I wrote this function, entries with the
 * same hash value are inserted before the other 
 * entries.
 */
int enterName(SymTab *table, char *name) {

    // If the name is not already in the symbol table,
    // make a copy of the name and add it to the
    // symbol table.
    if(findName(table, name) == 0) {

        // Determine where to insert the new name in the table.
        int newHashValue = createHashValue(table->size, name);
        
        // Create space in memory for the new entry.
        SymEntry *newEntry = malloc(sizeof(SymEntry));

        // Create space in memory for the name of the entry and 
        // create a copy of the name to add it to the symbol table.
        newEntry->name = strdup(name);

        // Set the new entry attribute to NULL.
        newEntry->attribute = NULL;

        // SET THE NEXT FIELD AT ALL HERE??? I THINK SO --> 
        // Given that the new entry is always inserted at the start of the
        // slot in the hash table, need to set its next to reference 
        // all entries that may already exists in that slot.
        newEntry->next = table->contents[newHashValue];

        // Store the new entry in the symbol table at the hashed
        // location and set current to be the new entry value.
        table->contents[newHashValue] = newEntry;
        table->current = newEntry;
        
        // After adding the new entry 
        // to the symbol table, return 1.
        return 1;

    } else {

        // --> SET CURRENT TO REFERENCE THE (NAME, ATTRIBUTE) PAIR???

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

    // Obtain the hash value for the name being searched
    // for in order to get to the right slot in the table.
    int hashValue = createHashValue(table->size, name);

    // Move through each slot in the symbol table.
    currentSlot = table->contents[hashValue]; 

    // In any given row of the symbol, traverse  
    // until last entry is reached.
    while(currentSlot != NULL) {

        // If the name in the symbol table is found,
        // set current to reference the (name, attribute) 
        // pair and return 1.
        if(strcmp(currentSlot->name, name) == 0) {

            table->current = currentSlot;
            return 1;
        }

        // Move to the next entry in any 
        // given row of the symbole table.
        nextEntryPoint = currentSlot->next;
        currentSlot = nextEntryPoint;
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
void setCurrentAttr(SymTab *table, void *attr) {

    // PRE: hashCurrent() == 1
    // change the attribute value of the 
    // current (name, attribute) pair to attr
    table->current->attribute = attr;
}

/**
 * The function gets the current attribute
 * in the symbol table.  The value is
 * returned from the function.
 */
void *getCurrentAttr(SymTab *table) {

    // PRE: hasCurrent() == 1
    // return the attribute in the 
    // current (name, attribute) pair
    return table->current->attribute;
}

/**
 * The function gets the name of the
 * current (name, attribute) pair in 
 * the symbol table. The value is 
 * returned from the function,
 */
char *getCurrentName(SymTab *table) {

    // PRE: hasCurrent() == 1
    // return the name in the 
    // current (name, attribute) pair
    return table->current->name;
}

/**
 * The function sets current to the "first" (name, attribute)
 * pair in the symbol table and returns 1. Otherwise, if the
 * table is empty, it returns 0.
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

/*
    If all (name, attribute) pairs have been visited since the last call to
    startIterator, return 0. Otherwise, set current to the "next" (name, attribute) 
    pair and return 1.
*/
int nextEntry(SymTab *table) {

    // First check if current is NULL, which indicates
    // that all (name, attribute) pairs have been visited
    // since the last call or the table is empty.
    if(table->current == NULL) {

        // Did not move to any next entry.
        return 0;
    }

    // Get the hash value of the current attribute in the symbol table.
    int hashValue = createHashValue(table->size, table->current->name);

    // If the hash value is the table size - 1, that means that the
    // current (name, attribute) pair is located in the last slot
    // of the symbol table. Therefore, you need to check it.
    if(hashValue == table->size - 1) {

        // Create temporary variables to traverse 
        // through the entries in the given slot.
        SymEntry *currentEntry = table->contents[hashValue];
        SymEntry *nextEntry;

        // While there are still entries in the slot,
        // move through each entry in the given slot.
        while(currentEntry != NULL) {

            // Move to the next entry in the slot.
            nextEntry = currentEntry;
            currentEntry = currentEntry->next;
        }

        // When you get to the end of the entries in 
        // the given slot, check if there are no other
        // entries after the current entry in the slot.
        if(nextEntry != NULL && (strcmp(nextEntry->name, table->current->name) == 0)) {

            // If the conditional is met, there are
            // no other next entries in the table.
            return 0;
        }
    }

    // If the current entry in the table has a next reference,
    // move to that next reference, which is the next entry.
    if(table->current->next == NULL) {

        // Move to the next slot in the table.
        hashValue += 1;

        // While the given slot in the table is NULL,
        // move to the next slot in the symbol table.
        while(table->contents[hashValue] == NULL) {

            // Move to the next slot in the symbol table.
            hashValue += 1;

            // If there are no other slots to visit
            // in the symbol table, return 0.
            if(hashValue == (table->size - 1)) {
                
                // No other next entry.
                return 0;
            }
        }

        // Set the next entry equal to the first entry 
        // in the next open, non-NULL slot in the table.
        table->current = table->contents[hashValue];
    } else {

        // Otherwise, if the current entry in the table has a next 
        // reference, move to that next reference, which is the next 
        // entry.
        table->current = table->current->next;
    }

    // Return 1 to indicate a move to the next entry.
    return 1;
}

/**
 * The function returns a hash value that is used
 * to determine which slot in the symbol table any
 * given entry is inserted in. The hash function is
 * generated by first summing the ASCII values of  
 * each character in the name being processed in the 
 * fucntion. Next, that obtained sum is modded by 
 * the current size of the symbol table to produce
 * the hash value. This function is used in the
 * enterName() function.
 */
int createHashValue(int tableSize, char *name) {

    // Create a counter variable 
    // and a hash value variable.
    int i;
    int hashVal = 0;

    // Sum the ASCII character values of 
    // the name variable up to obtain part 
    // of the hash value.
    for(i = 0; i < strlen(name); i++) {

        // Sum up ASCII values.
        hashVal += name[i];
    }

    // Mod the obtained sum of characters
    // to get the final hash value.
    hashVal %= tableSize;

    // Return the hash value from the function.
    return hashVal;
}

/**
 * The function prints out any symbol
 * table passed into it onto the terminal
 * screen.
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
