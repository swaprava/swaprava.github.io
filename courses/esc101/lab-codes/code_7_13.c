#include<stdio.h>

int main()
{
    char str[400];
    scanf("%s", str);
    int l=0;
    while(str[l]!='\0'){
        ++l;
    }
    int max=1, mi=0, mj=0;
    for(int i=0; i<l; ++i){
        for(int j=i; j<l; ++j){
            int flag = 1;
            int x = i, y = j;
            while(y>x){
                if(str[x] != str[y]){
                    flag = 0;
                    break;
                }
                ++x;
                --y;
            }
            if(flag){
                if(j-i+1 > max){
                    max = j-i+1;
                    mi = i;
                    mj = j;
                }
            }
        }
    }
    for(int i=mi; i<=mj; ++i){
        printf("%c",str[i] );
    }
    printf("\n");
    return 0;
}
