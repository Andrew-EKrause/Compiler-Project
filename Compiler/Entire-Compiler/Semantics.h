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

/*
    The struct is a linked list of
    nodes that can contain arguments
    and expressions.
*/
struct Node {
    void *name;
    struct Node *next;
};

/* ================= */
/* Semantics Actions */
/* ================= */

/* 
    The functions handle the cases where there is an int literal.
*/
extern struct ExprRes *doIntLit(char *digits);
extern struct ExprRes *doIntLitNeg(char *digits);
extern struct ExprRes *doRval(char *name);
extern struct InstrSeq *doAssign(char *name, struct ExprRes *Res1);

/* 
    The functions handle the cases for basic arithmetic operations.
*/
extern struct ExprRes *doAdd(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doSubtraction(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doMult(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doDivide(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doExponential(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doModulo(struct ExprRes *Res1, struct ExprRes *Res2);

/*
    The functions handle the cases for printing out values.
*/
extern struct InstrSeq *doPrint(struct ExprRes *Expr);
//extern struct InstrSeq *doPrint(struct Node *node);
extern struct InstrSeq *doPrintlines(struct ExprRes *Res);
extern struct InstrSeq *doPrintspaces(struct ExprRes *Res);
extern struct InstrSeq *doRead(struct Node *node);

/*  
    The functions complete branch expression operations.
*/
// extern struct BExprRes *doBExpr(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doBExprEq(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doBExprNotEq(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doBExprLtOrEq(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doBExprGtOrEq(struct ExprRes *Res1, struct ExprRes *Res2);

/*
    The functions handle control flow and conditonal operations.
*/
extern struct ExprRes *doBExprLt(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doBExprGt(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doNegate(struct ExprRes *Res1);
extern struct ExprRes *doOr(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doAnd(struct ExprRes *Res1, struct ExprRes *Res2);

/* 
    The functions handle cases where there are conditionals and loops.
    In other words, additional control flow.
*/
extern struct InstrSeq *doIf(struct ExprRes *Res, struct InstrSeq *seq);
extern struct InstrSeq *doIfElse(struct ExprRes *Res, struct InstrSeq *seq1, struct InstrSeq *seq2);
extern struct InstrSeq *doWhile(struct ExprRes *Res, struct InstrSeq *seq);
extern struct InstrSeq *doFor(struct InstrSeq *Assignment1, struct ExprRes *CondRes, struct InstrSeq *Assignment2, struct InstrSeq *seq);

/*
    The functions enable multiple arguments and expressions to be 
    handled together by appending them to various lists.
*/
extern struct Node *appendToArgList(char *c, struct Node *next);
extern struct Node *appendToExprList(struct ExprRes *Res1, struct Node *next);

/*
    The function adds the assembly code that appears
    at the top of all MIPS assembly program files.
*/
extern void	Finish(struct InstrSeq *Code);
