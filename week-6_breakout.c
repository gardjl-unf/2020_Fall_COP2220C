/* COP2220C Wednesday October 7, 2020
 * Author: Jason Gardner, Wendolyn Villafuerte
 * Filename: week-6_breakout.c
 * Purpose: Birthmonths
 * Objective: Pointers
 */

// Headers
#include <stdio.h>

// Define
#define NUM 16
#define NUM_MONTHS 12

// Function Prototypes
void displayValues(int *array, int size);
int findHighest(int *array, int size);
int findLowest(int *array, int size);
void displayPercentage(int *array, int size);

// Main Function
int main (void) {
    // Variable Declaration/Initialization
    int birthMonths[NUM] = {6, 9, 7, 9, 9, 5, 8, 6, 6, 4, 3, 12, 3, 7, 12, 12};
    int monthCount[NUM_MONTHS] = {0};
    // Work
    displayValues(birthMonths, NUM);
    for (int i = 0; i < NUM_MONTHS; i++) {
        monthCount[i] = findHighest(birthMonths, NUM);
        printf("\nMonth %d Occurs %d times.", i+1, monthCount[i]);
    }
    // Return
    return 0;
}

void displayValues(int *array, int size) {
    printf("Months array contains:  ");
    for (int i = 0; i < size; i++) {
        printf("%d, ", *(array+i));
    }
}
int findHighest(int *array, int size) {
    int occur = 0;
    for (int i = 1; i <= NUM_MONTHS; i++) {
    //    if (*(array+i) ==) {
    //        occur+=1;
    //    }
    }
    return occur;
    // For each month, count the number of times that month shows up.  We need to get the one that shows up the most.
}

int findLowest(int *array, int size) {

}

void displayPercentage(int *array, int size) {

}