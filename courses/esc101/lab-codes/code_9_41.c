#include <stdio.h>

int main(){
	int n;
	scanf("%d", &n);

    int mat[n][n];
    
    int dir = 0;
    int i = 0, j = 0, k = 1;

    for(i=0;i<n;i++){
    	for(j=0;j<n;j++){
    		mat[i][j] = 0;
    	}
    }
    i = 0;
    j = 0;
    k = 1;
    while (k <= n * n) {
        mat[i][j] = k++;
        if (dir == 0){
            j++;
            if (j == n || mat[i][j] != 0){
            	dir = 1;
            	j--;
            	i++;
            }	
        } else if (dir == 1) {
            i++;
            if (i == n || mat[i][j] != 0){
            	dir = 2;
            	i--;
            	j--;
            }
        } else if (dir == 2) {
            j--;
            if (j < 0 || mat[i][j] != 0){
            	dir = 3;
            	j++;
            	i--;
            }
        } else if (dir == 3) {
            i--;
            if (i < 0 || mat[i][j] != 0){
            	dir = 0;
            	i++;
            	j++;
            }
        }
    }

    for(i=0;i<n;i++){
    	for(j=0;j<n;j++){
    		printf("%d ", mat[i][j]);
    	}
    	printf("\n");
    }
	return 0;
}
