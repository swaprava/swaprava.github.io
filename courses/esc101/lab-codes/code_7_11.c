// C++ program to calculate pow(x,n) 
#include <stdio.h>

typedef long long ll;
/* Function to calculate x raised to the power y */

ll power(ll x,  ll y) 
{ 
	printf("%lld,%lld\n",x, y );
	if(y==0)
	    return 1;
// 	if (y == 1) 
// 		return x; 

	ll p = power(x, y / 2);
	if (y % 2 == 0) {
		return p*p; 
	}
	else{
		return x*p*p; 
	}
} 
 

/* Driver code */
int main() 
{ 
	ll x ;
	 ll y;
	scanf("%lld", &x);
	scanf("%lld", &y); 
	printf("%lld\n", power(x, y));
	return 0; 
} 
