#include <stdio.h> 
#include <stdlib.h> 

int gridColour(int** grid, int pos, int size, int colours, int neigh); 
int modulo(int inp, int size); 

int main() { 
  int n; 
  int c;
  int k;
  scanf("%d %d %d", &n, &c, &k); 
  int **grid = (int**)calloc(n, sizeof(int*)); 
  for (int i = 0; i < n; i++) { 
    grid[i] = (int*)calloc(n, sizeof(int)); 
  } 
  int soln = gridColour(grid, 0, n, c, k); 
  printf("%d", soln); 
  return 0; 
} 

int modulo(int inp, int size) { 
  return inp >= 0 ? inp % size : (inp + size) % size; 
} 

int gridColour(int** grid, int pos, int size, int colours, int k) { 
  if (pos == size * size) {
    // Base case 
    return 1; 
  } 
  int row = pos / size; 
  int col = pos % size; 
  int soln = 0; 
  int temp = 1; 
  for (int i = 1; i <= colours; i++) { 
    temp = 1; 
    // Check constraints; 
    temp *= grid[modulo(row - 1, size)][col] != i; 
    temp *= grid[modulo(row + 1, size)][col] != i; 
    temp *= grid[row][modulo(col - 1, size)] != i; 
    temp *= grid[row][modulo(col + 1, size)] != i; 
    
    if (!k) {
        temp *= grid[modulo(row - 1, size)][modulo(col - 1, size)] != i; 
        temp *= grid[modulo(row + 1, size)][modulo(col + 1, size)] != i; 
    }
    
    if (temp) { 
      grid[row][col] = i; 
      soln += gridColour(grid, pos + 1, size, colours, k); 
    } 
  } 
  grid[row][col] = 0; 
  return soln; 
} 
