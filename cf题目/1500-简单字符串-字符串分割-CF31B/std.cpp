#include<bits/stdc++.h>
using namespace std;
string s;
int n,flag,p,cnt;
int main()
{
	cin>>s;
	n=s.length();
	if(s[0]=='@') {cout<<"No solution";return 0;}
	if(s[n-1]=='@') {cout<<"No solution";return 0;}
	for(int i=0;i<n;i++)
	{
		if(s[i]=='@' && p==0) {p=i;continue;}
		if(s[i]=='@' && i-p<=2) {flag=1;break;}
		if(s[i]=='@') p=i;
		else cnt++;
	}
	if(cnt==n) flag=1;
	if(flag) {cout<<"No solution";return 0;}
	cout<<s[0];cnt=0;
	for(int i=0;i<n;i++) if(s[i]=='@') cnt=i;
	for(int i=1;i<n;i++)
	{
		if(s[i-1]=='@'&& i-1<cnt) cout<<s[i]<<",";
		else cout<<s[i];
	}
	return 0;
}