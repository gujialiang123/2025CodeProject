#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define int long long
using namespace std;

const int N = 1e6 + 100;
const int mod = 1e9 + 7;
char ch[N];
int t , n , m , z , k , a[N] , b[N];

int ksm(int x,int y) {
	int res = 1;
	for(;y;y >>= 1 , x = x * x % mod) 
		if(y & 1) 
			res = res * x % mod;
	return res;
}

signed main() {
	cin >> t;
	while(t --) {
		cin >> n >> m >> k;
		int wd = (9 / k);
		int now = (((ksm(wd + 1 , m - n) - 1) % mod) + mod) % mod; 
		now = ksm(wd + 1 , n) % mod * now % mod;
		cout << now << "\n"; 
	}
	return 0;
}
