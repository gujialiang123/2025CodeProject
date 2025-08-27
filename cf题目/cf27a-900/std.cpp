#include <iostream>
using namespace std;
int a[300001];//注意：测试点没有题目给的那么小，开大点！！
int main(){
	int i,j,k,n;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>k;
		a[k]++;//输入n，它作为一个指针，它指向的数++
	}
	for(i=1;i<=300001;i++)
	if(a[i]==0){//一旦发现没有出现过，输出且程序结束
		cout<<i<<endl;
		return 0;
	}
	return 0;
}