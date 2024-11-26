#include<stdio.h>

int main()
{
    char s1[100], s2[100];
    int a[256]={0}, i, pos=0;
    scanf("%s", s1);
    for(i=0; s1[i]!='\0'; i++){
        char c=s1[i];
        if(a[c]==0){
            s2[pos++]=c;
            a[c]=1;
        }
    }
    s2[pos]='\0';
    printf("%s", s2);
    return 0;
}
