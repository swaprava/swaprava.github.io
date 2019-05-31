#include <stdio.h>
#include <stdlib.h>

int countMinima(int arr[], int i, int j){
 int count = 0;
 count += (arr[i]<=arr[i+1]);
 count += (arr[j]<=arr[j-1]);
 int p;
 for (p = i+1; p < j; p++){
   count += (arr[p]<=arr[p-1])&&(arr[p]<=arr[p+1]);
 }
 return count;
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
    printf("%d\n", countMinima(A,l,u));
  }
  return 0;
}
