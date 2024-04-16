/* COP2220C Exam 4 Program
 * Filename: exam-4_gardner-jason_cop2220c.c
 * Author: Jason Gardner
 * Date: December 9, 2020
 */

// I truly enjoyed this course, professor Gehrig.  Thank you.

// Header Files
#include <stdio.h>
#include <ctype.h>
#include <string.h>
//#include <stdlib.h>

// Definitions
#define MAX_PACKAGES 20
#define OPTION_LEN 25
#define SIZE_LEN 5

// Structure(s)
typedef struct {
    char size[SIZE_LEN];
    double price;
    char sameDay;
} reprint_t;

// Function Prototypes
void displayWelcome (void);
void displayCredits (void);
char getOption (void);
int loadData (reprint_t *reprint);
void displayReprint (reprint_t *reprint);
int searchStatus (char searchStatus, reprint_t reprints[], int numPackages);
int searchSize (char *size, reprint_t reprints[], int numPackages);

/* main
 * Runs at program start
 * @param void - none
 * @return int - program status
 */
int main () {
    // String Literals - I/O and User Experience
    const char* SEARCH_PROMPT = "Please enter %s:  ";
    const char* DISPLAY_MATCHES = "%d matches found.\n";

    // Variable Declaration/Initialization
    reprint_t reprints[MAX_PACKAGES] = {0};
    reprint_t *data = reprints;
    char option = '\0';
    char searchStatus = '\0';
    char *newLine = '\0';
    char size[SIZE_LEN+1];

    // Call displayWelcome to display welcome messasge
    displayWelcome();

    // If we successfully load the data
    if (loadData(data)) {
        do {
           option = getOption();
           switch (option) {
                case('D'):
                // D: Display by availible status
                    printf(SEARCH_PROMPT, "availability status [Y/N]");
                    scanf(" %c", searchStatus);
                    break;
                case('O'):
                // O: Display by size and order
                    printf(SEARCH_PROMPT, "size [(width)x(height)]");
                    scanf("%5s", searchSize);
                    if (newLine = strchr(searchStatus, '\n')) {
                        newLine = '\0';
                    }
                    if ()
                    break;
                case('E'):
                // E: Exit
                    break;
                default:
                // default:  Default (nothing) case
                    break;
           }
        } while (option != 'E');
    }
// strchr (remember this for a minute from meow)

    // Call displayCredits to display credits message
    displayCredits();
}

/* displayWelcome
 * Display welcome message to user
 * @param void - none
 * @return void - none
 */
void displayWelcome () {
    // String Literals - I/O and User Experience
    const char *WELCOME_MESSAGE = "Welcome to the Photo Reprint Ordering System by Jason Gardner\n";

    // Display welcome message to user
    printf("%s", WELCOME_MESSAGE);
}

/* displayCredits
 * Display credits message to user
 * @param void - none
 * @return void - none
 */
void displayCredits () {
    // String Literals - I/O and User Experience
    const char *CREDITS_MESSAGE = "Prepared by: Jason Gardner";

    // Display credits message to user
    printf("%s", CREDITS_MESSAGE);
}

/* getOption
 * Display menu to user, get input from them, and return it to caller
 * @param void - none
 * @return char - chosen user option (NOTE:  THIS SHOULD BE RETURNED IN UPPERCASE)
 */
char getOption () {
    // String Literals - I/O and User Experience
    const char *OPTION_MENU[OPTION_LEN] = { 
                                "(D)isplay by Available Status\n",
                                "(O)rder by Size\n",
                                };
    const char *OPTION_EXIT = "(E)xit\n";
    const char *INPUT_PROMPT = "\nPlease enter an option D/O/E:  ";
    const char *INPUT_ERROR = "\nError:  Please enter a valid option [D, O, or E]";

    // Variable Declaration/Initialization
    char option = '\0';
    int const numOptions = 2;

    // Do (posttest) while we have an invalid input value
    do {
        // Display all of the menu options and exit option (iterate through them to numOptions)
        // I realize this is overkill.  I wanted to write this on a time limit to see if I could
        for (int i = 0; i < numOptions; i++) {
            printf("%s", *(OPTION_MENU + i));
        }
        printf("%s", OPTION_EXIT);

        // Prompt user for a character input and store that in option
        printf("%s", INPUT_PROMPT);
        scanf(" %c", option);
        // Change the user entry to uppercase under the assumption they'll potentially give us a lowercase option that is otherwise valid
        option = toupper(option);
        // Notify user they've entered an invalid value (if they have)
        if (option != 'D' && option != 'O' && option != 'E') {
            printf("%s", INPUT_ERROR);
        }
    } while (option != 'D' && option != 'O' && option != 'E');
    return option;
}

/* loadFile
 * Load file containing photo data
 * @param reprint_t reprint - structure containing photo reprint data (base address pointer)
 * @return int - number of loaded members
 */
int loadData (reprint_t *reprint) {
    // String Literals - I/O and User Experience
    const char *FILE_OPEN_ERROR = "Error:  Failed to open file %s";
    const char *FILENAME = "PrintPrices.txt";
    const char *FILE_FORMAT = "%s %lf %c";

    // Variable Declaration/Initialization
    int numPackages = 0;
    FILE *inputFile;

    // If we can open inputFile (in read mode)
    if (inputFile = fopen(FILENAME, "r")) {
        // While we pull in the input data, process it through the input format and put it into members at our pointer
        // This is broken, fix it
        while(fscanf(inputFile, FILE_FORMAT, reprint->size, reprint->price, reprint->sameDay) && numPackages <= MAX_PACKAGES) {
            // Increment the pointer (to the next member)
            reprint++;
            // Increment the number of print packages we have in our data structure
            numPackages++;
        }
    }
    else {
        // Display error message to user
        printf(FILE_OPEN_ERROR, FILENAME);
    }
    // Close the inputFile
    fclose(inputFile);
    // Return numPackages to caller
    return numPackages;
}

/* displayReprint
 * Display data from member for a specific reprint package
 * @param reprint_t *reprint - structure containing photo reprint data (pointer to specific member)
 * @return void - none
 */
void displayReprint (reprint_t *reprint) {
    // String Literals - I/O and User Experience
    const char *DISPLAY_PACKAGE = "Size:  %s\tPrice:  $%.2lf\tSame Day Available:  %c\n";

    // Display the current member using our display format
    printf(DISPLAY_PACKAGE, reprint->size, reprint->price, reprint->sameDay);
}

/* searchStatus
 * Search members for same day availibility status and print those ones (returning the number we printed)
 * @param char status - Status we're looking for (Y or N)
 * @param reprint_t reprints[] - The array of photo packages
 * @param int numPackages - The number of available packages (so we don't leave the array)
 * @return int - the number of matching packages
 */
int searchStatus (char searchStatus, reprint_t reprints[], int numPackages) {
    // Variable Declaration/Initialization
    int numResults = 0;
    int offset = 0;
    reprint_t *m = reprints;

    for (; offset < numPackages; offset++) {
        if ((m+offset)->sameDay == searchStatus) {
            numResults++;
        }
    }
    return numResults;
}

/* searchSize
 * Search members for same day availibility status and print those ones (returning the number we printed)
 * @param char status - Size we're looking for (we should have a maximum of a 5 character string here)
 * @param reprint_t reprints[] - The array of photo packages
 * @param int numPackages - The number of available packages (so we don't leave the array)
 * @return int - the number of matching packages
 */
int searchSize (char *size, reprint_t reprints[], int numPackages) {
    // Variable Declaration/Initialization
    int numResults = 0;
    int offset = 0;
    reprint_t *m = reprints;

    for (; offset < numPackages; offset++) {
        if (!strcmp(searchSize, (m+offset)->size)) {
            numResults++;
        }
    }
    return numResults;
}

/* Test data and expected results:
D Y, O 5x7 2, O 12x14 1, E.
D Y Should display same day yes entries:
All but entry 7, which is 9 total entries (of the 10)
O 5x7 2 Should display the order dialogue for a 5x7, and give the user a price for it 2.99, and the extended price for 2, 5.98
O 12x14 1 Won't be found.  No matching data.
E will exit the program.
*/

