#include<stdio.h>
int main()
{
    int i,j,n, num, elem, not_scalar=0;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&num);
            if(i==0 && j==0)
            {
                elem = num;
            }
            if((i==j && num != elem )||(i!=j && num != 0 ))
            {
                not_scalar = 1;
            }
        }
    }
    if(not_scalar)
    {
        printf("GIVEN %d x %d matrix is NOT a SCALAR MATRIX",n,n);
    }
    else
    {
        printf("GIVEN %d x %d matrix is a SCALAR MATRIX",n,n);
    }
    return 0;
}
