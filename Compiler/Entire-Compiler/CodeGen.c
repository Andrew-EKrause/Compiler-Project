/**
 * The Code Generator file produces assembly code
 * that is generated from the other components of
 * the compiler. The file also creates the initial
 * MIPS assembly code that is needed to begin the
 * process of running an assembly program. The 
 * functions within this file help with the process
 * of creating assembly code instructions as well
 * as manipulating the registers that are used
 * in the program that is processed by the Code
 * Generator file.
 * 
 * @file CodeGen.c
 * @author Thomas Gendreau
 * @version 0.1
 * @date 2022-04-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// Include the standard C library,
// a standard I/O library, and a 
// library of strings.
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

// Include the CodeGen.h file API.
#include "CodeGen.h"

// Create a global external file variable.
extern FILE *aFile;

// Create a global variable to indicate when 
// to move to the next instruction label.
int NextLabel = 1;

// Create a global variable to indicate when
// to move to the next string label.
int NextStringLabel = 1;

// Create a global variable to indicate when
// to move to the next array label.
int NextArrayLabel = 1;

// Create a struct with temporary ('t'-registers)
// to store values that are obtained throughout the
// execution and translation process.
struct TmpReg {
  unsigned char Free;
  unsigned char Used;
  char *Name;
} Registers[10] = {
                    {1, 0, "$t0"}, 
                    {1, 0, "$t1"}, 
                    {1, 0, "$t2"}, 
                    {1, 0, "$t3"}, 
                    {1, 0, "$t4"}, 
                    {1, 0, "$t5"}, 
                    {1, 0, "$t6"}, 
                    {1, 0, "$t7"}, 
                    {1, 0, "$t8"}, 
                    {1, 0, "$t9"}};

// Define the maximum number of registers as ten.
#define MAXREG 10

// Create a global char variable as the buffer,
// and give it a size of 16 for memory.
char Buf[16];

/**
 * The function creates a copy of a 
 * string that is passed into it.
 */
char *CopyStr(char *AStr) {

    // Return a copy of the string. If 
    //v there is no string, return NULL.
    return (AStr) ? strdup(AStr) : NULL;
}

/**
 * The function generates an instruction based on the label (add, addi, subu, etc),
 * the opcode, and the two or three operands that are provided as input parameters.
 * The instruction is created through the instruction sequence struct and returned 
 * as a struct variable.
 */
struct InstrSeq *GenInstr(char *Label, char *OpCode, char *Oprnd1, char *Oprnd2, char *Oprnd3) {
  
    // Declare a struct of type InstrSeq 
    // (instruction sequence).
    struct InstrSeq *instr;

    // Reserve space for the instruction sequence 
    // being created. Add the values that are
    // passed into this function as parameters
    // to the different components of the struct.
    instr = (struct InstrSeq *)malloc(sizeof(struct InstrSeq));
    instr->Label = CopyStr(Label);
    instr->OpCode = CopyStr(OpCode);
    instr->Oprnd1 = CopyStr(Oprnd1);
    instr->Oprnd2 = CopyStr(Oprnd2);
    instr->Oprnd3 = CopyStr(Oprnd3);
    instr->Next = NULL;

    // Return the created instruction sequence.
    return instr;
}

/**
 * The function appends an instruction to the struct that holds all of the
 * instructions generated through the compiler. The struct is essentially a 
 * linked list of instructions. The contents of the linked list, the 
 * instructions that are stored in it, are printed out at the conclusion
 * of the programs. The printed out instructions are the contents of the
 * assembly code equivalent to the C-code programs passed through the 
 * compiler.
 */
extern struct InstrSeq *AppendSeq(struct InstrSeq *Seq1, struct InstrSeq *Seq2) {
    
    // Declare a struct of type InstrSeq 
    // (instruction sequence).
    struct InstrSeq *instr;

    // If there is not the first instruction
    // sequence, return the second instruction
    // sequence.
    if (!Seq1) return Seq2;

    // Otherwise, set the instr variable 
    // equal to the first instruction.
    instr = Seq1;

    // The while loop ensures that the instruction
    // is inserted at the end of the linked list.
    // The loop moves to the next node in the list
    // until the NULL value is reached.
    while(instr->Next) {
        instr = instr->Next;
    } 
    instr->Next = Seq2;

    // Return the first instruction sequence.
    return Seq1;
}

/**
 * The function writes out the instruction to 
 * a listing file, called aFile, in order to 
 * create an assembly program in a file that
 * can be run in MIPS. 
 */
void WriteSeq(struct InstrSeq *ASeq) {

    // Create a variable of type InstrSeq
    // for storing the linked list of 
    // instructions.
    struct InstrSeq *instr;

    // Print statement to indicate writing out to the file.
    printf("WriteSeq\n");

    // Set the variable equal to the instruction 
    // parameter that is passed into the function.
    instr = ASeq;

    // While there is an instruction (in other words, there is 
    // not a NULL value), move through the linked list of 
    // instructions. For each instruction, print out each
    // component of the instruction to the assembly file.
    while (instr) {

        // If there is an instruction label, then print out
        // the instruction label to the listing file, aFile.
        if (instr->Label) fprintf(aFile, "%s:", instr->Label);
        
        // If there is an instruction opcode, print out
        // the opcode to the listing file.
        if (instr->OpCode) {

            // Print out the opcode to the listing file.
            fprintf(aFile, "\t%s\t", instr->OpCode);
            
            // If there is a first instruction operand, a second
            // instruction operand, and/or a third instruction
            // operand, then print them out the listing file.
            if (instr->Oprnd1) fprintf(aFile, "\t%s", instr->Oprnd1);
            if (instr->Oprnd2) fprintf(aFile, ", %s", instr->Oprnd2);
            if (instr->Oprnd3) fprintf(aFile, ", %s", instr->Oprnd3);
        }

        // Print out a newline to the listing file. Then
        // move to the next instruction in the file.
        fprintf(aFile, "\n");
        instr = instr->Next;
    }

    // If there is a listing file, aFile, then
    // close the listing file after writing out
    // to it.
    if (aFile != stdout) fclose(aFile);
}

/**
 * The function generates a label for
 * the instruction. The label created
 * for the instruction is returned.
 */
char *GenLabel() {

    // Create a char* (string) for storing the
    // label that will be created for the 
    // instruction.
    char *label;

    // Create space for the instruction label
    // and store the characters for the label
    // in the variable.
    label = (char *)malloc(8);
    sprintf(label, "L%d", NextLabel++);

    // Return the label from the function.
    return label;
}

/**
 * The function generates a label for
 * a string. The label created for the
 * string is returned.
 */
char *GenerateStringLabel() {

    // Create a char* (string) for storing the
    // label that will be created for the string.
    char *stringLabel;

    // Create space for the string label and 
    // store the characters for the label in
    // the variable.
    stringLabel = (char *)malloc(8);
    sprintf(stringLabel, "S%d", NextStringLabel++);

    // Return the string label from the function.
    return stringLabel;
}

/**
 * The function generates a label for
 * an array. The label created for the 
 * array is returned.
 */
char *GenerateArrayLabel() {

    // Create a char* (string) for storing the
    // label that will be created for the array.
    char *arrayLabel;

    // Create space for the array label and
    // store the characters for the label in
    // the variable.
    arrayLabel = (char *)malloc(8);
    sprintf(arrayLabel, "A%d", NextArrayLabel++);

    // Return the array label from the function.
    return arrayLabel;
}

/**
 * The function searches for and finds
 * the available temporary registers
 * and fills them with information.
 */
int AvailTmpReg() {

    // Create a counter variable.
    int i;

    // In the for loop, check all the registers
    // and determine if any of them are free.
    for (i = 0; i < MAXREG; i++) {

        // If there are any free registers, 
        // free them and return the index of
        // the register.
        if (Registers[i].Free) {
            Registers[i].Free = 0;
            Registers[i].Used = 1;
            return i;
        }
    }

    // If no temporary registers are
    // free, return negative one.
    return -1;
}

/**
 * The function returns the name of the value
 * stored inside of the temporary register.
 * If there are no temporary registers, return
 * NULL.
 */
char *TmpRegName(int RegNum) {

    // If the register number is greater than 
    // or equal to zero and less than the max
    // number of registers available, return
    // the name of that register.
    if ((RegNum >= 0) && (RegNum < MAXREG)) {
        return Registers[RegNum].Name;
    } else {
        return NULL;
    }
}

/**
 * The function releases space in the 
 * given temporary register, which is
 * selected via the number that is 
 * passed through as a parameter.
 */
void ReleaseTmpReg(int ANum) {

    // If the register number is greater
    // than or equal to zero, free that 
    // register by setting its Free 
    // component equal to one.
    if ((ANum >= 0) && (ANum < MAXREG)) {
        Registers[ANum].Free = 1;
    }

    // Return from the function.
    return;
}

/**
 * The function resets all of the 
 * temporary registers to 'Free'.
 */
void ResetAllTmpReg() {

    // Create a counter variable.
    int i;

    // Loop through all registers and
    // set free them by changing the
    // the component variables.
    for (i = 0; i < MAXREG; i++) {
        Registers[i].Free = 1;
        Registers[i].Used = 0;
    }

    // Return from the function.
    return;
}

/**
 * The function determines the address and
 * offset of a given instruction, and then
 * saves the sequence of instructions to 
 * the main linked list struct of assembly
 * code instructions.
 */
struct InstrSeq *SaveSeq() {

    // Create two variables of type InstrSeq.
    struct InstrSeq *save, *code;

    // Create two variables for counting and 
    // determining whether to add certain  
    // assembly instructions.
    int i, scnt;

    // Create two char variables to determine the
    // address and the offset for each register in
    // each instruction.
    char addr[8], offset[8];

    // Set the scnt variable to zero and set save
    // to NULL.
    scnt = 0;
    save = NULL;

    // For each register, if the register is not free,
    // then print out an address offset to the addr 
    // variable. Store the instruction in the save 
    // variable.
    for (i = 0; i < MAXREG; i++) {

        // If the registers are not free, complete
        // the following procedures.
        if (!Registers[i].Free) {

            // Increment the scnt variable, store the address
            // offset in the addr variable, and store the 
            // instruction in the save variable.
            scnt++; // --> MAY WANT TO SWITCH THIS AROUND WITH THE LINE BELOW IT!!!
            sprintf(addr, "%d($sp)", scnt * 4); // --> MAY WANT TO SWITCH THIS AROUND WITH THE LINE ABOVE IT!!!
            save = AppendSeq(save, GenInstr(NULL, "sw", TmpRegName(i), addr, NULL));
        }
    }
    
    // If the scnt variable is greater than zero, then
    // complete the following procedures in the conditional.
    if (scnt > 0) {

        // Store the address offset variable in the
        // offset variable via the sprintf function.
        sprintf(offset, "%d", scnt * 4);

        // Store the function results in the code variable,
        // and call the AppendSeq function to add the 
        // instruction sequence to the linked list of 
        // instructions struct.
        code = GenInstr(NULL, "subu", "$sp", "$sp", offset);
        AppendSeq(code, save);
    }

    // Return the code variable from the function.
    return code;
}

/**
 * The function restores the instruction 
 * sequence when called. ADD MORE COMMENTS LATER...
 */
struct InstrSeq *RestoreSeq() {

    // Create two variables of type InstrSeq.
    struct InstrSeq *code, *save;
    
    // Create two variables for counting and 
    // determining to add certain assembly 
    // instructions.
    int i, scnt;

    // Create two char variables to determine the
    // address and the offset for each register in
    // each instruction.
    char addr[8], offset[8];

    // Give the scnt and NULL variables initial values.
    scnt = 0;
    save = NULL;

    // For each register, check if a given register 
    // is not free and complete the procedures within
    // the conditional.
    for (i = 0; i < MAXREG; i++) {

        // If a given register is not free, 
        // complete the operations below.
        if (!Registers[i].Free) {

            // Increment the scnt counter, add the offset value to the
            // addr variable, and save the function call results in the
            // save variable.
            scnt++;
            sprintf(addr, "%d($sp)", scnt * 4);
            save = AppendSeq(save, GenInstr(NULL, "lw", TmpRegName(i), addr, NULL));
        }
    }

    // If the scnt variable is greater than zero, then
    // complete the following procedures in the conditional.
    if (scnt > 0) {

        // Store the address offset variable in the
        // offset variable via the sprintf function.
        sprintf(offset, "%d", scnt * 4);

        // Store the nested function results in the code variable.
        code = AppendSeq(save, GenInstr(NULL, "addu", "$sp", "$sp", offset));
    }

    // Return the code variable from the function.
    return code;
}

/**
 * The function prints out the immediate value
 * to the buffer and then returns that buffer.
 * This function is utilized for immediate values
 * that will be generated for the assembly code.
 */
char *Imm(int Val) {

    // Print the value to the buffer 
    // and return the buffer.
    sprintf(Buf, "%d", Val);
    return Buf;
}

/**
 * The function creates a register offset.
 * This function is useful for cases where
 * memory address offsets are needed (like
 * cases where arrays or functions are 
 * utilized).
 */
char *RegOff(int Offset, char *Reg) {

    // Print out the offset and register
    // to the buffer and return the buffer.
    sprintf(Buf, "%d(%s)", Offset, Reg);
    return Buf;
}
