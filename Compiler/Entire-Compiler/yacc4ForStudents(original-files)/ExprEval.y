%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IOMngr.h"
#include "SymTab.h"
#include "Semantics.h"
#include "CodeGen.h"

extern int yylex();	/* The next token function. */
extern char *yytext;   /* The matched token text.  */
extern int yyleng;      /* The token text length.   */
extern int yyparse();
extern int yyerror(char *);
void dumpTable();

extern SymTab *table;

%}


%union {
  long val;
  char * string;
  struct ExprRes * ExprRes;
  struct InstrSeq * InstrSeq;
  struct BExprRes * BExprRes;
}

%type <string> Id
%type <ExprRes> Factor
%type <ExprRes> Term
%type <ExprRes> Expr
%type <InstrSeq> StmtSeq
%type <InstrSeq> Stmt
%type <BExprRes> BExpr

%token Ident 		
%token IntLit 	
%token Int
%token Write
%token IF
%token EQ	

%%

Prog			:	Declarations StmtSeq						{Finish($2); } ;
Declarations	:	Dec Declarations							{ };
Declarations	:											{ };
Dec			:	Int Ident {enterName(table, yytext); }';'	{};
StmtSeq 		:	Stmt StmtSeq								{$$ = AppendSeq($1, $2); } ;
StmtSeq		:											{$$ = NULL;} ;
Stmt			:	Write Expr ';'								{$$ = doPrint($2); };
Stmt			:	Id '=' Expr ';'								{$$ = doAssign($1, $3);} ;
Stmt			:	IF '(' BExpr ')' '{' StmtSeq '}'					{$$ = doIf($3, $6);};
BExpr		:	Expr EQ Expr								{$$ = doBExpr($1, $3);};
Expr			:	Expr '+' Term								{$$ = doAdd($1, $3); } ;
Expr			:	Term									{$$ = $1; } ;
Term		:	Term '*' Factor								{ $$ = doMult($1, $3); } ;
Term		:	Factor									{ $$ = $1; } ;
Factor		:	IntLit									{ $$ = doIntLit(yytext); };
Factor		:	Ident									{ $$ = doRval(yytext); };
Id			: 	Ident									{ $$ = strdup(yytext);}
 
%%

int yyerror(char *s)  {
  writeIndicator(getCurrentColumnNum());
  writeMessage("Illegal Character in YACC");
  return 1;
}
