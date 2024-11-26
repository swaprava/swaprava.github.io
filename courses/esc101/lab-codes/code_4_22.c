#include <stdio.h>
#include <math.h>
int main(){
    float a,b,c,d,e,alpha,beta;
    scanf("%f %f %f %f %f %f %f",&a,&b,&c,&d,&e,&alpha,&beta);
    if(beta <= 0 || alpha <= 0){
        if(d != 0){
            printf("Undefined");
        }
        else{
            float area = a*pow(beta,5)/5 + b*pow(beta,4)/4 + c*pow(beta,3)/3 + e*exp(beta);
            area = area - (a*pow(alpha,5)/5 + b*pow(alpha,4)/4 + c*pow(alpha,3)/3 + e*exp(alpha));
            printf("%.1f",area);
        }
    }
    else{
        float area = a*pow(beta,5)/5 + b*pow(beta,4)/4 + c*pow(beta,3)/3 + d*log(beta) + e*exp(beta);
        area = area - (a*pow(alpha,5)/5 + b*pow(alpha,4)/4 + c*pow(alpha,3)/3 + d*log(alpha) + e*exp(alpha));
        printf("%.1f",area);
    }
    return 0;
}
