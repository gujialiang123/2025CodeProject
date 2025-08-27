#include<bits/stdc++.h>
using namespace std;
int n,m;
bool dis[105][105][105];
int main()
{
 cin>>n>>m;
 for(int i=1;i<=m;i++)
 {
  int u,v,c;
  cin>>u>>v>>c;
  dis[u][v][c]=1;
  dis[v][u][c]=1;//无向图 
 }
 for(int k=1;k<=n;k++)
  for(int u=1;u<=n;u++)
   for(int v=1;v<=n;v++)
    for(int c=1;c<=m;c++)
    if(dis[u][k][c]&&dis[k][v][c])
     dis[u][v][c]=1;
  int q;
  cin>>q;
  while(q--)
  {
   int u,v,ans=0;
   cin>>u>>v;
   for(int i=1;i<=m;i++)
   if(dis[u][v][i]) ans++;
   cout<<ans<<endl;
  }
 return 0;
}