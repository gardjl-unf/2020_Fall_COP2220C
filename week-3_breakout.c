/* COP2220C September 16, 2020
 * Author: Group 1
 * Filename: week-3_breakout.c
 * Purpose: Temp Conversions
 * Objective: Decision Structures
 */

#include <stdio.h>
#include <ctype.h>

double cToK (double);
double cToF (double);
double fToC (double);
double fToK (double);
double kToF (double);
double kToC (double);

int main (void) {
	double inputTemp = 0.0;
	double outputTemp = 0.0;
	char inputType;
	char outputType;
	printf("%s","Please enter the temperature type (C, F, K):  ");
	scanf("\n%c", &inputType);
	printf("%s","Please enter the temperature:  ");
	scanf("%lf", &inputTemp);
	printf("%s","Convert temperature to (C, F, K):  ");
	scanf("\n%c", &outputType);
	if (tolower(inputType) == 'c')  {
		if (tolower(outputType) == 'f') {
			outputTemp = cToF (inputTemp);
		}
		else if (tolower(outputType) == 'k') {
				outputTemp = cToK (inputTemp);
		}
	    else if (tolower(outputType) == 'c') {
			outputTemp = inputTemp;
		}
		else
			printf("Invalid output value entered.");
	}
	else if (tolower(inputType) == 'f') {
        if (tolower(outputType) == 'c') {
            outputTemp = fToC (inputTemp);
        }
        else if (tolower(outputType) == 'k') {
            outputTemp = fToK (inputTemp);
        }
        else if (tolower(outputType) == 'f') {
            outputTemp = inputTemp;
        }
        else
            printf("Invalid output value entered.");
        }
	else if (tolower(inputType) == 'k') {
		if (tolower(outputType) == 'f') {
			outputTemp = kToF (inputTemp);
        }
        else if (tolower(outputType) == 'c') {
            outputTemp = kToC (inputTemp);
        }
        else if (tolower(outputType) == 'k') {
            outputTemp = inputTemp;
        }
        else
            printf("Invalid output value entered.");
        }
	else {
		printf("Invalid input value entered.");
	}
	if (outputTemp) {
		printf("Output temperature is %.2lf.", outputTemp);
	}
	return 0;
}

double cToF (double inputTemp) {
	double outputTemp;
	outputTemp = (inputTemp * 9/5) + 32;
	return outputTemp;
}

double cToK (double inputTemp) {
	double outputTemp;
	outputTemp = inputTemp + 273.15;
	return outputTemp;
}

double fToC (double inputTemp) {
	double outputTemp;
	outputTemp = (inputTemp - 32) * (5/9);
	return outputTemp;
}

double fToK (double inputTemp) {
	double outputTemp;
	outputTemp = (inputTemp -32) * (5/9) + 273.15;
	return outputTemp;
}

double kToC (double inputTemp) {
	double outputTemp;
	outputTemp = inputTemp - 273.15;
	return outputTemp;
}

double kToF (double inputTemp) {
	double outputTemp;
	outputTemp = (inputTemp - 273.15) * (9/5) +32;
	return outputTemp;
}