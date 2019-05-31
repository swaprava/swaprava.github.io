#include<stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for(int i=0; i<n; ++i) {
        scanf("%d", &arr[i]);
    }

    for(int i=0; i<n-1; ++i) {
        int minindex = i;
        for(int j=i; j<n; ++j) {
            minindex = (arr[j]<arr[minindex] ? j : minindex);
        }
        int tmp = arr[i];
        arr[i] = arr[minindex];
        arr[minindex] = tmp;

        for(int k=0; k<n-1; ++k) {
            printf("%d ", arr[k]);
        }
        printf("%d\n", arr[n-1]);
    }

    return 0;
}
