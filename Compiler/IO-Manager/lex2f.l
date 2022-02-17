%{
#include <stdio.h>
#include "SymTab.h"
#include "IOMngr.h"
#define IDENT 1
#define HEX 2
#define YY_INPUT(buf, result, max_size) \
{ int c = getNextSourceChar(); \
      result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
    }
extern int yylex();
extern char *yytext;
typedef struct {
    int type;
    int count
} Attr;
%}

letter [a-z]
digit [0-9]|[A-F]

%%

{letter}+   {return INDENT;}
{digit}+    {return HEX;}

[ \r\n\t]   {}

%%

int main(int argc, char *argv[]) {
    SymTab *table = createSymTab(17);
    openFiles(argv[1], argv[2]);
    int more;
    int newToken;
    int token;
    Attr *a;
    while((token = yylex())) {
        newToken = enterName(table, yytext);
        if(newToken) {
            a = (Attr *) malloc(sizeof(Attr));
            a->type = token;
            a->count = 1;
            setCurrentAttr(table, a);
        } else {
            a = getCurrentAttr(table, a);
            a->count++;
        }
    }
    more = startIterator(table);
    while(more) {
        printf("%s\t%s\t%d\n", getCurrentName(table),
                               ((Attr *) getCurrentAttr(table))->type == IDENT ? "Identifier" : "Hexadecimal",
                               ( a = getCurrentAttr(table))->count);
        free(a);
        more = nextEntry(table);
    }
    destroySymTab(table);
}

int yywrap() {
    return 1;
}