#include <stdio.h> // header file macro
#define PI 3.1415  // variable definition macro
#define circleArea(r) (PI*r*r) // function definition macro

int main()
{
    // predefined macro 
    printf ("Today's date: %s\n", __DATE__);
    printf ("Time: %s\n", __TIME__);

    
    // use of the defined variable macro
    float radius, area;
    printf("Enter the radius: ");
    scanf("%f", &radius);
    // Notice, the use of PI
    area = PI*radius*radius;
    printf ("Area=%.2f\n",area);

    // using function macro
    printf ("Using function macro, area = %.2f\n", circleArea(radius));
    
    return 0;
}
