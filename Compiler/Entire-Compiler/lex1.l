%{
    // #include "yaccExample.h"
    #include "IOMngr.h"
    #include "ExprEval.tab.h"

    #define YY_INPUT(buf,result,max_size) \
    { int c = getNextSourceChar(); \
    result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
    }

    // --> MAYBE ENABLE YOUR CODE TO RECOGNIZE COMMENTS LATER ON!!!
%}

letter [A-Za-z]
digit [0-9]

%%

int					                    {return Int;}
print					                {return Print;}
printString                             {return Printstrings;}
printLines                              {return Printlines;}
printSpaces                             {return Printspaces;}
read                                    {return Read;}
if					                    {return IF;}
else                                    {return ELSE;}
while                                   {return WHILE;}
for                                     {return FOR;}

{letter}({letter}|{digit})*	            {return Ident;}
{digit}{digit}*		                    {return IntLit;}
\".*\"                                  {return StrLit;}

\|\|                                    {return OR;}
\&\&                                    {return AND;}
\!                                      {return '!';}

\!\=                                    {return NOT_EQ;}
\=\=					                {return EQ;}
\<\=                                    {return LT_OR_EQ;}
\>\=                                    {return GT_OR_EQ;}
\<                                      {return LT;}
\>                                      {return GT;}

\=					                    {return '=';}
\+					                    {return '+';}
\-                                      {return '-';}
\*					                    {return '*';}
\/					                    {return '/';}
\%                                      {return '%';}
\^                                      {return '^';}

\;					                    {return ';';}
\{					                    {return '{';}
\}					                    {return '}';}
\(					                    {return '(';}
\)					                    {return ')';}
\,                                      {return ',';}
\[				                        {return '[';}
\]                                      {return ']';}

[ ]                                     {}
\t				                        {}
\r				                        {}
\n				                        {}
\0                                      {}

.				                        {
                                            writeIndicator(getCurrentColumnNum());
				                            writeMessage("Illegal Character in lex");
                                        }

%%

int yywrap () {
    return 1;
}
