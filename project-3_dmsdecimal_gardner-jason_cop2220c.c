/* COP2220C Thursday September 30, 2020
 * Author: Jason Gardner
 * Filename: project-3_dmsdecimal_gardner-jason_cop2220c.c
 * Purpose: Convert Coordinates (DMS -> Decimal)
 * Objective: Functions, Arithmetic, Loops, Input Sanitization/"Sanity Check"
 */

// Headers
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

// Function Prototypes
void displayWelcome(void);
void displayCredits(void);
int getDegrees(void);
int getMinutes(void);
double getSeconds(void);
bool getDirection(void);
double dmsToDecimal(int degrees, int minutes, double seconds, bool isNeg);
void displayOutput(double latitude, double longitude);

// Main Function
int main (void) {
    // Variable Declaration/Initialization
    double latitudeDecimal = 0.0;
    double longitudeDecimal = 0.0;
    bool isNegLatitude = false;
    bool isNegLongitude = false;
    int latitudeDegrees = 0;
    int longitudeDegrees = 0;
    int latitudeMinutes = 0;
    int longitudeMinutes = 0;
    double latitudeSeconds = 0.0;
    double longitudeSeconds = 0.0;
    char sentinel = 'y';

    // Display Welcome Message (Function)
    displayWelcome();

    // Run Program Until User enters 'n' or 'N'
    while (tolower(sentinel) != 'n') {

        // Latitude
        printf("\t*** Latitude ***\n");
        // Acquire Inputs from User [Degrees, Minutes, Seconds, Direction] (Function)
        latitudeDegrees = getDegrees();
        latitudeMinutes = getMinutes();
        latitudeSeconds = getSeconds();
        isNegLatitude = getDirection();
        // Perform Conversion from DMS -> Decimal (Function)
        latitudeDecimal = dmsToDecimal(latitudeDegrees, latitudeMinutes, latitudeSeconds, isNegLatitude);

        // Longitude
        printf("\t *** Longitude ***\n");
        // Acquire Inputs from User [Degrees, Minutes, Seconds, Direction] (Function)
        longitudeDegrees = getDegrees();
        longitudeMinutes = getMinutes();
        longitudeSeconds = getSeconds();
        isNegLongitude = getDirection();
        // Perform Conversion from DMS -> Decimal (Function)
        longitudeDecimal = dmsToDecimal(longitudeDegrees, longitudeMinutes, longitudeSeconds, isNegLongitude);

        // Display Specified Output (Function)
        displayOutput(latitudeDecimal, longitudeDecimal);

        // Ask User If They Would Like to Perform Another Conversion (Sentinel Value)
        printf("\n\nCheck another value ([Y]es/[N]o):  ");
        scanf(" %c", &sentinel);
    }

    // Display Credits (Function)
    displayCredits();

    // Main Return (Success!)
    return 0;
}

/* displayWelcome Function
 * Parameters: void
 * Return: void
 * Display Welcome Message
 */
void displayWelcome(void) {
    // Output Welcome Message to Console
    printf("Welcome to the DMS to Decimal Latitude/Longitude Converter by Jason Gardner\n\n");
}

/* displayCredits Function
 * Parameters: void
 * Return: void
 * Display Credits Message
 */
void displayCredits(void) {
    // Output Credits Message to Console
    printf("\nResults Provided by Jason Gardner");
}

/* getDegrees Function
 * Parameters: void
 * Return: int degrees
 * Acquire and Validate User Input (degrees)
 */
int getDegrees(void) {
    // Variable Declaration/Initialization ("Invalid" Value to Enter Loop)
    int degrees = 1000;

    
    /* Note: Latitude is invalid > +/- 90 degrees.
     * This function does not have inputs to differntiate.
     */ 

    // While invalid...
    while (degrees > 180 || degrees < 0) {
        // Ask User for Value
        printf("Please enter the number of degrees:  ");
        scanf("%d", &degrees);
        if (degrees > 180 || degrees < 0) {
            printf("\nInvalid Entry:  Please enter a valid value between 0 and 180\n");
        }
    }
    return degrees;
}

/* getMinutes Function
 * Parameters: void
 * Return: int minutes
 * Acquire and Validate User Input (minutes)
 */
int getMinutes(void) {
    // Variable Declaration/Initialization ("Invalid" Value to Enter Loop)
    int minutes = 1000;

    // While invalid...
    while (minutes > 60 || minutes < 0) {
        // Ask User for Value
        printf("Please enter the number of minutes:  ");
        scanf("%d", &minutes);

        // Warn User of Invalid Value
        if (minutes > 60 || minutes < 0) {
            printf("\nInvalid Entry:  Please enter a valid value between 0 and 60\n");
        }
    }

    // Return to Caller
    return minutes;
}

/* getSeconds Function
 * Parameters: void
 * Return: double seconds
 * Acquire and Validate User Input (seconds)
 */
double getSeconds(void) {
    // Variable Declaration/Initialization ("Invalid" Value to Enter Loop)
    double seconds = 1000;

    // While invalid...
    while (seconds > 60 || seconds< 0) {
        // Ask User for Value
        printf("Please enter the number of seconds:  ");
        scanf("%lf", &seconds);

        // Warn User of Invalid Value
        if (seconds > 60 || seconds < 0) {
            printf("\nInvalid Entry:  Please enter a valid value between 0 and 60\n");
        }
    }

    // Return to Caller
    return seconds;
}

/* getDirection Function
 * Parameters: void
 * Return: bool isNeg
 * Acquire and Validate User Input (direction) and Return if Our Final Output Should Be Negative
 */
bool getDirection(void) {
    // Variable Declaration/Initialization
    bool isNeg = false;
    char direction = '0';
    // While invalid...
    while (tolower(direction) != 'n' && tolower(direction) != 's' && tolower(direction) != 'e' && tolower(direction) != 'w') {
        // Ask User for Value
        printf("Please enter a direction ([N]orth, [S]outh, [E]ast, or [W]est):  ");
        scanf(" %c", &direction);

        // Warn User of Invalid Value
        if (tolower(direction) != 'n' && tolower(direction) != 's' && tolower(direction) != 'e' && tolower(direction) != 'w') {
            printf("\nInvalid Entry:  Please enter a valid value ([N]orth, [S]outh, [E]ast, or [W]est)\n");
        }
    }

    // Evaluate If Input Direction Indicates a Negative Result
    // South and West Are Negative
    if (tolower(direction) == 's' || tolower(direction) == 'w') {
        isNeg = true;
    }
    // North and East Are Not Negative
    else if (tolower(direction) == 'n' || tolower(direction) == 'e') {
        isNeg = false;
    }

    // Return to Caller
    return isNeg;
}

/* dmsToDecimal Function
 * Parameters: int degrees, int minutes, double seconds, bool isNeg
 * Return: double decimal
 * Use Input Values to Calculate Decimal Degrees from Components of DMS User Input Values
 * Equation (decimal value) = degrees + minutes/60 + seconds/3600
 */
double dmsToDecimal(int degrees, int minutes, double seconds, bool isNeg) {
    // Variable Declaration/Initialization
    double decimal = 0.0;

    /* Perform Conversion DMS -> Decimal
     * isNeg ternary to make result negative as needed
     * Otherwise, conversion is degrees+minutes/60+seconds/3600
     */
    decimal = (isNeg?-1:1) * ((double)degrees + (double)(minutes/60.0) + seconds/3600.0);

    // Return to Caller
    return decimal;
}

/* displayOutput Function
 * Parameters: double latitude, double longitude
 * Return: void
 * Output Decimal Latitude and Longitude
 */
void displayOutput(double latitude, double longitude) {
    // Display Requested Conversion Output
    printf("\nLatitude and Longitude are:  %.4f, %.4f", latitude, longitude);
}

/* Test Data and Expected Results:
 * Latitude(DMS)                Longitude (DMS)             Latitude                Longitude
 * 30°17'14.2794" North         81°30'17.2074" West         30.287300               -81.504780
 * 30°45'29.5272" South         81°35'39.012" East          -30.758202              81.594170
 * 40°51'29.1342" North         2°17'40.8978" East          40.858093               2.294694
 * 22°33'9.36" North            88°20'3.1194" West          22.5526                 -88.3342
 * 1°17'56.3994" South          33°52'33.5994" West         -1.299                  -33.876
 * 
 * Additional Testing for Flow Control Variables (Tested First Run):
 * Degrees 185 and -5
 * Minutes 75 and -100
 * Seconds 88 and -66
 * Direction 'A' and 'N'
 * Main loop Control 'p'
 */

/* Output
 ***** CASE #1/#2 AND FLOW CONTROL TESTING *****
Welcome to the DMS to Decimal Latitude/Longitude Converter by Jason Gardner

        *** Latitude ***
Please enter the number of degrees:  185

Invalid Entry:  Please enter a valid value between 0 and 180
Please enter the number of degrees:  -5

Invalid Entry:  Please enter a valid value between 0 and 180
Please enter the number of degrees:  30
Please enter the number of minutes:  75

Invalid Entry:  Please enter a valid value between 0 and 60
Please enter the number of minutes:  -100

Invalid Entry:  Please enter a valid value between 0 and 60
Please enter the number of minutes:  17
Please enter the number of seconds:  88

Invalid Entry:  Please enter a valid value between 0 and 60
Please enter the number of seconds:  -66

Invalid Entry:  Please enter a valid value between 0 and 60
Please enter the number of seconds:  14.2794
Please enter a direction ([N]orth, [S]outh, [E]ast, or [W]est):  A

Invalid Entry:  Please enter a valid value ([N]orth, [S]outh, [E]ast, or [W]est)
Please enter a direction ([N]orth, [S]outh, [E]ast, or [W]est):  N
         *** Longitude ***
Please enter the number of degrees:  81
Please enter the number of minutes:  30
Please enter the number of seconds:  17.2074
Please enter a direction ([N]orth, [S]outh, [E]ast, or [W]est):  w

Latitude and Longitude are:  30.2873, -81.5048

Check another value ([Y]es/[N]o):  p
        *** Latitude ***
Please enter the number of degrees:  30
Please enter the number of minutes:  45
Please enter the number of seconds:  29.5272
Please enter a direction ([N]orth, [S]outh, [E]ast, or [W]est):  s
         *** Longitude ***
Please enter the number of degrees:  81
Please enter the number of minutes:  35
Please enter the number of seconds:  39.012
Please enter a direction ([N]orth, [S]outh, [E]ast, or [W]est):  e

Latitude and Longitude are:  -30.7582, 81.5942

Check another value ([Y]es/[N]o):  n

Results Provided by Jason Gardner

***** CASE #3 *****
Welcome to the DMS to Decimal Latitude/Longitude Converter by Jason Gardner

        *** Latitude ***
Please enter the number of degrees:  40
Please enter the number of minutes:  51
Please enter the number of seconds:  29.1342
Please enter a direction ([N]orth, [S]outh, [E]ast, or [W]est):  n
         *** Longitude ***
Please enter the number of degrees:  2
Please enter the number of minutes:  17
Please enter the number of seconds:  40.8978
Please enter a direction ([N]orth, [S]outh, [E]ast, or [W]est):  e

Latitude and Longitude are:  40.8581, 2.2947

Check another value ([Y]es/[N]o):  n

Results Provided by Jason Gardner

***** CASE #4 *****
Welcome to the DMS to Decimal Latitude/Longitude Converter by Jason Gardner

        *** Latitude ***
Please enter the number of degrees:  22
Please enter the number of minutes:  33
Please enter the number of seconds:  9.36
Please enter a direction ([N]orth, [S]outh, [E]ast, or [W]est):  n
         *** Longitude ***
Please enter the number of degrees:  88
Please enter the number of minutes:  20
Please enter the number of seconds:  3.1194
Please enter a direction ([N]orth, [S]outh, [E]ast, or [W]est):  w

Latitude and Longitude are:  22.5526, -88.3342

Check another value ([Y]es/[N]o):  n

Results Provided by Jason Gardner

***** CASE #5 *****
Welcome to the DMS to Decimal Latitude/Longitude Converter by Jason Gardner

        *** Latitude ***
Please enter the number of degrees:  1
Please enter the number of minutes:  17
Please enter the number of seconds:  56.3994
Please enter a direction ([N]orth, [S]outh, [E]ast, or [W]est):  s
         *** Longitude ***
Please enter the number of degrees:  33
Please enter the number of minutes:  52
Please enter the number of seconds:  33.5994
Please enter a direction ([N]orth, [S]outh, [E]ast, or [W]est):  w

Latitude and Longitude are:  -1.2990, -33.8760

Check another value ([Y]es/[N]o):  n

Results Provided by Jason Gardner
 */