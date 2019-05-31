#include <stdio.h>

int main(){
	
	char section[11];
	char name[11];
	char day[11];
	
	scanf("%[^/]", section);
	scanf("/%[^/]", name);
	scanf("/%s", day);
	
	printf("%10s\n", name);
	printf("%10s\n", day);
	printf("%10s\n", section);
	
	return 0;
}
