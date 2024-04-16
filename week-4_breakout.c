/* COP2220C Wednesday September 24, 2020
 * Author: Dylan 
 * Filename: week-4_breakout.c
 * Purpose: 
 * Objective: 
 */

// Headers
#include <stdio.h>

// Main Function
int main (void) {
    int tableNumber = 1;
    while (tableNumber!=0) {
        printf("%s", "Please enter number for multiplication table (0 to Quit):  ");
        scanf("%d", tableNumber);
        for (int i = 0; i <= 10; i++) {
            printf("%d * %d = %d\n", tableNumber, i, tableNumber*i);
        }
        
    }
    printf("%s", "Goodbye!");
    // Return
    return 0;
}