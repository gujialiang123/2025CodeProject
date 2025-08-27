#include<bits/stdc++.h>
using namespace std;
const int N = 2005;
int n, b, a[N], ans = 0;
int main(){
	cin >> n >> b;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
	}
	for(int i = 1; i <= n; i++){ // 枚举买入日期
		int maxi = INT_MIN;
		for(int j = i; j <= n; j++){ // 枚举卖出日期
			maxi = max(maxi, a[j]); // 找最佳卖出日期
		}
		int sum = b / a[i]; // 可以买入的数量 
		int cha = maxi - a[i]; // 买入与卖出的差距 
		ans = max(ans, b + sum * cha); // 最后记得加上开始的钱数 
	}
	cout << ans; 
	return 0;
}