#include<stdio.h>

int main(){
    int * pc;
    int c;
    c=22;
    printf("Address of c:%p\n",&c);
    printf("Value of c:%d\n\n",c);

    pc=&c;
    printf("Address in pointer pc:%p\n",pc);
    printf("Content pointed by pc:%d\n\n",*pc);

    c=11;
    printf("Address in pointer pc:%p\n",pc);
    printf("Content pointed by pc:%d\n\n",*pc);

    *pc=2; 
    printf("Address of c:%p\n",&c);
    printf("Value of c:%d\n\n",c);
    return 0;
}
