#include<iostream>
using namespace std;
int n,a[100005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=2;i<n;i++){//不要越界
		if(a[1]<a[i]&&a[i]>a[i+1]){//条件一
			cout<<3<<endl<<1<<' '<<i<<' '<<i+1;
			return 0;
		}
		if(a[1]>a[i]&&a[i]<a[i+1]){//条件二
			cout<<3<<endl<<1<<' '<<i<<' '<<i+1;
			return 0;
		}
	}
	cout<<0;
	return 0;
}