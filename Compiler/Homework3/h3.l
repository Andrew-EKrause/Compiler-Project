%{
    #include "IOMngr.h"
    #include "SymTab.h"
    #include "h3.tab.h"

    #define YY_INPUT(buf, result, max_size) \
    { int c = getNextSourceChar(); \
    result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
    }
%}

letter [A-Za-z]
digit [0-9]

%%

\{\}|\{{letter}(\,{letter})*\}  {return SetLit;}
{letter}({letter}|{digit})*     {return Ident;}
\+                              {return UNION;}
\*                              {return INTERSECT;}
\=                              {return '=';}
\;                              {return ';';}
\(                              {return '(';}
\)                              {return ')';}
\{                              {return '{';}
\}                              {return '}';}
\,                              {return ',';}
[ ]                             {}
\t                              {}
\r                              {}
\n                              {}
\0                              {}
.                               {
                                    writeIndicator(getCurrentColumnNum());
                                    writeMessage("Illegal Character in lex");
                                }

%%

int yywrap() {
    return 1;
}