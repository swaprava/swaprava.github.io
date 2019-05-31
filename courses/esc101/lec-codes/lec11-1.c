#include <stdio.h>

int main () {

    int tableOftheNumber = 2, multiplier;

    printf("Enter the number: ");
    scanf("%d",&tableOftheNumber);

    printf("Multiplication table of %d is:\n", tableOftheNumber);
    
    for(multiplier = 1; multiplier <= 10; multiplier++){
        
        printf("%d x %d = %d\n", tableOftheNumber, multiplier, tableOftheNumber * multiplier);

    }

    return 0;
}