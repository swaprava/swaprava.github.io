#include <stdio.h>

int main() {
    int d, m;
    scanf("%d-%d", &d, &m);
    
    switch(m) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12: printf("%d", 31 - d); break;
        case 2: printf("%d", 28 - d); break;
        case 4:
        case 6:
        case 9:
        case 11: printf("%d", 30-d); break;
        default: printf("Invalid Month"); break;
    }
    return 0;
}
