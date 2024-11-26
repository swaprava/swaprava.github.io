#include <stdio.h>

// The defined structure to be used to store a point
struct point {
	int x;
	int y;
};

// The defined structure to be used to store a line
struct line {
	int m;
	int c;
};

int main() {
	struct line ll;
	scanf("%d %d", &ll.m, &ll.c);

	int n;
	scanf("%d", &n);

	int sum = 0;

	while (n--) {
		struct point pt;
		scanf("%d %d", &pt.x, &pt.y);

		if (pt.y > ll.m * pt.x + ll.c) {
			sum += pt.x * pt.y;
		}
		else if (pt.y < ll.m * pt.x + ll.c) {
			sum -= pt.x * pt.y;
		}
	}

	printf("%d\n", sum);

	return 0;
}

