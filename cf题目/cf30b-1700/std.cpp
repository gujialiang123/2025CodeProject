#include<cstdio>
using namespace std;
int dd,mm,yy,bd,bm,by;
int day[20]={0,31,28,31,30,31,30,31,31,30,31,30,31};
//所有天数 
bool check(int d,int m,int y)
{
	if(d<1||d>day[m]+(m==2&&y%4==0)||m<1||m>12||y<1||y>99)
	//作越界判断 
	return false;
	return (yy-y>18||(yy-y==18&&m<mm)||(d<=dd&&m==mm&&yy-y==18));
	//满足一个就可以参加比赛 
}
int main()
{
	scanf("%d.%d.%d",&dd,&mm,&yy);
	scanf("%d.%d.%d",&bd,&bm,&by);
	if(check(bd,bm,by)||check(bd,by,bm)||check(bm,bd,by)||check(bm,by,bd)||check(by,bd,bm)||check(by,bm,bd))
	//枚举所有六种情况 
	printf("YES");
	else
	printf("NO");
	return 0;
}