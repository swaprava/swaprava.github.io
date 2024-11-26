#include <stdio.h>

int main(void) {
  char c;
  int a, b;

  scanf("%c %d %d", &c, &a, &b);

  // Your code goes here.
  int p = (c - 'a')%26;
  char ans = 'A' + ((a*p+b)%26 + 26)%26;
  printf("%c %d", ans, ans - 'A');
  return 0;
}
