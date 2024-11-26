#include<stdio.h>

int gcd(int a, int b) {
    int g = 1;
    for (int i = 2; i <= ((a < b) ? a : b); i++)
        g = ((a % i == 0 && b % i == 0) ? i : g);
        
    return g;
}

long int lcm(int a, int b) {
    return ((long int) a * b) / (long int) gcd(a, b);
}

int main()
{
    int n, x;
    scanf("%d", &n);
    
    long int l = 1;
    while (n--) {
        scanf("%d", &x);
        
        l = lcm(l, x);
    }
    
    printf("%ld", l);
    
    return 0;
}
