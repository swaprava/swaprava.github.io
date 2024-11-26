#include <stdio.h>

int main () {
    
    FILE * fread;
    char ch;

    fread = fopen("example.txt", "r");

    if (fread == NULL)
        printf ("ERROR: no such file\n");
    else {
        while (!feof(fread)) {
            fscanf (fread, "%c", &ch);
            printf ("%c", ch);
            // printf ("%c %ld ", ch, ftell(fread));
        }
    }
    
    return 0;
}