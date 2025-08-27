#include<bits/stdc++.h>
using namespace std;
int main()
{
 srand(time(NULL));
 freopen("cf1875d10.in","w",stdout);
 int t=rand()%50+1;
 cout<<t<<endl;
 while(t--)
 {
  int n=rand()%100+1;
  cout<<n<<endl;
  for(int i=1;i<=n;i++)
  cout<<rand()%1000000000<<" ";
  cout<<endl;
 }
 return 0;
}

