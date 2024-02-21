#include<stdio.h>

#define MaxFib 100

int fib[MaxFib];

int f(int n){

    if(n>=0 && n<=2) return n;
    if (fib[n]) return fib[n];
    int val = f(n-1) + f(n-2);
    fib[n] = val;
    return val;
}

int main()
{
    int n;
    scanf("%d", &n);
    int i;
    for( i=0; i<MaxFib ; ++i) fib[i]=0;
    printf("%d\n",f(n));
    return 0;
}
