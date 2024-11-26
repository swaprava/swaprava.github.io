#include <stdio.h>
#include <math.h>
 
int main() {
  
    int n;
    double m;
    printf("Please enter a positive number: ");
    scanf("%d",&n);
    if (n>0){
	    m = log(n);			// natural log
	    printf("%f\n", m);
    }
    else
	    printf("Why can't you follow instructions?\n");

    return 0;
}
