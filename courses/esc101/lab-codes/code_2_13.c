#include <stdio.h>

int main(void) {
  int v1i, v1j, v1k, v2i, v2j, v2k;
  
  scanf("%d %d %d", &v1i, &v1j, &v1k);
  scanf("%d %d %d", &v2i, &v2j, &v2k);
  
  int vdot = v1i * v2i + v1j * v2j + v1k * v2k;
  printf("%d", vdot);

  return 0;
}
