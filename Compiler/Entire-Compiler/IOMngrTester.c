#include "IOMngr.c"

int main(int argc, char *argv[]) {
    if (argc == 0) {
        fprintf(stdout, "Source File is required for program to run.\n");
        return 0;
    }
    openFiles(argv[1], argc > 1 ? argv[2] : NULL);

    
    char c = getNextSourceChar();

    while (c != EOF) {
        printf("%c", c);
        c = getNextSourceChar();
    }
    

   //fprintf(stdout, "%s", fread(1, sizeof(char), 1024, sourceFile));
    closeFiles();
    return 1;
}