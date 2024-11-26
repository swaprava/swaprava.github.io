#include <stdio.h>

#define rootTwo 1.414

int main() {
  // This program calculates the volume of tetrahedron and outputs a single
  // float value rounded to 3 decimal places. It takes as input a single
  // integer which is the edge length of tetrahedron.

  // Following is the buggy code. You have to debug it to print the desired
  // output.

  int a;
  scanf("%d", &a);
  float V = ((a * a * a) / 6.0) / rootTwo;
  printf("Volume of a tetrahedron is: %.3f.", V);
  return 0;
}
