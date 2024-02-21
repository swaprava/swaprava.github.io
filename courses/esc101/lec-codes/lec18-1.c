#include <stdio.h>

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

int main()  {
    char s[10];
    read_into_array(s,10);
    for (int i=0; i < 10; i++)
        printf ("%c", s[i]);

    printf("\n%s", s);
    printf("\n");
    return 0;
}