
output: SymTab.o SymTabTests.o
	gcc SymTab.o SymTabTests.o -o symtabtests -g -Wall -Werror -Wextra -fsanitize=address

SymTab.o: SymTab.c SymTab.h
	gcc -c SymTab.c -g -fsanitize=address

SymTabTests.o: SymTabTests.c
	gcc -c SymTabTests.c -g -fsanitize=address

clean:
	rm *.o symtabtests
