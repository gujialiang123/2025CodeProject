#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 200005

int n,k,a[MAXN],b[MAXN],Ans = 0;

inline bool chk( int x ){
	int tmp = k;
	for( int i = 1 ; i <= n ; i ++ ){
		tmp = k;
		for( int j = i ; j <= n ; j ++ ){
			if( a[j] < x - ( j - i ) ){
				if( tmp < ( x - j + i - a[j] ) ) break;
				tmp -= ( x - j + i - a[j] );
			}
			else return 1;
		}
	}
	return 0;
}

inline void solve(){
	scanf("%lld%lld",&n,&k);
	for( int i = 1 ; i <= n ; i ++ ) scanf("%lld",&a[i]);
	int l = 0,r = 1e9,Ans = 0;
	while( l <= r ){
		int mid = ( l + r ) >> 1;
		if( chk( mid ) ) Ans = mid,l = mid + 1;
		else r = mid - 1;
	}
	printf("%lld\n",Ans);
}

signed main(){
	int testcase; scanf("%lld",&testcase);
	while( testcase -- ) solve();
	return 0;
}
