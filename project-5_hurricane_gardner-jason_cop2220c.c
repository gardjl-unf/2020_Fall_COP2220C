/* COP2220C Saturday October 17, 2020
 * Author: Jason Gardner
 * Filename: project-5_hurricane_gardner-jason_cop2220c.c
 * Purpose: Import and Display Hurricane Data
 * Objective: Strings, Files, Functions, Decisions, Loops, Arrays, Pointers
 */

// Headers
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

// Definitions
#define NUM_STORMS 30
#define READ_LENGTH 40

// Function Prototypes
void displayWelcome(void);
void displayCredits(void);
void displayStorm (const char *designator, const char *name, int startdate, int enddate, int windspeed);
int getOption(void);
int calculateDuration(int startDate, int endDate);
bool findString(const char *inputString, const char *compareString);
bool checkChar(char i, char j);
void pauseDisplay(void);

/* main
 * Called at program start
 * 
 * @param void - none
 * @return int - program status
 */
int main (void) {
    // String Literals for I/O and User Experience
    const char *FILE_OPEN_ERROR = "Could not open file %s";
    const char *INPUT_FORMAT = "%s %s %i %i %i";
    const char *SEARCH_STRING = "Please enter the %s you would like to search for [%s]:  ";
    const char *SRESULTS_COUNT = "\nSearch Results: %d Storms Found Matching \"%s\"\n\n";
    const char *IRESULTS_COUNT = "\nSearch Results: %d Storms Found with a %s %s of %d %s\n\n";

    // Variable Declaration/Initialization
    const char *fileName = "StormData_20201017.txt";
    char *readLine = malloc(READ_LENGTH * sizeof(char));
    bool paused = false;
    int numberStorm = 0;
    int option = -1;
    int numResults = 0;
    int numSearch = 0;

    // Allocate Arrays to Be Filled From File Input
    char *stormDesignators[NUM_STORMS][READ_LENGTH] = {NULL};
    char *stormNames[NUM_STORMS][READ_LENGTH] = {NULL};
    int stormStartDates[NUM_STORMS] = {0};
    int stormEndDates[NUM_STORMS] = {0};
    int stormWindspeeds[NUM_STORMS] = {0};
    int stormDurations[NUM_STORMS] = {0};

    // Call displayWelcome
    displayWelcome();

    // Set *inputFile Pointer to File (fileName) in Read Mode
    FILE *inputFile = fopen(fileName, "r");
    // If File Can't Be Opened
    if (inputFile == NULL){
        // Display Error Message
        printf(FILE_OPEN_ERROR, fileName);
        // Free Allocated Memory
        free(readLine);
        // Return 1 (Error)
        return 1;
    }

    // While Data Returned from fgets (from inputFile) is Not Empty
    while (fgets(readLine, READ_LENGTH, inputFile) != NULL) {
        // Read in Data to Arrays Allocated for this Purpose
        sscanf(readLine, INPUT_FORMAT, (char*)stormDesignators[numberStorm], (char*)stormNames[numberStorm], &stormStartDates[numberStorm], &stormEndDates[numberStorm], &stormWindspeeds[numberStorm]);
        // Iterate Accumulator for Number of Storms
        numberStorm++;
    }

    // Close File
    fclose(inputFile);

    // For each storm
    for (int i = 0; i < numberStorm; i ++) {
        // Call calculateDuration to populate stormDurations array
        stormDurations[i] = calculateDuration(stormStartDates[i], stormEndDates[i]);
    }

    // While option is Not 0
    while (option != 0) {
        // Set option to return from getOption
        option = getOption();
        // Switch statement for variable option
        switch (option) {
            // Exit condition
            case 0:
                break;
            // Display all storms
            case 1:
                // For each storm
                for (int i = 0; i < numberStorm; i++) {
                    // If index is multiple of 10, not 0, and not paused
                    if (((i % 10) == 0) && i != 0 && !paused) {
                        // Call pauseDisplay and set paused flag
                        pauseDisplay();
                        paused = true;
                    }
                    // Call displayStorm and unset paused flag
                    paused = false;
                    displayStorm((char*)stormDesignators[i], (char*)stormNames[i], stormStartDates[i], stormEndDates[i], stormWindspeeds[i]);
                }
                // Unset paused flag
                paused = false;
                break;
            // Display storms by designator
            case 2:
                // Prompt user and get search string
                printf(SEARCH_STRING, "designator", "SS/TD/TS/H/MH");
                scanf("%s", readLine);
                // Flush input buffer (bug prevention)
                fflush(stdin);
                // For each storm
                for (int i = 0; i < numberStorm; i++) {
                    // If number of results is multiple of 10, not 0, and not paused
                    if (((numResults % 10) == 0) && numResults != 0 && !paused) {
                        // Call pauseDisplay and set paused flag
                        pauseDisplay();
                        paused = true;
                    }
                    // If string comparison is true
                    if (findString((char*)stormDesignators[i], readLine)) {
                        // Iterate results accumulator
                        numResults++;
                        // Call displayStorm and unset paused flag
                        paused = false;
                        displayStorm((char*)stormDesignators[i], (char*)stormNames[i], stormStartDates[i], stormEndDates[i], stormWindspeeds[i]);
                    }
                }
                // Print message displaying number of results and reset accumulator and paused flag
                printf(SRESULTS_COUNT, numResults, readLine);
                paused = false;
                numResults = 0;
                break;
            // Display storms by name
            case 3:
                // Prompt user and get search string
                printf(SEARCH_STRING, "storm name", "Partial Matches Allowed");
                scanf("%s", readLine);
                // Flush input buffer (bug prevention)
                fflush(stdin);
                // For each storm
                for (int i = 0; i < numberStorm; i++) {
                    // If number of results is multiple of 10, not 0, and not paused
                    if (((numResults % 10) == 0) && numResults != 0 && !paused) {
                        // Call pauseDisplay and set paused flag
                        pauseDisplay();
                        paused = true;
                    }
                    // If string comparison is true
                    if (findString((char*)stormNames[i], readLine)) {
                        // Iterate results accumulator
                        numResults++;
                        // Call displayStorm and unset paused flag
                        paused = false;
                        displayStorm((char*)stormDesignators[i], (char*)stormNames[i], stormStartDates[i], stormEndDates[i], stormWindspeeds[i]);
                    }
                }
                // Print message displaying number of results and reset accumulator and paused flag
                printf(SRESULTS_COUNT, numResults, readLine);
                paused = false;
                numResults = 0;
                break;
            // Display storms by maximum duration
            case 4:
                // Prompt user and get search value
                printf(SEARCH_STRING, "duration", "Maximum (Days");
                scanf("%d", &numSearch);
                // Flush input buffer (bug prevention)
                fflush(stdin);
                // For each storm
                for (int i = 0; i < numberStorm; i++) {
                    // If number of results is multiple of 10, not 0, and not paused
                    if (((numResults % 10) == 0) && numResults != 0 && !paused) {
                        // Call pauseDisplay and set paused flag
                        pauseDisplay();
                        paused = true;
                    }
                    // If search number is greater than or equal to duration at index
                    if (numSearch >= stormDurations[i]) {
                        // Iterate results accumulator
                        numResults++;
                        // Call displayStorm and unset paused flag
                        paused = false;
                        displayStorm((char*)stormDesignators[i], (char*)stormNames[i], stormStartDates[i], stormEndDates[i], stormWindspeeds[i]);
                    }
                }
                // Print message displaying number of results and reset accumulator and paused flag
                printf(IRESULTS_COUNT, numResults, "Maximum", "Duration", numSearch, "Day(s)");
                paused = false;
                numResults = 0;
                break;
            // Display storms by minimum windspeed
            case 5:
                // Prompt user and get search value
                printf(SEARCH_STRING, "windspeed", "Minimum (MPH)");
                scanf("%d", &numSearch);
                // Flush input buffer (bug prevention)
                fflush(stdin);
                // For each storm
                for (int i = 0; i < numberStorm; i++) {
                    // If number of results is multiple of 10, not 0, and not paused
                    if (((numResults % 10) == 0) && numResults != 0 && !paused) {
                        // Call pauseDisplay and set paused flag
                        pauseDisplay();
                        paused = true;
                    }
                    // If search number is less than or equal to duration at index
                    if (numSearch <= stormWindspeeds[i]) {
                        // Iterate results accumulator
                        numResults++;
                        // Call displayStorm and unset paused flag
                        paused = false;
                        displayStorm((char*)stormDesignators[i], (char*)stormNames[i], stormStartDates[i], stormEndDates[i], stormWindspeeds[i]);
                    }
                }
                // Print message displaying number of results and reset accumulator and paused flag
                printf(IRESULTS_COUNT, numResults, "Minimum", "Windspeed", numSearch, "MPH");
                paused = false;
                numResults = 0;
                break;
            // Default condition
            default:
                break;
        }
    }
    // Call displayCredits
    displayCredits();

    // Free Allocated Memory
    free(readLine);

    // Return 0 (Success)
    return 0;
}

/* displayWelcome
 * Display welcome message
 * 
 * @param void - none
 * @return void - none
 */
void displayWelcome(void) {
    // String Literals for I/O and User Experience
    const char *DISPLAY_WELCOME = "Welcome to the 2020 Atlantic Hurricane Information Center by Jason Gardner\n\n";

    //  Display the welcome message
    printf("%s", DISPLAY_WELCOME);
}

/* displayCredits
 * Display credits message
 * 
 * @param void - none
 * @return void - none
 */
void displayCredits(void) {
    // String Literals for I/O and User Experience
    const char *DISPLAY_CREDITS = "\nResults provided by Jason Gardner";

    // Display the credits message
    printf("%s", DISPLAY_CREDITS);
}

/* displayStorm
 * Display storm data to user
 * 
 * @ param const char *designator - Storm designator
 * @param const char *name - Storm name
 * @param int startdate - Storm starting date
 * @param int enddate - Storm ending date
 * @param int windspeed - Storm windspeed
 * @return void - none
 */
void displayStorm (const char *designator, const char *name, int startdate, int enddate, int windspeed) {
    // String Literals for I/O and User Experience
    const char *DISPLAY_STORM = "\n%s\t %s    \tStart:  %d\tEnd:  %d\t Windspeed:  %d";

    // Display storm data
    printf(DISPLAY_STORM, designator, name, startdate, enddate, windspeed);
}

/* getOption
 * Display menu and get menu option from user for return
 * @param void - none
 * @return int - user option input
 */
int getOption(void) {
    // String Literals for I/O and User Experience
    const char *OPTIONS[] = {"Display Information for Storm(s) [All]\n",
                            "Display Information for Storm(s) [by Designator]\n",
                            "Display Information for Storm(s) [by Name]\n",
                            "Display Information for Storm(s) [by Maximum Duration]\n",
                            "Display Information for Storm(s) [by Minimum Windspeed]\n"
                            };
    const char *PRINT_OPTIONS = "\t%d) %s";
    const char *EXIT_PROGRAM = "\t0) Exit the Program\n";
    const char *PROMPT_INPUT = "Please Enter an Option [0-%d]:  ";
    const char *INPUT_ERROR = "\nInvalid Entry:  Please Enter a Number Between 0 and %d\n";

    // Variable Declaration/Initialization
    int numOptions = 5;
    int input = -1;

    // While input is invalid (outside number of options)
    while (input < 0 || input > numOptions) {
        // Display the program option prompt to user
        for (int i = 0; i < numOptions; i++) {
            printf(PRINT_OPTIONS, i + 1, OPTIONS[i]);
        }
        printf("%s", EXIT_PROGRAM);
        printf(PROMPT_INPUT, numOptions);

        // Get user input
        scanf("%d", &input);
        // Flush input buffer (bug prevention)
        fflush(stdin);
        // If input isn't in valid range, display error
        if (input < 0 || input > numOptions) {
            printf(INPUT_ERROR, numOptions);
        }
    }
    // Return input to caller
    return input;
}

/* calculateDuration
 * Calculate duration of storm using start and end date
 * @param int startDate - Storm start date
 * @param int endDate - Storm end date
 * @return int - duration of storm
 */
int calculateDuration(int startDate, int endDate) {
    // Variable Declaration/Initialization
    int duration = 0;

    // Duration is enddate minus startdate
    duration = endDate - startDate;

    // Return duration to caller
    return duration;
}

/* findString
 * Recursively search a string for a substring, returning bool for located
 * 
 * @param char *inputString - String being compared TO
 * @param char *compareString - String being compared FROM
 * @return bool - True if string is found as part of first string
 */
bool findString(const char *inputString, const char *compareString) {
    // Variable Declaration/Initialization
    int i = strlen(compareString) - 1;
    bool matched = true;

    // While the characters are the same (recursive) to 0
    while ((matched = checkChar(inputString[i], compareString[i])) && i > 0) {
        // Iterate back through the string from length
        i--;
    }
    // Return matched to caller
    return matched;
}

/* checkChar
 * Check that characters are the same
 * 
 * @param char i - Character from string
 * @param char j - Character from substring
 * @return bool - If characters match
 */
bool checkChar(char i, char j) {
    // If characters match (lowercase)
    if (tolower(i) == tolower(j)) {
        // Return true to caller
        return true;
    }
    // Return false to caller
    return false;
}

/* pauseDisplay
 * Pause display of results
 * @param void - none
 * @return void - none
 */
void pauseDisplay(void) {
    // String Literals for I/O and User Experience
    const char *PAUSE_DISPLAY = "\n\nPlease Press Enter to Continue...\n";

    // Variable Declaration/Initialization
    char enter = '\0';

    // Display pause
    printf("%s", PAUSE_DISPLAY);
    // While pause isn't newline or carriage return
    while (enter != '\n' && enter != '\r') {
        // Set enter to return from getchar
        enter = getchar();
        // Flush input buffer (bug prevention)
        fflush(stdin);
    }
}

/* Test Cases
Control Flow:
Test '9' and 'q' loop menu (testing fflush [these are why it is necessary])

Option '1':
TS Arthur Start:  516 End:  519 Windspeed: 60
TS Bertha Start:  527 End:  528 Windspeed: 50
TS Cristobal Start:  601 End:  609 Windspeed: 60
TS Dolly Start:  622 End:  624 Windspeed: 45
TS Edouard Start:  704 End:  706 Windspeed: 45
TS Fay Start:  709 End:  711 Windspeed: 60
TS Gonzalo Start:  721 End:  725 Windspeed: 65
H Hanna Start:  723 End:  727 Windspeed: 90
H Isaias Start:  730 End:  805 Windspeed: 85
TD Ten Start:  731 End:  801 Windspeed: 35

Please Press Enter to Continue...

TS Josephine Start:  811 End:  816 Windspeed: 45
TS Kyle Start:  814 End:  816 Windspeed: 50
MH Laura Start:  820 End:  828 Windspeed: 150
H Marco Start:  820 End:  825 Windspeed: 75
H Nana Start:  901 End:  904 Windspeed: 75
TS Omar Start:  831 End:  905 Windspeed: 40
H Paulette Start:  907 End:  922 Windspeed: 105
TS Rene Start:  907 End:  914 Windspeed: 50
H Sally Start:  911 End:  917 Windspeed: 105
MH Teddy Start:  912 End:  922 Windspeed: 140

Please Press Enter to Continue...

TS Vicky Start:  914 End:  917 Windspeed: 50
TS Wilfred Start:  918 End:  920 Windspeed: 40
SS Alpha Start:  918 End:  918 Windspeed: 50
TS Beta Start:  917 End:  922 Windspeed: 60

Option '2' and "TS":
TS Arthur Start:  516 End:  519 Windspeed: 60
TS Bertha Start:  527 End:  528 Windspeed: 50
TS Cristobal Start:  601 End:  609 Windspeed: 60
TS Dolly Start:  622 End:  624 Windspeed: 45
TS Edouard Start:  704 End:  706 Windspeed: 45
TS Fay Start:  709 End:  711 Windspeed: 60
TS Gonzalo Start:  721 End:  725 Windspeed: 65
TS Josephine Start:  811 816 Windspeed: 45
TS Kyle Start:  814 End:  816 Windspeed: 50
TS Omar Start:  831 End:  905 Windspeed: 40

Please Press Enter to Continue...

TS Rene Start:  907 End:  914 Windspeed: 50
TS Vicky Start:  914 End:  917 Windspeed: 50
TS Wilfred Start:  918 End:  920 Windspeed: 40
TS Beta Start:  917 End:  922 Windspeed: 60
Search Results: 14 Storms Found Matching "TS"

Option '3' and "a":

TS Arthur Start:  516 End:  519 Windspeed: 60
SS Alpha Start:  918 End:  918 Windspeed: 50
Search Results: 2 Storms Found Matching "a"

Option '4' and 1:
TS Bertha Start:  527 End:  528 Windspeed: 50
TS Alpha Start:  918 End:  918 Windspeed: 50
Search Results: 2 Storms Found with a Maximum Duration of 1 Day(s)

Option '5' and 105:
MH Laura Start:  820 End:  828 Windspeed:  150
H Paulette Start:  907 End:  922 Windspeed:  105
H Sally Start:  911 End:  917 Windspeed:  105
MH Teddy Start:  912 End:  922 Windspeed:  140
Search Results: 4 Storms Found with a Minimum Windspeed of 105 MPH

Option '0':
Results provided by Jason Gardner
*/

/* Test Runs:
Welcome to the 2020 Atlantic Hurricane Information Center by Jason Gardner

        1) Display Information for Storm(s) [All]
        2) Display Information for Storm(s) [by Designator]
        3) Display Information for Storm(s) [by Name]
        4) Display Information for Storm(s) [by Maximum Duration]
        5) Display Information for Storm(s) [by Minimum Windspeed]        
        0) Exit the Program
Please Enter an Option [0-5]:  9

Invalid Entry:  Please Enter a Number Between 0 and 5
        1) Display Information for Storm(s) [All]
        2) Display Information for Storm(s) [by Designator]
        3) Display Information for Storm(s) [by Name]
        4) Display Information for Storm(s) [by Maximum Duration]
        5) Display Information for Storm(s) [by Minimum Windspeed]
        0) Exit the Program
Please Enter an Option [0-5]:  q

Invalid Entry:  Please Enter a Number Between 0 and 5
        1) Display Information for Storm(s) [All]
        2) Display Information for Storm(s) [by Designator]
        3) Display Information for Storm(s) [by Name]
        4) Display Information for Storm(s) [by Maximum Duration]
        5) Display Information for Storm(s) [by Minimum Windspeed]
        0) Exit the Program
Please Enter an Option [0-5]:  1

TS       Arthur         Start:  516     End:  519        Windspeed:  60
TS       Bertha         Start:  527     End:  528        Windspeed:  50
TS       Cristobal      Start:  601     End:  609        Windspeed:  60
TS       Dolly          Start:  622     End:  624        Windspeed:  45
TS       Edouard        Start:  704     End:  706        Windspeed:  45
TS       Fay            Start:  709     End:  711        Windspeed:  60
TS       Gonzalo        Start:  721     End:  725        Windspeed:  65
H        Hanna          Start:  723     End:  727        Windspeed:  90
H        Isaias         Start:  730     End:  805        Windspeed:  85
TD       Ten            Start:  731     End:  801        Windspeed:  35

Please Press Enter to Continue...


TS       Josephine      Start:  811     End:  816        Windspeed:  45
TS       Kyle           Start:  814     End:  816        Windspeed:  50
MH       Laura          Start:  820     End:  828        Windspeed:  150
H        Marco          Start:  820     End:  825        Windspeed:  75
H        Nana           Start:  901     End:  904        Windspeed:  75
TS       Omar           Start:  831     End:  905        Windspeed:  40
H        Paulette       Start:  907     End:  922        Windspeed:  105
TS       Rene           Start:  907     End:  914        Windspeed:  50
H        Sally          Start:  911     End:  917        Windspeed:  105
MH       Teddy          Start:  912     End:  922        Windspeed:  140

Please Press Enter to Continue...


TS       Vicky          Start:  914     End:  917        Windspeed:  50
TS       Wilfred        Start:  918     End:  920        Windspeed:  40
SS       Alpha          Start:  918     End:  918        Windspeed:  50
TS       Beta           Start:  917     End:  922        Windspeed:  60 1) Display Information for Storm(s) [All]
        2) Display Information for Storm(s) [by Designator]
        3) Display Information for Storm(s) [by Name]
        4) Display Information for Storm(s) [by Maximum Duration]
        5) Display Information for Storm(s) [by Minimum Windspeed]
        0) Exit the Program
Please Enter an Option [0-5]:  2
Please enter the designator you would like to search for [SS/TD/TS/H/MH]:  TS

TS       Arthur         Start:  516     End:  519        Windspeed:  60
TS       Bertha         Start:  527     End:  528        Windspeed:  50
TS       Cristobal      Start:  601     End:  609        Windspeed:  60
TS       Dolly          Start:  622     End:  624        Windspeed:  45
TS       Edouard        Start:  704     End:  706        Windspeed:  45
TS       Fay            Start:  709     End:  711        Windspeed:  60
TS       Gonzalo        Start:  721     End:  725        Windspeed:  65
TS       Josephine      Start:  811     End:  816        Windspeed:  45
TS       Kyle           Start:  814     End:  816        Windspeed:  50
TS       Omar           Start:  831     End:  905        Windspeed:  40

Please Press Enter to Continue...


TS       Rene           Start:  907     End:  914        Windspeed:  50
TS       Vicky          Start:  914     End:  917        Windspeed:  50
TS       Wilfred        Start:  918     End:  920        Windspeed:  40
TS       Beta           Start:  917     End:  922        Windspeed:  60
Search Results: 14 Storms Found Matching "TS"

        1) Display Information for Storm(s) [All]
        2) Display Information for Storm(s) [by Designator]
        3) Display Information for Storm(s) [by Name]
        4) Display Information for Storm(s) [by Maximum Duration]
        5) Display Information for Storm(s) [by Minimum Windspeed]
        0) Exit the Program
Please Enter an Option [0-5]:  3
Please enter the storm name you would like to search for [Partial Matches Allowed]:  a

TS       Arthur         Start:  516     End:  519        Windspeed:  60
SS       Alpha          Start:  918     End:  918        Windspeed:  50
Search Results: 2 Storms Found Matching "a"

        1) Display Information for Storm(s) [All]
        2) Display Information for Storm(s) [by Designator]
        3) Display Information for Storm(s) [by Name]
        4) Display Information for Storm(s) [by Maximum Duration]
        5) Display Information for Storm(s) [by Minimum Windspeed]
        0) Exit the Program
Please Enter an Option [0-5]:  4
Please enter the duration you would like to search for [Maximum (Days]:  1

TS       Bertha         Start:  527     End:  528        Windspeed:  50
SS       Alpha          Start:  918     End:  918        Windspeed:  50
Search Results: 2 Storms Found with a Maximum Duration of 1 Day(s)

        1) Display Information for Storm(s) [All]
        2) Display Information for Storm(s) [by Designator]
        3) Display Information for Storm(s) [by Name]
        4) Display Information for Storm(s) [by Maximum Duration]
        5) Display Information for Storm(s) [by Minimum Windspeed]
        0) Exit the Program
Please Enter an Option [0-5]:  5
Please enter the windspeed you would like to search for [Minimum (MPH)]:  105

MH       Laura          Start:  820     End:  828        Windspeed:  150
H        Paulette       Start:  907     End:  922        Windspeed:  105
H        Sally          Start:  911     End:  917        Windspeed:  105
MH       Teddy          Start:  912     End:  922        Windspeed:  140
Search Results: 4 Storms Found with a Minimum Windspeed of 105 MPH

        1) Display Information for Storm(s) [All]
        2) Display Information for Storm(s) [by Designator]
        3) Display Information for Storm(s) [by Name]
        4) Display Information for Storm(s) [by Maximum Duration]
        5) Display Information for Storm(s) [by Minimum Windspeed]
        0) Exit the Program
Please Enter an Option [0-5]:  0

Results provided by Jason Gardner
*/