#include <stdio.h>

int max (int num1, int num2){
    int maxNum = 0;
    if (num1 > num2){
        maxNum = num1;
        num1++ ;
    }
    else{
        maxNum = num2;
        num2++ ;
    }
    
    printf("inside the function, num1 = %d, num2 = %d\n", num1, num2);
    // these num1 and num2 are clones of the originals
    return maxNum;
}

int main(void)
{
    int num1, num2, maxNum;

    // take input from the user
    printf("Enter first integer: ");
    scanf("%d", &num1);

    printf("Enter second integer: ");
    scanf("%d", &num2);

    printf("Before calling the function, num1 = %d, num2 = %d\n", num1, num2);
    // single line replacement of the entire max finding method
    maxNum = max(num1, num2);
    printf("After calling the function, num1 = %d, num2 = %d\n", num1, num2);

    printf("Maximum of %d and %d is %d\n", num1, num2, maxNum);
    
    return 0;
}