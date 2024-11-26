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

    printf ("\nIn reverse order\n");
    for (int i = 0; i < length ; i++)
        printf ("arr[%d] = %d ", length - i - 1, arr[length - i - 1]);

    printf ("\n");

    // printf ("Accessing something dangerous, arr[1000] = %d", arr[1000]);

    return 0;
}
