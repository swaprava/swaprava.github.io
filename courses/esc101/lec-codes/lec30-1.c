#include <stdio.h>

int main(int argc, char const *argv[])
{
    for (int i=0; i < argc; i++)
        printf ("argv[%d] = %s\n", i, argv[i]);
    
    if (argc < 2){
        printf ("Too few arguments\n");
        return 0;
    }
    else if (argc == 2){
        printf ("Hello %s, how are you?\n", argv[1]);
    }
    else
    {
        printf ("Too many arguments\n");
    }
    
    return 0;
}
