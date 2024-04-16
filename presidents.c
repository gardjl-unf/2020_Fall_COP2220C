#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME_LEN 30
#define MAX_PREZ 50

typedef struct {
    char firstName[NAME_LEN];
    char lastName[NAME_LEN];
    int birthYear;
    int birthMonth;
    int birthDay;
    } president_t;

    void displayPresident(president_t *p);

int main(void) {
    FILE *inputFile;
    char readLine[NAME_LEN];
    president_t presidents[MAX_PREZ];
    president_t *currentPrez = presidents;
    size_t numPrez = 0;
    char *startPtr;
    char *endPtr;
    inputFile = fopen("Presidents3.txt", "r");
    if(!inputFile) {
        printf("Failed to open file");
        return 1;
    }
    while(fgets(readLine, sizeof(readLine), inputFile) && numPrez < MAX_PREZ) {
        sscanf(readLine, "%s %s %i %i %i", currentPrez->firstName, currentPrez->lastName, &currentPrez->birthYear, &currentPrez->birthMonth, &currentPrez->birthDay);
        endPtr = strchr(readLine, '\n');
        if (endPtr) {
            *endPtr = '\0';
        }
        startPtr = readLine;
        endPtr = strchr(startPtr, '|');

        strncpy(currentPrez->firstName, startPtr, endPtr - startPtr);

        startPtr = endPtr + 1;
        endPtr = strchr(startPtr, '|');

        strncpy(currentPrez->lastName, startPtr, endPtr - startPtr);

        startPtr = endPtr + 1;
        endPtr = strchr(startPtr, '|');

        currentPrez->birthYear = atoi(startPtr);

        startPtr = endPtr + 1;
        endPtr = strchr(startPtr, '|');

        currentPrez->birthMonth = atoi(startPtr);

        startPtr = endPtr + 1;
        endPtr = strchr(startPtr, '\n');

        currentPrez->birthDay = atoi(startPtr);


        ++numPrez;
        ++currentPrez;
    }

    fclose(inputFile);

    currentPrez = presidents;
    for (int i = 0; i < numPrez; ++i, ++currentPrez) {
        displayPresident(currentPrez);
    }

    return 0;
}

void displayPresident(president_t *p) {
    printf("%s %s was born on %d/%d/%d", p->firstName, p->lastName, p->birthMonth, p->birthDay, p->birthYear);
}