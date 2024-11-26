#include <stdio.h>

int main(void) {
  int a11, a12, a13, a21, a22, a23, a31, a32, a33;
  
  scanf("%d %d %d", &a11, &a12, &a13);
  scanf("%d %d %d", &a21, &a22, &a23);
  scanf("%d %d %d", &a31, &a32, &a33);
  
  int det = a11 * (a22*a33 - a23*a32) - a12 * (a21*a33 - a23*a31) + a13 * (a21*a32 - a22*a31);
  printf("%d", det);

  return 0;
}
