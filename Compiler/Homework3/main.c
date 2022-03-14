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

// Creat a main function to help run
// the programs together and test
// input files.
int main(int argc, char *argv[]) {

    // Create a new symbol table (assign
    // the global variable) to begin testing.
    // The size value can change.
    table = createSymTab(17);

    // Check if there are any files that
    // can be opened. If not, print out
    // message indicating file open failure.
    // --> MAYBE THAT MEANS THAT THE FILE SHOULD BE CALLED "listing" FILE???
    if(!openFiles(argv[1], "listing")) {
        
        // Print file opening failure 
        // message and exit.
        printf("open failed\n");
        exit(0);
    }

    // Call the parsing function.
    yyparse();
}
