#include <stdio.h>

int main(){
    
        float b=5, c=3, d=4, e,f,g;
        
        e = d/b/c;
        f = d/(b/c);
        g = (d/b)/c;
        
        printf("%f\n", e);
        printf("%f\n", f);
        printf("%f\n", g);
        
      	return 0;
}