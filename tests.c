#include <stdio.h>
#include <criterion/criterion.h>
#include "csv.h"


// Helper functions
#define EPSILON 0.01

void countRowsTest(char *inFile, int expected) {
    FILE *currFile = NULL;
    currFile = fopen(inFile, "r");
    if(currFile == NULL){
        printf("Error: File \'%s\'is not present\n",inFile);
        return;
    }
    int actual = countRows(currFile);
    fclose(currFile);
    cr_assert_eq( actual, expected, "countRows(\"%s\") should have counted %d rows, but counted %d instead.\n",inFile, expected, actual);
}

void countColumnsTest(char *inFile, int expected){
    FILE *currFile = NULL;
    currFile = fopen(inFile,"r");
    if(currFile == NULL){
        printf("Error: File \'%s\'is not present\n",inFile);
        return;
    }
    int actual = countColumns(currFile);
    fclose(currFile);
    cr_assert_eq(actual, expected, "countColumns(\"%s\") should have counted %d columns, but counted %d instead.\n",inFile, expected, actual);
}

void maxFieldTest(int colIndex, char *inFile, double expected){
    FILE *currFile = NULL;
    currFile = fopen(inFile,"r");
    if(currFile == NULL){
        printf("Error: File \'%s\'is not present\n",inFile);
        return;
    }
    double actual = maxField(colIndex,currFile);
    fclose(currFile);
    cr_assert_float_eq(actual, expected, EPSILON, "maxField(%d,\"%s\") should have found %f as the maximum, but found %f instead.\n",colIndex,inFile, expected, actual);
}

void minFieldTest(int colIndex, char *inFile, double expected){
    FILE *currFile = NULL;
    currFile = fopen(inFile,"r");
    if(currFile == NULL){
        printf("Error: File \'%s\'is not present\n",inFile);
        return;
    }
    double actual = minField(colIndex, currFile);
    fclose(currFile);
    cr_assert_float_eq(actual, expected, EPSILON,"minField(%d,\"%s\") should have found %f as the minimum, but found %f instead.\n", colIndex, inFile, expected, actual);
}

void meanFieldTest(int colIndex, char *inFile, double expected){
    FILE *currFile = NULL;
    currFile = fopen(inFile,"r");
    if(currFile == NULL){
        printf("Error: File \'%s\'is not present\n",inFile);
        return;
    }
    double actual = meanField(colIndex, currFile);
    fclose(currFile);
    cr_assert_float_eq(actual, expected, EPSILON, "meanField(%d,\"%s\") should have returned %f as the mean, but returned %f instead.\n", colIndex, inFile, expected, actual);
}

void findRecordsTest(int colIndex, char *value, char *inFile, int expectedN, char **expectedStrs, char **actualStrs){
    FILE *currFile = NULL;
    currFile = fopen(inFile,"r");
    if(currFile == NULL){
        printf("Error: File \'%s\'is not present\n",inFile);
        return;
    }
    int actualN = findRecords(colIndex, value, currFile, actualStrs);
    fclose(currFile);
    cr_assert_eq(actualN, expectedN, "findRecords(%d,\"%s\",\"%s\",[]) should have found %d matches, but found %d instead.\n", colIndex, value, inFile, expectedN, actualN);
    for(int i = 0; i < actualN; i++){
        char *expected = expectedStrs[i];
        char *actual = actualStrs[i];
        cr_assert_str_eq(actual, expected, "findRecords(%d,\"%s\",\"%s\",[]) should have found record \"%s\", but instead found \"%s\"", colIndex, value, inFile, expected,actual);
    }
    
}
  
// Tests
Test(rowCount, test00) { countRowsTest("test.csv",819); }
Test(columnCount, test00) { countColumnsTest("test.csv",8); }
Test(min, test00) { minFieldTest(7,"test.csv",0.0); }
Test(max, test00) { maxFieldTest(7,"test.csv",100.0); }
//Test(mean, test00) { runTest("tests.csv",); }
//Test(records, test00) { runTest("tests.csv",); }
