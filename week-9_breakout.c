#include <stdio.h>
#include <stdlib.h>

#define LINE_LEN 40
#define POS_LEN 5
#define MAX_PLAYERS 100
#define LEN_NAME 30
#define LEN_POSITION 5

typedef struct
{
    int jersey;
    char firstName[LEN_NAME +1];
    char lastName [LEN_NAME +1];
    char positions [LEN_POSITION +1];
    int heightFeet;
    int heightInches;
    int weight;
    int age;
} player_t;

void displayPlayer (player_t *playerPtr);

int main(void)
{
    FILE *inPtr;
    char tempLine[LINE_LEN];
    player_t team[MAX_PLAYERS];
    player_t *playerPtr = team;
    int index, count;

    inPtr= fopen("Armada_20170705v1.txt","r");
    if(inPtr)
    {
        count = 0;
        while(fgets(tempLine,sizeof(tempLine),inPtr)&& count < MAX_PLAYERS)
        {
            sscanf(tempLine,"%i %s %s %s %i %i %i %i",&playerPtr->jersey, playerPtr->firstName,
                   playerPtr->lastName, playerPtr->positions, &playerPtr->heightFeet, &playerPtr->heightInches,
                   &playerPtr->weight,&playerPtr->age);

            displayPlayer(playerPtr);

            playerPtr++;
            count++;
        }
        fclose(inPtr);
        playerPtr = team;
        /*for(index = 0; index < count-1; index++)
            displayPlayer(playerPtr + index);
            */
    }
    else
        printf("Issues reading file\n");

    return 0;
}

void displayPlayer (player_t *playerPtr)
{
    //More resource efficient to use pointer (4 bytes vs 88 bytes with dot notation)
    printf("%s %s (%i) plays %s, is %i %i, weighs %i pounds, and is %i years old.\n", playerPtr->firstName,
           playerPtr->lastName, playerPtr->jersey, playerPtr->positions, playerPtr->heightFeet, playerPtr->heightInches,
           playerPtr->weight,playerPtr->age);
}
