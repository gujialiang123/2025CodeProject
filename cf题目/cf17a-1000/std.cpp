#include<bits/stdc++.h>
using namespace std;
inline int read(){//快读 
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
int n,k,cnt,ans,p[1005];
bool f[1005];
void init(){//筛法 
	for(int i=2;i<=n;i++)
		if(!f[i]){
			p[++cnt]=i;
			for(int j=i*2;j<=n;j+=i)f[j]=1;
		}
}
int main(){
	n=read(),k=read();
	init();//筛素数 
	for(int i=3;i<=cnt&&ans<k;i++){ //从3开始，只要枚举完或满足条件就退出 
		for(int j=1;j<i-1;j++)//枚举相邻的两个素数 
		    if(p[j]+p[j+1]+1==p[i]){//满足条件 ，是好素数 
		    	ans++;
		    	break;
		    }
	}
	puts(ans==k?"YES":"NO");//输出 
	return 0;
}