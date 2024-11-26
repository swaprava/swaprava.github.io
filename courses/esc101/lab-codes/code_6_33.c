#include<stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    
    if (n == 1) {
        printf("1");
        return 0;
    }
    
    int c, first = 1;
    for (int x = 2; x <= n; x++) {
        c = 0;
        while(n % x == 0) {
            c++;
            n /= x;
        }
        
        if (c) {
            if (!first) {
                printf(" . ");
            }
            else {
                first = 0;
            }
            
            printf("%d^%d", x, c);
        }
    }
    
    return 0;
}
