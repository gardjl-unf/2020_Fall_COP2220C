/* COP2220C Wednesday September 9, 2020
 * Author: Jason Gardner
 * Filename: project-2_coronavirus_gardner-jason_cop2220c.c
 * Purpose: Calculate/Evaluate Coronavirus Cases
 * Objective: I/O, Arithmetic, Functions, Conditionals
 */

// Headers
#include <stdio.h>

// Function Preconstruction
void DisplayWelcome (void);
double ComputePercentage (int, int);
void DisplayContribution (double);
void DisplayCredits (void);

// Main Function
int main (void) {
    /* Google Style guidelines for C/C++ suggest that variables 
     * should be declared as close to use as possible.  
     * Explanation is that it is a memory consideration.  
     * Initializing early unnecessarily uses memory as the
     * variables might not be used.  In practice, good arguments
     * are made for string literals (localization, readability, and 
     * centralization for changes to code) by my past professors.
     * 
     * Source:  https://google.github.io/styleguide/cppguide.html#Local_Variables
     */

    // String Literals for I/O and User Experience
    const char *PROMPT_STATE_CASES = "Please enter the number of new cases in the state:  ";
    const char *PROMPT_COUNTY_CASES = "Please enter the number of new cases in the county:  ";
    const char *DISPLAY_OUTPUT = "\nCases in State:  \t\t%d\nCases in County:  \t\t%d\nContribution Percentage:  \t%.2f%\n";

    // Variable Declaration/Initialization
    int stateCases = 0;
    int countyCases = 0;

    // Display Welcome Message [Function]
    DisplayWelcome();

    // Acquire Required Inputs from User and Store in Variables
    printf("%s", PROMPT_STATE_CASES);
    scanf("%d", &stateCases);
    printf("%s", PROMPT_COUNTY_CASES);
    scanf("%d", &countyCases);

    // Do Required Arithmetic and Store in Variable [Function]
    double contributionPercentage = ComputePercentage(stateCases, countyCases);

    // Display Output (Inputs and Percentage)
    printf(DISPLAY_OUTPUT, stateCases, countyCases, contributionPercentage);

    // Display Output (Contribution) [Function]
    DisplayContribution(contributionPercentage);

    // Display Output (Credits) [Function]
    DisplayCredits();

    // Main Return
    return 0;
}

void DisplayWelcome (void) {
    // String Literals for I/O and User Experience
    const char *WELCOME_MESSAGE = "Welcome to the Coronavirus Contribution Calculator by Jason Gardner\n\n";

    // Display Welcome Message
    printf("%s", WELCOME_MESSAGE);
}

double ComputePercentage (int stateCases, int countyCases) {
    // Calculate Percentage of Cases in County Compared to the State and Return That Value
    return countyCases*100.0/stateCases;
}

void DisplayContribution (double contributionPercentage) {
    // String Literals for I/O and User Experience
    const char *DISPLAY_CONTRIBUTION = "This contribution percentage is \"%s.\"\n";

    // Structure for Thresholds for Expected Outputs
    struct contributions {
        int contributionThreshold;
        char *contributionDescription;
    };

    /* Given - Thresholds and Associated Outputs
     * Easily modified if thresholds or descriptions change.
     * Note that the data is ordered and any changes must be ordered low->high!
     */

    const struct contributions contributionValues[] = {
        {0, "Little"},
        {5, "Some"},
        {10, "Moderate"},
        {20, "High"},
        {25, "Very High"}
        };

    // Figure out the number of items in the contributionValues array.
    const int contributionLevels = sizeof(contributionValues)/sizeof(contributionValues[0]);

    // Iterate through thresholds and display related message when criteria matches.
    for (int i = contributionLevels - 1; i >= 0; i--) {
        if (contributionPercentage >= contributionValues[i].contributionThreshold) {
            printf(DISPLAY_CONTRIBUTION, contributionValues[i].contributionDescription);
            break;
        }
    }
}

void DisplayCredits (void) {
    // String Literals for I/O and User Experience
    const char *CREDITS = "\nResults Provided by Jason Gardner";

    //  Display Credits
    printf("%s", CREDITS);
}

/* Test Data and Expected Results:
 *  State       County          Percentage      Message
 * 100          25              25.00           Very High
 * 100          10              10.00           Moderate
 * 100          1               1.00            Little
 */

/* Output
 * 
 */