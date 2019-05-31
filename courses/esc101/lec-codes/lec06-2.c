#include <stdio.h>

int main(){
    
	char firstStr[80];
	printf("Please enter a sentence: "); // unnecessary for prutor
	
    //gets(firstStr);
    fgets(firstStr, 80, stdin);
	
	//printf("Entered sentence is: ");
	//puts(firstStr);

	printf("Entered sentence is: %s", firstStr);
	return 0;
}