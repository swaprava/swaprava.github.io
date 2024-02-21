#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int t1 = 1;
    int t2 = 1;
    while (n > t2) {
        t2 = t2 + t1;
        t1 = t2 - t1;
    }
    printf("%d", t1);
    return 0;
}
