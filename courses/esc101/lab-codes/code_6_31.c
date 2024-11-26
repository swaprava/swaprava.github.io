#include<stdio.h>

int main()
{
    int ans=0;
    int ok = 0;
    char c;
    do{
        scanf("%c",&c);
        if(c=='(')
            ans=ans+1;
        else if(c==')')
            ans=ans-1;
        else {
            break;
        }
        if(ans<0)
            ok=1;
    }
    while(1);
    if(ans!=0)
        ok=1;
    if(ok==0)
        printf("ALLOWED");
    else
        printf("NOT ALLOWED");
    return 0;
}
