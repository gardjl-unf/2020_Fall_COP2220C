#include <stdio.h>

#define LINE_LEN 80
#define NUM_PLAYERS 100

int main (void) {
    int numberPlayer = 0;
    int searchNumber = 0;
    char *fileName = "JaguarsRoster2020_10.txt";
    char readLine[LINE_LEN];
    int jerseyNumbers[NUM_PLAYERS];
    char firstNames[NUM_PLAYERS][LINE_LEN];
    char lastNames[NUM_PLAYERS][LINE_LEN];
    char playerPositions[NUM_PLAYERS][LINE_LEN];
    int playerAges[NUM_PLAYERS];
    int playerFeet[NUM_PLAYERS];
    int playerInches[NUM_PLAYERS];
    int playerWeights[NUM_PLAYERS];
    FILE *inputFile = fopen(fileName, "r");
    if (inputFile == NULL){
        printf("Could not open file %s", fileName);
        return 1;
    }
    while (fgets(readLine, LINE_LEN, inputFile) != NULL) {
        sscanf(readLine, "%i %s %s %s %i %i %i %i", jerseyNumbers[numberPlayer], firstNames[numberPlayer], lastNames[numberPlayer], playerPositions[numberPlayer], playerAges[numberPlayer], playerFeet[numberPlayer], playerInches[numberPlayer], playerWeights[numberPlayer]);
        numberPlayer++;
    }
   
    for (int i = 0; i < numberPlayer; i++) {
        printf("%s %s plays %s, is %d years old, is %d'%d\" and, and weighs %d lbs.\n", jerseyNumbers[i], firstNames[i], lastNames[i], playerPositions[i], playerAges[i], playerFeet[i], playerInches[i], playerWeights[i]);
    }
    printf("Choose a jersey number to display:  ");
    scanf("%d", &searchNumber);

}