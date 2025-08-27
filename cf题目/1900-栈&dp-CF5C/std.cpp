#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn=1e6+1;//节省空间

char c[maxn];
int len,st[maxn];//数组模拟栈
bool a[maxn];//由于只用0和1，所以采用bool，操作方便，且节省空间
int maximum(int a,int b)//自己写max更快
{
    return a>b?a:b;
}
int main()
{
    int i,j,p=0,ans=0,sum=0,num=0;
    scanf("%s",c);
    len=strlen(c);
    for(i=0;i<len;i++)
    {
        if(c[i]=='(')
        {
            p++;
            st[p]=i;
        }
        else
        {
            if(p!=0)//栈是否为空，即是否有能匹配的
            {
                a[st[p]]=1;
                a[i]=1;
                p--;
            }
        }
    }
    for(i=0;i<=len;i++)
    {
        if(a[i])
        {
            sum++;
        }
        else
        {
            ans=maximum(ans,sum);
            sum=0;
        }
    }
    for(i=0;i<=len;i++)
    {
        if(a[i])
        {
            sum++;
        }
        else
        {
            if(sum==ans)
            {
                num++;
            }
            sum=0;
        }
    }
    if(ans==0)
    {
        cout<<"0 1";
    }
    else
    {
        cout<<ans<<' '<<num;
    }
    return 0;
}
