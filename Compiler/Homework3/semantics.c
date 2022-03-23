/**
 * The semantics.c file utilizes the Symbol Table 
 * that was created before this file to interpret
 * programs using the grammar that was specified 
 * through the lex and yacc files. The grammar that
 * is being interpreted involves applying simple 
 * operations on sets of values such as union and
 * intersection operations. The functions in the
 * semantics file help complete various operations
 * that were specified in the grammar as well as
 * interact with other attributes of the programs
 * passed through this file.
 * 
 * @file semantics.c
 * @author Andrew Krause
 * @version 0.1
 * @date 2022-03-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// Include the standard I/O library,
// a second C library of functions,
// the IOMngr.h source file, and
// the semantics.h file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IOMngr.h"
#include "semantics.h"

// Create a global symbol table to be used
// throughout the semantics.c file program.
extern struct SymTab *table;

/**
 * The function prints out the symbol table
 * that is created in the program to store
 * values from the test files.
 */
void printSymTab() {

    // Create a variable to start printing
    // values in the table.
    int hasMore = startIterator((SymTab (*))table);

    // Print out the first variable and value in the table.
    printf("Output:\n\n");

    // While there is another value in the symbol table,
    // print out the values in the symbol table.
    while(hasMore) {

        // Print out the the current value in the symbol 
        // table and move to the next entry in the table. 
        // Call a separate print function to print out each
        // attribute (set/symbol table) for each value.
        printf("%s: ", getCurrentName((SymTab (*))table));
        printSetAttribute(getCurrentAttr((SymTab (*))table));
        printf("\n");
        hasMore = nextEntry((SymTab (*))table);
    }
    printSymbolTable(table); // --> DEBUGGING STATEMENT; REMOVE LATER!!!
}

/**
 * The function prints out each attribute for each
 * value in the symbol table that is printed out by
 * the function above. Each attribute is a set or 
 * symbol table. Therefore, braces and commas are
 * printed out in this function to help represent
 * the set.
 */
void printSetAttribute(SymTab *printSet) {

    // Print out the opening brace.
    printf("{");

    // Create a variable to start printing 
    // values in the table.
    int nextSetVal = startIterator(printSet);

    // While there is another value in the set/symbol
    // table, print out the values in that set/symbol table.
    while(nextSetVal) {

        // Print out the the current value in set/symbol
        // table and move to the next entry in the table.
        printf("%s", getCurrentName(printSet));
        nextSetVal = nextEntry(printSet);

        // If there is a next entry in the set/table
        // print out a comma to separate the values.
        if(nextSetVal) {
            printf(",");
        }
    }

    // Print out the closing brace.
    printf("}");
}

/**
 * The function stores a variable name
 * in the symbol table and sets the value
 * of that variable (what the variable is
 * equal to) to the current attribute in
 * the table.
 */
void storeVar(char *name, SymTab *set) {

    // Store the variable name in the table
    // and set the current attribute.
    enterName((SymTab (*))table, name);
    setCurrentAttr((SymTab (*))table, (void*)set);
}

/**
 * The function obtains the value
 * (in the form of a set) of the 
 * specified variable name from the
 * global symbol table in the program.
 */
SymTab* getVal(char *name) {

    // Check if the variable name is not 
    // existent in the symbol table. 
    if(enterName((SymTab (*))table, name)) {

        // If the name is not already in the table,
        // set the current attribute to an empty set
        // (NULL) and write out some messages.
        writeIndicator(getCurrentColumnNum());
        writeMessage("Initialize variable to empty");
        setCurrentAttr((SymTab (*))table, (void*)NULL);
    }

    // Return the current attribute in the table
    // (this is the set assigned to a value).
    return (SymTab*) getCurrentAttr((SymTab (*))table);
}

/**
 * The function unions two sets (symbol tables)
 * and combines the result in a new set (symbol
 * table) that is returned as a new symbol table.
 */
SymTab* doUNION(SymTab *set1, SymTab *set2) {

    // Create a new symbol table (set) to store
    // the union of the two sets that are passed
    // in as parameters.
    SymTab* unionSymTab = createSymTab(17);
    
    // If either of the sets/symbol tables are not NULL,
    // then peform a union of the two sets/symbol tables.
    if(set1 || set2) {

        // Create an integer value for the start iterator function.
        // This is for the first set.
        int moveSet1 = startIterator(set1);
        int entryUnionSymTab1;

        // While there is a next entry in the symbol table, 
        // add the value in the first symbol table to the
        // union symbol table. 
        while(moveSet1) {
            
            // Enter the name of the first set into the union symbol table.
            // Then move to the next entry in the first set.
            entryUnionSymTab1 = enterName(unionSymTab, getCurrentName(set1));
            moveSet1 = nextEntry(set1);
        }

        // Create an integer value for the start iterator function.
        // This is for the second set.
        int moveSet2 = startIterator(set2);
        int entryUnionSymTab2;

        // While there is a next entry in the symbol table, 
        // add the value in the second symbol table to the
        // union symbol table. 
        while(moveSet2) {
            
            // Enter the name of the second set into the union symbol table.
            // Then move to the next entry in the second set.
            entryUnionSymTab2 = enterName(unionSymTab, getCurrentName(set2)); 
            moveSet2 = nextEntry(set2);
        }
    }

    // Return the set/symbol table that contains
    // the union of set 1 and set 2 (symbol tables).
    return unionSymTab;
}

/**
 * The function performs the intersection of two 
 * sets (symbol tables) and combines the result
 * in a new set that is returned as a new symbol
 * table.
 */
SymTab* doINTERSECT(SymTab *set1, SymTab *set2) {

    // Create a new symbol table (set) to store
    // the intersection of the two sets that are passed
    // in as parameters.
    SymTab* intersectSymTab = createSymTab(17);

    // If either of the sets/symbol tables are NULL,
    // return the empty set/symbol table. 
    if(set1 && set2) {

        // Create an integer value for the start iterator function.
        // This is for the first set, which is used to intersect with
        // the second set.
        int moveIntersect = startIterator(set1);
        int entryIntersectTabs;

        // While there is a next entry in the symbol table, 
        // add the value in the first symbol table to the
        // union symbol table. 
        while(moveIntersect) {
            
            // Check if the first name in the first set/symbol table
            // is in the second set/symbol table.
            if(findName(set2, getCurrentName(set1))) {

                // If the value in the first set is also in the second set, 
                // enter that value into the symbol table.
                entryIntersectTabs = enterName(intersectSymTab, getCurrentName(set1));
            }

            // Move to the next entry in the first set.
            moveIntersect = nextEntry(set1);
        }
    }

    // Return the set/symbol table that contains the
    // intersection of set 1 and set 2 (symbol tables).
    return intersectSymTab;
}

/**
 * The function creates a new set (symbol
 * table) from the set literal (char*) that
 * is passed in as a parameter.
 */
SymTab* makeSet(char *name) {
    
    // Create a new symbol table in which
    // the set literal will be stored.
    SymTab* newSet = createSymTab(17);

    // Create an integer to detect how the
    // set literal was inserted into the table.
    int entry = 0;

    // If the value of the set literal is empty, "",
    // then create an empty set. Otherwise, add
    // the set literal to the symbol table.
    if(!(strlen(name) == 0)) {

        // Loop through the set literal, which may
        // be a comma delimited list of letters, and
        // store the letters in the symbol table.
        int i;
        for(i = 0; i < strlen(name); i++) {

            // If a given character in the set literal is not
            // a comma, or brace, store it in the symbol table.
            if(name[i] != '{' && name[i] != ',' && name[i] != '}') {

                // Enter the given part of the string literal
                // into the new symbol table (set).
                entry = enterName(newSet, &name[i]);
            }
        }
    }

    // Return the new symbol table or set
    // from the function
    return newSet;
}
