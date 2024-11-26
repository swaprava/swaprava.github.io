#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple calculator

int main(int argc, char const *argv[])
{
    int numOfElements = (argc + 1) / 2;
    int count = 0;
    float *value;
    value = (float *) malloc (numOfElements * sizeof(float));

    for (int i=1; i < argc ; i++){
        if (!strcmp(argv[i], "/")){
            value[count-1] = value[count-1] / atof(argv[i + 1]);
            i++;
        }
        else if (!strcmp(argv[i], "X") || !strcmp(argv[i], "x")) {
            value[count-1] = value[count-1] * atof(argv[i + 1]);
            i++;
        }
            
        else if (!strcmp(argv[i], "-")) {
            value[count] = -atof(argv[i + 1]);
            count++; i++;
        }

        else if (!strcmp(argv[i], "+"))
            continue;

        else {
            value[count] = atof(argv[i]);
            count++;
        }
        
    }


    float sum = 0.0;
    for (int i = 0; i < count; i++) {
        printf ("value[%d] = %f\n", i, value[i]);
        sum += value[i];
    }

    printf ("Calculated value = %f\n", sum);
    return 0;
}