/* COP2220C Wednesday September 30, 2020
 * Author: Jason Gardner
 * Filename: week-5_inclass.c
 * Purpose: 
 * Objective: Arrays
 */

// Headers
#include <stdio.h>
#include <ctype.h>

// Defines

// Function Prototypes
double computeAverage (int *values, int numElements);
int inputElements (int *values, int numElements);
int checkHighest (int values[], int numElements);
int checkLowest (int values[], int numElements);

// Main Function
int main (void) {
    // Variable Declaration/Initialization
    int numValues = 7;
    int highs[] = {77,82,81,78,77,79,78};
    int lows[] = {61,56,58,58,62,64,64};
    double avgHigh=0.0, avgLow=0.0;
    int highestHigh = 0, lowestHigh = 0, highestLow = 0, lowestLow = 0;
    //printf("Please Input Highs:  \n");
    //numValues = inputElements(highs, numValues);
    //printf("Please Input Lows:  \n");
    //numValues = inputElements(lows, numValues);
    // Work
    for (int i=0;i<numValues;i++) {
       printf("The Temperatures for Day %d:\tHigh: %3d, Low: %3d\n", i+1, highs[i], lows[i]);
    }
    avgHigh = computeAverage(highs, numValues);
    avgLow = computeAverage(lows, numValues);
    highestHigh = checkHighest(highs, numValues);
    lowestHigh = checkLowest(highs, numValues);
    highestLow = checkHighest(lows, numValues);
    lowestLow = checkLowest(lows, numValues);
    printf("Average High: %lf\tAverage Low: %lf", avgHigh, avgLow);
    printf("\nHighest High:  %d\t Lowest High:  %d", highestHigh, lowestHigh);
    printf("\nHighest Low:  %d\t Lowest Low:  %d", highestLow, lowestLow);
    printf("\nSize of Array: %d", sizeof(highs));           
    // Return
    return 0;
}

double computeAverage (int values[], int numElements) {
    int total = 0;
    double average = 0.0;
    for (int i=0;i<numElements;i++) {
        total += values[i];
    }
    average = (double)total/numElements;
    return average;
}
 int inputElements (int values[], int numElements) {
     int number = 0;
     char another = 'y';
     while (tolower(another)!= 'n') {
         for (int i=0;i<numElements;i++) {
             printf("Please enter a value: ");
             scanf("%d", &number);
             values[i] = number;
             printf("Would you like to enter another value? [Y]es/[N]o:  ");
             scanf("\n%c", &another);
             if (tolower(another)=='n') {
                 return i+1;
             }
         }
     }
     return numElements;
 }

 int checkHighest (int values[], int numElements) {
     int highestValue = 0;
     for (int i; i<numElements; i++) {
        highestValue=highestValue<values[i]?values[i]:highestValue;
     }
     return highestValue;
 }
 int checkLowest (int values[], int numElements) {
     int lowestValue = 1000;
     for (int i; i<numElements; i++) {
        lowestValue=lowestValue>values[i]?values[i]:lowestValue;
     }
     return lowestValue;
 }