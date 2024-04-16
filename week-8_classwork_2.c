#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN_LINE 80

int main (void) {
    char line[LEN_LINE];
    char number[LEN_LINE];
    char readLine[LEN_LINE];
    char readNumber[LEN_LINE];
    char *pNewLine;

    FILE *myFile = fopen("myfile.txt", "w");
    if (myFile == NULL){
        printf("Could not open file");
        free(line);
        return 1;
    }

    printf("Enter your full name:  ");
    fgets(line, LEN_LINE, stdin);
    pNewLine = strchr(line, '\n');
    if (pNewLine) {
        *pNewLine = '\0';
    }
    printf("Enter your phone number:  ");
    fgets(number, LEN_LINE, stdin);
    pNewLine = strchr(number, '\n');
    if (pNewLine) {
        *pNewLine = '\0';
    }

    printf("\nYour name is %s.\n", line);
    printf("Your phone number is %s.\n", number);

    fprintf(myFile, "%s\n", line);
    fprintf(myFile, "%s\n", number);

    fclose(myFile);

    myFile = fopen("myfile.txt", "r");
    if (myFile == NULL){
        printf("Could not open file");
        free(line);
        return 1;
    }

    fgets(readLine, LEN_LINE, myFile);
    pNewLine = strchr(readLine, '\n');
    if (pNewLine) {
        *pNewLine = '\0';
    }
    fgets(readNumber, LEN_LINE, myFile);
    pNewLine = strchr(readNumber, '\n');
    if (pNewLine) {
        *pNewLine = '\0';
    }

    printf("\nYour name is %s.\n", readLine);
    printf("Your phone number is %s.\n", readNumber);

    fclose(myFile);
    free(line);
    return 0;
}