#include<map>
#include<cstdio>
#include<string>
#include<iostream>
using namespace std;int n,maxn;//maxnΪ���������Ǹ���ӽ�������nΪ�������
map<string,int>s;string ans,k;//s��ʾÿ֧��ӽ��򼸸���ans��ʾ���������Ǹ���ӣ�kΪ��������
int main()
{
	scanf("%d",&n);
	while(n--)
	 {
     	cin>>k;s[k]++;//���룬���Ҵ˶ӽ���
     	if(s[k]>maxn) {maxn=s[k];ans=k;}
     }
	cout<<ans;//����
}
