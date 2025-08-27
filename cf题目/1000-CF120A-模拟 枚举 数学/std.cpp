#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
string a;
int main()
{
	int b;char ans;cin>>a>>b;
	if(a=="front")ans=(b==1)?'L':'R';
	if(a=="back")ans=(b==1)?'R':'L';
	cout<<ans;
	return 0;
}
