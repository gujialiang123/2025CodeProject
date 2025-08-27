#include<cstdio>
#include<iostream>
using namespace std;
const int Maxn=1000+20,inf=0x3f3f3f3f;
int nxt[Maxn],a[Maxn];
bool f[Maxn],vis[Maxn];
int n,m,val,pos;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
int main()
{
//	freopen("in.txt","r",stdin);
	n=read(),pos=read();
	
	for(int i=1;i<=n;++i)
	{
		int x=read();
		if(x)nxt[x]=i,vis[i]=1;
	}
	for(int i=1;i<=n;++i)
	{
		if(vis[i])continue;
		int cnt=0,x=i;
		while(x)
		{
			++cnt;
			if(x==pos){val=cnt;goto GG;}
			x=nxt[x];
		}
		a[++m]=cnt;
		
		GG:;
	}
	f[0]=1;
	for(int i=1;i<=m;++i)
	{
		for(int j=n;j>=a[i];--j)
		if(f[j-a[i]])f[j]=1;
	}
	for(int i=0;i<=n;++i)
	if(f[i])printf("%d\n",i+val);
	
	return 0;
}