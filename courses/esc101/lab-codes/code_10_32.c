#include <stdio.h>
#include <stdlib.h>


void rotate(int **, int);

void print2d(int **, int);

int main(){
  int n, **mat, i, j;

  scanf("%d", &n);
  mat = (int **) malloc(n*sizeof(int *));

  for(i=0;i<n;i++)
    mat[i] = (int *) malloc(n*sizeof(int));

  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      scanf("%d", &mat[i][j]);

  rotate(mat, n);
  print2d(mat, n);

  for(i=0;i<n;i++)
    free(mat[i]);
  free(mat);

  return 0;
}

void rotate(int **mat, int n){
  int offset, width, j, a, b, c , d;

  for(offset=0;offset<n/2;offset++){
    width = n - 2*offset - 1;
    for(j=0; j<width; j++){
      a = mat[offset][offset+j];
      b = mat[offset+j][offset+width];
      c = mat[offset+width][offset+width-j];
      d = mat[offset+width-j][offset];

      mat[offset][offset+j] = d;
      mat[offset+j][offset+width] = a;
      mat[offset+width][offset+width-j] = b;
      mat[offset+width-j][offset] = c;
    }
  }
  return;
}

void print2d(int **mat, int n){
  int i, j;

  for(i=0;i<n;i++){
    for(j=0;j<n;j++)
      printf("%d ", mat[i][j]);

    printf("\n");
  }
  return;
}
