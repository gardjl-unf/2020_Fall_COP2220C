/* COP2220C Friday October 9, 2020
 * Author: Jason Gardner
 * Filename: project-4_hurricane_gardner-jason_cop2220c.c
 * Purpose: 
 * Objective: Functions, Decisions, Arrays, Loops, Pointers
 */

// Headers
#include <stdio.h>
#include <stdbool.h>

// Definitions
#define NUM_STORMS 24

// Function Prototypes
void displayWelcome(void);
void displayCredits(void);
int getOption(void);
void displayStorm(int index, char category, int start, int end, int duration, int windspeed);
int calculateDifference(int firstNumber, int secondNumber);
char categorizeStorm(int windspeed);
int findHighest(int *values, int size);
int findLowest (int *values, int size);
int findValue (int search, int *values, int size);
double calculateAverage(int *values, int size);

// Main Function
int main (void) {
    // String Literals for I/O and User Experience
    const char *PROMPT_STORMNUMBER = "\nPlease enter the number of the storm (1-%i):  ";
    const char *PROMPT_WINDSPEED = "Please enter a minimum windspeed:  ";
    const char *VALIDATION_STORMNUMBER = "\nInvalid Entry:  Please enter a number between 1 and %i!\n";
    const char *DISPLAY_HIGHEST = "\nStorm with Highest Windspeed:";
    const char *DISPLAY_SHORTEST = "\nStorm with Shortest Duration:";
    const char *DISPLAY_AVERAGE = "\nAverage storm duration is:  %.2lf days\n";
    const char *DISPLAY_SEARCH_SUCCESS = "\nSearch Result:  %i storms with a minimum windspeed of %iMPH\n";
    const char *DISPLAY_SEARCH_FAILURE = "\nSearch Result: No Matches for storms with a minimum windspeed of %iMPH\n";

    // Variable Declaration/Initialization
    int startDates[NUM_STORMS] = {2020137, 2020148, 2020153, 2020174, 2020186, 
                                2020191, 2020203, 2020205, 2020212, 2020213, 
                                2020224, 2020227, 2020233, 2020233, 2020245, 
                                2020244, 2020251, 2020251, 2020255, 2020256, 
                                2020258, 2020262, 2020262, 2020261};
    int endDates[NUM_STORMS] = {2020140, 2020149, 2020161, 2020176, 2020188, 
                                2020193, 2020207, 2020209, 2020218, 2020214, 
                                2020229, 2020229, 2020241, 2020238, 2020248, 
                                2020249, 2020266, 2020258, 2020261, 2020266, 
                                2020261, 2020264, 2020262, 2020266};
    int windspeeds[NUM_STORMS] = {60, 50, 60, 45, 45, 
                                60, 65, 90, 85, 35, 
                                45, 50, 150, 75, 75, 
                                40, 105, 50, 105, 140, 
                                50, 40, 50, 60};
    int stormDurations[NUM_STORMS] = {0};
    char stormCategories[NUM_STORMS] = {' '};

    int sentinel = -1;
    int highest = 0;
    int shortest = 0;
    int stormNumber = 0;
    int searchIndex = 0;
    int searchValue = 0;
    int matchCounter = 0;
    double average = 0.0;
    bool searchFound = false;

    // Populate Categorization and Duration Arrays
    // Iterate across arrays
    for (int i = 0; i < NUM_STORMS; i++) {
        // Set storm durations by calculating difference in dates
        stormDurations[i] = calculateDifference(endDates[i], startDates[i]);
        // Set storm categories by calling the function to do so
        stormCategories[i] = categorizeStorm(windspeeds[i]);
    }
    // Display Welcome Message (Function)
    displayWelcome();
    // Do-While sentinel is not equal to 0.
    do {
        // Set sentinel to return from getOption.
        sentinel = getOption();
        // Switch from sentinel
        switch (sentinel) {
            // Exit case
            case 0:
                break;
            // Display all storms case
            case 1:
                // Iterate over storm array
                for (int i = 0; i < NUM_STORMS; i++) {
                    // Display storm at each index
                    displayStorm(i, stormCategories[i], startDates[i], endDates[i], stormDurations[i], windspeeds[i]);
                }
                break;
            // Display requested storm case
            case 2:
                // While input is invalid
                while (stormNumber <= 0 || stormNumber > NUM_STORMS) {
                    // Prompt for storm number, store as stormNumber
                    printf(PROMPT_STORMNUMBER, NUM_STORMS);
                    scanf("%i", &stormNumber);
                    // Convert user number to index (-1)
                    searchIndex = stormNumber - 1;
                    // If invalid - print validation message
                    if (stormNumber <= 0 || stormNumber > NUM_STORMS) {
                        printf(VALIDATION_STORMNUMBER, NUM_STORMS);
                    }
                    // Otherwise - display storm
                    else {
                        displayStorm(searchIndex, stormCategories[searchIndex], startDates[searchIndex], endDates[searchIndex], stormDurations[searchIndex], windspeeds[searchIndex]);
                    }
                }
                // Reset storm number - Persistent (so reentering 2 from options immediately meets condition to exit loop otherwise)
                stormNumber = 0;
                break;
            // Display highest windspeed case
            case 3:
                printf(DISPLAY_HIGHEST);
                highest = findHighest(windspeeds, NUM_STORMS);
                displayStorm(highest, stormCategories[highest], startDates[highest], endDates[highest], stormDurations[highest], windspeeds[highest]);
                break;
            // Display shortest duration case
            case 4:
                printf(DISPLAY_SHORTEST);
                shortest = findLowest(stormDurations, NUM_STORMS);
                displayStorm(shortest, stormCategories[shortest], startDates[shortest], endDates[shortest], stormDurations[shortest], windspeeds[shortest]);
                break;
            // Display average windspeed case
            case 5:
                average = calculateAverage(stormDurations, NUM_STORMS);
                printf(DISPLAY_AVERAGE, average);
                break;
            // Display matching over windspeed value case
            case 6:
                // Reset search counter and flag
                matchCounter = 0;
                searchFound = false;
                // Prompt user for windspeed value and store as searchValue
                printf(PROMPT_WINDSPEED);
                scanf("%i", &searchValue);
                // Iterate over ther windspeed array
                for (int i = 0; i < NUM_STORMS; i++) {
                    // if windspeed is greater (or equal to) searchValue
                    if (windspeeds[i] >= searchValue) {
                        // Display storm - Increment search counter - Flag search found
                        displayStorm(i, stormCategories[i], startDates[i], endDates[i], stormDurations[i], windspeeds[i]);
                        matchCounter++;
                        searchFound = true;
                    }
                }
                // If flag - display search success message with count
                if (searchFound == true) {
                    printf(DISPLAY_SEARCH_SUCCESS, matchCounter, searchValue);
                }
                // If flag false - display search failure message
                else if (searchFound == false) {
                    printf(DISPLAY_SEARCH_FAILURE, searchValue);
                }
                break;
            default:
                break;
        }
    } while (sentinel != 0);

    // Display credits (function)
    displayCredits();

    // Return from main - success
    return 0;
}

/* displayWelcome - displays welcome message
 * parameters:  None
 * return:  None
 */
void displayWelcome(void) {
    // String Literals for I/O and User Experience
    const char *DISPLAY_WELCOME = "Welcome to the Atlantic Hurricane Information Center by Jason Gardner\n";

    //  Display the welcome message
    printf(DISPLAY_WELCOME);
}

/* displayCredits - displays credits message
 * parameters:  None
 * return:  None
 */
void displayCredits(void) {
    // String Literals for I/O and User Experience
    const char *DISPLAY_CREDITS = "Results provided by Jason Gardner";

    // Display the credits message
    printf(DISPLAY_CREDITS);
}

/* displayStorm - displays storm information
 * parameters:  int stormNumber, int category, int start, int end, int duration, int windspeed
 * return:  None
 */
void displayStorm(int stormNumber, char category, int start, int end, int duration, int windspeed) {
    // Display the storm information
    printf("\nStorm #%i\nStart Date:\t%i\nEnd Date:\t%i\nDuration:\t%i days\nMaximum Sustained Windspeed:  %iMPH (",stormNumber + 1, start, end, duration, windspeed);
    // Switch for storm category - Cases convert to a string
    switch (category) {
        case 'd':
            printf("Tropical Depression)\n");
            break;
        case 's':
            printf("Tropical Storm)\n");
            break;
        case '1':
            printf("Category 1 Hurricane)\n");
            break;
        case '2':
            printf("Category 2 Hurricane)\n");
            break;
        case '3':
            printf("Category 3 Hurricane)\n");
            break;
        case '4':
            printf("Category 4 Hurricane)\n");
            break;
        case '5':
            printf("Category 5 Hurricane)\n");
            break;
        default:
            break;
    }
}

/* getOption - Gets option from user for what action to perform in main
 * parameters:  None
 * return:  int input
 */
int getOption(void) {
    // String Literals for I/O and User Experience
    const char *OPTION_ALL = "Display Information for Storm(s) [All]\n";
    const char *OPTION_BYINDEX = "Display Information for Storm [by Storm Number]\n";
    const char *OPTION_HIGHEST = "Display Information for Storm [Highest Windspeed]\n";
    const char *OPTION_DURATION = "Display Information for Storm [Shortest Duration]\n";
    const char *OPTION_AVERAGE = "Display Average Storm Duration\n";
    const char *OPTION_BYMINIMUM = "Display Information for Storm(s) [by Minimum Windspeed]\n";
    const char *EXIT_PROGRAM = "Exit the Program\n";
    const char *PROMPT_INPUT = "Please Enter an Option [0-%d]:  ";

    // Variable Declaration/Initialization
    int numOptions = 6;
    int input = -1;

    // While input is invalid (outside number of options)
    while (input < 0 || input > numOptions) {
        // Display the program option prompt to user and take input
        printf("\n1) %s2) %s3) %s4) %s5) %s6) %s0) %s\n",
                OPTION_ALL,
                OPTION_BYINDEX,
                OPTION_HIGHEST,
                OPTION_DURATION,
                OPTION_AVERAGE,
                OPTION_BYMINIMUM,
                EXIT_PROGRAM);
        printf(PROMPT_INPUT, numOptions);
        scanf("%d", &input);
    }
    return input;
}

/* findHighest - find and return index of largest value int in an int array
 * parameters:  int *numbers, int arraySize
 * return:  int highest
 */
int findHighest(int *numbers, int arraySize) {
    // Variable Declaration/Initialization
    int highest = 0;
    for (int i = 1; i < arraySize; i++) {
        // highest = the index of the highest between the current value or the array position value
        highest = *(numbers + i) > *(numbers + highest) ? i: highest;
    }
    return highest;
}

/* findLowest - find and return index of lowest value int in an int array
 * parameters:  int *numbers, int arraySize
 * return:  int lowest
 */
int findLowest(int *numbers, int arraySize) {
    // Variable Declaration/Initialization
    int lowest = 0;
    for (int i = 1; i < arraySize; i++) {
        // lowest = the index of the lowest between the current lowest or the array position value
        lowest = *(numbers + i) < *(numbers + lowest) ? i: lowest;
    }
    return lowest;
}

/* calculateAverage - calculate and return the average value from an int array
 * parameters:  int *numbers, int size
 * return:  double average
 */
double calculateAverage(int *numbers, int arraySize) {
    // Variable Declaration/Initialization
    double total = 0.0;
    double average = 0.0;

    // Iterate across array
    for (int i = 0; i < arraySize; i++) {
        // Accumulate total of values
        total += *(numbers + i);
    }
    average = total / arraySize;
    return average;
}

/* Function Removed - Linear Search, Previous Version of Assignment
int findValue(int value, int *numbers, int arraySize) {
    // Variable Declaration/Initialization
    int foundIndex = -1;
    for (int i = 0; i < arraySize; i++) {
        if (value == *(numbers + i)) {
            foundIndex = i;
        }
    }
    return foundIndex;
}
*/

/* calculateDifference - difference between two int (firstNumber - secondNumber)
 * parameters:  int firstNumber, int secondNumber
 * return:  int difference
 */
int calculateDifference(int firstNumber, int secondNumber) {
    // Variable Declaration/Initialization
    int difference = 0;

    // Subtract numbers (first-last)
    difference = firstNumber - secondNumber;

    // Return difference to caller
    return difference;
}

/* categorizeStorm - return a char representing storm category based on Saffir-Simpson minimum windspeeds
 * parameters:  int windspeed
 * return:  char category
 */
char categorizeStorm(int windspeed) {
    // Variable Declaration/Initialization
    char category = ' ';

    // Set category to a char representing storm category
    if (windspeed >= 157) {
        category = '5';
    } 
    else if (windspeed >= 130) {
        category = '4';
    } 
    else if (windspeed >= 111) {
        category = '3';
    } 
    else if (windspeed >= 96) {
        category = '2';
    } 
    else if (windspeed >= 74) {
        category = '1';
    } 
    else if (windspeed >= 39) {
        category = 's';
    } 
    else if (windspeed >= 0) {
        category = 'd';
    }

    // return category to caller
    return category;
}


/* Test Data and Expected Results:
 * Option: 1
 * Expected: Storm 1-24 Data
 * 
 * Option: 2, 2 (TEST FLOW CONTROL WITH: 0, 25)
 * Expected: Storm #2 (2020148, 2020149, 1, 50, Tropical Storm)
 * 
 * Option: 3
 * Expected: Storm #13 (2020233, 2020241, 8, 150, Category 4 Hurricane)
 * 
 * Option: 4
 * Expected:  Storm #23 (2020262, 2020262, 0, 50, Tropical Storm)
 * 
 * Option: 5
 * Expected:  4.54 days
 * 
 * Option: 6, 100
 * Expected: Storms #13, #17, #19, #20
 */

/* Output
Welcome to the Atlantic Hurricane Information Center by Jason Gardner

1) Display Information for Storm(s) [All]
2) Display Information for Storm [by Storm Number]        
3) Display Information for Storm [Highest Windspeed]      
4) Display Information for Storm [Shortest Duration]      
5) Display Average Storm Duration
6) Display Information for Storm(s) [by Minimum Windspeed]
0) Exit the Program

Please Enter an Option [0-6]:  1

Storm #1
Start Date:     2020137
End Date:       2020140
Duration:       3 days
Maximum Sustained Windspeed:  60MPH (Tropical Storm)

Storm #2
Start Date:     2020148
End Date:       2020149
Duration:       1 days
Maximum Sustained Windspeed:  50MPH (Tropical Storm)

Storm #3
Start Date:     2020153
End Date:       2020161
Duration:       8 days
Maximum Sustained Windspeed:  60MPH (Tropical Storm)

Storm #4
Start Date:     2020174
End Date:       2020176
Duration:       2 days
Maximum Sustained Windspeed:  45MPH (Tropical Storm)

Storm #5
Start Date:     2020186
End Date:       2020188
Duration:       2 days
Maximum Sustained Windspeed:  45MPH (Tropical Storm)

Storm #6
Start Date:     2020191
End Date:       2020193
Duration:       2 days
Maximum Sustained Windspeed:  60MPH (Tropical Storm)

Storm #7
Start Date:     2020203
End Date:       2020207
Duration:       4 days
Maximum Sustained Windspeed:  65MPH (Tropical Storm)

Storm #8
Start Date:     2020205
End Date:       2020209
Duration:       4 days
Maximum Sustained Windspeed:  90MPH (Category 1 Hurricane)

Storm #9
Start Date:     2020212
End Date:       2020218
Duration:       6 days
Maximum Sustained Windspeed:  85MPH (Category 1 Hurricane)

Storm #10
Start Date:     2020213
End Date:       2020214
Duration:       1 days
Maximum Sustained Windspeed:  35MPH (Tropical Depression)

Storm #11
Start Date:     2020224
End Date:       2020229
Duration:       5 days
Maximum Sustained Windspeed:  45MPH (Tropical Storm)

Storm #12
Start Date:     2020227
End Date:       2020229
Duration:       2 days
Maximum Sustained Windspeed:  50MPH (Tropical Storm)

Storm #13
Start Date:     2020233
End Date:       2020241
Duration:       8 days
Maximum Sustained Windspeed:  150MPH (Category 4 Hurricane)

Storm #14
Start Date:     2020233
End Date:       2020238
Duration:       5 days
Maximum Sustained Windspeed:  75MPH (Category 1 Hurricane)

Storm #15
Start Date:     2020245
End Date:       2020248
Duration:       3 days
Maximum Sustained Windspeed:  75MPH (Category 1 Hurricane)

Storm #16
Start Date:     2020244
End Date:       2020249
Duration:       5 days
Maximum Sustained Windspeed:  40MPH (Tropical Storm)

Storm #17
Start Date:     2020251
End Date:       2020266
Duration:       15 days
Maximum Sustained Windspeed:  105MPH (Category 2 Hurricane)

Storm #18
Start Date:     2020251
End Date:       2020258
Duration:       7 days
Maximum Sustained Windspeed:  50MPH (Tropical Storm)

Storm #19
Start Date:     2020255
End Date:       2020261
Duration:       6 days
Maximum Sustained Windspeed:  105MPH (Category 2 Hurricane)

Storm #20
Start Date:     2020256
End Date:       2020266
Duration:       10 days
Maximum Sustained Windspeed:  140MPH (Category 4 Hurricane)

Storm #21
Start Date:     2020258
End Date:       2020261
Duration:       3 days
Maximum Sustained Windspeed:  50MPH (Tropical Storm)

Storm #22
Start Date:     2020262
End Date:       2020264
Duration:       2 days
Maximum Sustained Windspeed:  40MPH (Tropical Storm)

Storm #23
Start Date:     2020262
End Date:       2020262
Duration:       0 days
Maximum Sustained Windspeed:  50MPH (Tropical Storm)

Storm #24
Start Date:     2020261
End Date:       2020266
Duration:       5 days
Maximum Sustained Windspeed:  60MPH (Tropical Storm)

1) Display Information for Storm(s) [All]
2) Display Information for Storm [by Storm Number]
3) Display Information for Storm [Highest Windspeed]
4) Display Information for Storm [Shortest Duration]
5) Display Average Storm Duration
6) Display Information for Storm(s) [by Minimum Windspeed]
0) Exit the Program

Please Enter an Option [0-6]:  2

Please enter the number of the storm (1-24):  0

Invalid Entry:  Please enter a number between 1 and 24!

Please enter the number of the storm (1-24):  25

Invalid Entry:  Please enter a number between 1 and 24!

Please enter the number of the storm (1-24):  2

Storm #2
Start Date:     2020148
End Date:       2020149
Duration:       1 days
Maximum Sustained Windspeed:  50MPH (Tropical Storm)

1) Display Information for Storm(s) [All]
2) Display Information for Storm [by Storm Number]
3) Display Information for Storm [Highest Windspeed]
4) Display Information for Storm [Shortest Duration]
5) Display Average Storm Duration
6) Display Information for Storm(s) [by Minimum Windspeed]
0) Exit the Program

Please Enter an Option [0-6]:  3

Storm with Highest Windspeed:
Storm #13
Start Date:     2020233
End Date:       2020241
Duration:       8 days
Maximum Sustained Windspeed:  150MPH (Category 4 Hurricane)

1) Display Information for Storm(s) [All]
2) Display Information for Storm [by Storm Number]
3) Display Information for Storm [Highest Windspeed]
4) Display Information for Storm [Shortest Duration]
5) Display Average Storm Duration
6) Display Information for Storm(s) [by Minimum Windspeed]
0) Exit the Program

Please Enter an Option [0-6]:  4

Storm with Shortest Duration:
Storm #23
Start Date:     2020262
End Date:       2020262
Duration:       0 days
Maximum Sustained Windspeed:  50MPH (Tropical Storm)

1) Display Information for Storm(s) [All]
2) Display Information for Storm [by Storm Number]
3) Display Information for Storm [Highest Windspeed]
4) Display Information for Storm [Shortest Duration]
5) Display Average Storm Duration
6) Display Information for Storm(s) [by Minimum Windspeed]
0) Exit the Program

Please Enter an Option [0-6]:  5

Average storm duration is:  4.54 days

1) Display Information for Storm(s) [All]
2) Display Information for Storm [by Storm Number]
3) Display Information for Storm [Highest Windspeed]
4) Display Information for Storm [Shortest Duration]
5) Display Average Storm Duration
6) Display Information for Storm(s) [by Minimum Windspeed]
0) Exit the Program

Please Enter an Option [0-6]:  6
Please enter a minimum windspeed:  100

Storm #13
Start Date:     2020233
End Date:       2020241
Duration:       8 days
Maximum Sustained Windspeed:  150MPH (Category 4 Hurricane)

Storm #17
Start Date:     2020251
End Date:       2020266
Duration:       15 days
Maximum Sustained Windspeed:  105MPH (Category 2 Hurricane)

Storm #19
Start Date:     2020255
End Date:       2020261
Duration:       6 days
Maximum Sustained Windspeed:  105MPH (Category 2 Hurricane)

Storm #20
Start Date:     2020256
End Date:       2020266
Duration:       10 days
Maximum Sustained Windspeed:  140MPH (Category 4 Hurricane)

Search Result:  4 storms with a minimum windspeed of 100MPH

1) Display Information for Storm(s) [All]
2) Display Information for Storm [by Storm Number]
3) Display Information for Storm [Highest Windspeed]
4) Display Information for Storm [Shortest Duration]
5) Display Average Storm Duration
6) Display Information for Storm(s) [by Minimum Windspeed]
0) Exit the Program

Please Enter an Option [0-6]:  0
Results provided by Jason Gardner
 */