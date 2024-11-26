#include <stdio.h>
#define PI 3.14159

int main(void)
{
    int numOfSummands = 500, iterator;
    double result = 0.0;
    double desiredValue;

    printf("\nNumerical calculation of inverse square infinite sum\n\n"); 
    /* 1/1^2 + 1/2^2 + 1/3^2 + ... = pi^2 / 6 */

    desiredValue = PI * PI / 6.0;
    printf("Desired value is %lf\n\n", desiredValue);

    for (iterator = 1 ; iterator <= numOfSummands ; iterator++) {
        printf("Iteration %d\n", iterator);
        result = result + 1.0 / (iterator * iterator);
        printf("Result till this iteration = %lf\n", result);
        printf("Desired value = %lf\n", desiredValue);
        printf("Error = %lf\n\n", desiredValue - result);
    }

    return 0;
}
