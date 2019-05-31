#include <stdio.h>
#include <stdlib.h> // Note: this is necessary now

int main()
{
    float *f; int n;
    printf ("Enter an integer >= 3: ");
    scanf("%d", &n);
    f = (float *) malloc(n * sizeof(float));

    f[0] = 0.52;
    printf ("Now enter the value of the 3rd element: ");
    scanf("%f", &f[3]); //Overflow if n<=3
    printf("%f\n", *f + f[3]);
    return 0;
}


