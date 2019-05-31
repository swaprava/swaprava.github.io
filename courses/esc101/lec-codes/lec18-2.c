#include <stdio.h>

void swapnum (int *, int *); // function declaration

int main() 
{
    int num1 = 35, num2 = 45;

    printf("Before swapping: num1 = %d and num2 = %d\n", num1, num2);
    swapnum (&num1, &num2); /*calling swap function*/ 
    printf("After swapping: num1 = %d and num2 = %d\n", num1, num2);

    return 0;
} 

void swapnum ( int *var1, int *var2 ) {
    int tempnum ; 
    tempnum = *var1 ; 
    *var1 = *var2 ;
    *var2 = tempnum ;
}
