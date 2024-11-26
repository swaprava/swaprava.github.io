#include <stdio.h>
#include <stdlib.h> // Note: this is necessary now

int main()
{
    float *p, *np; int n;
    printf ("Enter an integer >= 3: ");
    scanf("%d", &n);
    p = (float *) malloc(n * sizeof(float));

    p[0] = 0.52;
    printf ("Now enter the value of the 3rd element: ");
    scanf("%f", &p[3]); //Overflow if n<=3
    printf("%f\n", *p + p[3]);

    // p = (float *) malloc(2 * n * sizeof(float));
    // printf("%f\n", *p + p[3]);

    np = (float *) realloc(p, 2 * n * sizeof(float));
    printf("%f\n", *np + np[3]);
    return 0;
}