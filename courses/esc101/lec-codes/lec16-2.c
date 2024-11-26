#include <stdio.h>

void move (char origin, char destination, char intermediate, int numOfDisks){
    
    if (numOfDisks == 0)
        return ;
        
    move (origin, intermediate, destination, numOfDisks-1);
    // getchar ();
    printf ("Move disk from %c to %c\n", origin, destination);
    move (intermediate, destination, origin, numOfDisks-1);  

}

int main()
{
    int num;
    printf ("Enter the number of disks: ");
    scanf ("%d", &num);
    move ('A', 'C', 'B', num);
    return 0;
}