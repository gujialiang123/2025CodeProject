#include<map>
#include<cstdio>
#include<string>
#include<iostream>
using namespace std;int n,maxn;//maxn为进球最多的那个球队进球数，n为进球次数
map<string,int>s;string ans,k;//s表示每支球队进球几个，ans表示进球最多的那个球队，k为输入的球队
int main()
{
	scanf("%d",&n);
	while(n--)
	 {
     	cin>>k;s[k]++;//输入，并且此队进球
     	if(s[k]>maxn) {maxn=s[k];ans=k;}
     }
	cout<<ans;//输入
}
