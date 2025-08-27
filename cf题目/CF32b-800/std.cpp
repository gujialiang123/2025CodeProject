#include<iostream>
using namespace std;
string s;
int main()
{
    cin>>s;
    int len=s.length();//测算长度
    for(int i=0;i<len;++i)//循环判断
    {
        if(s[i]=='.')//“.”是0，此时不用重置（想一想，为什么）
            cout<<0;
        if(s[i]=='-')//一条横分类讨论
        {
            if(s[i+1]=='.')//“-.”为1
                cout<<1;
            if(s[i+1]=='-')//“--”为2
                cout<<2;
            s[i+1]='?';//快乐重置
        }
    }
    return 0;
}