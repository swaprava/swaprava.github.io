#include <stdio.h>

int main(){
    long int a,b, res;
    char c;
    scanf("%c %ld %ld", &c, &a, &b);
    if(c == '+'){
        res = a+b;
        printf("%ld",res);
    }else if( c == '-' ){
        res = a-b;
        printf("%ld",res);
    }else if(c == '*'){
        res = a*b;
        printf("%ld",res);
    }else if(c == '/'){
        if(b == 0){
            printf("Invalid Calculation");
        }
        else{
            res = a/b;
            printf("%ld",res);
        }
    }
	else if (c == '%'){
		if(b <= 0){
            printf("Invalid Calculation");
        }
        else{
            res = ((a%b)+b)%b;
            printf("%ld",res);
        }
	}
    else{
        printf("Invalid Calculation");
    }
    return 0;
}
