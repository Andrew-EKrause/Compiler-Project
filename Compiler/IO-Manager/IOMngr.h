/*
    API for a IO Manager. The IO Manager 
    
*/

#define MAXLINE 1024

int openFiles(char *sourceName, char *listingName);

void closeFiles();

char getNextSourceChar();

void writeIndicator(int column);

void writeMessage(char *message);

int getCurrentLineNum();

int getCurrentColumnNum();