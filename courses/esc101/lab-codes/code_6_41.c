#include <stdio.h>
#include <math.h>

int main(){
    long N, newN = 0, temp, blocks, bPow;
    int k, len, i;
    scanf("%ld%d", &N, &k);
    len = log10(N) + 1; // Number of digits in the number
    blocks = len / k;
    if(len % k) blocks++; // One more block needed
    bPow = (long)pow(10,k);
    for(i = 0; i < blocks; i++){
        temp = N % bPow;
        newN = newN + ((temp + temp%10) % bPow)*((long)pow(bPow,i));
        N = N / bPow;
    }
    printf("%ld", newN);
    return 0;
}
