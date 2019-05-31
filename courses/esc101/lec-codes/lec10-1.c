#include <stdio.h>
#include <string.h>

int main(void)
{
    char section[5];
    int len;

    printf ("Enter your section: ");
    scanf (" %s", section);

    len = strlen(section);

    if ( strcmp(section, "a13") == 0 || strcmp(section, "A13") == 0 )
        printf("Lab day Monday, Tutor Deepanshu\n");

    else if ( strcmp(section, "a8") == 0 || strcmp(section, "A8") == 0 )
        printf("Lab day Wednesday, Tutor Anmol\n");

    else
        printf("Not in the known list\n");
    

    return 0;
}