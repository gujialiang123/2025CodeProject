#include<iostream>
using namespace std;
int a[1010];//开一个桶
int main(){
	freopen("cd37a-10.in","r",stdin);
	freopen("cd37a-10.out","w",stdout);
    int n,i,s=0,x,m=0;
    cin>>n;
    for(i=0;i<n;i++){
        cin>>x;
        a[x]++;//将对应桶的数量增加。
    }
    for(i=0;i<=1000;i++){
        if(a[i])m++;//找有的长度。
        if(a[i]>s)s=a[i];//找最多数量。
    }
    cout<<s<<" "<<m<<endl;
}

