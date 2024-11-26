#include <stdio.h>

struct student_st
{
    int roll;
    char email[20];
    char name[20];
};

union student_un
{
    int roll;
    char email[20];
    char name[20];
};


int main() {

    struct student_st st1;
    printf ("Size of struct point pt = %ld\n", sizeof(st1));
    
    union student_un st2;
    printf ("Size of union student st = %ld\n", sizeof(st2));
    

    return 0;
}