#include <stdio.h>

int main()
{
    int length = 5;
    int arr[length];

    printf ("Enter integers as requested below\n");

    for (int i = 0; i < length ; i++) {
        printf ("Enter number %d: ", i);
        scanf ("%d", &arr[i]);
    }

    printf ("You have entered\n");
    for (int i = 0; i < length ; i++)
        printf ("arr[%d] = %d ", i, arr[i]);

    // computing the differential order
    for (int i = length - 1; i > 0 ; i--)
        arr[i] = arr[i] - arr[i-1];

    printf ("\nThe differential order\n");
    for (int i = 0; i < length ; i++)
        printf ("arr[%d] = %d ", i, arr[i]);

    printf ("\n");

    return 0;
}