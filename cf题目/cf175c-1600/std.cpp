#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,t;
int p[105],f=1,ans,num,cnt,tmp;
struct node
{
	int k,c;
}a[105];
bool cmp(node a,node b)
{
	return a.c<b.c;
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld%lld",&a[i].k,&a[i].c);
	sort(a+1,a+n+1,cmp);//很容易想到的结构体排序
	scanf("%lld",&t);
	for(int i=1;i<=t;i++) scanf("%lld",&p[i]);
	for(int i=1;i<=n;i++)
	{
		if(f==t+1)//第三种情况，跳出循环
		{
			tmp=i;
			break;
		}
		if(num+a[i].k<p[f])//第一种情况
		{
			num+=a[i].k;
			ans+=a[i].k*f*a[i].c;
		}
		else if(num+a[i].k==p[f])//因为不会特殊处理所以单独打了一个相等的情况
		{
			num=p[f];
			ans+=a[i].k*f*a[i].c;
			f++;
		}
		else//第二种情况
		{
			ans+=(p[f]-num)*f*a[i].c;//补齐当前的p
			a[i].k-=p[f]-num;
			num=p[f];
			f++;
			i--;//再重新考虑一遍当前a的数量
		}
	}
	if(tmp)//第三种情况跳出循环后的计算答案
	{
		for(int i=tmp;i<=n;i++) ans+=a[i].k*f*a[i].c;
	}
	printf("%lld",ans);
	return 0;
}
