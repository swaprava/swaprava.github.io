#include<stdio.h>
#include<math.h>
int numOfDigits(int n){
    int ret=0;
    for(;n;ret++,n/=10);
    return ret;
}
int compare(int a,int b){
    int da=numOfDigits(a),db=numOfDigits(b);
    long long int ab=a*pow(10,db)+b,ba=b*pow(10,da)+a;
    if(ab>ba)
        return 1;
    return 0;
}
int main()
{
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
    if(compare(a,b)){
        int temp=a;
        a=b;
        b=temp;
    }
    if(compare(a,c)){
        int temp=a;
        a=c;
        c=temp;
    }
    if(compare(b,c)){
        int temp=c;
        c=b;
        b=temp;
    }
    printf("%d%d%d",c,b,a);
    return 0;
}
