#include <stdio.h>
#define ROWS 3
#define COLS 3

int main()
{
    int matrix[ROWS][COLS];

    // read the matrix
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            printf ("Enter integer element (%d,%d): ", i, j);
            scanf ("%d", &matrix[i][j]);
        }
    }

    // int matrix[][COLS] = {{1}, {2,3}, {4,5,6}};

    // print the matrix
    printf ("\nYour entered matrix is:\n");
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            printf ("%d", matrix[i][j]);
            if (j != COLS-1) printf ("\t");
        }
        printf ("\n");
    }

    return 0;
}
