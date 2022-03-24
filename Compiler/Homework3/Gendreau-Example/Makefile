# This makefile is used for running tests
# on the example given by the professor for 
# the Compilers class (CS 442) at UWL. Multiple
# C files are compiled to run the program.
# The SymTab.c file and the IOMngr.c file
# are both compiled and used to help run the
# program. In addition to the C files, lex
# and yacc files are used to help properly 
# process the rules of the language being
# processed. The program itself consists 
# of the semantics.c and main.c files.
#
# Author: Andrew Krause
# Date: 2022-03-25
#

# ===============================================
# Include makefile flags here.
# ===============================================
CC = gcc # Flag to pass to gcc
LEX = boolLex.l # Lexical file; this file name can change
BISON = boolExpr.y # Bison file; this file name can change
OFLAG = -o # Flag to indicate use of object file
CFLAG = -c # Flag to avoid linking
GFLAG = -g # Flag to invoke GDB debugger
FFLAG = -fsanitize=address # Flag to use fsanitize for memory leaks

# ===============================================
# Run all of the tests here. The tests for the
# lexical analysis are run in main as well.
# ===============================================
main:
	bison -d $(BISON)
	flex $(LEX)
	$(CC) $(OFLAG) gendreau-h3 boolExpr.tab.c lex.yy.c semantics.c SymTab.c IOMngr.c main.c $(GFLAG) $(FFLAG)

# ===============================================
# Group of cleaning protocols after execution.
# ===============================================

# Remove any object files as well as the executable files.
clean:
	rm -r gendreau-h3.dSYM
	rm boolExpr.tab.c lex.yy.c gendreau-h3
