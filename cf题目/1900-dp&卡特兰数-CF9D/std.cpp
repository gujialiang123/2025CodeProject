#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=36;
ll f[maxn][maxn][maxn];
ll C[maxn][maxn]; 
int n,H;
void init(){
	for(register int i=0;i<=n;i++)
		C[i][0]=C[i][i]=1;
	for(register int i=1;i<=n;i++)
		for(register int j=1;j<i;j++)
				C[i][j]=C[i-1][j]+C[i-1][j-1];
}
int main(){
	scanf("%d%d",&n,&H);
	f[1][1][1]=1,init();
	for(register int i=2;i<=n;i++)
		for(register int j=1;j<=n;j++)
			for(register int u=1;u<=j;u++)
				for(register int k=1;k<=j-u;k++)
					f[i][j][u]+=f[i-1][j-u][k]*C[k*2][u];
	register ll sum=0;
	for(register int i=H;i<=n;i++)
		for(register int j=1;j<=n;j++)
				sum+=f[i][n][j];
	printf("%lld\n",sum);
	return 0;
}