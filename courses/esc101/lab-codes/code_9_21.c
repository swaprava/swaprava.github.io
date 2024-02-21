#include <stdio.h>
#include <string.h>

int main(){
    char str1[1000], str2[1000], temp[1000];
    int i, j, k;
    
    scanf("%s", str1);
    scanf("%s", str2);
    
    int len = strlen(str1);
    int max = 0;
    
    for(i = 0; i < len; i++){
        for(j = i; j < len; j++){
            for(k = i; k <= j; k++){
                temp[k-i] = str1[k];
            }
            temp[k-i] = '\0';
            if(strstr(str2, temp) != NULL)
                if(j-i+1 > max)
                    max = j-i+1;
        }
    }
    
    printf("%d", max);
    return 0;
}
