#include <stdio.h>

int main(void) {
  char c;

  scanf("%c",&c);

  // Your code goes here.
  int p = (c - 'a')%26;
  char ans = 'A' + (p*p+3)%26;
  printf("%c %d", ans, ans - 'A');
  return 0;
}
