#include <stdio.h>

int main(){
    
	int firstInt, secondInt;
	printf("Please enter two integers: ");
	scanf("%d %d", &firstInt, &secondInt);
	
	printf("Sum of these two integers is %d\n", firstInt + secondInt);
	
	return 0;
}