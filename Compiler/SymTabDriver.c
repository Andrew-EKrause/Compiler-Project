/**
 * The file contains main function with many different
 * tests for the other functions in the SymTab.c file.
 * The tests determine if the Symbol Table created in 
 * the SymTab.c file behaves as expected under different
 * scenarios and function calls. A final summary of the
 * test results is printed out at the end of the program.
 * 
 * IMPORTANT: To run this file, type the following command
 * in to the terminal: gcc SymTab.c SymTabDriver.c 
 * 
 * @file SymTabDriver.c
 * @author Andrew Krause
 * @version 0.1
 * @date 2022-01-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// Include the standard I/O library
// as well as the  SymTab.h file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SymTab.h"

// Create a main function to test the Symbol Table
// based off of the SymTab.h file and the SymTab.c file.
int main() {

   // Create symbol tables to test the 
   // functions in the SymTab.c file.
   SymTab *testTable1;
   SymTab *testTable2;
   SymTab *testTable3;

   // Display a message to the user indicating the
   // start of tests for the Symbol Table
   printf("\n\n\n\n\n\n---------------------------------------------------------");
   printf("\nTESTS FOR SYMBOL TABLE:");
   printf("\n---------------------------------------------------------\n");

   // Tests for the *createSymTab(int size) function.
   printf("\n--> Tests for SymTab *createSymTab(int size):\n\n");

   // Create new symbol tables.
   testTable1 = createSymTab(6);
   testTable2 = createSymTab(20);
   testTable3 = createSymTab(100);

   // Create an integer to track the number of passed tests.
   int numPassed1 = 0;

   // Create if statements to determine how many  
   // tests were passed for the create function.
   if(testTable1->size == 6) {
      numPassed1 += 1;
   }
   if(testTable2->size == 20) {
      numPassed1 += 1;
   }
   if(testTable3->size == 100) {
      numPassed1 += 1;
   }

   // Determine the if the size of the symbol tables matches 
   // the expected output in the print statements.
   printf("EXPECTED: Size of testTable1 is: < 6 >\n");
   printf("ACTUAL: Size of testTable1 is: %d\n", testTable1->size);
   printf("\n");
   printf("EXPECTED: Size of testTable1 is: < 20 >\n");
   printf("ACTUAL: Size of testTable1 is: %d\n", testTable2->size);
   printf("\n");
   printf("EXPECTED: Size of testTable1 is: < 100 >\n");
   printf("ACTUAL: Size of testTable1 is: %d\n", testTable3->size);
   printf("\n");
   printf("(1) SUMMARY: < %d/3 > tests passed for *createSymTab(int size).", numPassed1);
   printf("\n---------------------------------------------------------\n");

   // Include an extra print statement at the end.
   printf("\n");
   // ===================================================================================================




   // Tests for the destroySymTab(SymTab *table) function.
   printf("\n--> Tests for SymTab destroySymTab(SymTab *table):\n\n");
   printf("--> WITH THESE TEST I HAVE BEEN GETTING A WERID ERROR. RUN REPEATEDLY. <--\n\n");
   printf("--> UNCOMMENT THE CODE IN THE TEST FILE TO RUN THIS PARTICULAR TEST. <--\n\n");

   // Destroy the symbol tables.
   destroySymTab(testTable1);
   destroySymTab(testTable2);
   destroySymTab(testTable3);

   // --> UNCOMMENT EVERYTHING BELOW THIS LINE TO THE "--> UNCOMMENT ENDMARKER"

   // // Create an integer to track the number of passed tests.
   // int numPassed2 = 0;

   // // Determine the if the size of the symbol tables matches 
   // // the expected output in the print statements.
   // printf("EXPECTED: testTable1 has been cleared\n");
   // if(testTable1 == NULL) {
   //    numPassed2 += 1;
   //    printf("ACTUAL: testTable1 has been cleared\n");
   // } else {
   //    printf("ACTUAL: testTable1 has NOT been cleared\n");
   // }
   // printf("\n");

   // printf("EXPECTED: testTable2 has been cleared\n");
   // if(testTable2->current == NULL) {
   //    numPassed2 += 1;
   //    printf("ACTUAL: testTable2 has been cleared\n");

   // } else {
   //    printf("ACTUAL: testTable2 has NOT been cleared\n");
   // }
   // printf("\n");

   // printf("EXPECTED: testTable3 has been cleared\n");
   // if(testTable3->current == NULL) {
   //    numPassed2 += 1;
   //    printf("ACTUAL: testTable3 has been cleared\n");

   // } else {
   //    printf("ACTUAL:testTable3 has NOT been cleared\n");
   // }
   // printf("\n");

   // --> UNCOMMENT ENDMARKER

   // printf("(2) SUMMARY: < %d/3 > tests passed for *destroySymTab(SymTab *table).", numPassed2);
   printf("\n---------------------------------------------------------\n");

   // Include an extra print statement at the end.
   printf("\n");
   // ===================================================================================================




   // Tests for the enterName(SymTab *table, char *name) function.
   printf("\n--> Tests for SymTab enterName(SymTab *table, char *name):\n\n");

   // First, create new symbol tables.
   testTable1 = createSymTab(6);
   testTable2 = createSymTab(20);
   testTable3 = createSymTab(100);

   // Create integers to track the number of passed tests.
   int returnNumPassed3 = 0;
   int numPassed3 = 0;

   // Enter a name for the first test table.
   int entry1 = enterName(testTable1, "length");

   // Enter names for the second test table.
   int entry2 = enterName(testTable2, "length");
   int entry3 = enterName(testTable2, "width");
   int entry4 = enterName(testTable2, "height");

   // Enter names for the third test table.
   int entry5 = enterName(testTable3, "length");
   int entry6 = enterName(testTable3, "length");
   int entry7 = enterName(testTable3, "width");
   int entry8 = enterName(testTable3, "height");
   int entry9 = enterName(testTable3, "perimeter");
   int entry10 = enterName(testTable3, "area");

   // Create if statements to determine how many  
   // tests were passed for the enter name function
   // for the return values.
   if(entry1 == 1) {
      returnNumPassed3 += 1;
   }
   if(entry2 == 1) {
      returnNumPassed3 += 1;
   }
   if(entry3 == 1) {
      returnNumPassed3 += 1;
   }
   if(entry4 == 1) {
      returnNumPassed3 += 1;
   }
   if(entry5 == 1) {
      returnNumPassed3 += 1;
   }
   if(entry6 == 0) {
      returnNumPassed3 += 1;
   }
   if(entry7 == 1) {
      returnNumPassed3 += 1;
   }
   if(entry8 == 1) {
      returnNumPassed3 += 1;
   }
   if(entry9 == 1) {
      returnNumPassed3 += 1;
   }
   if(entry10 == 1) {
      returnNumPassed3 += 1;
   }

   // Create char arrays to determine the current 
   // attribute name value.
   char current1[strlen(getCurrentName(testTable1)) + 1];
   strcpy(current1, getCurrentName(testTable1));

   char current2[strlen(getCurrentName(testTable2)) + 1];
   strcpy(current2, getCurrentName(testTable2));

   char current3[strlen(getCurrentName(testTable3)) + 1];
   strcpy(current3, getCurrentName(testTable3));

   // Determine the if the current attribute name values are 
   // correct given all of the entries to each symbol table for.
   printf("EXPECTED: current name of testTable1 is: < length >\n");
   printf("ACTUAL: current name of testTable1 is: %s\n", current1);
   if(strcmp(current1, "length") == 0) {
      numPassed3 += 1;
   }
   printf("\n");

   printf("EXPECTED: current name of testTable2 is: < height >\n");
   printf("ACTUAL: current name of testTable2 is: %s\n", current2);
   if(strcmp(current2, "height") == 0) {
      numPassed3 += 1;
   }
   printf("\n");

   printf("EXPECTED: current name of testTable3 is: < area >\n");
   printf("ACTUAL: current name of testTable3 is: %s\n", current3);
   if(strcmp(current3, "area") == 0) {
      numPassed3 += 1;
   }
   printf("\n");

   printf("(3.1) SUMMARY: < %d/10 > tests passed for enterName(SymTab *table, char *name) with expected return values.", returnNumPassed3);
   printf("\n(3.2) SUMMARY: < %d/3 > tests passed for enterName(SymTab *table, char *name) with expected current name values.", numPassed3);
   printf("\n---------------------------------------------------------\n");

   // Include an extra print statement at the end.
   printf("\n");
   // ===================================================================================================




   // Tests for the enterName(SymTab *table, char *name) function.
   printf("\n--> Tests for SymTab findName(SymTab *table, char *name):\n");
   printf("--> (Symbol tables used in this test are the same as the tables in the enterName() test.)\n\n");

   // Create an integer to track the number of tests passed.
   int numPassed4 = 0;

   // Create names to search for in the symbol tables.
   char testName1[] = "length";
   char testName2[] = "width";
   char testName3[] = "height";
   char testName4[] = "perimeter";
   char testName5[] = "foo";
   char testName6[] = "Descartes";

   // Create variables to store the results of the findName() function.
   // The function indicates whether the name was found or not.
   int firstTableFound1 = findName(testTable1, testName1); // 1
   int firstTableFound2 = findName(testTable1, testName2); // 0
   int firstTableFound3 = findName(testTable1, testName5); // 0

   int secondTableFound1 = findName(testTable2, testName1); // 1
   int secondTableFound2 = findName(testTable2, testName2); // 1
   int secondTableFound3 = findName(testTable2, testName4); // 0

   int thirdTableFound1 = findName(testTable3, testName3); // 1
   int thirdTableFound2 = findName(testTable3, testName6); // 0
   int thirdTableFound3 = findName(testTable3, testName4); // 1

   // Print out the results of the tests for testTable1.
   printf("EXPECTED: < length > is found in testTable1.\n");
   if(firstTableFound1 == 1) {
      numPassed4 += 1;
      printf("ACTUAL: < length > is found in testTable1.");
   } else {
      printf("ACTUAL: < length > NOT found in testTable1.");    
   }
   printf("\n\n");

   printf("EXPECTED: < width > is not found in testTable1.\n");
   if(firstTableFound2 == 0) {
      numPassed4 += 1;
      printf("ACTUAL: < width > is not found in testTable1.");
   } else {
      printf("ACTUAL: < width > IS found in testTable1.");    
   }
   printf("\n\n");

   printf("EXPECTED: < foo > is not found in testTable1.\n");
   if(firstTableFound3 == 0) {
      numPassed4 += 1;
      printf("ACTUAL: < foo > is not found in testTable1.");
   } else {
      printf("ACTUAL: < foo > IS found in testTable1.");    
   }
   printf("\n\n");

   // Print out the results of the tests for testTable2.
   printf("EXPECTED: < length > is found in testTable2.\n");
   if(secondTableFound1 == 1) {
      numPassed4 += 1;
      printf("ACTUAL: < length > is found in testTable2.");
   } else {
      printf("ACTUAL: < length > NOT found in testTable2.");    
   }
   printf("\n\n");

   printf("EXPECTED: < width > is found in testTable2.\n");
   if(secondTableFound2 == 1) {
      numPassed4 += 1;
      printf("ACTUAL: < width > is found in testTable2.");
   } else {
      printf("ACTUAL: < width > NOT found in testTable2.");    
   }
   printf("\n\n");

   printf("EXPECTED: < perimeter > is not found in testTable2.\n");
   if(secondTableFound3 == 0) {
      numPassed4 += 1;
      printf("ACTUAL: < perimeter > is not found in testTable2.");
   } else {
      printf("ACTUAL: < perimeter > IS found in testTable2.");    
   }
   printf("\n\n");

   // Print out the results of the tests for testTable3.
   printf("EXPECTED: < height > is found in testTable3.\n");
   if(thirdTableFound1 == 1) {
      numPassed4 += 1;
      printf("ACTUAL: < height > is found in testTable3.");
   } else {
      printf("ACTUAL: < height > NOT found in testTable3.");    
   }
   printf("\n\n");

   printf("EXPECTED: < Descartes > is not found in testTable3.\n");
   if(thirdTableFound2 == 0) {
      numPassed4 += 1;
      printf("ACTUAL: < Descartes > is not found in testTable3.");
   } else {
      printf("ACTUAL: < Descartes > IS found in testTable3.");    
   }
   printf("\n\n");

   printf("EXPECTED: < perimeter > is found in testTable3.\n");
   if(thirdTableFound3 == 1) {
      numPassed4 += 1;
      printf("ACTUAL: < perimeter > is found in testTable3.");
   } else {
      printf("ACTUAL: < perimeter > is NOT found in testTable3.");    
   }
   printf("\n\n");

   // Print out the summary of the test results.
   printf("(4) SUMMARY: < %d/9 > tests passed for findName(SymTab *table, char *name) with expected return values.", numPassed4);
   printf("\n---------------------------------------------------------\n");

   // Include an extra print statement at the end.
   printf("\n");
   // ===================================================================================================




   // Tests for the hasCurrent(SymTab *table) function.
   printf("\n--> Tests for SymTab hasCurrent(SymTab *table):\n");
   printf("--> (Symbol tables used in this test are the same as the tables in the enterName() test.)\n\n");

   // Create an empty symbol table.
   SymTab *testTable4 = createSymTab(2);

   // Create an integer to track the number of tests passed.
   int numPassed5 = 0;

   // Create integers to test if a given table has current.
   int firstCurrent = hasCurrent(testTable1); // 1
   int secondCurrent = hasCurrent(testTable2); // 1
   int thirdCurrent = hasCurrent(testTable3); // 1
   int fourthCurrent = hasCurrent(testTable4); // 0

   // Print out the results of the tests for testTable1.
   printf("EXPECTED: current of testTable1 does reference a name.\n");
   if(firstCurrent == 1) {
      numPassed5 += 1;
      printf("ACTUAL: current of testTable1 does reference a name.");
   } else {
      printf("ACTUAL: current of testTable1 does NOT reference a name.");    
   }
   printf("\n\n");

   // Print out the results of the tests for testTable2.
   printf("EXPECTED: current of testTable2 does reference a name.\n");
   if(secondCurrent == 1) {
      numPassed5 += 1;
      printf("ACTUAL: current of testTable2 does reference a name.");
   } else {
      printf("ACTUAL: current of testTable2 does NOT reference a name.");    
   }
   printf("\n\n");

   // Print out the results of the tests for testTable3.
   printf("EXPECTED: current of testTable3 does reference a name.\n");
   if(thirdCurrent == 1) {
      numPassed5 += 1;
      printf("ACTUAL: current of testTable3 does reference a name.");
   } else {
      printf("ACTUAL: current of testTable3 does NOT reference a name.");    
   }
   printf("\n\n");

   // Print out the results of the tests for testTable4.
   printf("EXPECTED: current of testTable4 does not reference a name.\n");
   if(fourthCurrent == 0) {
      numPassed5 += 1;
      printf("ACTUAL: current of testTable4 does not reference a name.");
   } else {
      printf("ACTUAL: current of testTable4 DOES reference a name.");    
   }
   printf("\n\n");

   // Print out the summary of the test results.
   printf("(5) SUMMARY: < %d/4 > tests passed for hasCurrent(SymTab *table) with expected return values.", numPassed5);
   printf("\n---------------------------------------------------------\n");

   // Include an extra print statement at the end.
   printf("\n");
   // ===================================================================================================




   // Tests for the setCurrentAttr(SymTab *table, void *attr) and *getCurrentAttr(SymTab *table) functions.
   printf("\n--> Tests for setCurrentAttr(SymTab *table, void *attr) and *getCurrentAttr(SymTab *table):\n");
   printf("--> (Symbol tables used in this test are the same as tables in the enterName() test.)\n\n");
   printf("--> (The SET and GET methods are both tested here given that they can rely on each other.)\n\n");

   // First enter names into testTable4 in order to next set attributes.
   int entry11 = enterName(testTable4, "hello");
   int entry12 = enterName(testTable4, "world");

   // Create an integer to track the number of tests passed.
   int numPassed6And7 = 0;

   // Create pointers to pass into the function as an attribute parameter.
   // Create a pointer for the value of 4.
   void *memory1 = (int *)malloc(sizeof(int));
   int *four = (int *)memory1;
   *four = 4;

   // Create a pointer for the value of 100.
   void *memory2 = (int *)malloc(sizeof(int));
   int *hundred = (int *)memory2;
   *hundred = 100;

   // Create a pointer for the value of "c".
   char *characterC = strdup("c");

   // Create a pointer for the value of "hello".
   char *helloString = strdup("hello");

   // Set the current attributes of the four symbol tables that were created earlier on.
   setCurrentAttr(testTable1, four);
   setCurrentAttr(testTable2, hundred);
   setCurrentAttr(testTable3, characterC);
   setCurrentAttr(testTable4, helloString); 

   // Use the getCurrentAttr function to check if the current attributes were set properly.
   printf("EXPECTED: current attribute of testTable1 is < 4 >\n");
   if(*(int *)(getCurrentAttr(testTable1)) == 4) {
      printf("ACTUAL: current attribute of testTable1 is %d", *(int *)(testTable1->current->attribute));
      numPassed6And7 += 1;
   } else {
      printf("ACTUAL: current attribute of testTable1 is NOT 4");
   }
   printf("\n\n");

   printf("EXPECTED: current attribute of testTable2 is < 100 >\n");
   if(*(int *)(getCurrentAttr(testTable2)) == 100) {
      printf("ACTUAL: current attribute of testTable2 is %d", *(int *)(testTable2->current->attribute));
      numPassed6And7 += 1;
   } else {
      printf("ACTUAL: current attribute of testTable2 is NOT 100");
   }
   printf("\n\n");

   printf("EXPECTED: current attribute of testTable3 is < c >\n");
   if(strcmp(getCurrentAttr(testTable3), "c") == 0) {
      printf("ACTUAL: current attribute of testTable3 is %c", *(char *)(testTable3->current->attribute));
      numPassed6And7 += 1;
   } else {
      printf("ACTUAL: current attribute of testTable3 is NOT c");
   }
   printf("\n\n");

   printf("EXPECTED: current attribute of testTable4 is < hello >\n");
   if(strcmp(getCurrentAttr(testTable4), "hello") == 0) {
      // printf("ACTUAL: current attribute of testTable4 is %s", *(testTable4->current->attribute));
      printf("ACTUAL: current attribute of testTable4 is ");

      // Cast the void pointer to a char value and print out 
      // each character in the void pointer.
      char *printPointer = (char *)(testTable4->current->attribute); 
	
      // While the temporary pointer does not equal the
      // NULL-terminating character, print out each 
      // character in the void pointer.
      while(*printPointer != '\0'){ 
         printf("%c",*printPointer); 
         printPointer++; 
      }

      // Like the previous checks, increase the number 
      // of passed tests if the conditions were met.
      numPassed6And7 += 1;
   } else {
      printf("ACTUAL: current attribute of testTable4 is NOT hello");
   }
   printf("\n\n");

   // Free the memory that was used above for the test cases.
   free(memory1);
   free(memory2);
   free(characterC);
   free(helloString);

   // Print out the summary of the test results.
   printf("(6) SUMMARY: < %d/4 > tests passed for setCurrentAttr(SymTab *table, void *attr) and *getCurrentAttr(SymTab *table) with expected values.", numPassed6And7);
   printf("\n---------------------------------------------------------\n");

   // Include an extra print statement at the end.
   printf("\n");
   // ===================================================================================================




   // Tests for the getCurrentName(SymTab *table) function.
   printf("\n--> Tests for getCurrentName(SymTab *table):\n\n");

   // Declare new symbol tables before allocating size for them.
   SymTab *testTable5;
   SymTab *testTable6;
   SymTab *testTable7;

   // Create new symbol tables to test the function with.
   testTable5 = createSymTab(5);
   testTable6 = createSymTab(30);
   testTable7 = createSymTab(200);

   // Enter names into testTable5.
   int entry13 = enterName(testTable5, "the");
   int entry14 = enterName(testTable5, "times");
   int entry15 = enterName(testTable5, "change");

   // Enter names into testTable6.
   int entry16 = enterName(testTable6, "once");
   int entry17 = enterName(testTable6, "upon");
   int entry18 = enterName(testTable6, "time");

   // Enter names into testTable7.
   int entry19 = enterName(testTable7, "mr");
   int entry20 = enterName(testTable7, "tambourine");
   int entry21 = enterName(testTable7, "man");

   // Create an integer to track the number of tests passed.
   int numPassed8 = 0;

   // Use the getCurrentName function to check if the current names are correctly returned.
   printf("EXPECTED: current name of testTable5 is < change >\n");
   if(strcmp(getCurrentName(testTable5), "change") == 0) {
      printf("ACTUAL: current name of testTable5 is %s", testTable5->current->name);
      numPassed8 += 1;
   } else {
      printf("ACTUAL: current name of testTable5 is NOT are");
   }
   printf("\n\n");

   printf("EXPECTED: current name of testTable6 is < time >\n");
   if(strcmp(getCurrentName(testTable6), "time") == 0) {
      printf("ACTUAL: current name of testTable6 is %s", testTable6->current->name);
      numPassed8 += 1;
   } else {
      printf("ACTUAL: current name of testTable6 is NOT time");
   }
   printf("\n\n");

   printf("EXPECTED: current name of testTable7 is < man >\n");
   if(strcmp(getCurrentName(testTable7), "man") == 0) {
      printf("ACTUAL: current name of testTable7 is %s", testTable7->current->name);
      numPassed8 += 1;
   } else {
      printf("ACTUAL: current name of testTable7 is NOT man");
   }
   printf("\n\n");

   // Print out the summary of the test results.
   printf("(7) SUMMARY: < %d/3 > tests passed for getCurrentName(SymTab *table) with expected values.", numPassed8);
   printf("\n---------------------------------------------------------\n");

   // Include an extra print statement at the end.
   printf("\n");
   // ===================================================================================================




   // Tests for the startIterator(SymTab *table) function.
   printf("\n--> Tests for startIterator(SymTab *table):\n");
   printf("--> (Symbol tables used in this test are the same as tables in the getCurrentName() test.)\n\n");

   // Create an integer to track the number of tests passed.
   int numPassed9 = 0;

   // Use the startIterator function to check if the first (name, attribute) pair is visited.
   // ------------------------------------------------------------------------------------------------
   // List the expected order of the entered names for testTable5.
   printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
   printf("The names that were entered into testTable5 in the previous tests were: 'the', 'times', and 'change'.\n\n");

   // Expected slot for the name 'the' in testTable5.
   printf("'the' has a hash value of %d.\n", createHashValue(5, "the")); 
   printf("'the' should be in slot %d of the symbol table.\n\n", createHashValue(5, "the"));

   // Expected slot for the name 'the' in testTable5.
   printf("'times' has a hash value of %d.\n", createHashValue(5, "times")); 
   printf("'times' should be in slot %d of the symbol table.\n\n", createHashValue(5, "times"));

   // Expected slot for the name 'the' in testTable5.
   printf("'change' has a hash value of %d.\n", createHashValue(5, "change")); 
   printf("'change' should be in slot %d of the symbol table.\n\n", createHashValue(5, "change"));

   printf("EXPECTED: based on the above information, < times > should be the first entry visited.\n");

   // Call the iterator function and set the value to the latest entry in the first non-empty slot.
   int iteratorTest1 = startIterator(testTable5);
   if((iteratorTest1 == 1) && (strcmp(testTable5->current->name, "times") == 0)) {
      printf("ACTUAL: the first entry visited is %s\n", testTable5->current->name);
      numPassed9 += 1;
   } else {
      printf("ACTUAL: the first entry visited is NOT times.\n");
   }
   printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
   printf("\n");
   // ------------------------------------------------------------------------------------------------

   // ------------------------------------------------------------------------------------------------
   // List the expected order of the entered names for testTable6.
   printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
   printf("The names that were entered into testTable5 in the previous tests were: 'once', 'upon', and 'time'.\n\n");

   // Expected slot for the name 'the' in testTable6.
   printf("'once' has a hash value of %d.\n", createHashValue(30, "once")); 
   printf("'once' should be in slot %d of the symbol table.\n\n", createHashValue(30, "once"));

   // Expected slot for the name 'the' in testTable6.
   printf("'upon' has a hash value of %d.\n", createHashValue(30, "upon")); 
   printf("'upon' should be in slot %d of the symbol table.\n\n", createHashValue(30, "upon"));

   // Expected slot for the name 'the' in testTable6.
   printf("'time' has a hash value of %d.\n", createHashValue(30, "time")); 
   printf("'time' should be in slot %d of the symbol table.\n\n", createHashValue(30, "time"));

   printf("EXPECTED: based on the above information, < upon > should be the first entry visited.\n");

   // Call the iterator function and set the value to the latest entry in the first non-empty slot.
   int iteratorTest2 = startIterator(testTable6);
   if((iteratorTest2 == 1) && (strcmp(testTable6->current->name, "upon") == 0)) {
      printf("ACTUAL: the first entry visited is %s\n", testTable6->current->name);
      numPassed9 += 1;
   } else {
      printf("ACTUAL: the first entry visited is NOT upon.\n");
   }
   printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
   printf("\n");
   // ------------------------------------------------------------------------------------------------

   // ------------------------------------------------------------------------------------------------
   // List the expected order of the entered names for testTable7.
   printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
   printf("The names that were entered into testTable7 in the previous tests were: 'mr', 'tambourine', and 'man'.\n\n");

   // Expected slot for the name 'the' in testTable7.
   printf("'mr' has a hash value of %d.\n", createHashValue(200, "mr")); 
   printf("'mr' should be in slot %d of the symbol table.\n\n", createHashValue(200, "mr"));

   // Expected slot for the name 'the' in testTable7.
   printf("'tambourine' has a hash value of %d.\n", createHashValue(200, "tambourine")); 
   printf("'tambourine' should be in slot %d of the symbol table.\n\n", createHashValue(200, "tambourine"));

   // Expected slot for the name 'the' in testTable7.
   printf("'man' has a hash value of %d.\n", createHashValue(200, "man")); 
   printf("'man' should be in slot %d of the symbol table.\n\n", createHashValue(200, "man"));

   printf("EXPECTED: based on the above information, < mr > should be the first entry visited.\n");

   // Call the iterator function and set the value to the latest entry in the first non-empty slot.
   int iteratorTest3 = startIterator(testTable7);
   if((iteratorTest3 == 1) && (strcmp(testTable7->current->name, "mr") == 0)) {
      printf("ACTUAL: the first entry visited is %s\n", testTable7->current->name);
      numPassed9 += 1;
   } else {
      printf("ACTUAL: the first entry visited is NOT mr.\n");
   }
   printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
   printf("\n");
   // ------------------------------------------------------------------------------------------------

   // ------------------------------------------------------------------------------------------------
   // List the expected order of the entered names for testTable8.
   printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
   printf("The symbol table, testTable8, is empty. Therefore, the iterator function should return 0.\n\n");
   printf("EXPECTED: based on the above information, the iterator function should return 0.\n");

   // Declare a new, empty symbol table.
   SymTab *testTable8;
   testTable8 = createSymTab(12);

   // Call the iterator function and set the value to the latest entry in the first non-empty slot.
   int iteratorTest4 = startIterator(testTable8);
   if(iteratorTest4 == 0) {
      printf("ACTUAL: the return value of the iterator function is %d\n", iteratorTest4);
      numPassed9 += 1;
   } else {
      printf("ACTUAL: the return value of the iterator function is NOT 0.\n");
   }
   printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
   printf("\n");
   // ------------------------------------------------------------------------------------------------

   // Print out the summary of the test results.
   printf("(8) SUMMARY: < %d/4 > tests passed for getCurrentName(SymTab *table) with expected values.", numPassed9);
   printf("\n---------------------------------------------------------\n");

   // Include an extra print statement at the end.
   printf("\n");
   // ===================================================================================================




   // Tests for the startIterator(SymTab *table) function.
   printf("\n--> Tests for nextEntry(SymTab *table):\n");
   printf("--> (Symbol tables used in this test are the same as tables in the getCurrentName() and startIterator(SymTab *table) tests.)\n\n");

   // Create an integer to track the number of tests passed.
   int numPassed10 = 0;

   // Use the nextEntry function to check if the next (name, attribute) pair is visited.
   // ------------------------------------------------------------------------------------------------
   // List the expected order of the entered names for testTable5.
   printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
   printf("The names that were entered into testTable5 in the previous tests were: 'the', 'times', and 'change'.\n\n");

   // Expected slot for the name 'the' in testTable5.
   printf("'the' has a hash value of %d.\n", createHashValue(5, "the")); 
   printf("'the' should be in slot %d of the symbol table.\n\n", createHashValue(5, "the"));

   // Expected slot for the name 'the' in testTable5.
   printf("'times' has a hash value of %d.\n", createHashValue(5, "times")); 
   printf("'times' should be in slot %d of the symbol table.\n\n", createHashValue(5, "times"));

   // Expected slot for the name 'the' in testTable5.
   printf("'change' has a hash value of %d.\n", createHashValue(5, "change")); 
   printf("'change' should be in slot %d of the symbol table.\n\n", createHashValue(5, "change"));

   printf("EXPECTED: based on the above information, < the > should be the next entry visited.\n");

   // Call the iterator function and set the value to the latest entry in the first non-empty slot.
   int entryTest1 = nextEntry(testTable5);
   if((entryTest1 == 1) && (strcmp(testTable5->current->name, "the") == 0)) {
      printf("ACTUAL: the next entry visited is %s\n", testTable5->current->name);
      numPassed10 += 1;
   } else {
      printf("ACTUAL: the next entry visited is NOT the.\n");
   }
   printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
   printf("\n");
   // ------------------------------------------------------------------------------------------------

   // ------------------------------------------------------------------------------------------------
   // List the expected order of the entered names for testTable6.
   printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
   printf("The names that were entered into testTable5 in the previous tests were: 'once', 'upon', and 'time'.\n\n");

   // Expected slot for the name 'the' in testTable6.
   printf("'once' has a hash value of %d.\n", createHashValue(30, "once")); 
   printf("'once' should be in slot %d of the symbol table.\n\n", createHashValue(30, "once"));

   // Expected slot for the name 'the' in testTable6.
   printf("'upon' has a hash value of %d.\n", createHashValue(30, "upon")); 
   printf("'upon' should be in slot %d of the symbol table.\n\n", createHashValue(30, "upon"));

   // Expected slot for the name 'the' in testTable6.
   printf("'time' has a hash value of %d.\n", createHashValue(30, "time")); 
   printf("'time' should be in slot %d of the symbol table.\n\n", createHashValue(30, "time"));

   printf("EXPECTED: based on the above information, < once > should be the next entry visited.\n");

   // Call the iterator function and set the value to the latest entry in the first non-empty slot.
   int entryTest2 = nextEntry(testTable6);
   if((entryTest2 == 1) && (strcmp(testTable6->current->name, "once") == 0)) {
      printf("ACTUAL: the next entry visited is %s\n", testTable6->current->name);
      numPassed10 += 1;
   } else {
      printf("ACTUAL: the next entry visited is NOT once.\n");
   }
   printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
   printf("\n");
   // ------------------------------------------------------------------------------------------------

   // ------------------------------------------------------------------------------------------------
   // List the expected order of the entered names for testTable7.
   printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
   printf("The names that were entered into testTable7 in the previous tests were: 'mr', 'tambourine', and 'man'.\n\n");

   // Expected slot for the name 'the' in testTable7.
   printf("'mr' has a hash value of %d.\n", createHashValue(200, "mr")); 
   printf("'mr' should be in slot %d of the symbol table.\n\n", createHashValue(200, "mr"));

   // Expected slot for the name 'the' in testTable7.
   printf("'tambourine' has a hash value of %d.\n", createHashValue(200, "tambourine")); 
   printf("'tambourine' should be in slot %d of the symbol table.\n\n", createHashValue(200, "tambourine"));

   // Expected slot for the name 'the' in testTable7.
   printf("'man' has a hash value of %d.\n", createHashValue(200, "man")); 
   printf("'man' should be in slot %d of the symbol table.\n\n", createHashValue(200, "man"));

   printf("EXPECTED: based on the above information, < tambourine > should be the next entry visited.\n");

   // Call the iterator function and set the value to the latest entry in the first non-empty slot.
   int entryTest3 = nextEntry(testTable7);
   if((entryTest3 == 1) && (strcmp(testTable7->current->name, "tambourine") == 0)) {
      printf("ACTUAL: the next entry visited is %s\n", testTable7->current->name);
      numPassed10 += 1;
   } else {
      printf("ACTUAL: the next entry visited is NOT tambourine.\n");
   }
   printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
   printf("\n");
   // ------------------------------------------------------------------------------------------------

   // ------------------------------------------------------------------------------------------------
   // List the expected order of the entered names for testTable8.
   printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
   printf("The symbol table, testTable8, is empty. Therefore, the next entry function should return 0.\n\n");
   printf("EXPECTED: based on the above information, the next entry function should return 0.\n");

   // Call the iterator function and set the value to the latest entry in the first non-empty slot.
   int entryTest4 = nextEntry(testTable8);
   if(entryTest4 == 0) {
      printf("ACTUAL: the return value of the iterator function is %d\n", entryTest4);
      numPassed10 += 1;
   } else {
      printf("ACTUAL: the return value of the next entry function is NOT 0.\n");
   }
   printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
   printf("\n");
   // ------------------------------------------------------------------------------------------------

   // Print out the summary of the test results.
   printf("(9) SUMMARY: < %d/4 > tests passed for nextEntry(SymTab *table) with expected values.", numPassed10);
   printf("\n---------------------------------------------------------\n");

   // Include an extra print statement at the end.
   printf("\n");
   // ===================================================================================================



   
   // Tests for the createHashValue(int size, char *name) function.
   printf("\n--> Tests for createHashValue(int size, char *name):\n\n");

   // Create an integer to track the number of tests passed.
   int numPassed11 = 0;

   // Create variables to store the hash values.
   int createHashTest1 = createHashValue(4, "integer"); 
   int createHashTest2 = createHashValue(10, "string"); 
   int createHashTest3 = createHashValue(2, "candy"); 
   int createHashTest4 = createHashValue(15, "Gendreau"); 
   int createHashTest5 = createHashValue(13, "Saupe77"); 
   int createHashTest6 = createHashValue(58, "Charlie_T"); 
   int createHashTest7 = createHashValue(72, "Andrew_E_K"); 
   int createHashTest8 = createHashValue(18, "compilers_is_tough"); 
   int createHashTest9 = createHashValue(45, "floatVal"); 
   int createHashTest10 = createHashValue(200, "supercallifragilisticexpialidocious");

   // Check if the hash values fall between the correct ranges.
   if((createHashTest1 >= 0) && (createHashTest1 < 4)) {

      printf("createHashTest1 PASSED.\n");
      numPassed11 += 1;

   } else {
      printf("createHashTest1 FAILED.\n");
   }

   if((createHashTest2 >= 0) && (createHashTest2 < 10)) {

      printf("createHashTest2 PASSED.\n");
      numPassed11 += 1;

   } else {
      printf("createHashTest2 FAILED.\n");
   }

   if((createHashTest3 >= 0) && (createHashTest3 < 2)) {

      printf("createHashTest3 PASSED.\n");
      numPassed11 += 1;

   } else {
      printf("createHashTest3 FAILED.\n");
   }

   if((createHashTest4 >= 0) && (createHashTest4 < 15)) {

      printf("createHashTest4 PASSED.\n");
      numPassed11 += 1;

   } else {
      printf("createHashTest4 FAILED.\n");
   }

   if((createHashTest5 >= 0) && (createHashTest5 < 13)) {

      printf("createHashTest5 PASSED.\n");
      numPassed11 += 1;

   } else {
      printf("createHashTest5 FAILED.\n");
   }

   if((createHashTest6 >= 0) && (createHashTest6 < 58)) {

      printf("createHashTest6 PASSED.\n");
      numPassed11 += 1;

   } else {
      printf("createHashTest6 FAILED.\n");
   }

   if((createHashTest7 >= 0) && (createHashTest7 < 72)) {

      printf("createHashTest7 PASSED.\n");
      numPassed11 += 1;

   } else {
      printf("createHashTest7 FAILED.\n");
   }

   if((createHashTest8 >= 0) && (createHashTest8 < 18)) {

      printf("createHashTest8 PASSED.\n");
      numPassed11 += 1;

   } else {
      printf("createHashTest8 FAILED.\n");
   }

   if((createHashTest9 >= 0) && (createHashTest9 < 45)) {

      printf("createHashTest9 PASSED.\n");
      numPassed11 += 1;

   } else {
      printf("createHashTest9 FAILED.\n");
   }

   if((createHashTest10 >= 0) && (createHashTest9 < 200)) {

      printf("createHashTest10 PASSED.\n");
      numPassed11 += 1;

   } else {
      printf("createHashTest10 FAILED.\n");
   }

   // Print out the summary of the test results.
   printf("\n(10) SUMMARY: < %d/10 > tests passed for createHashValue(int size, char *name) with expected values.", numPassed11);
   printf("\n---------------------------------------------------------\n");

   // Include an extra print statement at the end.
   printf("\n");
   // ===================================================================================================




   // Destroy all of the symbol tables
   // at the conclusion of the tests.
   destroySymTab(testTable1);
   destroySymTab(testTable2);
   destroySymTab(testTable3);
   destroySymTab(testTable4);
   destroySymTab(testTable5);
   destroySymTab(testTable6);
   destroySymTab(testTable7);
   destroySymTab(testTable8);

   // Print the final summaries for all the tests as one large summary below.
   printf("\n=================================================================\n");
   printf("THIS FINAL SECTION LISTS OUT THE SUMMARIES OF ALL THE TESTS THAT\n");
   printf("WERE IMPLEMENTED ON THE DIFFERENT FUNCTIONS OF THE SYMBOL TABLE.\n");
   printf("=================================================================\n\n");

   // Print out all the summary print statements that appear in all of the other tests.
   printf("(1) SUMMARY: < %d/3 > tests passed for *createSymTab(int size).\n", numPassed1);
   // printf("(2) SUMMARY: < %d/3 > tests passed for *destroySymTab(SymTab *table).\n", numPassed2);
   printf("(2) SUMMARY: No tests for now.\n"); // --> TEMPORARY!!!
   printf("(3.1) SUMMARY: < %d/10 > tests passed for enterName(SymTab *table, char *name) with expected return values.\n", returnNumPassed3);
   printf("(3.2) SUMMARY: < %d/3 > tests passed for enterName(SymTab *table, char *name) with expected current name values.\n", numPassed3);
   printf("(4) SUMMARY: < %d/9 > tests passed for findName(SymTab *table, char *name) with expected return values.\n", numPassed4);
   printf("(5) SUMMARY: < %d/4 > tests passed for hasCurrent(SymTab *table) with expected return values.\n", numPassed5);
   printf("(6) SUMMARY: < %d/4 > tests passed for setCurrentAttr(SymTab *table, void *attr) and *getCurrentAttr(SymTab *table) with expected values.\n", numPassed6And7);
   printf("(7) SUMMARY: < %d/3 > tests passed for getCurrentName(SymTab *table) with expected values.\n", numPassed8);
   printf("(8) SUMMARY: < %d/4 > tests passed for getCurrentName(SymTab *table) with expected values.\n", numPassed9);
   printf("(9) SUMMARY: < %d/4 > tests passed for nextEntry(SymTab *table) with expected values.\n", numPassed10);
   printf("(10) SUMMARY: < %d/10 > tests passed for createHashValue(int size, char *name) with expected values.\n", numPassed11);

   // Include an extra print statement at the end.
   printf("\nEND OF TESTS FOR SYMBOL TABLE\n\n");

   // Return 0 at the end of the main function 
   // after all the tests have run.
   return 0;
}
