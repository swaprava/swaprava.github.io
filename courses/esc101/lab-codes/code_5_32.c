#include <stdio.h>
#include <math.h>
 
int main() {
    long int num;
    scanf("%ld", &num);
 
    if (num == 2) {
        printf("2\nPRIME");
    } else {
        int div;
        int isPrime = 1;
        for(int i=3; i < sqrt(num) + 1; i+=2){
            if(num%i == 0){
                printf("%d\n", i);
                isPrime = 0;
                break;
            }
        }
        if(isPrime == 0){
            printf("COMPOSITE");
        } else{
            printf("%d\nPRIME", num);
        }
    }
 
    return 0;
}
