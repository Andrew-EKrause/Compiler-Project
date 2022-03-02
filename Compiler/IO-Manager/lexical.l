%{
    #include <stdio.h>
    #include "IOMngr.h"
    #define IDENT 1
    #define INTEGER 2
    #define LINE 3
    #define YY_INPUT(buf,result,max_size) \
        { int c = getNextSourceChar(); \
            result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
        }
%}

letter [A-Za-z]
digit [0-9]

%%
    
{letter}({letter}|{digit})* {return IDENT;}

{digit}+ {return INTEGER;}

\n {return LINE;}

[ \r\t] { }

%%

int main(int argc, char * argv[]) {
    int numIds = 0;
    int numInts = 0;
    int numLines = 0;
    int token;
    openFiles(argv[1], argv[2]);
    while ((token = yylex())) {
        if (token == IDENT) numIds++;
        else if (token == INTEGER) numInts++;
        else numLines++;
    }
    printf("\nThe number of identifiers is %d\n", numIds);
    printf("The number of integers is %d\n", numInts);
    printf("The number of lines is %d\n", numLines);

    closeFiles();
    yylex_destroy();
}

int yywrap() {
    return 1;
}
