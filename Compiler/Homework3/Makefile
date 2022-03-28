# This makefile is used for running tests
# on the homework 3 assignment for the 
# Compilers class (CS 442) at UWL. Multiple
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
LEX = h3.l # Lexical file; this file name can change
BISON = h3.y # Bison file; this file name can change
OFLAG = -o # Flag to indicate use of object file
CFLAG = -c # Flag to avoid linking
GFLAG = -g -ggdb # Flags to invoke GDB debugger
WFLAG = -Wall -Werror -Wextra # Flags to show warnings
MEMCHECK = -fsanitize=address -fno-omit-frame-pointer -static-libsan 
# Flags directly above are used to check for memory leaks

# ===============================================
# Run all of the tests here. The tests run all 
# files needed to interpret the programs.
# ===============================================
main:
	bison -d $(BISON)
	flex $(LEX)
	$(CC) $(OFLAG) h3 h3.tab.c lex.yy.c semantics.c SymTab.c IOMngr.c main.c $(GFLAG) $(MEMCHECK)

# ===============================================
# Group of cleaning protocols after execution.
# ===============================================

# Remove any object files as well as the executable files.
clean:
	rm -r h3.dSYM
	rm h3.tab.c lex.yy.c h3
