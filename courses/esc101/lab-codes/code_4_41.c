#include <stdio.h>

int main() {
	int x1, x2, x3, x4, y1, y2, y3, y4;
	scanf("%d %d %d %d %d %d %d %d", &x1, &x2, &x3, &x4, &y1, &y2, &y3, &y4);
	if (x1 == x2 && y2 == y3 && x3 == x4 && y4 == y1){
		if (y1 == y2 || x1 == x4)
			printf("NO");
		else
			printf("YES");
	}
	else{
		printf("NO");
	}
    return 0;
}
