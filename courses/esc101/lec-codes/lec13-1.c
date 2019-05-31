#include <stdio.h>

int max (int a, int b); // option 1

// option 2 is to define the whole function here itself

int main(void)
{
    int num1, num2, maxNum;

    // take input from the user
    printf("Enter first integer: ");
    scanf("%d", &num1);

    printf("Enter second integer: ");
    scanf("%d", &num2);

    // single line replacement of the entire max finding method
    maxNum = max(num1, num2);

    printf("Maximum of %d and %d is %d\n", num1, num2, maxNum);
    
    return 0;
}

// option 1
int max (int a, int b){
    if (a > b) return a;
    else return b;
}