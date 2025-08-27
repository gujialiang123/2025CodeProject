#include<bits/stdc++.h>
using namespace std;
long long k,ans,t,a,b,i;
bool x[5000000];
int main()
{
    scanf("%d%d",&a,&b);
    k=a*b/__gcd(a,b);
    if(a>b)
    {
	    for(i=1;i<=b+1;i++)
		{
		    t=a*i%b;
			if(x[t]==true) break;
			ans+=t;
			x[t]=true;
		}
		if(a*(i-1)%b==0) ans+=b;
		if(ans>k-ans) puts("Dasha");
		else if(ans<k-ans) puts("Masha");
		else puts("Equal");
	}
	else 
	{
   	    for(i=1;i<=a+1;i++)
		{
		    t=b*i%a;
			if(x[t]==true) break;
			ans+=t;
			x[t]=true;
		}
		if(b*(i-1)%a==0) ans+=a;
		if(ans<k-ans) puts("Dasha");
		else if(ans>k-ans) puts("Masha");
		else puts("Equal");
	}
}