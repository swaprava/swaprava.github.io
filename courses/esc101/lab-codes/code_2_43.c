#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void) {
  int x1, x2, x3, y1, y2, y3;
  scanf("%d %d", &x1, &y1);
  scanf("%d %d", &x2, &y2);
  scanf("%d %d", &x3, &y3);
  
  int BAx = x1-x2;
  int BAy = y1-y2;
  int BCx = x3-x2;
  int BCy = y3-y2;
  int area = abs(BAx*BCy - BAy*BCx);
  printf("%d", area);

  return 0;
}
