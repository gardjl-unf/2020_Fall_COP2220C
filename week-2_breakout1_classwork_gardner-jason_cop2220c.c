/* COP2220C September 9, 2020
 * Author: Breakout Group 5:  William Thompson, Jason Gardner
 * Filename: week-2_breakout1_classwork_gardner-jason_cop2220c.c
 * Purpose:  Convert F to C and C to F
 * Objective: Functions, Arithmetic
 */

// Headers
#include <stdio.h>

// Function Preconstruction
double getTemperature(char*);
double cToF(double);
double fToC(double);

// Main Function
int main (void) {
    double fahrenheit = getTemperature("fahrenheit");
    double celsius = getTemperature("celsius");
    printf("\nF: %.2lf, C: %.2lf\n", fahrenheit, fToC(fahrenheit));
    printf("F: %.2lf, C: %.2lf", cToF(celsius), celsius);
    // Return
    return 0;
}

// getTemperature Function
double getTemperature (char* type) {
    double temperature;
    printf("Please enter temperature in %s:\t\t", type);
    scanf("%lf", &temperature);
    return temperature;
}

// Farenheit to Celsius Function
double fToC (double fahrenheit) {
    double celsius = ( fahrenheit - 32 ) * 5/9;
    return celsius;
}

// Celsius to Farenheit Function
double cToF (double celsius) {
    double fahrenheit = ( 9/5 * celsius ) + 32;
    return fahrenheit;
}
/* Test Data and Expected Results:
 * 
 */

/* Output
 * 
 */