#include<bits/stdc++.h>
using namespace std;
int a[101],b[101],c[101],d[101],n,num=0xffffff,ans,flag;//这里有一点要注意num要取一个足够大的数字
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
	cin>>a[i]>>b[i]>>c[i]>>d[i];//输入4个指标
    for(int i=1;i<=n;i++){
        flag=1;
        for(int j=1;j<=n;j++)
            if(a[i]<a[j] && b[i]<b[j] && c[i]<c[j])
	        flag=0;//查找是否过时
        if(flag)
            if(num>d[i])
		num=d[i],ans=i;//剩下的找价格最小值
    }
    cout<<ans;//输出
    return 0;
}
