#include <stdio.h>

int main(){

	int n;
	scanf("%d\n", &n);

	int A[n][n];

    int i, j;
    // Scan the matrix
    for(i=0;i<n;i++){
    	for(j=0;j<n;j++){
    		scanf("%d", &A[i][j]);
    	}
    }


    int tmp;

    // Transpose the matrix
    for(i=0;i<n;i++){
        for(j=i;j<n;j++){
            tmp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = tmp;
        }
    }

    // Swap Columns
    for(j=0;j<n/2;j++){
        for(i=0;i<n;i++){
            tmp = A[i][j];
            A[i][j] = A[i][n-j-1];
            A[i][n-j-1] = tmp;
        }
    }
  
    // Print the rotated matrix
    for(i=0;i<n;i++){
    	for(j=0;j<n;j++){
    		printf("%d ", A[i][j]);
    	}
    	printf("\n");
    }

    return 0;
}
