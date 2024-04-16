/* COP2220C 02DEC2020
 * Author: Jason Gardner
 * Filename: project-7_MAINT_gardner-jason_cop2220c.c
 * Purpose: Data Maintenence Functions for Loaded Hurricane Data
 */

//#define DEBUG

// Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "project-7_MAINT_gardner-jason_cop2220c.h"

/* maintenance
 * Perform maintenence functions on array of storms (add/modify/delete/save)
 *
 * @param storm_t *s - pointer to storm_t structure
 * @param int numEntries - number of entries in the storm_t array
 * 
 * @return int - number of entries
 */
int maintenance(storm_t *s, int numEntries) {
    // String Literals for I/O and User Experience
    const char *MAINT_PROMPT = "Please enter %s:  ";
    const char *ERROR_NOSPACE = "\nError:  Storm Data Full (%i Entries)\nPlease delete or modify existing entries.\n\n";

    // Variable Declaration/Initialization
    int maintOption = -1;
    int stormNumber = 0;
    storm_t *currentStorm = s;

    // do-while menuOption isn't 0
    do {
        maintOption = maintGetOption();
        switch (maintOption) {
            case 0:
            // 0: Exit maintenence menu
                break;
            case 1:
            // 1: Add storm data (to end of array)
                // Set currentStorm pointer to base address offset by number of entries
                currentStorm = s + numEntries;
                // As long as that doesn't exceed the array size
                if (numEntries < NUM_STORMS) {
                    // Call modifyEntry to create the record
                    modifyEntry(currentStorm);
                    // Increment the number of storms
                    numEntries++;
                    #ifdef DEBUG
                    printf("Record (%i) Added\n", numEntries);
                    displayStorm(currentStorm);
                    #endif
                }
                // If we're going to exceed the array size
                else {
                    // Display error
                    printf(ERROR_NOSPACE, numEntries);
                }
                break;
            case 2:
                // Prompt user for record number and store as stormNumber
                printf(MAINT_PROMPT, "record number to be changed");
                scanf("%i", &stormNumber);
                // Set currentStorm pointer to that record offset
                currentStorm = s + stormNumber - 1;
                // Call modifyEntry to change the record
                modifyEntry(currentStorm);
                #ifdef DEBUG
                printf("Record (%i) Modified\n", stormNumber);
                displayStorm(currentStorm);
                #endif
                break;
            case 3:
                // Prompt user for record number and store as stormNumber
                printf(MAINT_PROMPT, "record number to be deleted");
                scanf("%i", &stormNumber);
                // Set currentStorm pointer to that record offset
                currentStorm = s + stormNumber - 1;
                // Set number of entries to the return from deleteRecord
                numEntries = deleteRecord(currentStorm, numEntries);
                break;
            case 4:
            // 4:  Save storm data to file
                // Call saveData to save storm data currently in memory
                saveData(s, numEntries);
                break;
            default:
            // default: break
                break;
        }
    } while (maintOption);
    // Return numEntries to caller
    return numEntries;
}
/* maintGetOption
 * Display maintenence menu to user and pass option chosen back to caller
 * 
 * @param void - none
 * @return int - menu option chosen by user
 */
int maintGetOption(void) {
    // String Literals for I/O and User Experience
    const char OPTIONS[][LINE_LEN] = {"Add Storm Data\n",
                                      "Modify Storm Data\n",
                                      "Delete Storm Data\n",
                                      "Save Storm Data to File\n"
                            };
    const char *PRINT_OPTIONS = "\t%d) %s";
    const char *EXIT_PROGRAM = "\t0) Return to Main Menu\n";
    const char *PROMPT_INPUT = "Please Enter an Option [0-%d]:  ";
    const char *INPUT_ERROR = "\nInvalid Entry:  Please Enter a Number Between 0 and %d\n\n";

    // Variable Declaration/Initialization
    const int NUM_OPTIONS = 4;
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

/* modifyEntry
 * Change storm data at pointer
 * 
 * @param storm_t *s - pointer to storm data
 * 
 * @return void - none
 */
void modifyEntry(storm_t *s) {
    // String Literals for I/O and User Experience
    const char *MAINT_PROMPT = "Please enter %s:  ";

    // Variable Declaration/Initialization
    int inputNum = 0;
    double inputFloat = 0.0;
    char readLine[NAME_LEN];
    char *newLine;
    
    // Prompt user for a string and store in readLine
    /* Exceeding this length blows up the entry and enters corrupt data.
     * Was not sure how to fix it, short of using the long buffer I started 
     * with and then checking if it was the length I intended (maybe).  It's
     * why I was using a super long input string, but it still could have run into
     * this issue.
     */
    printf(MAINT_PROMPT, "storm name");
    scanf("%24s", readLine);
    // If it ends in a newLine character, replace it with a terminator
    newLine = strchr(readLine, '\n');
    if (newLine) {
        *newLine = '\0';
        newLine = NULL;
    }
    // Change the characters to uppercase (otherwise sorting doesn't work as intended)
    for (int i = 0; i <= strlen(readLine); i++) {
        readLine[i] = toupper(readLine[i]);
    }
    // Copy readLine to stormName at our pointer
    strcpy(s->stormName, readLine);
    
    // Do-while date is invalid
    do {
        // Prompt user for integer and store it in inputNum
        printf(MAINT_PROMPT, "date [MMDD]");
        scanf("%i", &inputNum);
        // Store as date at our pointer
        s->date = inputNum + REMOVE_YEAR;
    } while (inputNum > 1231);
    // Do-while time is invalid
    do {
        // Prompt user for integer and store it in inputNum
        printf(MAINT_PROMPT, "time (Format 24H [HHMM])");
        scanf("%i", &inputNum);
        // Store as time at our pointer
        s->time = inputNum;
    } while (s->time > 2359);
    // Do-while latitude is invalid
    do {
        // Prompt user for a floating point value and store it in inputFloat
        printf(MAINT_PROMPT, "latitude");
        scanf("%lf", &inputFloat);
        // Store as latitude at our pointer
        s->latitude = inputFloat;
    } while (s->latitude < -180 || s->latitude > 180);
    // Do-while longitude is invalid
    do {
        // Prompt user for a floating point value and store it in inputFloat
        printf(MAINT_PROMPT, "longitude");
        scanf("%lf", &inputFloat);
        // Store as longitude at our pointer
        s->longitude = inputFloat;
    } while (s->longitude < -90 || s->longitude > 90);
    // Prompt user for integer and store it in inputNum
    printf(MAINT_PROMPT, "windspeed");
    scanf("%i", &inputNum);
    // Store as windspeed at our pointer
    s->windspeed = inputNum;
    // Prompt user for integer and store it in inputNum
    printf(MAINT_PROMPT, "pressure");
    scanf("%i", &inputNum);
    // Store as pressure at our pointer
    s->pressure = inputNum;
}

/* deleteRecord
 * Remove record at pointer, shifting all entries to numEntries to the left,
 * returning the new number of entries.
 * 
 * @param storm_t *s - Pointer to entry to be deleted
 * @param int numEntries - Number of storm data entries
 * 
 * @return int - New number of entries
 */
int deleteRecord(storm_t *s, int numEntries) {
    // I tried to use "storm_t n* = s+1" here, didn't work, and I'm not fighting with this
    // Iterate across the storm pointers for numEntries
    for (int i = 0; i < numEntries; i++, s++) {
        // Copy all of the data from the entry to the right [(n)ext] to the entry to the left
        strcpy(s->stormName, (s + 1)->stormName);
        s->date = (s + 1)->date;
        s->time = (s + 1)->time;
        s->latitude = (s + 1)->latitude;
        s->longitude = (s + 1)->longitude;
        s->windspeed = (s + 1)->windspeed;
        s->pressure = (s + 1)->pressure;
    }
    // Decrement numEntries
    numEntries--;
    #ifdef DEBUG
    printf("Record (%i) Deleted\n", stormNumber);
    #endif
    // Return numEntries to caller
    return numEntries;
}

void saveData(storm_t *s, int numEntries) {
    // String Literals for I/O and User Experience
    const char *PROMPT_FILENAME = "Please enter filename:  ";
    const char *FILE_OPEN_ERROR = "Error:  Could not open file \"%s\"";
    char fileName[NAME_LEN] = {0};
    const char *OUTPUT_FORMAT = "%s%s%i%s%i%s%2.2lf%s%2.2lf%s%i%s%i%s";
    const char *OUTPUT_LASTLINE_FORMAT = "%s%s%i%s%i%s%2.2lf%s%2.2lf%s%i%s%i";

    // Variable Declaration/Initialization
    char readLine[NAME_LEN];
    char *newLine;

    // Prompt user for a filename and store it in readLine
    printf(PROMPT_FILENAME);
    scanf("%24s", readLine);
    // If readLine ends in a newLine, replace it with terminator
    newLine = strchr(readLine, '\n');
    if (newLine) {
        *newLine = '\0';
        newLine = NULL;
    }

    // Copy user input to fileName and add a .txt extension
    strcpy(fileName, readLine);
    strcat(fileName, ".txt");

    /* Flush input buffer (bug prevention) -- There actually was a bug here and the first
     * record name string started with a "0" without pre-emptively clearing the buffer.
     * 
     * Full testing of the program also completely destroyed all of the data if user searched
     * data before sorting it if I only flushed one buffer here.  I've been very dubious
     * about buffer behavior in C throughout the course.  It feels FAR safer to assume it
     * will manage to pass corrupted data unexpectedly.
     */
    fflush(stdin);
    fflush(stdout);

    // Open file
    FILE *outputFile = fopen(fileName, "w");
    // If file fails to open
    if (!outputFile) {
        // Display error message
        printf(FILE_OPEN_ERROR, fileName);
    }
    else {
        // For each entry
        for (int i = 1; i <= numEntries; i++, s++) {
            // Until the final entry
            if (i != numEntries) {
                // Output data at entry to file
                fprintf(outputFile, OUTPUT_FORMAT, s->stormName, DELIMITER, s->date, DELIMITER,
                    s->time, DELIMITER, s->latitude, DELIMITER, s->longitude, DELIMITER,
                    s->windspeed, DELIMITER, s->pressure, END_DELIMITER);
            }
            // This is the final line, and the format string doesn't end with a newline
            else {
                fprintf(outputFile, OUTPUT_LASTLINE_FORMAT, s->stormName, DELIMITER, s->date, DELIMITER,
                    s->time, DELIMITER, s->latitude, DELIMITER, s->longitude, DELIMITER,
                    s->windspeed, DELIMITER, s->pressure);
            }
        }
        // Close outputFile
        fclose(outputFile);
    }
}