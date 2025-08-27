#include<bits/stdc++.h>
using namespace std;
double l,d,v,g,r,t;
int main()
{
	scanf("%lf%lf%lf%lf%lf",&l,&d,&v,&g,&r);
	t=d/v; //到达路灯的时间
	while(t>g+r) t=t-g-r; 
	if(t<g) printf("%.8lf\n",l/v);
	else printf("%.8lf\n",l/v+(g+r-t));
	return 0;
}