#include <cstdio>
#include <iostream>
using namespace std;
int a,b,x,y;//原长a,b，比例x,y
int gcd(int n,int m){
	if(n<m) swap(n,m);
	return n==0?n:gcd(m,n%m);
}//辗转相除法求最小公约数
int main() {
	cin>>a>>b>>x>>y;
	//为避免x：y不是最简整数比，找出x,y的最小公约数进行化简
    int k=gcd(x,y);
	x/=k,y/=k;//直接除
	if(a<x||b<y){//特判：a或者b不能拆成x,y组成的小段（就是说x>a或y>b)则无解
		printf("0 0");
		return 0;
	}
	int base=min(a/x,b/y);//a/x表示a被拆分的数量，b/x同理，找出a,b范围内的最大段数
	printf("%d %d",x*base,y*base);//用最大段数乘上x,y得解
	return 0;
}