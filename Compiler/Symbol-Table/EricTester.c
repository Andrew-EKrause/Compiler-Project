#include "SymTab.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Test {
    char * name;
    int value;
} Test;

int main(int argc, char** argv) {
    char* name;
    int i, j;
    SymTab* table;

    table = createSymTab(10);

    printf("-----Pre-Test for hasCurrent Function-----\n\n");
    printf("Output: %d\n", hasCurrent(table));
    printf("Expected 0\n\n"); 

    printf("-----Adding Names-----\n"); 

    enterName(table, "hello");
    enterName(table, "world");
    enterName(table, "Shepard Pie");
    enterName(table, "Dog");
    enterName(table, "mouse");

    printf("-----Names added-----\n\n"); 

    printf("-----Test Find Name Functions-----\n\n"); 


    printf("Output: %d\n", findName(table, "hello"));
    printf("Expected: 1\n\n");

    printf("Output: %s\n", getCurrentName(table));
    printf("Expected: hello\n\n");
    
    printf("Output: %d\n", findName(table, ""));
    printf("Expected: 0\n\n");

    printf("Output: %s\n", getCurrentName(table));
    printf("Expected: hello\n\n");

    printf("Output: %d\n", findName(table, "Dog"));
    printf("Expected: 1\n\n");

    printf("Output: %s\n", getCurrentName(table));
    printf("Expected: Dog\n\n");

    printf("-----Testing setCurrentAttr-----\n\n");

    name = "Hello World";
    Test* test = (struct Test*)malloc(sizeof(struct Test));
    test->name = (char*)malloc(strlen(name) + 1);
    strcpy(test->name, name);
    test->value = 1;

    setCurrentAttr(table, test);

    printf("-----Current Attr set-----\n\n");

    printf("-----Testing getCurrentAttr-----\n\n");

    test = getCurrentAttr(table);
    printf("Output: %d\n", test->value);
    printf("Expected: 1\n\n");

    printf("Output: %s\n", test->name);
    printf("Expected: Hello World\n\n");

    printf("-----Starting Iterator-----\n\n");

    printSymbolTable(table); 

    startIterator(table);

    printf("-----Iterator Started-----\n\n");

    printf("-----Testing hasCurrent-----\n\n");

    printf("Output: %s\n", getCurrentName(table));
    printf("Expected: hello\n\n");

    nextEntry(table);
    printf("Output: %s\n", getCurrentName(table));
    printf("Expected: world\n\n");

    nextEntry(table);
    printf("Output: %s\n", getCurrentName(table));
    printf("Expected: Dog\n\n");

    nextEntry(table);
    printf("Output: %s\n", getCurrentName(table));
    printf("Expected: mouse\n\n");

    nextEntry(table);
    printf("Output: %s\n", getCurrentName(table));
    printf("Expected: Shepard Pie\n\n");

    nextEntry(table);
    printf("Output: %s\n", getCurrentName(table));
    printf("Expected: Shepard Pie\n");
    

    // looked through hash function by hand, this should be the order
    // Hello -> world -> Dog -> mouse -> Shepard Pie

    destroySymTab(table);

    
    printf("SymTab Destroyed\n");
    printf("-----Test Complete-----\n");

    

    
    return 0;
}