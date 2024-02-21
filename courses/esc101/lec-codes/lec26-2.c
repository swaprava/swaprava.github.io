#include<stdio.h> 
  
int main() 
{ 
    // Pointer to an integer 
    int *p;  
    
    // Pointer to an array of 5 integers 
    int (*ptr)[5];  
    int arr[5]; 
    
    // Points to 0th element of the arr. 
    p = arr; 
    
    // Points to the whole array arr. 
    ptr = &arr;  
    
    printf("p = %p, ptr = %p\n", p, ptr); // addresses are printed in hexadecimal
    // printf("p = %ld, ptr = %ld\n", (size_t) p, (size_t) ptr); // print the unsigned long of the same address
    
    p++;  
    ptr++; 
    
    printf("p = %p, ptr = %p\n", p, ptr); // addresses are printed in hexadecimal
    // printf("p = %ld, ptr = %ld\n", (size_t) p, (size_t) ptr); // print the unsigned long of the same address
    
    return 0; 
} 