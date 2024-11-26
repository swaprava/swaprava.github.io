#include <stdio.h>

void print_arr(int a[], int len){
    int i;
    for(i=0; i<len; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void partition(int a[], int pos, int sum, int n){
    if(sum==n){
        print_arr(a, pos);
        return;
    }
    
    int i, rem = n-sum;
    if(pos==0 || rem<=a[pos-1])
    for(i=rem; i>=1; i--){
        a[pos]=i;
        partition(a, pos+1, sum+i, n);
    }
    
    else
    for(i=a[pos-1]; i>=1; i--){
        a[pos]=i;
        partition(a, pos+1, sum+i, n);
    }
}

int main() {
    int n, a[30];
    scanf("%d", &n);
    partition(a,0,0,n);
    
    return 0;
}
