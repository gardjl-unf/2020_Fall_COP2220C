#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN_LINE 80

int main (void) {
    char *line = malloc(LEN_LINE * sizeof(char));
    char *pNewLine;

    printf("Enter your full name:  ");
    fgets(line, LEN_LINE, stdin);
    pNewLine = strchr(line, '\n');
    if (pNewLine) {
        *pNewLine = '\0';
    }
    printf("Your name is %s.\n", *line);

    free(line);
    return 0;
}