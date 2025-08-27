#include<iostream>
using namespace std;
int main()
{
	int n,a,b,c,ans=0;
	cin>>n>>a>>b>>c;
	for(int i=0;i<=min(n/2,c);i++) 
		for(int j=0;j<=min(n,b);j++)
			if((n-i*2-j)*2<=a && n-i*2-j>=0) ans++; 
	cout<<ans<<endl; 
	return 0;
}