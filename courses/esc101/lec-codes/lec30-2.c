#include <stdio.h>
#include <stdlib.h>

// Addition of any number of elements

int main(int argc, char const *argv[])
{
    int numOfElements = (argc + 1) / 2;
    float sum = 0.0;

    for (int i = 0; i < numOfElements; i++) {
        sum += atof(argv[2*i + 1]);
    }

    printf ("Calculated value = %f\n", sum);
    return 0;
}
