/*
 *	Programmer:	C by Discovery
 *	Course:		COP 2220
 *  File:		qsort.c
 *
 * Synopsis  - Sorts an array of ints and an array of structures.
 *             The structures are sorted by name (a string) and
 *             by age (an int). The arrays are displayed before
 *             and after sorting.
 *
 * Objective - To study and use pointers to functions and study
 *             an example using the library function qsort.
 */
// Includes
#include <stdio.h>
#include <stdlib.h>                                 /* Note 1 */
#include <string.h>

// Defines
#define NUMELTS 5

// Structure definitions

// typedef
typedef struct
{
    char *name;
    char *lastName;
    int age;
} member_t;


/* Function Prototypes */                           /* Note 2 */
int compare_ints( const void *a, const void *b);
int compare_age( const void *x, const void *y);
int compare_name( const void *x, const void *y);
int compare_name2( const void *x, const void *y);
void print( char * l, member_t x[], int num );
void print_ints( char * label, int ints[], int num );

// main function
int main(void)
{
    char *list[5] = { "cat", "cart", "cabin", "cap", "can" };
    int integers[6] = { 45, 36, 12, 88, 99, 10 };
    static member_t ary[NUMELTS] =	{  {"ralph", "laurel", 42},
        {"helen", "troy", 45},
        {"todd", "stone", 20},
        {"louise", "fall", 12},
        {"sharon", "stone", 23},
    };

    print_ints( "Integers before sorting", integers, 6 );
    /* Note 3 */
    qsort((void *)integers, 6, sizeof(integers[0]), compare_ints);
    print_ints( "Integers after sorting", integers, 6 );

    print( "Original array", ary, 5 );

    qsort( (void *)ary, NUMELTS, sizeof(member_t), compare_name2 );
    print( "After sorting by last name", ary, 5 );


    /* Note 4 */
    qsort( (void *)ary, NUMELTS, sizeof(member_t), compare_age );
    print( "After sorting by age", ary, 5 );
    /* Note 5 */
    qsort( (void *)ary, NUMELTS, sizeof(member_t), compare_name );
    print( "After sorting by name", ary, 5 );

    system( "PAUSE" );

    return 0;
}

/*******************************compare_ints()******************/
/* PRECONDITION:  a and b are pointers to the objects being
 *                compared.
 *
 * POSTCONDITION: as qsort() requires, the value returned is -1 if
 *                a is less than *b, 0 if *a and *b are equal, and
 *                1 if *a is greater than *b.
 */
int compare_ints( const void *a, const void *b)
{
    /* Note 6 */
    if ( *(int * )a < *( int * )b )
        return -1;
    else if ( *(int *)a > *(int *)b )
        return 1;
    else
        return 0;
}

/*******************************compare_age()*******************/
/* PRECONDITION:  a and b are pointers to the objects being
 *                compared.
 *
 * POSTCONDITION: as qsort() requires, the value returned is -1 if
 *                the age in *a is less
 *                than the age in *b, 0 if the ages are equal, and
 *                1 if the age in *a is greater than that in *b.
 */
int compare_age( const void *x, const void *y)
{
    /* Note 7 */
    if ( ((member_t * )x)->age < ( (member_t * )y)->age )
        return -1;
    else if ( ((member_t *)x)->age > ((member_t *)y)-> age )
        return 1;
    else
        return 0;
}

/*******************************compare_name()******************/
/* PRECONDITION:  a and b are pointers to the objects
 *                being compared.
 *
 * POSTCONDITION: as qsort() requires, the value returned is -1 if
 *                the name in *a comes before the name in *b
 *                alphabetically, 0 if the names are identical, and
 *                1 if the name in *a comes after the name in *b.
 */
int compare_name( const void *x, const void *y)
{
    /* Note 8 */
    return ( strcmp( ((member_t * )x)->name, ((member_t * )y)->name ));
}

int compare_name2( const void *x, const void *y)
{
    int result;

    result = strcmp( ((member_t * )x)->lastName, ((member_t * )y)->lastName );
    if ( result == 0 )
        result = strcmp( ((member_t * )x)->name, ((member_t * )y)->name );
    return result;
}

/*******************************print()*************************/
/* PRECONDITION:  l is a null-terminated string that will be output
 *                before the contents of the array; x is the array
 *                of member_ts, and num is the number of
 *                elements in x.
 *
 * POSTCONDITION: the string l is displayed followed by
 *                the contents of x.
 */
void print( char *label, member_t array[], int num )
{
    int i;

    printf( "%s\n", label );
    for (i = 0; i < num; i++)
        printf("%s %s\t %d\n", array[i].name, array[i].lastName, array[i].age);
    printf("\n");
}

/*******************************print_ints()********************/
/* PRECONDITION:  label is a null-terminated string that will be
 *                displayed before the contents of the array; x is the
 *                array of member_ts, and num is the number
 *                of elements in x.
 *
 * POSTCONDITION: the string label is displayed followed
 *                by the contents of x.
 */
void print_ints( char * label, int ints[], int num )
{
    int i;

    printf( "%s\n", label );
    for (i = 0; i < num; i++)
        printf("%d ", ints[i]);
    printf( "\n");
}
