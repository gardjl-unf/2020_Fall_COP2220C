/* COP2220C Wednesday September 30, 2020
 * Author: Jason Gardner, Aboubacar Abdoulaye, Carlos Ramirez Pita
 * Filename: week-5_breakout.c
 * Purpose: 
 * Objective: Arrays
 */

// Headers
#include <stdio.h>

// Function Prototypes
int findTallest (int feet[], int inches[], int arrSize);
int findShortest (int feet[], int inches[], int arrSize);
int findAverage (int feet[], int inches[], int arrSize);

// Defines
#define arraySize 15

// Main Function
int main (void) {
    // Variable Declaration/Initialization
    int feet[] =  {6, 5, 6, 6, 5, 5, 6, 6, 5, 5, 5, 6, 5, 5, 5};
    int inches[] =  {3, 7, 1, 1, 7, 9, 2, 2, 7, 8, 11, 1, 5, 10, 8};
    int tallestIndex = 0, shortestIndex = 0, averageInches = 0;


    // Set tallestIndex equal to return from findTallest
    tallestIndex = findTallest(feet, inches, arraySize);
    // Display Output
    printf("Tallest Person is %d'%d\"\n", feet[tallestIndex], inches[tallestIndex]);
    // Set shortestIndex equal to return from findShortest
    shortestIndex = findShortest(feet, inches, arraySize);
    // Display Output
    printf("Shortest Person is %d'%d\"\n", feet[shortestIndex], inches[shortestIndex]);
    // Set averageInches equal to return from findAverage
    averageInches = findAverage (feet, inches, arraySize);
    // Display Output (Feet = Inches/12, Remaining Inches = Inches%12)
    printf("The average height is %d'%d\"\n", averageInches/12, averageInches%12);
    
    return 0;
}

int findTallest (int feet[], int inches[], int arrSize) {
    // Variable Declaration/Initialization
    int tallestIndex = 0;

    // Iterate over the array
    // Note the initial highest is at index 0, so we start iterating at 1
    for (int i = 1; i < arrSize; i++) {
        // If the index is larger than the current (at tallestIndex) by feet, or feet and inches
        if (feet[tallestIndex] < feet[i] || (feet[tallestIndex] <= feet[i] && inches[tallestIndex] < inches[i])) {
            // Set tallest to the current index
            tallestIndex = i;
        }
    }
    // Return tallest
    return tallestIndex;
}

int findShortest (int feet[], int inches[], int arrSize) {
    // Variable Declaration/Initialization
    int shortestIndex = 0;

    // Iterate over the array
    // Note the initial lowest is at index 0, so we start iterating at 1
    for (int i = 1; i < arrSize; i++) {
        // If the index value is smaller than the current (at shortestIndex) by feet, or feet and inches
        if (feet[shortestIndex] > feet[i] || (feet[shortestIndex] >= feet[i] && inches[shortestIndex] > inches[i] )) {
            // Set shortest to the current index
            shortestIndex = i;
        }
    }
    // Return shortest
    return shortestIndex;
}

int findAverage (int feet[], int inches[], int arrSize) {
    // Variable Declaration/Initialization
    int accumulator = 0;

    // Iterate over the array
    for (int i = 0; i < arrSize; i++) {
        // Add up feet and inches (into inches)
        accumulator = feet[i] * 12 + inches [i];
    }
    // Return the added value from across the array
    return accumulator;
}