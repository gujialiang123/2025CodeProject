#include<bits/stdc++.h>
#define MAXN 110
using namespace std;
int n,x,c[MAXN];
int main()
{
	//freopen("cd35d-10.in","r",stdin);
	//freopen("cd35d-10.out","w",stdout);
	scanf("%d%d",&n,&x);
	for(int i=1;i<=n;++i) scanf("%d",&c[i]),c[i]*=(n-i+1); //体积 
	sort(c+1,c+n+1); //从小到大排序 
	int ans=0; 
	for(int i=1;i<=n;++i)
		if (x>=c[i]) ++ans,x-=c[i]; //贪心选择 
		else break;
	printf("%d\n",ans);
	return 0;
}