#include <stdio.h>
#include <stdlib.h>


void permutation(int* arr, int n, int r, int i){
  int j,k;
  int flag;
  if(i == r-1){
    for(j = 0; j < r; j++){
      printf("%d ",arr[j]);
    }
    printf("\n");
    return;
  }
  for(j = 1; j <= n; j++){
    flag = 0;
    for(k = 0; k <= i; k++){
      if(arr[k] == j){
        flag = 1;
      }
    }
    if(flag == 0){
      arr[i+1] = j;
      permutation(arr, n, r, i+1);
    }
  }
}

int main (void) {
  int n;
  int r;
  scanf("%d %d", &n, &r);
  int* arr = (int*)malloc(r*sizeof(int));
  permutation(arr, n, r, -1);
  return 0;
}
