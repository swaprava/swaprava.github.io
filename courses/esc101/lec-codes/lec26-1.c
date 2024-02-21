#include <stdio.h>
#include <stdlib.h>

int main() {
  int a[2][3];
  int **b;
  b = (int**)malloc(2*sizeof(int*));
  b[0] = (int*)malloc(3*sizeof(int));
  b[1] = (int*)malloc(3*sizeof(int));

  printf ("*a + 3 = %p,\t a[1] = %p\n", *a+3, a[1]);
  printf ("*b + 3 = %p,\t b[1] = %p\n", *b+3, b[1]);

  return 0;
}