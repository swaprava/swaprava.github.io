#include <stdio.h>

int main(){
    int a,b;
    char ab;
    char c;
    scanf("%c\n",&c);
    scanf("%d\n",&a);
    scanf("%d\n",&b);
    scanf("%c",&ab);
    if(c == '+'){
        long res;
        res = (long)a+b;
        if(ab == 'A')
            printf("%ld",(res<0?-1*res:res));
        else if(ab == 'N'){
            printf("%ld",res);
        }
        else{
            printf("Invalid Calculation");
        }
    }else if( c == '-' ){
        long res;
        res = (long)a-b;
        if(ab == 'A')
            printf("%ld",(res<0?-1*res:res));
        else if(ab == 'N'){
            printf("%ld",res);
        }
        else{
            printf("Invalid Calculation");
        }
    }else if(c == '*'){
        long res;
        res = (long)a*b;
        if(ab == 'A')
            printf("%ld",(res<0?-1*res:res));
        else if(ab == 'N'){
            printf("%ld",res);
        }
        else{
            printf("Invalid Calculation");
        }
    }else if(c == '/'){
        if(b == 0){
            printf("Invalid Calculation");
        }
        else{
            float res;
            res = (float)a/b;
            if(ab == 'A')
                printf("%.4f",(res<0?-1*res:res));
            else if(ab == 'N'){
                printf("%.4f",res);
            }
            else{
                printf("Invalid Calculation");
            }
        }
    }
    else{
        printf("Invalid Calculation");
    }
    return 0;
}
