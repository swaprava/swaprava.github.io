#include <stdio.h>
#include "hello.h"
#include "fact.h"

int main () {
    hello();
    printf ("Factorial of 5 is %ld\n", factorial(5));
}