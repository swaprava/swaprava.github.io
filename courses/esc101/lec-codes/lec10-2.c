#include <stdio.h>
#include <string.h>

int main(void)
{
    char section[5];
    int len, sectionID;

    printf ("Enter your section: ");
    scanf (" %s", section);

    len = strlen(section);

    printf("first character %c \n", section[0]);
    printf("second character %c \n", section[1]);
    printf("third character %c \n", section[2]);

    if ( (section[0] != 'a') && (section[0] != 'A') ) {
        printf ("invalid section, not a or A\n");
        return 0;
    }
    else if (len <= 2) 
        sectionID = section[1] - '0';
    else if (len <= 3)
                sectionID = (section[1] - '0') * 10 + section[2] - '0';
    else {
        printf ("invalid section, not within 2 digits\n");
        return 0;
    }

    printf("Section A%d\n", sectionID);

    
    switch (sectionID)
    {
        case 13:
            printf("Lab day Monday, Tutor Deepanshu\n");
            break;

        case 8:
            printf("Lab day Wednesday, Tutor Anmol\n");
            break;
    
        default:
            printf("Not in the known list\n");
            break;
    }

    return 0;
}