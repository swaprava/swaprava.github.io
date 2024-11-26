#include <stdio.h>

int main(void) {
  int b = 8; // base value
  int n;
  
  scanf("%d",&n);
  
  // Your code goes here.
  int n1 = n;
  int d0, d1, d2 , d3;
  d0 = n%b;
  n = n/b;
  d1 = n%b;
  n = n/b;
  d2 = n%b;
  n = n/b;
  d3 = n%b;
  printf("%d in base 10 is equal to %d%d%d%d in base %d.",n1,d3,d2,d1,d0,b);
  return 0;
}
