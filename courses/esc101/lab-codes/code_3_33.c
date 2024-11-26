#include <stdio.h>

int main() {
	// This program outputs the password of a government website.

	char name[20];
	scanf("%s", name);
	int dd, mm, yyyy;
	scanf("%d/%d/%d", &dd, &mm, &yyyy);
	printf("%s%d", name, yyyy);
	return 0;
}
