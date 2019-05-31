#include <stdio.h>

int main () {

    FILE * fwrite;
    fwrite = fopen("morning.txt", "w");
    
    if (fwrite == NULL)
        printf ("File opening failed\n");
    else {
        fprintf(fwrite, "Good morning everyone!\n");
        fclose(fwrite);
    }
    
    return 0;
}