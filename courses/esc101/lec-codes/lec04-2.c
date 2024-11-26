#include <stdio.h>

int main () {
    int x = 2345, y=123;
    printf("%d\n",x); //Usual

    printf("%.6d\n%6d\n",x,x); //Display using 6 columns, with zero padded

    printf("%6d\n",y); //Note: Right aligned

    printf("%2d\n",x); //Less columns, same as %d

}