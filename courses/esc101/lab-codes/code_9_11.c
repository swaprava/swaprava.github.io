#include <stdio.h>
#include <string.h>

int main() {
	char str[1000];
	scanf("%s", str);
	int i, j, k, n = strlen(str), max = 0;
	for (i = 0; i < n; i++) {
		for (j = i; j < n; j++) {
			int flag = 1, len = j-i+1;
			for (k = i; k < j; k++) {
				if (str[k] >= str[k+1]) {
					flag = 0;
					break;
				}
			}
			if (flag) {
				max = (max < len) ? len : max;
			}
		}
	}
	printf("%d", max);
	return 0;
}
