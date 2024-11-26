#include <stdio.h>
#include <stdlib.h>

int sumSubarray(int arr[], int i, int j){
 int sum = 0;
 int p;
 for(p = i; p <= j; p++){
   sum += arr[p];
 }
 return sum;
}

int main(){
  int A[1000];
  int n;
  scanf("%d", &n);
  int i;
  for (i = 0; i < n; i++){
    scanf("%d", A + i);
  }
  int m,l,u;
  scanf("%d", &m);
  for(i = 1; i <= m; i++){
    scanf("%d %d", &l, &u);
    printf("%d\n", sumSubarray(A,l,u));
  }
  return 0;
}
