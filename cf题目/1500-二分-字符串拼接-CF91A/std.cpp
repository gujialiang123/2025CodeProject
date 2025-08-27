#include<bits/stdc++.h>
using namespace std;
vector<int>pos[300];//位置
int main()
{
	string s1,s2;
	int i,j,ans=0;
	cin>>s1>>s2;
	for(i=0;i<s1.size();i++)
		pos[s1[i]].push_back(i);
	for(i=0;i<s2.size();i++)
		if(pos[s2[i]].empty()) break;
	if(i<s2.size()) {cout<<-1;return 0;}
	for(i='a';i<='z';i++)
		pos[i].push_back(s1.size()+1);
	for(i=0;i<s2.size();)
	{
		ans++;
		j=*upper_bound(pos[s2[i]].begin(),pos[s2[i]].end(),-1);
		while(j<s1.size())
		{
			i++;
			if(i>=s2.size()) break;
			j=*upper_bound(pos[s2[i]].begin(),pos[s2[i]].end(),j);
		}
	}
	cout<<ans;
	return 0;
}