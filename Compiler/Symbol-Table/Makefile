# This makefile is used for running tests
# on the Symbol Table file (SymTab.c). The 
# Symbol Table is a component of the Compiler
# Project. There are several commands in this
# makefile that compile multiple .c files and
# produce an executable that runs the tests.
#
# Author: Andrew Krause
# Date: 2022-01-26
#

# ===============================================
# Include makefile flags here.
# ===============================================
CC = gcc # Flag to pass to gcc
LEX = lexical.l # Lexical file; this file name can change
OFLAG = -o # Flag to indicate use of object file
CFLAG = -c # Flag to avoid linking
GFLAG = -g -ggdb # Flags to invoke GDB debugger
WFLAG = -Wall -Werror -Wextra # Flags to show warnings
MEMCHECK = -fsanitize=address -fno-omit-frame-pointer -static-libsan 
# Flags directly above are used to check for memory leaks

# ===============================================
# Group of tests for the Symbol Table Test Driver.
# ===============================================

# Create an executable file to run your tests on the Symbol
# Table (SymTab.c) with the tester by compiling the object
# files that were produced by previous commands in this file.
output: SymTab.o SymTabTests.o
	$(CC) SymTab.o SymTabTests.o $(OFLAG) symtabtests $(GFLAG) $(WFLAG) $(MEMCHECK)

# Create an object file for the Symbol Table file.
SymTab.o: SymTab.c SymTab.h
	$(CC) $(CFLAG) SymTab.c $(GFLAG) $(MEMCHECK)

# Create an object file for the testing file.
SymTabTests.o: SymTabTests.c
	$(CC) $(CFLAG) SymTabTests.c $(GFLAG) $(MEMCHECK)

# ===============================================
# Group of cleaning protocols after execution.
# ===============================================

# Remove any object files as well as the executable file.
clean:
	rm *.o symtabtests
