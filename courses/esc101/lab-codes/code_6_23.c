#include <stdio.h>
#include <stdlib.h>



int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)b - *(int*)a );
}


int sortdig (int n)
{
	int a[9] = {0};
	int pos=0,ans=0, i=0;;
	while (n){a[pos++]= n%10;n/=10;}
	qsort(a,pos,sizeof(int),cmpfunc);
	for(i=0;i<pos;i++) {ans=ans*10+a[i];}
	return ans;
}

int addtrail(int n, int dig)
{
	int pos=0, ans=n;
	while(n) {pos++;n=n/10;}
	while (pos<dig) {pos++;ans*=10;}
	return ans;
}

int revdig(int n)
{
	int ans=0;
	while (n)
	{
		ans = ans*10 + n%10;
		n = n/10;
	}
	return ans;
}

void karprekar (int n)
{
	int diff = n;
	while(diff!=6174)
	{
		int large = sortdig(diff);
		large = addtrail(large,4);
		int small = revdig(large);
		diff = large - small;
		printf("%04d - %04d = %04d\n",large, small, diff);
	}
	
}

int main()
{
	int n;
	scanf("%d",&n);
	karprekar(n);
	return 0;
}
