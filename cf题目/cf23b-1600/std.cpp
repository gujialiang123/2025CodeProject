#include<iostream>
#include<cstdio>
using namespace std;

int T,n;

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		(n<2)?printf("0\n"):printf("%d\n",n-2);
	}
	return 0;
}