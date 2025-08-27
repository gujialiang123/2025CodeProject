#include <iostream>
#include <string>
#include <cstring> 
using namespace std;
int chartoint(char c){return c-'a'+1;}//字母转数字
char inttochar(int r){return r+'a'-1;}//数字转字母
int g[30][30];
int n=26,m;
void floyd()
{
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
}
string s1,s2;
char c1,c2;
int u,v,w,v1,v2;
int main()
{
	cin>>s1>>s2>>m;
	if(s1.size()!=s2.size())//位数不同肯定不可达
	{
		cout<<-1;
		return 0;
	}
	memset(g,0x3f,sizeof(g));
	for(int i=1;i<=n;i++) g[i][i]=0;
	while(m--)
	{
		cin>>c1>>c2>>w;
		u=chartoint(c1);
		v=chartoint(c2);
		g[v][u]=min(g[v][u],w);//倒着建图
	}
	floyd();
	string as=s1;
	int p,ans=0;
	for(int i=0;i<s1.size();i++)
	{
		if(s1==s2) continue;
		p=0x3f3f3f3f;
		v1=chartoint(s1[i]);
		v2=chartoint(s2[i]);
		for(u=1;u<=n;u++)//枚举源点
		{
			if(g[u][v1]==0x3f3f3f3f||g[u][v2]==0x3f3f3f3f) continue;
			if(p>g[u][v1]+g[u][v2])
			{
				p=g[u][v1]+g[u][v2];
				as[i]=inttochar(u);
			}
		}
		if(p==0x3f3f3f3f)
		{
			cout<<-1;
			return 0;
		}
		ans+=p;
	}
	cout<<ans<<endl<<as;
	return 0;
}