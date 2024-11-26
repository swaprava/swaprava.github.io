#include <stdio.h>
#include <stdlib.h>

void check(int **mat, int i, int j, int k){
    for (int ii=0; ii<k; ii++){
        for (int jj=0; jj<k; jj++){
            if (ii!=jj && mat[ii+i][jj+j] !=0){
                return;
            }
            if (ii==jj && mat[ii+i][jj+j] !=1){
                return;
            }
        }
    }
    printf("%d,%d\n", i, j);
    return;
}

int main(){
  int m, n, k, **mat, i, j;

  scanf("%d %d %d", &m, &n, &k);
  mat = (int **) malloc(m*sizeof(int *));

  for(i=0;i<m;i++)
    mat[i] = (int *) malloc(n*sizeof(int));

  for(i=0;i<m;i++)
    for(j=0;j<n;j++)
      scanf("%d", &mat[i][j]);
      
    for (i=0; i<=m-k; i++){
        for (j=0; j<=n-k; j++){
            // printf("%d %d\n", i, j);
            check(mat, i, j, k);
        }
    }


  for(i=0;i<m;i++)
    free(mat[i]);
  free(mat);

  return 0;
}
