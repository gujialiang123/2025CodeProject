#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
using namespace std;
int n,k;
int tree[105][105];
//树状数组 
inline int sum(int line,int x)
{
    int res=0;
    for(int i=x;i>=1;i-=lowbit(i))
        res+=tree[line][i];
    return res;
}
inline int query(int line,int l,int r)
{
    return sum(line,r)-sum(line,l-1);
}
inline void add(int line,int x)
{
    for(int i=x;i<=k;i+=lowbit(i))
        tree[line][i]++;
}
//同上，等差数列求和 
inline int cost(int l,int r)
{
    return (l+r)*(r-l+1)>>1;
}
int main()
{
    scanf("%d%d",&n,&k);
    int mid=(k>>1)+1;
    for(int i=1;i<=n;i++)
    {
        int m;
        scanf("%d",&m);
        int ansx=-1,ansy=-1;
        int minn=0x3f3f3f3f;
        for(int x=1;x<=k;x++)//枚举行 
            for(int y=1;y+m-1<=k;y++)//枚举列 
                if(query(x,y,y+m-1)==0)//如果这一片区域没有人坐 
                {
                    int tmp;
                    if(y>=mid) tmp=cost(y,y+m-1)-mid*m+abs(x-mid)*m;
                    else if(y+m-1<=mid) tmp=mid*m-cost(y,y+m-1)+abs(x-mid)*m;
                    else tmp=abs(x-mid)*m+cost(mid,y+m-1)-(y+m-mid)*mid+mid*(mid-y)-cost(y,mid-1);//同前 
                    if(tmp<minn)
                    {
                        minn=tmp;
                        ansx=x;
                        ansy=y;
                    }
                }
        if(minn!=0x3f3f3f3f)
        {
            printf("%d %d %d\n",ansx,ansy,ansy+m-1);
            for(int j=ansy;j<=ansy+m-1;j++)
                add(ansx,j); 
        }
        else puts("-1");
    }
    return 0;
}