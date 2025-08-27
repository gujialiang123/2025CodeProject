#include<bits/stdc++.h>
using namespace std;
int n,m,len,vis[27],ans;
double dis[27],x;
char map[35][35];
double diss(int x,int y,int xx,int yy)
{return sqrt((x-xx)*(x-xx)+(y-yy)*(y-yy));}
string a;
int main()
{
    cin>>n>>m>>x;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>map[i][j];
            if(map[i][j]>='a')vis[map[i][j]-'a'+1]=1;
		}
    }
    for(char g='a';g<='z';g++)
    {
        dis[g-'a'+1]=55;
        for(int i=1;i<=n;i++)//遍历一遍键盘
            for(int j=1;j<=m;j++)
                if(map[i][j]==g)//找到了g
                    for(int k=1;k<=n;k++)//再次遍历一遍键盘
                        for(int h=1;h<=m;h++)
    if(map[k][h]=='S') dis[g-'a'+1]=min(dis[g-'a'+1],diss(i,j,k,h));
	}
    cin>>len>>a;//字符串
    for(int i=0;i<len;i++)
    {
        if((a[i]<='Z'&&dis[a[i]-'A'+1]==55)||(a[i]>='a'&&!vis[a[i]-'a'+1]))
		{
            cout<<-1;
            return 0;//直接退出
        }
        if(a[i]<='Z'&&dis[a[i]-'A'+1]>x)ans++;//手短，ans++
    }
    cout<<ans;
    return 0;
}