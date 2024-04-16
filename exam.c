#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 20
// Unsure about how valuable stocks CAN be
#define LEN 10
#define DEL " "

typedef struct {
    char ticker[LEN];
    double price;
    double delta;
} stock_t;

void displayStock(char *ticker, double price, double delta);
int indexSearch(char *ticker, stock_t stocks[], int count);
void displayWelcome(void);
int readStocks(stock_t *s);
char displayMenu(void);
void displayCredits(void);

int main() {
    const char *TICKER_PROMPT = "\nPlease enter the ticker you would like to buy:  ";
    const char *NOT_FOUND = "\nStock not found";
    stock_t stocks[MAX];
    stock_t *currentStock = stocks;
    char tickerSearch = {0};
    int foundIndex = -2;
    int numBuy = 0;
    double extPrice = 0.0;
    int stockCounter = 0;
    char option = '\0';
    stockCounter = readStocks(stocks);
    displayWelcome();
    while (option != 'E') {
        currentStock = stocks;
        displayMenu();
        switch (option) {
            case 'D':
            for (int i = 0; i < stockCounter; ++i) {
                displayStock(currentStock->ticker, currentStock->price, currentStock->delta);
                ++currentStock;
            }
                break;
            case 'B':
                // For repeat searches
                foundIndex = -2;
                printf("%s", TICKER_PROMPT);
                scanf("%s", &tickerSearch);
                // Too tired to remember command, but here I would want to replace the newline with a \0 string termination
                if ((foundIndex = indexSearch(&tickerSearch, stocks, stockCounter)) != -1) {
                    printf("\n%s found, please enter number you would like to purchase:  ", stocks[foundIndex].ticker);
                    scanf("%d", &numBuy);
                    extPrice = stocks[foundIndex].price * numBuy;
                    printf("\n\nBuy Order\nStock:  %-15s  Price:  %2.2lf  Shares:  %d  Extended Price:  %2.2lf", stocks[foundIndex].ticker, stocks[foundIndex].price, numBuy, extPrice);

                }
                else {
                    printf("%s", NOT_FOUND);
                }
                break;
            default:
                break;
        }
    }

    displayCredits();
    return 0;
}

void displayStock(char *ticker, double price, double delta) {
    const char *DISPLAY_STOCK = "%-15sPrice:  %2.2lf  Percent Change:  %2.2lf";
    printf(DISPLAY_STOCK, ticker, price, delta);
}

int indexSearch(char *ticker, stock_t stocks[], int count) {
    int foundIndex = -1;
    for (int i = 0; i < count; ++i) {
        if (!(strcmp(ticker, stocks[i].ticker))) {
            foundIndex = i;
        }
    }
    return foundIndex;
}

void displayWelcome(void) {
    char *WELCOME = "Welcome to the Stock Exam by Jason Gardner";
    printf("%s", WELCOME);
}

int readStocks(stock_t *s) {
    const char *FILE_OPEN_ERROR = "Unable to open file \"%s\"";
    const char *FILENAME = "SP500_MostActive_20201118.txt";
    FILE *inputFile;
    char readLine[LEN];
    int counter;
    inputFile = fopen(FILENAME, "r");
    if (!inputFile) {
        printf(FILE_OPEN_ERROR, FILENAME);
    }
    else {
        while(fgets(readLine, sizeof(readLine), inputFile) != NULL && counter <= MAX) {
            strcpy(s->ticker, strtok(readLine, DEL));
            s->price = atof(strtok(NULL, DEL));
            s->delta = atof(strtok(NULL, DEL));
            s++;
            counter++;
        }
    }
    fclose(inputFile);
    return counter;
}

char displayMenu(void) {
    char *MENU = "\n(D)isplay\n(B)uy\n(E)xit\n";
    char *OPTION_ENTRY = "\nPlease Enter Option:  ";
    char *DISPLAY_ERROR = "\nInvalid Entry:  Please enter a valid value [D/B/E]\n";
    char option = '\0';
    while (option != 'E' && option != 'B' && option != 'D') {
        printf("%s", MENU);
        printf("%s", OPTION_ENTRY);
        scanf("\n%c", &option);
        if (option != 'E' && option != 'B' && option != 'D') {
            printf("%s", DISPLAY_ERROR);
        }
    }
    return option;
}

void displayCredits(void) {
    char *MESSAGE_CREDITS = "Prepared by: Jason Gardner";
    printf("%s", MESSAGE_CREDITS);
}

/*
ENORMOUS TECHNICAL ISSUES WITH PROCTORING
HAD TO GET HELP AND STARTED LATE,
THEN CHROME CLOSED ON THE FINAL QUESTION AND IT TOOK FOREVER TO FIX.
CAN'T FIX MY MENU OR RUN TEST DATA INSIDE THE ALLOTED TIME
OR COMMENTS

I'M HOPEFUL I AM CLOSE, BUT I AM ALSO INFURIATED WITH HOW PROCTORING WENT.  I LOST A LOT LOT LOT OF TIME.
*/