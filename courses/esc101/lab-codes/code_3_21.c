#include <stdio.h>

#define PI 3.1416

int main() {
	float r, h, V;
	scanf("%f %f", &r, &h);
	V = (PI / 3) * r * r * h;
	printf("%.3f\n", V);
	return 0;
}
