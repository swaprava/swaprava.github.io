#include <stdio.h>
//#define PI 3.14159

// What if the desired value was not known?

int main(void)
{
    // no desired value, no number of summands
    int iterator;
    double result = 0.0, currentValue;
    double margin = 1E-8, actualDiff;

    printf("\nNumerical calculation of inverse square infinite sum\n\n"); 
    /* 1/1^2 + 1/2^2 + 1/3^2 + ... = pi^2 / 6 */

    //Initialization 
    currentValue = result;
    actualDiff = 2 * margin; // this is used such that the check passes first time
                                    // but you may use anything larger than the margin

    for (iterator = 1 ; actualDiff > margin ; iterator++) {
        printf("Iteration %d\n", iterator);
        result = result + 1.0 / (iterator * iterator);

        printf("Current value = %f\n", currentValue);
        printf("Updated value in this iteration = %f\n", result);
        actualDiff = result - currentValue;
        printf("Difference value = %f\n", actualDiff);
        printf("Tolerance margin = %f\n\n", margin);

        // VERY IMPORTANT: current value must be updated
        currentValue = result;
    }

    printf("Converged in %d iterations\n\n", iterator);

    return 0;
}