#include<stdio.h>

void isRotation(char s1[], char s2[]){
    int len1=0, len2=0;
    for(; s1[len1]!='\0'; len1++);
    for(; s2[len2]!='\0'; len2++);
    
    if(len1!=len2){
        printf("NO");
        return;
    }
    
    int i, j;
    int isrot=0;
    for(i=0; i<len1*2; i++){
        int flag=1;
        for(j=0; j<len2; j++){
            if(s2[j]!=s1[(i+j)%len1]){
                flag=0;
                break;
            }
        }
        if(flag){
            isrot=1;
            break;
        }
    }
    
    if(isrot)
        printf("YES");
    else
        printf("NO");
}

int main()
{
    char s1[100], s2[100];
    scanf("%s %s", s1, s2);
    
    isRotation(s1, s2);
    return 0;
}
