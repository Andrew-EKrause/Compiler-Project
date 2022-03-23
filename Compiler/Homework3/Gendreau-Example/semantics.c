#include <stdio.h>
#include <stdlib.h>
#include "SymTab.h"
#include "IOMngr.h"
#include "semantics.h"

extern struct SymTab *table;

void printSymTab() {
    int hasMore = startIterator((SymTab (*))table);
    //printf("Val of hasMore: %d\n", hasMore); // --> DEBUGGING STATEMENT
    printf("%20s\t%10s\n", "Variable", "Value");
    while(hasMore) {
        // printf("In hasMore while loop\n"); // --> DEBUGGING STATEMENT
        printf("%20s\t%10s\n", getCurrentName((SymTab (*))table), getCurrentAttr((SymTab (*))table) ? "true" : "false");
        // printSymbolTable(table); // --> DEBUGGING STATEMENT  
        // printf("Val of hasMore in loop: %d\n", hasMore); // --> DEBUGGING STATEMENT

        hasMore = nextEntry((SymTab (*))table);
        // printf("Val of hasMore in loop: %d\n", hasMore); // --> DEBUGGING STATEMENT
    }
    printSymbolTable((SymTab (*))table); // --> DEBUGGING STATEMENT
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
