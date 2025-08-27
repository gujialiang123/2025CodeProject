#include<bits/stdc++.h>
using namespace std;
const int maxn=1010; 
int n,q[maxn],m,p[maxn],a,b,c;
int main()
{
	scanf("%d",&n); 
	memset(p,0x3f,sizeof(p));
	for(int i=1;i<=n;i++) scanf("%d",&q[i]); 
	scanf("%d",&m);
	for(int i=0;i<m;i++)
	{
		cin>>a>>b>>c;   
		if(q[a]>q[b]) p[b]=min(p[b],c);  
	}
	int cnt=0,ans=0;
	for(int i=1;i<=n;i++)
	{
		if(p[i]>1000000) cnt++;
		else ans+=p[i];  
	}
	if(cnt>1) cout<<-1;
	else cout<<ans;
	return 0;
}