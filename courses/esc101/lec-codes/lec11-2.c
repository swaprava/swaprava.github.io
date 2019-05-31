#include <stdio.h>

int main(void) 
{

    int n, i;
    double sum = 0.0;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    printf("Entered value of n is %d\n\n", n);

    for (i = 1; i <= n; i++) {

        printf("Iteration %d\n", i);
        sum = sum + 1.0 / i;
        printf("partial sum till this iteration is %lf\n\n", sum);

    }

    printf("Final value of sum = %lf \n \n", sum);

    return 0;
}