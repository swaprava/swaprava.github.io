#include <stdio.h>
#include <stdlib.h>

void combination(int* arr, int n, int r, int i, int last){
  int j;
  if(i == r-1){
    for(j = 0; j < r; j++){
      printf("%d ",arr[j]);
    }
    printf("\n");
    return;
  }
  for(j = last + 1; j <= n; j++){
    arr[i+1]=j;
    combination(arr,n,r,i+1,j);
  }
}
int main (void) {
  int n;
  int r;
  scanf("%d %d", &n, &r);
  int* arr = (int*)malloc(r*sizeof(int));
  combination(arr, n, r, -1, 0);
  return 0;
}
