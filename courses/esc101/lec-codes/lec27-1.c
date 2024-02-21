#include <stdio.h>

struct point
{
    float x;
    float y; // can also be declared in a single statement for all variables of same type
};

int main() {
     struct point pt;
     printf ("Enter the x and y coordinates respectively: ");
     scanf("%f %f", &pt.x, &pt.y);
     printf ("The point is (%f, %f)\n", pt.x, pt.y);

     return 0;
}