/* COP2220C Wednesday September 9, 2020
 * Author: Jason Gardner
 * Filename: week-2_breakout2_classwork_gardner-jason_cop2220c.c
 * Purpose: Calculate Various Parameters of a Circle
 * Objective: Includes, Functions, Arithmetic
 */

// Definitions
#define _USE_MATH_DEFINES

// Headers
#include <stdio.h>
#include <math.h>

// Function Prototypes
double getDiameter(void);
double computeCircumference(double);
double computeArea(double);
double computeVolume(double);

// Main Function
int main (void) {
    // Variable Declaration/Initializion
    double diameter = 0.0;
    double radius = 0.0;
    double circumference = 0.0;
    double area = 0.0;
    double volume = 0.0;

    // Call getDiameter to set diameter too user value
    diameter = getDiameter();
    
    // radius is half diamter
    radius = diameter / 2;

    /* Call computeCircumference, computeArea, and computeVolume
     * to set related values
     */
    circumference = computeCircumference(radius);
    area = computeArea(radius);
    volume = computeVolume(radius);

    // Provide Requested Output Data (Format String) with diameter, circumference, area, volume
    printf("\nDiameter: %lf\nCircumference: %.3lf\nArea: %.3lf\nVolume: %.3lf", diameter, circumference, area, volume);

    // Main Return
    return 0;
}

// getDiameter Function
double getDiameter(void) {
    // Variable Declaration/Initializion
    double diameter = 0.0;
    
    // Request user enter diameter value and store it to diameter
    printf("Please enter the diameter of the circle:\t");
    scanf("%lf", &diameter);

    // Return diameter to caller
    return diameter;
}

// computeCircumference Function
double computeCircumference(double radius) {
    // Variable Declaration/Initializion
    double circumference = 0.0;

    // Calculate Circumference (circumference = (2)(pi)(r))
    circumference = 2 * M_PI * radius;

    // Return circumference to caller
    return circumference;
}

// computeArea Function
double computeArea(double radius) {
    // Variable Declaration/Initializion
    double area = 0.0;

    // Calculate Area (area = (pi)(r^2))
    area = M_PI * pow(radius, 2);

    // Return area to caller
    return area;
}

// computeVolume Function
double computeVolume(double radius) {
    // Variable Declaration/Initializion
    double volume = 0.0;

    // Calculate Volume (volume = (4/3)(pi)(r^3))
    volume = (4.0/3) * M_PI * pow(radius, 3);

    // Return volume to caller
    return volume;
}