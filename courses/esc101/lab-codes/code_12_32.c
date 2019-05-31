#include <stdio.h>
#include <stdlib.h>

int sudokuSolv(int** board, int* emptySet, int depth, int size, int emptySetSize);

int main() {
  int n;
  scanf("%d", &n);
  int **board = (int**)calloc(n, sizeof(int*));
  for (int i = 0; i < n; i++) {
    board[i] = (int*)calloc(n, sizeof(int));
  }
  int r, c, v;
  int count;
  while (1) {
    scanf("%d %d %d", &r, &c, &v);
    if (r == -1) {
      break;
    }
    count += 1;
    board[r][c] = v;
  }
  int* emptySet = (int*)(calloc(n * n - count, sizeof(int)));
  int index = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (!board[i][j]) {
        emptySet[index] = i * n + j;
        index += 1;
      }
    }
  }
  int soln = sudokuSolv(board, emptySet, 0, n, index);
  printf("%d", soln);
  return 0;
}

int sudokuSolv(int** board, int* emptySet, int depth, int size, int emptySetSize) {
  // base case
  if (depth == emptySetSize) {
    
    int temp = 1;
    int found = 0;
    // check the diagonal:
    for (int i = 1; i <= size; i++) {
      for (int j = 0; j < size; j++) {
        if (board[j][j] == i) {
          found = 1;
          break;
        }
      }
      if (found == 0) {
        return 0;
      }
      found = 0;
    }
    /*
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d", board[i][j]);
        }
    }
    printf("\n");
    */
    return 1;
  }
  int soln = 0;
  int row = emptySet[depth] / size;
  int col = emptySet[depth] % size;
  int temp = 1;
  for (int i = 1; i <= size; i++) {
    // Check constraints
    temp = 1;
    for (int j = 0; j < size; j++) {
      temp *= (board[row][j] != i);
      temp *= (board[j][col] != i);
    }
    if (temp) {
      board[row][col] = i;
      soln += sudokuSolv(board, emptySet, depth + 1, size, emptySetSize);
    }
  }
  board[row][col] = 0;
  return soln;
}
