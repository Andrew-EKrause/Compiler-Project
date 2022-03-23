#include <stdio.h>
#include <stdlib.h>
#include "SymTab.h"
#include "IOMngr.h"

extern int yyparse();

SymTab *table;

int main(int argc, char *argv[]) {
    table = createSymTab(17);
    if(!openFiles(argv[1], "listing")) {
        printf("open failed\n");
        exit(0);
    }
    yyparse();
}
