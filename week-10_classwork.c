#include <stdio.h>
#include "CALCDEFS.H"

int main(void) {
    char operator = '0';
    double a = 0.0;
    double b = 0.0;
    double r = 0.0;
    printf("Welcome to the Calculator by Jason Gardner\n\n");
    printf("Please enter the first number:  ");
    scanf("%lf", &a);
    printf("Please enter the second number:  ");
    scanf("%lf", &b);
    printf("Please enter the operator (+, -, *, /, or q to quit):  ");
    scanf(" %c", &operator);
    switch (operator) {
        case '+':
            r = add(a,b);
            printf("Result is %.2lf", r);
            break;
        case '-':
            r = subtract(a,b);
            printf("Result is %.2lf", r);
            break;
        case '*':
            r = multiply(a,b);
            printf("Result is %.2lf", r);
            break;
        case '/':
            r = divide(a,b);
            printf("Result is %.2lf", r);
            break;
        case 'q':
            break;
        default:
            printf("Error:  Invalid Operator");
            break;
    }

}