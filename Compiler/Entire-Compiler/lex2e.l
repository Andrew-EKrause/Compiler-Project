%{
#include <stdio.h>
#include "SymTab.h"
#define IDENT 1
#define HEX 2
extern int yylex();
extern char *yytext;
typedef struct {
    int count;
} Attr;
%}

letter  [a-z]
digit   [0-9]|[A-F]

%%

{letter}+   {return IDENT;}
{digit}+    {return HEX;}

[ \r\n\t]   {}

%%

int main(int argc, char *argv[]) {
    SymTab *table = createSymTab(17);
    int more;
    int newToken;
    int token;
    Attr *a;
    while((token = yylex())) {
        newToken = enterName(table, yytext);
        if(newToken) {
            a = (Attr *) malloc(sizeof(Attr));
            a->count = 1;
            setCurrentAttr(table, a);
        } else {
            a = getCurrentAttr(table);
            a->count++;
        }
    }
    more = startIterator(table);
    while(more) {
        printf("%s\t%d\n", getCurrentName(table), (a = getCurrentAttr(table))->count);
        free(a);
        more = nextEntry(table);
    }
    destroySymTab(table);
}

int yywrap() {
    return 1;
}