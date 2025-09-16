#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    if(data == NULL){
        printf("Incorrect column name\n");
        exit(EXIT_FAILURE);
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
 *    returns: the maximum value in the column as an integer
 */
int maxField(int colIndex, FILE *currFile){
    char buffer[bufferSize];
    //skip header
    fgets(buffer, bufferSize, currFile);

    int max = 0;
    while(fgets(buffer, bufferSize, currFile) != NULL){
        int currIndex = colIndex;
        char *data = strtok(buffer, ",");

        while(currIndex != 0){
            currIndex--;
            data = strtok(NULL, ",");
        }
        int temp = atoi(data);

        if(temp > max){
            max = temp;
        }
    }


    //if no numeric exit_failure

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
    //skip header
    fgets(buffer, bufferSize, currFile);

    double mINIMUM = 0;
    //flag to set the first value of the column as the starting minimum value
    int fIRSTVAL = 0;

    //Loop through each line of the file
    while(fgets(buffer, bufferSize, currFile) != NULL){

        //The column that you are looking at
        int currIndex = colIndex;
        char *data = strtok(buffer, ",");

        //Loop through until you are at the column you want
        while(currIndex != 0){
            currIndex--;
            data = strtok(NULL, ",");
        }

        //Make sure that the value exists
        if (data != NULL) {

            //Check if it is negitive
            int nEGITIVEVALUE = 0;

            if (data[nEGITIVEVALUE] == '-') {

                nEGITIVEVALUE = nEGITIVEVALUE + 1;
            }

            //Check if every character is a digit
            int yESDIGITS = 1;

            //Check every character if there is a decimal
            int yESDECIMAL = 0;

            int iSSUEFOUND = 0;

            //Loop through each character
            for (nEGITIVEVALUE; data[nEGITIVEVALUE] != '\0' && data[nEGITIVEVALUE] != '\r' && data[nEGITIVEVALUE] != '\n'; nEGITIVEVALUE++) {


                if (((data[nEGITIVEVALUE]) >= '0' && (data[nEGITIVEVALUE]) <= '9')) {

                    
                    yESDIGITS = 0;
                    
                }

                else if (data[nEGITIVEVALUE] == '.' && yESDECIMAL == 0) {


                    yESDECIMAL = 1;
                }

                else if (data[nEGITIVEVALUE] == '.' && yESDECIMAL == 1) {


                    iSSUEFOUND = 1;
                }

                else {

                    iSSUEFOUND = 1;

                }
            }


            if (iSSUEFOUND == 0 && yESDIGITS == 0){

                double temp = atof(data);

                if (fIRSTVAL == 0) {

                    mINIMUM = temp;
                    fIRSTVAL = 1;
                }

                if (temp < mINIMUM)

                    mINIMUM = temp;

                
            }
        }
    }

    rewind(currFile);

    //The first value wasnt changed so there wasnt any numeric value
    if (fIRSTVAL == 0) {
        exit(EXIT_FAILURE);
    }

    return mINIMUM;
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

    double tOTAL = 0.0;
    int aMOUNT = 0;


    //Loop through each line of the file
    while(fgets(buffer, bufferSize, currFile) != NULL){

        //The column that you are looking at
        int currIndex = colIndex;
        char *data = strtok(buffer, ",");

        //Loop through until you are at the column you want
        while(currIndex != 0){
            currIndex--;
            data = strtok(NULL, ",");
        }

        //Make sure that the value exists
        if (data != NULL) {

            //Check if it is negitive
            int nEGITIVEVALUE = 0;

            if (data[nEGITIVEVALUE] == '-') {

                nEGITIVEVALUE = nEGITIVEVALUE + 1;
            }

            //Check if every character is a digit
            int yESDIGITS = 1;

            //Check every character if there is a decimal
            int yESDECIMAL = 0;

            int iSSUEFOUND = 0;

            //Loop through each character
            for (nEGITIVEVALUE; data[nEGITIVEVALUE] != '\0' && data[nEGITIVEVALUE] != '\r' && data[nEGITIVEVALUE] != '\n'; nEGITIVEVALUE++) {


                if (((data[nEGITIVEVALUE]) >= '0' && (data[nEGITIVEVALUE]) <= '9')) {

                    
                    yESDIGITS = 0;
                    
                }

                else if (data[nEGITIVEVALUE] == '.' && yESDECIMAL == 0) {


                    yESDECIMAL = 1;
                }

                else if (data[nEGITIVEVALUE] == '.' && yESDECIMAL == 1) {


                    iSSUEFOUND = 1;
                }

                else {

                    iSSUEFOUND = 1;

                }
            }


            if (iSSUEFOUND == 0 && yESDIGITS == 0){

                double temp = atof(data);

                tOTAL = tOTAL + temp;

                aMOUNT = aMOUNT + 1;
            }
        }
    }

    rewind(currFile);

    //No number counted
    if (aMOUNT == 0) {
        exit(EXIT_FAILURE);
    }

    double mEAN = tOTAL / aMOUNT;

    return mEAN;
}





int main(int argc, char *argv[]){
    FILE *currFile = NULL;
    int h_flag = 0;

    if(argc <= 1){
        printf("Insufficient command line");
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
                int maxNum = maxField(colIndex, currFile);
                printf("%d\n", maxNum);
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
                int meanNum = meanField(colIndex, currFile);

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
