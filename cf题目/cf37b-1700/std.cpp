#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
struct juanzhou
{
	int pow,dem;
}a[maxn];
struct Uesd
{
	int time,number;
}b[maxn];
int n,blood,reb,bound,sum_dem,num=0,Max_num,stand_blood;
bool used[maxn];
bool cmp(Uesd x,Uesd y)
{
	return x.time<y.time;
}
bool flag=0;
void solve()
{
	while(blood>0)//��ʾBOSS has been alive
	{
		int Max=0;
		for(int i=1;i<=n;i++)
		{
			//ֻҪ�������û���ù������ҿ����ã�����ȡ���ܹ���������˺�
			//ÿһ�غ϶��ܶ�BOSS����˺����ǿ϶������ŵ�
			if(((blood*100.0/stand_blood)<=a[i].pow) && (!used[i]) && a[i].dem>Max)
			{
				Max=a[i].dem;
				//uesd[i]=true;����ط�ע��һ�£��������ǻ���ȷ�������費��Ҫ��
				Max_num=i;
			}
		}
			//cout << Max_num<<" Test"<<endl; 
			if(Max!=0)//the demage can demage the BOSS this time
			{
				used[Max_num]=true;//�Ѹոյľ����������
				sum_dem+=Max;//ÿһ�붼��Ҫ�˺�����ô�����˺���¼һ��
				b[++num].number=Max_num;
				b[num].time=bound;//��һ�غϣ�Ҳ������һ���ڣ�ʹ���˸þ���
			}
			blood-=sum_dem;// �˺�BOSS
			//cout<<sum_dem<<" --------test"<<endl;
			blood+=reb;//ˣ����Ѫ
			if(blood>stand_blood)//BOSS��Ѫ�����ܳ��������Ѫ��
			{
				blood=stand_blood;
			}
			if(blood==stand_blood)//��Ѫ֮��ص��˱�����Ѫ��
			{
				int cnt=0;
				for(int kkk=1;kkk<=n;kkk++)
				{
					if( (a[kkk].pow==100) &&(!used[kkk]) )//���þ��� 
					{
						break;
					}	
					cnt++;
				}
				if(cnt==n)
				{
					flag=1;
					return ;
				}
			}
		bound++;//�� 0 �غϿ�ʼ 
	}
}
int main()
{
	n=read(),blood=read(),reb=read();
	for(int i=1;i<=n;i++)
	{
		a[i].pow=read(),a[i].dem=read();
	}
	stand_blood=blood;//��Ϊ�и��ָ����Ҳ��ܳ���������Ѫ�����ȼ�¼һ�±�����Ѫ��
	solve();
	if(flag==1)
	{
		cout<<"NO"<<endl;
		return 0;
	}
	cout<<"YES"<<endl;
	cout<<bound<<" "<<num<<endl;
	sort(b+1,b+num+1,cmp);
	for(int i=1;i<=num;i++)
	{
		cout<<b[i].time<<" "<<b[i].number<<endl;
	}
	return 0;
}
