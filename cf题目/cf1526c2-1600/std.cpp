#include <bits/stdc++.h>
using namespace std;
long long n;
priority_queue<long long,vector<long long>,less<long long> >q; //�����
int main() {
//	freopen("potions.in","r",stdin);
//	freopen("potions.out","w",stdout);
	cin>>n;
	long long ans=0,s=0;//ans��ҩ��ƿ�� s:��ǰ������
	for (int i=1; i<=n; i++) {
		long long x;
		cin>>x;
		if (x<0)
			q.push(-x); //���Ϊ����������ֵ���
		s+=x; //��ǰ�����ͼ�x
		ans++; //ҩ��ƿ����1
		if(s<0) {  //�������ֵ������������
			long long k=q.top(); //ȡ���������ľ���ֵ��������С�ĸ���
			s+=k; //�����ͻָ�k
			ans--; //ҩ��ƿ����1����Ϊ������һƿҩ��
			q.pop(); 
		}
	}
	cout<<ans;
	return 0;
}
