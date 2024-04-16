/* COP2220C Wednesday September 9, 2020
 * Author: Jason Gardner
 * Filename: week-2_classwork_gardner-jason_cop2220c.c
 * Purpose: 
 * Objective:  
 */

/* Design Criteria:
 * 
*/

// Headers
#include <stdio.h>

// Function Preconstruction
void displayWelcome (void);
double getLength (void);
double getWidth (void);
double computeArea (double, double);
void displayDimensions (double, double, double);

// Main Function
int main (void) {

    displayWelcome();
    double length = getLength();
    double width = getWidth();
    double area = computeArea(length, width);
    displayDimensions(length, width, area);

    return 0;
}

void displayWelcome (void) {
    const char *WELCOME_MESSAGE = "Welcome to the Area Calculator by Jason Gardner\n\n";
    printf("%s", WELCOME_MESSAGE);
}

double getLength (void) {
    const char *LENGTH_PROMPT = "Please enter the length:\t";
    printf(LENGTH_PROMPT);
    double length = scanf("%lf", &length);
    return length;
}

double getWidth (void) {
    const char *WIDTH_PROMPT = "Please enter the width:\t\t";
    printf(WIDTH_PROMPT);
    double width = scanf("%lf", &width);
    return width;
}

double computeArea (double length, double width) {
    return (length * width);
}

void displayDimensions (double length, double width, double area) {
    const char *DISPLAY_LENGTH = "\nThe length is: \t%.2lf\n";
    const char *DISPLAY_WIDTH = "The width is: \t%.2lf\n";
    const char *DISPLAY_AREA = "The area is: \t%.2lf\n";

    printf(DISPLAY_LENGTH, length);
    printf(DISPLAY_WIDTH, width);
    printf(DISPLAY_AREA, area);
}

/* Test Data and Expected Results:
 * 
 */

/* Output
 * 
 */