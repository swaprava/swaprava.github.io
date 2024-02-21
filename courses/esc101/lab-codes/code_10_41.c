#include <stdio.h>
#include <stdlib.h>

int checksum(int **mat, int i, int j, int k){
    int summ = 0;
    for (int ii=0; ii<k; ii++){
        for (int jj=0; jj<k; jj++){
            summ += mat[ii+i][jj+j];
        }
    }
    return summ;
}

int main(){
  int m, n, k, **mat, i, j;

  scanf("%d %d %d", &m, &n, &k);
    // printf("%d %d %d", m, n, k);
  mat = (int **) malloc(m*sizeof(int *));

  for(i=0;i<m;i++)
    mat[i] = (int *) malloc(n*sizeof(int));

  for(i=0;i<m;i++)
    for(j=0;j<n;j++)
      scanf("%d", &mat[i][j]);
      
    int msum, summ;
    msum = checksum(mat,0,0,k);
    // printf("%d\n", msum);
    for (i=0; i<=m-k; i++){
        for (j=0; j<=n-k; j++){
            // printf("%d %d\n", i, j);
            summ = checksum(mat, i, j, k);
            // printf("%d\n", summ);
            if (summ>msum){
                msum = summ;
            }
        }
    }
    printf("%d", msum);

//   for(i=0;i<m;i++)
//     free(mat[i]);
//   free(mat);

  return 0;
}
