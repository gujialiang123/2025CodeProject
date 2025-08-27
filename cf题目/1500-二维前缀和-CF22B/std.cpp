#include<bits/stdc++.h>
using namespace std;
char ch[30][30];
int ans;
int main()
{
	int n, m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) cin>>ch[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=i;k<=n;k++)
				for(int l=j;l<=m;l++)
				{
					int I=i,J=j;
					while(J<l && ch[I][J]=='0') J++;
					if(J!=l) break;
					while(I<k && ch[I][J]=='0') I++;
					if(I!=k) break;
					while(J>j && ch[I][J]=='0') J--;
					if(J!=j) break;
					while(I>i && ch[I][J]=='0') I--;
					if(I!=i) break;
					ans=max(ans,2*(k-i+1+l-j+1));
				}
	cout<<ans<<endl;
 return 0;
}