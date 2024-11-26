#include <stdio.h>

int main(void)
{
    int outerIterator, innerIterator, n;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    // Outer for loop
    for (outerIterator = 1 ; outerIterator <= n ; outerIterator++){ // line indices
        // Inner for loop
        for (innerIterator = 1 ; innerIterator <= outerIterator ; innerIterator++){ // width indices in every line
            printf(" %2d", innerIterator);
        }
        printf("\n");
    }
    return 0;
}
