#include <stdio.h>

int main() {
	int a, b, c, d;
	float wage1, wage2, total;
	scanf("%d %d", &a, &b);
	scanf("%d %d", &c, &d);
	
	
	wage1 = a + 0.01*b;
	wage2 = c + 0.01*d;
	total = wage1 + wage2;
	
	printf("%7.2f\n", wage1);
	printf("%7.2f\n", wage2);
	printf("%7.2f\n", total);
	
	return 0;
}
