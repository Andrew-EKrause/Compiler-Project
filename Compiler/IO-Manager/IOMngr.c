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
// such as files for the 
// IO Manager file.
FILE *sourceFile;
FILE *listingFile;
char *fileSourceName;

// Create another set of global
// variables for IO Manager.
char lineOfChars[MAXLINE];
int onWriteIndicatorLine;
int moveToNextLine;
int currentLineNum;
int currentColumnNum;

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

    // Each time you open files, reset the file 
    // information to NULL in order to avoid data
    // conflicts. This enables multiple sequential 
    // runs.
    sourceFile = NULL;
    listingFile = NULL;
    fileSourceName = NULL;

    // Reset the global variables here.
    onWriteIndicatorLine = 1;
    moveToNextLine = 1;
    currentLineNum = 1;
    currentColumnNum = -1;

    // Open the file with the source name and store the
    // opened file in the global sourceFile variable.
    // Also store the opened file name in a global var.
    sourceFile = fopen(sourceName, "r");

    // If the source file is empty, then
    // return 0 to indicate that the opening
    // failed.
    if(sourceFile == NULL) {
        return 0;
    }

    // If the source file is not NULL, then 
    // store the source name in the global 
    // variable for the file source name.
    fileSourceName = strdup(sourceName);

    // If the listingName parameter is not NULL,
    // open the file with that name and check if
    // the file is empty.
    if(listingName) {

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
    
    // If the source file is not NULL,
    // close the source file.
    if(sourceFile) {
        fclose(sourceFile);
    }

    // If the listing file is not NULL,
    // close the listing file.
    if(listingFile) {
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
 * increment the global variables pertaining
 * to line and column number as needed.
 * 
 * PLEASE NOTE: If there is a listing file,
 * lines are printed to that file here.
 * 
 */
char getNextSourceChar() {

    // Check if the source file exists. If the source file
    // exists, then proceed with the operations.
    if(sourceFile) {

        // Check if the end of the a given line was reached.
        if((int)(strlen(lineOfChars)) < currentColumnNum) {

            // If end of file reached, reset the 
            // variables for the next iteration.
            currentColumnNum = -1;
            moveToNextLine = 1;
            currentLineNum++;
        }

        // Check if you need to move to the next line in the file.
        if(moveToNextLine == 1) {

            // Once the newline is reached on any given line, 
            // get the next line from the source file.
            fgets(lineOfChars, MAXLINE, sourceFile); 

            // Check if the end of the file has been reached
            // after obtaining the next line in the file.
            if(feof(sourceFile)) {
                return EOF;
            }

            // Check if the listing file exists. If the listing
            // file exists, write out current line to it.
            if(listingFile) {
                fprintf(listingFile, "%d. %s", currentLineNum, lineOfChars);
            }

            // When you move to the next line, change variables to
            // indicate that you are now no longer on the old line.
            // The writeIndicatorLine variable is only for the case
            // when information is printed to standard out.
            onWriteIndicatorLine = currentLineNum;
            moveToNextLine = 0;
        }

        // Increase the current column number.
        currentColumnNum++;

        // Return the next source character.
        return lineOfChars[currentColumnNum];

    // If the source file does not exist, return EOF.
    } else {
        return EOF;
    }
}

/**
 * The function writes a line containing a 
 * single '^' character in the indicated
 * column. If there is no listing file, 
 * then the current line should be echoed 
 * to stdout the first time (for that line)
 * that writeIndicator or writeMessage is
 * called.
 * 
 * PLEASE NOTE: If there is NOT a listing file,
 * the appropriate lines are written to standard
 * out through this function.
 * 
 * MAYBE ADD CHECKS TO SEE IF FILE IS NULL AS WELL AS
 * IF THE FUNCTION WAS USED IN THE PROPER ORDER!!!
 * 
 */
void writeIndicator(int column) {

    // Create a counter variable for determining
    // which column needs to be written to.
    int i = 0;

    //printf("%d\n", onWriteIndicatorLine);
    //printf("%d\n", currentLineNum);

    // If the write indicator was called, make sure that
    // the only printed line is the line that write 
    // indicator was called on.
    if(!listingFile && onWriteIndicatorLine == currentLineNum) {

        //printf("INSIDE WRITE INDICATOR FOR STDOUT\n");

        // Print the line that has errors or other messages associated 
        // with it to standard output.
        fprintf(stdout, "%d. %s", currentLineNum, lineOfChars);

        // Set the write indicator variable 
        // to zero in order to only write out
        // the line associated with the function
        // and no other line.
        onWriteIndicatorLine = 0;
    }

    // If the listing file is not NULL, place
    // a indicator in the appropriate location
    // of the listing file. Otherwise, write the 
    // '^' character to standard output.
    if(listingFile) {

        // While the counter variable is less than the
        // column parameter, move the '^' variable by
        // a space until you reach the correct location
        // to insert.
        while(i < (column + countDigitSpace())) {

            // Place a space in the listing file 
            // and increment the counter variable.
            fprintf(listingFile, " ");
            i++;
        }

        // Put the '^' indicator in the listing file
        // after reaching the location based on the column.
        fprintf(listingFile, "^");
        fprintf(listingFile, "\n");

    } else {

        //printf("INSIDE WRITE INDICATOR FOR STDOUT");
        // While the counter variable is less than the
        // column parameter, move the '^' variable by
        // a space until you reach the correct location
        // to insert.
        while(i < (column + countDigitSpace())) {

            // Place a space in the standard output
            // and increment the counter variable.
            fprintf(stdout, " ");
            i++;
        }

        // Put the '^' indicator in the standard output
        // after reaching the location based on the column.
        fprintf(stdout, "^");
        fprintf(stdout, "\n");
    }
}

/**
 * The function counts the number of spaces
 * taken up by the line numbers in the source
 * file as well as the space and dot characters.
 */
int countDigitSpace() {
     
     // The number variable is initially one to
     // account for the dot and space values.
     int counter = 2;
     int number = currentLineNum;

    // While the number is not zero,
    // count the digits in the number.
     while(number != 0) {

         // Count digits and increment counter.
         number = number / 10;
         counter++;
     }

    // Return the counter variable.
    return counter;
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
    if(listingFile) {

        // If the listing File is not NULL,
        // Put a message in the listing file
        // along with a newline character.
        fprintf(listingFile, "%s\n", message); 

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
