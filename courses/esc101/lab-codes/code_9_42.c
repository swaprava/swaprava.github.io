#include <stdio.h>
#include <string.h>

int max(int a, int b) {
	return a > b ? a : b;
}

int LCS(char* str1, char* str2, int i, int j) {
	if (i == -1 || j == -1) {
		return 0;
	}
	if (str1[i] == str2[j]) {
		return 1 + LCS(str1, str2, i-1, j-1);
	}
	return max(LCS(str1, str2, i, j-1), LCS(str1, str2, i-1, j));
}

int main() {
	char str1[100], str2[100];
	scanf("%s", str1);
	scanf("%s", str2);
	printf("%d\n", LCS(str1, str2, strlen(str1)-1, strlen(str2)-1));
	return 0;
}
