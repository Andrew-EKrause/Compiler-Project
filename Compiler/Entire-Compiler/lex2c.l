%{
#include <stdio.h>
#include "IOMngr.h"
#define YY_INPUT(buf, result, max_size) \
{ int c = getNextSourceChar(); \
      result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
    }

int numIds = 0;
int numInts = 0;
int numLines = 0;

%}

letter  [A-Za-z]
digit   [0-9]

%%

{letter}({letter}|{digit})*     {numIds++;}
{digit}+                        {numInts++;}
\n                              {numLines++;}
[ \r\t]                         { }

%%

int main(int argc, char * argv[]) {
    openFiles(argv[1], argv[2]);
    yylex();
}

int yywrap() {

    printf("The number of identifiers is %d\n", numIds);
    printf("The number of integers is %d\n", numInts);
    printf("The number of lines is %d\n", numLines);
    return 1;
}