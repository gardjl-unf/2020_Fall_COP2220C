/* COP2220C Monday August 31, 2020
 * Author: Jason Gardner
 * Filename: project-1_gardner-jason_cop2220c.c
 * Purpose: Coronavirus Recovery Calculator
 * Objective:  Familiarity with I/O and Arithmetic
 */

/* Design Criteria:
 * "Design (using a flowchart and pseuodocode with C syntax) and implement a program that will compute
 * and display the percentage of patients who have recovered from COVID-19. Display a message to welcome 
 * the user to your program. (Include your name in the welcome message.) Prompt the user to input the 
 * number of cases and the number of recoveries. Compute the percentage of recovery as the quotient of 
 * the number of recoveries divided by the number of cases. Display the number of recoveries, the number of
 *  cases, and the percentage of recovery. Display a message that the results were provided by your name. 
 * Include a comment containing your name, course, and date at the beginning of the source code."
*/

#include <stdio.h>

int main (void) {
    // String Literals for I/O and User Experience
    const char *WELCOME_MESSAGE = "Welcome to the Coronavirus Recovery Calculator\nAuthor: Jason Gardner\n\n";
    const char *PROMPT_CASES = "Please enter the number of cases:  ";
    const char *PROMPT_RECOVERIES = "Please enter the number of recoveries:  ";
    // Output String (int, int, float) - Example appears to truncate float
    const char *OUTPUT_MESSAGE = "\nNumber of Cases:\t\t%i\nNumber of Recoveries:\t\t\%i\nPercentage of Recoveries:\t%3.3f%\n\nResults Provided by:  Jason Gardner";

    // Variable Declaration/Initialization
    int cases = 0;
    int recoveries = 0;
    float recoveryPercentage = 0.0;

    // Welcome Message
    printf("%s", WELCOME_MESSAGE);

    // Acquire and Store User Inputs (Number of Cases and Recoveries)
    printf("%s", PROMPT_CASES);
    scanf("%i", &cases);
    printf("%s", PROMPT_RECOVERIES);
    scanf("%i", &recoveries);

    // Calculate Requested Output - Float Conversion
    recoveryPercentage = recoveries*100.0/cases;

    // Display Requested Output
    printf("%s", OUTPUT_MESSAGE, cases, recoveries, recoveryPercentage);

    return 0;
}

/* Test Data and Expected Results:
 * Cases            Recoveries          Recovery Percentage
 * 1763339          496901              28.180
 * 1000000          500000              50.000
 * 100000           100000              100.000
 */

/* Output:
 * Welcome to the Coronavirus Recovery Calculator
 * Author: Jason Gardner
 * 
 * Please enter the number of cases:  1763339
 * Please enter the number of recoveries:  496901
 * 
 * Number of Cases:                1763339
 * Number of Recoveries:           496901
 * Percentage of Recoveries:       28.180
 * 
 * Results Provided by:  Jason Gardner
 * 
 * Welcome to the Coronavirus Recovery Calculator
 * Author: Jason Gardner
 * 
 * Please enter the number of cases:  1000000
 * Please enter the number of recoveries:  500000
 * 
 * Number of Cases:                1000000
 * Number of Recoveries:           500000
 * Percentage of Recoveries:       50.000
 * 
 * Results Provided by:  Jason Gardner
 * 
 * Welcome to the Coronavirus Recovery Calculator
 * Author: Jason Gardner
 * 
 * Please enter the number of cases:  100000
 * Please enter the number of recoveries:  100000
 * 
 * Number of Cases:                100000
 * Number of Recoveries:           100000
 * Percentage of Recoveries:       100.000
 * 
 * Results Provided by:  Jason Gardner
 */