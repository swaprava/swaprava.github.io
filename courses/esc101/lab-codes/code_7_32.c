#include<stdio.h>

int main() {
    int n,k;
    scanf("%d %d", &n, &k);

    int arr[n];
    for(int i=0; i<n; ++i) {
        scanf("%d", &arr[i]);
    }

    int part1[n];
    int part2[n];
    int count1=0, count2=0;

    for(int i=n-1; i>=0; --i) {
        if(arr[i] <= k) {
            part1[count1++] = arr[i];
        }
        else {
            part2[count2++] = arr[i];
        }
    }

    if(count1 == 0) {
        printf("EMPTY\n");
    }
    else {
        int i;
        for(i=0; i<count1-1; ++i) {
            printf("%d ", part1[i]);
        }
        printf("%d\n", part1[i]);
    }

    if(count2 == 0) {
        printf("EMPTY\n");
    }
    else {
        int i;
        for(i=0; i<count2-1; ++i) {
            printf("%d ", part2[i]);
        }
        printf("%d\n", part2[i]);
    }

    return 0;
}
