#include <stdio.h>

/* This program finds the fibonacci numbers within 50 on demand, if it is computed and available, it will produce it, otherwise will compute it */

int main()
{
    int length = 51, num, currIndex = -1;
    int fib[length];

    char answer = 'y';

    while (answer == 'y' || answer == 'Y') {

        printf ("Which fibonacci number do you want (enter a nonnegative integer <= 50): ");
        scanf ("%d", &num);

        if (num <= currIndex) {
            printf ("We have it ready, it is fib[%d] = %d\n", num, fib[num]);
        }
        else {
            printf ("Don't have in store (have till %d), need to compute\n", currIndex);
            if (num <= 1)
            {
                for (int j = currIndex+1; j<=num ; j++)
                {
                    fib[j] = j;
                    printf ("fib[%d] = %d\n", j, fib[j]);
                }
                    
            }    
            else 
            {
                if (currIndex < 0)
                {
                    fib[0] = 0;
                    fib[1] = 1;
                    printf("fib[0] = 0\nfib[1] = 1\n");
                    currIndex = 1;
                }
                if (currIndex == 0)
                {
                    fib[1] = 1;
                    printf("fib[1] = 1\n");
                    currIndex = 1;
                }
                for (int k = currIndex+1; k <=num; k++) 
                {
                    fib[k] = fib[k-1] + fib[k-2];
                    printf ("fib[%d] = %d\n", k, fib[k]);
                }
            }

            currIndex = num;

        }

        printf ("Want to continue (y/n) : ");
        scanf (" %c", &answer);
    }

    return 0;
}
