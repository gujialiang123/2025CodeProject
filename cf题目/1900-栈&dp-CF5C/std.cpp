#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn=1e6+1;//��ʡ�ռ�

char c[maxn];
int len,st[maxn];//����ģ��ջ
bool a[maxn];//����ֻ��0��1�����Բ���bool���������㣬�ҽ�ʡ�ռ�
int maximum(int a,int b)//�Լ�дmax����
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
            if(p!=0)//ջ�Ƿ�Ϊ�գ����Ƿ�����ƥ���
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
