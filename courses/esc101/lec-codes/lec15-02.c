#include <stdio.h>


/*
// local variable
void f() {
    int var1;
    var1 = 1; // OK: in scope
}
void g() {
    var1 = 2; // Error: not in scope
}
*/

int var2 = 99; // global variable, what about declaring it const?

void f() {
    var2 = 1; // OK: in scope
    printf ("%d\n", var2);

    // what if instead of updating the global variable, we redefine it
    //int var2 = 1; // OK: in scope
    //printf ("%d\n", var2);
}
void g() {
    var2 = 2; // OK: still in scope
    printf ("%d\n", var2);
}

void h() {
    static int x = 1; // for static variables, this is initialization, and is not updated afterwards
    printf ("%d ", x);
    x += 10;
}


int main()
{
    //f();
    //printf ("%d\n", var2);


    /*
    for (int i = 0; i < 10; i++) {
        static int n = 0; // what about static?
        printf("%d\n", ++n);
    }

    */
    
    
    h();
    h();
    h();
    printf ("\n");
    

    return 0;
}
