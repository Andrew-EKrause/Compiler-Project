/*
    The CodeGen.h file contains routines to support the generation
    of assembly code. API for a Code Generator file. The Code Generator
    produces the assembly code equivalent to the C-like language that 
    will be compiled (translated to the assembly code).
*/
//#pragma once

/* Include the standard I/O package. */
#include <stdio.h>

/* Create an external file for the assembly code to be added to. */
extern FILE *AssmFile;

/*
    An InstrSeq (instruction sequence) is a building block
    for generating instructions in MIPS assembly code.
*/
struct InstrSeq {
    char *Label;
    char *OpCode;
    char *Oprnd1;
    char *Oprnd2;
    char *Oprnd3;
    struct InstrSeq *Next;
};

/*
    The function begins the process of generating assembly code.
*/
extern void InitCodeGen(char *AFilename);

/* 
    The function generates an assembly code instruction.
*/
extern struct InstrSeq *GenInstr(char *Label, char *OpCode, char *Oprnd1, char *Oprnd2, char *Oprnd3);

/*
    The function appends different instruction sets together.
*/
extern struct InstrSeq *AppendSeq(struct InstrSeq *Seq1, struct InstrSeq *Seq2);

/*
    The function writes the instruction sequence to a file.
*/
extern void WriteSeq(struct InstrSeq *ASeq);

/*
    The function generates a label for an instruction.
*/
extern char *GenLabel();

/*
    The function determines how many temporary
    registers are available for use.
*/
extern int AvailTmpReg();

/*
    The program obtains the name of the temporary
    register being used in the program.
*/
extern char *TmpRegName(int RegNum);

/*
    The function frees the temporary 
    register that was used in memory.
*/
extern void ReleaseTmpReg(int ANum);

/*
    The function resets all of the temporary
    registers being used throughout the program.
*/
extern void ResetAllTmpReg();

/*
    The function saves the sequence of instructions
    that were generated.
*/
extern struct InstrSeq *SaveSeq();

/*
    The function restores a sequence of instructions.
*/
extern struct InstrSeq *RestoreSeq();

/*
    The function works with immediate values
    in assembly code.
*/
extern char *Imm(int Val);

/*
    The function creates an offset for registers if neccessary.
*/
extern char *RegOff(int Offset, char *Reg);
