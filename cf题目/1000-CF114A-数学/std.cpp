#include<bits/stdc++.h>
using namespace std;
long long a,b,n;
bool ans=0;
int main()
{
    cin>>a>>b;//输入
    while(b>0)//
    {
        if(b==1)//1就直接退（因为b>=2，所以说明成功了）
        {
            ans=0;//其实没有用
            break;
        }
        if(b%a!=0)//mod出现余数
        {
            ans=1;
            break;
        }
        n++;//去的位数
        b=b/a;//b除a
    }
    if(ans==0)//YES
    {
        cout<<"YES"<<endl;
        cout<<n-1<<endl;//一定要-1
    }
    else//NO
    cout<<"NO"<<endl;
    return 0;
}
