#include <stdio.h>
#include <math.h>

int main(){
	int i, n, sum, temp, num_digits;
	scanf("%d", &n);
	for (i=n; ;i++){
		temp = i;
		num_digits = 0;
		sum = 0;
		while(temp!=0){
			temp = temp/10;
			num_digits++;
		}
		temp = i;
		while(temp!=0){
			sum += pow(temp%10, num_digits);
			temp = temp/10;
		}
		if (sum == i){
			printf("%d", i);
			break;
		}
	}
	return 0;

}
