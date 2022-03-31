%{
    // #include "yaccExample.h"
    #include "IOMngr.h"
    // #include "y.tab.h"
    #include "ExprEval.tab.h"

    #define YY_INPUT(buf,result,max_size) \
	{ int c = getNextSourceChar(); \
    result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
    }
%}

letter [A-Za-z]
digit [0-9]

%%

if					                      {return IF;}
else                                      {return ELSE;}
while                                     {return WHILE;}
for                                       {return FOR;}
int					                      {return Int;}
read                                      {return Read;}
printlines                                {return Printlines;}
printspaces                               {return Printspaces;}
print					                  {return Write;}

{letter}({letter}|{digit})*	              {return Ident;}
{digit}{digit}*		                      {return IntLit;}

\=\=					                  {return EQ;}
\!\=                                      {return NOT_EQ;}
\<\=                                      {return LT_OR_EQ;}
\>\=                                      {return GT_OR_EQ;}
\<                                        {return LT;}
\>                                        {return GT;}
\!                                        {return '!';}
\|\|                                      {return OR;}
\&\&                                      {return AND;}

\=					                      {return '=';}
\+					                      {return '+';}
\-                                        {return '-';}
\*					                      {return '*';}
\/                                        {return '/';}
\^                                        {return '^';}
\%                                        {return '%';}

\;					                      {return ';';}
\{					                      {return '{';}
\}					                      {return '}';}
\(					                      {return '(';}
\)					                      {return ')';}
\,                                        {return ',';}

[ ]				                          {}
\t			        	                  {}
\r				                          {}
\n				                          {}
\0                                        {}

.				                          {
                                            writeIndicator(getCurrentColumnNum());
				                            writeMessage("Illegal Character in lex");
                                          }

%%

int yywrap () {
    return 1;
}
