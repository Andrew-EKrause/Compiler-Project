%{

#include "semantics.h"
#include "IOMngr.h"
#include <string.h> // --> MAY NOT NEED
#include <ctype.h> // --> MAY NOT NEED; MAY NOT NEED THE %union BELOW AS WELL!!!

extern int yylex(); /* The next token function. */
extern char *yytext; /* The matched token text. */
extern int yyerror(char *s);

%}

%union { 
    char character;
    char* string;
}

%type <string> Id 
%type <SymTab*> Expr 
%type <SymTab*> Term 
%type <SymTab*> Factor 

%token Ident 
%token SetLit
%token UNION 
%token INTERSECT 

%%

Prog        : StmtSeq                   {printSymTab();};
StmtSeq     : Stmt StmtSeq              {};
StmtSeq     :                           {};
Stmt        : Id '=' Expr';'            {storeVar($1, $3);};
Expr        : Expr UNION Term           {$$ = doUNION($1, $3);};
Expr        : Term                      {$$ = $1;};
Term        : Term INTERSECT Factor     {$$ = doINTERSECT($1, $3);};
Term        : Factor                    {$$ = $1;};
Factor      : '('Expr')'                {$$ = $2;};
Factor      : Id                        {$$ = getValue($1);};
Factor      : SetLit                    {$$ = makeSet($1);};
Id          : Ident                     {$$ = strdup(yytext);};

%%

int yyerror(char *s) {
    WriteIndicator(getCurrentColumnNum());
    WriteMessage("Illegal Character in YACC");
    return 1;
}
