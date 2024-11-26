#include<stdio.h>

int is_prime(int n) {
    if(n<2) return 0;
    
    int i;
    for(i=2; i<n; i++)
        if(n%i == 0)
            return 0;
    
    return 1;
}

int golden_x(int n) {
    int x;
    for(x=2; x<=n/2; x++) {
        if(is_prime(x) && is_prime(n-x)) {
            return x;
        }
    }
    return -1;
}

int main()
{
    int Q, N, n;
    scanf("%d", &Q);
    while(Q--) {
        scanf("%d", &N);
        
        int xmax=0, ans=-1;
        for(n=2; n<=N; n+=2) {
            int x = golden_x(n);
            if(xmax < x) {
                xmax = x;
                ans = n;
            }
        }
        if(ans==-1) printf("No solutions\n");
        else printf("%d = %d + %d\n", ans, xmax, ans-xmax);
    }
    return 0;
}
