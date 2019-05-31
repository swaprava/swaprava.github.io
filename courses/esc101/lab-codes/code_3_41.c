#include <stdio.h>
#include <math.h>

int main() {
	float a, b, c, A;
	scanf("%f %f %f", &a, &b, &c);
	float s = (a + b + c) / 2;
	A = sqrt(s * (s-a) * (s-b) * (s-c));
	printf("%.3f %.3f\n", A, s);
	return 0;
}
