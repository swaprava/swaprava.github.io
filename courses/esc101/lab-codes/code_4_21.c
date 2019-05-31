#include <stdio.h>

int main(){
	char n;
	scanf("%c",&n);
	if(n=='a'){
		printf("alpha");
	}
	else if(n == 'b'){
		printf("beta");
	}
	else if(n == 'c'){
		printf("gamma");
	}
	else if(n == 'd'){
		printf("delta");
	}
	else if(n == 'A'){
		printf("ALPHA");
	}
	else if(n == 'B'){
		printf("BETA");
	}
	else if(n == 'C'){
		printf("GAMMA");
	}
	else if(n == 'D'){
		printf("DELTA");
	}
	else{
		printf("Invalid Character");
	}

	return 0;
}
