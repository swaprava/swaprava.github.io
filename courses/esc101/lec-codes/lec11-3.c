#include <stdio.h>

int main(void)
{
    int n, count = 0, i, temp;

    printf("Enter how many numbers: ");
    scanf("%d", &n);

    for (i=1 ; i <= n ; i++){
        printf("Enter number %d: ", i);
        scanf("%d", &temp);

        if ((temp%3 == 0) || (temp%5 == 0))
            count += 1;
    }

    printf("Final count = %d\n", count);
    return 0;
}
