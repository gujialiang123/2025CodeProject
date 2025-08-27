#include<stdio.h>
#include<iostream>
#include<stack>
using namespace std;
const int N=1e5+10;
inline int read(char ch=getchar(),int n=0,int m=1)
{
	while(ch<'0' or ch>'9')
	{
		if(ch=='-')m=-1;
		ch=getchar();
	}
	while(ch>='0' and ch<='9')n=(n<<3)+(n<<1)+ch-'0',ch=getchar();
	return n*m;
}
ostream& operator <<(ostream& o,__uint128_t &a)
{
	__uint128_t x=a;
	stack<int>s;
	while(x)s.push(x%10),x/=10;
	while(!s.empty())o<<s.top(),s.pop();
	return o;
}
int n=read(),a[N],sum,b[N];
signed main()
{
	for(int i=1;i<=n;i++)a[i]=read(),b[a[i]]++,sum+=a[i];
	if(!b[0])return puts("-1"),0;
	if(sum%3==1)
	{
		if(b[1])b[1]--,sum--;
		else if(b[4])b[4]--,sum-=4;
		else if(b[7])b[7]--,sum-=7;
		else if(b[2]>=2)b[2]-=2,sum-=4;
		else if(b[2]and b[5])b[2]--,b[5]--,sum-=7;
		else if(b[2]and b[8])b[2]--,b[8]--,sum-=10;
		else if(b[5]>=2)b[5]-=2,sum-=10;
		else if(b[5]and b[8])b[5]--,b[8]--,sum-=13;
		else if(b[8]>=2)b[8]-=2,sum-=16;
		else return puts("-1"),0;
	}
	else if(sum%3==2)
	{
		if(b[2])b[2]--,sum-=2;
		else if(b[5])b[5]--,sum-=5;
		else if(b[8])b[8]--,sum-=8;
		else if(b[1]>=2)b[1]-=2,sum-=2;
		else if(b[1]and b[4])b[1]--,b[4]--,sum-=5;
		else if(b[1]and b[7])b[1]--,b[7]--,sum-=8;
		else if(b[4]>=2)b[4]-=2,sum-=8;
		else if(b[4]and b[7])b[4]--,b[7]--,sum-=11;
		else if(b[7]>=2)b[7]-=2,sum-=14;
		else return puts("-1"),0;
	}
	if(!sum)return puts("0"),0;
	for(int i=9;i>=0;i--)
		for(int j=1;j<=b[i];j++)cout<<i;
	return 0;
}