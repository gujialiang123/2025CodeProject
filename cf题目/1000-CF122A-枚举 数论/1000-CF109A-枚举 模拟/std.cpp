#include<bits/stdc++.h>//万能头文件好
using namespace std;
#define ll long long//个人习惯
int main(){
	ll n,i=0,j=0;
	//先定义好，i是4的个数，j是7的个数，一定要初始化为0
	scanf("%lld",&n);//输入
	i=n/4;n-=i*4;//前文的第一步
	if(n){
		while(i>0){
			n+=4;i--;
			if(n%7==0){j=n/7;n=0;break;}
			//前文的第二步
		}
	}
	if(n)printf("-1\n");
	//若还有剩余的，则无法满足条件，输出-1
	else{//否则
		while(i>=7){i-=7;j+=4;}//前文的第三步
		while(i--)printf("4");//输出4
		while(j--)printf("7");//输出7
		printf("\n");//换行是个好习惯
	}
	return 0;//over~
}
