#include <stdio.h>
#include <math.h>

int main() {
    long int n;
    scanf("%ld", &n);
    int len = log10(n) + 1;
    for (int i = 0; i < len; i++) {
        if (((n / (long)pow(10, i)) % 10) != ((n /(long)pow(10, len - i - 1)) % 10)) {
            printf("NO");
            return 0;
        }
    }
    printf("YES");
    return 0;
}
