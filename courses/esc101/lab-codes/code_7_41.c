#include<stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for(int i=0; i<n; ++i) {
        scanf("%d", &arr[i]);
    }

    float sum =0;
    int i;
    for(i=0; i<n-1; ++i) {
        sum += arr[i];
        printf("%.3f ", sum/(i+1));
    }
    sum += arr[i];
    printf("%.3f\n", sum/(i+1));

    return 0;
}
