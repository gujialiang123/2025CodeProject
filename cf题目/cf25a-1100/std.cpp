#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int a[105];
int main()
{
	int n;
	scanf("%d",&n);
	int sum=0;//一开始忘了归0，交了10+次
	for(int i=1;i<=n;i++){
		int t;
		scanf("%d",&t);
		a[i]=t%2;//还是要存下来的，后面找数时要用到。
		sum+=a[i]; 
	}
	int ans=0;
	if(sum==1)//n最少为3，所以不用特判n=2。
	{
		for(int i=1;i<=n;i++)//找唯一的奇数
		{
			if(a[i]==1)
			{
				ans=i;
				break;
			}
		}
	}
	if(sum==n-1)
	{
		for(int i=1;i<=n;i++)//找唯一的偶数
		{
			if(a[i]==0)
			{
				ans=i;
				break;
			}
		}
	}
	printf("%d\n",ans);
	return 0; 
}