/* COP2220C Wednesday October 14, 2020
 * Author: Jason Gardner
 * Filename: week-7)classwork.c
 * Purpose: Get name
 * Objective: Strings
 */

// Headers
#include <stdio.h>

// Definitions
#define LEN_NAME 80

// Function Prototypes

// Main Function
int main (void) {
    // String Literals for I/O and User Experience
    char *PROMPT_NAME = "Please enter your name:  ";
    char *DISPLAY_NAME = "You entered the name %s";
    // Variable Declaration/Initialization
    char fullName[LEN_NAME + 1];
    // Work
    printf(PROMPT_NAME);
    fgets(fullName, LEN_NAME, stdin);
    printf(DISPLAY_NAME, fullName);
    // Return
    return 0;
}