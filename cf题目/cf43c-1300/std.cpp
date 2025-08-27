#include<bits/stdc++.h>
using namespace std;
const int MAXN=10000+10;
int n,three,two,one;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
	    int t;
		scanf("%d",&t);
		if(t%3==0) three++;
		if(t%3==1) one++;
		if(t%3==2) two++;
	}
	printf("%d\n",three/2+min(one,two));
	return 0;
}
