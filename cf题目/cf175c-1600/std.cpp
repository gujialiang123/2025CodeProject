#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,t;
int p[105],f=1,ans,num,cnt,tmp;
struct node
{
	int k,c;
}a[105];
bool cmp(node a,node b)
{
	return a.c<b.c;
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld%lld",&a[i].k,&a[i].c);
	sort(a+1,a+n+1,cmp);//�������뵽�Ľṹ������
	scanf("%lld",&t);
	for(int i=1;i<=t;i++) scanf("%lld",&p[i]);
	for(int i=1;i<=n;i++)
	{
		if(f==t+1)//���������������ѭ��
		{
			tmp=i;
			break;
		}
		if(num+a[i].k<p[f])//��һ�����
		{
			num+=a[i].k;
			ans+=a[i].k*f*a[i].c;
		}
		else if(num+a[i].k==p[f])//��Ϊ�������⴦�����Ե�������һ����ȵ����
		{
			num=p[f];
			ans+=a[i].k*f*a[i].c;
			f++;
		}
		else//�ڶ������
		{
			ans+=(p[f]-num)*f*a[i].c;//���뵱ǰ��p
			a[i].k-=p[f]-num;
			num=p[f];
			f++;
			i--;//�����¿���һ�鵱ǰa������
		}
	}
	if(tmp)//�������������ѭ����ļ����
	{
		for(int i=tmp;i<=n;i++) ans+=a[i].k*f*a[i].c;
	}
	printf("%lld",ans);
	return 0;
}
