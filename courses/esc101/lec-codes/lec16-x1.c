#include <stdio.h>
#include <stdlib.h>

// int callCount = 0;

int fibonacci (int num, int callDepth) 
{
    for (int i=0; i < callDepth ; i++)
        printf ("  ");

    printf ("Calling fibonacci with %d\n", num);
    // callCount++ ;
 
    if (num <= 0) {
        printf ("Wrong entry ... exiting\n");
        exit(1);
    }

    if (num <= 2)
        return 1;
    else {
        callDepth++ ;
        return fibonacci (num - 1, callDepth) + fibonacci (num - 2, callDepth);
    }
        
        
}

int main()
{
    int num;

    printf ("Enter the number: ");
    scanf ("%d", &num);

    printf ("Fibonacci number %d is %d\n", num, fibonacci(num, 0));

    // printf ("Total number of calls to fibonacci = %d\n", callCount);

    return 0;
}