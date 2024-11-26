#include <stdio.h>
#include <stdlib.h>

int nQueens(int** board, int col, int size, int d);
int safe(int inp, int size);
int min(int a, int b);
int max(int a, int b);

int main() {
  int n, d;
  scanf("%d %d", &n, &d);
  int **board = (int**)calloc(n, sizeof(int*));
  for (int i = 0; i < n; i++) {
    board[i] = (int*)calloc(n, sizeof(int));
  }
  int soln = nQueens(board, 0, n, d);
  printf("%d", soln);
  return 0;
}

int safe(int inp, int size) {
  if (inp < 0) {
    return 0;
  }
  if (inp >= size) {
    return 0;
  }
  return 1;
}

int min(int a, int b) {
  return a > b ? b : a;
}

int max(int a, int b) {
  return a > b ? a : b;
}

int nQueens(int **board, int col, int size, int d) {
  if (col == size) {
    /*
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[j][i]) {
                printf("%d", j);
            }
        }
    }
    printf("\n");
    */
    return 1;
  }
 
  int num = 0;
  int j;
  for (int i = 0; i < size; i++) {
    // Check if [col][i] is legal. For this, check rows, cols, diags
    int legal = 1;
    for (j = 0; j < size; j++) { // row and col
      legal *= (1 - board[i][j]) * (1 - board[j][col]);
    }

    j = 1;
    while (safe(i - j, size) && safe(col - j, size) && j <= d) {
      legal *= (1 - board[i - j][col - j]);
      j++;
    }

    j = 1;
    while (safe(i + j, size) && safe(col - j, size) && j <= d) {
      legal *= (1 - board[i + j][col - j]);
      j++;
    }

    j = 1;
    while (safe(i - j, size) && safe(col + j, size) && j <= d) {
      legal *= (1 - board[i - j][col + j]);
      j++;
    }

    j = 1;
    while (safe(i + j, size) && safe(col + j, size) && j <= d) {
      legal *= (1 - board[i + j][col + j]);
      j++;
    }

    if (legal) {
      // place a queen, make call, remove queen
      board[i][col] = 1;
      num += nQueens(board, col + 1, size, d);
      board[i][col] = 0;
    }
  }
  return num;
}
