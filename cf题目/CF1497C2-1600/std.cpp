#include<bits/stdc++.h>
using namespace std;
int t,n,k;
int main()
{
   cin>>t;
   while(t--)
   {
    cin>>n>>k;
    for(int i=1;i<=k-3;i++)cout<<1<<' ';//�������������k-3��1
    n-=k-3;//��n��ȥk-3
    if(n%2)cout<<1<<' '<<n/2<<' '<<n/2<<'\n';
    else if(n%4)cout<<2<<' '<<n/2-1<<' '<<n/2-1<<'\n';
    else cout<<n/2<<' '<<n/4<<' '<<n/4<<'\n';
   }
   return 0;
}
