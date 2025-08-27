#include<bits/stdc++.h>
#define int long long
using namespace std;
int T, n;
map<int,int> cnt;
int dp[5005];
signed main() {
	ios :: sync_with_stdio(false); 
	freopen("cf1875d10.in","r",stdin);
	freopen("cf1875d10.out","w",stdout);
	cin >> T;
	while (T--) {
		cin >> n;
		cnt.clear();
		memset(dp, 0x3f, sizeof(dp));
		for (int i = 1, tmp; i <= n; i++) {
			cin >> tmp;
			cnt[tmp]++;
		}
		int mex = 0;
		while (cnt[mex]) mex++;
		dp[mex] = 0;
		for (int i = mex; i >= 1; i--) {
			for (int j = 0; j < i; j++) {
				dp[j] = min(dp[j], dp[i] + (cnt[j] - 1) * i + j);
			}
		}
		cout << dp[0] << endl;
		
	}
	return 0;
}
