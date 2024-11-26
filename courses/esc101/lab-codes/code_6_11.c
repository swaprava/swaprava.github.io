#include<stdio.h>
int main(){
    int s, x, y, i, j;
    scanf("%d %d %d", &s, &x, &y);
    // Go over all the unit squares
    // Remember we need to start printing from top left corner
    for(j = y + s - 1; j >= y; j--){
        for(i = x; i < x + s; i++){
            // Find which quadrant is this unit square in
            if(((i >= 0)&&(j>=0))||((i<0)&&(j<0)))
                printf("%d", 0);
            else
                printf("%d", 1);
        }
        if(j > y)
            printf("\n");
    }
    return 0;
}
