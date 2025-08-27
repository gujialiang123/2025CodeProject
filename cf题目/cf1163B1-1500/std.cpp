#include <bits/stdc++.h>
#define int long long//不开long long 见祖宗，虽然这里好像不用开 
using namespace std;
const int N=1e6+10;
int a[N],sum[20],cnt[N];
signed main(){
	int n,ans,mx;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		cnt[sum[a[i]]]--;
		sum[a[i]]++;
		cnt[sum[a[i]]]++;
		if(i==1) mx=sum[a[i]];
		else mx=max(mx,sum[a[i]]);
		if(i==1) ans=i;
		else if(cnt[i]==1 || cnt[1]==i) ans=i;
		else if(cnt[1]==1 && cnt[mx]*mx==i-1) ans=i;
		else if(cnt[mx]==1 && (mx-1)*cnt[mx-1]+mx==i) ans=i;
	}
	cout<<ans;
	return 0;
}
