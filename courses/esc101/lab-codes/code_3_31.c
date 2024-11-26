#include <stdio.h>
#include <math.h>

#define PI 3.1416

int main() {
	float r, h, V;
	scanf("%f %f", &h, &V);
	float r_square = V / (PI * h);
	r = sqrt(r_square);
	printf("%.2f\n", r);
	return 0;
}
