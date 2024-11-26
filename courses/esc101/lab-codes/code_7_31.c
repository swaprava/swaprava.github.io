#include<stdio.h>

#define MAX 100

int main() {
    int occ[MAX+1];
    for(int i=1; i<=MAX; ++i) {
        occ[i] = 0;
    }

    int n;
    scanf("%d", &n);

    int tmp;
    for(int i=0; i<n; ++i) {
        scanf("%d", &tmp);
        occ[tmp] = 1;
    }

    int i;
    for(i=1; i<=MAX; ++i) {
        if(!occ[i])
            break;
    }

    printf("%d\n", i);
    return 0;
}
