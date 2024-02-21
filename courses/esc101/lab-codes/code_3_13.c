#include <stdio.h>

int main() {
  // This program takes input 2 integers which correspond to cost price of 
  // smartphone and percentage of discount applicable to it. Program should 
  // print the price of the smartphone after applying the discount. Output
  // should be a single float rounded upto 2 decimal places.

  // Following is the buggy code. You have to debug it to print the desired
  // output.

  int costPrice, discount;
  scanf("%d", &costPrice);
  scanf("%d", &discount);
  float sellPrice = costPrice - ((float)discount / 100) * costPrice;
  printf("Selling Price after %d%% discount is %.2f\n", discount, sellPrice);
  return 0;
}
