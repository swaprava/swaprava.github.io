#include <stdio.h>

int main(){
    
	char firstChar;
	printf("Please enter a character: "); // unnecessary for prutor
	
	//scanf("%c", &firstChar);
	
    firstChar = getchar();
	
	//printf("Entered character is %c\n", firstChar);
	
	printf("Entered character is ");
	putchar(firstChar);
    printf("\n");
	
	return 0;
}