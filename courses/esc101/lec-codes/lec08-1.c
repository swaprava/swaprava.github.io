#include <stdio.h>

int main(){
    
        int m=10, n=5;
        int a = 99;
        
        {
            //int a=7;
            printf("inside, variable value = %d\n", a++);
        }
        
        printf("outside, value = %d", a);
        
      	return 0;
}