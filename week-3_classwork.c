/* COP2220C September 16, 2020
 * Author: Jason Gardner
 * Filename: week-3_classwork.c
 * Purpose: 
 * Objective: Decision Structures
 */

// Notes - ctype.h

// Definitions
#define _USE_MATH_DEFINES

// Headers
#include <stdio.h>
#include <math.h>

// Function Prototypes
double getValue (char*);
double squareArea (double);
double rectangleArea (double, double);
double circleArea (double);

// Main Function
int main (void) {
    // String Literals for I/O and User Experience
    char *WELCOME_MESSAGE = "Welcome to the Area Calculator";
    char *SHAPE_PROMPT = "\nPlease enter the shape -- (S)quare, (R)ectangle, or (C)ircle:  ";
    char *PROMPT_LENGTH = "\nPlease enter the length:  ";
    char *PROMPT_WIDTH = "\nPlease enter the width:  ";
    char *PROMPT_RADIUS = "\nPlease enter the radius:  ";
    char *INVALID_ENTRY = "\nPlease enter a valid shape.";
    char *AREA_OUTPUT_F = "\nThe area is %.2lf.";

    // Variable Declaration/Initialization
    char shape;
    double length =  0.0;
    double width = 0.0;
    double area = 0.0;

    // Work
    printf(WELCOME_MESSAGE);
    printf(SHAPE_PROMPT);
    scanf("\n%c", &shape);

    if (shape == 's' || shape == 'S') {
        length = getValue(PROMPT_LENGTH);
        area = squareArea(length);
    }
    else if (shape == 'r' || shape == 'R') {
        length = getValue(PROMPT_LENGTH);
        width = getValue(PROMPT_WIDTH);
        area = rectangleArea(length, width);
    }
    else if (shape == 'c' || shape == 'C') {
        length = getValue(PROMPT_RADIUS);
        area = circleArea(length);
    }
    else {
        printf(INVALID_ENTRY);
    }

    if (area) {
        printf(AREA_OUTPUT_F, area);
    }



    // Main Function Return
    return 0;
}

double getValue (char *PROMPT) {
    double len_wid_rad;
    printf(PROMPT);
    scanf("%lf", &len_wid_rad);
    return len_wid_rad;
}

double squareArea (double sideLength) {
    double area;
    area = pow(sideLength, 2);
    return area;
}

double rectangleArea (double length, double width) {
    double area;
    area = length * width;
    return area;
}

double circleArea (double radius) {
    double area;
    area = M_PI * pow(radius, 2);
    return area;
}

/* Test Data and Expected Results:
 * 
 */

/* Output
 * 
 */