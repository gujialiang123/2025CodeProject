#include<cstdio>
const int MOD=1000000007;
const int MAXN=1e6+5;
int n,dp[MAXN];
void work(){
	for(int i=2;i<=n;i++){
		dp[i]=(dp[i-1]+dp[i-2]+2)%MOD;
	}
}
int main(){
	scanf("%d",&n);
	dp[1]=1;
	work();
	printf("%d",dp[n]);
}
