#include <stdio.h>
#define NUM 0 // conditional preprocessor

int main()
{
    //int NUM = 10;
    #if(NUM == 0)
       printf("\nNumber is Zero\n");
    #elif(NUM > 0)
       printf("\nNumber is Positive\n");
    #else
       printf("\nNumber is Negative\n");
    #endif

    return 0;
}