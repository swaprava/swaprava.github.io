#include <stdio.h>

// The defined structure to be used for each person
struct person {
	char name[100];
	char birthday[100];
};

int main() {
	int n;
	scanf("%d", &n);

	struct person persons[n];

	for (int i = 0; i < n; i++) {
		scanf("%s %s", persons[i].name, persons[i].birthday);
	}

	int x;
	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		printf("%s %s\n", persons[x - 1].birthday, persons[x - 1].name);
	}

	return 0;
}
