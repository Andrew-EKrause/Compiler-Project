/*
    API for the Semantics file for the main compiler project.
    The file contains several structs for storing instruction-
    related data generated in the compiling process. The file
    also contains functions for processing different events
    based on the input of the C-like program being translated.
    In summary, the Semantics.h file contains the action and
    supporting routines for performing semantics processing.  
*/
//#pragma once

/* 
    The struct contains the semantic 
    records for identifiers. 
*/
struct IdList {
    struct SymEntry * TheEntry;
    struct IdList * Next;
};

/* 
    The struct contains a semantic 
    record for expression results. 
*/
struct ExprRes {
    int Reg;
    struct InstrSeq * Instrs;
};

/* 
    The struct contains a list of 
    expression results. 
*/
struct ExprResList {
	  struct ExprRes *Expr;
	  struct ExprResList * Next;
};

/*
    The struct contains a B-expression 
    result.
*/
struct BExprRes {
    char * Label;
    struct InstrSeq * Instrs;
};

/* ================= */
/* Semantics Actions */
/* ================= */

/* 
    The function handles the case where there is an int literal.
*/
extern struct ExprRes *doIntLit(char *digits);

/* 
    The function handles the case where there is an R-value. 
*/
extern struct ExprRes *doRval(char *name);

/* 
    The function completes an assignment to a variable. 
*/
extern struct InstrSeq *doAssign(char *name, struct ExprRes *Res1);

/* 
    The function performs the addition operation. 
*/
extern struct ExprRes *doAdd(struct ExprRes *Res1, struct ExprRes *Res2);

/* 
    The function performs the multiplication operation. 
*/
extern struct ExprRes *doMult(struct ExprRes *Res1, struct ExprRes *Res2);

/* 
    The function completes a print operation. Whenever values need 
    to be printed out to a console, the function changes the C-like
    code to assembly code.
*/
extern struct InstrSeq *doPrint(struct ExprRes *Expr);

/*  
    The function completes a B-expression operation.
*/
extern struct BExprRes *doBExpr (struct ExprRes *Res1, struct ExprRes *Res2);

/* 
    The function completes a do-if expression operation.
*/
extern struct InstrSeq *doIf(struct BExprRes *bRes, struct InstrSeq *seq);

/*
    The function adds the assembly code that appears
    at the top of all MIPS assembly program files.
*/
extern void	Finish(struct InstrSeq *Code);
