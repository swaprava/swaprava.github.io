#include <stdio.h>
int main(){
	
	int a, b;

	scanf("%d %d", &a, &b);
	
	printf("%7d|%d\n", a, b);
	printf("%7d|%7d\n", a+b, a-b);
	printf("%7d|%7.3f", a*b, (float)a/b);

	return 0;
}
