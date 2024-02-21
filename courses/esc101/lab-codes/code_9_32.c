#include <stdio.h>
#include <string.h>

int max = 0;

int LIS(char* str, int n) {
	if (n <= 1) {
		return n;
	}

	int maxHere = 1, i;
	for (i = 0; i < n-1; i++) {
		int maxTill = LIS(str, i+1);
		if (str[i] < str[n-1] && maxTill + 1 > maxHere) {
			maxHere = maxTill + 1;
		}
	}

	if (max < maxHere) {
		max = maxHere;
	}

	return maxHere;
}

int main() {
	char str[100];
	scanf("%s", str);
	LIS(str, strlen(str));
	printf("%d\n", max);
	return 0;
}
