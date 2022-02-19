
output: IOMngr.o lex.yy.c
	gcc IOMngr.o lexInput.txt lexOutput.txt lex.yy.c -o lextests -g -Wextra -fsanitize=address

IOMngr.o: IOMngr.c IOMngr.h
	gcc -c IOMngr.c -g -fsanitize=address

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c -g -fsanitize=address

clean:
	rm *.o lextests