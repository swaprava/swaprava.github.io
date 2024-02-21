#include <stdio.h>

void displayEuclid (int);

int main(void)
{
    int n;

    // take input from the user
    printf("Enter n: ");
    scanf("%d", &n);

    displayEuclid (n);

    return 0;
}


int primorial (int);
int isPrime (int);

void displayEuclid (int number){
    int i, euclidNum;
    
    for (i=1; i<=number; i++) {
        euclidNum = primorial(i)+1;
        if (isPrime(euclidNum) == 1)
            printf("%d: Prime\n", euclidNum);
        else
            printf("%d: Composite\n", euclidNum);
    }

}


int primorial(int n)  // return the n-th primorial number
{
    int count=0, i=2, prod=1;
    while (count < n){
        if (isPrime(i) == 1){
            prod = prod * i;
            count++; 
        }
        i++; 
    }
    return prod;
}


int isPrime (int num){
    
    int j;

    for (j = 2; j*j <= num; j++){
        if (num % j == 0)
            return 0;
    }

    return 1;
}