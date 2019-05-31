#include <stdio.h>
#include <math.h>

int main() {
	float x1, x2, x3, y1, y2, y3, d1, d2, d3;
	scanf("%f %f %f %f %f %f", &x1, &x2, &x3, &y1, &y2, &y3);
	d1 = pow((pow(x1-x2, 2) + pow(y1-y2, 2)), 0.5);
	d2 = pow((pow(x2-x3, 2) + pow(y2-y3, 2)), 0.5);
	d3 = pow((pow(x3-x1, 2) + pow(y3-y1, 2)), 0.5);
// 	printf ("%f %f %f\n", d1, d2, d3);
	if (d1+d2 == d3 || d2+d3 == d1 || d3+d1 == d2){
		printf("not a triangle");
	}
	else{
		if (d1 == d2 || d2==d3 || d3==d1){
			printf("isosceles triangle");
		}
		else{
			printf("scalene triangle");
		}
	}
    return 0;
}
