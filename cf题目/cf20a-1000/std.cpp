#include<bits/stdc++.h>
using namespace std;
string s;
int l;
bool flag=0;
int main()
{
    cin>>s;
    l=s.size();
    while(s[l-1]=='/'&&l>=1) l--;
    if(!l) cout<<"/"<<endl;//需要特判的两种情况
    if(l==1) cout<<s[0]<<endl;
    for(register int i=0;i<l;i++)
    {
        if(flag)//如果之前有过斜杠了
        {
            if(s[i]!='/'){
                cout<<s[i];
                flag=0;
            }
        }
        else//如果之前没有斜杠
        {
            cout<<s[i];
            if(s[i]=='/') flag=1;
        }
    }
    return 0;
}