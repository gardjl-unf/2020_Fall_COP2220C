#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 80
#define NUM 100
#define DELIMITER " "

typedef struct {
    char name[LEN];
    char ethnicity[LEN];
    int age;
} person_t;

int  main () {
    FILE *file;
    char readLine[LEN];
    person_t fileInput[NUM];
    person_t *p = fileInput;
    int personCounter = 0;
    file = fopen("testdata.txt", "r");

    while (fgets(readLine, sizeof(readLine), file) && personCounter <= NUM) {
        strcpy(p->name, strtok(readLine, DELIMITER));
        strcpy(p->ethnicity, strtok(NULL, DELIMITER));
        p->age = atoi(strtok(NULL, DELIMITER));
        p++;
        personCounter++;
    }
    p = fileInput;
    for (int i = 0; i < personCounter; ++i) {
        printf("%s is %s and is %d", p->name, p->ethnicity, p->age);
        p++;
    }
    return 0;
}