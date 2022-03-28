/**
 * The file contains functions that support
 * semantic action routines. The functions
 * supporting these semantic action routines
 * guide the compilation process. The functions
 * in this file include print functions for 
 * generating MIPS assembly code equivalent to
 * the C-like language, a function for addition,
 * a function for subtraction, a function for
 * multiplication, a function for exponents,
 * a function for arrays, a function for other
 * functions, etc. The code in this file 
 * makes up the majority of the logic needed
 * to create the compiler for the C-like
 * language that is compiled into the MIPS 
 * assembly code.
 * 
 * C-like program is compiled into assembly code,
 * 
 * @file Semantics.c
 * @author Andrew Krause
 * @version 0.1
 * @date 2022-04-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// Include the strings library as 
// well as the standard C library.
#include <strings.h>
#include <stdlib.h>

// Include the .h files needed to 
// complete the compilation process.
#include "CodeGen.c" // --> ASK QUINN OR GENDREAU; WHY .c? WHY IS .h NOT WORKING???
#include "Semantics.h"
#include "SymTab.h"
#include "IOMngr.h"

// Create an external global symbol table for
// memory management of the variable values.
extern SymTab *table;

/* ========================== */
/* Semantics support routines */
/* ========================== */

/**
 * The function returns a struct that contains
 * a new instruction generated within the function.
 * The function handles cases where an int literal
 * is being evaluated. The function ensures that
 * the int literal is added into a register via
 * the "li" label (It loads an immediate value
 * into a register).
 */
struct ExprRes *doIntLit(char *digits) { 

    // Create a struct of type ExprRes to store 
    // the new instruction being created.
    struct ExprRes *res;
  
    // Allocate space for the struct, find the available registers to
    // use for creation of the instruction, and generate the instruction.
    res = (struct ExprRes *) malloc(sizeof(struct ExprRes));
    res->Reg = AvailTmpReg();
    res->Instrs = GenInstr(NULL, "li", TmpRegName(res->Reg), digits, NULL);

    // Return the resulting instruction.
    return res;
}

/**
 * The function returns a struct that contains a new
 * instruction generated within the function. The
 * function handles cases where data is being stored
 * at some address in memory. The function ensures
 * that the r-value is added into a register via
 * the "lw" label (It loads the data from the data
 * memory through a specified address).
 */
struct ExprRes *doRval(char *name) { 

    // Create a struct of type ExprRes to store
    // the new instruction being created.
    struct ExprRes *res;
  
    // If the value is not found in the symbol table,
    // meaning it was never created, return an error.
    if(!findName(table, name)) {
		writeIndicator(getCurrentColumnNum());
		writeMessage("Undeclared variable");
    }

    // Allocate space for the struct, find the available registers to
    // use for creation of the instruction, and generate the instruction.
    res = (struct ExprRes *) malloc(sizeof(struct ExprRes));
    res->Reg = AvailTmpReg();
    res->Instrs = GenInstr(NULL, "lw", TmpRegName(res->Reg), name, NULL);

    // Return the resulting instruction.
    return res;
}

/**
 * The function returns a struct that contains a new
 * instruction generated within the function. The
 * function handles cases where data is being added
 * together. Two integer values are combined in the
 * process of addition. The function ensures that
 * the values are added together in a process that 
 * stores the result in a third register. The label
 * for this process is the "add" label (It stores 
 * the data added together via register2 and register3
 * in register1).
 */
struct ExprRes *doAdd(struct ExprRes *Res1, struct ExprRes *Res2) { 

    // Create an integer variable to represent 
    // the available temporary registers.
    int reg;
    reg = AvailTmpReg();

    // Call the AppendSeq function to determine what
    // registers are open as well as add the instrutions
    // to the linked list of instructions.
    AppendSeq(Res1->Instrs, Res2->Instrs);
    AppendSeq(Res1->Instrs, GenInstr(NULL, "add", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));
    
    // Call the functions below to indicate 
    // that the registers used in the "add" 
    // operation are now free to use again. 
    ReleaseTmpReg(Res1->Reg);
    ReleaseTmpReg(Res2->Reg);
    
    // Set the register number of the result
    // equal to the "reg" variable that was used
    // to determine what register number to use
    // for the operation.
    Res1->Reg = reg;
    
    // Free the space in the result variable,
    // and return the other result.
    free(Res2);
    return Res1;
}

struct ExprRes *doMult(struct ExprRes *Res1, struct ExprRes *Res2) { 

    int reg;
   
    reg = AvailTmpReg();
    AppendSeq(Res1->Instrs, Res2->Instrs);
    AppendSeq(Res1->Instrs, GenInstr(NULL, "mul", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));
    ReleaseTmpReg(Res1->Reg);
    ReleaseTmpReg(Res2->Reg);
    Res1->Reg = reg;
    free(Res2);
    return Res1;
}

struct InstrSeq *doPrint(struct ExprRes *Expr) { 

    struct InstrSeq *code;
    
    code = Expr->Instrs;
  
    AppendSeq(code, GenInstr(NULL, "li", "$v0", "1", NULL));
    AppendSeq(code, GenInstr(NULL, "move", "$a0", TmpRegName(Expr->Reg), NULL));
    AppendSeq(code, GenInstr(NULL, "syscall", NULL, NULL, NULL));

    AppendSeq(code, GenInstr(NULL, "li", "$v0", "4", NULL));
    AppendSeq(code, GenInstr(NULL, "la", "$a0", "_nl", NULL));
    AppendSeq(code, GenInstr(NULL, "syscall", NULL, NULL, NULL));

    ReleaseTmpReg(Expr->Reg);
    free(Expr);

    return code;
}

struct InstrSeq *doAssign(char *name, struct ExprRes *Expr) { 

    struct InstrSeq *code;
  
    if(!findName(table, name)) {
		writeIndicator(getCurrentColumnNum());
		writeMessage("Undeclared variable");
    }

    code = Expr->Instrs;
  
    AppendSeq(code, GenInstr(NULL, "sw", TmpRegName(Expr->Reg), name, NULL));

    ReleaseTmpReg(Expr->Reg);
    free(Expr);
  
    return code;
}

extern struct BExprRes *doBExpr(struct ExprRes *Res1, struct ExprRes *Res2) {

    struct BExprRes *bRes;
	AppendSeq(Res1->Instrs, Res2->Instrs);
    bRes = (struct BExprRes *) malloc(sizeof(struct BExprRes));
    bRes->Label = GenLabel();
    AppendSeq(Res1->Instrs, GenInstr(NULL, "bne", TmpRegName(Res1->Reg), TmpRegName(Res2->Reg), bRes->Label));
    bRes->Instrs = Res1->Instrs;
    ReleaseTmpReg(Res1->Reg);
  	ReleaseTmpReg(Res2->Reg);
    free(Res1);
    free(Res2);
    return bRes;
}

extern struct InstrSeq *doIf(struct BExprRes *bRes, struct InstrSeq *seq) {
    
    struct InstrSeq * seq2;
    seq2 = AppendSeq(bRes->Instrs, seq);
    AppendSeq(seq2, GenInstr(bRes->Label, NULL, NULL, NULL, NULL));
    free(bRes);
    return seq2;
}

// // --> NOT SURE WHAT THIS IS YET...LEAVE COMMENTED OUT FOR NOW!!!
// extern struct InstrSeq *doIf(struct ExprRes *res1, struct ExprRes *res2, struct InstrSeq *seq) {
//     struct InstrSeq *seq2;
//     char * label;
//     label = GenLabel();
//     AppendSeq(res1->Instrs, res2->Instrs);
//     AppendSeq(res1->Instrs, GenInstr(NULL, "bne", TmpRegName(res1->Reg), TmpRegName(res2->Reg), label));
//     seq2 = AppendSeq(res1->Instrs, seq);
//     AppendSeq(seq2, GenInstr(label, NULL, NULL, NULL, NULL));
//     ReleaseTmpReg(res1->Reg);
//     ReleaseTmpReg(res2->Reg);
//     free(res1);
//     free(res2);
//     return seq2;
// }

void Finish(struct InstrSeq *Code) { 
    
    struct InstrSeq *code;
    // --> NOT SURE WHY THE CODE BELOW IS COMMENTED OUT. CHECK LATER!!!
    // struct SymEntry *entry;
    int hasMore;
    struct Attr * attr;

    code = GenInstr(NULL, ".text", NULL, NULL, NULL);
    // --> NOT SURE WHY THE CODE BELOW IS COMMENTED OUT. CHECK LATER!!!
    // AppendSeq(code,GenInstr(NULL,".align","2",NULL,NULL));
    AppendSeq(code, GenInstr(NULL, ".globl", "main", NULL, NULL));
    AppendSeq(code, GenInstr("main", NULL, NULL, NULL, NULL));
    AppendSeq(code, Code);
    AppendSeq(code, GenInstr(NULL, "li", "$v0", "10", NULL)); 
    AppendSeq(code, GenInstr(NULL, "syscall", NULL, NULL, NULL));
    AppendSeq(code, GenInstr(NULL, ".data", NULL, NULL, NULL));
    AppendSeq(code, GenInstr(NULL, ".align", "4", NULL, NULL));
    AppendSeq(code, GenInstr("_nl", ".asciiz", "\"\\n\"", NULL, NULL));

    // Traverse the symbol table and 
    hasMore = startIterator(table);

    // Traverse the symbol table and add the following assembly code
    // information to each instruction to avoid dropping off of the
    // program.
    while (hasMore) {

        // Add the following code to the instructions in order to 
        // avoid dropping off the program, and move to then next
        // entry in the symbol table.
	    AppendSeq(code, GenInstr((char *) getCurrentName(table), ".word", "0", NULL, NULL));
        hasMore = nextEntry(table);
    }
  
    // Write the obtained data out to a listing 
    // file and return from the function.
    WriteSeq(code);
    return;
}
