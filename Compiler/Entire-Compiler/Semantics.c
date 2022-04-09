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
 * (also called MIPS code) which can be run in a 
 * simulator like the Mars simulator.
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

/* ================================================================== */
/* SECTION FOR INTEGER LITERALS: POSITIVE AND NEGATIVE; RVALUES */
/* ================================================================== */

/**
 * INTEGER LITERAL: POSITIVE
 *
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
 * INTEGER LITERAL: NEGATIVE
 * 
 *  DESCRIPTION...
 */
extern struct ExprRes *doIntLitNeg(char *digits) { 

    // Create a struct of type ExprRes to store 
    // the new instruction being created.
    struct ExprRes *res;
  
    // Allocate space for the struct, find the available registers to
    // use for creation of the instruction, and generate the instruction.
    res = (struct ExprRes *) malloc(sizeof(struct ExprRes));
    res->Reg = AvailTmpReg();
    res->Instrs = GenInstr(NULL, "li", TmpRegName(res->Reg), digits, NULL);
    AppendSeq(res->Instrs, GenInstr(NULL, "mul", TmpRegName(res->Reg), TmpRegName(res->Reg), "-1"));

    // Return the resulting instruction.
    return res;
}

/**
 * LOAD THE WORD (lw)
 *
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

/* ================================================================== */
/* SECTION FOR ARITHMETIC OPERATIONS: ADDITION, SUBTRACTION, */
/* MULTIPLICATION, DIVISION, EXPONENTIATION, AND MODULUS. */ 
/* ================================================================== */

/**
 * ADDITION (add)
 *
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

/**
 * SUBTRACTION (sub)
 * 
 * DESCRIPTION...
 */
struct ExprRes *doSubtraction(struct ExprRes *Res1, struct ExprRes *Res2) { 

    // Create an integer variable to represent 
    // the available temporary registers.
    int reg;
    reg = AvailTmpReg();

    // Call the AppendSeq function to determine what
    // registers are open as well as add the instrutions
    // to the linked list of instructions.
    AppendSeq(Res1->Instrs, Res2->Instrs);
    AppendSeq(Res1->Instrs, GenInstr(NULL, "sub", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));
    
    // Call the functions below to indicate 
    // that the registers used in the "sub" 
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

/**
 * MULTIPLICATION (mul)
 * 
 * The function returns a struct that contains a new
 * instruction generated within the function. The
 * function handles cases where data is being multiplied
 * together. Two integer values are combined in the
 * process of multiplication. The function ensures that
 * the values are multiplied together in a process that 
 * stores the result in a third register. The label
 * for this process is the "mul" label (It stores the
 * data multiplied together via register2 and register3
 * in register1).
 */
struct ExprRes *doMult(struct ExprRes *Res1, struct ExprRes *Res2) { 

    // Create an integer variable to represent 
    // the available temporary registers.
    int reg;
    reg = AvailTmpReg();
    
    // Call the AppendSeq function to determine what
    // registers are open as well as add the instrutions
    // to the linked list of instructions.
    AppendSeq(Res1->Instrs, Res2->Instrs);
    AppendSeq(Res1->Instrs, GenInstr(NULL, "mul", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));
    
    // Call the functions below to indicate 
    // that the registers used in the "mul" 
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

/**
 * DIVISION (div)
 * 
 * DESCRIPTION...
 */
struct ExprRes *doDivide(struct ExprRes *Res1, struct ExprRes *Res2) { 

    // Create an integer variable to represent 
    // the available temporary registers.
    int reg;
    reg = AvailTmpReg();
    
    // Call the AppendSeq function to determine what
    // registers are open as well as add the instrutions
    // to the linked list of instructions.
    AppendSeq(Res1->Instrs, Res2->Instrs);
    AppendSeq(Res1->Instrs, GenInstr(NULL, "div", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));
    
    // Call the functions below to indicate 
    // that the registers used in the "mul" 
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

/**
 * MODULUS (series of instructions)
 * 
 * DESCRIPTION...
 */
extern struct ExprRes *doModulo(struct ExprRes *Res1, struct ExprRes *Res2) {
  
    // Need to do a division, then use mfhi (move from hi) to access the remainder of our operation. This is the modulo.

    int reg;
    reg = AvailTmpReg();

    AppendSeq(Res1->Instrs, Res2->Instrs);
    AppendSeq(Res1->Instrs, GenInstr(NULL, "div", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg))); // We dont care about the quotient
    AppendSeq(Res1->Instrs, GenInstr(NULL, "mfhi", TmpRegName(reg), NULL, NULL));

    ReleaseTmpReg(Res1->Reg);
    ReleaseTmpReg(Res2->Reg);

    Res1->Reg = reg;
    free(Res2);
    return Res1;
}

/**
 * EXPONENTIATION (series of instructions)
 * 
 * DESCRIPTION...
 */
struct ExprRes *doExponential(struct ExprRes *Res1, struct ExprRes *Res2) {

    // In this function, the base is store in Res1->Reg and 
    // the exponent is stored in Res2->Reg. Loop over the
    // exponent and create instructions where we multiply
    // the base by itself.

    // Create three register variables to allocate
    // space for the exponential operation.
    int reg = AvailTmpReg();
    int reg2 = AvailTmpReg();
    int reg3 = AvailTmpReg();

    // Create three new labels using the GenLabel()
    // function. They should be a string (char*).
    char *label = GenLabel();
    char *label2 = GenLabel();
    char *label3 = GenLabel();

    // Call the function to add the two registers representing
    // the expressions to the linked list of instructions.
    AppendSeq(Res1->Instrs, Res2->Instrs);

    // Call the functions to complete the exponentiation operation.
    AppendSeq(Res1->Instrs, GenInstr(NULL, "move", TmpRegName(reg), TmpRegName(Res1->Reg), NULL));
    AppendSeq(Res1->Instrs, GenInstr(NULL, "move", TmpRegName(reg2), TmpRegName(Res2->Reg), NULL));
    AppendSeq(Res1->Instrs, GenInstr(NULL, "move", TmpRegName(reg3), TmpRegName(Res2->Reg), NULL));
    AppendSeq(Res1->Instrs, GenInstr(NULL, "sub", TmpRegName(reg3), TmpRegName(reg3), "1"));

    // Create a branch instruction and subtract one from the counter variable 
    // stored in the register. This helps complete the process of looping and
    // multiplying repeatedly.
    AppendSeq(Res1->Instrs, GenInstr(NULL, "beq", "$zero", TmpRegName(reg3), label3));
    AppendSeq(Res1->Instrs, GenInstr(NULL, "sub", TmpRegName(reg2), TmpRegName(reg2), "1"));
    AppendSeq(Res1->Instrs, GenInstr(label, NULL, NULL, NULL, NULL));
    AppendSeq(Res1->Instrs, GenInstr(NULL, "beq", "$zero", TmpRegName(reg2), label2));
    AppendSeq(Res1->Instrs, GenInstr(NULL, "mul", TmpRegName(reg), TmpRegName(reg), TmpRegName(Res1->Reg)));
    AppendSeq(Res1->Instrs, GenInstr(NULL, "sub", TmpRegName(reg2), TmpRegName(reg2), "1"));
    AppendSeq(Res1->Instrs, GenInstr(NULL, "j", label, NULL, NULL));
    AppendSeq(Res1->Instrs, GenInstr(label3, NULL, NULL, NULL, NULL));
    AppendSeq(Res1->Instrs, GenInstr(NULL, "move", TmpRegName(reg), TmpRegName(Res1->Reg), NULL));
    AppendSeq(Res1->Instrs, GenInstr(label2, NULL, NULL, NULL, NULL));

    // Release all of the registers after use.
    ReleaseTmpReg(Res1->Reg);
    ReleaseTmpReg(Res2->Reg);
    ReleaseTmpReg(reg2);
    ReleaseTmpReg(reg3);

    // Set the first register equal to the first reg variable, free
    // the second register struct, and return from the function.
    Res1->Reg = reg;
    free(Res2);
    return Res1;
}

/* ================================================================== */
/* SECTION FOR PRINTING OUT CONTENT AND ASSIGNING VARIABLES: PRINT, */ 
/* PRINTLINES, PRINTSPACES, READ, AND ASSIGNMENT */
/* ================================================================== */

/**
 * PRINT (series of instructions)
 * 
 * The function returns a struct that contains a new
 * instruction generated within the function. The
 * function handles cases where the data needs to be
 * printed out to the console (usually in an editor).
 * There are a series of instructions that are used
 * to print out values in assembly. Labels like "li",
 * "la", "move", and "syscall" are used for this process.
 */
// --> YOU WILL NEED TO CHANGE THIS AND MAKE IT SO
// --> THAT THERE CAN BE MULTIPLE EXPRESSIONS PRINTED.
// --> TO DO THIS, YOU MAY NEED TO CHANGE THE PARAMETER
// --> AND 
struct InstrSeq *doPrint(struct ExprRes *Expr) { 

    // Create a struct of type ExprRes to store
    // the new instruction being created.
    struct InstrSeq *code;
    
    // Store the instruction in the expression result
    // within the code variable that was created.
    code = Expr->Instrs;
  
    // Add the MIPS assembly code to the linked list of instructions.
    AppendSeq(code, GenInstr(NULL, "li", "$v0", "1", NULL));
    AppendSeq(code, GenInstr(NULL, "move", "$a0", TmpRegName(Expr->Reg), NULL));
    AppendSeq(code, GenInstr(NULL, "syscall", NULL, NULL, NULL));

    // Add more MIPS assembly code to complete the process of adding
    // the proper procedures to enable printing out to the screen.
    AppendSeq(code, GenInstr(NULL, "li", "$v0", "4", NULL));
    AppendSeq(code, GenInstr(NULL, "la", "$a0", "_nl", NULL));
    AppendSeq(code, GenInstr(NULL, "syscall", NULL, NULL, NULL));

    // Call the functions below to indicate 
    // that the registers used in the print 
    // operation are now free to use again. 
    ReleaseTmpReg(Expr->Reg);
    free(Expr);

    // Return the code variable with the instruction data.
    return code;
}

// // --> THIS MAY BE THE PRINT THAT YOU WILL ACTUALLY WANT TO USE!!!
// struct InstrSeq *doPrint(struct Node *node) {

//     struct InstrSeq *code = (struct InstrSeq *)malloc(sizeof(struct InstrSeq));
//     struct Node *curr = node;

//     while (curr) {

//         struct ExprRes *currInstr = (struct ExprRes *)curr->name;

//         AppendSeq(code, currInstr->Instrs);
//         AppendSeq(code, GenInstr(NULL, "li", "$v0", "1", NULL));
//         AppendSeq(code, GenInstr(NULL, "move", "$a0", TmpRegName(currInstr->Reg), NULL));
//         AppendSeq(code, GenInstr(NULL, "syscall", NULL, NULL, NULL));

//         ReleaseTmpReg(currInstr->Reg);
//         free(currInstr);
//         curr = curr->next;
//     }

//     return code;
// }

/**
 * PRINTLINES (series of instructions)
 * 
 * DESCRIPTION...
 */
extern struct InstrSeq *doPrintlines(struct ExprRes *Res) {

    struct InstrSeq *code = (struct InstrSeq *)malloc(sizeof(struct InstrSeq));
    int reg = AvailTmpReg();
    AppendSeq(code, Res->Instrs);
    AppendSeq(code, GenInstr(NULL, "move", TmpRegName(reg), TmpRegName(Res->Reg), NULL));

    char *label = GenLabel();
    char *label2 = GenLabel();

    AppendSeq(code, GenInstr(NULL, "beq", "$zero", TmpRegName(reg), label2));
    AppendSeq(code, GenInstr(label, NULL, NULL, NULL, NULL)); // Label to jump back to, based on amount of new lines desired;

    AppendSeq(code, GenInstr(NULL, "li", "$v0", "4", NULL));
    AppendSeq(code, GenInstr(NULL, "la", "$a0", "_nl", NULL));
    AppendSeq(code, GenInstr(NULL, "syscall", NULL, NULL, NULL));

    AppendSeq(code, GenInstr(NULL, "sub", TmpRegName(reg), TmpRegName(reg), "1"));
    AppendSeq(code, GenInstr(NULL, "bne", "$zero", TmpRegName(reg), label));
    AppendSeq(code, GenInstr(label2, NULL, NULL, NULL, NULL));

    ReleaseTmpReg(reg);
    ReleaseTmpReg(Res->Reg);

    free(Res);

    return code;
}

/**
 * PRINTSPACES (series of instructions)
 * 
 * DESCRIPTION...
 */
extern struct InstrSeq *doPrintspaces(struct ExprRes *Res) {
    
    struct InstrSeq *code = (struct InstrSeq *)malloc(sizeof(struct InstrSeq));
    int reg = AvailTmpReg();
    
    AppendSeq(code, Res->Instrs);
    AppendSeq(code, GenInstr(NULL, "move", TmpRegName(reg), TmpRegName(Res->Reg), NULL));

    char *label = GenLabel();
    char *label2 = GenLabel();

    AppendSeq(code, GenInstr(NULL, "beq", "$zero", TmpRegName(reg), label2));
    AppendSeq(code, GenInstr(label, NULL, NULL, NULL, NULL)); // Label to jump back to, based on amount of new lines desired;

    AppendSeq(code, GenInstr(NULL, "li", "$v0", "4", NULL));
    AppendSeq(code, GenInstr(NULL, "la", "$a0", "_space", NULL));
    AppendSeq(code, GenInstr(NULL, "syscall", NULL, NULL, NULL));

    AppendSeq(code, GenInstr(NULL, "sub", TmpRegName(reg), TmpRegName(reg), "1"));
    AppendSeq(code, GenInstr(NULL, "bne", "$zero", TmpRegName(reg), label));
    AppendSeq(code, GenInstr(label2, NULL, NULL, NULL, NULL));

    ReleaseTmpReg(reg);
    ReleaseTmpReg(Res->Reg);

    free(Res);
    return code;
}

/**
 * READ (series of instructions)
 * 
 * DESCRIPTION...
 */
extern struct InstrSeq *doRead(struct Node *node) {
  
    struct InstrSeq *code = (struct InstrSeq *)malloc(sizeof(struct InstrSeq));
    struct Node *curr = node;

    while (curr) {

        AppendSeq(code, GenInstr(NULL, "li", "$v0", "5", NULL));
        AppendSeq(code, GenInstr(NULL, "syscall", NULL, NULL, NULL));
        AppendSeq(code, GenInstr(NULL, "sw", "$v0", (char *)curr->name, NULL));

        curr = curr->next;
    }

    return code;
}

/**
 * ASSIGNMENT (sw)
 * 
 * The function returns a struct that contains a new
 * instruction generated within the function. The
 * function handles cases where the data needs to be
 * assigned to a variable. The label for this process
 * is the "sw" label (It stores the data in memory).
 */
struct InstrSeq *doAssign(char *name, struct ExprRes *Expr) { 

    // Create a struct of type InstrSeq to store
    // the new instruction being created.
    struct InstrSeq *code;
  
    // If the variable name that is being assigned a value
    // through this function is not in the symbol table,
    // write out a message to indicate that.
    if(!findName(table, name)) {
		writeIndicator(getCurrentColumnNum());
		writeMessage("Undeclared variable");
    }

    // Set the code variable value equal to the
    // instruction component of the expression.
    code = Expr->Instrs;
  
    // Call the function to add the instruction data to the 
    // code variable. The assignment involves the use of the 
    // "sw" (store word) assembly label.
    AppendSeq(code, GenInstr(NULL, "sw", TmpRegName(Expr->Reg), name, NULL));

    // Free up the register used and free 
    // the Expr struct that was used. 
    ReleaseTmpReg(Expr->Reg);
    free(Expr);
  
    // Return the code variable with the instruction data.
    return code;
}

/* ================================================================== */
/* SECTION FOR COMPARING EXPRESSIONS: EQUAL, NOT EQUAL, LESS THAN OR */
/* EQUAL TO, GREATER THAN OR EQUAL TO, LESS THAN, AND GREATER THAN. */
/* ================================================================== */

// /**
//  * The function returns a struct that contains a new
//  * instruction generated within the function. The
//  * function handles cases where there is a branch in
//  * the code. In this particular case, the branch occurs
//  * when there are two values that are not equal. The 
//  * label for this process is the "bne" label (branch
//  * if not equal).
//  */
// extern struct BExprRes *doBExpr(struct ExprRes *Res1, struct ExprRes *Res2) {

//     // Create a variable of type BExprRes.
//     // This stores the branch instruction.
//     struct BExprRes *bRes;
	
//     // Using the AppendSeq function, add the 
//     // Res1 and Res2 instructions to the main
//     // linked list of instructions.
//     AppendSeq(Res1->Instrs, Res2->Instrs);
    
//     // Create space for the instruction that will be
//     // generated. Create a label for the instruction.
//     bRes = (struct BExprRes *) malloc(sizeof(struct BExprRes));
//     bRes->Label = GenLabel();
    
//     // Call the AppendSeq function again to add the 
//     // newly formed instruction to the linked list
//     // of instructions. Set the instruction part 
//     // of the bRes variable to the instruction 
//     // component of Res1.
//     AppendSeq(Res1->Instrs, GenInstr(NULL, "bne", TmpRegName(Res1->Reg), TmpRegName(Res2->Reg), bRes->Label));
//     bRes->Instrs = Res1->Instrs;
    
//     // Release the temporary registers 
//     // for reuse after the instruction 
//     // is created with the registers.
//     ReleaseTmpReg(Res1->Reg);
//   	ReleaseTmpReg(Res2->Reg);
    
//     // Free the structs used for the 
//     // registers to free up memory. 
//     free(Res1);
//     free(Res2);

//     // Return the bRes variable 
//     // from the function.
//     return bRes;
// }

/**
 * EQUAL (seq)
 * 
 * DESCRIPTION...
 */
extern struct ExprRes *doBExprEq(struct ExprRes *Res1, struct ExprRes *Res2) {
    
    struct ExprRes *Res;
    int reg = AvailTmpReg();

    AppendSeq(Res1->Instrs, Res2->Instrs);
    Res = (struct ExprRes *)malloc(sizeof(struct ExprRes));
    AppendSeq(Res1->Instrs, GenInstr(NULL, "seq", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));

    Res->Reg = reg;
    Res->Instrs = Res1->Instrs;

    ReleaseTmpReg(Res1->Reg);
    ReleaseTmpReg(Res2->Reg);

    free(Res1);
    free(Res2);

    return Res;
}

/**
 * NOT EQUAL (sne)
 * 
 * DESCRIPTION...
 */
extern struct ExprRes *doBExprNotEq(struct ExprRes *Res1, struct ExprRes *Res2) {
    
    struct ExprRes *Res;
    int reg = AvailTmpReg();

    AppendSeq(Res1->Instrs, Res2->Instrs);
    Res = (struct ExprRes *)malloc(sizeof(struct ExprRes));
    AppendSeq(Res1->Instrs, GenInstr(NULL, "sne", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));

    Res->Reg = reg;
    Res->Instrs = Res1->Instrs;

    ReleaseTmpReg(Res1->Reg);
    ReleaseTmpReg(Res2->Reg);

    free(Res1);
    free(Res2);

    return Res;
}

/**
 * LESS THAN OR EQUAL TO (sle)
 * 
 * DESCRIPTION...
 */
extern struct ExprRes *doBExprLtOrEq(struct ExprRes *Res1, struct ExprRes *Res2) {
    
    struct ExprRes *Res;
    int reg = AvailTmpReg();

    AppendSeq(Res1->Instrs, Res2->Instrs);
    Res = (struct ExprRes *)malloc(sizeof(struct ExprRes));
    AppendSeq(Res1->Instrs, GenInstr(NULL, "sle", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));

    Res->Reg = reg;
    Res->Instrs = Res1->Instrs;

    ReleaseTmpReg(Res1->Reg);
    ReleaseTmpReg(Res2->Reg);

    free(Res1);
    free(Res2);
    
    return Res;
}

/**
 * GREATER THAN OR EQUAL TO (sge)
 * 
 * DESCRIPTION...
 */
extern struct ExprRes *doBExprGtOrEq(struct ExprRes *Res1, struct ExprRes *Res2) {

    struct ExprRes *Res;
    int reg = AvailTmpReg();

    AppendSeq(Res1->Instrs, Res2->Instrs);
    Res = (struct ExprRes *)malloc(sizeof(struct ExprRes));
    AppendSeq(Res1->Instrs, GenInstr(NULL, "sge", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));

    Res->Reg = reg;
    Res->Instrs = Res1->Instrs;

    ReleaseTmpReg(Res1->Reg);
    ReleaseTmpReg(Res2->Reg);

    free(Res1);
    free(Res2);
    return Res;
}

/**
 * LESS THAN (slt)
 * 
 * DESCRIPTION...
 */
extern struct ExprRes *doBExprLt(struct ExprRes *Res1, struct ExprRes *Res2) {
   
    struct ExprRes *Res;
    int reg = AvailTmpReg();

    AppendSeq(Res1->Instrs, Res2->Instrs);
    Res = (struct ExprRes *)malloc(sizeof(struct ExprRes));
    AppendSeq(Res1->Instrs, GenInstr(NULL, "slt", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));

    Res->Reg = reg;
    Res->Instrs = Res1->Instrs;

    ReleaseTmpReg(Res1->Reg);
    ReleaseTmpReg(Res2->Reg);

    free(Res1);
    free(Res2);
    return Res;
}

/**
 * GREATER THAN (sgt)
 * 
 * DESCRIPTION...
 */
extern struct ExprRes *doBExprGt(struct ExprRes *Res1, struct ExprRes *Res2) {
    
    struct ExprRes *Res;
    int reg = AvailTmpReg();

    AppendSeq(Res1->Instrs, Res2->Instrs);
    Res = (struct ExprRes *)malloc(sizeof(struct ExprRes));
    AppendSeq(Res1->Instrs, GenInstr(NULL, "sgt", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));

    Res->Reg = reg;
    Res->Instrs = Res1->Instrs;
    
    ReleaseTmpReg(Res1->Reg);
    ReleaseTmpReg(Res2->Reg);

    free(Res1);
    free(Res2);
    return Res;
}

/* ================================================================== */
/* SECTION FOR BOOLEAN EXPRESSIONS: NEGATION, OR, AND AND. */
/* ================================================================== */

/**
 * NEGATION (series of instructions)
 * 
 * DESCRIPTION...
 */
extern struct ExprRes *doNegate(struct ExprRes *Res1) {
  
    struct ExprRes *Res;
    int reg = AvailTmpReg();

    Res = (struct ExprRes *)malloc(sizeof(struct ExprRes));
    AppendSeq(Res1->Instrs, GenInstr(NULL, "not", TmpRegName(reg), TmpRegName(Res1->Reg), NULL));

    // This next bit should (ideally) clear all of the garbage bits
    // --> THIS MAY BE INCORRECT!!!
    AppendSeq(Res1->Instrs, GenInstr(NULL, "sll", TmpRegName(reg), TmpRegName(reg), "31"));
    AppendSeq(Res1->Instrs, GenInstr(NULL, "srl", TmpRegName(reg), TmpRegName(reg), "31"));

    Res->Reg = reg;
    Res->Instrs = Res1->Instrs;
    ReleaseTmpReg(Res1->Reg);

    free(Res1);
    return Res;
}

/**
 * OR (series of instructions)
 * 
 * DESCRIPTION...
 */
extern struct ExprRes *doOr(struct ExprRes *Res1, struct ExprRes *Res2) {
    
    struct ExprRes *Res;
    int reg = AvailTmpReg();

    Res = (struct ExprRes *)malloc(sizeof(struct ExprRes));
    AppendSeq(Res1->Instrs, Res2->Instrs);
    AppendSeq(Res1->Instrs, GenInstr(NULL, "or", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));

    AppendSeq(Res1->Instrs, GenInstr(NULL, "sll", TmpRegName(reg), TmpRegName(reg), "31"));
    AppendSeq(Res1->Instrs, GenInstr(NULL, "srl", TmpRegName(reg), TmpRegName(reg), "31"));

    Res->Reg = reg;
    Res->Instrs = Res1->Instrs;
    ReleaseTmpReg(Res1->Reg);
    ReleaseTmpReg(Res2->Reg);

    free(Res1);
    free(Res2);
    return Res;
}

/**
 * AND (series of instructions)
 * 
 * DESCRIPTION...
 */
extern struct ExprRes *doAnd(struct ExprRes *Res1, struct ExprRes *Res2) {
   
    struct ExprRes *Res;
    int reg = AvailTmpReg();

    Res = (struct ExprRes *)malloc(sizeof(struct ExprRes));
    AppendSeq(Res1->Instrs, Res2->Instrs);
    AppendSeq(Res1->Instrs, GenInstr(NULL, "and", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));

    // I'm leaving this here in case I find out I need to do this in the future...
    // AppendSeq(Res1->Instrs, GenInstr(NULL, "sll", TmpRegName(reg), TmpRegName(reg), "31"));
    // AppendSeq(Res1->Instrs, GenInstr(NULL, "srl", TmpRegName(reg), TmpRegName(reg), "31"));

    Res->Reg = reg;
    Res->Instrs = Res1->Instrs;
    ReleaseTmpReg(Res1->Reg);
    ReleaseTmpReg(Res2->Reg);

    free(Res1);
    free(Res2);
    return Res;
}

/* ================================================================== */
/* SECTION FOR CONDITIONALS AND LOOPS: IF, IF-ELSE, WHILE, AND FOR. */
/* ================================================================== */

// /**
//  * IF (series of instructions)
//  * 
//  * The function returns a struct that contains a new
//  * instruction generated within the function. The
//  * function handles cases where there is a conditional
//  * statement in the C-like code (if-statement).
//  */
// extern struct InstrSeq *doIf(struct ExprRes *Res, struct InstrSeq *seq) {
    
//     // Create a struct of type InstrSeq to store
//     // the new instruction being created.
//     struct InstrSeq * seq2;

//     // Call the AppendSeq function in order to
//     // store the instruction data and add it
//     // to the linked list of instructions.
//     seq2 = AppendSeq(Res->Instrs, seq);
//     AppendSeq(seq2, GenInstr(Res->Label, NULL, NULL, NULL, NULL));
    
//     // Free the branch register used to 
//     // free up memory space and return
//     // the variable from the function.
//     free(Res);
//     return seq2;
// }

// --> MAY ACTUALLY WANT TO USE THIS FOR YOUR IF CASE!!!
extern struct InstrSeq *doIf(struct ExprRes *Res, struct InstrSeq *seq) {

    struct InstrSeq *seq2;
    char *label = GenLabel();
    AppendSeq(Res->Instrs, GenInstr(NULL, "beq", "$zero", TmpRegName(Res->Reg), label));
    seq2 = AppendSeq(Res->Instrs, seq);
    AppendSeq(seq2, GenInstr(label, NULL, NULL, NULL, NULL));
    free(Res);
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

/**
 * IF-ELSE (series of instructions)
 * 
 * DESCRIPTION...
 */
extern struct InstrSeq *doIfElse(struct ExprRes *Res, struct InstrSeq *seq1, struct InstrSeq *seq2) {
   
    struct InstrSeq *code;
    char *label1 = GenLabel();
    char *label2 = GenLabel();

    AppendSeq(Res->Instrs, GenInstr(NULL, "beq", "$zero", TmpRegName(Res->Reg), label1));
    code = AppendSeq(Res->Instrs, seq1);

    AppendSeq(code, GenInstr(label1, NULL, NULL, NULL, NULL));
    AppendSeq(code, GenInstr(NULL, "bne", "$zero", TmpRegName(Res->Reg), label2));
    AppendSeq(code, seq2);
    AppendSeq(code, GenInstr(label2, NULL, NULL, NULL, NULL));

    free(Res);
    return code;
}

/**
 * WHILE (series of instructions)
 * 
 * DESCRIPTION...
 */
extern struct InstrSeq *doWhile(struct ExprRes *Res, struct InstrSeq *seq) {
   
    struct InstrSeq *code = (struct InstrSeq *)malloc(sizeof(struct InstrSeq));
    char *label1 = GenLabel();
    char *label2 = GenLabel();

    AppendSeq(code, GenInstr(label1, NULL, NULL, NULL, NULL));
    AppendSeq(code, Res->Instrs);
    AppendSeq(code, GenInstr(NULL, "beq", "$zero", TmpRegName(Res->Reg), label2));
    AppendSeq(code, seq);
    AppendSeq(code, GenInstr(NULL, "j", label1, NULL, NULL));
    AppendSeq(code, GenInstr(label2, NULL, NULL, NULL, NULL));

    free(Res);
    return code;
}

/**
 * FOR (series of instructions)
 * 
 * DESCRIPTION...
 */
extern struct InstrSeq *doFor(struct InstrSeq *Assignment1, struct ExprRes *CondRes, struct InstrSeq *Assignment2, struct InstrSeq *seq) {
    
    struct InstrSeq *code = (struct InstrSeq *)malloc(sizeof(struct InstrSeq));
    char *label1 = GenLabel();
    char *label2 = GenLabel();

    AppendSeq(code, Assignment1);
    AppendSeq(code, GenInstr(label1, NULL, NULL, NULL, NULL));
    AppendSeq(code, CondRes->Instrs);
    AppendSeq(code, GenInstr(NULL, "beq", "$zero", TmpRegName(CondRes->Reg), label2));
    AppendSeq(code, seq);
    AppendSeq(code, Assignment2);
    AppendSeq(code, GenInstr(NULL, "j", label1, NULL, NULL));
    AppendSeq(code, GenInstr(label2, NULL, NULL, NULL, NULL));

    ReleaseTmpReg(CondRes->Reg);
    free(CondRes);
    return code;
}

/* ================================================================== */
/* SECTION FOR ADDING ARGUMENTS AND EXPRESSIONS TO LISTS: APPEND TO */
/* ARGUMENT LIST, AND APPEND TO EXPRESSION LIST. */
/* ================================================================== */

/**
 * APPEND TO ARGUMENT LIST
 * 
 * DESCRIPTION...
 */
extern struct Node *appendToArgList(char *c, struct Node *next) {
    
    struct Node *curr = (struct Node *)malloc(sizeof(struct Node));

    curr->name = strdup(c);
    curr->next = next;

    return curr;
}

/**
 * APPEND TO EXPRESSION LIST
 * 
 * DESCRIPTION...
 */
extern struct Node *appendToExprList(struct ExprRes *Res1, struct Node *next) {
   
    struct Node *curr = (struct Node *)malloc(sizeof(struct Node));

    curr->name = Res1;
    curr->next = next;

    return curr;
}

/* ================================================================== */
/* SECTION FOR FINAL ASSEMBLY COMPONENTS: FINISH. */
/* ================================================================== */

/**
 * FINISH (series of instructions)
 * 
 *  The function finalizes the process of creating
 * assembly code for a given C-like program that
 * is compiled. This function is typically called
 * at the end of the compilation process to ensure
 * that the file format of each assembly program
 * is syntactically correct. The function helps
 * generate a complete file that can be run in 
 * a simulator like the Mars environment.
 */
void Finish(struct InstrSeq *Code) { 
    
    // Create a struct of type InstrSeq to store
    // the new instruction being created.
    struct InstrSeq *code;

    // --> NOT SURE WHY THE CODE BELOW IS COMMENTED OUT. CHECK LATER!!!
    // struct SymEntry *entry;
    
    // Create a variable to track iteration through the
    // symbol table. Create another variable of type 
    // struct Attr to track the attributes in the table.
    int hasMore;
    struct Attr *attr;

    // Generate an instruction with the ".text" keyword
    // at the top of the file. 
    code = GenInstr(NULL, ".text", NULL, NULL, NULL);

    // --> NOT SURE WHY THE CODE BELOW IS COMMENTED OUT. CHECK LATER!!!
    // AppendSeq(code,GenInstr(NULL,".align","2",NULL,NULL));
    
    // Call the AppendSeq functions to display the heading
    // content at the top of each assembly file created at
    // the end of the compiling process.
    AppendSeq(code, GenInstr(NULL, ".globl", "main", NULL, NULL));
    AppendSeq(code, GenInstr("main", NULL, NULL, NULL, NULL));
    AppendSeq(code, Code);
    AppendSeq(code, GenInstr(NULL, "li", "$v0", "10", NULL)); 
    AppendSeq(code, GenInstr(NULL, "syscall", NULL, NULL, NULL));
    AppendSeq(code, GenInstr(NULL, ".data", NULL, NULL, NULL));
    AppendSeq(code, GenInstr(NULL, ".align", "4", NULL, NULL));
    AppendSeq(code, GenInstr("_nl", ".asciiz", "\"\\n\"", NULL, NULL));

    // Start traversing the symbol table by
    // calling the startIterator() function.
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
