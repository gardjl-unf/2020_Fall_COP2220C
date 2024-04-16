/* COP2220C Saturday October 28, 2020
 * Author: Jason Gardner
 * Filename: project-6_hurricane_gardner-jason_cop2220c.c
 * Purpose: Import and Display Hurricane Data
 * Objective: Strings, Files, Functions, Decisions, Loops, Arrays, Pointers, Types, Structures
 */

/*  gcc option -Wall warns me of various tedious things, so a lot of suggestions
 * for more streamlined code end up sacrificed to making the compiler not complain
 * printf(MYSTRING) gets a warning, so I end up having to write printf("%s", MYSTRING)
 * Initialization of most things is another one of these cases.
 */


// Headers
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// Definitions
#define NUM_STORMS 1000
#define LINE_LEN 100
#define DELIMITER '|'
#define END_DELIMITER '\n'
//#define DEBUG

// Types/Structures
typedef struct {
    char stormName[LINE_LEN + 1];
    int date;
    int time;
    double latitude;
    double longitude;
    int windspeed;
    int pressure;
} storm_t ;

// Function Prototypes
void displayWelcome (void);
void displayCredits (void);
int loadRecords (storm_t *s);
void displayStorm (storm_t *s);
int getOption (void);
bool findString(const char *inputString, const char *compareString);
bool checkChar(char i, char j);

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
    // Results Format Strings:  Number of Results, and the value searched for
    const char *RESULT_NUM = "\nSearch Result:  %i results found for %i\n\n";
    const char *RESULT_STR = "\nSearch Result: %i results for for \"%s\"\n\n";

    // Variable Declaration/Initialization
    // Array of storm_t "objects"
    storm_t stormData[NUM_STORMS];
    // Pointer to individual storm, initialized at the base of our array
    storm_t *pStorm = stormData;
    /* Another C textbook I was reading, Modern C, by Jens Gustedt, spent quite some time
     * writing about number types.  In particular, he spent a while devoted to
     * how number types handle overflow.  The recommendation was size_t for positive whole
     * numbers, to include indices and counters. I used it here to test it.
     */
    const size_t removeYear = 20190000;
    int numEntries = 0;
    int option = -1;
    int findNum = 0;
    char findStr[LINE_LEN];
    int searchCount = 0;

    /* Read in file via function loadRecords
     * Because loadRecords returns the number of records,
     * which COULD be 0, written to return -1 on an error
     * opening the file and exit the program.
     */
    if ((numEntries = loadRecords(pStorm)) == -1) {
        return 1;
    }

    // Call displayWelcome
    displayWelcome();

    // While option isn't 0/false
    while (option) {
        // Get option
        option = getOption();
        // Use option - decision (switch)
        switch(option) {
            // 0: Exit
            case 0:
                break;
            // 1: Display entries from record number to final record
            case 1:
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
                // Print a blank line
                printf("\n");
                /* Set storm pointer to the base address of our array(stormData)
                 * Offset that by (findNum -1)
                 */
                pStorm = stormData + (findNum - 1);

                /* From that offset number, to the  numEntries-1
                 * Increment index, and the storm pointer
                 */
                for (int i = findNum - 1; i < numEntries; i++, pStorm++) {
                    // Call displayStorm for pStorm
                    displayStorm(pStorm);                    
                }
                // Print a blank line
                printf("\n");
                break;
            // 2: Display entries by date (with count)
            case 2:
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
                    if ((pStorm->date - removeYear) == findNum) {
                        // Call displayStorm for pStorm
                        displayStorm(pStorm);
                        // Increment counter
                        searchCount++;
                    }                    
                }
                // Display count of search result
                printf(RESULT_NUM, searchCount, findNum);
                break;
            // 3: Display entries by name [exact] (with count)
            case 3:
                // Prompt user for "name [exact]"
                printf(SEARCH_PROMPT, "name [exact]");
                // Get (user input) and store that string to findStr
                scanf("%s", findStr);
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
            // 4: Display entries by name [partial] (with count)
            case 4:
                // Prompt user for "name [partial]"
                printf(SEARCH_PROMPT, "name [partial]");
                // Get (user input) and store that string to findStr
                scanf("%s", findStr);
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
            // 5: Display entries by windspeed [minimum] (with count)
            case 5:
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
            // 6: Display entries by pressure [maximum] (with count)
            case 6:
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
            // default:  none
            default:
                break;
        
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
 * @param storm_t *s - pointer to storm struct type for entry of data
 * @return int - number of storms entered
 */
int loadRecords (storm_t *s) {
    // String Literals for I/O and User Experience
    const char *FILE_OPEN_ERROR = "Error:  Could not open file \"%s\"";
    const char *FILENAME = "StormsAL2019.txt";

    // Variable Declaration/Initialization
    int numEntries = 0;
    char readLine[LINE_LEN + 1];
    char *pStart;
    char *pEnd;
    // Open file
    FILE *inputFile = fopen(FILENAME, "r");
    // If file fails to open
    if (!inputFile){
        // Display error message
        printf(FILE_OPEN_ERROR, FILENAME);
        // Return -1 (Error)
        return -1;
    }
    
    /* While the string read fromt the file exists, and we haven't exceeded the size
     * of our storm array
     */
    while (fgets(readLine, sizeof(readLine), inputFile) && numEntries <= NUM_STORMS) {
        /* Non-Classwork Code
        strcpy(s->stormName, strtok(readLine, DELIMITER));
        s->date = strtol(strtok(NULL, DELIMITER), NULL, 10);
        s->time = strtol(strtok(NULL, DELIMITER), NULL, 10);
        s->latitude = strtod(strtok(NULL, DELIMITER), NULL);
        s->longitude = strtod(strtok(NULL, DELIMITER), NULL);
        s->windspeed = strtol(strtok(NULL, DELIMITER), NULL, 10);
        s->pressure = strtol(strtok(NULL, END_DELIMITER), NULL, 10);
        */


       /* Code form classwork:
        * atoi/atof is FAR easier to use. When looking up usage, ran into
        * text suggesting that they had been depreciated.  They have NOT.
        * 
        * strtok() needs the input string first time, NULL remaining times
        * 
        * Changed from STRING to CHARACTER in definitions between methods
        * 
        * Different data types preclude a loop, here
        */

        // Set start pointer to the beginning of buffer
        pStart = readLine;
        // Set end pointer to first delimiter
        pEnd = strchr(readLine, DELIMITER);

        /* Copy string to stormName, starting at the start pointer, for length
         * pEnd - pStart
         */
        strncpy(s->stormName, pStart, pEnd - pStart);

        // Move start pointer to be one character past the delimiter at pEnd
        pStart = pEnd + 1;
        // End pointer to next delimiter
        pEnd = strchr(pStart, DELIMITER);

        // Storm date to integer value at start pointer
        s->date = atoi(pStart);

        // Again...
        pStart = pEnd + 1;
        pEnd = strchr(pStart, DELIMITER);

        // Storm time to integer value at start pointer
        s->time = atoi(pStart);

        // Again...
        pStart = pEnd + 1;
        pEnd = strchr(pStart, DELIMITER);

        // Storm latitude to floating point value at start pointer
        s->latitude = atof(pStart);

        // Again...
        pStart = pEnd + 1;
        pEnd = strchr(pStart, DELIMITER);

        // Storm longitude to floating point value at start pointer
        s->longitude = atof(pStart);

        // Again...
        pStart = pEnd + 1;
        pEnd = strchr(pStart, DELIMITER);

        // Storm windspeed to integer value at start pointer
        s->windspeed = atoi(pStart);

        // Again...
        pStart = pEnd + 1;
        /* But this is the last item in the buffer, which should end with a different
         * character, so the pointer goes to that
         */
        pEnd = strchr(pStart, END_DELIMITER);

        // Storm pressure to integer value at start pointer
        s->pressure = atoi(pStart);

        // Increment number of entries
        numEntries++;

        #ifdef DEBUG
        printf("Storm Data (#%d) Loaded:\n", numEntries);
        displayStorm(s);
        #endif

        // Increment storm pointer to next storm.
        s++;
    }

    // Close inputFile
    fclose(inputFile);

    #ifdef DEBUG
    printf("Number of Entries Loaded:  %d\n", numEntries);
    #endif

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
                            "Display Information for Storm(s) [by Pressure (Maximum)]\n"
                            };
    const char *PRINT_OPTIONS = "\t%d) %s";
    const char *EXIT_PROGRAM = "\t0) Exit the Program\n";
    const char *PROMPT_INPUT = "Please Enter an Option [0-%d]:  ";
    const char *INPUT_ERROR = "\nInvalid Entry:  Please Enter a Number Between 0 and %d\n\n";

    // Variable Declaration/Initialization
    const int NUM_OPTIONS = 6;
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
    const char *OUTPUT_FORMAT = "Storm Name:  %s\tDate:  %i\tTime:  %i\tLatitude:  %.2lf\tLongitude:  %.2lf\tWindspeed:  %iMPH\tPressure:  %imb\n";

    // Print out the storm data
    printf(OUTPUT_FORMAT, s->stormName, s->date, s->time, s->latitude, s->longitude, s->windspeed, s->pressure);
}

bool findString(const char *inputString, const char *compareString) {
    // Variable Declaration/Initialization
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

/* Test Data:
 *
 * Rename file in folder with compiled program.
 * Expected Output:
 * Error:  Could not open file "StormsAL2019.txt"
 * [Program Ends]
 * 
 * Flow Control:
 * Menu: Enter "-5", "25", and "q"
 * Expected Output:
 * Invalid Entry:  Please Enter a Number Between 0 and 6
 * [Menu Loop]
 * Main Menu -> Option 1: "-5", "0",and "500"
 * Expected Output:
 * Invalid Entry:  Valid Records Exist in Range of 1-493
 * [Input Loop]
 * 
 * Main Menu -> Option 1 -> 1
ANDREA|20190520|1800|28.10|-68.60|35|1008
ANDREA|20190521|0|29.10|-68.80|35|1006
ANDREA|20190521|600|29.90|-69.00|35|1007
ANDREA|20190521|1200|30.60|-69.10|30|1009
ANDREA|20190521|1800|30.80|-68.60|30|1009
ANDREA|20190522|0|31.30|-67.70|30|1010
ANDREA|20190522|600|31.60|-66.70|25|1011
BARRY|20190710|1200|28.50|-86.50|25|1009
BARRY|20190710|1800|28.10|-87.10|30|1009
BARRY|20190711|0|27.80|-87.60|30|1008
...
SEBASTIEN|20191126|1200|52.20|-9.30|45|970
SEBASTIEN|20191126|1800|52.20|-8.90|40|972
SEBASTIEN|20191127|0|51.80|-8.20|40|974
SEBASTIEN|20191127|600|51.40|-6.00|40|976
SEBASTIEN|20191127|1200|51.30|-2.10|40|980
[493 Results]

 * Main Menu -> Option 1 -> 490
SEBASTIEN|20191126|1800|52.20|-8.90|40|972
SEBASTIEN|20191127|0|51.80|-8.20|40|974
SEBASTIEN|20191127|600|51.40|-6.00|40|976
SEBASTIEN|20191127|1200|51.30|-2.10|40|980
[4 Results]

 * Main Menu -> Option 2 -> 1119
SEBASTIEN|20191119|600|19.40|-58.10|35|1006
SEBASTIEN|20191119|1200|19.90|-58.50|40|1004
SEBASTIEN|20191119|1800|20.30|-59.40|40|1004
[3 Reults]

 * Main Menu -> Option 2 -> 1024
PABLO|20191024|0|40.20|-38.40|50|998
PABLO|20191024|600|39.00|-39.90|50|995
PABLO|20191024|1200|36.90|-39.30|50|990
PABLO|20191024|1800|35.80|-36.90|45|988
[4 RESULTS]

 * Main Mehu -> Option 2 -> 0411
[NO RESULTS]

 * Main Menu -> Option 3 -> seb
[NO RESULTS]

 * Main Menu -> Option 3 -> sebastien
SEBASTIEN|20191119|600|19.40|-58.10|35|1006
SEBASTIEN|20191119|1200|19.90|-58.50|40|1004
SEBASTIEN|20191119|1800|20.30|-59.40|40|1004
SEBASTIEN|20191120|0|20.40|-60.30|40|1002
SEBASTIEN|20191120|600|20.50|-61.00|45|1000
SEBASTIEN|20191120|1200|20.80|-61.70|45|999
SEBASTIEN|20191120|1800|21.30|-61.70|45|999
SEBASTIEN|20191121|0|21.90|-61.70|50|996
SEBASTIEN|20191121|600|22.40|-61.40|50|996
SEBASTIEN|20191121|1200|22.90|-60.90|50|996
...
SEBASTIEN|20191126|1200|52.20|-9.30|45|970
SEBASTIEN|20191126|1800|52.20|-8.90|40|972
SEBASTIEN|20191127|0|51.80|-8.20|40|974
SEBASTIEN|20191127|600|51.40|-6.00|40|976
SEBASTIEN|20191127|1200|51.30|-2.10|40|980
[34 RESULTS]

 * Main Menu -> Option 4 -> seb
SEBASTIEN|20191119|600|19.40|-58.10|35|1006
SEBASTIEN|20191119|1200|19.90|-58.50|40|1004
SEBASTIEN|20191119|1800|20.30|-59.40|40|1004
SEBASTIEN|20191120|0|20.40|-60.30|40|1002
SEBASTIEN|20191120|600|20.50|-61.00|45|1000
SEBASTIEN|20191120|1200|20.80|-61.70|45|999
SEBASTIEN|20191120|1800|21.30|-61.70|45|999
SEBASTIEN|20191121|0|21.90|-61.70|50|996
SEBASTIEN|20191121|600|22.40|-61.40|50|996
SEBASTIEN|20191121|1200|22.90|-60.90|50|996
...
SEBASTIEN|20191126|1200|52.20|-9.30|45|970
SEBASTIEN|20191126|1800|52.20|-8.90|40|972
SEBASTIEN|20191127|0|51.80|-8.20|40|974
SEBASTIEN|20191127|600|51.40|-6.00|40|976
SEBASTIEN|20191127|1200|51.30|-2.10|40|980
[34 RESULTS]
 * Main Menu -> Option 4 -> sebastien
SEBASTIEN|20191119|600|19.40|-58.10|35|1006
SEBASTIEN|20191119|1200|19.90|-58.50|40|1004
SEBASTIEN|20191119|1800|20.30|-59.40|40|1004
SEBASTIEN|20191120|0|20.40|-60.30|40|1002
SEBASTIEN|20191120|600|20.50|-61.00|45|1000
SEBASTIEN|20191120|1200|20.80|-61.70|45|999
SEBASTIEN|20191120|1800|21.30|-61.70|45|999
SEBASTIEN|20191121|0|21.90|-61.70|50|996
SEBASTIEN|20191121|600|22.40|-61.40|50|996
SEBASTIEN|20191121|1200|22.90|-60.90|50|996
...
SEBASTIEN|20191126|1200|52.20|-9.30|45|970
SEBASTIEN|20191126|1800|52.20|-8.90|40|972
SEBASTIEN|20191127|0|51.80|-8.20|40|974
SEBASTIEN|20191127|600|51.40|-6.00|40|976
SEBASTIEN|20191127|1200|51.30|-2.10|40|980
[34 RESULTS]

 * Main Menu -> Option 4 -> andr
ANDREA|20190520|1800|28.10|-68.60|35|1008
ANDREA|20190521|0|29.10|-68.80|35|1006
ANDREA|20190521|600|29.90|-69.00|35|1007
ANDREA|20190521|1200|30.60|-69.10|30|1009
ANDREA|20190521|1800|30.80|-68.60|30|1009
ANDREA|20190522|0|31.30|-67.70|30|1010
ANDREA|20190522|600|31.60|-66.70|25|1011
[7 RESULTS]

 * Main Menu -> Option 5 -> 140
DORIAN|20190901|600|26.40|-75.60|145|934
DORIAN|20190901|1200|26.50|-76.50|155|927
DORIAN|20190901|1640|26.50|-77.00|160|910
DORIAN|20190901|1800|26.50|-77.10|160|910
DORIAN|20190902|0|26.60|-77.70|155|914
DORIAN|20190902|215|26.60|-77.80|155|914
DORIAN|20190902|600|26.60|-78.00|145|916
LORENZO|20190929|300|24.30|-45.00|140|925
[8 RESULTS]

 * Main Menu -> Option 6 -> 920
DORIAN|20190901|1640|26.50|-77.00|160|910
DORIAN|20190901|1800|26.50|-77.10|160|910
DORIAN|20190902|0|26.60|-77.70|155|914
DORIAN|20190902|215|26.60|-77.80|155|914
DORIAN|20190902|600|26.60|-78.00|145|916
[6 RESULTS]

 * Main Menu -> Option 0
[END PROGRAM]
 */

/* Program Output
PS C:\Users\gardj\OneDrive - Florida State College at Jacksonville\2020 3(Fall) FSCJ\COP2220C-1433\workspace\project_6> .\project-6_hurricane_gardner-jason_cop2220c.exe  
Error:  Could not open file "StormsAL2019.txt"
PS C:\Users\gardj\OneDrive - Florida State College at Jacksonville\2020 3(Fall) FSCJ\COP2220C-1433\workspace\project_6> .\project-6_hurricane_gardner-jason_cop2220c.exe  
Welcome to the 2019 Atlantic Basin Information Center by Jason Gardner

        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]       
        4) Display Information for Storm(s) [by Name (Partial)]     
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        0) Exit the Program
Please Enter an Option [0-6]:  -5

Invalid Entry:  Please Enter a Number Between 0 and 6

        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        0) Exit the Program
Please Enter an Option [0-6]:  25

Invalid Entry:  Please Enter a Number Between 0 and 6

        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        0) Exit the Program
Please Enter an Option [0-6]:  q

Invalid Entry:  Please Enter a Number Between 0 and 6

        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        0) Exit the Program
Please Enter an Option [0-6]:  1

Please enter record number:  -5

Invalid Entry:  Valid Records Exist in Range of 1-493

Please enter record number:  0

Invalid Entry:  Valid Records Exist in Range of 1-493

Please enter record number:  500

Invalid Entry:  Valid Records Exist in Range of 1-493

Please enter record number:  1

Storm Name:  ANDREA     Date:  20190520 Time:  1800     Latitude:  28.10        Longitude:  -68.60      Windspeed:  35MPH       Pressure:  1008mb
Storm Name:  ANDREA     Date:  20190521 Time:  0        Latitude:  29.10        Longitude:  -68.80      Windspeed:  35MPH       Pressure:  1006mb
Storm Name:  ANDREA     Date:  20190521 Time:  600      Latitude:  29.90        Longitude:  -69.00      Windspeed:  35MPH       Pressure:  1007mb
Storm Name:  ANDREA     Date:  20190521 Time:  1200     Latitude:  30.60        Longitude:  -69.10      Windspeed:  30MPH       Pressure:  1009mb
Storm Name:  ANDREA     Date:  20190521 Time:  1800     Latitude:  30.80        Longitude:  -68.60      Windspeed:  30MPH       Pressure:  1009mb
Storm Name:  ANDREA     Date:  20190522 Time:  0        Latitude:  31.30        Longitude:  -67.70      Windspeed:  30MPH       Pressure:  1010mb
Storm Name:  ANDREA     Date:  20190522 Time:  600      Latitude:  31.60        Longitude:  -66.70      Windspeed:  25MPH       Pressure:  1011mb
Storm Name:  BARRY      Date:  20190710 Time:  1200     Latitude:  28.50        Longitude:  -86.50      Windspeed:  25MPH       Pressure:  1009mb
Storm Name:  BARRY      Date:  20190710 Time:  1800     Latitude:  28.10        Longitude:  -87.10      Windspeed:  30MPH       Pressure:  1009mb
Storm Name:  BARRY      Date:  20190711 Time:  0        Latitude:  27.80        Longitude:  -87.60      Windspeed:  30MPH       Pressure:  1008mb
Storm Name:  BARRY      Date:  20190711 Time:  600      Latitude:  27.70        Longitude:  -88.00      Windspeed:  35MPH       Pressure:  1007mb
Storm Name:  BARRY      Date:  20190711 Time:  1200     Latitude:  27.70        Longitude:  -88.40      Windspeed:  35MPH       Pressure:  1005mb
Storm Name:  BARRY      Date:  20190711 Time:  1800     Latitude:  27.70        Longitude:  -88.80      Windspeed:  40MPH       Pressure:  1005mb
Storm Name:  BARRY      Date:  20190712 Time:  0        Latitude:  27.80        Longitude:  -89.20      Windspeed:  45MPH       Pressure:  1001mb
Storm Name:  BARRY      Date:  20190712 Time:  600      Latitude:  27.90        Longitude:  -89.70      Windspeed:  45MPH       Pressure:  1001mb
Storm Name:  BARRY      Date:  20190712 Time:  1200     Latitude:  28.10        Longitude:  -90.20      Windspeed:  50MPH       Pressure:  998mb
Storm Name:  BARRY      Date:  20190712 Time:  1800     Latitude:  28.40        Longitude:  -90.70      Windspeed:  55MPH       Pressure:  993mb
Storm Name:  BARRY      Date:  20190713 Time:  0        Latitude:  28.60        Longitude:  -91.10      Windspeed:  60MPH       Pressure:  993mb
Storm Name:  BARRY      Date:  20190713 Time:  600      Latitude:  28.90        Longitude:  -91.50      Windspeed:  60MPH       Pressure:  993mb
Storm Name:  BARRY      Date:  20190713 Time:  1200     Latitude:  29.30        Longitude:  -91.90      Windspeed:  65MPH       Pressure:  993mb
Storm Name:  BARRY      Date:  20190713 Time:  1500     Latitude:  29.60        Longitude:  -92.20      Windspeed:  65MPH       Pressure:  993mb
Storm Name:  BARRY      Date:  20190713 Time:  1800     Latitude:  29.90        Longitude:  -92.40      Windspeed:  60MPH       Pressure:  996mb
Storm Name:  BARRY      Date:  20190714 Time:  0        Latitude:  30.40        Longitude:  -92.80      Windspeed:  50MPH       Pressure:  999mb
Storm Name:  BARRY      Date:  20190714 Time:  600      Latitude:  31.00        Longitude:  -93.20      Windspeed:  40MPH       Pressure:  1003mb
Storm Name:  BARRY      Date:  20190714 Time:  1200     Latitude:  31.60        Longitude:  -93.50      Windspeed:  35MPH       Pressure:  1005mb
Storm Name:  BARRY      Date:  20190714 Time:  1800     Latitude:  32.30        Longitude:  -93.60      Windspeed:  35MPH       Pressure:  1007mb
Storm Name:  BARRY      Date:  20190715 Time:  0        Latitude:  33.00        Longitude:  -93.60      Windspeed:  25MPH       Pressure:  1008mb
Storm Name:  BARRY      Date:  20190715 Time:  600      Latitude:  33.90        Longitude:  -93.60      Windspeed:  25MPH       Pressure:  1008mb
Storm Name:  BARRY      Date:  20190715 Time:  1200     Latitude:  34.70        Longitude:  -93.60      Windspeed:  20MPH       Pressure:  1008mb
Storm Name:  BARRY      Date:  20190715 Time:  1800     Latitude:  35.50        Longitude:  -93.50      Windspeed:  20MPH       Pressure:  1008mb
Storm Name:  BARRY      Date:  20190716 Time:  0        Latitude:  36.30        Longitude:  -93.30      Windspeed:  15MPH       Pressure:  1009mb
Storm Name:  BARRY      Date:  20190716 Time:  600      Latitude:  37.20        Longitude:  -92.90      Windspeed:  15MPH       Pressure:  1010mb
Storm Name:  THREE      Date:  20190722 Time:  1200     Latitude:  24.60        Longitude:  -77.40      Windspeed:  25MPH       Pressure:  1013mb
Storm Name:  THREE      Date:  20190722 Time:  1800     Latitude:  25.00        Longitude:  -78.40      Windspeed:  25MPH       Pressure:  1013mb
Storm Name:  THREE      Date:  20190723 Time:  0        Latitude:  25.70        Longitude:  -79.30      Windspeed:  25MPH       Pressure:  1013mb
Storm Name:  THREE      Date:  20190723 Time:  600      Latitude:  26.90        Longitude:  -79.60      Windspeed:  30MPH       Pressure:  1013mb
Storm Name:  THREE      Date:  20190723 Time:  1200     Latitude:  28.60        Longitude:  -80.00      Windspeed:  30MPH       Pressure:  1014mb
Storm Name:  CHANTAL    Date:  20190820 Time:  1800     Latitude:  40.10        Longitude:  -59.70      Windspeed:  30MPH       Pressure:  1008mb
Storm Name:  CHANTAL    Date:  20190821 Time:  0        Latitude:  40.30        Longitude:  -57.10      Windspeed:  35MPH       Pressure:  1007mb
Storm Name:  CHANTAL    Date:  20190821 Time:  600      Latitude:  40.30        Longitude:  -54.80      Windspeed:  35MPH       Pressure:  1007mb
Storm Name:  CHANTAL    Date:  20190821 Time:  1200     Latitude:  40.10        Longitude:  -52.50      Windspeed:  35MPH       Pressure:  1007mb
Storm Name:  CHANTAL    Date:  20190821 Time:  1800     Latitude:  39.90        Longitude:  -50.30      Windspeed:  35MPH       Pressure:  1007mb
Storm Name:  CHANTAL    Date:  20190822 Time:  0        Latitude:  39.60        Longitude:  -48.30      Windspeed:  30MPH       Pressure:  1007mb
Storm Name:  CHANTAL    Date:  20190822 Time:  600      Latitude:  39.30        Longitude:  -46.30      Windspeed:  30MPH       Pressure:  1007mb
Storm Name:  CHANTAL    Date:  20190822 Time:  1200     Latitude:  38.90        Longitude:  -44.40      Windspeed:  30MPH       Pressure:  1007mb
Storm Name:  CHANTAL    Date:  20190822 Time:  1800     Latitude:  38.50        Longitude:  -42.90      Windspeed:  30MPH       Pressure:  1007mb
Storm Name:  CHANTAL    Date:  20190823 Time:  0        Latitude:  38.00        Longitude:  -41.80      Windspeed:  30MPH       Pressure:  1007mb
Storm Name:  CHANTAL    Date:  20190823 Time:  600      Latitude:  37.50        Longitude:  -41.20      Windspeed:  25MPH       Pressure:  1009mb
Storm Name:  CHANTAL    Date:  20190823 Time:  1200     Latitude:  36.90        Longitude:  -40.90      Windspeed:  25MPH       Pressure:  1011mb
Storm Name:  CHANTAL    Date:  20190823 Time:  1800     Latitude:  36.30        Longitude:  -40.80      Windspeed:  25MPH       Pressure:  1012mb
Storm Name:  CHANTAL    Date:  20190824 Time:  0        Latitude:  35.70        Longitude:  -40.90      Windspeed:  25MPH       Pressure:  1013mb
Storm Name:  CHANTAL    Date:  20190824 Time:  600      Latitude:  35.30        Longitude:  -41.20      Windspeed:  25MPH       Pressure:  1013mb
Storm Name:  CHANTAL    Date:  20190824 Time:  1200     Latitude:  35.10        Longitude:  -41.80      Windspeed:  25MPH       Pressure:  1013mb
Storm Name:  CHANTAL    Date:  20190824 Time:  1800     Latitude:  35.00        Longitude:  -42.50      Windspeed:  25MPH       Pressure:  1013mb
Storm Name:  CHANTAL    Date:  20190825 Time:  0        Latitude:  35.10        Longitude:  -43.20      Windspeed:  20MPH       Pressure:  1014mb
Storm Name:  CHANTAL    Date:  20190825 Time:  600      Latitude:  35.50        Longitude:  -43.60      Windspeed:  20MPH       Pressure:  1014mb
Storm Name:  CHANTAL    Date:  20190825 Time:  1200     Latitude:  35.90        Longitude:  -43.90      Windspeed:  20MPH       Pressure:  1014mb
Storm Name:  CHANTAL    Date:  20190825 Time:  1800     Latitude:  36.10        Longitude:  -44.10      Windspeed:  15MPH       Pressure:  1014mb
Storm Name:  CHANTAL    Date:  20190826 Time:  0        Latitude:  36.20        Longitude:  -44.40      Windspeed:  15MPH       Pressure:  1014mb
Storm Name:  CHANTAL    Date:  20190826 Time:  600      Latitude:  36.20        Longitude:  -44.80      Windspeed:  15MPH       Pressure:  1014mb
Storm Name:  CHANTAL    Date:  20190826 Time:  1200     Latitude:  36.40        Longitude:  -45.00      Windspeed:  15MPH       Pressure:  1014mb
Storm Name:  CHANTAL    Date:  20190826 Time:  1800     Latitude:  36.50        Longitude:  -44.80      Windspeed:  15MPH       Pressure:  1014mb
Storm Name:  DORIAN     Date:  20190824 Time:  600      Latitude:  10.30        Longitude:  -46.40      Windspeed:  25MPH       Pressure:  1011mb
Storm Name:  DORIAN     Date:  20190824 Time:  1200     Latitude:  10.40        Longitude:  -47.50      Windspeed:  30MPH       Pressure:  1010mb
Storm Name:  DORIAN     Date:  20190824 Time:  1800     Latitude:  10.60        Longitude:  -48.70      Windspeed:  35MPH       Pressure:  1008mb
Storm Name:  DORIAN     Date:  20190825 Time:  0        Latitude:  10.80        Longitude:  -49.90      Windspeed:  35MPH       Pressure:  1008mb
Storm Name:  DORIAN     Date:  20190825 Time:  600      Latitude:  11.00        Longitude:  -51.00      Windspeed:  35MPH       Pressure:  1008mb
Storm Name:  DORIAN     Date:  20190825 Time:  1200     Latitude:  11.20        Longitude:  -52.30      Windspeed:  40MPH       Pressure:  1007mb
Storm Name:  DORIAN     Date:  20190825 Time:  1800     Latitude:  11.40        Longitude:  -53.50      Windspeed:  45MPH       Pressure:  1007mb
Storm Name:  DORIAN     Date:  20190826 Time:  0        Latitude:  11.60        Longitude:  -54.70      Windspeed:  45MPH       Pressure:  1007mb
Storm Name:  DORIAN     Date:  20190826 Time:  600      Latitude:  11.90        Longitude:  -56.00      Windspeed:  45MPH       Pressure:  1006mb
Storm Name:  DORIAN     Date:  20190826 Time:  1200     Latitude:  12.20        Longitude:  -57.20      Windspeed:  45MPH       Pressure:  1006mb
Storm Name:  DORIAN     Date:  20190826 Time:  1800     Latitude:  12.60        Longitude:  -58.30      Windspeed:  45MPH       Pressure:  1006mb
Storm Name:  DORIAN     Date:  20190827 Time:  0        Latitude:  13.00        Longitude:  -59.20      Windspeed:  45MPH       Pressure:  1005mb
Storm Name:  DORIAN     Date:  20190827 Time:  130      Latitude:  13.10        Longitude:  -59.40      Windspeed:  45MPH       Pressure:  1005mb
Storm Name:  DORIAN     Date:  20190827 Time:  600      Latitude:  13.50        Longitude:  -60.20      Windspeed:  45MPH       Pressure:  1005mb
Storm Name:  DORIAN     Date:  20190827 Time:  1100     Latitude:  14.00        Longitude:  -60.90      Windspeed:  45MPH       Pressure:  1005mb
Storm Name:  DORIAN     Date:  20190827 Time:  1200     Latitude:  14.20        Longitude:  -61.20      Windspeed:  45MPH       Pressure:  1005mb
Storm Name:  DORIAN     Date:  20190827 Time:  1800     Latitude:  15.00        Longitude:  -62.00      Windspeed:  45MPH       Pressure:  1004mb
Storm Name:  DORIAN     Date:  20190828 Time:  0        Latitude:  15.70        Longitude:  -62.80      Windspeed:  50MPH       Pressure:  1003mb
Storm Name:  DORIAN     Date:  20190828 Time:  600      Latitude:  16.40        Longitude:  -63.50      Windspeed:  55MPH       Pressure:  1001mb
Storm Name:  DORIAN     Date:  20190828 Time:  1200     Latitude:  17.30        Longitude:  -64.20      Windspeed:  60MPH       Pressure:  999mb
Storm Name:  DORIAN     Date:  20190828 Time:  1530     Latitude:  17.80        Longitude:  -64.60      Windspeed:  65MPH       Pressure:  995mb
Storm Name:  DORIAN     Date:  20190828 Time:  1800     Latitude:  18.40        Longitude:  -65.10      Windspeed:  70MPH       Pressure:  993mb
Storm Name:  DORIAN     Date:  20190829 Time:  0        Latitude:  19.20        Longitude:  -65.70      Windspeed:  75MPH       Pressure:  989mb
Storm Name:  DORIAN     Date:  20190829 Time:  600      Latitude:  20.00        Longitude:  -66.30      Windspeed:  75MPH       Pressure:  988mb
Storm Name:  DORIAN     Date:  20190829 Time:  1200     Latitude:  21.00        Longitude:  -66.90      Windspeed:  75MPH       Pressure:  986mb
Storm Name:  DORIAN     Date:  20190829 Time:  1800     Latitude:  22.00        Longitude:  -67.40      Windspeed:  75MPH       Pressure:  983mb
Storm Name:  DORIAN     Date:  20190830 Time:  0        Latitude:  22.80        Longitude:  -68.00      Windspeed:  80MPH       Pressure:  978mb
Storm Name:  DORIAN     Date:  20190830 Time:  600      Latitude:  23.50        Longitude:  -68.80      Windspeed:  90MPH       Pressure:  978mb
Storm Name:  DORIAN     Date:  20190830 Time:  1200     Latitude:  24.30        Longitude:  -69.50      Windspeed:  95MPH       Pressure:  972mb
Storm Name:  DORIAN     Date:  20190830 Time:  1800     Latitude:  24.80        Longitude:  -70.30      Windspeed:  100MPH      Pressure:  968mb
Storm Name:  DORIAN     Date:  20190831 Time:  0        Latitude:  25.30        Longitude:  -71.10      Windspeed:  115MPH      Pressure:  949mb
Storm Name:  DORIAN     Date:  20190831 Time:  600      Latitude:  25.60        Longitude:  -72.10      Windspeed:  120MPH      Pressure:  947mb
Storm Name:  DORIAN     Date:  20190831 Time:  1200     Latitude:  25.90        Longitude:  -73.00      Windspeed:  125MPH      Pressure:  944mb
Storm Name:  DORIAN     Date:  20190831 Time:  1800     Latitude:  26.10        Longitude:  -74.00      Windspeed:  130MPH      Pressure:  942mb
Storm Name:  DORIAN     Date:  20190901 Time:  0        Latitude:  26.30        Longitude:  -74.70      Windspeed:  135MPH      Pressure:  939mb
Storm Name:  DORIAN     Date:  20190901 Time:  600      Latitude:  26.40        Longitude:  -75.60      Windspeed:  145MPH      Pressure:  934mb
Storm Name:  DORIAN     Date:  20190901 Time:  1200     Latitude:  26.50        Longitude:  -76.50      Windspeed:  155MPH      Pressure:  927mb
Storm Name:  DORIAN     Date:  20190901 Time:  1640     Latitude:  26.50        Longitude:  -77.00      Windspeed:  160MPH      Pressure:  910mb
Storm Name:  DORIAN     Date:  20190901 Time:  1800     Latitude:  26.50        Longitude:  -77.10      Windspeed:  160MPH      Pressure:  910mb
Storm Name:  DORIAN     Date:  20190902 Time:  0        Latitude:  26.60        Longitude:  -77.70      Windspeed:  155MPH      Pressure:  914mb
Storm Name:  DORIAN     Date:  20190902 Time:  215      Latitude:  26.60        Longitude:  -77.80      Windspeed:  155MPH      Pressure:  914mb
Storm Name:  DORIAN     Date:  20190902 Time:  600      Latitude:  26.60        Longitude:  -78.00      Windspeed:  145MPH      Pressure:  916mb
Storm Name:  DORIAN     Date:  20190902 Time:  1200     Latitude:  26.70        Longitude:  -78.30      Windspeed:  135MPH      Pressure:  927mb
Storm Name:  DORIAN     Date:  20190902 Time:  1800     Latitude:  26.80        Longitude:  -78.40      Windspeed:  125MPH      Pressure:  938mb
Storm Name:  DORIAN     Date:  20190903 Time:  0        Latitude:  26.90        Longitude:  -78.50      Windspeed:  115MPH      Pressure:  944mb
Storm Name:  DORIAN     Date:  20190903 Time:  600      Latitude:  27.00        Longitude:  -78.50      Windspeed:  105MPH      Pressure:  950mb
Storm Name:  DORIAN     Date:  20190903 Time:  1200     Latitude:  27.10        Longitude:  -78.50      Windspeed:  100MPH      Pressure:  954mb
Storm Name:  DORIAN     Date:  20190903 Time:  1800     Latitude:  27.60        Longitude:  -78.60      Windspeed:  95MPH       Pressure:  959mb
Storm Name:  DORIAN     Date:  20190904 Time:  0        Latitude:  28.10        Longitude:  -78.80      Windspeed:  90MPH       Pressure:  959mb
Storm Name:  DORIAN     Date:  20190904 Time:  600      Latitude:  28.80        Longitude:  -79.20      Windspeed:  90MPH       Pressure:  964mb
Storm Name:  DORIAN     Date:  20190904 Time:  1200     Latitude:  29.50        Longitude:  -79.60      Windspeed:  90MPH       Pressure:  963mb
Storm Name:  DORIAN     Date:  20190904 Time:  1800     Latitude:  30.10        Longitude:  -79.70      Windspeed:  95MPH       Pressure:  960mb
Storm Name:  DORIAN     Date:  20190905 Time:  0        Latitude:  30.70        Longitude:  -79.70      Windspeed:  100MPH      Pressure:  955mb
Storm Name:  DORIAN     Date:  20190905 Time:  600      Latitude:  31.40        Longitude:  -79.60      Windspeed:  100MPH      Pressure:  958mb
Storm Name:  DORIAN     Date:  20190905 Time:  1200     Latitude:  32.10        Longitude:  -79.20      Windspeed:  100MPH      Pressure:  958mb
Storm Name:  DORIAN     Date:  20190905 Time:  1800     Latitude:  32.70        Longitude:  -78.90      Windspeed:  95MPH       Pressure:  958mb
Storm Name:  DORIAN     Date:  20190906 Time:  0        Latitude:  33.40        Longitude:  -77.90      Windspeed:  90MPH       Pressure:  956mb
Storm Name:  DORIAN     Date:  20190906 Time:  600      Latitude:  34.10        Longitude:  -76.90      Windspeed:  90MPH       Pressure:  956mb
Storm Name:  DORIAN     Date:  20190906 Time:  1200     Latitude:  35.10        Longitude:  -75.70      Windspeed:  85MPH       Pressure:  956mb
Storm Name:  DORIAN     Date:  20190906 Time:  1230     Latitude:  35.20        Longitude:  -75.60      Windspeed:  85MPH       Pressure:  956mb
Storm Name:  DORIAN     Date:  20190906 Time:  1800     Latitude:  36.20        Longitude:  -73.70      Windspeed:  85MPH       Pressure:  956mb
Storm Name:  DORIAN     Date:  20190907 Time:  0        Latitude:  37.40        Longitude:  -71.20      Windspeed:  85MPH       Pressure:  956mb
Storm Name:  DORIAN     Date:  20190907 Time:  600      Latitude:  38.90        Longitude:  -68.90      Windspeed:  85MPH       Pressure:  955mb
Storm Name:  DORIAN     Date:  20190907 Time:  1200     Latitude:  40.80        Longitude:  -66.90      Windspeed:  85MPH       Pressure:  954mb
Storm Name:  DORIAN     Date:  20190907 Time:  1800     Latitude:  42.80        Longitude:  -64.60      Windspeed:  80MPH       Pressure:  954mb
Storm Name:  DORIAN     Date:  20190908 Time:  0        Latitude:  45.20        Longitude:  -62.90      Windspeed:  80MPH       Pressure:  956mb
Storm Name:  DORIAN     Date:  20190908 Time:  600      Latitude:  47.60        Longitude:  -61.90      Windspeed:  75MPH       Pressure:  960mb
Storm Name:  DORIAN     Date:  20190908 Time:  1200     Latitude:  49.40        Longitude:  -60.40      Windspeed:  70MPH       Pressure:  962mb
Storm Name:  DORIAN     Date:  20190908 Time:  1800     Latitude:  50.80        Longitude:  -57.90      Windspeed:  60MPH       Pressure:  966mb
Storm Name:  DORIAN     Date:  20190909 Time:  0        Latitude:  51.60        Longitude:  -54.80      Windspeed:  50MPH       Pressure:  980mb
Storm Name:  ERIN       Date:  20190826 Time:  1200     Latitude:  31.70        Longitude:  -72.70      Windspeed:  30MPH       Pressure:  1010mb
Storm Name:  ERIN       Date:  20190826 Time:  1800     Latitude:  31.50        Longitude:  -72.50      Windspeed:  30MPH       Pressure:  1010mb
Storm Name:  ERIN       Date:  20190827 Time:  0        Latitude:  31.20        Longitude:  -72.20      Windspeed:  30MPH       Pressure:  1010mb
Storm Name:  ERIN       Date:  20190827 Time:  600      Latitude:  30.90        Longitude:  -71.70      Windspeed:  30MPH       Pressure:  1010mb
Storm Name:  ERIN       Date:  20190827 Time:  1200     Latitude:  30.90        Longitude:  -71.10      Windspeed:  30MPH       Pressure:  1008mb
Storm Name:  ERIN       Date:  20190827 Time:  1800     Latitude:  31.30        Longitude:  -71.60      Windspeed:  35MPH       Pressure:  1005mb
Storm Name:  ERIN       Date:  20190828 Time:  0        Latitude:  31.70        Longitude:  -72.00      Windspeed:  35MPH       Pressure:  1004mb
Storm Name:  ERIN       Date:  20190828 Time:  600      Latitude:  32.20        Longitude:  -72.40      Windspeed:  35MPH       Pressure:  1002mb
Storm Name:  ERIN       Date:  20190828 Time:  1200     Latitude:  33.00        Longitude:  -72.90      Windspeed:  35MPH       Pressure:  1002mb
Storm Name:  ERIN       Date:  20190828 Time:  1800     Latitude:  33.90        Longitude:  -73.00      Windspeed:  30MPH       Pressure:  1003mb
Storm Name:  ERIN       Date:  20190829 Time:  0        Latitude:  34.80        Longitude:  -72.60      Windspeed:  30MPH       Pressure:  1003mb
Storm Name:  ERIN       Date:  20190829 Time:  600      Latitude:  35.60        Longitude:  -72.10      Windspeed:  30MPH       Pressure:  1003mb
Storm Name:  ERIN       Date:  20190829 Time:  1200     Latitude:  36.90        Longitude:  -70.90      Windspeed:  35MPH       Pressure:  1002mb
Storm Name:  ERIN       Date:  20190829 Time:  1800     Latitude:  38.50        Longitude:  -68.50      Windspeed:  35MPH       Pressure:  1002mb
Storm Name:  FERNAND    Date:  20190903 Time:  600      Latitude:  23.60        Longitude:  -94.00      Windspeed:  30MPH       Pressure:  1006mb
Storm Name:  FERNAND    Date:  20190903 Time:  1200     Latitude:  23.40        Longitude:  -94.70      Windspeed:  35MPH       Pressure:  1004mb
Storm Name:  FERNAND    Date:  20190903 Time:  1800     Latitude:  23.20        Longitude:  -95.40      Windspeed:  40MPH       Pressure:  1002mb
Storm Name:  FERNAND    Date:  20190904 Time:  0        Latitude:  23.10        Longitude:  -96.10      Windspeed:  45MPH       Pressure:  1000mb
Storm Name:  FERNAND    Date:  20190904 Time:  600      Latitude:  23.40        Longitude:  -96.80      Windspeed:  45MPH       Pressure:  1000mb
Storm Name:  FERNAND    Date:  20190904 Time:  1200     Latitude:  24.00        Longitude:  -97.20      Windspeed:  40MPH       Pressure:  1003mb
Storm Name:  FERNAND    Date:  20190904 Time:  1530     Latitude:  24.20        Longitude:  -97.70      Windspeed:  40MPH       Pressure:  1003mb
Storm Name:  FERNAND    Date:  20190904 Time:  1800     Latitude:  24.30        Longitude:  -98.00      Windspeed:  30MPH       Pressure:  1004mb
Storm Name:  FERNAND    Date:  20190905 Time:  0        Latitude:  24.70        Longitude:  -98.60      Windspeed:  25MPH       Pressure:  1007mb
Storm Name:  GABRIELLE  Date:  20190903 Time:  0        Latitude:  16.10        Longitude:  -30.10      Windspeed:  25MPH       Pressure:  1007mb
Storm Name:  GABRIELLE  Date:  20190903 Time:  600      Latitude:  16.80        Longitude:  -30.90      Windspeed:  25MPH       Pressure:  1007mb
Storm Name:  GABRIELLE  Date:  20190903 Time:  1200     Latitude:  17.50        Longitude:  -31.60      Windspeed:  25MPH       Pressure:  1007mb
Storm Name:  GABRIELLE  Date:  20190903 Time:  1800     Latitude:  18.10        Longitude:  -32.10      Windspeed:  30MPH       Pressure:  1006mb
Storm Name:  GABRIELLE  Date:  20190904 Time:  0        Latitude:  18.70        Longitude:  -32.60      Windspeed:  35MPH       Pressure:  1005mb
Storm Name:  GABRIELLE  Date:  20190904 Time:  600      Latitude:  19.50        Longitude:  -33.20      Windspeed:  40MPH       Pressure:  1004mb
Storm Name:  GABRIELLE  Date:  20190904 Time:  1200     Latitude:  20.10        Longitude:  -33.60      Windspeed:  45MPH       Pressure:  1003mb
Storm Name:  GABRIELLE  Date:  20190904 Time:  1800     Latitude:  20.50        Longitude:  -33.70      Windspeed:  45MPH       Pressure:  1002mb
Storm Name:  GABRIELLE  Date:  20190905 Time:  0        Latitude:  20.80        Longitude:  -33.90      Windspeed:  45MPH       Pressure:  1002mb
Storm Name:  GABRIELLE  Date:  20190905 Time:  600      Latitude:  21.50        Longitude:  -34.50      Windspeed:  45MPH       Pressure:  1001mb
Storm Name:  GABRIELLE  Date:  20190905 Time:  1200     Latitude:  22.30        Longitude:  -35.20      Windspeed:  45MPH       Pressure:  1000mb
Storm Name:  GABRIELLE  Date:  20190905 Time:  1800     Latitude:  22.90        Longitude:  -35.60      Windspeed:  40MPH       Pressure:  1002mb
Storm Name:  GABRIELLE  Date:  20190906 Time:  0        Latitude:  23.80        Longitude:  -36.20      Windspeed:  35MPH       Pressure:  1004mb
Storm Name:  GABRIELLE  Date:  20190906 Time:  600      Latitude:  25.00        Longitude:  -37.10      Windspeed:  35MPH       Pressure:  1005mb
Storm Name:  GABRIELLE  Date:  20190906 Time:  1200     Latitude:  26.20        Longitude:  -38.00      Windspeed:  40MPH       Pressure:  1004mb
Storm Name:  GABRIELLE  Date:  20190906 Time:  1800     Latitude:  27.40        Longitude:  -39.00      Windspeed:  45MPH       Pressure:  1002mb
Storm Name:  GABRIELLE  Date:  20190907 Time:  0        Latitude:  29.00        Longitude:  -40.10      Windspeed:  50MPH       Pressure:  999mb
Storm Name:  GABRIELLE  Date:  20190907 Time:  600      Latitude:  30.50        Longitude:  -41.60      Windspeed:  45MPH       Pressure:  1002mb
Storm Name:  GABRIELLE  Date:  20190907 Time:  1200     Latitude:  31.00        Longitude:  -43.90      Windspeed:  45MPH       Pressure:  1003mb
Storm Name:  GABRIELLE  Date:  20190907 Time:  1800     Latitude:  31.50        Longitude:  -45.80      Windspeed:  45MPH       Pressure:  1003mb
Storm Name:  GABRIELLE  Date:  20190908 Time:  0        Latitude:  31.80        Longitude:  -47.40      Windspeed:  45MPH       Pressure:  1002mb
Storm Name:  GABRIELLE  Date:  20190908 Time:  600      Latitude:  32.30        Longitude:  -48.40      Windspeed:  50MPH       Pressure:  1000mb
Storm Name:  GABRIELLE  Date:  20190908 Time:  1200     Latitude:  33.20        Longitude:  -49.00      Windspeed:  50MPH       Pressure:  999mb
Storm Name:  GABRIELLE  Date:  20190908 Time:  1800     Latitude:  34.50        Longitude:  -49.30      Windspeed:  55MPH       Pressure:  995mb
Storm Name:  GABRIELLE  Date:  20190909 Time:  0        Latitude:  35.80        Longitude:  -49.30      Windspeed:  55MPH       Pressure:  995mb
Storm Name:  GABRIELLE  Date:  20190909 Time:  600      Latitude:  37.10        Longitude:  -48.90      Windspeed:  50MPH       Pressure:  996mb
Storm Name:  GABRIELLE  Date:  20190909 Time:  1200     Latitude:  38.40        Longitude:  -48.00      Windspeed:  50MPH       Pressure:  997mb
Storm Name:  GABRIELLE  Date:  20190909 Time:  1800     Latitude:  40.00        Longitude:  -46.30      Windspeed:  50MPH       Pressure:  998mb
Storm Name:  GABRIELLE  Date:  20190910 Time:  0        Latitude:  41.40        Longitude:  -44.20      Windspeed:  45MPH       Pressure:  999mb
Storm Name:  GABRIELLE  Date:  20190910 Time:  600      Latitude:  42.40        Longitude:  -41.70      Windspeed:  45MPH       Pressure:  999mb
Storm Name:  GABRIELLE  Date:  20190910 Time:  1200     Latitude:  43.30        Longitude:  -39.10      Windspeed:  45MPH       Pressure:  999mb
Storm Name:  GABRIELLE  Date:  20190910 Time:  1800     Latitude:  44.10        Longitude:  -36.40      Windspeed:  45MPH       Pressure:  1000mb
Storm Name:  GABRIELLE  Date:  20190911 Time:  0        Latitude:  45.50        Longitude:  -33.50      Windspeed:  40MPH       Pressure:  1002mb
Storm Name:  GABRIELLE  Date:  20190911 Time:  600      Latitude:  47.00        Longitude:  -30.00      Windspeed:  40MPH       Pressure:  1003mb
Storm Name:  GABRIELLE  Date:  20190911 Time:  1200     Latitude:  49.00        Longitude:  -26.40      Windspeed:  35MPH       Pressure:  1005mb
Storm Name:  HUMBERTO   Date:  20190912 Time:  1200     Latitude:  23.00        Longitude:  -74.20      Windspeed:  25MPH       Pressure:  1010mb
Storm Name:  HUMBERTO   Date:  20190912 Time:  1800     Latitude:  23.40        Longitude:  -74.30      Windspeed:  25MPH       Pressure:  1010mb
Storm Name:  HUMBERTO   Date:  20190913 Time:  0        Latitude:  23.80        Longitude:  -74.30      Windspeed:  25MPH       Pressure:  1009mb
Storm Name:  HUMBERTO   Date:  20190913 Time:  600      Latitude:  24.20        Longitude:  -74.40      Windspeed:  25MPH       Pressure:  1009mb
Storm Name:  HUMBERTO   Date:  20190913 Time:  1200     Latitude:  24.70        Longitude:  -74.50      Windspeed:  30MPH       Pressure:  1008mb
Storm Name:  HUMBERTO   Date:  20190913 Time:  1800     Latitude:  25.20        Longitude:  -74.70      Windspeed:  30MPH       Pressure:  1008mb
Storm Name:  HUMBERTO   Date:  20190914 Time:  0        Latitude:  25.60        Longitude:  -75.20      Windspeed:  35MPH       Pressure:  1007mb
Storm Name:  HUMBERTO   Date:  20190914 Time:  600      Latitude:  26.00        Longitude:  -75.90      Windspeed:  35MPH       Pressure:  1006mb
Storm Name:  HUMBERTO   Date:  20190914 Time:  1200     Latitude:  26.50        Longitude:  -76.50      Windspeed:  40MPH       Pressure:  1004mb
Storm Name:  HUMBERTO   Date:  20190914 Time:  1800     Latitude:  27.00        Longitude:  -77.00      Windspeed:  45MPH       Pressure:  1003mb
Storm Name:  HUMBERTO   Date:  20190915 Time:  0        Latitude:  27.50        Longitude:  -77.30      Windspeed:  50MPH       Pressure:  998mb
Storm Name:  HUMBERTO   Date:  20190915 Time:  600      Latitude:  28.00        Longitude:  -77.60      Windspeed:  50MPH       Pressure:  997mb
Storm Name:  HUMBERTO   Date:  20190915 Time:  1200     Latitude:  28.60        Longitude:  -77.90      Windspeed:  55MPH       Pressure:  995mb
Storm Name:  HUMBERTO   Date:  20190915 Time:  1800     Latitude:  29.10        Longitude:  -78.10      Windspeed:  60MPH       Pressure:  993mb
Storm Name:  HUMBERTO   Date:  20190916 Time:  0        Latitude:  29.20        Longitude:  -77.80      Windspeed:  65MPH       Pressure:  987mb
Storm Name:  HUMBERTO   Date:  20190916 Time:  600      Latitude:  29.50        Longitude:  -77.30      Windspeed:  70MPH       Pressure:  982mb
Storm Name:  HUMBERTO   Date:  20190916 Time:  1200     Latitude:  29.80        Longitude:  -76.70      Windspeed:  75MPH       Pressure:  979mb
Storm Name:  HUMBERTO   Date:  20190916 Time:  1800     Latitude:  30.10        Longitude:  -76.10      Windspeed:  75MPH       Pressure:  975mb
Storm Name:  HUMBERTO   Date:  20190917 Time:  0        Latitude:  30.30        Longitude:  -75.40      Windspeed:  80MPH       Pressure:  966mb
Storm Name:  HUMBERTO   Date:  20190917 Time:  600      Latitude:  30.50        Longitude:  -74.70      Windspeed:  85MPH       Pressure:  964mb
Storm Name:  HUMBERTO   Date:  20190917 Time:  1200     Latitude:  30.70        Longitude:  -73.80      Windspeed:  90MPH       Pressure:  961mb
Storm Name:  HUMBERTO   Date:  20190917 Time:  1800     Latitude:  30.90        Longitude:  -72.90      Windspeed:  95MPH       Pressure:  956mb
Storm Name:  HUMBERTO   Date:  20190918 Time:  0        Latitude:  31.20        Longitude:  -71.60      Windspeed:  100MPH      Pressure:  952mb
Storm Name:  HUMBERTO   Date:  20190918 Time:  600      Latitude:  31.50        Longitude:  -70.30      Windspeed:  105MPH      Pressure:  951mb
Storm Name:  HUMBERTO   Date:  20190918 Time:  1200     Latitude:  32.00        Longitude:  -68.80      Windspeed:  105MPH      Pressure:  951mb
Storm Name:  HUMBERTO   Date:  20190918 Time:  1800     Latitude:  32.50        Longitude:  -67.20      Windspeed:  110MPH      Pressure:  950mb
Storm Name:  HUMBERTO   Date:  20190919 Time:  0        Latitude:  33.20        Longitude:  -65.00      Windspeed:  110MPH      Pressure:  950mb
Storm Name:  HUMBERTO   Date:  20190919 Time:  300      Latitude:  33.80        Longitude:  -64.00      Windspeed:  110MPH      Pressure:  950mb
Storm Name:  HUMBERTO   Date:  20190919 Time:  600      Latitude:  34.50        Longitude:  -62.90      Windspeed:  105MPH      Pressure:  951mb
Storm Name:  HUMBERTO   Date:  20190919 Time:  1200     Latitude:  36.00        Longitude:  -60.80      Windspeed:  95MPH       Pressure:  955mb
Storm Name:  HUMBERTO   Date:  20190919 Time:  1800     Latitude:  37.70        Longitude:  -59.30      Windspeed:  80MPH       Pressure:  961mb
Storm Name:  HUMBERTO   Date:  20190920 Time:  0        Latitude:  39.10        Longitude:  -58.50      Windspeed:  70MPH       Pressure:  967mb
Storm Name:  HUMBERTO   Date:  20190920 Time:  600      Latitude:  40.40        Longitude:  -58.00      Windspeed:  60MPH       Pressure:  972mb
Storm Name:  HUMBERTO   Date:  20190920 Time:  1200     Latitude:  41.50        Longitude:  -57.50      Windspeed:  50MPH       Pressure:  977mb
Storm Name:  JERRY      Date:  20190917 Time:  0        Latitude:  12.60        Longitude:  -42.60      Windspeed:  25MPH       Pressure:  1009mb
Storm Name:  JERRY      Date:  20190917 Time:  600      Latitude:  12.80        Longitude:  -43.50      Windspeed:  30MPH       Pressure:  1007mb
Storm Name:  JERRY      Date:  20190917 Time:  1200     Latitude:  13.00        Longitude:  -44.40      Windspeed:  30MPH       Pressure:  1007mb
Storm Name:  JERRY      Date:  20190917 Time:  1800     Latitude:  13.30        Longitude:  -45.40      Windspeed:  30MPH       Pressure:  1007mb
Storm Name:  JERRY      Date:  20190918 Time:  0        Latitude:  13.60        Longitude:  -46.30      Windspeed:  30MPH       Pressure:  1006mb
Storm Name:  JERRY      Date:  20190918 Time:  600      Latitude:  14.00        Longitude:  -47.40      Windspeed:  35MPH       Pressure:  1005mb
Storm Name:  JERRY      Date:  20190918 Time:  1200     Latitude:  14.40        Longitude:  -48.60      Windspeed:  45MPH       Pressure:  1002mb
Storm Name:  JERRY      Date:  20190918 Time:  1800     Latitude:  14.80        Longitude:  -49.90      Windspeed:  50MPH       Pressure:  1000mb
Storm Name:  JERRY      Date:  20190919 Time:  0        Latitude:  15.20        Longitude:  -51.20      Windspeed:  55MPH       Pressure:  998mb
Storm Name:  JERRY      Date:  20190919 Time:  600      Latitude:  15.80        Longitude:  -52.50      Windspeed:  60MPH       Pressure:  996mb
Storm Name:  JERRY      Date:  20190919 Time:  1200     Latitude:  16.50        Longitude:  -53.80      Windspeed:  70MPH       Pressure:  990mb
Storm Name:  JERRY      Date:  20190919 Time:  1800     Latitude:  17.20        Longitude:  -55.20      Windspeed:  80MPH       Pressure:  981mb
Storm Name:  JERRY      Date:  20190920 Time:  0        Latitude:  17.70        Longitude:  -56.60      Windspeed:  90MPH       Pressure:  976mb
Storm Name:  JERRY      Date:  20190920 Time:  600      Latitude:  18.10        Longitude:  -58.10      Windspeed:  85MPH       Pressure:  983mb
Storm Name:  JERRY      Date:  20190920 Time:  1200     Latitude:  18.50        Longitude:  -59.70      Windspeed:  75MPH       Pressure:  990mb
Storm Name:  JERRY      Date:  20190920 Time:  1800     Latitude:  19.20        Longitude:  -61.20      Windspeed:  65MPH       Pressure:  991mb
Storm Name:  JERRY      Date:  20190921 Time:  0        Latitude:  20.10        Longitude:  -62.40      Windspeed:  60MPH       Pressure:  993mb
Storm Name:  JERRY      Date:  20190921 Time:  600      Latitude:  21.00        Longitude:  -63.50      Windspeed:  55MPH       Pressure:  995mb
Storm Name:  JERRY      Date:  20190921 Time:  1200     Latitude:  21.70        Longitude:  -64.50      Windspeed:  55MPH       Pressure:  998mb
Storm Name:  JERRY      Date:  20190921 Time:  1800     Latitude:  22.50        Longitude:  -65.50      Windspeed:  55MPH       Pressure:  998mb
Storm Name:  JERRY      Date:  20190922 Time:  0        Latitude:  23.60        Longitude:  -66.10      Windspeed:  55MPH       Pressure:  998mb
Storm Name:  JERRY      Date:  20190922 Time:  600      Latitude:  24.50        Longitude:  -66.50      Windspeed:  55MPH       Pressure:  998mb
Storm Name:  JERRY      Date:  20190922 Time:  1200     Latitude:  25.40        Longitude:  -66.60      Windspeed:  55MPH       Pressure:  997mb
Storm Name:  JERRY      Date:  20190922 Time:  1800     Latitude:  26.30        Longitude:  -66.80      Windspeed:  55MPH       Pressure:  994mb
Storm Name:  JERRY      Date:  20190923 Time:  0        Latitude:  27.00        Longitude:  -67.20      Windspeed:  55MPH       Pressure:  993mb
Storm Name:  JERRY      Date:  20190923 Time:  600      Latitude:  27.40        Longitude:  -67.70      Windspeed:  55MPH       Pressure:  992mb
Storm Name:  JERRY      Date:  20190923 Time:  1200     Latitude:  27.70        Longitude:  -68.00      Windspeed:  55MPH       Pressure:  991mb
Storm Name:  JERRY      Date:  20190923 Time:  1800     Latitude:  28.20        Longitude:  -68.30      Windspeed:  55MPH       Pressure:  991mb
Storm Name:  JERRY      Date:  20190924 Time:  0        Latitude:  28.90        Longitude:  -68.60      Windspeed:  55MPH       Pressure:  991mb
Storm Name:  JERRY      Date:  20190924 Time:  600      Latitude:  29.70        Longitude:  -68.90      Windspeed:  50MPH       Pressure:  991mb
Storm Name:  JERRY      Date:  20190924 Time:  1200     Latitude:  30.50        Longitude:  -69.10      Windspeed:  45MPH       Pressure:  991mb
Storm Name:  JERRY      Date:  20190924 Time:  1800     Latitude:  30.90        Longitude:  -69.10      Windspeed:  45MPH       Pressure:  993mb
Storm Name:  JERRY      Date:  20190925 Time:  0        Latitude:  31.30        Longitude:  -68.90      Windspeed:  40MPH       Pressure:  996mb
Storm Name:  JERRY      Date:  20190925 Time:  600      Latitude:  31.60        Longitude:  -68.40      Windspeed:  40MPH       Pressure:  997mb
Storm Name:  JERRY      Date:  20190925 Time:  1200     Latitude:  31.80        Longitude:  -67.40      Windspeed:  35MPH       Pressure:  999mb
Storm Name:  JERRY      Date:  20190925 Time:  1800     Latitude:  32.00        Longitude:  -66.10      Windspeed:  30MPH       Pressure:  1000mb
Storm Name:  JERRY      Date:  20190926 Time:  0        Latitude:  32.30        Longitude:  -64.90      Windspeed:  25MPH       Pressure:  1001mb
Storm Name:  JERRY      Date:  20190926 Time:  600      Latitude:  32.90        Longitude:  -63.80      Windspeed:  25MPH       Pressure:  1003mb
Storm Name:  JERRY      Date:  20190926 Time:  1200     Latitude:  33.60        Longitude:  -62.90      Windspeed:  25MPH       Pressure:  1005mb
Storm Name:  JERRY      Date:  20190926 Time:  1800     Latitude:  34.10        Longitude:  -62.20      Windspeed:  25MPH       Pressure:  1005mb
Storm Name:  JERRY      Date:  20190927 Time:  0        Latitude:  34.60        Longitude:  -61.40      Windspeed:  25MPH       Pressure:  1006mb
Storm Name:  JERRY      Date:  20190927 Time:  600      Latitude:  35.00        Longitude:  -60.50      Windspeed:  25MPH       Pressure:  1006mb
Storm Name:  JERRY      Date:  20190927 Time:  1200     Latitude:  35.30        Longitude:  -59.40      Windspeed:  25MPH       Pressure:  1006mb
Storm Name:  JERRY      Date:  20190927 Time:  1800     Latitude:  35.30        Longitude:  -58.70      Windspeed:  25MPH       Pressure:  1006mb
Storm Name:  JERRY      Date:  20190928 Time:  0        Latitude:  35.10        Longitude:  -58.30      Windspeed:  20MPH       Pressure:  1007mb
Storm Name:  IMELDA     Date:  20190917 Time:  1200     Latitude:  28.30        Longitude:  -95.70      Windspeed:  30MPH       Pressure:  1008mb
Storm Name:  IMELDA     Date:  20190917 Time:  1500     Latitude:  28.60        Longitude:  -95.50      Windspeed:  35MPH       Pressure:  1006mb
Storm Name:  IMELDA     Date:  20190917 Time:  1745     Latitude:  28.90        Longitude:  -95.40      Windspeed:  40MPH       Pressure:  1003mb
Storm Name:  IMELDA     Date:  20190917 Time:  1800     Latitude:  29.00        Longitude:  -95.40      Windspeed:  40MPH       Pressure:  1003mb
Storm Name:  IMELDA     Date:  20190918 Time:  0        Latitude:  29.50        Longitude:  -95.50      Windspeed:  30MPH       Pressure:  1007mb
Storm Name:  IMELDA     Date:  20190918 Time:  600      Latitude:  29.90        Longitude:  -95.60      Windspeed:  30MPH       Pressure:  1007mb
Storm Name:  IMELDA     Date:  20190918 Time:  1200     Latitude:  30.40        Longitude:  -95.50      Windspeed:  30MPH       Pressure:  1007mb
Storm Name:  IMELDA     Date:  20190918 Time:  1800     Latitude:  30.60        Longitude:  -95.00      Windspeed:  30MPH       Pressure:  1007mb
Storm Name:  IMELDA     Date:  20190919 Time:  0        Latitude:  31.10        Longitude:  -94.80      Windspeed:  25MPH       Pressure:  1009mb
Storm Name:  KAREN      Date:  20190922 Time:  0        Latitude:  11.50        Longitude:  -58.80      Windspeed:  30MPH       Pressure:  1007mb
Storm Name:  KAREN      Date:  20190922 Time:  600      Latitude:  11.80        Longitude:  -59.90      Windspeed:  35MPH       Pressure:  1007mb
Storm Name:  KAREN      Date:  20190922 Time:  1200     Latitude:  12.10        Longitude:  -61.10      Windspeed:  35MPH       Pressure:  1007mb
Storm Name:  KAREN      Date:  20190922 Time:  1800     Latitude:  12.50        Longitude:  -62.20      Windspeed:  35MPH       Pressure:  1007mb
Storm Name:  KAREN      Date:  20190923 Time:  0        Latitude:  13.00        Longitude:  -63.20      Windspeed:  35MPH       Pressure:  1007mb
Storm Name:  KAREN      Date:  20190923 Time:  600      Latitude:  13.70        Longitude:  -64.10      Windspeed:  30MPH       Pressure:  1007mb
Storm Name:  KAREN      Date:  20190923 Time:  1200     Latitude:  14.40        Longitude:  -64.80      Windspeed:  30MPH       Pressure:  1007mb
Storm Name:  KAREN      Date:  20190923 Time:  1800     Latitude:  15.10        Longitude:  -65.40      Windspeed:  30MPH       Pressure:  1007mb
Storm Name:  KAREN      Date:  20190924 Time:  0        Latitude:  15.70        Longitude:  -65.70      Windspeed:  30MPH       Pressure:  1007mb
Storm Name:  KAREN      Date:  20190924 Time:  600      Latitude:  16.40        Longitude:  -65.80      Windspeed:  35MPH       Pressure:  1006mb
Storm Name:  KAREN      Date:  20190924 Time:  1200     Latitude:  17.00        Longitude:  -65.80      Windspeed:  35MPH       Pressure:  1006mb
Storm Name:  KAREN      Date:  20190924 Time:  1800     Latitude:  17.70        Longitude:  -65.60      Windspeed:  40MPH       Pressure:  1004mb
Storm Name:  KAREN      Date:  20190924 Time:  2200     Latitude:  18.10        Longitude:  -65.40      Windspeed:  40MPH       Pressure:  1004mb
Storm Name:  KAREN      Date:  20190924 Time:  2300     Latitude:  18.30        Longitude:  -65.30      Windspeed:  40MPH       Pressure:  1004mb
Storm Name:  KAREN      Date:  20190925 Time:  0        Latitude:  18.50        Longitude:  -65.20      Windspeed:  40MPH       Pressure:  1003mb
Storm Name:  KAREN      Date:  20190925 Time:  600      Latitude:  19.70        Longitude:  -65.00      Windspeed:  40MPH       Pressure:  1003mb
Storm Name:  KAREN      Date:  20190925 Time:  1200     Latitude:  21.00        Longitude:  -64.80      Windspeed:  35MPH       Pressure:  1004mb
Storm Name:  KAREN      Date:  20190925 Time:  1800     Latitude:  22.30        Longitude:  -64.50      Windspeed:  35MPH       Pressure:  1004mb
Storm Name:  KAREN      Date:  20190926 Time:  0        Latitude:  23.60        Longitude:  -64.20      Windspeed:  35MPH       Pressure:  1004mb
Storm Name:  KAREN      Date:  20190926 Time:  600      Latitude:  24.80        Longitude:  -64.00      Windspeed:  35MPH       Pressure:  1004mb
Storm Name:  KAREN      Date:  20190926 Time:  1200     Latitude:  25.90        Longitude:  -63.70      Windspeed:  40MPH       Pressure:  1004mb
Storm Name:  KAREN      Date:  20190926 Time:  1800     Latitude:  26.90        Longitude:  -63.10      Windspeed:  40MPH       Pressure:  1005mb
Storm Name:  KAREN      Date:  20190927 Time:  0        Latitude:  27.70        Longitude:  -62.30      Windspeed:  35MPH       Pressure:  1005mb
Storm Name:  KAREN      Date:  20190927 Time:  600      Latitude:  28.30        Longitude:  -61.20      Windspeed:  35MPH       Pressure:  1005mb
Storm Name:  KAREN      Date:  20190927 Time:  1200     Latitude:  28.80        Longitude:  -60.00      Windspeed:  30MPH       Pressure:  1006mb
Storm Name:  LORENZO    Date:  20190922 Time:  1800     Latitude:  10.90        Longitude:  -18.80      Windspeed:  25MPH       Pressure:  1008mb
Storm Name:  LORENZO    Date:  20190923 Time:  0        Latitude:  11.00        Longitude:  -20.40      Windspeed:  30MPH       Pressure:  1007mb
Storm Name:  LORENZO    Date:  20190923 Time:  600      Latitude:  11.00        Longitude:  -21.90      Windspeed:  35MPH       Pressure:  1007mb
Storm Name:  LORENZO    Date:  20190923 Time:  1200     Latitude:  11.10        Longitude:  -23.30      Windspeed:  40MPH       Pressure:  1006mb
Storm Name:  LORENZO    Date:  20190923 Time:  1800     Latitude:  11.20        Longitude:  -24.60      Windspeed:  45MPH       Pressure:  1004mb
Storm Name:  LORENZO    Date:  20190924 Time:  0        Latitude:  11.40        Longitude:  -25.90      Windspeed:  50MPH       Pressure:  1002mb
Storm Name:  LORENZO    Date:  20190924 Time:  600      Latitude:  11.80        Longitude:  -27.20      Windspeed:  55MPH       Pressure:  999mb
Storm Name:  LORENZO    Date:  20190924 Time:  1200     Latitude:  12.20        Longitude:  -28.70      Windspeed:  55MPH       Pressure:  997mb
Storm Name:  LORENZO    Date:  20190924 Time:  1800     Latitude:  12.60        Longitude:  -30.20      Windspeed:  55MPH       Pressure:  997mb
Storm Name:  LORENZO    Date:  20190925 Time:  0        Latitude:  13.00        Longitude:  -31.60      Windspeed:  60MPH       Pressure:  993mb
Storm Name:  LORENZO    Date:  20190925 Time:  600      Latitude:  13.40        Longitude:  -33.00      Windspeed:  70MPH       Pressure:  988mb
Storm Name:  LORENZO    Date:  20190925 Time:  1200     Latitude:  13.90        Longitude:  -34.50      Windspeed:  75MPH       Pressure:  983mb
Storm Name:  LORENZO    Date:  20190925 Time:  1800     Latitude:  14.40        Longitude:  -36.00      Windspeed:  80MPH       Pressure:  979mb
Storm Name:  LORENZO    Date:  20190926 Time:  0        Latitude:  14.50        Longitude:  -37.50      Windspeed:  85MPH       Pressure:  975mb
Storm Name:  LORENZO    Date:  20190926 Time:  600      Latitude:  14.70        Longitude:  -38.80      Windspeed:  95MPH       Pressure:  967mb
Storm Name:  LORENZO    Date:  20190926 Time:  1200     Latitude:  15.20        Longitude:  -39.80      Windspeed:  105MPH      Pressure:  955mb
Storm Name:  LORENZO    Date:  20190926 Time:  1800     Latitude:  16.00        Longitude:  -40.60      Windspeed:  115MPH      Pressure:  947mb
Storm Name:  LORENZO    Date:  20190927 Time:  0        Latitude:  17.10        Longitude:  -41.20      Windspeed:  125MPH      Pressure:  937mb
Storm Name:  LORENZO    Date:  20190927 Time:  600      Latitude:  18.10        Longitude:  -41.90      Windspeed:  125MPH      Pressure:  937mb
Storm Name:  LORENZO    Date:  20190927 Time:  1200     Latitude:  18.90        Longitude:  -42.70      Windspeed:  120MPH      Pressure:  943mb
Storm Name:  LORENZO    Date:  20190927 Time:  1800     Latitude:  19.60        Longitude:  -43.50      Windspeed:  110MPH      Pressure:  948mb
Storm Name:  LORENZO    Date:  20190928 Time:  0        Latitude:  20.30        Longitude:  -44.20      Windspeed:  105MPH      Pressure:  952mb
Storm Name:  LORENZO    Date:  20190928 Time:  600      Latitude:  21.10        Longitude:  -44.60      Windspeed:  100MPH      Pressure:  957mb
Storm Name:  LORENZO    Date:  20190928 Time:  1200     Latitude:  22.00        Longitude:  -44.90      Windspeed:  105MPH      Pressure:  957mb
Storm Name:  LORENZO    Date:  20190928 Time:  1800     Latitude:  22.90        Longitude:  -45.00      Windspeed:  115MPH      Pressure:  951mb
Storm Name:  LORENZO    Date:  20190929 Time:  0        Latitude:  23.80        Longitude:  -45.00      Windspeed:  130MPH      Pressure:  936mb
Storm Name:  LORENZO    Date:  20190929 Time:  300      Latitude:  24.30        Longitude:  -45.00      Windspeed:  140MPH      Pressure:  925mb
Storm Name:  LORENZO    Date:  20190929 Time:  600      Latitude:  24.70        Longitude:  -45.00      Windspeed:  130MPH      Pressure:  933mb
Storm Name:  LORENZO    Date:  20190929 Time:  1200     Latitude:  25.60        Longitude:  -44.80      Windspeed:  110MPH      Pressure:  945mb
Storm Name:  LORENZO    Date:  20190929 Time:  1800     Latitude:  26.40        Longitude:  -44.40      Windspeed:  90MPH       Pressure:  950mb
Storm Name:  LORENZO    Date:  20190930 Time:  0        Latitude:  27.20        Longitude:  -44.00      Windspeed:  90MPH       Pressure:  954mb
Storm Name:  LORENZO    Date:  20190930 Time:  600      Latitude:  28.20        Longitude:  -43.60      Windspeed:  90MPH       Pressure:  955mb
Storm Name:  LORENZO    Date:  20190930 Time:  1200     Latitude:  29.20        Longitude:  -43.20      Windspeed:  90MPH       Pressure:  955mb
Storm Name:  LORENZO    Date:  20190930 Time:  1800     Latitude:  30.20        Longitude:  -42.70      Windspeed:  90MPH       Pressure:  955mb
Storm Name:  LORENZO    Date:  20191001 Time:  0        Latitude:  31.20        Longitude:  -41.90      Windspeed:  90MPH       Pressure:  956mb
Storm Name:  LORENZO    Date:  20191001 Time:  600      Latitude:  32.60        Longitude:  -40.70      Windspeed:  85MPH       Pressure:  957mb
Storm Name:  LORENZO    Date:  20191001 Time:  1200     Latitude:  34.30        Longitude:  -39.00      Windspeed:  85MPH       Pressure:  957mb
Storm Name:  LORENZO    Date:  20191001 Time:  1800     Latitude:  35.90        Longitude:  -36.80      Windspeed:  85MPH       Pressure:  958mb
Storm Name:  LORENZO    Date:  20191002 Time:  0        Latitude:  37.80        Longitude:  -34.40      Windspeed:  85MPH       Pressure:  959mb
Storm Name:  LORENZO    Date:  20191002 Time:  600      Latitude:  40.20        Longitude:  -31.40      Windspeed:  80MPH       Pressure:  959mb
Storm Name:  LORENZO    Date:  20191002 Time:  1200     Latitude:  43.00        Longitude:  -28.00      Windspeed:  70MPH       Pressure:  959mb
Storm Name:  LORENZO    Date:  20191002 Time:  1800     Latitude:  45.90        Longitude:  -24.40      Windspeed:  65MPH       Pressure:  960mb
Storm Name:  LORENZO    Date:  20191003 Time:  0        Latitude:  49.20        Longitude:  -21.50      Windspeed:  60MPH       Pressure:  961mb
Storm Name:  LORENZO    Date:  20191003 Time:  600      Latitude:  52.00        Longitude:  -18.70      Windspeed:  60MPH       Pressure:  962mb
Storm Name:  LORENZO    Date:  20191003 Time:  1200     Latitude:  54.50        Longitude:  -15.70      Windspeed:  60MPH       Pressure:  963mb
Storm Name:  LORENZO    Date:  20191003 Time:  1800     Latitude:  55.80        Longitude:  -13.30      Windspeed:  60MPH       Pressure:  966mb
Storm Name:  LORENZO    Date:  20191004 Time:  0        Latitude:  55.40        Longitude:  -10.50      Windspeed:  55MPH       Pressure:  977mb
Storm Name:  LORENZO    Date:  20191004 Time:  600      Latitude:  54.50        Longitude:  -8.20       Windspeed:  50MPH       Pressure:  985mb
Storm Name:  MELISSA    Date:  20191008 Time:  1800     Latitude:  35.00        Longitude:  -74.10      Windspeed:  40MPH       Pressure:  1009mb
Storm Name:  MELISSA    Date:  20191009 Time:  0        Latitude:  36.10        Longitude:  -72.40      Windspeed:  40MPH       Pressure:  1009mb
Storm Name:  MELISSA    Date:  20191009 Time:  600      Latitude:  37.00        Longitude:  -70.40      Windspeed:  45MPH       Pressure:  1008mb
Storm Name:  MELISSA    Date:  20191009 Time:  1200     Latitude:  37.70        Longitude:  -68.80      Windspeed:  45MPH       Pressure:  1007mb
Storm Name:  MELISSA    Date:  20191009 Time:  1800     Latitude:  38.40        Longitude:  -68.10      Windspeed:  50MPH       Pressure:  1006mb
Storm Name:  MELISSA    Date:  20191010 Time:  0        Latitude:  38.90        Longitude:  -68.20      Windspeed:  55MPH       Pressure:  1004mb
Storm Name:  MELISSA    Date:  20191010 Time:  600      Latitude:  38.90        Longitude:  -68.70      Windspeed:  55MPH       Pressure:  1002mb
Storm Name:  MELISSA    Date:  20191010 Time:  1200     Latitude:  38.60        Longitude:  -69.20      Windspeed:  55MPH       Pressure:  1000mb
Storm Name:  MELISSA    Date:  20191010 Time:  1800     Latitude:  38.00        Longitude:  -69.20      Windspeed:  55MPH       Pressure:  998mb
Storm Name:  MELISSA    Date:  20191011 Time:  0        Latitude:  37.90        Longitude:  -68.40      Windspeed:  55MPH       Pressure:  996mb
Storm Name:  MELISSA    Date:  20191011 Time:  600      Latitude:  38.40        Longitude:  -68.70      Windspeed:  55MPH       Pressure:  994mb
Storm Name:  MELISSA    Date:  20191011 Time:  1200     Latitude:  38.60        Longitude:  -69.40      Windspeed:  50MPH       Pressure:  995mb
Storm Name:  MELISSA    Date:  20191011 Time:  1800     Latitude:  38.20        Longitude:  -69.70      Windspeed:  50MPH       Pressure:  996mb
Storm Name:  MELISSA    Date:  20191012 Time:  0        Latitude:  37.80        Longitude:  -69.10      Windspeed:  50MPH       Pressure:  997mb
Storm Name:  MELISSA    Date:  20191012 Time:  600      Latitude:  37.90        Longitude:  -68.40      Windspeed:  45MPH       Pressure:  998mb
Storm Name:  MELISSA    Date:  20191012 Time:  1200     Latitude:  38.00        Longitude:  -67.50      Windspeed:  45MPH       Pressure:  998mb
Storm Name:  MELISSA    Date:  20191012 Time:  1800     Latitude:  38.20        Longitude:  -66.30      Windspeed:  45MPH       Pressure:  998mb
Storm Name:  MELISSA    Date:  20191013 Time:  0        Latitude:  38.60        Longitude:  -64.90      Windspeed:  45MPH       Pressure:  998mb
Storm Name:  MELISSA    Date:  20191013 Time:  600      Latitude:  39.10        Longitude:  -63.50      Windspeed:  40MPH       Pressure:  999mb
Storm Name:  MELISSA    Date:  20191013 Time:  1200     Latitude:  39.50        Longitude:  -61.70      Windspeed:  40MPH       Pressure:  1000mb
Storm Name:  MELISSA    Date:  20191013 Time:  1800     Latitude:  39.70        Longitude:  -59.80      Windspeed:  35MPH       Pressure:  1001mb
Storm Name:  MELISSA    Date:  20191014 Time:  0        Latitude:  40.00        Longitude:  -57.90      Windspeed:  35MPH       Pressure:  1002mb
Storm Name:  MELISSA    Date:  20191014 Time:  600      Latitude:  40.50        Longitude:  -55.50      Windspeed:  35MPH       Pressure:  1003mb
Storm Name:  MELISSA    Date:  20191014 Time:  1200     Latitude:  40.80        Longitude:  -52.90      Windspeed:  35MPH       Pressure:  1004mb
Storm Name:  MELISSA    Date:  20191014 Time:  1800     Latitude:  40.90        Longitude:  -49.80      Windspeed:  35MPH       Pressure:  1004mb
Storm Name:  FIFTEEN    Date:  20191014 Time:  1200     Latitude:  12.60        Longitude:  -19.30      Windspeed:  30MPH       Pressure:  1006mb
Storm Name:  FIFTEEN    Date:  20191014 Time:  1800     Latitude:  13.30        Longitude:  -20.00      Windspeed:  30MPH       Pressure:  1006mb
Storm Name:  FIFTEEN    Date:  20191015 Time:  0        Latitude:  14.20        Longitude:  -20.40      Windspeed:  30MPH       Pressure:  1006mb
Storm Name:  FIFTEEN    Date:  20191015 Time:  600      Latitude:  15.00        Longitude:  -21.00      Windspeed:  30MPH       Pressure:  1006mb
Storm Name:  FIFTEEN    Date:  20191015 Time:  1200     Latitude:  15.70        Longitude:  -21.70      Windspeed:  30MPH       Pressure:  1006mb
Storm Name:  FIFTEEN    Date:  20191015 Time:  1800     Latitude:  16.30        Longitude:  -22.60      Windspeed:  30MPH       Pressure:  1007mb
Storm Name:  FIFTEEN    Date:  20191016 Time:  0        Latitude:  17.00        Longitude:  -23.40      Windspeed:  30MPH       Pressure:  1009mb
Storm Name:  FIFTEEN    Date:  20191016 Time:  600      Latitude:  17.60        Longitude:  -24.40      Windspeed:  25MPH       Pressure:  1009mb
Storm Name:  FIFTEEN    Date:  20191016 Time:  1200     Latitude:  18.20        Longitude:  -25.40      Windspeed:  25MPH       Pressure:  1009mb
Storm Name:  FIFTEEN    Date:  20191016 Time:  1800     Latitude:  18.70        Longitude:  -26.80      Windspeed:  25MPH       Pressure:  1009mb
Storm Name:  FIFTEEN    Date:  20191017 Time:  0        Latitude:  19.20        Longitude:  -28.30      Windspeed:  25MPH       Pressure:  1009mb
Storm Name:  FIFTEEN    Date:  20191017 Time:  600      Latitude:  19.50        Longitude:  -29.80      Windspeed:  25MPH       Pressure:  1009mb
Storm Name:  FIFTEEN    Date:  20191017 Time:  1200     Latitude:  19.30        Longitude:  -31.00      Windspeed:  25MPH       Pressure:  1009mb
Storm Name:  NESTOR     Date:  20191017 Time:  1200     Latitude:  22.20        Longitude:  -95.70      Windspeed:  35MPH       Pressure:  1007mb
Storm Name:  NESTOR     Date:  20191017 Time:  1800     Latitude:  22.60        Longitude:  -95.20      Windspeed:  35MPH       Pressure:  1005mb
Storm Name:  NESTOR     Date:  20191018 Time:  0        Latitude:  23.20        Longitude:  -94.50      Windspeed:  40MPH       Pressure:  1003mb
Storm Name:  NESTOR     Date:  20191018 Time:  600      Latitude:  24.10        Longitude:  -93.00      Windspeed:  45MPH       Pressure:  1002mb
Storm Name:  NESTOR     Date:  20191018 Time:  1200     Latitude:  25.20        Longitude:  -91.20      Windspeed:  50MPH       Pressure:  1001mb
Storm Name:  NESTOR     Date:  20191018 Time:  1800     Latitude:  26.40        Longitude:  -89.40      Windspeed:  50MPH       Pressure:  1000mb
Storm Name:  NESTOR     Date:  20191019 Time:  0        Latitude:  27.80        Longitude:  -87.80      Windspeed:  50MPH       Pressure:  996mb
Storm Name:  NESTOR     Date:  20191019 Time:  600      Latitude:  28.60        Longitude:  -87.10      Windspeed:  50MPH       Pressure:  996mb
Storm Name:  NESTOR     Date:  20191019 Time:  1200     Latitude:  29.30        Longitude:  -86.40      Windspeed:  40MPH       Pressure:  996mb
Storm Name:  NESTOR     Date:  20191019 Time:  1800     Latitude:  30.20        Longitude:  -85.40      Windspeed:  40MPH       Pressure:  999mb
Storm Name:  NESTOR     Date:  20191020 Time:  0        Latitude:  31.20        Longitude:  -84.20      Windspeed:  35MPH       Pressure:  1000mb
Storm Name:  NESTOR     Date:  20191020 Time:  600      Latitude:  33.10        Longitude:  -81.70      Windspeed:  40MPH       Pressure:  1002mb
Storm Name:  NESTOR     Date:  20191020 Time:  1200     Latitude:  35.10        Longitude:  -79.10      Windspeed:  40MPH       Pressure:  1002mb
Storm Name:  NESTOR     Date:  20191020 Time:  1800     Latitude:  37.00        Longitude:  -76.70      Windspeed:  40MPH       Pressure:  1002mb
Storm Name:  NESTOR     Date:  20191021 Time:  0        Latitude:  37.50        Longitude:  -74.50      Windspeed:  40MPH       Pressure:  1001mb
Storm Name:  OLGA       Date:  20191025 Time:  1200     Latitude:  24.70        Longitude:  -94.80      Windspeed:  35MPH       Pressure:  1004mb
Storm Name:  OLGA       Date:  20191025 Time:  1800     Latitude:  25.90        Longitude:  -93.60      Windspeed:  40MPH       Pressure:  998mb
Storm Name:  OLGA       Date:  20191026 Time:  0        Latitude:  27.00        Longitude:  -92.50      Windspeed:  45MPH       Pressure:  996mb
Storm Name:  OLGA       Date:  20191026 Time:  600      Latitude:  28.80        Longitude:  -91.20      Windspeed:  45MPH       Pressure:  994mb
Storm Name:  OLGA       Date:  20191026 Time:  1200     Latitude:  31.70        Longitude:  -90.00      Windspeed:  45MPH       Pressure:  993mb
Storm Name:  OLGA       Date:  20191026 Time:  1800     Latitude:  36.20        Longitude:  -89.30      Windspeed:  40MPH       Pressure:  993mb
Storm Name:  OLGA       Date:  20191027 Time:  0        Latitude:  40.10        Longitude:  -88.00      Windspeed:  30MPH       Pressure:  992mb
Storm Name:  OLGA       Date:  20191027 Time:  600      Latitude:  42.50        Longitude:  -87.00      Windspeed:  30MPH       Pressure:  992mb
Storm Name:  OLGA       Date:  20191027 Time:  1200     Latitude:  44.50        Longitude:  -84.70      Windspeed:  30MPH       Pressure:  994mb
Storm Name:  OLGA       Date:  20191027 Time:  1800     Latitude:  46.00        Longitude:  -80.30      Windspeed:  30MPH       Pressure:  998mb
Storm Name:  PABLO      Date:  20191023 Time:  1800     Latitude:  40.00        Longitude:  -38.30      Windspeed:  40MPH       Pressure:  1000mb
Storm Name:  PABLO      Date:  20191024 Time:  0        Latitude:  40.20        Longitude:  -38.40      Windspeed:  50MPH       Pressure:  998mb
Storm Name:  PABLO      Date:  20191024 Time:  600      Latitude:  39.00        Longitude:  -39.90      Windspeed:  50MPH       Pressure:  995mb
Storm Name:  PABLO      Date:  20191024 Time:  1200     Latitude:  36.90        Longitude:  -39.30      Windspeed:  50MPH       Pressure:  990mb
Storm Name:  PABLO      Date:  20191024 Time:  1800     Latitude:  35.80        Longitude:  -36.90      Windspeed:  45MPH       Pressure:  988mb
Storm Name:  PABLO      Date:  20191025 Time:  0        Latitude:  35.90        Longitude:  -35.10      Windspeed:  45MPH       Pressure:  988mb
Storm Name:  PABLO      Date:  20191025 Time:  600      Latitude:  36.30        Longitude:  -34.00      Windspeed:  45MPH       Pressure:  988mb
Storm Name:  PABLO      Date:  20191025 Time:  1200     Latitude:  36.40        Longitude:  -33.20      Windspeed:  40MPH       Pressure:  989mb
Storm Name:  PABLO      Date:  20191025 Time:  1800     Latitude:  35.90        Longitude:  -32.70      Windspeed:  40MPH       Pressure:  990mb
Storm Name:  PABLO      Date:  20191026 Time:  0        Latitude:  35.50        Longitude:  -31.80      Windspeed:  40MPH       Pressure:  990mb
Storm Name:  PABLO      Date:  20191026 Time:  600      Latitude:  35.20        Longitude:  -30.70      Windspeed:  40MPH       Pressure:  990mb
Storm Name:  PABLO      Date:  20191026 Time:  1200     Latitude:  35.10        Longitude:  -29.10      Windspeed:  45MPH       Pressure:  989mb
Storm Name:  PABLO      Date:  20191026 Time:  1800     Latitude:  35.60        Longitude:  -26.60      Windspeed:  50MPH       Pressure:  987mb
Storm Name:  PABLO      Date:  20191027 Time:  0        Latitude:  37.00        Longitude:  -23.80      Windspeed:  55MPH       Pressure:  985mb
Storm Name:  PABLO      Date:  20191027 Time:  600      Latitude:  39.50        Longitude:  -20.70      Windspeed:  60MPH       Pressure:  983mb
Storm Name:  PABLO      Date:  20191027 Time:  1200     Latitude:  41.90        Longitude:  -18.80      Windspeed:  65MPH       Pressure:  980mb
Storm Name:  PABLO      Date:  20191027 Time:  1800     Latitude:  44.10        Longitude:  -17.30      Windspeed:  70MPH       Pressure:  977mb
Storm Name:  PABLO      Date:  20191028 Time:  0        Latitude:  45.50        Longitude:  -17.00      Windspeed:  60MPH       Pressure:  982mb
Storm Name:  PABLO      Date:  20191028 Time:  600      Latitude:  46.30        Longitude:  -17.60      Windspeed:  45MPH       Pressure:  990mb
Storm Name:  PABLO      Date:  20191028 Time:  1200     Latitude:  46.50        Longitude:  -17.90      Windspeed:  35MPH       Pressure:  995mb
Storm Name:  PABLO      Date:  20191028 Time:  1800     Latitude:  46.60        Longitude:  -17.60      Windspeed:  35MPH       Pressure:  995mb
Storm Name:  PABLO      Date:  20191029 Time:  0        Latitude:  46.80        Longitude:  -16.40      Windspeed:  30MPH       Pressure:  995mb
Storm Name:  REBEKAH    Date:  20191027 Time:  0        Latitude:  40.50        Longitude:  -51.50      Windspeed:  35MPH       Pressure:  1004mb
Storm Name:  REBEKAH    Date:  20191027 Time:  600      Latitude:  40.40        Longitude:  -48.00      Windspeed:  50MPH       Pressure:  989mb
Storm Name:  REBEKAH    Date:  20191027 Time:  1200     Latitude:  40.20        Longitude:  -45.00      Windspeed:  60MPH       Pressure:  976mb
Storm Name:  REBEKAH    Date:  20191027 Time:  1800     Latitude:  40.20        Longitude:  -43.10      Windspeed:  65MPH       Pressure:  968mb
Storm Name:  REBEKAH    Date:  20191028 Time:  0        Latitude:  40.50        Longitude:  -41.10      Windspeed:  70MPH       Pressure:  965mb
Storm Name:  REBEKAH    Date:  20191028 Time:  600      Latitude:  41.20        Longitude:  -39.50      Windspeed:  70MPH       Pressure:  966mb
Storm Name:  REBEKAH    Date:  20191028 Time:  1200     Latitude:  42.40        Longitude:  -39.40      Windspeed:  65MPH       Pressure:  967mb
Storm Name:  REBEKAH    Date:  20191028 Time:  1800     Latitude:  42.90        Longitude:  -40.40      Windspeed:  60MPH       Pressure:  969mb
Storm Name:  REBEKAH    Date:  20191029 Time:  0        Latitude:  42.20        Longitude:  -40.10      Windspeed:  55MPH       Pressure:  971mb
Storm Name:  REBEKAH    Date:  20191029 Time:  600      Latitude:  42.30        Longitude:  -38.50      Windspeed:  55MPH       Pressure:  973mb
Storm Name:  REBEKAH    Date:  20191029 Time:  1200     Latitude:  43.00        Longitude:  -38.90      Windspeed:  55MPH       Pressure:  975mb
Storm Name:  REBEKAH    Date:  20191029 Time:  1800     Latitude:  43.40        Longitude:  -40.60      Windspeed:  50MPH       Pressure:  977mb
Storm Name:  REBEKAH    Date:  20191030 Time:  0        Latitude:  41.80        Longitude:  -42.70      Windspeed:  50MPH       Pressure:  979mb
Storm Name:  REBEKAH    Date:  20191030 Time:  600      Latitude:  39.90        Longitude:  -43.70      Windspeed:  50MPH       Pressure:  980mb
Storm Name:  REBEKAH    Date:  20191030 Time:  1200     Latitude:  38.30        Longitude:  -42.80      Windspeed:  45MPH       Pressure:  982mb
Storm Name:  REBEKAH    Date:  20191030 Time:  1800     Latitude:  38.10        Longitude:  -41.50      Windspeed:  45MPH       Pressure:  984mb
Storm Name:  REBEKAH    Date:  20191031 Time:  0        Latitude:  38.40        Longitude:  -40.00      Windspeed:  45MPH       Pressure:  986mb
Storm Name:  REBEKAH    Date:  20191031 Time:  600      Latitude:  39.30        Longitude:  -37.70      Windspeed:  40MPH       Pressure:  988mb
Storm Name:  REBEKAH    Date:  20191031 Time:  1200     Latitude:  40.30        Longitude:  -36.20      Windspeed:  40MPH       Pressure:  990mb
Storm Name:  REBEKAH    Date:  20191031 Time:  1800     Latitude:  41.00        Longitude:  -34.50      Windspeed:  40MPH       Pressure:  992mb
Storm Name:  REBEKAH    Date:  20191101 Time:  0        Latitude:  40.80        Longitude:  -32.40      Windspeed:  35MPH       Pressure:  995mb
Storm Name:  REBEKAH    Date:  20191101 Time:  600      Latitude:  40.60        Longitude:  -30.20      Windspeed:  35MPH       Pressure:  1002mb
Storm Name:  REBEKAH    Date:  20191101 Time:  1200     Latitude:  40.50        Longitude:  -27.50      Windspeed:  35MPH       Pressure:  1016mb
Storm Name:  SEBASTIEN  Date:  20191119 Time:  600      Latitude:  19.40        Longitude:  -58.10      Windspeed:  35MPH       Pressure:  1006mb
Storm Name:  SEBASTIEN  Date:  20191119 Time:  1200     Latitude:  19.90        Longitude:  -58.50      Windspeed:  40MPH       Pressure:  1004mb
Storm Name:  SEBASTIEN  Date:  20191119 Time:  1800     Latitude:  20.30        Longitude:  -59.40      Windspeed:  40MPH       Pressure:  1004mb
Storm Name:  SEBASTIEN  Date:  20191120 Time:  0        Latitude:  20.40        Longitude:  -60.30      Windspeed:  40MPH       Pressure:  1002mb
Storm Name:  SEBASTIEN  Date:  20191120 Time:  600      Latitude:  20.50        Longitude:  -61.00      Windspeed:  45MPH       Pressure:  1000mb
Storm Name:  SEBASTIEN  Date:  20191120 Time:  1200     Latitude:  20.80        Longitude:  -61.70      Windspeed:  45MPH       Pressure:  999mb
Storm Name:  SEBASTIEN  Date:  20191120 Time:  1800     Latitude:  21.30        Longitude:  -61.70      Windspeed:  45MPH       Pressure:  999mb
Storm Name:  SEBASTIEN  Date:  20191121 Time:  0        Latitude:  21.90        Longitude:  -61.70      Windspeed:  50MPH       Pressure:  996mb
Storm Name:  SEBASTIEN  Date:  20191121 Time:  600      Latitude:  22.40        Longitude:  -61.40      Windspeed:  50MPH       Pressure:  996mb
Storm Name:  SEBASTIEN  Date:  20191121 Time:  1200     Latitude:  22.90        Longitude:  -60.90      Windspeed:  50MPH       Pressure:  996mb
Storm Name:  SEBASTIEN  Date:  20191121 Time:  1800     Latitude:  23.50        Longitude:  -60.10      Windspeed:  50MPH       Pressure:  996mb
Storm Name:  SEBASTIEN  Date:  20191122 Time:  0        Latitude:  24.20        Longitude:  -58.80      Windspeed:  50MPH       Pressure:  996mb
Storm Name:  SEBASTIEN  Date:  20191122 Time:  600      Latitude:  24.50        Longitude:  -57.30      Windspeed:  50MPH       Pressure:  996mb
Storm Name:  SEBASTIEN  Date:  20191122 Time:  1200     Latitude:  25.00        Longitude:  -55.80      Windspeed:  50MPH       Pressure:  996mb
Storm Name:  SEBASTIEN  Date:  20191122 Time:  1800     Latitude:  25.80        Longitude:  -54.40      Windspeed:  55MPH       Pressure:  994mb
Storm Name:  SEBASTIEN  Date:  20191123 Time:  0        Latitude:  26.70        Longitude:  -52.60      Windspeed:  60MPH       Pressure:  991mb
Storm Name:  SEBASTIEN  Date:  20191123 Time:  600      Latitude:  28.10        Longitude:  -50.50      Windspeed:  60MPH       Pressure:  991mb
Storm Name:  SEBASTIEN  Date:  20191123 Time:  1200     Latitude:  29.60        Longitude:  -48.40      Windspeed:  55MPH       Pressure:  994mb
Storm Name:  SEBASTIEN  Date:  20191123 Time:  1800     Latitude:  31.50        Longitude:  -46.40      Windspeed:  55MPH       Pressure:  994mb
Storm Name:  SEBASTIEN  Date:  20191124 Time:  0        Latitude:  33.50        Longitude:  -44.40      Windspeed:  55MPH       Pressure:  994mb
Storm Name:  SEBASTIEN  Date:  20191124 Time:  600      Latitude:  35.20        Longitude:  -41.70      Windspeed:  55MPH       Pressure:  994mb
Storm Name:  SEBASTIEN  Date:  20191124 Time:  1200     Latitude:  36.60        Longitude:  -38.50      Windspeed:  55MPH       Pressure:  994mb
Storm Name:  SEBASTIEN  Date:  20191124 Time:  1800     Latitude:  38.20        Longitude:  -34.70      Windspeed:  55MPH       Pressure:  994mb
Storm Name:  SEBASTIEN  Date:  20191125 Time:  0        Latitude:  40.00        Longitude:  -30.90      Windspeed:  55MPH       Pressure:  992mb
Storm Name:  SEBASTIEN  Date:  20191125 Time:  600      Latitude:  41.90        Longitude:  -26.70      Windspeed:  60MPH       Pressure:  988mb
Storm Name:  SEBASTIEN  Date:  20191125 Time:  1200     Latitude:  44.00        Longitude:  -22.00      Windspeed:  60MPH       Pressure:  982mb
Storm Name:  SEBASTIEN  Date:  20191125 Time:  1800     Latitude:  46.40        Longitude:  -16.30      Windspeed:  60MPH       Pressure:  978mb
Storm Name:  SEBASTIEN  Date:  20191126 Time:  0        Latitude:  48.80        Longitude:  -12.20      Windspeed:  55MPH       Pressure:  974mb
Storm Name:  SEBASTIEN  Date:  20191126 Time:  600      Latitude:  51.30        Longitude:  -9.30       Windspeed:  50MPH       Pressure:  972mb
Storm Name:  SEBASTIEN  Date:  20191126 Time:  1200     Latitude:  52.20        Longitude:  -9.30       Windspeed:  45MPH       Pressure:  970mb
Storm Name:  SEBASTIEN  Date:  20191126 Time:  1800     Latitude:  52.20        Longitude:  -8.90       Windspeed:  40MPH       Pressure:  972mb
Storm Name:  SEBASTIEN  Date:  20191127 Time:  0        Latitude:  51.80        Longitude:  -8.20       Windspeed:  40MPH       Pressure:  974mb
Storm Name:  SEBASTIEN  Date:  20191127 Time:  600      Latitude:  51.40        Longitude:  -6.00       Windspeed:  40MPH       Pressure:  976mb
Storm Name:  SEBASTIEN  Date:  20191127 Time:  1200     Latitude:  51.30        Longitude:  -2.10       Windspeed:  40MPH       Pressure:  980mb

        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        0) Exit the Program
Please Enter an Option [0-6]:  1

Please enter record number:  490

Storm Name:  SEBASTIEN  Date:  20191126 Time:  1800     Latitude:  52.20        Longitude:  -8.90       Windspeed:  40MPH       Pressure:  972mb
Storm Name:  SEBASTIEN  Date:  20191127 Time:  0        Latitude:  51.80        Longitude:  -8.20       Windspeed:  40MPH       Pressure:  974mb
Storm Name:  SEBASTIEN  Date:  20191127 Time:  600      Latitude:  51.40        Longitude:  -6.00       Windspeed:  40MPH       Pressure:  976mb
Storm Name:  SEBASTIEN  Date:  20191127 Time:  1200     Latitude:  51.30        Longitude:  -2.10       Windspeed:  40MPH       Pressure:  980mb

        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        0) Exit the Program
Please Enter an Option [0-6]:  2

Please enter date [MMDD]:  1119

Storm Name:  SEBASTIEN  Date:  20191119 Time:  600      Latitude:  19.40        Longitude:  -58.10      Windspeed:  35MPH       Pressure:  1006mb
Storm Name:  SEBASTIEN  Date:  20191119 Time:  1200     Latitude:  19.90        Longitude:  -58.50      Windspeed:  40MPH       Pressure:  1004mb
Storm Name:  SEBASTIEN  Date:  20191119 Time:  1800     Latitude:  20.30        Longitude:  -59.40      Windspeed:  40MPH       Pressure:  1004mb

Search Result:  3 results found for 1119

        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        0) Exit the Program
Please Enter an Option [0-6]:  2

Please enter date [MMDD]:  1024

Storm Name:  PABLO      Date:  20191024 Time:  0        Latitude:  40.20        Longitude:  -38.40      Windspeed:  50MPH       Pressure:  998mb
Storm Name:  PABLO      Date:  20191024 Time:  600      Latitude:  39.00        Longitude:  -39.90      Windspeed:  50MPH       Pressure:  995mb
Storm Name:  PABLO      Date:  20191024 Time:  1200     Latitude:  36.90        Longitude:  -39.30      Windspeed:  50MPH       Pressure:  990mb
Storm Name:  PABLO      Date:  20191024 Time:  1800     Latitude:  35.80        Longitude:  -36.90      Windspeed:  45MPH       Pressure:  988mb

Search Result:  4 results found for 1024

        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        0) Exit the Program
Please Enter an Option [0-6]:  2

Please enter date [MMDD]:  0411


Search Result:  0 results found for 265

        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        0) Exit the Program
Please Enter an Option [0-6]:  3

Please enter name [exact]:  seb


Search Result: 0 results for for "seb"

        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        0) Exit the Program
Please Enter an Option [0-6]:  3

Please enter name [exact]:  sebastien

Storm Name:  SEBASTIEN  Date:  20191119 Time:  600      Latitude:  19.40        Longitude:  -58.10      Windspeed:  35MPH       Pressure:  1006mb
Storm Name:  SEBASTIEN  Date:  20191119 Time:  1200     Latitude:  19.90        Longitude:  -58.50      Windspeed:  40MPH       Pressure:  1004mb
Storm Name:  SEBASTIEN  Date:  20191119 Time:  1800     Latitude:  20.30        Longitude:  -59.40      Windspeed:  40MPH       Pressure:  1004mb
Storm Name:  SEBASTIEN  Date:  20191120 Time:  0        Latitude:  20.40        Longitude:  -60.30      Windspeed:  40MPH       Pressure:  1002mb
Storm Name:  SEBASTIEN  Date:  20191120 Time:  600      Latitude:  20.50        Longitude:  -61.00      Windspeed:  45MPH       Pressure:  1000mb
Storm Name:  SEBASTIEN  Date:  20191120 Time:  1200     Latitude:  20.80        Longitude:  -61.70      Windspeed:  45MPH       Pressure:  999mb
Storm Name:  SEBASTIEN  Date:  20191120 Time:  1800     Latitude:  21.30        Longitude:  -61.70      Windspeed:  45MPH       Pressure:  999mb
Storm Name:  SEBASTIEN  Date:  20191121 Time:  0        Latitude:  21.90        Longitude:  -61.70      Windspeed:  50MPH       Pressure:  996mb
Storm Name:  SEBASTIEN  Date:  20191121 Time:  600      Latitude:  22.40        Longitude:  -61.40      Windspeed:  50MPH       Pressure:  996mb
Storm Name:  SEBASTIEN  Date:  20191121 Time:  1200     Latitude:  22.90        Longitude:  -60.90      Windspeed:  50MPH       Pressure:  996mb
Storm Name:  SEBASTIEN  Date:  20191121 Time:  1800     Latitude:  23.50        Longitude:  -60.10      Windspeed:  50MPH       Pressure:  996mb
Storm Name:  SEBASTIEN  Date:  20191122 Time:  0        Latitude:  24.20        Longitude:  -58.80      Windspeed:  50MPH       Pressure:  996mb
Storm Name:  SEBASTIEN  Date:  20191122 Time:  600      Latitude:  24.50        Longitude:  -57.30      Windspeed:  50MPH       Pressure:  996mb
Storm Name:  SEBASTIEN  Date:  20191122 Time:  1200     Latitude:  25.00        Longitude:  -55.80      Windspeed:  50MPH       Pressure:  996mb
Storm Name:  SEBASTIEN  Date:  20191122 Time:  1800     Latitude:  25.80        Longitude:  -54.40      Windspeed:  55MPH       Pressure:  994mb
Storm Name:  SEBASTIEN  Date:  20191123 Time:  0        Latitude:  26.70        Longitude:  -52.60      Windspeed:  60MPH       Pressure:  991mb
Storm Name:  SEBASTIEN  Date:  20191123 Time:  600      Latitude:  28.10        Longitude:  -50.50      Windspeed:  60MPH       Pressure:  991mb
Storm Name:  SEBASTIEN  Date:  20191123 Time:  1200     Latitude:  29.60        Longitude:  -48.40      Windspeed:  55MPH       Pressure:  994mb
Storm Name:  SEBASTIEN  Date:  20191123 Time:  1800     Latitude:  31.50        Longitude:  -46.40      Windspeed:  55MPH       Pressure:  994mb
Storm Name:  SEBASTIEN  Date:  20191124 Time:  0        Latitude:  33.50        Longitude:  -44.40      Windspeed:  55MPH       Pressure:  994mb
Storm Name:  SEBASTIEN  Date:  20191124 Time:  600      Latitude:  35.20        Longitude:  -41.70      Windspeed:  55MPH       Pressure:  994mb
Storm Name:  SEBASTIEN  Date:  20191124 Time:  1200     Latitude:  36.60        Longitude:  -38.50      Windspeed:  55MPH       Pressure:  994mb
Storm Name:  SEBASTIEN  Date:  20191124 Time:  1800     Latitude:  38.20        Longitude:  -34.70      Windspeed:  55MPH       Pressure:  994mb
Storm Name:  SEBASTIEN  Date:  20191125 Time:  0        Latitude:  40.00        Longitude:  -30.90      Windspeed:  55MPH       Pressure:  992mb
Storm Name:  SEBASTIEN  Date:  20191125 Time:  600      Latitude:  41.90        Longitude:  -26.70      Windspeed:  60MPH       Pressure:  988mb
Storm Name:  SEBASTIEN  Date:  20191125 Time:  1200     Latitude:  44.00        Longitude:  -22.00      Windspeed:  60MPH       Pressure:  982mb
Storm Name:  SEBASTIEN  Date:  20191125 Time:  1800     Latitude:  46.40        Longitude:  -16.30      Windspeed:  60MPH       Pressure:  978mb
Storm Name:  SEBASTIEN  Date:  20191126 Time:  0        Latitude:  48.80        Longitude:  -12.20      Windspeed:  55MPH       Pressure:  974mb
Storm Name:  SEBASTIEN  Date:  20191126 Time:  600      Latitude:  51.30        Longitude:  -9.30       Windspeed:  50MPH       Pressure:  972mb
Storm Name:  SEBASTIEN  Date:  20191126 Time:  1200     Latitude:  52.20        Longitude:  -9.30       Windspeed:  45MPH       Pressure:  970mb
Storm Name:  SEBASTIEN  Date:  20191126 Time:  1800     Latitude:  52.20        Longitude:  -8.90       Windspeed:  40MPH       Pressure:  972mb
Storm Name:  SEBASTIEN  Date:  20191127 Time:  0        Latitude:  51.80        Longitude:  -8.20       Windspeed:  40MPH       Pressure:  974mb
Storm Name:  SEBASTIEN  Date:  20191127 Time:  600      Latitude:  51.40        Longitude:  -6.00       Windspeed:  40MPH       Pressure:  976mb
Storm Name:  SEBASTIEN  Date:  20191127 Time:  1200     Latitude:  51.30        Longitude:  -2.10       Windspeed:  40MPH       Pressure:  980mb

Search Result: 34 results for for "sebastien"

        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        0) Exit the Program
Please Enter an Option [0-6]:  4

Please enter name [partial]:  seb

Storm Name:  SEBASTIEN  Date:  20191119 Time:  600      Latitude:  19.40        Longitude:  -58.10      Windspeed:  35MPH       Pressure:  1006mb
Storm Name:  SEBASTIEN  Date:  20191119 Time:  1200     Latitude:  19.90        Longitude:  -58.50      Windspeed:  40MPH       Pressure:  1004mb
Storm Name:  SEBASTIEN  Date:  20191119 Time:  1800     Latitude:  20.30        Longitude:  -59.40      Windspeed:  40MPH       Pressure:  1004mb
Storm Name:  SEBASTIEN  Date:  20191120 Time:  0        Latitude:  20.40        Longitude:  -60.30      Windspeed:  40MPH       Pressure:  1002mb
Storm Name:  SEBASTIEN  Date:  20191120 Time:  600      Latitude:  20.50        Longitude:  -61.00      Windspeed:  45MPH       Pressure:  1000mb
Storm Name:  SEBASTIEN  Date:  20191120 Time:  1200     Latitude:  20.80        Longitude:  -61.70      Windspeed:  45MPH       Pressure:  999mb
Storm Name:  SEBASTIEN  Date:  20191120 Time:  1800     Latitude:  21.30        Longitude:  -61.70      Windspeed:  45MPH       Pressure:  999mb
Storm Name:  SEBASTIEN  Date:  20191121 Time:  0        Latitude:  21.90        Longitude:  -61.70      Windspeed:  50MPH       Pressure:  996mb
Storm Name:  SEBASTIEN  Date:  20191121 Time:  600      Latitude:  22.40        Longitude:  -61.40      Windspeed:  50MPH       Pressure:  996mb
Storm Name:  SEBASTIEN  Date:  20191121 Time:  1200     Latitude:  22.90        Longitude:  -60.90      Windspeed:  50MPH       Pressure:  996mb
Storm Name:  SEBASTIEN  Date:  20191121 Time:  1800     Latitude:  23.50        Longitude:  -60.10      Windspeed:  50MPH       Pressure:  996mb
Storm Name:  SEBASTIEN  Date:  20191122 Time:  0        Latitude:  24.20        Longitude:  -58.80      Windspeed:  50MPH       Pressure:  996mb
Storm Name:  SEBASTIEN  Date:  20191122 Time:  600      Latitude:  24.50        Longitude:  -57.30      Windspeed:  50MPH       Pressure:  996mb
Storm Name:  SEBASTIEN  Date:  20191122 Time:  1200     Latitude:  25.00        Longitude:  -55.80      Windspeed:  50MPH       Pressure:  996mb
Storm Name:  SEBASTIEN  Date:  20191122 Time:  1800     Latitude:  25.80        Longitude:  -54.40      Windspeed:  55MPH       Pressure:  994mb
Storm Name:  SEBASTIEN  Date:  20191123 Time:  0        Latitude:  26.70        Longitude:  -52.60      Windspeed:  60MPH       Pressure:  991mb
Storm Name:  SEBASTIEN  Date:  20191123 Time:  600      Latitude:  28.10        Longitude:  -50.50      Windspeed:  60MPH       Pressure:  991mb
Storm Name:  SEBASTIEN  Date:  20191123 Time:  1200     Latitude:  29.60        Longitude:  -48.40      Windspeed:  55MPH       Pressure:  994mb
Storm Name:  SEBASTIEN  Date:  20191123 Time:  1800     Latitude:  31.50        Longitude:  -46.40      Windspeed:  55MPH       Pressure:  994mb
Storm Name:  SEBASTIEN  Date:  20191124 Time:  0        Latitude:  33.50        Longitude:  -44.40      Windspeed:  55MPH       Pressure:  994mb
Storm Name:  SEBASTIEN  Date:  20191124 Time:  600      Latitude:  35.20        Longitude:  -41.70      Windspeed:  55MPH       Pressure:  994mb
Storm Name:  SEBASTIEN  Date:  20191124 Time:  1200     Latitude:  36.60        Longitude:  -38.50      Windspeed:  55MPH       Pressure:  994mb
Storm Name:  SEBASTIEN  Date:  20191124 Time:  1800     Latitude:  38.20        Longitude:  -34.70      Windspeed:  55MPH       Pressure:  994mb
Storm Name:  SEBASTIEN  Date:  20191125 Time:  0        Latitude:  40.00        Longitude:  -30.90      Windspeed:  55MPH       Pressure:  992mb
Storm Name:  SEBASTIEN  Date:  20191125 Time:  600      Latitude:  41.90        Longitude:  -26.70      Windspeed:  60MPH       Pressure:  988mb
Storm Name:  SEBASTIEN  Date:  20191125 Time:  1200     Latitude:  44.00        Longitude:  -22.00      Windspeed:  60MPH       Pressure:  982mb
Storm Name:  SEBASTIEN  Date:  20191125 Time:  1800     Latitude:  46.40        Longitude:  -16.30      Windspeed:  60MPH       Pressure:  978mb
Storm Name:  SEBASTIEN  Date:  20191126 Time:  0        Latitude:  48.80        Longitude:  -12.20      Windspeed:  55MPH       Pressure:  974mb
Storm Name:  SEBASTIEN  Date:  20191126 Time:  600      Latitude:  51.30        Longitude:  -9.30       Windspeed:  50MPH       Pressure:  972mb
Storm Name:  SEBASTIEN  Date:  20191126 Time:  1200     Latitude:  52.20        Longitude:  -9.30       Windspeed:  45MPH       Pressure:  970mb
Storm Name:  SEBASTIEN  Date:  20191126 Time:  1800     Latitude:  52.20        Longitude:  -8.90       Windspeed:  40MPH       Pressure:  972mb
Storm Name:  SEBASTIEN  Date:  20191127 Time:  0        Latitude:  51.80        Longitude:  -8.20       Windspeed:  40MPH       Pressure:  974mb
Storm Name:  SEBASTIEN  Date:  20191127 Time:  600      Latitude:  51.40        Longitude:  -6.00       Windspeed:  40MPH       Pressure:  976mb
Storm Name:  SEBASTIEN  Date:  20191127 Time:  1200     Latitude:  51.30        Longitude:  -2.10       Windspeed:  40MPH       Pressure:  980mb

Search Result: 34 results for for "seb"

        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        0) Exit the Program
Please Enter an Option [0-6]:  4

Please enter name [partial]:  and 

Storm Name:  ANDREA     Date:  20190520 Time:  1800     Latitude:  28.10        Longitude:  -68.60      Windspeed:  35MPH       Pressure:  1008mb
Storm Name:  ANDREA     Date:  20190521 Time:  0        Latitude:  29.10        Longitude:  -68.80      Windspeed:  35MPH       Pressure:  1006mb
Storm Name:  ANDREA     Date:  20190521 Time:  600      Latitude:  29.90        Longitude:  -69.00      Windspeed:  35MPH       Pressure:  1007mb
Storm Name:  ANDREA     Date:  20190521 Time:  1200     Latitude:  30.60        Longitude:  -69.10      Windspeed:  30MPH       Pressure:  1009mb
Storm Name:  ANDREA     Date:  20190521 Time:  1800     Latitude:  30.80        Longitude:  -68.60      Windspeed:  30MPH       Pressure:  1009mb
Storm Name:  ANDREA     Date:  20190522 Time:  0        Latitude:  31.30        Longitude:  -67.70      Windspeed:  30MPH       Pressure:  1010mb
Storm Name:  ANDREA     Date:  20190522 Time:  600      Latitude:  31.60        Longitude:  -66.70      Windspeed:  25MPH       Pressure:  1011mb

Search Result: 7 results for for "and"

        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        0) Exit the Program
Please Enter an Option [0-6]:  5

Please enter windspeed [minimum]:  140

Storm Name:  DORIAN     Date:  20190901 Time:  600      Latitude:  26.40        Longitude:  -75.60      Windspeed:  145MPH      Pressure:  934mb
Storm Name:  DORIAN     Date:  20190901 Time:  1200     Latitude:  26.50        Longitude:  -76.50      Windspeed:  155MPH      Pressure:  927mb
Storm Name:  DORIAN     Date:  20190901 Time:  1640     Latitude:  26.50        Longitude:  -77.00      Windspeed:  160MPH      Pressure:  910mb
Storm Name:  DORIAN     Date:  20190901 Time:  1800     Latitude:  26.50        Longitude:  -77.10      Windspeed:  160MPH      Pressure:  910mb
Storm Name:  DORIAN     Date:  20190902 Time:  0        Latitude:  26.60        Longitude:  -77.70      Windspeed:  155MPH      Pressure:  914mb
Storm Name:  DORIAN     Date:  20190902 Time:  215      Latitude:  26.60        Longitude:  -77.80      Windspeed:  155MPH      Pressure:  914mb
Storm Name:  DORIAN     Date:  20190902 Time:  600      Latitude:  26.60        Longitude:  -78.00      Windspeed:  145MPH      Pressure:  916mb
Storm Name:  LORENZO    Date:  20190929 Time:  300      Latitude:  24.30        Longitude:  -45.00      Windspeed:  140MPH      Pressure:  925mb

Search Result:  8 results found for 140

        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        0) Exit the Program
Please Enter an Option [0-6]:  6

Please enter pressure [maximum]:  920

Storm Name:  DORIAN     Date:  20190901 Time:  1640     Latitude:  26.50        Longitude:  -77.00      Windspeed:  160MPH      Pressure:  910mb
Storm Name:  DORIAN     Date:  20190901 Time:  1800     Latitude:  26.50        Longitude:  -77.10      Windspeed:  160MPH      Pressure:  910mb
Storm Name:  DORIAN     Date:  20190902 Time:  0        Latitude:  26.60        Longitude:  -77.70      Windspeed:  155MPH      Pressure:  914mb
Storm Name:  DORIAN     Date:  20190902 Time:  215      Latitude:  26.60        Longitude:  -77.80      Windspeed:  155MPH      Pressure:  914mb
Storm Name:  DORIAN     Date:  20190902 Time:  600      Latitude:  26.60        Longitude:  -78.00      Windspeed:  145MPH      Pressure:  916mb

Search Result:  5 results found for 920

        1) Display Information for Storm(s) [from Entry #]
        2) Display Information for Storm(s) [by Date]
        3) Display Information for Storm(s) [by Name (Exact)]
        4) Display Information for Storm(s) [by Name (Partial)]
        5) Display Information for Storm(s) [by Windspeed (Minimum)]
        6) Display Information for Storm(s) [by Pressure (Maximum)]
        0) Exit the Program
Please Enter an Option [0-6]:  0

Results provided by Jason Gardner
*/