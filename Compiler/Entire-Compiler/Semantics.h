/*
    API for the Semantics file for the main compiler project.
    The file contains several structs for storing instruction-
    related data generated in the compiling process. The file
    also contains functions for processing different events
    based on the input of the C-like program being translated.
    In summary, the Semantics.h file contains the action and
    supporting routines for performing semantics processing.  
*/
#pragma once

/* ================= */
/* Structs */
/* ================= */

/* 
    The struct contains a semantic 
    record for expression results. 
*/
struct ExprRes {
    int Reg;
    struct InstrSeq *Instrs;
};

/* 
    The struct contains a list of 
    expression results. 
*/
struct ExprResList {
	  struct ExprRes *Expr;
	  struct ExprResList *Next;
};

/*
    The struct contains a B-expression 
    result.
*/
struct BExprRes {
    char *Label;
    struct InstrSeq *Instrs;
};

/*
    The struct is a linked list of
    strings created for printing out
    strings in the C-like language.
*/
struct StringItem {
    char *String;
    struct StringItem *Next;
    char *StringLabel;
};

/*
    The struct is a linked list of arrays
    created for enabling both 1D array and
    2D array functionality.
*/
struct ArrayItem {
    char *ArrayName;
    char *ArrayLabel;
    int Size1;
    int Size2;
    struct ArrayItem *Next;
};

/* ================= */
/* Enumerations */
/* ================= */

/*
    Create an enumeration for boolean operators.
    Create another enumeration for printing lines
    and spaces.
*/
enum BExprOps {and, or, not};
enum PrintExprOps {newline, space};

/* ================= */
/* Semantics Actions */
/* ================= */

/*
    The function adds the assembly code that appears
    at the top of all MIPS assembly program files.
*/
extern void	Finish(struct InstrSeq *Code);

/*
    The function calls the enterName() function of 
    symbol table, and frees the name after inserting
    it into the symbol table.
*/
extern void enterNameAndFreeDec(SymTab *table, char *name);

/*
    The functions handle the cases for printing out values
    and reading values.
*/
extern struct InstrSeq *doPrintStrings(char *stringValue);
extern struct InstrSeq *doPrintExpressions(struct ExprResList *list);
extern struct ExprResList *createExprList(struct ExprRes *res, struct ExprResList *list);
extern struct InstrSeq *doPrintformat(struct ExprRes *Res, enum PrintExprOps printType);

/* 
    The functions handle cases where there are conditionals and loops.
    In other words, additional control flow.
*/
extern struct InstrSeq *doIf(struct ExprRes *Res, struct InstrSeq *seq);
extern struct InstrSeq *doIfElse(struct ExprRes *Res, struct InstrSeq *seq1, struct InstrSeq *seq2);
extern struct InstrSeq *doWhile(struct ExprRes *Res, struct InstrSeq *seq);
extern struct InstrSeq *doFor(struct InstrSeq *Assignment1, struct ExprRes *CondRes, struct InstrSeq *Assignment2, struct InstrSeq *seq);
extern struct InstrSeq *doAssign(char *name, struct ExprRes *Res1);

/*
    The functions handle cases where there are 1D arrays and 2D arrays.
*/
extern struct InstrSeq *createArrayDec(char *name, char *size1, char *size2);
extern struct InstrSeq *doArrayAssign(char *name, struct ExprRes *Res1, struct ExprRes *Res2, struct ExprRes *Res3);
/*
    The function handles boolean operations.
*/
extern struct ExprRes *doBooleanOps(struct ExprRes *Res1, struct ExprRes *Res2, enum BExprOps boolOperator);

/*
    The function handles equality operations.
*/
extern struct ExprRes *doEqualityOps(struct ExprRes *Res1, struct ExprRes *Res2, char *inst);

/* 
    The functions handle the cases for basic arithmetic operations.
*/
extern struct ExprRes *doArithmeticOps(struct ExprRes *Res1, struct ExprRes *Res2, char *inst);
extern struct ExprRes *doModulo(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doExponential(struct ExprRes *Res1, struct ExprRes *Res2);

/* 
    The functions handle the cases where there is an int literal.
*/
extern struct ExprRes *doIntLitNeg(struct ExprRes *Res);
extern struct ExprRes *doIntLit(char *digits);
extern struct ExprRes *doRval(char *name);

/*
    The function creates a list of expressions. This function can
    work with identifiers and array expressions in the compiler.
*/
extern struct InstrSeq *createReadListArray(char *readName, struct ExprRes *readSize1, struct ExprRes *readSize2, struct InstrSeq *readList);
extern struct InstrSeq *createReadListIdent(char *readName, struct InstrSeq *readList);
