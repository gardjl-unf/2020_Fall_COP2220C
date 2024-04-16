/* COP2220C Sunday September 6, 2020
 * Author: Jason Gardner
 * Filename: week-1_classwork_gardner-jason_cop2220c.c
 * Purpose: Calculate a percentage-based payraise.
 * Objective: Demonstrate familiarity with I/O, arithemetic, functions
 */

/* Design Criteria:
 * Design a program that will use functions to
 * Request the user to enter a player number
 * Request the user to enter a salary
 * Request the user to enter a percentage raise
 * Print a message that the player earns the current
 * salary and will earn the adjusted salary
*/

#include <stdio.h>

int main (void);
void GetPlayerNumber (int*);
void GetPlayerSalary (double*);
void GetPlayerRaise (float*);
void CalculateNewSalary (double, float, double*);
void DisplayOutput (int, double, double);

int main (void) {
    const char *WELCOME_MESSAGE = "Welcome to the Salary Increase Calculator by Jason Gardner\n\n";
    int playerNumber = 0;
    double playerSalary = 0.0;
    float playerRaise = 0.0;
    double playerNewSalary = 0.0;
    printf(WELCOME_MESSAGE);
    GetPlayerNumber(&playerNumber);
    GetPlayerSalary(&playerSalary);
    GetPlayerRaise(&playerRaise);
    CalculateNewSalary (playerSalary, playerRaise, &playerNewSalary);
    DisplayOutput(playerNumber, playerSalary, playerNewSalary);
    return 0;
}

void GetPlayerNumber (int *playerNumber) {
    const char *PROMPT_PLAYERNUMBER = "Please enter the player number:  ";
    printf("%s", PROMPT_PLAYERNUMBER);
    scanf("%i", playerNumber);
}

void GetPlayerSalary (double *playerSalary) {
    const char *PROMPT_PLAYERSALARY = "Please enter the player salary:  ";
    printf("%s", PROMPT_PLAYERSALARY);
    scanf("%lf", playerSalary);
}

void GetPlayerRaise (float *playerRaise) {
    const char *PROMPT_PLAYERRAISE = "Please enter the player raise percentage:  ";
    printf("%s", PROMPT_PLAYERRAISE);
    scanf("%f", playerRaise);
}

void CalculateNewSalary (double playerSalary, float playerRaise, double *playerNewSalary) {
    *playerNewSalary = playerSalary * (1 + playerRaise/100);
}

void DisplayOutput (int playerNumber, double playerSalary, double playerRaise) {
    const char *DISPLAY_OUTPUT = "\nPlayer %i's salary increased from $%.2f to $%.2f.";
    printf(DISPLAY_OUTPUT, playerNumber, playerSalary, playerRaise);
}