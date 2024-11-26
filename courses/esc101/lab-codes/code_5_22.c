#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int count = 0;
    if (n <= 0) {
        printf("-1");
        return 0;
    }
    while (n != 1) {
        count += 1;
        n = n % 2 ? 3 * n + 1 : n / 2;
    }
    printf("%d", count);
    return 0;
}
