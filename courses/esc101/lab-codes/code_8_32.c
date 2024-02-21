#include<stdlib.h>
#include<stdio.h>

int isSubsetSum(int arr[], int n, int sum){
  if ((n <= 0) && (sum == 0))
		return 1;
  if (n <= 0  && sum != 0)  return 0;

  return isSubsetSum(arr, n-1, sum - arr[n-1]) + isSubsetSum(arr, n-1, sum);
}

int main(){

  int i, n, k;
  int arr[20];
  scanf("%d %d", &n, &k);
  for(i=0;i<n;i++)
  	scanf("%d", &arr[i]);
  printf("%d\n", isSubsetSum(arr, n, k));
  return 0;
}
