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
OFLAG = -o # Flag to indicate use of object file
CFLAG = -c # Flag to avoid linking
GFLAG = -g # Flag to invoke GDB debugger
FFLAG = -fsanitize=address # Flag to use fsanitize for memory leaks

# ===============================================
# Group of tests for the Symbol Table Test Driver.
# ===============================================

# Create an executable file to run your tests on the Symbol
# Table (SymTab.c) with the tester by compiling the object
# files that were produced by previous commands in this file.
output: SymTab.o SymTabTests.o
	$(CC) SymTab.o SymTabTests.o $(OFLAG) symtabtests $(GFLAG) -Wall -Werror -Wextra $(FFLAG)

# Create an object file for the Symbol Table file.
SymTab.o: SymTab.c SymTab.h
	$(CC) $(CFLAG) SymTab.c $(GFLAG) $(FFLAG)

# Create an object file for the testing file.
SymTabTests.o: SymTabTests.c
	$(CC) $(CFLAG) SymTabTests.c $(GFLAG) $(FFLAG)

# ===============================================
# Group of cleaning protocols after execution.
# ===============================================

# Remove any object files as well as the executable file.
clean:
	rm *.o symtabtests
