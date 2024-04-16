/* COP2220C Saturday October 3, 2020
 * Author: Jason Gardner
 * Filename: project-4_covid_gardner-jason_cop2220c.c
 * Purpose: Track Duval County Covid-19 Data
 * Objective: Arrays, Loops, Pass by Reference ("Pointers")
 */

// Headers
#include <stdio.h>
#include <limits.h>

// Definitions
#define NUM_DAYS 30

// Function Prototypes
void displayWelcome(void);
void displayCredits(void);
int getOption(void);
int findHighest(int *numbers, int arraySize);
int findLowest(int *numbers, int arraySize);
double computeAverage(int *numbers, int arraySize);
int findValue(int value, int *numbers, int arraySize);

// Main Function
int main (void) {
    // String Literals for I/O and User Experience
    const char *DISPLAY_LOWEST = "\nThe lowest number of cases was:  %d on %d\n";
    const char *DISPLAY_HIGHEST = "\nThe highest number of cases was:  %d on %d\n";
    const char *DISPLAY_AVERAGE = "\nThe average number of cases was:  %.2lf\n";
    const char *SEARCH_PROMPT = "Please enter a search value (by date):  ";
    const char *DISPLAY_SEARCH_SUCCESS = "\nSearch Result:  Number of cases on %d was %d.\n";
    const char *DISPLAY_SEARCH_FAILURE = "\nSearch Result: Date was not found in the case data.\n";

    // Variable Declaration/Initialization
    int cases[NUM_DAYS] = { 40, 39, 42, 13, 13,
                    22, 22, 27, 31, 29,
                    14, 27, 15, 49, 23, 
                    39, 32, 47, 56, 73, 
                    99, 143, 199, 275, 193, 
                    130, 214, 305, 446, 678 };
    int dates[NUM_DAYS] = { 528, 529, 530, 531, 601, 
                    602, 603, 604, 605, 606, 
                    607, 608, 609, 610, 611, 
                    612, 613, 614, 615, 616, 
                    617, 618, 619, 620, 621, 
                    622, 623, 624, 625, 626 };
    int sentinel = -1, highest = 0, lowest = 0, searchIndex = 0, searchValue = 0;
    double average = 0.0;
    // Work
    displayWelcome();
    do {
        sentinel = getOption();
        switch (sentinel) {
            case 0:
                break;
            case 1:
                lowest = findLowest(cases, NUM_DAYS);
                printf(DISPLAY_LOWEST, cases[lowest], dates[lowest]);
                break;
            case 2:
                highest = findHighest(cases, NUM_DAYS);
                printf(DISPLAY_HIGHEST, cases[highest], dates[highest]);
                break;
            case 3:
                average = computeAverage(cases, NUM_DAYS);
                printf(DISPLAY_AVERAGE, average);
                break;
            case 4:
                printf(SEARCH_PROMPT);
                scanf("%d", &searchValue);
                searchIndex = findValue(searchValue, dates, NUM_DAYS);
                if (searchIndex != -1) {
                    printf(DISPLAY_SEARCH_SUCCESS, dates[searchIndex], cases[searchIndex]);
                }
                else {
                    printf(DISPLAY_SEARCH_FAILURE);
                }
                break;
            case 5:
            default:
                break;
        }
    } while (sentinel != 0);
    displayWelcome();
    // Return
    return 0;
}

void displayWelcome(void) {
    // String Literals for I/O and User Experience
    const char *DISPLAY_WELCOME = "Welcome to the Duval County, FL COVID-19 Evaluator by Jason Gardner\n";

    //
    printf(DISPLAY_WELCOME);
}

void displayCredits(void) {
    // String Literals for I/O and User Experience
    const char *DISPLAY_CREDITS = "Results provided by Jason Gardner";

    //
    printf(DISPLAY_CREDITS);
}

int getOption(void) {
    // String Literals for I/O and User Experience
    const char *OPTION_LOWEST = "Find Lowest Number of Cases\n";
    const char *OPTION_HIGHEST = "Find Highest Number of Cases\n";
    const char *OPTION_AVERAGE = "Calculate Average Number of Cases\n";
    const char *OPTION_SEARCH = "Search Data (by Date)";
    const char *OPTION_MINIMUM = "Display Cases (by Minimum)";
    const char *EXIT_PROGRAM = "Exit the Program\n";
    const char *PROMPT_INPUT = "Please Enter an Option [0-%d]:  ";

    int numOptions = 5;
    int input = -1;

    while (input < 0 || input > numOptions) {
        printf("\n1) %s2) %s3) %s4) %s0) %s\n",
                OPTION_LOWEST,
                OPTION_HIGHEST,
                OPTION_AVERAGE,
                OPTION_SEARCH,
                OPTION_MINIMUM,
                EXIT_PROGRAM);
        printf(PROMPT_INPUT, numOptions);
        scanf("%d", &input);
    }
    return input;
}

int findHighest(int *numbers, int arraySize) {
    int highest = 0;
    for (int i = 1; i < arraySize; i++) {
        highest = *(numbers + i) > *(numbers + highest) ? i: highest;
    }
    return highest;
}

int findLowest(int *numbers, int arraySize) {
    int lowest = 0;
    for (int i = 1; i < arraySize; i++) {
        lowest = *(numbers + i) < *(numbers + lowest) ? i: lowest;
    }
    return lowest;
}

double computeAverage(int *numbers, int arraySize) {
    double total = 0.0;
    double average = 0.0;
    for (int i = 0; i < arraySize; i++) {
        total += *(numbers + i);
    }
    average = total / arraySize;
    return average;
}

int findValue(int value, int *numbers, int arraySize) {
    int foundIndex = -1;
    for (int i = 0; i < arraySize; i++) {
        if (value == *(numbers + i)) {
            foundIndex = i;
        }
    }
    return foundIndex;
}

/* Test Data and Expected Results:
 * 
 */

/* Output
 * 
 */