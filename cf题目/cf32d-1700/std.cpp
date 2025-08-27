#include<cstdio>

using namespace std;

#define rd(x) x=read()
#define rei register int

char a[310][310];

inline int read()//快读优化 
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int main(){
    int n,m,k,cnt=0;
    rd(n);rd(m);rd(k);
    for(rei i=1;i<=n;i++)
    	scanf(" %s",a[i]+1);
	int len=n<m?n:m;
    for(rei l=1;l<=len;l++){//暴力枚举答案 
		for(rei i=l+1;i+l<=n;i++){
			for(rei j=l+1;j+l<=m;j++){
    			if(a[i][j]=='*'&&a[i+l][j]=='*'&&a[i-l][j]=='*'&&a[i][j+l]=='*'&&a[i][j-l]=='*'){//一个个配对 
    				if(cnt+1==k){//继续配对 
						printf("%d %d\n",i,j);
						printf("%d %d\n",i-l,j);
						printf("%d %d\n",i+l,j);
						printf("%d %d\n",i,j-l);
						printf("%d %d",i,j+l);
    					return 0;//打印答案并结束 
    				}
    				else cnt++;
    			}
			}
		}
    }	
    printf("-1");//找不到答案 
    return 0;//大功告成！
}