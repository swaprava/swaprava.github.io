#include <stdio.h>
#include <stdlib.h>

char* cipher(char * inp, char* s){
    char *out = (char*)malloc(100);
    char *c = inp;
    char* tmp = out;
    while(*c!='\0'){
        *tmp = s[*c-'a'];
        tmp++;
        c++;
    }
    *tmp = '\0';
    return out;
}

int main(){
    char* s = (char*)malloc(27);
    scanf("%s",s);
    char* inp = (char*)malloc(100);
    scanf("%s",inp);

    // printf("%s %s\n",s,inp);

    printf("%s",cipher(inp, s));
    
    return 0;
}
