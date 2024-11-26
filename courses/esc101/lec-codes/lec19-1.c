#include<stdio.h>

int dot_product (int[], int[], int);
// int dot_product (int *, int *, int);

int main(){
    int size = 4;
    int vec1[] = {1,1,1,1};
    int vec2[] = {1,-1,1,-1};

    printf("vec1 . vec1 = %d\n", dot_product(vec1, vec1, size));
    printf("vec1 . vec2 = %d\n", dot_product(vec1, vec2, size));

    return 0;
}

int dot_product (int a[], int b[], int size){
    int p = 0, i;
    for(i=0; i<size; i++)
        p = p + (a[i] * b[i]);

    return p;
}

/* int dot_product (int *a, int *b, int size){
    int p = 0, i;
    for(i=0; i<size; i++)
        p = p + (a[i]*b[i]);

    return p;
} */
