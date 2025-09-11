#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bufferSize 1024

//return number of columns
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

// return number of rows
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

//get column index of column name
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

//return max field of column
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
                
            }

            else if(strcmp(argv[i], "-mean") == 0){
                
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