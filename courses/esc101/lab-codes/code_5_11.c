#include <stdio.h>

int main() {
    int n;
    int i;
    scanf("%d %d", &n, &i);
    
    switch (n) {
        case 1:
        case 4:
        case 5: i = i * 2; break;
        case 2:
        case 7:
        case 9: i = i * 3; break;
        default: i = i * 4; break;
    }
    
    switch (n) {
        case 7:
        case 8: i = i + 3;
        case 1:
        case 2:
        case 4: i = i + 5;
        case 9:
        case 3:
        case 6:
        case 5: i = i + 7;
    }
    
    printf("%d", i);
    
    return 0;
}
