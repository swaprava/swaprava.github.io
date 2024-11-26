#include<stdio.h>

int is_coprime(int a, int b) {
    for (int i = 2; i <= ((a > b) ? b : a); i++) {
        if (a % i == 0 && b % i == 0)
            return 0;
    }
    return 1;
}

int main()
{
    int n, a, b;
    scanf("%d", &n);
    
    long int sum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &a, &b);
        
        if (is_coprime(a, b))
            sum += a * b;
    }
    
    printf("%ld", sum);
    
    return 0;
}
