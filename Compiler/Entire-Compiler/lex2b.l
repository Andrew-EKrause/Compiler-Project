%{
#include <stdio.h>
#define IDENT 1
#define INTEGER 2
#define LINE 3
%}

letter  [A-Za-z]
digit   [0-9]

%%

{letter}({letter}|{digit})*     {return INDENT;}
{digit}+                        {return INTEGER;}
\n                              {return LINE;}
[ \r\t]                         { }

%%

int main(int argh, char * argv[]) {
    int numIds = 0;
    int numInts = 0;
    int nuLines = 0;

    int token;
    while((token = yylex())) {
        if(token == IDENT) numIds++;
        else if(token == INTEGER) numInts++;
        else numLines++;
    }
    printf("The number of identifiers is %d\n", numIds);
    printf("The number of integers is %d\n", numInts);
    printf("The number of lines is %d\n", numLines);    
}

int yywrap() {
    return 1;
}