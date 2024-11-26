#include <stdio.h>
#include <string.h>

int read_into_array (char t[], int size) {
    char ch;
    int count = 0;
    scanf("%c", &ch);
    while (count < size && ch != '\n') {
	    t[count] = ch;
	    count = count + 1;
        scanf("%c", &ch);
    }
    t[count] = '\0';
    return count;
}

void str_find() {
    char str[100];
    int size = 100;
    read_into_array(str, size);
    char *p = strstr(str, "very nice");
    if(p!=NULL){
        printf("%s\n", p);
        printf("%ld\n", p-str+1); // note the difference is in the addresses
    }else
        printf("Not found\n");


/*     int a[10];
    // long int b1, b0;
    // b1 = (long int) &a[1], b0 = (long int) &a[0];

    printf ("%ld\n", &a[1] - &a[0]);
    // printf ("%ld\n", b1-b0); */
}

    
int main(){
    
    str_find();

    return 0;
}