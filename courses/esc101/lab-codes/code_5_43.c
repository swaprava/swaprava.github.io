#include <stdio.h>

int main(){
	int i, j, rows;
	scanf("%d", &rows);
	for (i=1; i<=rows; i++){
		for (j=1; j<=rows-i; j++)
			printf("  ");
		for (j=1; j<=i/2; j++){
			printf("%2d  ", j);
		}
		for (j=(i+1)/2; j>0; j--){
			if(j!=1){
				printf("%2d  ", j);
			}
			else
				printf("%2d", j);
		}
		printf("\n");
	}
	return 0;
}
