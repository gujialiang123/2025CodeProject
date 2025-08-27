#include <cstdio>
#include <algorithm>
using namespace std;
int const N=1e5+10;
long long f[N];
int n,m,ans[N];
int main()
{
    int s,k; scanf("%d%d",&s,&k);
    int n; f[1]=1;
    for(n=2;f[n-1]<s;n++)
        for(int j=max(1,n-k);j<=n-1;j++) f[n]+=f[j];
    int m=0;
    for(int i=n-1;i>=1&&s;i--) if(f[i]<=s) ans[++m]=f[i],s-=f[i];
    if(m<2) ans[++m]=0;
    printf("%d\n",m);
    for(int i=1;i<=m;i++) printf("%d ",ans[i]);
    puts("");
    return 0;
}