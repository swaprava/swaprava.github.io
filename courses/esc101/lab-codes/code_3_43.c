#include <stdio.h>

int main() {
	int n, m, childLeft;
	scanf("%d%d", &n, &m);
	childLeft = n - (m%n);
	printf("%d", childLeft);
	return 0;
}
