/* COP2220C Wednesday September 9, 2020
 * Author: Jason Gardner
 * Filename: project-2_hurricane_gardner-jason_cop2220c.c
 * Purpose: Tropical Weather Categorization
 * Objective: Functions, Arithmetic, Logic
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

// Main Function
int main (void) {
    // Variable Declaration/Initialization
    double latitude = 0.0;
    double longitude = 0.0;
    int windspeed = 0;

    // Display Welcome Message (Function)
    displayWelcome();

    // Request Working Data From User (latitude, longitude, windspeed)
    printf("Please enter latitude (in degrees):  ");
    scanf("%lf", &latitude);
    printf("Please enter longitude (in degrees):  ");
    scanf("%lf", &longitude);
    printf("Please enter wind speed (in MPH):  ");
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
    // Display Welcome Messsage
    printf("Welcome to the Tropical Weather Categorizer by Jason Gardner\n\n");
}

// displayLatitudeDMS Function - Convert Decimal Latitude to Degrees, Minutes, Seconds
void displayLatitudeDMS(double decimalLatitude) {
    /* Perform Conversion from Decimal -> DMS
    * Always positive (fabs for absolute value), sign indicated by direction.
    * They're (*=60) the remaining fraction after all previous values are subtracted from the original.
    */
    int latitudeDegrees = (int)fabs(decimalLatitude);
    int latitudeMinutes = (int)(fabs(decimalLatitude - latitudeDegrees) * 60);
    double latitudeSeconds = (fabs(decimalLatitude - latitudeDegrees) - latitudeMinutes/60.0) * 3600.0;

    // Display Requested Output
    printf("\nStorm Latitude:\t\t%i\370%i'%.3f\" ", latitudeDegrees, latitudeMinutes, latitudeSeconds);
    // Determine "Direction" [Relationship to Equator]
    if (decimalLatitude > 0) {
        printf("%s", "North\n");
    }
    else {
        printf("%s", "South\n");
    }
    /***** Alternative - MORE ADVANCED *****
    * printf("%s", decimalLatitude>0?"North":"South");
    *****/
}

// displayLongitudeDMS Function - Convert Decimal Longitude to Degrees, Minutes, Seconds
void displayLongitudeDMS(double decimalLongitude) {
    /* Perform Conversion from Decimal -> DMS
    * Always positive (fabs for absolute value), sign indicated by direction.
    * They're (*=60) the remaining fraction after all previous values are subtracted from the original.
    */
    int longitudeDegrees = (int)fabs(decimalLongitude);
    int longitudeMinutes = (int)(fabs(decimalLongitude - longitudeDegrees) * 60);
    double longitudeSeconds = (fabs(decimalLongitude - longitudeDegrees) - longitudeMinutes/60.0) * 3600.0;

    // Display Requested Output
    printf("Storm Longitude:\t%i\370%i'%.3f\" ", longitudeDegrees, longitudeMinutes, longitudeSeconds);
    // Determine "Direction" [Relationship to Prime Meridian]
    if (decimalLongitude > 0) {
        printf("%s", "East\n");
    }
    else {
        printf("%s", "West\n");
    }
    /***** Alternative - MORE ADVANCED *****
     * printf("%s", decimalLongitude>0?"East":"West");
     *****/
}

// displayCategory Function - Display Appropriate Storm Category Based on Wind Speed
void displayCategory(int windSpeed) {
    /* Categories by windspeed [Given Data]
     * >=157 "Hurricane Category 5"
     * >= 130 "Hurricane Category 4"
     * >= 111 "Hurricane Category 3"
     * >= 96 "Hurricane Category 2"
     * >= 74 "Hurricane Category 1"
     * >= 39 "Tropical Storm"
     * >= 0 "Tropical Depression"
     * "None" <- No Valid Criteria
     */

    // Set Storm Category to category based on windspeed
    if (windSpeed >= 157) {
        printf("A storm system with a top sustained wind speed of %dMPH is categorized as a \"%s\"\n\n", windSpeed, "Hurricane Category 5");
    } 
    else if (windSpeed >= 130) {
        printf("A storm system with a top sustained wind speed of %dMPH is categorized as a \"%s\"\n\n", windSpeed, "Hurricane Category 4");
    } 
    else if (windSpeed >= 111) {
        printf("A storm system with a top sustained wind speed of %dMPH is categorized as a \"%s\"\n\n", windSpeed, "Hurricane Category 3");
    } 
    else if (windSpeed >= 96) {
        printf("A storm system with a top sustained wind speed of %dMPH is categorized as a \"%s\"\n\n", windSpeed, "Hurricane Category 2");
    } 
    else if (windSpeed >= 74) {
        printf("A storm system with a top sustained wind speed of %dMPH is categorized as a \"%s\"\n\n", windSpeed, "Hurricane Category 1");
    } 
    else if (windSpeed >= 39) {
        printf("A storm system with a top sustained wind speed of %dMPH is categorized as a \"%s\"\n\n", windSpeed, "Tropical storm");
    } 
    else if (windSpeed >= 0) {
        printf("A storm system with a top sustained wind speed of %dMPH is categorized as a \"%s\"\n\n", windSpeed, "Tropical depression");
    } else {
        printf("A storm system with a top sustained wind speed of %dMPH is categorized as a \"%s\"\n\n", windSpeed, "None");
    }

    /***** Alternative MORE ADVANCED *****
    
    const char *DISPLAY_WINDSPEED = "A storm system with a top sustained wind speed of %dMPH is categorized as a \"%s\"\n\n";
    
    struct hurricaneCategories {
        int sustainedWindspeed;
        char *stormCategory;
    };

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

    const int numberOfCategories = sizeof(categoryDefinitions)/sizeof(categoryDefinitions[0]);

    for (int i = 0; i <= numberOfCategories - 1; i++) {
        // If windspeed Threshold is Exceeded for a Category
        if (windSpeed >= categoryDefinitions[i].sustainedWindspeed) {
            // Display That Category (Format String)
            printf(DISPLAY_WINDSPEED, windSpeed, categoryDefinitions[i].stormCategory);
            break;
        }
    }

    *****/
}

// displayCredits Function - Display Credits for Program
void displayCredits() {
    // Display Credits Message
    printf("Results Provided by Jason Gardner");
}

/* Test Data and Expected Results (Source: https://www.fcc.gov/media/radio/dms-decimal):
 *  Latitude        Longitude       Wind Speed      Latitude(DMS) + Direction     Longitude(DMS)          Category
 *  30.287300       -81.504780      32              30°17'14.2794" North          81°30'17.2074" West     Tropical depression
 *  -30.758202      81.594170       100             30°45'29.5272" South          81°35'39.012" East      Hurricane Category 2
 *  40.858093       2.294694        72              40°51'29.1342" North          2°17'40.8978" East      Tropical storm
 *  22.5526         -88.3342        91              22°33'9.36" North             88°20'3.1194" West      Hurricane Category 1
 *  -1.299          -33.876         180             1°17'56.3994" South           33°52'33.5994" West     Hurricane Category 5
 */

/* Output

 * Case #1
Welcome to the Tropical Weather Categorizer by Jason Gardner

Please enter latitude (in degrees):  30.287300
Please enter longitude (in degrees):  -81.504780
Please enter wind speed (in MPH):  32

Storm Latitude:         30°17'14.280" North
Storm Longitude:        81°30'17.208" West
A storm system with a top sustained wind speed of 32MPH is categorized as a "Tropical depression"

Results Provided by Jason Gardner

 * Case #2
Welcome to the Tropical Weather Categorizer by Jason Gardner

Please enter latitude (in degrees):  -30.758202
Please enter longitude (in degrees):  81.594170
Please enter wind speed (in MPH):  100

Storm Latitude:         30°45'29.527" South
Storm Longitude:        81°35'39.012" East
A storm system with a top sustained wind speed of 100MPH is categorized as a "Hurricane Category 2"

Results Provided by Jason Gardner

 * Case #3
Welcome to the Tropical Weather Categorizer by Jason Gardner

Please enter latitude (in degrees):  40.858093
Please enter longitude (in degrees):  2.294694
Please enter wind speed (in MPH):  72

Storm Latitude:         40°51'29.135" North
Storm Longitude:        2°17'40.898" East
A storm system with a top sustained wind speed of 72MPH is categorized as a "Tropical storm"

Results Provided by Jason Gardner

 * Case #4
 * 
Welcome to the Tropical Weather Categorizer by Jason Gardner

Please enter latitude (in degrees):  22.5526
Please enter longitude (in degrees):  -88.3342
Please enter wind speed (in MPH):  91

Storm Latitude:         22°33'9.360" North
Storm Longitude:        88°20'3.120" West
A storm system with a top sustained wind speed of 91MPH is categorized as a "Hurricane Category 1"

Results Provided by Jason Gardner

 * Case #5
Welcome to the Tropical Weather Categorizer by Jason Gardner

Please enter latitude (in degrees):  -1.299
Please enter longitude (in degrees):  -33.876
Please enter wind speed (in MPH):  180

Storm Latitude:         1°17'56.400" South
Storm Longitude:        33°52'33.600" West
A storm system with a top sustained wind speed of 180MPH is categorized as a "Hurricane Category 5"

Results Provided by Jason Gardner
 */