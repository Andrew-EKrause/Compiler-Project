%{
#include <stdio.h>

int numIds = 0;
int numInts = 0;
int numLines = 0;
%}

letter [A-Za-z]
digit [0-9]

%%

{letter}({letter}|{digit})*     {numIds++;}
{digit}+                        {numInts++;}
\n                              {numLines++;}
[ \r\t]                         { }

%%

int yywrap() {

    printf("The number of identifiers is %d\n", numIds);
    printf("The number of integers is %d\n", numInts);
    printf("The number of lines is %d\n", numLines);
    return 1;
}