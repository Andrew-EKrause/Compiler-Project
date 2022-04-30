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
 * ================================================
 * 
 * C-like program is compiled into assembly code,
 * (also called MIPS code) which can be run in a 
 * simulator like the Mars simulator.
 * 
 * ================================================
 * 
 * NOTE: The order of the functions in this file
 * follow the order of productions (from top to 
 * bottom) of the grammar in the ExprEval.y file.
 * However, there are a few functions that are 
 * out of order in this file compared to the grammar
 * listed in the YACC file.
 * 
 * ================================================
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
#include <string.h>
#include <stdlib.h>

// Include the .h files needed to 
// complete the compilation process.
#include "SymTab.h"
#include "IOMngr.h"
#include "CodeGen.h"
#include "Semantics.h"

// Create an external global symbol table for
// memory management of the variable values.
extern SymTab *table;

// Create a global list of strings in order
// to print strings out in the C-like language.
struct StringItem *listOfStrings;

// Create a global list of arrays in order
// to store arrays befoe using them in the 
// C-like language.
struct ArrayItem *listOfArrays;

/* ========================== */
/* Semantics support routines */
/* ========================== */

/* ================================================================== */
/* SECTION FOR FINAL ASSEMBLY COMPONENTS: FINISH AND ENTER NAME. */
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

    // --> Not sure why I put code below. Use for functions maybe later.
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
    AppendSeq(code, GenInstr("_spc", ".asciiz", "\" \"", NULL, NULL));

    // ======================================================
    // Load the arrays into the data section of the MIPS
    // code before the MIPS program is run.
    // ======================================================

    // Create two struct variables for traversing through the
    // global list of arrays in the "listOfArrays" variable.
    struct ArrayItem *arrayItem;
    struct ArrayItem *nextArray;

    // Create string variables (char*) in order to 
    // add numerical values to the instructions.
    char *totalArraySize = NULL;
    totalArraySize = malloc(100 * sizeof(totalArraySize));

    // Assign the "arrayItem" struct to the global variable 
    // to begin the process of traversing through the list
    // of array values.
    arrayItem = listOfArrays;

    // Loop through the list of arrays and put each array declaration 
    // in the global/data section of the MIPS assembly code in the file. 
    // Essentially, you are adding each array value in the linked list 
    // of arrays to the global/data section of the assembly code to 
    // reserve space for it.
    while(arrayItem) {

        // Call the function to store the list of array values in the 
        // global/data section of the MIPS assembly code. These values
        // are loaded and ready to use at compile time. A shift-left
        // logical operation is performed to ensure that a proper amount
        // of space is allocated.
        sprintf(totalArraySize, "%d", (arrayItem->Size1 * arrayItem->Size2)<<2);
        AppendSeq(code, GenInstr(arrayItem->ArrayName, ".space", totalArraySize, NULL, NULL));
        
        // Move to the next array value
        // in the list of arrays.
        nextArray = arrayItem;
        arrayItem = arrayItem->Next;

        // Free the different attributes in the 
        // StringItem struct in each iteration.
        free(nextArray->ArrayLabel);
        free(nextArray);
    }

    // Free the total array size variable after 
    // loading all of the arrays into the .data
    // segment.
    free(totalArraySize);

    // ======================================================
    // Load the strings into the data section of the MIPS
    // code before the MIPS program is run.
    // ======================================================

    // Create two struct variables for traversing through the
    // global list of strings in the "listOfStrings" variable.
    struct StringItem *stringItem;
    struct StringItem *nextString;

    // Assign the "stringItem" struct to the global variable
    // to begin the process of traversing though the list of
    // string values.
    stringItem = listOfStrings;

    // Loop through the list of strings and put each string 
    // literal in the global/data section of the MIPS assembly
    // code in the file. Essentially, you are adding each string
    // value in the linked list of strings to the global/data
    // section of the assembly code.
    while(stringItem) {

        // Call the function to store the list of string values in the 
        // global/data section of the MIPS assembly code. These values
        // are loaded and ready to use at compile time.
        AppendSeq(code, GenInstr(stringItem->StringLabel, ".asciiz", stringItem->String, NULL, NULL));
        
        // Move to the next string value
        // in the list of strings.
        nextString = stringItem;
        stringItem = stringItem->Next;

        // Free the different attributes in the 
        // StringItem struct in each iteration.
        free(nextString->String);
        free(nextString->StringLabel);
        free(nextString);
    }

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

/**
 * ENTER NAME (WITH FREE)
 * 
 * The function enters a name into the symbol table,
 * and then frees the name variable in order to 
 * help in the process of maintaining a clean memory
 * in the compilation process.
 */
void enterNameAndFreeDec(SymTab *table, char *name) {

    // The name into the symbol table, and 
    // then free the name in order to help
    // in maintaining clean memory.
    enterName(table, name);
    free(name);
}

/* ================================================================== */
/* SECTION FOR PRINTING OUT EXPESSIONS READING, AND ASSIGNING VARIABLES: */ 
/* PRINTEXPRESSIONS, PRINTSTRINGS, PRINTLINES, PRINTSPACES AND READ */
/* ================================================================== */

/**
 * PRINT and PRINT EXPRESSIONS
 * 
 * The function returns a struct that contains a new
 * instruction generated within the function. The
 * function handles cases where the data needs to be
 * printed out to the console (usually in an editor).
 * There are a series of instructions that are used
 * to print out values in assembly. Labels like "li",
 * "la", "move", and "syscall" are used for this process.
 * The function handles cases when users want to print 
 * out a single item or multiple items. 
 */
extern struct InstrSeq *doPrintExpressions(struct ExprResList *list) {

    // Create a variable of type instruction sequence, an expression
    // list variable, and a variable to represent a boolean.
    struct InstrSeq *resultInstruction = NULL;
    struct ExprResList *listOfExprs = list;

    // --> NOTES:
    // --> 1 is the syscall number for printing an integer.
    // --> 11 is the syscall number for printing a character.
    // --> 32 is the ASCII character for a space. I use "_spc" here instead.

    // Loop through the list of expressions and add assembly code to 
    // the linked list of instructions to print out each item in the
    // expression.
    while(listOfExprs) {

        // Set the variable equal to the call for adding the instructions to the 
        // linked list of instructions.
        resultInstruction = AppendSeq(resultInstruction, listOfExprs->Expr->Instrs);

        // Call the function multiple times to print out a given item in the expression.
        AppendSeq(resultInstruction, GenInstr(NULL, "add", "$a0", TmpRegName(listOfExprs->Expr->Reg), "$zero"));
        AppendSeq(resultInstruction, GenInstr(NULL, "li", "$v0", "1", NULL));
        AppendSeq(resultInstruction, GenInstr(NULL, "syscall", NULL, NULL, NULL));

        // Call the function multiple times to print out a space in
        // order to separate item being printed out in the expression.
        AppendSeq(resultInstruction, GenInstr(NULL, "li", "$v0", "11", NULL));
        AppendSeq(resultInstruction, GenInstr(NULL, "la", "$a0", "_spc", NULL));
        AppendSeq(resultInstruction, GenInstr(NULL, "syscall", NULL, NULL, NULL));

        // Release the temporary registers so that they
        // can be used again, and free the list of 
        // expressions struct.
        ReleaseTmpReg(listOfExprs->Expr->Reg);
        free(listOfExprs->Expr);

        // Move to the next item in the list of expressions.
        list = listOfExprs;
        listOfExprs = listOfExprs->Next;
        free(list); // --> KEEP AN EYE ON THIS ONE!!!
    }

    // Return the resulting instructions.
    return resultInstruction;
}

/**
 * {PRINT and PRINT EXPRESSIONS} - HELPER FUNCTION
 * 
 * The function is used to help complete the 
 * PRINT and PRINT EXPRESSION functionalities
 * of the compiler. The function creates a 
 * list of items that can then be passed into
 * the doPrintExpression() function to be
 * printed out.
 */
extern struct ExprResList *createExprList(struct ExprRes *res, struct ExprResList *list) {

    // Create a struct of type ExprResList. Allocate space for the struct.
    struct ExprResList *resultExpr = malloc(sizeof(struct ExprResList));

    // Add the item, an expression, to the list of expressions
    // that will be read in by the doPrintExpressions function.
    resultExpr->Expr = res;
    resultExpr->Next = list;

    // Return the resulting list of expressions
    // from the function.
    return resultExpr;
}

/**
 * PRINT STRINGS
 * 
 * The function is used to enable the functionality
 * of printing out a string literal using a function
 * in the C-like language. The function uses a global
 * variable of type StringItem to store the string
 * values along with assembly instructions that are
 * generated. The variable of StringItem will be used
 * later on in the Finish() function. 
 */
extern struct InstrSeq *doPrintStrings(char *stringValue) {

    // Create a struct of type StringItem and allocate space for it. The
    // struct is used to store each string literal that the user wants to
    // print out.
    struct StringItem *resultString = malloc(sizeof(struct StringItem));

    // Set each attribute of the StringItem struct.
    // Each attribute ensures that a given string 
    // literal is properly processed and prepared 
    // to be converted to the MIPS assembly code.
    resultString->String = stringValue;
    resultString->Next = listOfStrings;
    resultString->StringLabel = GenerateStringLabel();
    listOfStrings = resultString;

    // Create a new struct of type InstrSeq, and append instructions
    // to it that will print out a string value in MIPS assembly code.
    struct InstrSeq *code = NULL;
    code = AppendSeq(code, GenInstr(NULL, "li", "$v0", "4", NULL));
    AppendSeq(code, GenInstr(NULL, "la", "$a0", resultString->StringLabel, NULL));
    AppendSeq(code, GenInstr(NULL, "syscall", NULL, NULL, NULL));

    // Return the resulting list of strings 
    // from the function. The list of strings 
    // will be visited in the Finish() function
    // and placed in the global/data section 
    // of the MIPS assembly file.
    return code;
}

/**
 * PRINT LINES and PRINT SPACES
 * 
 * The function handles cases when the user wants to
 * print a newline or a space in the C-like language
 * via the printlines() and printspaces() functions
 * specified in the ExprEval.y file grammar. The 
 * function can print out a newline or a space given
 * the use of an enum, PrintExprOps, which is included 
 * in the parameters of the function.
 */
extern struct InstrSeq *doPrintformat(struct ExprRes *Res, enum PrintExprOps printType) {

    // Create a struct of type InstrSeq to store
    // the assembly instructions that are being
    // generated by the function. Also create
    // a variable to use the available registers.
    struct InstrSeq *code = Res->Instrs;
    int reg = AvailTmpReg();

    // AppendSeq(code, Res->Instrs); // --> DO NOT NEED THIS???

    // Call the function to move the value passed in as a parameter 
    // into an available register. These instructions are then added
    // to the linked list of instructions that will be returned.
    AppendSeq(code, GenInstr(NULL, "move", TmpRegName(reg), TmpRegName(Res->Reg), NULL));

    // Create two labels using the GenLabel() function.
    // This helps to print out the correct number of 
    // newlines or spaces.
    char *label1 = GenLabel();
    char *label2 = GenLabel();

    // Call the function multiple times to create a branch
    // instruction to help loop through and print out the
    // correct number of specified newlines or spaces.
    AppendSeq(code, GenInstr(NULL, "beq", "$zero", TmpRegName(reg), label2));
    AppendSeq(code, GenInstr(label1, NULL, NULL, NULL, NULL)); // Label to jump back to, based on amount of new lines or spaces desired.
    AppendSeq(code, GenInstr(NULL, "li", "$v0", "4", NULL));

    // If the enum value is equal to "newline", then
    // ensure that a newline is printed out in the 
    // instruction. Otherwise, print out a space.
    if(printType == newline) {
        AppendSeq(code, GenInstr(NULL, "la", "$a0", "_nl", NULL));
    } else {
        AppendSeq(code, GenInstr(NULL, "la", "$a0", "_spc", NULL));
    }

    // Add the syscall instruction to the linked list of 
    // instructions to finalize the printing process.
    AppendSeq(code, GenInstr(NULL, "syscall", NULL, NULL, NULL));

    // Subtract one from the counter register and include a check to
    // ensure that there is no overlap in the loop (for example, if
    // the value is less than zero).
    AppendSeq(code, GenInstr(NULL, "subi", TmpRegName(reg), TmpRegName(reg), "1"));
    AppendSeq(code, GenInstr(NULL, "bne", "$zero", TmpRegName(reg), label1));
    AppendSeq(code, GenInstr(label2, NULL, NULL, NULL, NULL));

    // Release the temporary registers using
    // the ReleaseTmpReg() function and free
    // the ExprRes variable. 
    ReleaseTmpReg(reg);
    ReleaseTmpReg(Res->Reg);
    free(Res);

    // Return the resulting instructions
    // from the function.
    return code;
}

/* ================================================================== */
/* SECTION FOR CONDITIONALS AND LOOPS: IF, IF-ELSE, WHILE, FOR, AND */
/* ASSIGNMENT. */
/* ================================================================== */

/**
 * IF
 * 
 * The function returns a struct that contains a new
 * instruction generated within the function. The
 * function handles cases where there is a conditional
 * statement in the C-like code (if-statement).
 */
extern struct InstrSeq *doIf(struct ExprRes *Res, struct InstrSeq *seq) {

    // Create a new struct of type InstrSeq to add the 
    // assembly instructions to as they are generated
    // in this function.
    struct InstrSeq *seq2;
    char *label = GenLabel();

    // Create a new register value for helping in the 
    // process of building the instructions. Append the
    // first set of instructions on the InstSeq variable.
    int reg = AvailTmpReg();
    seq2 = AppendSeq(Res->Instrs, GenInstr(NULL, "sne", TmpRegName(reg), TmpRegName(Res->Reg), "$zero"));

    // Call the function to add the generated assembly instructions to 
    // the linked list of instructions that will be returned from the 
    // function.
    AppendSeq(seq2, GenInstr(NULL, "beq", TmpRegName(reg), "$zero", label));
    AppendSeq(seq2, seq);
    AppendSeq(seq2, GenInstr(label, NULL, NULL, NULL, NULL));

    // Release the registers that were used to help
    // generate the instructions. The registers are
    // released so that they can be reused later on 
    // in the execution of the compilation process.
    ReleaseTmpReg(Res->Reg);
    ReleaseTmpReg(reg);

    // Free the ExprRes struct and
    // return the instruction sequence.
    free(Res);
    free(label);
    return seq2;
}

/**
 * IF-ELSE 
 * 
 * The function returns a struct that contains a new
 * instruction generated within the function. The 
 * function handles cases where there is an if-else 
 * conditional statement in the C-like code.
 */
extern struct InstrSeq *doIfElse(struct ExprRes *Res, struct InstrSeq *seq1, struct InstrSeq *seq2) {
   
    // Create a variable of type InstrSeq to store
    // the assembly instructions that will be 
    // generated from the function. Also create
    // two labels that will be used in the process
    // of generating the code.
    struct InstrSeq *code;
    char *label1 = GenLabel();
    char *label2 = GenLabel();

    // Call the function to add the branch instruction to the linked list
    // of instructions. The branch instruction is used to capture the "if"
    // part of the if-else statement.
    AppendSeq(Res->Instrs, GenInstr(NULL, "beq", "$zero", TmpRegName(Res->Reg), label1));
    code = AppendSeq(Res->Instrs, seq1);

    // Call the function multiple times to generate the "else" part 
    // of the if-else statement. In this process of assembly code
    // generation, labels are also added to move from what section
    // of the assembly code to another (this helps capture the 
    // behavior of the if-else statement).
    AppendSeq(code, GenInstr(label1, NULL, NULL, NULL, NULL)); // --> KEEP IN MIND THAT YOU MAY NEED TO USE A JUMP IF THIS DOES NOT WORK!!!
    AppendSeq(code, GenInstr(NULL, "bne", "$zero", TmpRegName(Res->Reg), label2));
    AppendSeq(code, seq2);
    AppendSeq(code, GenInstr(label2, NULL, NULL, NULL, NULL));

    // Release the regisers used in this function to allow
    // them to be used again in the compilation process.
    ReleaseTmpReg(Res->Reg); // --> KEEP AN EYE ON THIS!!!

    // Free the ExprRes struct, the labels,
    // and return the generated assembly
    // code from the function.
    free(Res);
    free(label1);
    free(label2);
    return code;
}

/**
 * WHILE 
 * 
 * The function is used to help complete the 
 * process of generating assembly code for 
 * a while-loop in the C-like language that
 * the compiler processes. A struct is returned
 * from the function that contains the assembly
 * code instructions that are produced.
 */
extern struct InstrSeq *doWhile(struct ExprRes *Res, struct InstrSeq *seq) {
  
    // Create a new variable of type InstrSeq and allocate
    // space for it. The variable is used to store the 
    // assembly code instructions that are generated by the
    // function. 
    struct InstrSeq *code = NULL;

    // Create two new labels for proper jumps 
    // in the assembly code for the while loop.
    char *label1 = GenLabel();
    char *label2 = GenLabel();

    // Call the function multiple times to generate assembly code
    // for the while loop and put it in the linked list of instructions
    // that will be returned from this function.
    code = AppendSeq(code, GenInstr(label1, NULL, NULL, NULL, NULL));
    AppendSeq(code, Res->Instrs);
    AppendSeq(code, GenInstr(NULL, "beq", "$zero", TmpRegName(Res->Reg), label2));
    AppendSeq(code, seq);
    AppendSeq(code, GenInstr(NULL, "j", label1, NULL, NULL));
    AppendSeq(code, GenInstr(label2, NULL, NULL, NULL, NULL));

    // Release the temporary register that was
    // used so that it can be used again.
    ReleaseTmpReg(Res->Reg); // --> KEEP AN EYE ON THIS!!!

    // Free the ExprRes struct, the labels, and  
    // return the linked list of generated assembly
    // instructions 
    free(label1);
    free(label2);
    free(Res);
    return code;
}

/**
 * FOR 
 * 
 * The function is used to complete the process 
 * of generating assembly code for a for-loop in
 * the C-like language that the compiler processes.
 * A struct is returned from the function that 
 * contains the assembly code instructions that
 * are produced.
 */
extern struct InstrSeq *doFor(struct InstrSeq *Assignment1, struct ExprRes *CondRes, struct InstrSeq *Assignment2, struct InstrSeq *seq) {
    
    // Create a variable of type InstrSeq and reserve space for it. The 
    // variable will be used to store the assembly instructions generated
    // by this function. 
    struct InstrSeq *code = NULL;
    
    // Also create two labels through the GenLabel() function
    // in order to capture the loop and jump behavior of for
    // loops in the C-like language.
    char *label1 = GenLabel();
    char *label2 = GenLabel();

    // Call the function multiple times to generate the assembly
    // code for the for loop. The assembly code that is created
    // is stored in the linked list of instructions, the "code"
    // variable.
    code = AppendSeq(code, Assignment1);
    AppendSeq(code, GenInstr(label1, NULL, NULL, NULL, NULL));
    AppendSeq(code, CondRes->Instrs);
    AppendSeq(code, GenInstr(NULL, "beq", "$zero", TmpRegName(CondRes->Reg), label2));
    AppendSeq(code, seq);
    AppendSeq(code, Assignment2);
    AppendSeq(code, GenInstr(NULL, "j", label1, NULL, NULL));
    AppendSeq(code, GenInstr(label2, NULL, NULL, NULL, NULL));

    // Call the function to release the temporary
    // registers so that they can be used again
    // by future processes.
    ReleaseTmpReg(CondRes->Reg);
    
    // Free the ExprRes struct and return the
    // InstrSeq variable that contains the assembly
    // code generated from this function.
    free(CondRes);
    return code;
}

/**
 * ASSIGNMENT
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
    // --> CONSIDER ADDING A DESTROY EXPRESSION FUNCTION HERE!!!
    free(Expr);
  
    // Return the code variable with the instruction data.
    return code;
}

/* ================================================================== */
/* SECTION FOR ARRAYS: 1D ARRAYS AND 2D ARRAYS */
/* ================================================================== */

/**
 * CREATE 1D ARRAYS AND 2D ARRAYS
 * 
 * The function returns a struct that contains
 * new instructions generated within the function.
 * The function generates assembly instructions
 * for 1D and 2D array declarations. Offsets as 
 * well as the array size are calculated in order
 * to reserve the proper amount of space for the
 * array. An array struct, called ArrayItem, is
 * used to store attributes in the array such as
 * the array size(s). The array struct is traversed
 * through in the Finish() function to reserve
 * space for the array(s) in the .data segment of
 * the MIPS code generated in the compilatoion
 * process.
 */
extern struct InstrSeq *doArrayDec(char *name, char *size1, char *size2) {

    // Create a new struct of type InstrSeq, and append instructions
    // to it that will help store the array in the .data segment so
    // that the array is ready for use at compile time.
    struct InstrSeq *code = NULL;

    // Create a variable that finds the next available
    // register that you can use in declaring the array.
    int reg = AvailTmpReg();

    // Create a struct of type ArrayItem and allocate space
    // for it. The struct is used to store each Array that 
    // the user declares.
    struct ArrayItem *resultArray = malloc(sizeof(struct ArrayItem));

    // Assume that at least one size was entered for the array declaration
    // (this would make it a 1D array), and convert it to an actual integer.
    // Declare a second integer for reserving space for a 2D array.
    int spaceOneDimension = atoi(size1);
    int spaceTwoDimension;

    // Ceate variable for converting the integers for the array
    // size into strings in order to eliminate memory leak issues.
    char *spaceOneDimensionString = NULL;
    spaceOneDimensionString = malloc(100 * sizeof(spaceOneDimensionString));
    char *spaceTwoDimensionString = NULL;
    spaceTwoDimensionString = malloc(100 * sizeof(spaceTwoDimensionString));

    // If the second array size variable is NULL, then
    // generate MIPS assembly instructions for the creation
    // of a single-dimensional array.
    if(!size2) {

        // Set each attivute of the ArrayItem struct for 1D arrays.
        // Each attribute ensures that a given 1D array is properly
        // processed and prepared to be converted to the MIPS code.
        resultArray->ArrayName = name;
        resultArray->ArrayLabel = GenerateArrayLabel();
        resultArray->Size1 = spaceOneDimension;
        resultArray->Size2 = 1;
        resultArray->Next = listOfArrays;
        listOfArrays = resultArray;

        // Create a new struct of type InstrSeq, and append instructions // --> NOT SURE THIS IS RIGHT!!!!
        // to it that will declare an array in MIPS assembly code.
        sprintf(spaceOneDimensionString, "%d", spaceOneDimension);
        code = AppendSeq(code, GenInstr(NULL, "sll", TmpRegName(reg), spaceOneDimensionString, "2"));
        AppendSeq(code, GenInstr(NULL, "la", "$a0", resultArray->ArrayLabel, NULL));

    // If the second array size variable is not NULL, 
    // then generate MIPS assembly instructions for 
    // the creation of a two-dimensional array.
    } else {

        // If there was a second size entered for the 
        // array declaration, we are working with a 2D
        // array. Convert the second size variable to
        // an integer value.
        int spaceTwoDimension = atoi(size2);

        // Set each attivute of the ArrayItem struct for 2D arrays.
        // Each attribute ensures that a given 2D array is properly
        // processed and prepared to be converted to the MIPS code.
        resultArray->ArrayName = name;
        resultArray->ArrayLabel = GenerateArrayLabel();
        resultArray->Size1 = spaceOneDimension;
        resultArray->Size2 = spaceTwoDimension;
        resultArray->Next = listOfArrays;
        listOfArrays = resultArray;

        // Obtain the total amount of space you will need for the 
        // 2D array by multiplying the declared sizes by each other
        // and then by four via the "sll" instruction.
        spaceTwoDimension = spaceTwoDimension * spaceOneDimension;

        // Create a new struct of type InstrSeq, and append instructions // --> NOT SURE THIS IS RIGHT!!!!
        // to it that will declare an array in MIPS assembly code.
        sprintf(spaceTwoDimensionString, "%d", spaceTwoDimension);
        code = AppendSeq(code, GenInstr(NULL, "sll", TmpRegName(reg), spaceTwoDimensionString, "2"));
        AppendSeq(code, GenInstr(NULL, "la", "$a0", resultArray->ArrayLabel, NULL));
    }

    // Free up the strings and 
    // the register that was used.
    free(spaceOneDimensionString);
    free(spaceTwoDimensionString);
    ReleaseTmpReg(reg);

    // =========================================
    // NOTE: The list of arrays that was added
    // to in this function will be visited in 
    // the Finish() function and placed in the 
    // global/data section of the MIPS assembly
    // file.
    // =========================================

    // Return the resulting instructions for
    // the arrays from the array declaration
    // function.
    return code;
}

/**
 * ASSIGN TO 1D ARRAYS AND 2D ARRAYS
 * 
 * The function returns a struct that contains
 * new instructions generated within the function.
 * The function generates assembly instructions
 * for assignments to 1D and 2D arrays. The offsets
 * are calculated in order to ensure that the arrays
 * are properly assigned to in the function. After
 * the instructions are generated for the 1D and 2D
 * array assignment, return the instructions from
 * the function.
 */
extern struct InstrSeq *doArrayAssign(char *name, struct ExprRes *Res1, struct ExprRes *Res2, struct ExprRes *Res3) {

    // Create a struct of type InstrSeq to store
    // the new instruction being created.
    struct InstrSeq *code = NULL;

    // Create a temporary variable to help in calculating
    // the offset for the array or 2D array that is passed
    // through the function.
    char *charOffset = NULL;
    charOffset = malloc(100 * sizeof(charOffset));

    // Load the address of the read name array and reserve space 
    // in order to store values that are read in to the array.
    code = AppendSeq(Res1->Instrs, GenInstr(NULL, "sll", TmpRegName(Res1->Reg), TmpRegName(Res1->Reg), "2"));

    // Create two struct variables for traversing through the
    // global list of arrays in the "listOfArrays" variable.
    struct ArrayItem *arrayAssignItem;
    struct ArrayItem *nextAssignArray;

    // Assign the "arrayReadItem" struct to the global variable 
    // to begin the process of traversing through the list
    // of array values.
    arrayAssignItem = listOfArrays;

    // If there is a second size, then you need
    // to calculate the offset for the 2D array.
    if(Res2) {

        // Loop through the list of arrays and find which array
        // is equal to the array name that was passed in as a 
        // parameter to this function.
        while(arrayAssignItem) {

            // If the second size attribute of a given array item
            // in the struct is NULL, then generate space for a 1D
            // array.
            if(strcmp(arrayAssignItem->ArrayName, name) == 0 ) {

                // As soon as you find the array struct corresponding to the array
                // that you are reading in, finish calculating the offset that you
                // need for the 2D array.
                AppendSeq(code, Res2->Instrs);
                sprintf(charOffset, "%d", arrayAssignItem->Size1);
                AppendSeq(code, GenInstr(NULL, "mul", TmpRegName(Res2->Reg), TmpRegName(Res2->Reg), charOffset));
                AppendSeq(code, GenInstr(NULL, "sll", TmpRegName(Res2->Reg), TmpRegName(Res2->Reg), "2")); 
                AppendSeq(code, GenInstr(NULL, "add", TmpRegName(Res1->Reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));

                // Release the temporary register for readSize2 
                // so that it can be used again later on in the
                // program.
                ReleaseTmpReg(Res2->Reg);

                // After completing the instruction generation
                // above, break out of the loop.
                break; 
            }

            // Move to the next array value
            // in the list of arrays.
            nextAssignArray = arrayAssignItem;
            arrayAssignItem = nextAssignArray->Next;
        }
    } 

    // Add the calculated offset to the tempVariable to be formatted 
    // properly before generating a store word (sw) instruction for it.
    // Then generate a store word instruction and put Res3 in as a value.
    sprintf(charOffset, "%s(%s)", name, TmpRegName(Res1->Reg));
    AppendSeq(code, GenInstr(NULL, "sw", TmpRegName(Res3->Reg), charOffset, NULL));

    // Free the temporary registers that you used
    // inside of this function. Free the temporary 
    // variable and the readName variable as well.
    ReleaseTmpReg(Res1->Reg);
    ReleaseTmpReg(Res3->Reg);
    free(charOffset);
    free(name);

    // Return the instructions from the read
    // array list function.
    return code; // --> WAS THE ORIGINAL!!!
    // Res1->Instrs = code; // --> UPDATED!!!
    // return code; // --> UPDATED!!!
}

/* ================================================================== */
/* SECTION FOR BOOLEAN EXPRESSIONS: NEGATION, OR, AND AND. */
/* ================================================================== */

/**
 * AND, OR, and NOT
 * 
 * The function generates assembly instructions
 * for the following boolean operators: and, or, not.
 * The function follows a similar instruction creation
 * process for all boolean operators. Therefore, an 
 * additional parameter (an enum) is used to enable
 * different instructions to be generated based on 
 * the various boolean values being parsed in the 
 * C-like language.
 */
extern struct ExprRes *doBooleanOps(struct ExprRes *Res1, struct ExprRes *Res2, enum BExprOps boolOperator) {
   
    // Create a struct of type ExprRes for
    // storing the instruction that will be
    // generated in. Also create a variable
    // for the available registers.
    struct ExprRes *Res;
    int reg = AvailTmpReg();

    // Allocate space for the Res variable declared above.
    Res = (struct ExprRes *)malloc(sizeof(struct ExprRes));

    // The conditionals determine which grammar is being 
    // utilized. In other words, they determine which 
    // case is being invoked and generates the corresponding
    // instruction.
    if(boolOperator == and) {

        // If the case is an "and" boolean operation, generate an
        // "and" instruction in assembly code. This is completed
        // by checking various bits of data using the "sne" and
        // $zero registers.
        AppendSeq(Res1->Instrs, Res2->Instrs);
        AppendSeq(Res1->Instrs, GenInstr(NULL, "sne", TmpRegName(Res1->Reg), TmpRegName(Res1->Reg), "$zero"));
        AppendSeq(Res1->Instrs, GenInstr(NULL, "sne", TmpRegName(Res2->Reg), TmpRegName(Res2->Reg), "$zero"));
        AppendSeq(Res1->Instrs, GenInstr(NULL, "and", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));

    } else if(boolOperator == or) {

        // If the case is an "or" boolean operation, generate an 
        // "or" instruction in assembly code. This is also done
        // by checking various bits of data using the "sne" and
        // $zero registers.
        AppendSeq(Res1->Instrs, Res2->Instrs);
        AppendSeq(Res1->Instrs, GenInstr(NULL, "sne", TmpRegName(Res1->Reg), TmpRegName(Res1->Reg), "$zero"));
        AppendSeq(Res1->Instrs, GenInstr(NULL, "sne", TmpRegName(Res2->Reg), TmpRegName(Res2->Reg), "$zero"));
        AppendSeq(Res1->Instrs, GenInstr(NULL, "or", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));

    } else {

        // If neither of the two above cases are true, then the 
        // case must be a "not" boolean operation. Generate a
        // "not" instruction by using the "seq" sudo instruction
        // in combination with the $zero register.
        AppendSeq(Res1->Instrs, NULL);
        AppendSeq(Res1->Instrs, GenInstr(NULL, "seq", TmpRegName(reg), TmpRegName(Res1->Reg), "$zero"));
    }

    // Set the attributes of the Res structure,
    // release the first temporary register, and
    // free Res1.
    Res->Reg = reg;
    Res->Instrs = Res1->Instrs;
    ReleaseTmpReg(Res1->Reg);
    free(Res1);

    // If the second register is not
    // NULL, release the second temporary 
    // register and free Res2.
    if(Res2) {
        ReleaseTmpReg(Res2->Reg);
        free(Res2);
    }

    // Return the register
    // from the function.
    return Res;
}

/* ================================================================== */
/* SECTION FOR COMPARING EXPRESSIONS: EQUAL, NOT EQUAL, LESS THAN OR */
/* EQUAL TO, GREATER THAN OR EQUAL TO, LESS THAN, AND GREATER THAN. */
/* ================================================================== */

/**
 * NOT EQUAL, EQUAL, LESS THAN OR EQUAL TO,
 * GREATER THAN OR EQUAL TO, LESS THAN, and
 * GREATER THAN
 * 
 * The function generates assembly instructions
 * for equality operators such as: !=, ==, <=,
 * >=, <, and >. The function follows a similar
 * instruction generation process for all equality
 * operators. Therefore, an additional parameter
 * in the function (char *inst) is used to ensure
 * that any equality instruction can be created 
 * for the C-like language.
 */
extern struct ExprRes *doEqualityOps(struct ExprRes *Res1, struct ExprRes *Res2, char *inst) {
    
    // Create a new struct of type ExprRes, and
    // set the reg variable equal to the function
    // to obtain an available register.
    int reg = AvailTmpReg();

    // Create a new instruction based on the information passed through
    // the parameters of the function. The instruction is then appended
    // to a linked list of instructions upon being generated.
    AppendSeq(Res1->Instrs, Res2->Instrs);
    AppendSeq(Res1->Instrs, GenInstr(NULL, inst, TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));
    
    // Call the functions to release 
    // the temporary registers.
    ReleaseTmpReg(Res1->Reg);
    ReleaseTmpReg(Res2->Reg);

    // Set the Reg attribute to the created
    // integer variable and the Instrs attribute
    // to the generated instruction.
    Res1->Reg = reg;

    // Free the registers and
    // return the instruction
    // from the function.
    free(Res2);
    return Res1;
}

/* ================================================================== */
/* SECTION FOR ARITHMETIC OPERATIONS: ADDITION, SUBTRACTION, */
/* MULTIPLICATION, DIVISION, EXPONENTIATION, AND MODULUS. */ 
/* ================================================================== */

/**
 * ADD, SUBTRACT, MULTIPLY, DIVIDE
 * 
 * The function completes basic arithmetic operations. The operations
 * inlcude addition, subtraction, multiplication, and division. Given
 * that each of these operations follows a similar configuration pattern
 * in the generation of assembly instructions, an additional parameter
 * is used (char *inst) to allow for different instructions to be
 * generated.
 */
extern struct ExprRes *doArithmeticOps(struct ExprRes *Res1, struct ExprRes *Res2, char *inst) { 

    // Create an integer variable to represent 
    // the available temporary registers.
    int reg;
    reg = AvailTmpReg();
    
    // Call the AppendSeq function to determine what
    // registers are open as well as add the instructions
    // to the linked list of instructions.
    AppendSeq(Res1->Instrs, Res2->Instrs);
    AppendSeq(Res1->Instrs, GenInstr(NULL, inst, TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));

    // Call the functions below to indicate 
    // that the registers used in the operation 
    // are now free to use again. 
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
 * MODULUS
 * 
 * The function returns a struct that contains a new
 * instruction generated within the function. The
 * function handles cases where the modulus operator
 * is used. Two MIPS assembly instruction labels are
 * used to complete the modulus operation: The "div"
 * label (divide) and the "mfhi" label (move from hi).
 */
extern struct ExprRes *doModulo(struct ExprRes *Res1, struct ExprRes *Res2) {
  
    // Create an integer variable to represent
    // the available temporary registers.
    int reg;
    reg = AvailTmpReg();

    // Call the AppendSeq function to determine what 
    // registers are open as well as add the instructions
    // to the linked list of instructions.
    // In this case, we perform division and then utilize
    // the "mfhi" MIPS assembly instruction (move from hi)
    // to complete the modulus operation.
    AppendSeq(Res1->Instrs, Res2->Instrs);
    AppendSeq(Res1->Instrs, GenInstr(NULL, "div", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg))); // --> DO WE CARE ABOUT THE QUOTIENT???
    AppendSeq(Res1->Instrs, GenInstr(NULL, "mfhi", TmpRegName(reg), NULL, NULL));

    // Call the functions below to indicate 
    // that the registers used in the modulus 
    // operation are now free to use again. 
    ReleaseTmpReg(Res1->Reg);
    ReleaseTmpReg(Res2->Reg);

    // Set the register number of the result
    // equal to the "reg" variable that was used
    // to determine what register number to use
    // for the operation.
    Res1->Reg = reg;
    
    // Free the temporary register so it
    // can be reused by other processes.
    ReleaseTmpReg(reg);

    // Free the space in the result variable,
    // and return the other result.
    free(Res2);
    return Res1;
}

/**
 * EXPONENTIATION
 * 
 * The function returns a struct that contains a new
 * instruction generated within the function. The
 * function handles cases where the exponentiation 
 * operator is used. Multiple MIPS instructions are 
 * used to complete the process of exponentiation. In 
 * essence, the instructions used equate to repeated
 * multiplication in order to raise the value to a 
 * given power.
 */
struct ExprRes *doExponential(struct ExprRes *Res1, struct ExprRes *Res2) {

    // In this function, the base is store in Res1->Reg and 
    // the exponent is stored in Res2->Reg. Loop over the
    // exponent and create instructions where we multiply
    // the base by itself.

    // Create three register variables to allocate
    // space for the exponential operation.
    int reg1 = AvailTmpReg();
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
    AppendSeq(Res1->Instrs, GenInstr(NULL, "move", TmpRegName(reg1), TmpRegName(Res1->Reg), NULL));
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
    AppendSeq(Res1->Instrs, GenInstr(NULL, "mul", TmpRegName(reg1), TmpRegName(reg1), TmpRegName(Res1->Reg)));
    AppendSeq(Res1->Instrs, GenInstr(NULL, "subi", TmpRegName(reg2), TmpRegName(reg2), "1"));
    AppendSeq(Res1->Instrs, GenInstr(NULL, "j", label, NULL, NULL));
    AppendSeq(Res1->Instrs, GenInstr(label3, NULL, NULL, NULL, NULL));
    AppendSeq(Res1->Instrs, GenInstr(NULL, "move", TmpRegName(reg1), TmpRegName(Res1->Reg), NULL));
    AppendSeq(Res1->Instrs, GenInstr(label2, NULL, NULL, NULL, NULL));

    // Release all of the registers after use.
    ReleaseTmpReg(Res1->Reg); // --> KEEP AN EYE ON THIS!!!
    ReleaseTmpReg(Res2->Reg);
    ReleaseTmpReg(reg2);
    ReleaseTmpReg(reg3);

    // Set the first register equal to the first reg variable, free
    // the second register struct, and return from the function.
    Res1->Reg = reg1; // --> WE SET RES1 = REG1, SO CAN WE FREE IT AFTERWARDS???
    // ReleaseTmpReg(reg1); // --> KEEP AN EYE ON THIS!!!
    free(Res2);
    free(label);
    free(label2);
    free(label3);
    return Res1;
}

/* ================================================================== */
/* SECTION FOR INTEGER LITERALS: POSITIVE AND NEGATIVE; RVALUES */
/* ================================================================== */

/**
 * INTEGER LITERAL: NEGATIVE
 * 
 * The function returns a struct that contains a new 
 * instruction generated within the function. The 
 * function handles cases where a negative int literal
 * is being evaluated. The function ensures that the 
 * negative int literal is added into a register via
 * the "li" label (It loads an immediate value into
 * a register). The value is then multiplied by negative
 * one to ensure that it is read as negative in MIPS
 * assembly.
 */
extern struct ExprRes *doIntLitNeg(struct ExprRes *Res) {

    // Multiply the expression by negative one in order to ensure that the
    // negative value is applied to the expression result passed into this
    // function.
    AppendSeq(Res->Instrs, GenInstr(NULL, "mul", TmpRegName(Res->Reg), TmpRegName(Res->Reg), "-1"));

    // Return the resulting instruction.
    return Res;
}

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
 * LOAD THE WORD
 *
 * The function returns a struct that contains a new
 * instruction generated within the function. The
 * function handles cases where data is being obtained
 * from some address in memory. The function ensures
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
 * LOAD THE ARRAY
 *
 * The function returns a struct that contains a new
 * instruction generated within the function. The
 * function handles cases where data is being obtained
 * from an array in memory. The function generates MIPS
 * code that calculates the correct offset values in 
 * order to access the proper data stored in the given
 * array. That data is then loaded from the array into
 * a register for use by the program being compiled.
 */
struct ExprRes *doRvalArray(char *name, struct ExprRes *Res1, struct ExprRes *Res2) { 

    // Create a struct of type InstrSeq to store
    // the new instruction being created.
    struct InstrSeq *code = NULL;

    // Create a temporary variable to help in calculating
    // the offset for the array or 2D array that is passed
    // through the function.
    char *tempRvalVariable = NULL;
    tempRvalVariable = malloc(100 * sizeof(tempRvalVariable));

    // Load the address of the read name array and find
    // the location in memory where the value is stored.
    code = AppendSeq(Res1->Instrs, GenInstr(NULL, "sll", TmpRegName(Res1->Reg), TmpRegName(Res1->Reg), "2"));

    // Create two struct variables for traversing through the
    // global list of arrays in the "listOfArrays" variable.
    struct ArrayItem *arrayRvalItem;
    struct ArrayItem *nextRvalArray;

    // Assign the "arrayReadItem" struct to the global variable 
    // to begin the process of traversing through the list
    // of array values.
    arrayRvalItem = listOfArrays;

    // If there is a second size, then you need
    // to calculate the offset for the 2D array.
    if(Res2) {

        // Loop through the list of arrays and find which array
        // is equal to the array name that was passed in as a 
        // parameter to this function.
        while(arrayRvalItem) {

            // If the second size attribute of a given array item
            // in the struct is NULL, then generate space for a 1D
            // array.
            if(strcmp(arrayRvalItem->ArrayName, name) == 0 ) {

                // As soon as you find the array struct corresponding to the array
                // that you are reading in, finish calculating the offset that you
                // need for the 2D array.
                AppendSeq(code, Res2->Instrs);
                sprintf(tempRvalVariable, "%d", arrayRvalItem->Size1);
                AppendSeq(code, GenInstr(NULL, "mul", TmpRegName(Res2->Reg), TmpRegName(Res2->Reg), tempRvalVariable));
                AppendSeq(code, GenInstr(NULL, "sll", TmpRegName(Res2->Reg), TmpRegName(Res2->Reg), "2")); 
                AppendSeq(code, GenInstr(NULL, "add", TmpRegName(Res1->Reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));

                // Release the temporary register for readSize2 
                // so that it can be used again later on in the
                // program.
                ReleaseTmpReg(Res2->Reg);

                // After completing the instruction generation
                // above, break out of the loop.
                break; 
            }

            // Move to the next array value
            // in the list of arrays.
            nextRvalArray = arrayRvalItem;
            arrayRvalItem = arrayRvalItem->Next;
        }
    } 

    // Add the calculated offset to the tempVariable to be formatted 
    // properly before generating a store word (sw) instruction for it.
    // Then generate a store word instruction.
    sprintf(tempRvalVariable, "%s(%s)", name, TmpRegName(Res1->Reg));
    AppendSeq(code, GenInstr(NULL, "lw", TmpRegName(Res1->Reg), tempRvalVariable, NULL));

    // Free the temporary registers that you used
    // inside of this function. Free the temporary 
    // variable and the readName variable as well.
    ReleaseTmpReg(Res1->Reg); // --> KEEP AN EYE ON THIS!!!
    free(tempRvalVariable);
    free(name);

    // Set the Res1 variable equal to the
    // code instruction variable in order to
    // retain all of the previous instructions
    // that were generated.
    Res1->Instrs = code;

    // Return the resulting instruction for
    // obtaining the value of the array.
    return Res1;
}

/**
 * READLIST ARRAY
 * 
 * The function returns a struct that contains
 * new instructions generated within the function.
 * The function handles cases where the read function
 * is being used for a single array value input or for 
 * multiple array value inputs. The function can also
 * generate instructions that read in values for 1D
 * and 2D arrays. If there are 2D arrays that have 
 * values being read in, then the second size variable,
 * "readSize2", is used to calculate the proper offset.
 * The instructions that are generated and returned
 * from the function enable a MIPS program to read
 * in single or multiple array values that are then
 * stored in different array variables.
 */
extern struct InstrSeq *createReadListArray(char *readName, struct ExprRes *readSize1, struct ExprRes *readSize2, struct InstrSeq *readList) {

    // Create a struct of type InstrSeq to store
    // the new instruction being created.
    struct InstrSeq *code = NULL;

    // Create a temporary variable to help in calculating
    // the offset for the array or 2D array that is passed
    // through the function.
    char *tempVariable = NULL;
    tempVariable = malloc(100 * sizeof(tempVariable));

    // Load the address of the read name array and reserve space 
    // in order to store values that are read in to the array.
    code = AppendSeq(readSize1->Instrs, GenInstr(NULL, "sll", TmpRegName(readSize1->Reg), TmpRegName(readSize1->Reg), "2"));

    // Create two struct variables for traversing through the
    // global list of arrays in the "listOfArrays" variable.
    struct ArrayItem *arrayReadItem;
    struct ArrayItem *nextReadArray;

    // Assign the "arrayReadItem" struct to the global variable 
    // to begin the process of traversing through the list
    // of array values.
    arrayReadItem = listOfArrays;

    // If there is a second size, then you need
    // to calculate the offset for the 2D array.
    if(readSize2) {

        // Loop through the list of arrays and find which array
        // is equal to the array name that was passed in as a 
        // parameter to this function.
        while(arrayReadItem) {

            // If the second size attribute of a given array item
            // in the struct is NULL, then generate space for a 1D
            // array.
            if(strcmp(arrayReadItem->ArrayName, readName) == 0 ) {

                // As soon as you find the array struct corresponding to the array
                // that you are reading in, finish calculating the offset that you
                // need for the 2D array.
                AppendSeq(code, readSize2->Instrs);
                sprintf(tempVariable, "%d", arrayReadItem->Size1);
                AppendSeq(code, GenInstr(NULL, "mul", TmpRegName(readSize2->Reg), TmpRegName(readSize2->Reg), tempVariable));
                AppendSeq(code, GenInstr(NULL, "sll", TmpRegName(readSize2->Reg), TmpRegName(readSize2->Reg), "2")); 
                AppendSeq(code, GenInstr(NULL, "add", TmpRegName(readSize1->Reg), TmpRegName(readSize1->Reg), TmpRegName(readSize2->Reg)));

                // Release the temporary register for readSize2 
                // so that it can be used again later on in the
                // program.
                ReleaseTmpReg(readSize2->Reg);

                // After completing the instruction generation
                // above, break out of the loop.
                break; 
            }

            // Move to the next array value
            // in the list of arrays.
            nextReadArray = arrayReadItem;
            arrayReadItem = arrayReadItem->Next;
        }
    } 

    // Generate a series of instructions to load the array 
    // into an address after being read in by the user input.
    AppendSeq(code, GenInstr(NULL, "li", "$v0", "5", NULL)); 
    AppendSeq(code, GenInstr(NULL, "syscall", NULL, NULL, NULL));

    // Add the calculated offset to the tempVariable to be formatted 
    // properly before generating a store word (sw) instruction for it.
    // Then generate a store word instruction.
    sprintf(tempVariable, "%s(%s)", readName, TmpRegName(readSize1->Reg));
    AppendSeq(code, GenInstr(NULL, "sw", "$v0", tempVariable, NULL));

    // Lastly, append the readList variable to the instruction sequence
    // being returned in order to move to the next array attribute being 
    // read in by the function.
    AppendSeq(code, readList);

    // Free the temporary registers that you used
    // inside of this function. Free the temporary 
    // variable and the readName variable as well.
    ReleaseTmpReg(readSize1->Reg);
    free(tempVariable);
    free(readName);

    // Return the instructions from the read
    // array list function.
    return code; // --> THIS WAS THE ORIGINAL!!!

    // readSize1->Instrs = code; // --> UPDATED!!!
    // return readSize1->Instrs; // --> UPDATED!!!
}

/**
 * READLIST IDENTIFIER
 * 
 * The function returns a struct that contains
 * new instructions generated within the function.
 * The function handles cases where the read function
 * is being used for a single input or for multiple
 * inputs. The instructions that are generated and
 * returned from the function enable a MIPS program
 * to read in single or multiple values that can
 * then be stored in various variables (integers).
 */
extern struct InstrSeq *createReadListIdent(char *readName, struct InstrSeq *readList) {

    // Create a struct of type InstrSeq to store
    // the new instruction being created.
    struct InstrSeq *code = NULL;

    // Generate a series of instructions to read in an identifier
    // that can then be stored into a variable for use later on
    // in a given program that is being compiled.
    code = AppendSeq(code, GenInstr(NULL, "li", "$v0", "5", NULL));
    AppendSeq(code, GenInstr(NULL, "syscall", NULL, NULL, NULL));
    AppendSeq(code, GenInstr(NULL, "sw", "$v0", readName, NULL));

    // Lastly, append the sequence of instructions to 
    // the instruction struct being returned from this
    // function in case you have more than one identifier
    // that you are reading in for use. Free the string
    // variable as well.
    AppendSeq(code, readList); 
    free(readName);

    // Return the instructions from the
    // read list identifier function.
    return code;
}
