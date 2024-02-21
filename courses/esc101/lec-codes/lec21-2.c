#include <stdio.h>
#include <string.h>

void strrevx (char srcStr[], char destStr[]){
    int i;
    int size = strlen(srcStr);
    destStr[size] = '\0';
    for(i=0; i<size; i++){
        destStr[i] = srcStr[size-i-1]; // reversal
    }
}

void strrev (char str[]){
    char temp;
    int size = strlen(str);
    int start = 0, end = size-1;

    while (start < end){
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

int main() 
{ 
   char str[50] = "123456789"; 
   char revstr[50];
  
   printf("The given string is = %s\n", str); 

   strrevx (str, revstr);
//    strrev(str);
  
   printf("After reversing string is = %s\n", revstr); 
//    printf("After reversing (inplace) string is = %s\n", str); 
  
   return 0; 
} 