#include <stdio.h>

int main(void) {
	
	int a, b, c, d, total;
	char name[11];
	char section[11];
	
	scanf("%d+%d+%d+%d", &a, &b, &c, &d);
	scanf(",%[^,]", section);
	scanf(",%s", name);
	
	total = a + b + c + d;
	printf("%s of %s scored %d\n", name, section, total);

	return 0;
}
