#include<stdio.h>

int sum_of_digits(int x) {
	int sum = 0;

	while (x) {
		sum += x % 10;
		x /= 10;
	}

	return sum;
}

int main() {
	int n, m;

	scanf("%d %d", &n, &m);
	m /= 2;

	int i, a, b;

	for (i = 0; i < n; i++) {
		scanf("%d %d", &a, &b);

		if (m && sum_of_digits(a) == sum_of_digits(b)) {
			printf("Allowed\n");
			m--;
		}
		else {
			printf("Not Allowed\n");
		}
	}

	for (; i < n; i++) {
		printf("Not Allowed\n");
	}

	return 0;
}
