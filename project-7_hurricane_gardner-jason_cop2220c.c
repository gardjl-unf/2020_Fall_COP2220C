/* COP2220C 02DEC2020
 * Author: Jason Gardner
 * Filename: project-7_hurricane_gardner-jason_cop2220c.c
 * Purpose: Manage/Parse/Display Hurricane Data
 * Objectives: Input, calculations, decisions, loops, functions, arrays, strings, files, structures, and output
 * 
 * Compile Command:  gcc .\project-7_hurricane_gardner-jason_cop2220c.c .\project-7_MAINT_gardner-jason_cop2220c.c -o .\project-7_hurricane_gardner-jason_cop2220c.exe
 */

//#define DEBUG

// Headers
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "project-7_MAINT_gardner-jason_cop2220c.h"

// Function Prototypes
void displayWelcome (void);
void displayCredits (void);
int loadRecords (storm_t storms[], int capacity);
void displayStorm (storm_t *s);
int getOption (void);
bool findString(const char *inputString, const char *compareString);
bool checkChar(char i, char j);
int compareDateTime(const void *a, const void *b);
int compareName(const void *a, const void *b);

/* main
 * Called at program start
 * 
 * @param void - none
 * @return int - program status
 */
int main(void) {
    // String Literals for I/O and User Experience
    const char *SEARCH_PROMPT = "\nPlease enter %s:  ";
    const char *ERROR_RECORDS = "\nInvalid Entry:  Valid Records Exist in Range of 1-%d\n";
    const char *ERROR_OOB = "\nNumber of Records Requested (%i) Exceeds Number of Available Records\nDisplaying All Records from %i-%i\n";
    const char *RESULT_NUM = "\nSearch Result:  %i results found for %i\n\n";
    const char *RESULT_STR = "\nSearch Result: %i results for for \"%s\"\n\n";

    // Variable Declaration/Initialization
    storm_t stormData[NUM_STORMS] = {0};
    storm_t *pStorm = stormData;
    int numEntries = 0;
    int numDisplay = 0;
    int option = -1;
    int findNum = 0;
    char findStr[NAME_LEN];
    int searchCount = 0;

    if ((numEntries = loadRecords(pStorm, NUM_STORMS)) == -1) {
        /* We already printed the error in the load function, short circuit program here.
         * If zero records loaded, that's fine, because we can add records now.
         */
    }
    else {
        // Call displayWelcome
        displayWelcome();

        // While option isn't 0/false
        while (option) {
            // Get option
            option = getOption();
            // Use option - decision (switch)
            switch(option) {
                case 0:
                // 0: Exit
                    break;
                case 1:
                // 1: Display entries from record number to final record
                    // Do (post-test) while record number is invalid
                    do {
                        // Prompt user for "record number"
                        printf(SEARCH_PROMPT, "record number");
                        // Get (user input) and store that integer in findNum
                        scanf("%i", &findNum);
                        // Flush input buffer (bug prevention)
                        fflush(stdin);
                        // If record number is outside number of records
                        if (findNum < 1 || findNum > numEntries) {
                            // Display error message
                            printf(ERROR_RECORDS, numEntries);
                        }
                    } while (findNum  < 1 || findNum > numEntries);
                    // Prompt user for "number of records"
                    printf(SEARCH_PROMPT, "number of records");
                    scanf("%i", &numDisplay);
                    fflush(stdin);
                    if ((findNum + numDisplay) > numEntries) {
                        printf(ERROR_OOB, numDisplay, findNum, numEntries);
                        numDisplay = numEntries - findNum + 1;
                    }
                    // Print a blank line
                    printf("\n");
                    /* Set storm pointer to the base address of our array(stormData)
                    * Offset that by (findNum -1)
                    */
                    pStorm = stormData + (findNum - 1);

                    /* From that offset number, to the  numEntries-1
                    * Increment index, and the storm pointer
                    */
                    for (int i = 0; i < numDisplay; i++, pStorm++) {
                        // Call displayStorm for pStorm
                        displayStorm(pStorm);                    
                    }
                    // Print a blank line
                    printf("\n");
                    break;
                case 2:
                // 2: Display entries by date (with count)
                    // Prompt user for "date [MMDD]"
                    printf(SEARCH_PROMPT, "date [MMDD]");
                    // Get (user input) and store that integer in findNum
                    scanf("%i", &findNum);
                    // Flush input buffer (bug prevention)
                    fflush(stdin);
                    // Print a blank line
                    printf("\n");
                    // Set storm pointer to base address of array
                    pStorm = stormData;
                    // Set our counter to 0
                    searchCount = 0;
                    // From 0 to numEntries-1, increment index and storm pointer
                    for (int i = 0; i < numEntries; i++, pStorm++) {
                        // If the date matches our search
                        if ((pStorm->date - REMOVE_YEAR) == findNum) {
                            // Call displayStorm for pStorm
                            displayStorm(pStorm);
                            // Increment counter
                            searchCount++;
                        }                    
                    }
                    // Display count of search result
                    printf(RESULT_NUM, searchCount, findNum);
                    break;
                case 3:
                // 3: Display entries by name [exact] (with count)
                    // Prompt user for "name [exact]"
                    printf(SEARCH_PROMPT, "name [exact]");
                    // Get (user input) and store that string to findStr
                    scanf("%24s", findStr);
                    // Flush input buffer (bug prevention)
                    fflush(stdin);
                    // Print a blank line
                    printf("\n");
                    // Set storm pointer to base of array
                    pStorm = stormData;
                    // Set count to 0
                    searchCount = 0;
                    // From 0 to numEntries-1, increment index and storm pointer
                    for (int i = 0; i < numEntries; i++, pStorm++) {
                        /* Check if search string and storm name are the same length AND
                        * check if the strings match
                        */
                        if ((strlen(pStorm->stormName) == strlen(findStr)) && (findString(pStorm->stormName, findStr))) {
                            // Call displayStorm for pStorm
                            displayStorm(pStorm);
                            // Increment counter
                            searchCount++;
                        }                    
                    }
                    // Display count of search result
                    printf(RESULT_STR, searchCount, findStr);
                    break;
                case 4:
                // 4: Display entries by name [partial] (with count)
                    // Prompt user for "name [partial]"
                    printf(SEARCH_PROMPT, "name [partial]");
                    // Get (user input) and store that string to findStr
                    scanf("%24s", findStr);
                    // Flush input buffer (bug prevention)
                    fflush(stdin);
                    // Print a blank line
                    printf("\n");
                    // Set storm pointer to base of array
                    pStorm = stormData;
                    // Set counter to 0
                    searchCount = 0;
                    // From 0 to numEntries-1, increment index and storm pointer
                    for (int i = 0; i < numEntries; i++, pStorm++) {
                        // If the substring matches the string
                        if (findString(pStorm->stormName, findStr)) {
                            // Call displayStorm for pStorm
                            displayStorm(pStorm);
                            // Increment counter
                            searchCount++;
                        }                    
                    }
                    // Display count of search result
                    printf(RESULT_STR, searchCount, findStr);
                    break;
                case 5:
                // 5: Display entries by windspeed [minimum] (with count)
                    // Prompt user for "windspeed [minimum]"
                    printf(SEARCH_PROMPT, "windspeed [minimum]");
                    // Get (user input) and store that integer to findNum
                    scanf("%i", &findNum);
                    // Flush input buffer (bug prevention)
                    fflush(stdin);
                    // Print a blank line
                    printf("\n");
                    // Set storm pointer to base of array
                    pStorm = stormData;
                    // Set counter to 0
                    searchCount = 0;
                    // From 0 to numEntries-1, increment index and storm pointer
                    for (int i = 0; i < numEntries; i++, pStorm++) {
                        // If windspeed is greater than or equal to that number
                        if (pStorm->windspeed >= findNum) {
                            // Call displayStorm for pStorm
                            displayStorm(pStorm);
                            // Increment counter
                            searchCount++;
                        }                    
                    }
                    // Display count of search result
                    printf(RESULT_NUM, searchCount, findNum);
                    break;
                case 6:
                // 6: Display entries by pressure [maximum] (with count)
                    // Prompt the user for "pressure [maximum]"
                    printf(SEARCH_PROMPT, "pressure [maximum]");
                    // Get (user input) and store that integer to findNum
                    scanf("%i", &findNum);
                    // Flush input buffer (bug prevention)
                    fflush(stdin);
                    // Print a blank line
                    printf("\n");
                    // Set storm pointer to base of array
                    pStorm = stormData;
                    // Set counter to 0
                    searchCount = 0;
                    // From 0 to numEntries-1, increment index and storm pointer
                    for (int i = 0; i < numEntries; i++, pStorm++) {
                        // If pressure is less than or equal to that number
                        if (pStorm->pressure <= findNum) {
                            // Call displayStorm for pStorm
                            displayStorm(pStorm);
                            // Increment counter
                            searchCount++;
                        }                    
                    }
                    // Display count of search result
                    printf(RESULT_NUM, searchCount, findNum);
                    break;
                case 7:
                // 7: Sort items by date
                    qsort(stormData, numEntries, sizeof(storm_t), compareDateTime);
                    break;
                case 8:
                // 8: Sort items by storm name
                    qsort(stormData, numEntries, sizeof(storm_t), compareName);
                    break;
                case 9:
                // 9: Maintenence menu
                    numEntries = maintenance(pStorm, numEntries);
                    break;
                default:
                // default:  none
                    break;
            
            }
        }
    }

    // Call displayCredits
    displayCredits();

    // Return 0 (success)
    return 0;
}

/* loadRecords
 * load records from text document, enter those records into the storm array
 * 
 * @param storm_t storms[] - array of storm_t structures
 * @param int capacity - capacity of that array (there is a define related to this, but, specifications)
 * @return int - number of storms entered into array
 */
int loadRecords (storm_t storms[], int capacity) {
    // String Literals for I/O and User Experience
    const char *FILE_OPEN_ERROR = "Error:  Could not open file \"%s\"";
    const char *FILENAME = "StormsAL2019.txt";

    // Variable Declaration/Initialization
    storm_t *s = storms;
    int numEntries = 0;
    char readLine[LINE_LEN];

    // Open file
    FILE *inputFile = fopen(FILENAME, "r");
    // If file fails to open
    if (!inputFile){
        // Display error message
        printf(FILE_OPEN_ERROR, FILENAME);
    }
    else {    
        /* While the string read fromt the file exists, and we haven't exceeded the size
        * of our storm array
        */
        while (fgets(readLine, sizeof(readLine), inputFile) && numEntries <= capacity) {
            strcpy(s->stormName, strtok(readLine, DELIMITER));
            s->date = atoi(strtok(NULL, DELIMITER));
            s->time = atoi(strtok(NULL, DELIMITER));
            s->latitude = atof(strtok(NULL, DELIMITER));
            s->longitude = atof(strtok(NULL, DELIMITER));
            s->windspeed = atoi(strtok(NULL, DELIMITER));
            s->pressure = atoi(strtok(NULL, END_DELIMITER));

            // Increment number of entries
            numEntries++;

            #ifdef DEBUG
            printf("Storm Data (#%d) Loaded:\n", numEntries);
            displayStorm(s);
            #endif

            // Increment storm pointer to next storm.
            s++;

            #ifdef DEBUG
            printf("Number of Entries Loaded:  %d\n", numEntries);
            #endif
        }
    }
    // Close inputFile
    fclose(inputFile);

    // Return numEntries to caller
    return numEntries;
}

/* displayWelcome
 * Display welcome message
 * 
 * @param void - none
 * @return void - none
 */
void displayWelcome(void) {
    // String Literals for I/O and User Experience
    const char *DISPLAY_WELCOME = "Welcome to the 2019 Atlantic Basin Information Center by Jason Gardner\n\n";

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

/* getOption
 * Display menu and get menu option from user for return
 * @param void - none
 * @return int - user option input
 */
int getOption(void) {
    // String Literals for I/O and User Experience
    const char OPTIONS[][LINE_LEN] = {"Display Information for Storm(s) [from Entry #]\n",
                            "Display Information for Storm(s) [by Date]\n",
                            "Display Information for Storm(s) [by Name (Exact)]\n",
                            "Display Information for Storm(s) [by Name (Partial)]\n",
                            "Display Information for Storm(s) [by Windspeed (Minimum)]\n",
                            "Display Information for Storm(s) [by Pressure (Maximum)]\n",
                            "Sort Storm Data [by Date/Time]\n",
                            "Sort Storm Data [by Storm Name]\n",
                            "Maintain Data\n"
                            };
    const char *PRINT_OPTIONS = "\t%d) %s";
    const char *EXIT_PROGRAM = "\t0) Exit the Program\n";
    const char *PROMPT_INPUT = "Please Enter an Option [0-%d]:  ";
    const char *INPUT_ERROR = "\nInvalid Entry:  Please Enter a Number Between 0 and %d\n\n";

    // Variable Declaration/Initialization
    /* This is also used to reference the maintenance menu options (this variable name).
     * I was trying to keep this variable near the menu so adding/removing items
     * involves changing the strings above, and then making this match.
     */
    const int NUM_OPTIONS = 9;
    int input = -1;

    // While input is invalid (outside number of options)
    while (input < 0 || input > NUM_OPTIONS) {
        // Display the program option prompt to user
        for (int i = 0; i < NUM_OPTIONS; i++) {
            printf(PRINT_OPTIONS, i + 1, OPTIONS[i]);
        }
        printf("%s", EXIT_PROGRAM);
        printf(PROMPT_INPUT, NUM_OPTIONS);

        // Get user input
        scanf("%d", &input);
        // Flush input buffer (bug prevention)
        fflush(stdin);
        // If input isn't in valid range, display error
        //Project 6 Feedback:  "input= -1"
        if (input < 0 || input > NUM_OPTIONS) {
            printf(INPUT_ERROR, NUM_OPTIONS);
        }
    }
    // Return input to caller
    return input;
}

/* displayStorm
 * Output individual storm data to console
 * 
 * @param storm_t *s - pointer to individual storm data
 * @return void - none
 */
void displayStorm (storm_t *s) {
    // String Literals for I/O and User Experience
    const char *OUTPUT_FORMAT = "Storm Name: %s\tDate: %i\tTime: %04i\n\tLatitude: %.2lf\t\tLongitude: %.2lf\n\tWindspeed: %iMPH\tPressure: %imb\n";

    // Print out the storm data
    printf(OUTPUT_FORMAT, s->stormName, s->date, s->time, s->latitude, s->longitude, s->windspeed, s->pressure);
}

/* findString
 * Check that strings match
 * 
 * @param const char *inputString - String input by user
 * @param const char *compareString - String comparing to (storm name)
 * @return bool - if strings match
 */
bool findString(const char *inputString, const char *compareString) {
    // Variable Declaration/Initialization
    // Project 6 Feedback: "(int)" I didn't understand this.  strlen returns an unsigned integer (size_t)
    int i = strlen(compareString) - 1;
    bool matched = true;

    // While the characters are the same counting down to 0 (will run 0th time)
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

/* compareDateTime
 * qsort compare function for two integers
 * 
 * @param const void *x - pointer to first
 * @param const void *y - pointer to second
 * @return int - return integer to qsort for sorting
 */
int compareDateTime(const void *x, const void *y) {
    /* Looks complicated, forcing order of operations,
     * but just casting the void pointer to a storm so we can
     * access the parameters.  Pulling out the year.  Adding the 
     * time in, because we're sorting by date AND time.
     * 
     * Just returns an integer of the format MMDDHHMM for sorting
     */
    return (((((((storm_t *)x)->date) - REMOVE_YEAR) * 10000) + ((storm_t *)x)->time) - ((((((storm_t *)y)->date) - REMOVE_YEAR) * 10000) + ((storm_t *)y)->time));
}

/* compareName
 * qsort compare function for two strings
 * 
 * @param const void *x - pointer to first
 * @param const void *y - pointer to second
 * @return int - return integer to qsort for sorting
 */
int compareName(const void *x, const void *y) {
    /* Looks complicated, forcing order of operations,
     * but just casting the void pointer to a storm so we can
     * access the parameters.
     */
    return (strcmp(((storm_t *)x)->stormName, ((storm_t *)y)->stormName ));
}

/* Test Data and Expected Results - They're formatted differently here - Expected Data Pulled from Input File

Main Menu: 1
Record Number: 1
Number of Records: 1

Expected Record(s) (1):
ANDREA|20190520|1800|28.10|-68.60|35|1008

Main Menu: 1
Record Number: 490
Number of records: 10

Expected Records (4):
SEBASTIEN|20191126|1800|52.20|-8.90|40|972
SEBASTIEN|20191127|0|51.80|-8.20|40|974
SEBASTIEN|20191127|600|51.40|-6.00|40|976
SEBASTIEN|20191127|1200|51.30|-2.10|40|980

Main Menu: 2
Date: 1127

Expected Records (3):
SEBASTIEN|20191127|0|51.80|-8.20|40|974
SEBASTIEN|20191127|600|51.40|-6.00|40|976
SEBASTIEN|20191127|1200|51.30|-2.10|40|980

Main Menu: 3
Name: seb

Expected Records:
None

Main Menu: 3
Name: sebastien

Expected Records (34):
SEBASTIEN|20191119|600|19.40|-58.10|35|1006
SEBASTIEN|20191119|1200|19.90|-58.50|40|1004
SEBASTIEN|20191119|1800|20.30|-59.40|40|1004
SEBASTIEN|20191120|0|20.40|-60.30|40|1002
SEBASTIEN|20191120|600|20.50|-61.00|45|1000
...

SEBASTIEN|20191126|1200|52.20|-9.30|45|970
SEBASTIEN|20191126|1800|52.20|-8.90|40|972
SEBASTIEN|20191127|0|51.80|-8.20|40|974
SEBASTIEN|20191127|600|51.40|-6.00|40|976
SEBASTIEN|20191127|1200|51.30|-2.10|40|980

Main Menu: 4
Name: seb

Expected Records (34):
SEBASTIEN|20191119|600|19.40|-58.10|35|1006
SEBASTIEN|20191119|1200|19.90|-58.50|40|1004
SEBASTIEN|20191119|1800|20.30|-59.40|40|1004
SEBASTIEN|20191120|0|20.40|-60.30|40|1002
SEBASTIEN|20191120|600|20.50|-61.00|45|1000
...
SEBASTIEN|20191126|1200|52.20|-9.30|45|970
SEBASTIEN|20191126|1800|52.20|-8.90|40|972
SEBASTIEN|20191127|0|51.80|-8.20|40|974
SEBASTIEN|20191127|600|51.40|-6.00|40|976
SEBASTIEN|20191127|1200|51.30|-2.10|40|980

Main Menu: 4
Name: Bobbert

Expected Records:
None

Main Menu: 5
Windspeed: 155

Expected Records (5):
DORIAN|20190901|1200|26.50|-76.50|155|927
DORIAN|20190901|1640|26.50|-77.00|160|910
DORIAN|20190901|1800|26.50|-77.10|160|910
DORIAN|20190902|0|26.60|-77.70|155|914
DORIAN|20190902|215|26.60|-77.80|155|914

Main Menu: 6
Pressure: 910

Expected Records (2):
DORIAN|20190901|1640|26.50|-77.00|160|910
DORIAN|20190901|1800|26.50|-77.10|160|910

Main Menu: 7
Main Menu: 9
Maintenance Menu: 4
Filename: byDate

Expected Output:
byDate.txt contains storms sorted by date

Maintenence Menu: 0

Main Menu: 7
Main Menu: 9
Maintenance Menu: 4
Filename: byName

Expected Output:
byName.txt contains storms sorted by name

Maintenance Menu: 1
Entered Data:
Bobbert|1213|0625|20.2|-9.2|120|1010
Test cases for invalid data here:
Date > 1231
Time > 2359
-180 > Longitude > 180
-90 > Latitude > 90

Maintenence Menu: 2
Storm Number: 493
Entered Data:
Bobbert|1212|0001|19.2|-2.1|115|1000

Maintenence Menu: 3
Storm Number: 492

Maintenence Menu: 4
Filename: modifiedStorms

Expected Output:
modifiedStorms.txt contains storms with final three records (to line 493)
SEBASTIEN|20191127|0|51.80|-8.20|40|974
BOBBERT|1212|0001|19.2|-2.1|115|1000
BOBBERT|1213|0625|20.2|-9.2|120|1010

Testing the edge case for maintance menu option 1 is done with a seperate compile with
NUM_STORMS set to 493 to make sure an entry can't exceed the array size.
Ideally, would have written a DEBUG statement that allows
a different fileName to be entered for debugging purposes (for the initial load).
However, as the program should be tested as a non-debug build, that's impractical as well.
This was tested, and displays the expected error/warning to the user.

For reference, extending out the maintenance menu to reload the initial file (or load another),
could be practically done for the debug build by defining the menu in #ifndef DEBUG and #ifdef DEBUG

Previous feedback, testing more than one storm name in partial match, the storms in this year didn't loop, so unless
I misunderstood the partial match and messed it up a few times in a row (where it matches inside the word), I
would need to add a value here and view values to test it specifically.  Sebastien was used to verify that I was
searching out to the edge of the array without under/over counting.

Very unsure why my previous version of this converted a value to octal during search.

While I tried to sanitize/sanity-check user data, user can still mess things up.  I've been trying to make
sense of when this happens (and why the program acts so unexpectedly when it does).  My initial LARGE errors, that
were solved by flushing the input buffers, came from testing a character when an integer was expected.  I expected it would
view the character as it's integer representation.  Instead, the logic of the entire program broke and looped infinitely
while skipping that input.

*/

/* Test Data
PS C:\Users\Jason\OneDrive - Florida State College at Jacksonville\2020 3(Fall) FSCJ\COP2220C-1433\workspace\project_7> gcc .\project-7_hurricane_gardner-jason_cop2220c.c .\project-7_MAINT_gardner-jason_cop2220c.c -o .\project-7_hurricane_gardner-jason_cop2220c.exe
PS C:\Users\Jason\OneDrive - Florida State College at Jacksonville\2020 3(Fall) FSCJ\COP2220C-1433\workspace\project_7> .\project-7_hurricane_gardner-jason_cop2220c.exe
Welcome to the 2019 Atlantic Basin Information Center by Jason Gardner

        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]       
        4) Display Information for Storm(s) [by Name (Partial)]     
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)] 
        7) Sort Storm Data [by Date/Time]
        8) Sort Storm Data [by Storm Name]
        9) Maintain Data
        0) Exit the Program
Please Enter an Option [0-9]:  1

Please enter record number:  1

Please enter number of records:  1

Storm Name: ANDREA      Date: 20190520  Time: 1800
        Latitude: 28.10         Longitude: -68.60
        Windspeed: 35MPH        Pressure: 1008mb

        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        7) Sort Storm Data [by Date/Time]
        8) Sort Storm Data [by Storm Name]
        9) Maintain Data
        0) Exit the Program
Please Enter an Option [0-9]:  1

Please enter record number:  490

Please enter number of records:  10

Number of Records Requested (10) Exceeds Number of Available Records
Displaying All Records from 490-493

Storm Name: SEBASTIEN   Date: 20191126  Time: 1800
        Latitude: 52.20         Longitude: -8.90
        Windspeed: 40MPH        Pressure: 972mb
Storm Name: SEBASTIEN   Date: 20191127  Time: 0000
        Latitude: 51.80         Longitude: -8.20
        Windspeed: 40MPH        Pressure: 974mb
Storm Name: SEBASTIEN   Date: 20191127  Time: 0600
        Latitude: 51.40         Longitude: -6.00
        Windspeed: 40MPH        Pressure: 976mb
Storm Name: SEBASTIEN   Date: 20191127  Time: 1200
        Latitude: 51.30         Longitude: -2.10
        Windspeed: 40MPH        Pressure: 980mb

        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        7) Sort Storm Data [by Date/Time]
        8) Sort Storm Data [by Storm Name]
        9) Maintain Data
        0) Exit the Program
Please Enter an Option [0-9]:  2

Please enter date [MMDD]:  1127

Storm Name: SEBASTIEN   Date: 20191127  Time: 0000
        Latitude: 51.80         Longitude: -8.20
        Windspeed: 40MPH        Pressure: 974mb
Storm Name: SEBASTIEN   Date: 20191127  Time: 0600
        Latitude: 51.40         Longitude: -6.00
        Windspeed: 40MPH        Pressure: 976mb
Storm Name: SEBASTIEN   Date: 20191127  Time: 1200
        Latitude: 51.30         Longitude: -2.10
        Windspeed: 40MPH        Pressure: 980mb

Search Result:  3 results found for 1127

        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        7) Sort Storm Data [by Date/Time]
        8) Sort Storm Data [by Storm Name]
        9) Maintain Data
        0) Exit the Program
Please Enter an Option [0-9]:  3

Please enter name [exact]:  seb


Search Result: 0 results for for "seb"

        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        7) Sort Storm Data [by Date/Time]
        8) Sort Storm Data [by Storm Name]
        9) Maintain Data
        0) Exit the Program
Please Enter an Option [0-9]:  3

Please enter name [exact]:  sebastien

Storm Name: SEBASTIEN   Date: 20191119  Time: 0600
        Latitude: 19.40         Longitude: -58.10
        Windspeed: 35MPH        Pressure: 1006mb
Storm Name: SEBASTIEN   Date: 20191119  Time: 1200
        Latitude: 19.90         Longitude: -58.50
        Windspeed: 40MPH        Pressure: 1004mb
Storm Name: SEBASTIEN   Date: 20191119  Time: 1800
        Latitude: 20.30         Longitude: -59.40
        Windspeed: 40MPH        Pressure: 1004mb
Storm Name: SEBASTIEN   Date: 20191120  Time: 0000
        Latitude: 20.40         Longitude: -60.30
        Windspeed: 40MPH        Pressure: 1002mb
Storm Name: SEBASTIEN   Date: 20191120  Time: 0600
        Latitude: 20.50         Longitude: -61.00
        Windspeed: 45MPH        Pressure: 1000mb
Storm Name: SEBASTIEN   Date: 20191120  Time: 1200
        Latitude: 20.80         Longitude: -61.70
        Windspeed: 45MPH        Pressure: 999mb
Storm Name: SEBASTIEN   Date: 20191120  Time: 1800
        Latitude: 21.30         Longitude: -61.70
        Windspeed: 45MPH        Pressure: 999mb
Storm Name: SEBASTIEN   Date: 20191121  Time: 0000
        Latitude: 21.90         Longitude: -61.70
        Windspeed: 50MPH        Pressure: 996mb
Storm Name: SEBASTIEN   Date: 20191121  Time: 0600
        Latitude: 22.40         Longitude: -61.40
        Windspeed: 50MPH        Pressure: 996mb
Storm Name: SEBASTIEN   Date: 20191121  Time: 1200
        Latitude: 22.90         Longitude: -60.90
        Windspeed: 50MPH        Pressure: 996mb
Storm Name: SEBASTIEN   Date: 20191121  Time: 1800
        Latitude: 23.50         Longitude: -60.10
        Windspeed: 50MPH        Pressure: 996mb
Storm Name: SEBASTIEN   Date: 20191122  Time: 0000
        Latitude: 24.20         Longitude: -58.80
        Windspeed: 50MPH        Pressure: 996mb
Storm Name: SEBASTIEN   Date: 20191122  Time: 0600
        Latitude: 24.50         Longitude: -57.30
        Windspeed: 50MPH        Pressure: 996mb
Storm Name: SEBASTIEN   Date: 20191122  Time: 1200
        Latitude: 25.00         Longitude: -55.80
        Windspeed: 50MPH        Pressure: 996mb
Storm Name: SEBASTIEN   Date: 20191122  Time: 1800
        Latitude: 25.80         Longitude: -54.40
        Windspeed: 55MPH        Pressure: 994mb
Storm Name: SEBASTIEN   Date: 20191123  Time: 0000
        Latitude: 26.70         Longitude: -52.60
        Windspeed: 60MPH        Pressure: 991mb
Storm Name: SEBASTIEN   Date: 20191123  Time: 0600
        Latitude: 28.10         Longitude: -50.50
        Windspeed: 60MPH        Pressure: 991mb
Storm Name: SEBASTIEN   Date: 20191123  Time: 1200
        Latitude: 29.60         Longitude: -48.40
        Windspeed: 55MPH        Pressure: 994mb
Storm Name: SEBASTIEN   Date: 20191123  Time: 1800
        Latitude: 31.50         Longitude: -46.40
        Windspeed: 55MPH        Pressure: 994mb
Storm Name: SEBASTIEN   Date: 20191124  Time: 0000
        Latitude: 33.50         Longitude: -44.40
        Windspeed: 55MPH        Pressure: 994mb
Storm Name: SEBASTIEN   Date: 20191124  Time: 0600
        Latitude: 35.20         Longitude: -41.70
        Windspeed: 55MPH        Pressure: 994mb
Storm Name: SEBASTIEN   Date: 20191124  Time: 1200
        Latitude: 36.60         Longitude: -38.50
        Windspeed: 55MPH        Pressure: 994mb
Storm Name: SEBASTIEN   Date: 20191124  Time: 1800
        Latitude: 38.20         Longitude: -34.70
        Windspeed: 55MPH        Pressure: 994mb
Storm Name: SEBASTIEN   Date: 20191125  Time: 0000
        Latitude: 40.00         Longitude: -30.90
        Windspeed: 55MPH        Pressure: 992mb
Storm Name: SEBASTIEN   Date: 20191125  Time: 0600
        Latitude: 41.90         Longitude: -26.70
        Windspeed: 60MPH        Pressure: 988mb
Storm Name: SEBASTIEN   Date: 20191125  Time: 1200
        Latitude: 44.00         Longitude: -22.00
        Windspeed: 60MPH        Pressure: 982mb
Storm Name: SEBASTIEN   Date: 20191125  Time: 1800
        Latitude: 46.40         Longitude: -16.30
        Windspeed: 60MPH        Pressure: 978mb
Storm Name: SEBASTIEN   Date: 20191126  Time: 0000
        Latitude: 48.80         Longitude: -12.20
        Windspeed: 55MPH        Pressure: 974mb
Storm Name: SEBASTIEN   Date: 20191126  Time: 0600
        Latitude: 51.30         Longitude: -9.30
        Windspeed: 50MPH        Pressure: 972mb
Storm Name: SEBASTIEN   Date: 20191126  Time: 1200
        Latitude: 52.20         Longitude: -9.30
        Windspeed: 45MPH        Pressure: 970mb
Storm Name: SEBASTIEN   Date: 20191126  Time: 1800
        Latitude: 52.20         Longitude: -8.90
        Windspeed: 40MPH        Pressure: 972mb
Storm Name: SEBASTIEN   Date: 20191127  Time: 0000
        Latitude: 51.80         Longitude: -8.20
        Windspeed: 40MPH        Pressure: 974mb
Storm Name: SEBASTIEN   Date: 20191127  Time: 0600
        Latitude: 51.40         Longitude: -6.00
        Windspeed: 40MPH        Pressure: 976mb
Storm Name: SEBASTIEN   Date: 20191127  Time: 1200
        Latitude: 51.30         Longitude: -2.10
        Windspeed: 40MPH        Pressure: 980mb

Search Result: 34 results for for "sebastien"

        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        7) Sort Storm Data [by Date/Time]
        8) Sort Storm Data [by Storm Name]
        9) Maintain Data
        0) Exit the Program
Please Enter an Option [0-9]:  4

Please enter name [partial]:  seb      

Storm Name: SEBASTIEN   Date: 20191119  Time: 0600
        Latitude: 19.40         Longitude: -58.10
        Windspeed: 35MPH        Pressure: 1006mb
Storm Name: SEBASTIEN   Date: 20191119  Time: 1200
        Latitude: 19.90         Longitude: -58.50
        Windspeed: 40MPH        Pressure: 1004mb
Storm Name: SEBASTIEN   Date: 20191119  Time: 1800
        Latitude: 20.30         Longitude: -59.40
        Windspeed: 40MPH        Pressure: 1004mb
Storm Name: SEBASTIEN   Date: 20191120  Time: 0000
        Latitude: 20.40         Longitude: -60.30
        Windspeed: 40MPH        Pressure: 1002mb
Storm Name: SEBASTIEN   Date: 20191120  Time: 0600
        Latitude: 20.50         Longitude: -61.00
        Windspeed: 45MPH        Pressure: 1000mb
Storm Name: SEBASTIEN   Date: 20191120  Time: 1200
        Latitude: 20.80         Longitude: -61.70
        Windspeed: 45MPH        Pressure: 999mb
Storm Name: SEBASTIEN   Date: 20191120  Time: 1800
        Latitude: 21.30         Longitude: -61.70
        Windspeed: 45MPH        Pressure: 999mb
Storm Name: SEBASTIEN   Date: 20191121  Time: 0000
        Latitude: 21.90         Longitude: -61.70
        Windspeed: 50MPH        Pressure: 996mb
Storm Name: SEBASTIEN   Date: 20191121  Time: 0600
        Latitude: 22.40         Longitude: -61.40
        Windspeed: 50MPH        Pressure: 996mb
Storm Name: SEBASTIEN   Date: 20191121  Time: 1200
        Latitude: 22.90         Longitude: -60.90
        Windspeed: 50MPH        Pressure: 996mb
Storm Name: SEBASTIEN   Date: 20191121  Time: 1800
        Latitude: 23.50         Longitude: -60.10
        Windspeed: 50MPH        Pressure: 996mb
Storm Name: SEBASTIEN   Date: 20191122  Time: 0000
        Latitude: 24.20         Longitude: -58.80
        Windspeed: 50MPH        Pressure: 996mb
Storm Name: SEBASTIEN   Date: 20191122  Time: 0600
        Latitude: 24.50         Longitude: -57.30
        Windspeed: 50MPH        Pressure: 996mb
Storm Name: SEBASTIEN   Date: 20191122  Time: 1200
        Latitude: 25.00         Longitude: -55.80
        Windspeed: 50MPH        Pressure: 996mb
Storm Name: SEBASTIEN   Date: 20191122  Time: 1800
        Latitude: 25.80         Longitude: -54.40
        Windspeed: 55MPH        Pressure: 994mb
Storm Name: SEBASTIEN   Date: 20191123  Time: 0000
        Latitude: 26.70         Longitude: -52.60
        Windspeed: 60MPH        Pressure: 991mb
Storm Name: SEBASTIEN   Date: 20191123  Time: 0600
        Latitude: 28.10         Longitude: -50.50
        Windspeed: 60MPH        Pressure: 991mb
Storm Name: SEBASTIEN   Date: 20191123  Time: 1200
        Latitude: 29.60         Longitude: -48.40
        Windspeed: 55MPH        Pressure: 994mb
Storm Name: SEBASTIEN   Date: 20191123  Time: 1800
        Latitude: 31.50         Longitude: -46.40
        Windspeed: 55MPH        Pressure: 994mb
Storm Name: SEBASTIEN   Date: 20191124  Time: 0000
        Latitude: 33.50         Longitude: -44.40
        Windspeed: 55MPH        Pressure: 994mb
Storm Name: SEBASTIEN   Date: 20191124  Time: 0600
        Latitude: 35.20         Longitude: -41.70
        Windspeed: 55MPH        Pressure: 994mb
Storm Name: SEBASTIEN   Date: 20191124  Time: 1200
        Latitude: 36.60         Longitude: -38.50
        Windspeed: 55MPH        Pressure: 994mb
Storm Name: SEBASTIEN   Date: 20191124  Time: 1800
        Latitude: 38.20         Longitude: -34.70
        Windspeed: 55MPH        Pressure: 994mb
Storm Name: SEBASTIEN   Date: 20191125  Time: 0000
        Latitude: 40.00         Longitude: -30.90
        Windspeed: 55MPH        Pressure: 992mb
Storm Name: SEBASTIEN   Date: 20191125  Time: 0600
        Latitude: 41.90         Longitude: -26.70
        Windspeed: 60MPH        Pressure: 988mb
Storm Name: SEBASTIEN   Date: 20191125  Time: 1200
        Latitude: 44.00         Longitude: -22.00
        Windspeed: 60MPH        Pressure: 982mb
Storm Name: SEBASTIEN   Date: 20191125  Time: 1800
        Latitude: 46.40         Longitude: -16.30
        Windspeed: 60MPH        Pressure: 978mb
Storm Name: SEBASTIEN   Date: 20191126  Time: 0000
        Latitude: 48.80         Longitude: -12.20
        Windspeed: 55MPH        Pressure: 974mb
Storm Name: SEBASTIEN   Date: 20191126  Time: 0600
        Latitude: 51.30         Longitude: -9.30
        Windspeed: 50MPH        Pressure: 972mb
Storm Name: SEBASTIEN   Date: 20191126  Time: 1200
        Latitude: 52.20         Longitude: -9.30
        Windspeed: 45MPH        Pressure: 970mb
Storm Name: SEBASTIEN   Date: 20191126  Time: 1800
        Latitude: 52.20         Longitude: -8.90
        Windspeed: 40MPH        Pressure: 972mb
Storm Name: SEBASTIEN   Date: 20191127  Time: 0000
        Latitude: 51.80         Longitude: -8.20
        Windspeed: 40MPH        Pressure: 974mb
Storm Name: SEBASTIEN   Date: 20191127  Time: 0600
        Latitude: 51.40         Longitude: -6.00
        Windspeed: 40MPH        Pressure: 976mb
Storm Name: SEBASTIEN   Date: 20191127  Time: 1200
        Latitude: 51.30         Longitude: -2.10
        Windspeed: 40MPH        Pressure: 980mb

Search Result: 34 results for for "seb"

        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        7) Sort Storm Data [by Date/Time]
        8) Sort Storm Data [by Storm Name]
        9) Maintain Data
        0) Exit the Program
Please Enter an Option [0-9]:  4

Please enter name [partial]:  Bobbert


Search Result: 0 results for for "Bobbert"

        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        7) Sort Storm Data [by Date/Time]
        8) Sort Storm Data [by Storm Name]
        9) Maintain Data
        0) Exit the Program
Please Enter an Option [0-9]:  5

Please enter windspeed [minimum]:  155

Storm Name: DORIAN      Date: 20190901  Time: 1200
        Latitude: 26.50         Longitude: -76.50
        Windspeed: 155MPH       Pressure: 927mb
Storm Name: DORIAN      Date: 20190901  Time: 1640
        Latitude: 26.50         Longitude: -77.00
        Windspeed: 160MPH       Pressure: 910mb
Storm Name: DORIAN      Date: 20190901  Time: 1800
        Latitude: 26.50         Longitude: -77.10
        Windspeed: 160MPH       Pressure: 910mb
Storm Name: DORIAN      Date: 20190902  Time: 0000
        Latitude: 26.60         Longitude: -77.70
        Windspeed: 155MPH       Pressure: 914mb
Storm Name: DORIAN      Date: 20190902  Time: 0215
        Latitude: 26.60         Longitude: -77.80
        Windspeed: 155MPH       Pressure: 914mb

Search Result:  5 results found for 155

        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        7) Sort Storm Data [by Date/Time]
        8) Sort Storm Data [by Storm Name]
        9) Maintain Data
        0) Exit the Program
Please Enter an Option [0-9]:  6

Please enter pressure [maximum]:  910

Storm Name: DORIAN      Date: 20190901  Time: 1640
        Latitude: 26.50         Longitude: -77.00
        Windspeed: 160MPH       Pressure: 910mb
Storm Name: DORIAN      Date: 20190901  Time: 1800
        Latitude: 26.50         Longitude: -77.10
        Windspeed: 160MPH       Pressure: 910mb

Search Result:  2 results found for 910

        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        7) Sort Storm Data [by Date/Time]
        8) Sort Storm Data [by Storm Name]
        9) Maintain Data
        0) Exit the Program
Please Enter an Option [0-9]:  7
        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        7) Sort Storm Data [by Date/Time]
        8) Sort Storm Data [by Storm Name]
        9) Maintain Data
        0) Exit the Program
Please Enter an Option [0-9]:  9
        1) Add Storm Data
        2) Modify Storm Data
        3) Delete Storm Data
        4) Save Storm Data to File
        0) Return to Main Menu
Please Enter an Option [0-4]:  4
Please enter filename:  byDate
        1) Add Storm Data
        2) Modify Storm Data
        3) Delete Storm Data
        4) Save Storm Data to File
        0) Return to Main Menu
Please Enter an Option [0-4]:  0
        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        7) Sort Storm Data [by Date/Time]
        8) Sort Storm Data [by Storm Name]
        9) Maintain Data
        0) Exit the Program
Please Enter an Option [0-9]:  7
        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        7) Sort Storm Data [by Date/Time]
        8) Sort Storm Data [by Storm Name]
        9) Maintain Data
        0) Exit the Program
Please Enter an Option [0-9]:  9
        1) Add Storm Data
        2) Modify Storm Data
        3) Delete Storm Data
        4) Save Storm Data to File
        0) Return to Main Menu
Please Enter an Option [0-4]:  4
Please enter filename:  byName
        1) Add Storm Data
        2) Modify Storm Data
        3) Delete Storm Data
        4) Save Storm Data to File
        0) Return to Main Menu
Please Enter an Option [0-4]:  1
Please enter storm name:  Bobbert
Please enter date [MMDD]:  1232
Please enter date [MMDD]:  1213
Please enter time (Format 24H [HHMM]):  3599
Please enter time (Format 24H [HHMM]):  0625
Please enter latitude:  -190
Please enter latitude:  190
Please enter latitude:  20.2
Please enter longitude:  -100
Please enter longitude:  100
Please enter longitude:  -9.2
Please enter windspeed:  120
Please enter pressure:  1010
        1) Add Storm Data
        2) Modify Storm Data
        3) Delete Storm Data
        4) Save Storm Data to File
        0) Return to Main Menu
Please Enter an Option [0-4]:  2
Please enter record number to be changed:  493
Please enter storm name:  Bobbert
Please enter date [MMDD]:  1212
Please enter time (Format 24H [HHMM]):  0001
Please enter latitude:  19.2
Please enter longitude:  -2.1
Please enter windspeed:  115
Please enter pressure:  1000
        1) Add Storm Data
        2) Modify Storm Data
        3) Delete Storm Data
        4) Save Storm Data to File
        0) Return to Main Menu
Please Enter an Option [0-4]:  3
Please enter record number to be deleted:  492
        1) Add Storm Data
        2) Modify Storm Data
        3) Delete Storm Data
        4) Save Storm Data to File
        0) Return to Main Menu
Please Enter an Option [0-4]:  4
Please enter filename:  modifiedStorms
        1) Add Storm Data
        2) Modify Storm Data
        3) Delete Storm Data
        4) Save Storm Data to File
        0) Return to Main Menu
Please Enter an Option [0-4]:  0
        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        7) Sort Storm Data [by Date/Time]
        8) Sort Storm Data [by Storm Name]
        9) Maintain Data
        0) Exit the Program
Please Enter an Option [0-9]:  0
*/