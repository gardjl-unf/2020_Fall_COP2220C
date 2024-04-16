/* COP2220C Wednesday September 9, 2020
 * Author: Jason Gardner
 * Filename: project-2_hurricane[adv]_gardner-jason_cop2220c.c
 * Purpose: Tropical Weather Categorization
 * Objective: Functions, Arithmetic, Logic
 * 
 ***** More Advanced Variant of Project 2 *****
 */

// Headers
#include <stdio.h>
#include <math.h>

// Function Prototypes
void displayWelcome(void);
void displayLatitudeDMS(double);
void displayLongitudeDMS(double);
void displayCategory(int);
void displayCredits(void);

/* Google Style guidelines for C/C++ suggest that variables 
 * should be declared as close to use as possible.  
 * Explanation is that it is a memory consideration.  
 * Initializing early unnecessarily uses memory when the
 * variables might not be used.  In practice, good arguments
 * are made for string literals (localization, readability, and 
 * centralization for changes to U/I), and pre-initialization
 * by my past professors.
 * 
 * Source: https://google.github.io/styleguide/cppguide.html#Local_Variables
 * 
 */

// Main Function
int main (void) {
    // String Literals for I/O and User Experience
    const char *PROMPT_LATITUDE = "Please enter latitude (in degrees):  ";
    const char *PROMPT_LONGITUDE = "Please enter longitude (in degrees):  ";
    const char *PROMPT_WINDSPEED = "Please enter wind speed (in MPH):  ";

    // Variable Declaration/Initialization
    double latitude = 0.0;
    double longitude = 0.0;
    int windspeed = 0;

    // Display Welcome Message (Function)
    displayWelcome();

    // Request Working Data From User (latitude, longitude, windspeed)
    printf("%s", PROMPT_LATITUDE);
    scanf("%lf", &latitude);
    printf("%s", PROMPT_LONGITUDE);
    scanf("%lf", &longitude);
    printf("%s", PROMPT_WINDSPEED);
    scanf("%d", &windspeed);

    // Provide Requested Outputs, Calling Functions for Latitude, Longitude, and Categorization
    displayLatitudeDMS(latitude);
    displayLongitudeDMS(longitude);
    displayCategory(windspeed);

    // Display Credits Message (Function)
    displayCredits();

    // Main Return
    return 0;
}

// displayWelcome Function - Display Welcome Message
void displayWelcome() {
    // String Literals for I/O and User Experience
    const char *WELCOME_MESSAGE = "Welcome to the Tropical Weather Categorizer by Jason Gardner\n\n";

    // Display Welcome Messsage
    printf("%s", WELCOME_MESSAGE);
}

// displayLatitudeDMS Function - Convert Decimal Latitude to Degrees, Minutes, Seconds
void displayLatitudeDMS(double decimalLatitude) {
    // String Literals for I/O and User Experience
    const char *DISPLAY_LATITUDE = "\nStorm Latitude:\t\t%i\370%i'%.3lf\"\n";

    /* Perform Conversion from Decimal -> DMS
    * Always positive (fabs for absolute value), sign indicated by direction.
    * They're (*=60) the remaining fraction after all previous values are subtracted from the original.
    */
    int latitudeDegrees = (int)fabs(decimalLatitude);
    int latitudeMinutes = (int)(fabs(decimalLatitude - latitudeDegrees) * 60);
    double latitudeSeconds = (fabs(decimalLatitude - latitudeDegrees) - latitudeMinutes/60.0) * 3600.0;

    // Display Requested Output
    printf(DISPLAY_LATITUDE, latitudeDegrees, latitudeMinutes, latitudeSeconds);
}

// displayLongitudeDMS Function - Convert Decimal Longitude to Degrees, Minutes, Seconds
void displayLongitudeDMS(double decimalLongitude) {
    // String Literals for I/O and User Experience
    const char *DISPLAY_LONGITUDE = "Storm Longitude:\t%i\370%i'%.3lf\"\n";

    /* Perform Conversion from Decimal -> DMS
    * Always positive (fabs for absolute value), sign indicated by direction.
    * They're (*=60) the remaining fraction after all previous values are subtracted from the original.
    */
    int longitudeDegrees = (int)fabs(decimalLongitude);
    int longitudeMinutes = (int)(fabs(decimalLongitude - longitudeDegrees) * 60);
    double longitudeSeconds = (fabs(decimalLongitude - longitudeDegrees) - longitudeMinutes/60.0) * 3600.0;

    // Display Requested Output
    printf(DISPLAY_LONGITUDE, longitudeDegrees, longitudeMinutes, longitudeSeconds);
}

// displayCategory Function - Display Appropriate Storm Category Based on Wind Speed
void displayCategory(int windSpeed) {
    // String Literals for I/O and User Experience
    const char *DISPLAY_WINDSPEED = "A storm system with a top sustained wind speed of %dMPH is categorized as a \"%s\"\n\n";

    // Structure to Store windspeed Thresholds and Descriptions for These Storms - Given Data
    struct hurricaneCategories {
        int sustainedWindspeed;
        char *stormCategory;
    };

    /* Define hurricane categories in an array of hurricaneCategories
     * Saffir-Simpson Scale
     * Source:  https://www.nhc.noaa.gov/aboutsshws.php
     *          https://www.weather.gov/mob/tropical_definitions
     *          https://en.wikipedia.org/wiki/Saffir%E2%80%93Simpson_scale
     * 
     * "Tropical Depression" is categorized <= 38MPH, and is defined behaviorally =>
     * I could not properly categorize the "None" from given data. It will only
     * occur with negative wind speeds.
     * 
     * Note:    These categories are sorted high -> low if adjustment is needed.
     *          If some sort of structure isn't used, these values are hard-coded
     *          "magic" and changing values/code is much more difficult.
     */
    const struct hurricaneCategories categoryDefinitions[] = {
        {157, "Hurricane Category 5"},
        {130, "Hurricane Category 4"},
        {111, "Hurricane Category 3"},
        {96, "Hurricane Category 2"},
        {74, "Hurricane Category 1"},
        {39, "Tropical storm"},
        {0, "Tropical depression"},
        {-1000, "None"}
    };

    // Acquire Number of Defined Categories - (total/individual) Entries
    const int numberOfCategories = sizeof(categoryDefinitions)/sizeof(categoryDefinitions[0]);

    // Iterate Over Array of Values Until windspeed Value is Categorized
    for (int i = 0; i <= numberOfCategories - 1; i++) {
        // If windspeed Threshold is Exceeded for a Category
        if (windSpeed >= categoryDefinitions[i].sustainedWindspeed) {
            // Display That Category (Format String)
            printf(DISPLAY_WINDSPEED, windSpeed, categoryDefinitions[i].stormCategory);
            break;
        }
    }
}

// displayCredits Function - Display Credits for Program
void displayCredits() {
    // String Literals for I/O and User Experience
    const char *CREDITS_MESSAGE = "Results Provided by Jason Gardner";

    // Display Credits Message
    printf("%s", CREDITS_MESSAGE);
}

/* Test Data and Expected Results (Source: https://www.fcc.gov/media/radio/dms-decimal):
 *  Latitude        Longitude       Wind Speed      Latitude(DMS)       Longitude(DMS)          Category
 *  30.287300       -81.504780      32              30°17'14.2794"      -81°30'17.2074"         Tropical depression
 *  -30.758202      81.594170       100             -30°45'29.5272"     81°35'39.012"           Hurricane Category 2
 *  40.858093       2.294694        72              40°51'29.1342"      2°17'40.8978"           Tropical storm
 *  22.5526         -88.3342        91              22°33'9.36"         -88°20'3.1194"          Hurricane Category 1
 *  -1.299          -33.876         180             -1°17'56.3994"      -33°52'33.5994"         Hurricane Category 5
 */

/* Output

 * Case #1
Welcome to the Tropical Weather Categorizer by Jason Gardner

Please enter latitude (in degrees):  30.287300
Please enter longitude (in degrees):  -81.504780
Please enter wind speed (in MPH):  32

Storm Latitude:         30°17'14.280"
Storm Longitude:        -81°30'17.208"
A storm system with a top sustained wind speed of 32 is categorized as a "Tropical depression"

Results Provided by Jason Gardner

 * Case #2
Welcome to the Tropical Weather Categorizer by Jason Gardner

Please enter latitude (in degrees):  -30.758202
Please enter longitude (in degrees):  81.594170
Please enter wind speed (in MPH):  100

Storm Latitude:         -30°45'29.527"
Storm Longitude:        81°35'39.012"
A storm system with a top sustained wind speed of 100 is categorized as a "Hurricane Category 2"

Results Provided by Jason Gardner

 * Case #3
Welcome to the Tropical Weather Categorizer by Jason Gardner

Please enter latitude (in degrees):  40.858093
Please enter longitude (in degrees):  2.294694
Please enter wind speed (in MPH):  72

Storm Latitude:         40°51'29.135"
Storm Longitude:        2°17'40.898"
A storm system with a top sustained wind speed of 72 is categorized as a "Tropical storm"

Results Provided by Jason Gardner

 * Case #4
 * 
Welcome to the Tropical Weather Categorizer by Jason Gardner

Please enter latitude (in degrees):  22.5526
Please enter longitude (in degrees):  -88.3342
Please enter wind speed (in MPH):  91

Storm Latitude:         22°33'9.360"
Storm Longitude:        -88°20'3.120"
A storm system with a top sustained wind speed of 91 is categorized as a "Hurricane Category 1"

Results Provided by Jason Gardner

 * Case #5
Welcome to the Tropical Weather Categorizer by Jason Gardner

Please enter latitude (in degrees):  -1.299
Please enter longitude (in degrees):  -33.876
Please enter wind speed (in MPH):  180

Storm Latitude:         -1°17'56.400"
Storm Longitude:        -33°52'33.600"
A storm system with a top sustained wind speed of 180 is categorized as a "Hurricane Category 5"

Results Provided by Jason Gardner
 */