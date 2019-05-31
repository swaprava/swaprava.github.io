#include<stdio.h>

#define MAXN 10

int n;
char str[2*MAXN+1];

void genParens(int pos, int opencount, int closecount) {
    if(pos == 2*n) {
        printf("%s\n", str);
        return;
    }
    
    if(opencount<n) {
        str[pos] = '(';
        genParens(pos+1, opencount+1, closecount);
    }

    if(opencount > closecount) {
        str[pos] = ')';
        genParens(pos+1, opencount, closecount+1);
    }
}

int main() {
    scanf("%d", &n);

    str[2*n] = '\0';

    genParens(0, 0, 0);

    return 0;
}
