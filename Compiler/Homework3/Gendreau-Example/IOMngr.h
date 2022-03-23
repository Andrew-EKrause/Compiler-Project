/*
    API for a IO Manager. The IO Manager opens a source file
    as well as a listing file if the name of the listing file
    is provided. The IO Manager also has the ability to close
    file(s). The next source char of an in put file can be 
    returned by this program as well as the current line and
    column numbers. An error message is also written out in
    certain cases.    
*/

// Define the maximum number of characters per line.
#define MAXLINE 1024

/* 
    The function closes the file(s)
    that were opened by the IO Manager.
*/
int openFiles(char *sourceName, char *listingName);

/* 
    The function closes any files that
    were opened by the IO Manager. This
    operation is usually executed at the
    end of the program.
*/
void closeFiles();

/*
    The function returns the next source
    character. It also echoes the lines
    in the source file to the listing file
    if the listing file exists. The lines
    in the listing file should be numbered.
    Return EOF when the end of the source
    file is reached.
*/
char getNextSourceChar();

/*
    The function writes an indicator marker at
    a specified column in a file. It is used to
    help indicate where an error may have occurred
    in the file.
*/
void writeIndicator(int column);

/*
    The function counts the number of digits
    that a given line number and returns the
    total digits. This function is used only
    for formatting the output.
*/
int countDigitSpace();

/*
    The function is used to write
    a message, usually an error
    message to certain files or
    standard output.
*/
void writeMessage(char *message);

/*
    The function returns the current
    line number.
*/
int getCurrentLineNum();

/*
    The function returns the current 
    column number.
*/
int getCurrentColumnNum();
