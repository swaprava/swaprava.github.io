#include<stdio.h>
#define NumChars 256
int main()
{
    char s1[10010];
    char s2[10010];
    scanf("%s", s1);
    scanf("%s", s2);
    int character[NumChars];
    for(int i=0; i<NumChars; ++i){
        character[i] = 0;
    }
    for(int i=0; s1[i]!='\0'; ++i){
        character[(int)s1[i]]++;
    }
    for(int i=0; s2[i]!='\0'; ++i){
        character[(int)s2[i]]--;
    }
    int flag=1;
    for(int i=0; i<NumChars; ++i){
        if(character[i]){
            flag=0;
            break;
        }
    }
    if(flag){
        printf("Yes\n");
    }
    else{
        printf("No\n");
    }
    
    return 0;
}
