# This makefile is used for running tests
# on the IO Manager file (IOMngr.c). The 
# IO Manager, like Symbol Table, is also 
# a component of the Compiler Project. 
# There are several commands in this makefile 
# that compile multiple .c files and produce 
# an executable that runs the tests for the 
# IO Manager. Lexical analysis is also conducted.
#
# Author: Andrew Krause
# Date: 2022-02-21
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
# Run all of the tests here. The tests for the
# lexical analysis are run in main as well.
# ===============================================
main: IOMngr.o IOMngrTests.o
	$(CC) IOMngr.o IOMngrTests.o $(OFLAG) iomanagertests $(GFLAG) -Wextra $(FFLAG)
	flex lexical.l
	$(CC) IOMngr.c lex.yy.c -ll $(OFLAG) lexicaltests

# ===============================================
# Group of tests for the IO Manager Test Driver.
# ===============================================

# Create an object file for the IO Manager file.
IOMngr.o: IOMngr.c IOMngr.h
	$(CC) $(CFLAG) IOMngr.c $(GFLAG) $(FFLAG)

# Create an object file for the testing file.
IOMngrTests.o: IOMngrTests.c
	$(CC) $(CFLAG) IOMngrTests.c $(GFLAG) $(FFLAG)

# ===============================================
# Group of cleaning protocols after execution.
# ===============================================

# Remove any object files as well as the executable files.
clean:
	rm *.o iomanagertests
	rm lexicaltests
