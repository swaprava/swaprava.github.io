#include <stdio.h>
#include <math.h>

int main(){
	int i, j, k;
	double x, x0, res = 0;
	scanf("%d", &k);
	scanf("%lf", &x0);
	scanf("%lf", &x);
	float num, den;
	for (i=0; i<=k; i++){
		if(i%2 == 0)
			num = sin(x0)*pow(x-x0, i);
		else	
			num = cos(x0)*pow(x-x0, i);
		den = 1;
		for (j=1; j<=i; j++){
			den = den*j;
		}
		res += pow(-1, i/2)*num/den; 
	}
	printf("%.2lf\n", res);
	return 0;
}
