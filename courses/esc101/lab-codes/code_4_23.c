#include <stdio.h>

int main(){
    int a,b;
    char c;
    scanf("%c\n",&c);
    scanf("%d\n",&a);
    scanf("%d",&b);
    if(c == '+'){
        long res;
        res = (long)a+b;
        printf("%ld",res);
    }else if( c == '-' ){
        long res;
        res = (long)a-b;
        printf("%ld",res);
    }else if(c == '*'){
        long res;
        res = (long)a*b;
        printf("%ld",res);
    }else if(c == '/'){
        if(b == 0){
            printf("Invalid Calculation");
        }
        else{
            float res;
            res = (float)a/b;
            printf("%.3f",res);
        }
    }
    return 0;
}
