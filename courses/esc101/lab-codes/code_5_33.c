#include <stdio.h>

int main(){
	int i, j, h, rows_done=0;
	scanf("%d", &h);
	for (i=0; ; ){
		if (i==-1)
			break;
		for (j=0; j<h/2-i; j++)
			printf(" ");
		printf("*");
		for (j=0; j<2*i-1; j++)
			printf(" ");
		if (i!=0)
			printf("*");
		printf("\n");
		rows_done++;
		i = (rows_done<=h/2)?i+1:i-1;
	}
	return 0;	
}
