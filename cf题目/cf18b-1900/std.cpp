#include<iostream>
using namespace std;
typedef long long ll;   //类型定义long long为ll，避免频繁使用long long时累手 
int main()
{
	ios::sync_with_stdio(0);   //关同步流，加速cin输入和cout输出 
	ll n,d,m,l,ans=0;  
	cin>>n>>d>>m>>l; 
	for(ll i=1;i<=n;i++)
	{
		if(ans<((i-1)*m))
		{
			break;
		}
		while(ans<=(i-1)*m+l)
		{
			ans=(((i-1)*m+l)/d)*d+d;
		}
	}
	cout<<ans;
	return 0;
}