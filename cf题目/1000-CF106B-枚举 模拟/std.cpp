#include<bits/stdc++.h>
using namespace std;
int a[101],b[101],c[101],d[101],n,num=0xffffff,ans,flag;//������һ��Ҫע��numҪȡһ���㹻�������
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
	cin>>a[i]>>b[i]>>c[i]>>d[i];//����4��ָ��
    for(int i=1;i<=n;i++){
        flag=1;
        for(int j=1;j<=n;j++)
            if(a[i]<a[j] && b[i]<b[j] && c[i]<c[j])
	        flag=0;//�����Ƿ��ʱ
        if(flag)
            if(num>d[i])
		num=d[i],ans=i;//ʣ�µ��Ҽ۸���Сֵ
    }
    cout<<ans;//���
    return 0;
}
