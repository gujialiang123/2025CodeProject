#include<algorithm>
#include<iostream>
#include<string>
#include<cmath>
using namespace std;
int main()
{
    int n,k;
    string s;
    cin>>n>>k;
    cin>>s;
    string Min = "~~~~~~~~~~~~~~~~", nw = "";
    for(int i=1;i<=s.size();i++){
        nw=s.substr(0,i);
        while(nw.size()<k) {
		    nw=nw+nw;
		}
        Min=min(Min,nw.substr(0,k));
    }
    cout<<Min<<endl;
    return 0;
}
