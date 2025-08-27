#include<iostream>
#include<cstdio>
#include<algorithm>
#define f(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
inline int rd(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
inline void wt(int x){
	if(x<0) x=~x+1,putchar('-');
	if(x>9) wt(x/10);
	putchar(x%10+'0');
}
struct zkw{
	int l,r;
};
zkw a[1010];
int cmp(zkw a,zkw b){ //排序参数
	if(a.l==b.l) return a.r<b.r;
	return a.l<b.l;
}
int n,ans=0;
int yy[1010];
int main(){
	n=rd();
	f(i,1,n){
		a[i].l=rd();a[i].r=rd();
		if(a[i].l>a[i].r) swap(a[i].l,a[i].r);
	}
	sort(a+1,a+n+1,cmp);
	int la=a[1].r;//la为上一个记录点
	ans++;
	yy[ans]=la;
	f(i,2,n){ //对每一条线段一次判断
		if(a[i].l<=la && a[i].r>=la) continue;
		if(a[i].l>la){
			la=a[i].r;
			ans++;
			yy[ans]=la;
			continue;
		}
		if(a[i].r<la){
			la=a[i].r;
			yy[ans]=la;
			continue;
		}
	}
	wt(ans);
	putchar('\n');
	f(i,1,ans){
		wt(yy[i]);
		putchar(' ');
	} 
	return 0;
}