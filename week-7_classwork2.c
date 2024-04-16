/* COP2220C Wednesday October 14, 2020
 * Author: Jason Gardner
 * Filename: week-7)classwork.c
 * Purpose: Get name
 * Objective: Strings
 */

// Headers
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Definitions
#define LEN_NAME 80

// Function Prototypes
void convertToLower(char *inputString, int length);
void convertToUpper(char *inputString, int length);

// Main Function
int main (void) {
    // String Literals for I/O and User Experience
    const char *PROMPT_FIRSTNAME = "Please enter your first name:  ";
    const char *PROMPT_LASTNAME = "Please enter your last name:  ";
    const char *DISPLAY_NAME = "You entered the name %s\n";
    const char *DISPLAY_LENGTH = "Your name is %i characters long.\n";
    const char *DISPLAY_COMPARE = "Comparing %s to %s is %i.\n";
    // Variable Declaration/Initialization
    char fullName[LEN_NAME + 1];
    char firstName[LEN_NAME + 1];
    char lastName[LEN_NAME + 1];
    char fullNameUpper[LEN_NAME + 1];
    char firstNameUpper[LEN_NAME + 1];
    char lastNameUpper[LEN_NAME + 1];
    char fullNameLower[LEN_NAME + 1];
    char firstNameLower[LEN_NAME + 1];
    char lastNameLower[LEN_NAME + 1];
    int compareResult = 0;
    // Work
    printf(PROMPT_FIRSTNAME);
    fgets(firstName, LEN_NAME, stdin);
    printf(PROMPT_LASTNAME);
    fgets(lastName, LEN_NAME, stdin);
    firstName[strlen(firstName) - 1] = '\0';
    lastName[strlen(lastName) - 1] = '\0';
    strcpy(fullName, firstName);
    strcat(fullName, " ");
    strcat(fullName, lastName);
    printf(DISPLAY_NAME, fullName);
    printf(DISPLAY_LENGTH, strlen(fullName));
    compareResult = strcmp(firstName, lastName);
    printf(DISPLAY_COMPARE, firstName, lastName, compareResult);
    convertToUpper(firstName, LEN_NAME);
    printf(firstName);
    // Return
    return 0;
}

void convertToLower(char *inputString, int length) {
    for (int i = 0; i < length; i++) {
        if (*(inputString + i) >= 'A' && *(inputString + i) <= 'Z') {
            *(inputString + i) = *(inputString + i) + 32;
        }
    }
}

void convertToUpper(char *inputString, int length) {
    for (int i = 0; i < length; i++) {
        if (*(inputString + i) >= 'a' && *(inputString + i) <= 'z') {
            *(inputString + i) = *(inputString + i) - 32;
        }
    }
}

/*
char *titlecase(char *string) {
    char *ptr = NULL;

    ptr = string;

    *ptr = toupper(*ptr);
    for(ptr++ ; *ptr; ptr++)
    {
        if(*ptr==' ')
       {
           ptr++;
           *ptr = toupper(*ptr);
           break;
       }
    }

    return string;
}



char *lowercase(char *string) {
    char *ptr = NULL;

    ptr = string;

    for( ; *ptr; ptr++)
        *ptr = tolower(*ptr);

    return string;
}
*/