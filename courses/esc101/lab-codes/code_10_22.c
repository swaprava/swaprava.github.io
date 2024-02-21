#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char *s;
    s = (char*)malloc(100);

    int idx[100];
    int a[100];
    scanf("%s",s);
    int k;
    scanf("%d",&k);

    for(int i = 0;i<k-1;i++)
        scanf("%d",idx + i);
    for(int i = 0;i<k;i++)
        scanf("%d",a+i);
    
    char *p = (char*)malloc(100);
    char *arr[101];
    arr[0] = s;
    for(int i = 1; i < k; i++)
    {
        arr[i] = s + idx[i-1];
    }
    arr[k] = s + strlen(s);
    
    // for(int i = 0;i<k;i++){
    //     printf("%d %s\n",a[i], arr[i]);
    // }
    char *pp = p;
    for(int i = 0;i<k;i++){
        int t = a[i]-1;
        char * tmp = arr[t];
        while(tmp != arr[t+1]){
            *pp = *tmp;
            pp++;
            tmp++;
        }
    }
    *pp = '\0';

    printf("%s\n",p);

    return 0;
}
