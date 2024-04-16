/* COP2220C Wednesday October 14, 2020
 * Author: Jason Gardner, Aboubacar Abdoulaye
 * Filename: week-7_breakout.c
 * Purpose: 
 * Objective: 
 */

// Headers
#include <stdio.h>
#include <string.h>

// Definitions
#define NAME_LENGTH 80
#define NUM_PRESIDENTS 44
// Structures

// Function Prototypes
void displayPresident(char *firstName, char *lastName, int birthYear, int birthMonth, int birthDay);

// Main Function
int main(void)
{
    // String Literals for I/O and User Experience

    // Variable Declaration/Initialization
    
    char inputData[NUM_PRESIDENTS][NAME_LENGTH] = {"John Adams 1767 7 11",
                                                   "John Adams 1735 10 30",
                                                   "Chester Arthur 1829 10 5",
                                                   "James Buchanan 1791 4 23",
                                                   "George Bush 1924 6 12",
                                                   "George Bush 1946 7 6",
                                                   "James Carter 1924 10 1",
                                                   "Grover Cleveland 1837 3 18",
                                                   "William Clinton 1946 8 19",
                                                   "Calvin Coolidge 1872 7 4",
                                                   "Dwight Eisenhower 1890 10 14",
                                                   "Millard Fillmore 1800 1 7",
                                                   "Gerald Ford 1913 7 14",
                                                   "James Garfield 1831 11 19",
                                                   "Ulysses Grant 1822 4 27",
                                                   "Warren Harding 1865 11 2",
                                                   "Benjamin Harrison 1833 8 20",
                                                   "William Harrison 1773 2 9",
                                                   "Rutherford Hayes 1822 10 4",
                                                   "Herbert Hoover 1874 8 10",
                                                   "Andrew Jackson 1767 3 15",
                                                   "Thomas Jefferson 1743 4 13",
                                                   "Andrew Johnson 1808 12 29",
                                                   "Lyndon Johnson 1908 8 27",
                                                   "John Kennedy 1917 5 29",
                                                   "Abraham Lincoln 1809 2 12",
                                                   "James Madison 1751 3 16",
                                                   "William McKinley 1843 1 29",
                                                   "James Monroe 1758 4 28",
                                                   "Richard Nixon 1913 1 9",
                                                   "Barack Obama 1961 8 4",
                                                   "Franklin Pierce 1804 11 23",
                                                   "James Polk 1795 11 2",
                                                   "Ronald Reagan 1911 2 6",
                                                   "Franklin Roosevelt 1882 1 30",
                                                   "Theodore Roosevelt 1858 10 27",
                                                   "William Taft 1857 9 15",
                                                   "Zachary Taylor 1784 11 24",
                                                   "Harry Truman 1884 5 8",
                                                   "Donald Trump 1946 6 14",
                                                   "John Tyler 1790 3 29",
                                                   "Martin VanBuren 1782 12 5",
                                                   "George Washington 1732 2 22",
                                                   "Woodrow Wilson 1856 12 28"};

    char firstNames[NUM_PRESIDENTS][NAME_LENGTH] = {0};
    char lastNames[NUM_PRESIDENTS][NAME_LENGTH] = {0};
    int birthYears[NUM_PRESIDENTS] = {0};
    int birthMonths[NUM_PRESIDENTS] = {0};
    int birthDays[NUM_PRESIDENTS] = {0};

    //
    for (int i = 0; i < NUM_PRESIDENTS; i++)
    {
        sscanf(inputData[i], "%s %s %i %i %i", firstNames[i], lastNames[i], &birthYears[i], &birthMonths[i], &birthDays[i]);
    }

    for (int i = 0; i < NUM_PRESIDENTS; i++)
    {
        displayPresident(firstNames[i], lastNames[i], birthYears[i], birthMonths[i], birthDays[i]);
    }
    // Return
    return 0;
}

int getOption(void) {
    // String Literals for I/O and User Experience
    const char *OPTION_ALL = "Display Information for Presidents [All]\n";
    const char *OPTION_JOHNS = "Display Information for Presidents [Name: John]\n";
    const char *OPTION_JULY = "Display Information for Presidents [Birth Month: July]\n";
    const char *OPTION_SEARCH_NAME = "Display Information for Presidents [Search by: Name]\n";
    const char *OPTION_SEARCH_BIRTHMONTH = "Display Information for Presidents [Search by: Birth Month]\n";
    const char *EXIT_PROGRAM = "Exit the Program\n";
    const char *PROMPT_INPUT = "Please Enter an Option [0-%d]:  ";

    // Variable Declaration/Initialization
    int numOptions = 6;
    int input = -1;

    // While input is invalid (outside number of options)
    while (input < 0 || input > numOptions) {
        // Display the program option prompt to user and take input
        printf("\n1) %s2) %s3) %s4) %s5) %s0) %s\n",
                OPTION_ALL,
                OPTION_JOHNS,
                OPTION_JULY,
                OPTION_SEARCH_NAME,
                OPTION_SEARCH_BIRTHMONTH,
                EXIT_PROGRAM);
        printf(PROMPT_INPUT, numOptions);
        scanf("%d", &input);
    }
    return input;
}

void displayPresident(char *firstName, char *lastName, int birthYear, int birthMonth, int birthDay)
{
    printf("%s %s was born on %i/%i/%i\n", firstName, lastName, birthYear, birthMonth, birthDay);
}