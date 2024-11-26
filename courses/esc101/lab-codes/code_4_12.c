#include <stdio.h>
#include <math.h>

#define pi 3.1416 

int main() {
	float ba, h2, l, s, a, c, v, S, r_m, r;
	scanf("%f %f %f %f %f",&h2, &l, &S, &a, &c);
	s = (a+a+c)/2;
	r_m = pow(((s-a) * (s-a) * (s-c))/s, 0.5);
	ba = pow((s * (s-a) * (s-a) * (s-c)), 0.5);
	r = S/(2*pi*l);
	if (r<=r_m){
	    v = h2*c*l + ba*l - (pi*r*r*l);
	    printf("%.3f", v);
	}
	else
	    printf("NOT POSSIBLE");
    return 0;
}
