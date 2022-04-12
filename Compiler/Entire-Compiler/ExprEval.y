%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "IOMngr.h"
    #include "SymTab.h"
    #include "Semantics.h"
    #include "CodeGen.h"

    extern int yylex(); /* The next token function. */
    extern char *yytext; /* The matched token text.  */
    extern int yyleng; /* The token text length.   */
    extern int yyparse(); /* IMPORTANT; WHEN YOU CREATE THE EXPRESSION LIST, YOU WILL MAYBE WANT TO TAKE OUT THE PARANTHESES FOR THE REGULAR PRINT! */
    extern int yyerror(char *);
    void dumpTable();

    extern SymTab *table;
%}

%union {
    long val;
    char * string;
    struct ExprRes * ExprRes;
    struct InstrSeq * InstrSeq;
    struct IdList * IdList;
    struct Node * Node;
}

%type <string> Id
%type <InstrSeq> StmtSeq
%type <InstrSeq> Stmt
%type <InstrSeq> AssnmtStmt
%type <IdList> IdentList
%type <ExprRes> ExprL0
%type <ExprRes> ExprL1
%type <ExprRes> ExprL2
%type <ExprRes> ExprL3
%type <ExprRes> ExprL4
%type <ExprRes> ExprL5
%type <ExprRes> ExprL6
%type <ExprRes> ExprL7

%token Ident		
%token IntLit	
%token Int
%token Write
%token IF
%token EQ
%token NOT_EQ
%token LT_OR_EQ
%token GT_OR_EQ
%token LT
%token GT
%token OR
%token AND
%token Read

%%

Prog			            : Declarations StmtSeq						                           { Finish($2); };
Declarations	            : Dec Declarations							                           { };
            	            |											                           { };
                            
Dec			                : Int Ident                                                            { enterName(table, yytext); }';' {};
StmtSeq 		            : Stmt StmtSeq								                           { $$ = AppendSeq($1, $2); };
    		                |											                           { $$ = NULL; };

Stmt			            : Write '(' ExprL0 ')' ';'					                           { $$ = doPrint($3); };
                            | Read '(' IdentList ')' ';'                                           { $$ = doRead($3); };
    			            | IF '(' ExprL0 ')' '{' StmtSeq '}'			                           { $$ = doIf($3, $6); };
                            | AssnmtStmt ';'                                                       { $$ = $1; };

AssnmtStmt			        : Id '=' ExprL0							                               { $$ = doAssign($1, $3); };

ExprL0                      : ExprL0 OR ExprL1                                                     { $$ = doBooleanOPs($1, $3, or); };
                            | ExprL0 AND ExprL1                                                    { $$ = doBooleanOPs($1, $3, and); };
                            | ExprL1                                                               { $$ = $1; };

ExprL1                      : '!' ExprL2                                                           { $$ = doBooleanOPs($2, NULL, not); };
                            | ExprL2                                                               { $$ = $1; };

ExprL2                      : ExprL2 NOT_EQ ExprL3                                                 { $$ = doEqualityOps($1, $3, "sne"); };
      		                | ExprL2 EQ ExprL3					                                   { $$ = doEqualityOps($1, $3, "seq"); };
                            | ExprL2 LT_OR_EQ ExprL3                                               { $$ = doEqualityOps($1, $3, "sle"); };
                            | ExprL2 GT_OR_EQ ExprL3                                               { $$ = doEqualityOps($1, $3, "sge"); };
                            | ExprL2 LT ExprL3                                                     { $$ = doEqualityOps($1, $3, "slt"); };
                            | ExprL2 GT ExprL3                                                     { $$ = doEqualityOps($1, $3, "sgt"); };
                            | ExprL3                                                               { $$ = $1; };

ExprL3                      : ExprL3 '+' ExprL4						                               { $$ = doArithmeticOps($1, $3, "add"); };
    			            | ExprL3 '-' ExprL4							                           { $$ = doArithmeticOps($1, $3, "sub"); };
    			            | ExprL4									                           { $$ = $1; };

ExprL4                      : ExprL4 '*' ExprL5							                           { $$ = doArithmeticOps($1, $3, "mul"); };
    		                | ExprL4 '/' ExprL5							                           { $$ = doArithmeticOps($1, $3, "div"); };
    		                | ExprL4 '%' ExprL5							                           { $$ = doModulo($1, $3); };
                            | ExprL5                                                               { $$ = $1; };

ExprL5                      : ExprL6 '^' ExprL5                                                    { $$ = doExponential($1, $3); };
    		                | ExprL6									                           { $$ = $1; };

ExprL6                      : '(' ExprL0 ')'                                                       { $$ = $2; };
                            | ExprL7                                                               { $$ = $1; };

ExprL7    		            : '-'ExprL6                                                            { $$ = doIntLitNeg(yytext); };
                            | IntLit									                           { $$ = doIntLit(yytext); };
    		                | Ident									                               { $$ = doRval(yytext); };

IdentList                   : Id ',' IdentList                                                     { $$ = createIdentList($1, $3); };
                            | Id                                                                   { $$ = createIdentList($1, NULL); };

Id			                : Ident									                               { $$ = strdup(yytext); };

%%

int yyerror(char *s) {
    writeIndicator(getCurrentColumnNum());
    writeMessage("Illegal Character in YACC");
    return 1;
}
