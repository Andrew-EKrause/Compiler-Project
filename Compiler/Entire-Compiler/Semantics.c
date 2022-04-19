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
 * The functions out of order compared to the
 * ExprEval.y file are the createExprList() and 
 * the createIdentList() functions.
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
#include "CodeGen.h"
#include "Semantics.h"
#include "SymTab.h"
#include "IOMngr.h"

// Create an external global symbol table for
// memory management of the variable values.
extern SymTab *table;

// Create a global list of strings in order
// to print strings out in the C-like language.
struct StringItem *listOfStrings;

/* ========================== */
/* Semantics support routines */
/* ========================== */

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

    // --> NOT SURE WHY I PUT THE CODE BELOW. USE FOR FUNCTIONS MAYBE LATER!!!
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
    AppendSeq(code, GenInstr("_nl", ".asciiz", "\"\\n\"", NULL, NULL)); // --> Load a newline into the data section.
    AppendSeq(code, GenInstr("_spc", ".asciiz", "\" \"", NULL, NULL)); // --> Load a space into the data section.

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

    // Loop through the list of expressions and add assembly code to 
    // the linked list of instructions to print out each item in the
    // expression.
    while(listOfExprs) {

        // Set the variable equal to the call for adding the instructions to the 
        // linked list of instructions.
        resultInstruction = AppendSeq(resultInstruction, listOfExprs->Expr->Instrs);

        // Call the function multiple times to print out a given item in the expression.
        AppendSeq(resultInstruction, GenInstr(NULL, "add", "$a0", TmpRegName(listOfExprs->Expr->Reg), "$zero"));
        AppendSeq(resultInstruction, GenInstr(NULL, "li", "$v0", "1", NULL)); // --> 1 is the syscall number for printing an integer.
        AppendSeq(resultInstruction, GenInstr(NULL, "syscall", NULL, NULL, NULL));

        // Call the function multiple times to print out a space in
        // order to separate item being printed out in the expression.
        AppendSeq(resultInstruction, GenInstr(NULL, "li", "$v0", "11", NULL)); // --> 11 is the syscall number for printing a character.
        AppendSeq(resultInstruction, GenInstr(NULL, "la", "$a0", "_spc", NULL)); // --> 32 is the ASCII character for a space. I use "_spc" here instead.
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

/**
 * READ
 * 
 * The read function takes in a value that 
 * is entered by the user and stores it in
 * a declared variable. This function is 
 * useful in cases where user input needs
 * to be read in to a program. The function
 * loops through a list of identifiers to 
 * complete the read functionality. 
 */
extern struct InstrSeq *doRead(struct IdList *entry) {
  
    // Create a struct of type InstrSeq and reserve
    // space for it. This will store the instructions
    // generated in this function. Also create another 
    // struct of type IdList to represent the number 
    // of values that can be entered.
    struct InstrSeq *code = malloc(sizeof(struct InstrSeq));
    struct IdList *curr = entry;

    // There is another entry for a value that will 
    // be entered by the user, generate a series of
    // instructions to store the values that will be
    // entered.
    while (curr) {

        // Call the functions multiple times to generate
        // assembly instructions to store the values that
        // will be entered into the read function.
        AppendSeq(code, GenInstr(NULL, "li", "$v0", "5", NULL));
        AppendSeq(code, GenInstr(NULL, "syscall", NULL, NULL, NULL));
        AppendSeq(code, GenInstr(NULL, "sw", "$v0", curr->TheEntry->name, NULL));

        // Free the entry name and current
        // entry after it is entered into
        // the assembly code being generated.
        free(curr->TheEntry->name); 
        free(curr->TheEntry); 

        // Move to the next entry in
        // the list of identifiers.
        entry = curr;
        curr = curr->Next;

        // Lastly, free the entry
        // struct itself.
        free(entry);
    }

    // Return the linked list of
    // instructions that were
    // generated in the function.
    return code;
}

/**
 * {READ} - HELPER FUNCTION
 * 
 * The function is used to help complete the 
 * READ functionality of the compiler. The
 * function helps to create a list of identifers
 * that is used to run the read function of the
 * C-like language.
 */
extern struct IdList *createIdentList(char *idName, struct IdList *list) {

    // Create a new IdList to return from the
    // function and reserve space for the list.
    struct IdList *newList = malloc(sizeof(struct IdList));

    // Set the attributes of the list, and reserve
    // space for the SymEntry and string of characters.
    newList->Next = list;
    newList->TheEntry = malloc(sizeof(SymEntry));
    newList->TheEntry->name = strdup(idName);

    // Return the list of identifiers
    // from the function.
    return newList;
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
    struct InstrSeq *code = (struct InstrSeq *)malloc(sizeof(struct InstrSeq));

    // Create two new labels for proper jumps 
    // in the assembly code for the while loop.
    char *label1 = GenLabel();
    char *label2 = GenLabel();

    // Call the function multiple times to generate assembly code
    // for the while loop and put it in the linked list of instructions
    // that will be returned from this function.
    AppendSeq(code, GenInstr(label1, NULL, NULL, NULL, NULL));
    AppendSeq(code, Res->Instrs);
    AppendSeq(code, GenInstr(NULL, "beq", "$zero", TmpRegName(Res->Reg), label2));
    AppendSeq(code, seq);
    AppendSeq(code, GenInstr(NULL, "j", label1, NULL, NULL));
    AppendSeq(code, GenInstr(label2, NULL, NULL, NULL, NULL));

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
    struct InstrSeq *code = (struct InstrSeq *)malloc(sizeof(struct InstrSeq));
    
    // Also create two labels through the GenLabel() function
    // in order to capture the loop and jump behavior of for
    // loops in the C-like language.
    char *label1 = GenLabel();
    char *label2 = GenLabel();

    // Call the function multiple times to generate the assembly
    // code for the for loop. The assembly code that is created
    // is stored in the linked list of instructions, the "code"
    // variable.
    AppendSeq(code, Assignment1);
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
    ReleaseTmpReg(reg); // --> KEEP AN EYE ON!!!

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
    AppendSeq(Res1->Instrs, GenInstr(NULL, "subi", TmpRegName(reg2), TmpRegName(reg2), "1"));
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

// --> MAY HAVE TO CREATE ANOTHER RVAL OR MODIFY THE EXISTING ONE TO WORK WITH ARRAYS!!!
