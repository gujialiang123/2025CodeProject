#include<bits/stdc++.h>
using namespace std;
const int L=1000000;
int a[13][3],n,m,K,ans,ansx=1,ansy=1;
int main()
{
	cin>>n>>m>>K;
	for(int i=1;i<=K;i++) cin>>a[i][0]>>a[i][1];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			int now=0x3f3f3f3f;
			for(int k=1;k<=K;k++) 
			    now=min(now,abs(a[k][0]-i)+abs(a[k][1]-j));
			if(now>ans) ans=now,ansx=i,ansy=j; 
		}
	cout<<ansx<<" "<<ansy;
	return 0;
}