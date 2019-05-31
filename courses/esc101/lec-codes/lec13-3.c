#include <stdio.h>

int max (int a, int b){
    if (a > b) return a;
    else return b;
}

int main(void)
{
    int num1, num2, maxNum, n, i;

    // take input from the user
    printf("How many numbers: ");
    scanf("%d", &n);

    printf("Enter integer 1: ");
    scanf("%d", &num1);
    maxNum = num1;

    for (i = 1 ; i < n ; i++ ) {

        printf("Enter integer %d: ", i+1);
        scanf("%d", &num2);
        maxNum = max(maxNum, num2);

    }

    printf("Maximum of these %d numbers is %d\n", n, maxNum);
    
    return 0;
}