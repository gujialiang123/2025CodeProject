#include<iostream>
using namespace std;
int a[1010];//��һ��Ͱ
int main(){
	freopen("cd37a-10.in","r",stdin);
	freopen("cd37a-10.out","w",stdout);
    int n,i,s=0,x,m=0;
    cin>>n;
    for(i=0;i<n;i++){
        cin>>x;
        a[x]++;//����ӦͰ���������ӡ�
    }
    for(i=0;i<=1000;i++){
        if(a[i])m++;//���еĳ��ȡ�
        if(a[i]>s)s=a[i];//�����������
    }
    cout<<s<<" "<<m<<endl;
}

