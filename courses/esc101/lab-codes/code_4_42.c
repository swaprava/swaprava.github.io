#include <stdio.h>
#include <math.h>

int main() {
	float a, b, c, d, e, f, x1, x2;
	scanf("%f %f %f %f %f %f %f", &a, &b, &d, &e, &f, &x1, &x2);
	float res = 0;
	if (b != -1){
		res += (a*(pow(x2, b+1) - pow(x1, b+1)))/(b+1);
	}
	else {
		res += a*(log(x2) - log(x1));
	}
	res += d*(sin(x2) - sin(x1)) + e*(exp(x2)-exp(x1)) - f*(cos(x2)-cos(x1));
    printf("%.1f", res);
    return 0;
}
