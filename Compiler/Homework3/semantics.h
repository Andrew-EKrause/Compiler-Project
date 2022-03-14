/*
    The semantics.h file contains function
    signatures for the functions that are 
    implemented in the semantics.c file. 
    The functions utilized in the semantics
    files interact with the SymTab files as
    well as the IOMngr files.
*/
#include <string.h> // --> MAY NOT NEED
#include <ctype.h> // --> MAY NOT NEED
#include "SymTab.h"

/*
    Function prints out the symbol table.
*/
extern void printSymTab();

/*
    Function stores a set in a variable name.
*/
extern void storeVar(char *name, SymTab *set);

/*
    Function returns the set (symbol table)
    that a set literal (char) is in.
*/
extern SymTab* getValue(char *name);

/*
    Function performs a union of two sets (symbol tables).
*/
extern SymTab* doUNION(SymTab *set1, SymTab *set2);

/*
    Function performs an intersection of two sets (symbol tables).
*/
extern SymTab* doINTERSECT(SymTab *set1, SymTab *set2);

/*
    Function creates a new set (symbol table)
    from the set literal (char) that is passed 
    in as a parameter.
*/
extern SymTab* makeSet(char *name);
