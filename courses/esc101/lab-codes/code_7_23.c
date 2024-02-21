#include<stdio.h>
#define NumChars 256
int main()
{
    int n, m, k;
    int ar[1000];
    int temp[1000];
    scanf("%d", &k);
    scanf("%d", &m);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i){
        scanf("%d", &ar[i]);
    }
    int size = n/m;
    int r = (k%size + size)%size;
    for(int i=0; i<n; i+=size){
        for(int j=i, g=0; j<i+size; ++j, ++g) temp[g] = ar[j];
        for(int j=i; j<i+size; ++j){
            ar[i+(j-i+r)%size] = temp[j-i];
        }
    }
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", ar[i]);
    }
    printf("\n");


    return 0;
}
