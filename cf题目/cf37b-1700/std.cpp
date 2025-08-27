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
	while(blood>0)//表示BOSS has been alive
	{
		int Max=0;
		for(int i=1;i<=n;i++)
		{
			//只要这个卷轴没被用过，并且可以用，而且取出能攻击的最大伤害
			//每一回合都能对BOSS造成伤害，那肯定是最优的
			if(((blood*100.0/stand_blood)<=a[i].pow) && (!used[i]) && a[i].dem>Max)
			{
				Max=a[i].dem;
				//uesd[i]=true;这个地方注意一下，就是我们还不确定到底需不需要用
				Max_num=i;
			}
		}
			//cout << Max_num<<" Test"<<endl; 
			if(Max!=0)//the demage can demage the BOSS this time
			{
				used[Max_num]=true;//把刚刚的卷轴给他用了
				sum_dem+=Max;//每一秒都需要伤害，那么把总伤害记录一下
				b[++num].number=Max_num;
				b[num].time=bound;//这一回合，也就是这一秒内，使用了该卷轴
			}
			blood-=sum_dem;// 伤害BOSS
			//cout<<sum_dem<<" --------test"<<endl;
			blood+=reb;//耍赖回血
			if(blood>stand_blood)//BOSS的血量不能超过本身的血量
			{
				blood=stand_blood;
			}
			if(blood==stand_blood)//回血之后回到了本来的血量
			{
				int cnt=0;
				for(int kkk=1;kkk<=n;kkk++)
				{
					if( (a[kkk].pow==100) &&(!used[kkk]) )//能用卷轴 
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
		bound++;//从 0 回合开始 
	}
}
int main()
{
	n=read(),blood=read(),reb=read();
	for(int i=1;i<=n;i++)
	{
		a[i].pow=read(),a[i].dem=read();
	}
	stand_blood=blood;//因为有个恢复而且不能超过本来的血量，先记录一下本来的血量
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
