#include<stdio.h>

#define MAXN 10

int n;
char str[MAXN+1];

void genBinStrings(int pos) {
    if(pos == n) {
        printf("%s\n", str);
        return;
    }

    str[pos] = '0';
    genBinStrings(pos+1);

    str[pos] = '1';
    genBinStrings(pos+1);
}

int main() {
    scanf("%d", &n);

    str[n] = '\0';

    genBinStrings(0);

    return 0;
}
