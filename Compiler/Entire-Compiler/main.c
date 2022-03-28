/**
 * The file contains a single function that
 * is used to begin the process of running
 * the compiler. The function in this file
 * is the starting point for the compiling
 * process. The function writes the MIPS
 * assembly code that will be generated 
 * through the compilation process out to 
 * a file that can then be run in an 
 * environment such as Mars.
 * 
 * @file main.c
 * @author Andrew Krause
 * @version 0.1
 * @date 2022-04-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// Include the standard I/O library,
// the SymTab.h API, and the IOMngr.h
// API.
#include <stdio.h>
#include "SymTab.h"
#include "IOMngr.h"

// Include the yyparse() function
// as an external function. Also
// include the destroy lex function.
extern int yyparse();
extern int yylex_destroy();

// Create a global variable of 
// type symbol table to store
// the values of variables 
// throughout the compilation
// process.
SymTab *table;

// SymTab *ProcSymTab;
// struct SymEntry *entry;
// int inProc = 0;

// Create a global file variable to
// place the assembly code generated
// by the compiler in.
FILE *aFile;

/**
 * The main function creates a symbol table
 * as a type of memory for the values of 
 * variables. The function then opens a 
 * file containing the C-like language.
 * Afterwards, the main function opens a
 * listing file (assuming there is one).
 * Lastly, the yyparse() function is called
 * to begin the compilation process.
 */
int main(int argc, char * argv[]) {
	
	// Create a symbol table to store the
	// values of variables throughout the
	// process of running the program.
	table = createSymTab(33);

	// Call the function to open the 
	// appropriate files for the compilation
	// process.
	openFiles(argv[1], argv[2]);
	
	// If there are a certain number of
	// arguments, that indicates a listing
	// file is in use. Otherwise, print
	// the results out to stdout.
	if (argc == 4) 
		aFile = fopen(argv[3], "w");
	else
		aFile = stdout;

	// Call the yyparse() function to
	// begin the compiling process.
	yyparse();

	// Close all the files at the end of the program
    // and call yylex_destroy() to free up memory.
    closeFiles();
    yylex_destroy();
}
