%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "IOMngr.h"
    #include "SymTab.h"
    #include "Semantics.h"
    #include "CodeGen.h"

    extern int yylex(); /* The next token function. */
    extern char *yytext; /* The matched token text. */
    extern int yyleng; /* The token text length. */
    extern int yyparse(); /* Call function to parse data. */
    extern int yyerror(char *); /* The error report function. */
    void dumpTable(); /* Remove a table to free up memory. */

    extern SymTab *table;
%}

%union {
    long val;
    char * string;
    struct ExprRes * ExprRes;
    struct InstrSeq * InstrSeq;
    struct IdList * IdList;
    struct ExprResList * ExprResList;
}

%type <InstrSeq> StmtSeq
%type <InstrSeq> Stmt
%type <string> ArrayIntLit
%type <InstrSeq> AssnmtStmt
%type <InstrSeq> ArrayAssnmtStmt
%type <ExprResList> ExprList
%type <string> StrList
%type <ExprRes> ExprL0
%type <ExprRes> ExprL1
%type <ExprRes> ExprL2
%type <ExprRes> ExprL3
%type <ExprRes> ExprL4
%type <ExprRes> ExprL5
%type <ExprRes> ExprL6
%type <ExprRes> ExprL7
%type <InstrSeq> ReadList
%type <string> Id

%token Int
%token Ident	
%token StrLit	
%token Print
%token Printstrings
%token Printlines
%token Printspaces
%token Read
%token IF
%token ELSE
%token WHILE
%token FOR
%token OR
%token AND
%token NOT_EQ
%token EQ
%token LT_OR_EQ
%token GT_OR_EQ
%token LT
%token GT
%token IntLit	

%%

Prog			            : Declarations StmtSeq						                           { Finish($2); };
Declarations	            : Dec Declarations							                           { };
            	            |											                           { };
                            
Dec			                : Int Id ';'                                                           { enterNameAndFreeDec(table, $2); };
                            | Int Id '[' ArrayIntLit ']' ';'                                       { createArrayDec($2, $4, NULL); };
                            | Int Id '[' ArrayIntLit ']' '[' ArrayIntLit ']' ';'                   { createArrayDec($2, $4, $7); };

StmtSeq 		            : Stmt StmtSeq								                           { $$ = AppendSeq($1, $2); };
    		                |											                           { $$ = NULL; };

Stmt			            : Print '(' ExprList ')' ';'                                           { $$ = doPrintExpressions($3); };
                            | Printstrings '(' StrList ')' ';'                                     { $$ = doPrintStrings($3); };
                            | Printlines '(' ExprL0 ')' ';'                                        { $$ = doPrintformat($3, newline); };
                            | Printspaces '(' ExprL0 ')' ';'                                       { $$ = doPrintformat($3, space); };
                            | Read '(' ReadList ')' ';'                                            { $$ = $3; };
                            
                            | IF '(' ExprL0 ')' '{' StmtSeq '}'                                    { $$ = doIf($3, $6); };
                            | IF '(' ExprL0 ')' '{' StmtSeq '}' ELSE '{' StmtSeq '}'               { $$ = doIfElse($3, $6, $10); };
                            | WHILE '(' ExprL0 ')' '{' StmtSeq '}'                                 { $$ = doWhile($3, $6); };
                            | FOR '(' AssnmtStmt ';' ExprL0 ';' AssnmtStmt ')' '{' StmtSeq '}'     { $$ = doFor($3, $5, $7, $10); };
                            | AssnmtStmt ';'                                                       { $$ = $1; };
                            | ArrayAssnmtStmt ';'                                                  { $$ = $1; };

AssnmtStmt			        : Id '=' ExprL0							                               { $$ = doAssign($1, $3); };

ArrayAssnmtStmt             : Id '[' ExprL0 ']' '=' ExprL0                                         { $$ = doArrayAssign($1, $3, NULL, $6); };
                            | Id '[' ExprL0 ']' '[' ExprL0 ']' '=' ExprL0                          { $$ = doArrayAssign($1, $3, $6, $9); };

ExprList                    : ExprL0 ',' ExprList                                                  { $$ = createExprList($1, $3); };
                            | ExprL0                                                               { $$ = createExprList($1, NULL); };

ExprL0                      : ExprL0 OR ExprL1                                                     { $$ = doBooleanOps($1, $3, or); };
                            | ExprL0 AND ExprL1                                                    { $$ = doBooleanOps($1, $3, and); };
                            | ExprL1                                                               { $$ = $1; };

ExprL1                      : '!' ExprL1                                                           { $$ = doBooleanOps($2, NULL, not); };
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

ExprL7    		            : '-'ExprL6                                                            { $$ = doIntLitNeg($2); };
                            | IntLit									                           { $$ = doIntLit(yytext); };
    		                | Ident									                               { $$ = doRval(yytext); };

ReadList                    : Id '[' ExprL0 ']' '[' ExprL0 ']' ',' ReadList                        { $$ = createReadListArray($1, $3, $6, $9); };
                            | Id '[' ExprL0 ']' ',' ReadList                                       { $$ = createReadListArray($1, $3, NULL, $6); };
                            | Id '[' ExprL0 ']' '[' ExprL0 ']'                                     { $$ = createReadListArray($1, $3, $6, NULL); };
                            | Id '[' ExprL0 ']'                                                    { $$ = createReadListArray($1, $3, NULL, NULL); };
                            | Id ',' ReadList                                                      { $$ = createReadListIdent($1, $3); };
                            | Id                                                                   { $$ = createReadListIdent($1, NULL); };
                            |                                                                      { $$ = NULL; };

ArrayIntLit                 : IntLit                                                               { $$ = strdup(yytext); };
StrList                     : StrLit                                                               { $$ = strdup(yytext); };
Id			                : Ident									                               { $$ = strdup(yytext); };

%%

int yyerror(char *s) {
    writeIndicator(getCurrentColumnNum());
    writeMessage("Illegal Character in YACC");
    return 1;
}
