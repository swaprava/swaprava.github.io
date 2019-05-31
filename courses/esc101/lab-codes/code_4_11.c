#include <stdio.h>

int main() {
    char c;
	long int a, b, res;
	scanf("%c %ld %ld", &c, &a, &b);
	if (c == '+'){
		res = a+b;
	}
	else{
		res = a-b;
	}
	printf("%ld", res);
    return 0;
}
