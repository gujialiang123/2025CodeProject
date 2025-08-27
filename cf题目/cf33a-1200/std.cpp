#include<bits/stdc++.h>//万能头棒棒哒
using namespace std;
int n,m,k,x,c,p[1005],ans;
int main(){
    cin>>n>>m>>k;
    for (int i=1;i<=m;i++) p[i]=999999999;//初始化，尽量大
    for (int i=1;i<=n;i++){
    	cin>>x>>c;
    	p[x]=min(c,p[x]);//计算每排活力值
	}
	for (int i=1;i<=m;i++) ans+=p[i];//能力食物数
	cout<<min(k,ans)<<endl;//最终比大小
	return 0;
}