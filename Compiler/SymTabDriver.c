/**
 * DESCRIPTION...
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
#include "SymTab.c"

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
   printf("\nTests for Symbol Table:");
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
   printf("SUMMARY: < %d/3 > tests passed for *createSymTab(int size).", numPassed1);
   printf("\n---------------------------------------------------------\n");

   // Include an extra print statement at the end.
   printf("\n");
   // ===================================================================================================


   // Tests for the destroySymTab(SymTab *table) function.
   printf("\n--> Tests for SymTab destroySymTab(SymTab *table):\n\n");
   printf("--> WITH THESE TEST I HAVE BEEN GETTING A WERID ERROR. RUN REPEATEDLY. <--\n\n");
   printf("--> UNCOMMENT THE CODE IN THE TEST FILE TO RUN THIS PARTICULAR TEST. <--\n\n");

   // --> UNCOMMENT EVERYTHING BELOW THIS LINE TO THE "--> UNCOMMENT ENDMARKER"

   // // Destroy the symbol tables.
   // destroySymTab(testTable1);
   // destroySymTab(testTable2);
   // destroySymTab(testTable3);

   // // Create an integer to track the number of passed tests.
   // int numPassed2 = 0;

   // // Determine the if the size of the symbol tables matches 
   // // the expected output in the print statements.
   // printf("EXPECTED: testTable1 has been cleared\n");
   // if(testTable1->current == NULL) {
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

   // printf("SUMMARY: < %d/3 > tests passed for *destroySymTab(SymTab *table).", numPassed2);
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

   printf("SUMMARY: < %d/10 > tests passed for enterName(SymTab *table, char *name) with expected return values.", returnNumPassed3);
   printf("\nSUMMARY: < %d/3 > tests passed for enterName(SymTab *table, char *name) with expected current name values.", numPassed3);
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
   printf("SUMMARY: < %d/9 > tests passed for findName(SymTab *table, char *name) with expected return values.", numPassed4);
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
   printf("SUMMARY: < %d/4 > tests passed for hasCurrent(SymTab *table) with expected return values.", numPassed5);
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
   void *memory1 = malloc(sizeof(int));
   int *four = (int *)memory1;
   *four = 4;

   // Create a pointer for the value of 100.
   void *memory2 = malloc(sizeof(int));
   int *hundred = (int *)memory2;
   *hundred = 100;

   // Create a pointer for the value of "c".
   void *memory3 = malloc(sizeof(char));
   char *characterC = (char *)memory3;
   strcpy(characterC, "c");

   // Create a pointer for the value of "hello".
   void *memory4 = malloc(sizeof(char));
   char *helloString = (char *)memory4;
   strcpy(helloString, "hello");

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
   free(memory3);
   free(memory4);

   // Print out the summary of the test results.
   printf("SUMMARY: < %d/4 > tests passed for setCurrentAttr(SymTab *table, void *attr) and *getCurrentAttr(SymTab *table) with expected values.", numPassed6And7);
   printf("\n---------------------------------------------------------\n");

   // Include an extra print statement at the end.
   printf("\n");
   // ===================================================================================================


   // Tests for the setCurrentAttr(SymTab *table, void *attr) and *getCurrentAttr(SymTab *table) functions.
   printf("\n--> Tests for getCurrentName(SymTab *table):\n\n");

   // Declare new symbol tables before allocating size for them.
   SymTab *testTable5;
   SymTab *testTable6;
   SymTab *testTable7;

   // Create new symbol tables to test the function with.
   testTable5 = createSymTab(3);
   testTable6 = createSymTab(30);
   testTable7 = createSymTab(200);

   // Enter names into testTable5.
   int entry13 = enterName(testTable5, "the");
   int entry14 = enterName(testTable5, "times");
   int entry15 = enterName(testTable5, "change");

   // Enter names into testTable6.
   int entry16 = enterName(testTable6, "one");
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
   printf("SUMMARY: < %d/3 > tests passed for getCurrentName(SymTab *table) with expected values.", numPassed8);
   printf("\n---------------------------------------------------------\n");

   // Include an extra print statement at the end.
   printf("\n");
   // ===================================================================================================



















   // Print the final summaries for all the tests as one large summary below.
   // --> COMPLETE THIS LATER!!!

   // Include an extra print statement at the end.
   printf("\n");

   return 0;
}