#include <stdio.h>

int main(void)
{
    int number, sum = 0;

    printf("Enter an integer (-1 to end): ");
    scanf("%d", &number);

    while(number != -1){
        
        sum = sum + number;
        printf("Enter an integer (-1 to end): ");
        scanf("%d", &number);

    }

    printf("Sum = %d\n", sum);
    
    return 0;
}
