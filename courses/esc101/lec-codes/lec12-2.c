#include <stdio.h>

int main ()
{
    int n, x;
    printf("Enter an integer: ");
    scanf("%d", &n);     // input n

    x = 1;                // [while] initialization
    while (x <= n) {    // [while] condition

        if (x%3 == 0)
            printf("%d is divisible by 3\n", x);

        if (x%5 == 0)
            printf("%d is divisible by 5\n", x);

        //x = x+1;            // [while] update
    }
    
    return  0;
}
