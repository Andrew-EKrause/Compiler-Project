/**
 * The IO Manager file contains functions that enable
 * the IO Manager to perform operations on the source
 * file(s) that are passed through it. The IO Manager
 * is able to open a source file, open a listing file
 * if one is provided (this is a file with line numbers
 * and error messages), close file(s), return the next 
 * source character (every character), write a indicator
 * marker at a specified column, return the current line
 * number, and return the current column number.
 * 
 * @file IOMngr.c
 * @author Andrew Krause
 * @version 0.1
 * @date 2022-02-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// Include the standard I/O library,
// a second C library of functions,
// and the  IOMngr.h source file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IOMngr.h"

// Create global variables 
// for the IO Manager file.
FILE *sourceFile;
FILE *secondSourceFile;
FILE *listingFile;
char *fileSourceName;
int currentLineNum = 0;
int currentColumnNum = 0;

/**
 * The function opens the source file whose name 
 * is given in the sourceName paramter. If the 
 * listingName paramter is not NULL, open the listing
 * file whose name is given in the listingName param.
 * If listingName is NULL , the output goes to stdout.
 * Return 1 if the file open(s) were successfull, 
 * otherwise return 0.
 */
int openFiles(char *sourceName, char *listingName) {

    // Open the file with the source name and store the
    // opened file in the global sourceFile variable.
    // Also store the opened file name in a global var.
    sourceFile = fopen(sourceName, "r");
    // fileSourceName = strdup(sourceName); // --> ORIGINALLY LISTED HERE

    // If the source file is empty, then
    // return 0 to indicate that the opening
    // failed.
    if(sourceFile == NULL) {
        return 0;
    }

    // --> MOVE HERE FOR NOW
    // If the source file is not NULL, then 
    // store the source name in the global 
    // variable for the file source name.
    fileSourceName = strdup(sourceName);

    // If the listingName parameter is not NULL,
    // open the file with that name and check if
    // the file is empty.
    if(listingName != NULL) {

        // Open the listing file with the listingName.
        // Immediately give it read/write permissions.
        listingFile = fopen(listingName, "w+");

        // If the listing file is NULL, return 0.
        if(listingFile == NULL) {
            return 0;
        }
    }

    // If the file open(s) were successful,
    // return 1 to indicate completion.
    return 1;
}

/**
 * The function closes the file(s)
 * that were opened by the other 
 * IO Manager functions.
 */
void closeFiles() {
    
    // --> CONSIDER ADDING NULL CHECKS
    // Close the source file.
    fclose(sourceFile);

    // If the listing file is not NULL,
    // close the listing file.
    if(listingFile != NULL) {

        fclose(listingFile);
    }
}

/**
 * The function returns the next source char
 * in the source file that was opened. The 
 * function is also responsible for echoing
 * the lines in the source file to the listing
 * file (if one exists). The lines in the 
 * listing file should be numbered. Using
 * fgetc, EOF should be returned when the 
 * end of the source file is reached. Also,
 * increment the global variables pertianing
 * to line and column number as needed.
 */
char getNextSourceChar() {

    // --> REMEMBER THAT WHENEVER THIS FUNCTION IS CALLED,
    // --> IT IS ASSUMED THAT A SOURCE FILE WILL BE PROVIDED.

    // Create a variable to store the next source
    // character in it from the source file via
    // the fgetc function.
    char nextSourceChar = fgetc(sourceFile);

    // --> MAY NOT NEED THIS!!!
    // Check if the end of the file has been reached.
    // if(nextSourceChar == EOF) {

    //     return EOF;
    // }

    // Check if the next source character is a newline.
    if(nextSourceChar == '\n') {

        // If the next source character in the file
        // is a newline, set the current column number
        // to zero and increase the current line num.
        currentColumnNum = 0;
        currentLineNum++;
    } else {

        // Otherwise, increase the current 
        // column number.
        currentColumnNum++;
    }

    // Return the next source character.
    return nextSourceChar;
}

/**
 * The function writes a line containing a 
 * single '^' character in the indicated
 * column. If there is no listing file, 
 * then the current line should be echoed 
 * to stdout the first time (for that line)
 * that writeIndicator or writeMessage is
 * called.
 */
void writeIndicator(int column) {

    // Create a counter variable for determining
    // which column needs to be written to.
    int i = 0;

    // In order to avoid conflicting data, use the
    // second source file variable and open the source
    // file using that variable.
    secondSourceFile = fopen(fileSourceName, "r");

    // Specify the number of characters read per line.
    char charactersPerLine[1024]; // --> MAYBE 1028

    // While the counter variable is less than the
    // current column number, read a line from the
    // specified stream.
    while(i <= getCurrentLineNum()) {

        // Read line using fgets() and increment counter.
        fgets(charactersPerLine, 1024, secondSourceFile); // --> MAYBE 124 OR 128
        i++;
    }

    // Reset the counter variable back to zero.
    // Then check if the listing file is NULL.
    i = 0;

    // If the listing file is not NULL, place
    // a indicator in the appropriate location
    // of the listing file.
    if(listingFile != NULL) {

        // Write the specified string to the stream
        // up to but not including the NULL character.
        fputs(charactersPerLine, listingFile);

        // While the counter variable is less than the
        // column parameter, move the '^' variable by
        // a space until you reach the correct location
        // to insert.
        while(i < column) {

            // Place a space in the listing file 
            // and increment the counter variable.
            fputc(' ', listingFile);
            i++;
        }

        // Put the '^' indicator in the listing file
        // after reaching the location based on the column.
        fputc('^', listingFile);
    } else {

        // Otherwise, write the '^' character
        // to standard output by echoing the
        // line to stdout the first time (for
        // that line) that writeIndicator or
        // writeMessage is called. 
        fprintf(stdout, "\n");

        // While the counter variable is less than the
        // column parameter, move the '^' variable by
        // a space until you reach the correct location
        // to insert.
        while(i < column) {

            // Place a space in the standard output
            // and increment the counter variable.
            fprintf(stdout, " ");
            i++;
        }

        // Put the '^' indicator in the standard output
        // after reaching the location based on the column.
        fprintf(stdout, "^");
    }
}

/**
 * The function writes a message out
 * to the listingFile. If the listing 
 * file is NULL, the message is written
 * out to standard output. Error messages
 * are shown in the program through this
 * function.
 */
void writeMessage(char *message) {

    // If the listing File is not NULL,
    // Put a message in the listing file
    // along with a newline character.
    if(listingFile != NULL) {

        // If the listing File is not NULL,
        // Put a message in the listing file
        // along with a newline character.
        fputs(message, listingFile);
        fputc('\n', listingFile);
    } else {

        // If the listing file is NULL, write
        // the message to standard out.
        fprintf(stdout, "%s\n", message);
    }
}

/**
 * The function returns the current
 * line number for the source file.
 */
int getCurrentLineNum() {
    
    return currentLineNum;
}

/**
 * The function returns the current
 * column number for the source file.
 */
int getCurrentColumnNum() {
    
    return currentColumnNum;
}
