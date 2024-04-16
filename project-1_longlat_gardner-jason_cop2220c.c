/* COP2220C Thursday September 3, 2020
 * Author: Jason Gardner
 * Filename: project-1_gardner-jason_cop2220c.c
 * Purpose: Longitude/Latitude Decimal -> Degrees
 * Objective:  Familiarity with I/O and Arithmetic
 */

/* Design Criteria:
 * "Design (using a flowchart and pseuodocode with C syntax)
 *  and implement a program that will allow the user to enter 
 * their current location in latitude and longitude in decimal 
 * format, convert the location to degrees, minutes, and 
 * seconds format, and display the results. Display a message
 *  to welcome the user to your program. (Include your name
 *  in the welcome message.) Prompt the user to input the 
 * latitude and longitude in decimal format. Convert the 
 * latitude and longitude to degrees, minutes, and seconds 
 * format. Display a message to the user including the 
 * latitude and longitude in decimal format and in degrees,
 *  minutes, and seconds format."
*/

#include <stdio.h>
#include <math.h>

int main (void) {
    // String Literals for I/O and User Experience
    const char *WELCOME_MESSAGE = "Welcome to the Latitude/Longitude Converter (Decimal to Degrees) by Jason Gardner\n\n";
    const char *PROMPT_LATITUDE = "Please enter the latitude:\t";
    const char *PROMPT_LONGITUDE = "Please enter the longitude:\t";
    //  Degree Symbol \370, ASCII '248', Unicode \u00B0
    const char *OUTPUT_MESSAGE = "\nDecimal Coordinates:\t\t%f, %f\nDegree Coordinates:\t\t%i\370%i'%f\", %i\370%i'%f\"";

    // Variable Declaration/Initialization
    float latitude= 0.0;
    int latitudeDegrees = 0;
    int latitudeMinutes = 0;
    double latitudeSeconds = 0.0;

    float longitude = 0.0;
    int longitudeDegrees = 0;
    int longitudeMinutes = 0;
    double longitudeSeconds = 0.0;

    // Display Welcome Message
    printf("%s", WELCOME_MESSAGE);

    // Acquire and Store User Inputs
    printf("%s", PROMPT_LATITUDE);
    scanf("%f", &latitude);
    printf("%s", PROMPT_LONGITUDE);
    scanf("%f", &longitude);

    // Calculate Requested Output

    // Implicit Cast to Integer (Signed)
    latitudeDegrees = latitude;
    // Implicit Cast to Integer (Absolute Value [fabs]) Remainder *= 60
    latitudeMinutes = (fabs(latitude - latitudeDegrees) * 60);
    // (Absolute Value [fabs]) Remainder *= 60 && Slight Variablility (Precision)
    latitudeSeconds = (fabs(latitude - latitudeDegrees) - latitudeMinutes/60.0) * 3600.0;

    // Same Operations Described Above on second variable set.
    longitudeDegrees = longitude;
    longitudeMinutes = (fabs(longitude - longitudeDegrees) * 60);
    longitudeSeconds = (fabs(longitude- longitudeDegrees) - longitudeMinutes/60.0) * 3600.0;

    // Display Requested Output (OUTPUT_MESSAGE is a format string)
    printf(OUTPUT_MESSAGE, latitude, longitude, latitudeDegrees, latitudeMinutes, latitudeSeconds, longitudeDegrees, longitudeMinutes, longitudeSeconds);

    return 1;
}

/* Test Data and Expected Results (Source: https://www.fcc.gov/media/radio/dms-decimal):
 * Latitude           Longitude          Recovery Percentage
 * 30.287300          -81.504780         30°17'14.2794", -81°30'17.2074""
 * -30.758202         81.594170          -30°45'29.5272", 81°35'39.012"
 * 40.858093          2.294694           40°51'29.1342", 2°17'40.8978"
 */

/* Output:
 * Welcome to the Latitude/Longitude Converter (Decimal to Degrees) by Jason Gardner
 * 
 * Please enter the latitude:      30.287300
 * Please enter the longitude:     -81.504780
 * 
 * Decimal Coordinates:            30.287300, -81.504784
 * Degree Coordinates:             30°17'14.280396", -81°30'17.221069"
 * 
 * Welcome to the Latitude/Longitude Converter (Decimal to Degrees) by Jason Gardner
 * 
 * Please enter the latitude:      -30.758202
 * Please enter the longitude:     81.594170
 * 
 * Decimal Coordinates:            -30.758202, 81.594170
 * Degree Coordinates:             -30°45'29.525757", 81°35'39.010620"
 * 
 * Welcome to the Latitude/Longitude Converter (Decimal to Degrees) by Jason Gardner
 * 
 * Please enter the latitude:      40.858093
 * Please enter the longitude:     2.294694
 * 
 * Decimal Coordinates:            40.858093, 2.294694
 * Degree Coordinates:             40°51'29.135742", 2°17'40.898209"
 */