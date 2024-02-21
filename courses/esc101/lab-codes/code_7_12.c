#include<stdio.h>

int main()
{
    char str[40];
    scanf("%s", str);
    int x1=0, x2=0, x3=0, x4=0;
    for(int i=0; i<8; ++i ){
    	x1 = (str[i]-'0') + x1*2;
    }

    for(int i=8; i<16; ++i ){
    	x2 = (str[i]-'0') + x2*2;
    }

    for(int i=16; i<24; ++i ){
    	x3 = (str[i]-'0') + x3*2;
    }

    for(int i=24; i<32; ++i ){
    	x4 = (str[i]-'0') + x4*2;
    }
    printf("%d.%d.%d.%d\n", x1, x2, x3, x4);
    return 0;
}
