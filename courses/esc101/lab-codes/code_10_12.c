#include <stdio.h>
#include <stdlib.h>

/*
   Recursive definition of determinate using expansion by minors.
*/

int Determinant(int **a,int n)
{
   int i,j,j1,j2;
   int det = 0;
   int **m = NULL;

   if (n < 1) { /* Error */

   } else if (n == 1) { /* Shouldn't get used */
      det = *(*(a + 0) + 0);
   } else if (n == 2) {
      det = (**a) * *(*(a + 1) + 1) - **(a + 1) * *(*a + 1);
   } else {
      det = 0;
      for (j1=0;j1<n;j1++) {
         m = malloc((n-1)*sizeof(int *));
         for (i=0;i<n-1;i++)
            m[i] = malloc((n-1)*sizeof(int));
         for (i=1;i<n;i++) {
            j2 = 0;
            for (j=0;j<n;j++) {
               if (j == j1)
                  continue;
               m[i-1][j2] = *(*(a + i) + j);
               j2++;
            }
         }
         det += pow(-1,1+j1+1) * *(*a + j1) * Determinant(m,n-1);
         for (i=0;i<n-1;i++)
            free(m[i]);
         free(m);
      }
   }
   return(det);
}


int main(){

	int n ,i, j; 
	scanf("%d" , &n);

	int **m = malloc((n)*sizeof(int *));
	for (i=0 ; i<n ; i++)
            m[i] = malloc((n)*sizeof(int));

    // Scanning the matrix
    for (i=0;i<n;i++)
    	for (j = 0 ; j < n ; j++)
    		scanf("%d" , *(m + i ) +  j);

    printf("%d" , Determinant(m , n ));
    return 0;
}
