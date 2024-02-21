#include <stdio.h>

int main(void) {
  
    char c;

    scanf("%c",&c);

    // Your code goes here.
    char ans = 'A' + (25-(c - 'a'))%26;
    printf("%c %d", ans, ans-'A');
    
    return 0;
}
