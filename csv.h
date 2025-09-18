
#ifndef CSV
#define CSV

int countColumns(FILE *currFile);
int countRows(FILE *currFile);
void printResult(double num);
int allDigits(char *str);
int getColIndex(char *colName, FILE *currFile);
double maxField(int colIndex, FILE *currFile);
double minField(int colIndex, FILE *currFile);
double meanField(int colIndex, FILE *currFile);
int findRecords(bool h, int colIndex, char *value, FILE *currFile, char **matches);


#endif
