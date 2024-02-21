#include <stdio.h>

#define PI 3.1416

int main() {
    float r, R, h, V;
    scanf("%f%f%f", &r, &R, &h);
    V = (PI * h / 3) * (R*R + R*r + r*r);
    printf("%.4f\n", V);
    return 0;
}
