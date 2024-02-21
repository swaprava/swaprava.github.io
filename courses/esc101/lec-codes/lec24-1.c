#include <stdio.h>

int main() 
{
    int a[5] = {1,2,3,4,5};
    void * p;
    p = a;
    printf ("%p\n", p);
    // printf ("%p\n", *(p+1));
    printf ("%d\n", *((int *) p + 2));
    return 0; 
} 