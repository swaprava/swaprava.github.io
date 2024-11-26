#include <stdio.h>
#include <stdlib.h>

char* StringSwap(char* s, int i){
    char *n = (char*)malloc(100);
    char *c = s+i;
    char *p = n;
    while(*c != '\0'){
        *p = *c;
        p++;
        c++;
    }
    
    c = s;
    while(c!=(s+i)){
        *p = *c;
        c++;
        p++;
    }
    *p = '\0';
    return n;
}

int main(){
    int i;
    char *s;
    s = (char*)malloc(100);
    scanf("%s",s);
    scanf("%d",&i);
    printf("%s",StringSwap(s,i));
    return 0;
}

