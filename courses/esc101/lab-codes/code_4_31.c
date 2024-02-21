#include <stdio.h>

int main(){
    int t;
    scanf("%d",&t);

    if(t%100 >= 60){
        printf("Invalid Time");
    }
    else if(t>=600 && t<1200){
        printf("Morning");
    }
    else if(t>=1200 && t<1700){
        printf("Afternoon");
    }
    else if(t>=1700 && t<1900){
        printf("Evening");
    }
    else if((t>=1900 && t<2359) || (t>=0 && t<600)){
        printf("Night");
    }
    else{
        printf("Invalid Time");
    }

    
    return 0;
}
