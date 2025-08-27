#include <bits/stdc++.h>
using namespace std;
long long n;
priority_queue<long long,vector<long long>,less<long long> >q; //大根堆
int main() {
//	freopen("potions.in","r",stdin);
//	freopen("potions.out","w",stdout);
	cin>>n;
	long long ans=0,s=0;//ans：药剂瓶数 s:当前体力和
	for (int i=1; i<=n; i++) {
		long long x;
		cin>>x;
		if (x<0)
			q.push(-x); //如果为负数，绝对值入堆
		s+=x; //当前体力和加x
		ans++; //药剂瓶数加1
		if(s<0) {  //如果体力值不满足条件了
			long long k=q.top(); //取出堆中最大的绝对值，就是最小的负数
			s+=k; //体力和恢复k
			ans--; //药剂瓶数减1，因为丢弃了一瓶药剂
			q.pop(); 
		}
	}
	cout<<ans;
	return 0;
}
