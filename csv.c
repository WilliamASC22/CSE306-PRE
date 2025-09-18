#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define bufferSize 1024

/**
 * Function: countColumns
 * -------------------------
 *    Counts the number of columns in a .csv file.
 *
 *    *currFile: input file
 * 
 *    returns: the number of columns in the input file
 */
int countColumns(FILE *currFile){
    char buffer[bufferSize];
    int fields = 1;
    
    //fgets(buffer, size, file), check first line exists
    if(fgets(buffer, bufferSize, currFile) != NULL){
        for(int i = 0; buffer[i] != '\0'; i++){
            if(buffer[i] == ','){
                fields++;
            }
        }
    }

    //reset pointer
    rewind(currFile);

    return fields;
}

/**
 * Function: countRows
 * ----------------------------
 *    Returns the number of rows in a .csv file.
 *
 *    *currFile: input file 
 *
 *    returns: the number of rows in the input file 
 */
int countRows(FILE *currFile){
    char buffer[bufferSize];
    int lines = 0;

    while(fgets(buffer, bufferSize, currFile) != NULL){
        lines++;
    }

    //reset pointer
    rewind(currFile);

    return lines;
}
void printResult(double num){
    //if .00 == double print int, else print double
    if(floor(num) == num){
        int temp = (int)num;
        printf("%d\n", temp);
    }else{
        printf("%.2f\n", num);
    }
}
 
/**
 * Function: getColIndex
 * -----------------------
 *    Returns the index of a column name of a .csv file.
 *
 *    *colName: the name of the column
 *    *currFile: input file
 *
 *    returns: the index of the column name
 */
int getColIndex(char *colName, FILE *currFile){
    char buffer[bufferSize];
    fgets(buffer, bufferSize, currFile);
    int colIndex = 0;

    //strtok(char *str, delimiter) - breaks string by delim
    char *data = strtok(buffer, ",");

    while(data != NULL && strcmp(data, colName) != 0){
        data = strtok(NULL, ",");
        colIndex++;
    }

    //last column
    if(data == NULL){
        colIndex--;
    }

    //reset pointer
    rewind(currFile);

    return colIndex;
}

/**
 * Function: maxField
 * -----------------------
 *    Returns the biggest field in a column of a .csv file.
 *
 *    colIndex: index of the column
 *    *currFile: input file
 *
 *    returns: the maximum value in the column as a double
 */
double maxField(int colIndex, FILE *currFile){
    char buffer[bufferSize];
    //skip header
    fgets(buffer, bufferSize, currFile);

    double max = 0;
    while(fgets(buffer, bufferSize, currFile) != NULL){
        int currIndex = colIndex;
        char *data = strtok(buffer, ",");
        int index = 0;

        while(currIndex != 0){
            index++;
            int quoteFlag = 0;
            currIndex--;
            data = strtok(NULL, ",");

            if(data[0] == '"'){
                quoteFlag = 1;
                while(quoteFlag == 1){
                    if(data[strlen(data) - 1] != '"'){
                        data = strtok(NULL, ",");
                    }else{
                        quoteFlag = 0;
                    }
                }
            }
        }
        //flag non numeric
        int decimalFlag = 0;
        int i = 0;

        if(data[i] == '-'){
            i++;
        }

        for(i; data[i] != '\0' && data[i] != '\r' && data[i] != '\n'; i++){
            if((data[i] < '0' || data[i] > '9') && data[i] != '.'){
                printf("Non numeric data\n");
                exit(EXIT_FAILURE);
            }

            if(data[i] == '.'){
                decimalFlag++;
            }

            if(decimalFlag > 1){
                printf("Non numeric data\n");
                exit(EXIT_FAILURE);
            }
        }

        double temp = atof(data);

        if(temp > max){
            max = temp;
        }
    }

    return max;
}


/**
 * Function: minField
 * -----------------------
 *    Returns the minimum field value in a column of a .csv file.
 *
 *    colIndex: index of the column.
 *    *currFile: input file.
 *
 *    returns: the minimum value in the column as a double
 */
double minField(int colIndex, FILE *currFile){
    char buffer[bufferSize];
    // Skip header
    fgets(buffer, bufferSize, currFile);

    // Initliaize minimum value
    double minimum = 0.0;
    
    // Flag to set the first value of the column as the starting minimum value
    int FIRST_VAL = 0;

    // Loop through each line of the file
    while(fgets(buffer, bufferSize, currFile) != NULL){

        //The column that you are looking at
        int currIndex = colIndex;
        char *data = strtok(buffer, ",");
        int index = 0;

        //Loop through until you are at the column you want
        while(currIndex != 0){
            index++;
            int quoteFlag = 0;
            currIndex--;
            data = strtok(NULL, ",");

            if(data[0] == '"'){
                quoteFlag = 1;
                while(quoteFlag == 1){
                    if(data[strlen(data) - 1] != '"'){
                        data = strtok(NULL, ",");
                    }else{
                        quoteFlag = 0;
                    }
                }
            }
        }

        //flag non numeric
        int decimalFlag = 0;
        int i = 0;

        if(data[i] == '-'){
            i++;
        }

        int nOPROMBLEM = 0;

        for(i; data[i] != '\0' && data[i] != '\r' && data[i] != '\n'; i++){
            if((data[i] < '0' || data[i] > '9') && data[i] != '.'){
                nOPROMBLEM = 1;
            }

            if(data[i] == '.'){
                decimalFlag++;
            }

            if(decimalFlag > 1){
                nOPROMBLEM = 1;
            }
        }

        //Only change total and amount if there is no problem
        if (nOPROMBLEM == 0) {
        

            double temp = atof(data);
            
            if (FIRST_VAL == 0) {
                minimum = temp;
                FIRST_VAL = 1;
            }

            if (temp < minimum){ minimum = temp; }
        }
            
        
    }

    rewind(currFile);

    //The first value wasnt changed so there wasnt any numeric value
    if (FIRST_VAL == 0) {
        exit(EXIT_FAILURE);
    }

    return minimum;
}

/**
 * Function: meanField
 * ---------------------------
 *    Returns the mean of all values in a column of a .csv file.
 *
 *    colIndex: index of the column
 *    *currFile: input file
 *
 *    returns: the mean of the values in the column as a double.
 */
double meanField(int colIndex, FILE *currFile){
    char buffer[bufferSize];
    //skip header
    fgets(buffer, bufferSize, currFile);

    double total = 0.0;
    int amount = 0;


    //Loop through each line of the file
    while(fgets(buffer, bufferSize, currFile) != NULL){

        //The column that you are looking at
        int currIndex = colIndex;
        char *data = strtok(buffer, ",");
        int index = 0;

        //Loop through until you are at the column you want
        while(currIndex != 0){
            index++;
            int quoteFlag = 0;
            currIndex--;
            data = strtok(NULL, ",");

            if(data[0] == '"'){
                quoteFlag = 1;
                while(quoteFlag == 1){
                    if(data[strlen(data) - 1] != '"'){
                        data = strtok(NULL, ",");
                    }else{
                        quoteFlag = 0;
                    }
                }
            }
        }

        //flag non numeric
        int decimalFlag = 0;
        int i = 0;

        if(data[i] == '-'){
            i++;
        }

        int nOPROMBLEM = 0;

        for(i; data[i] != '\0' && data[i] != '\r' && data[i] != '\n'; i++){
            if((data[i] < '0' || data[i] > '9') && data[i] != '.'){
                nOPROMBLEM = 1;
            }

            if(data[i] == '.'){
                decimalFlag++;
            }

            if(decimalFlag > 1){
                nOPROMBLEM = 1;
            }
        }

        //Only change total and amount if there is no problem
        if (nOPROMBLEM == 0) {
            double temp = atof(data);
            total = total + temp;
            amount = amount + 1;
        }
        
        
    }

    rewind(currFile);

    //No number counted
    if (amount == 0) {
        exit(EXIT_FAILURE);
    }

    double mean = total / amount;
    
    return mean;
}

/**
 * Function: findRecords
 * -----------------------------
 *    Returns all rows that contains the specified value in the
 *    specified column.
 *   
 *    h: header row? (yes/no)
 *    colIndex: the index of the column to search for 'value'
 *    value: the desired value to search for in 'colIndex'
 *    *currFile: input file
 *    **matches: a list of all rows that match the criteria as strings
 *
 *    returns: the list of all rows as strings    
 */
int findRecords(bool h, int colIndex, char *value, FILE *currFile, char **matches) {

    #define MAX_LINE 1204

    char buffer[bufferSize];
    if( h ){ fgets(buffer, bufferSize, currFile); }

    int count = 0; 

    

    rewind(currFile);
    
    //Loop through each line of the file
    while(fgets(buffer, bufferSize, currFile) != NULL){
        int currIndex = 0;
        char *pb = buffer;
        
        int IN_QUOTES = 0;
        int MATCH = 0;
        
        char field[MAX_LINE];
        int fieldIndex = 0;

        int col = 0; 

        while (*pb != NULL) {
            // Detect if we're going in/out of quotes
            if (*pb == '"') { IN_QUOTES = !IN_QUOTES; }
            // If we've reached the end of our column
            else if (*pb == ',' && !IN_QUOTES) {
                    field[fieldIndex] = '\0'; // End the string
                // If we've reached our desired column index,   
                if (col == colIndex) {
                    // Check if the field matches 'value'
                    if (strcmp(field, value) == 0) { MATCH = 1; }
                    break; 
                }
                fieldIndex = 0;
                col++; // Move to the next column 
            } else { field[fieldIndex++] = *pb; }
            pb++;
        }

        if (MATCH) {
            matches[count] = strdup(buffer);
            count++;
        }


        return 0;
    }

    return count;

}

int main(int argc, char *argv[]){
    FILE *currFile = NULL;
    int h_flag = 0;

    if(argc <= 1){
        printf("Insufficient command line arguments");
    }else{

        //check if file is present
        currFile = fopen(argv[argc - 1], "r");
        if(currFile == NULL){
            printf("%s\n", "File is not present");
            exit(EXIT_FAILURE);
        }

        for(int i = 1; i < argc - 1; i++){
            //string compare, returns 0 if equals
            if(strcmp(argv[i], "-h") == 0){
                h_flag = 1;
            }
            
            else if(strcmp(argv[i], "-f") == 0){
                int columns = countColumns(currFile);
                printf("%d\n", columns);
            }

            else if(strcmp(argv[i], "-r") == 0){
                int rows = countRows(currFile);
                if(h_flag == 1){
                    rows--;
                }
                printf("%d\n", rows);
            }

            else if(strcmp(argv[i], "-max") == 0){
                int colIndex = 0;
                i++;
                char *tempIndex = argv[i];
                if(h_flag == 0){
                    colIndex = atoi(tempIndex);
                }else{
                    colIndex = getColIndex(tempIndex, currFile);
                }
                double maxNum = maxField(colIndex, currFile);
                printResult(maxNum);
            }

            else if(strcmp(argv[i], "-min") == 0){
                int colIndex = 0;
                i++;
                char *tempIndex = argv[i];
                if(h_flag == 0){
                    colIndex = atoi(tempIndex);
                }else{
                    colIndex = getColIndex(tempIndex, currFile);
                }
                double minNum = minField(colIndex, currFile);
                printf("%.2f\n", minNum);
            }

            else if(strcmp(argv[i], "-mean") == 0){
                int colIndex = 0;
                i++;
                char *tempIndex = argv[i];
                if(h_flag == 0){
                    colIndex = atoi(tempIndex);
                }else{
                    colIndex = getColIndex(tempIndex, currFile);
                }
                double meanNum = meanField(colIndex, currFile);

                //Return 2 digits after the decimal like in the example: 10.26
                printf("%.2f\n", meanNum);
            }

            else if(strcmp(argv[i], "-records") == 0){
                
            }

            else{

            }
        }
    }

    // currFile = fopen(argv[2], "r");
    // int field = countColumns(currFile);
    // printf("fields: %d\n", field);

    // int lines = countRows(currFile);
    // printf("%d\n", lines);


    fclose(currFile);
    return 0;
}