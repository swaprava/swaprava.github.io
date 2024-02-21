#include <stdio.h>

int main(void) {
  int v1i, v1j, v1k, v2i, v2j, v2k;

  scanf("%d %d %d", &v1i, &v1j, &v1k);
  scanf("%d %d %d", &v2i, &v2j, &v2k);
  
  int vci = v1j * v2k - v1k * v2j;
  int vcj = v1k * v2i - v1i * v2k;
  int vck = v1i * v2j - v1j * v2i;
  printf("%d %d %d", vci, vcj, vck);

  return 0;
}
