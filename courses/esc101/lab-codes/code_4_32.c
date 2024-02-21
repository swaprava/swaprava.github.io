#include <stdio.h>

#define PI 3.14159
int main(){
    float r1,r2,r3,h;
    scanf("%f\n",&r1);
    scanf("%f\n",&r2);
    scanf("%f %f",&r3,&h);
    float vol = (4.0/3)*PI*r1*r1*r1;
    vol = vol + (4.0/3)*PI*r2*r2*r2;
    vol = vol + (1.0/3)*PI*r3*r3*h;
    printf("%.1f",vol);
    return 0;
}
