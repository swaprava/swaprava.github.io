#include <stdio.h>

int main(void) {
    
    char c;
    int n;
    
    scanf("%c %d",&c,&n);
    
    char ans = 'A' + ((c - 'a' + n)%26 + 26)%26;
    printf("%c %d", ans, ans - 'A');
    
    return 0;
}
