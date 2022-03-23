%{
    #include "semantics.h"
    #include "IOMngr.h"
    #include <string.h>
    #include <stdbool.h>

    extern int yylex(); /* The next token function. */
    extern char *yytext; /* The matched token text. */
    extern int yyerror(char *s);
%}

%union {
    bool boolean;
    char* string;
}

%type <string> Id
%type <boolean> Expr
%type <boolean> Term
%type <boolean> Factor

%token Ident
%token TRUE
%token FALSE
%token OR
%token AND

%%

Prog            : StmtSeq                   {printSymTab();};
StmtSeq         : Stmt StmtSeq              { };
StmtSeq         :                           { };
Stmt            : Id '=' Expr ';'           {storeVar($1, $3);};
Expr            : Expr OR Term              {$$ = doOR($1, $3);};
Expr            : Term                      {$$ = $1;};
Term            : Term AND Factor           {$$ = doAND($1, $3);};
Term            : Factor                    {$$ = $1;};
Factor          : '!' Factor                {$$ = doNOT($2);};
Factor          : '(' Expr ')'              {$$ = $2;};
Factor          : Id                        {$$ = getVal($1);};
Factor          : TRUE                      {$$ = true;};
Factor          : FALSE                     {$$ = false;};
Id              : Ident                     {$$ = strdup(yytext);};

%%

int yyerror(char *s) {
    writeIndicator(getCurrentColumnNum());
    writeMessage("Illegal Character in YACC");
    return 1;
}